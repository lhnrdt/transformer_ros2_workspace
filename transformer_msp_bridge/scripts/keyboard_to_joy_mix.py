#!/usr/bin/env python3

"""
ROS 2 node: keyboard_to_joy_mix.

Publishes sensor_msgs/msg/Joy on /joy based on arrow key input with the mapping:
- left  -> axis[3] = -1.0, axis[1] = 0.0
- right -> axis[3] =  1.0, axis[1] = 0.0
- up    -> axis[3] =  0.0, axis[1] = 1.0
- left+up       -> axis[3] = -0.5, axis[1] = 0.5
- right+up      -> axis[3] =  0.5, axis[1] = 0.5
- left+right    -> axis[3] =  0.0, axis[1] = 0.0
- left+right+up -> axis[3] =  0.0, axis[1] = 1.0

Notes/Assumptions:
- Throttle axis index is 1; steering axis index is 3.
- Uses python-evdev to get true key down/up events (no artificial delays).
- You may need permissions to read /dev/input/event* (run as sudo or add udev rules).
"""

from __future__ import annotations

import threading
import argparse
from threading import Lock
from dataclasses import dataclass
from typing import Optional

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy


try:
    from evdev import InputDevice, ecodes, list_devices
except Exception:  # pragma: no cover - handled at runtime
    InputDevice = None  # type: ignore
    ecodes = None  # type: ignore
    list_devices = None  # type: ignore

# Optional preferred backend: pynput (global key press/release without root)
try:
    from pynput import keyboard as pynput_keyboard  # type: ignore
except Exception:  # pragma: no cover - handled at runtime
    pynput_keyboard = None  # type: ignore


AXIS_THROTTLE = 1  # index 1
AXIS_STEER = 3     # index 3
NUM_AXES = max(AXIS_THROTTLE, AXIS_STEER) + 1 if max(AXIS_THROTTLE, AXIS_STEER) + 1 >= 4 else 4
NUM_BUTTONS = 12


@dataclass
class KeyState:
    """Tracks pressed state of relevant keys and computes axes."""

    left: bool = False
    right: bool = False
    up: bool = False

    def compute_axes(self):
        """Compute (throttle, steer) for the current key state."""
        # Compute steering first
        steer = 0.0
        if self.left and not self.right:
            steer = -1.0
        elif self.right and not self.left:
            steer = 1.0
        else:
            steer = 0.0  # both or none -> 0

        # Compute throttle
        if self.up:
            if steer == 0.0:
                throttle = 1.0
            else:
                throttle = 0.5
                steer *= 0.5
        else:
            throttle = 0.0

        return throttle, steer


class KeyboardToJoyNode(Node):
    """ROS 2 node that converts keyboard arrow keys to Joy messages."""

    def __init__(self, device_path: Optional[str] = None, backend: str = 'auto', verbose: bool = False):
        """Initialize the node and start the input reader thread.

        Args:
            device_path: Optional explicit evdev device path (e.g., '/dev/input/event3').
            backend: 'auto' (default), 'pynput', or 'evdev'.
        """
        super().__init__('keyboard_to_joy_mix')
        self.pub = self.create_publisher(Joy, '/joy', 10)
        self.state = KeyState()
        self._lock = Lock()
        self.verbose = verbose

        # Choose backend
        self._backend = None
        self._listener = None  # for pynput
        self.device = None     # for evdev

        chosen = backend
        if chosen == 'auto':
            if pynput_keyboard is not None:
                chosen = 'pynput'
            else:
                chosen = 'evdev'

        if chosen == 'pynput':
            if pynput_keyboard is None:
                self.get_logger().warn('pynput not available; falling back to evdev backend.')
                chosen = 'evdev'
            else:
                self._backend = 'pynput'
                self._start_pynput()
                self.get_logger().info('Keyboard backend: pynput (global listener)')

        if self._backend is None and chosen == 'evdev':
            # Initialize evdev input device
            self.device = self._pick_input_device(device_path)
            if self.device is None:
                self.get_logger().error(
                    'No suitable keyboard input device found. Install pynput or ensure python-evdev is installed and you have permissions to read /dev/input/event*.'
                )
                raise RuntimeError('Keyboard input device not found')

            # Spawn background thread to read events without delays
            self.thread = threading.Thread(target=self._reader_loop_evdev, name='keyboard_evdev_reader', daemon=True)
            self.thread.start()
            self._backend = 'evdev'
            self.get_logger().info('Keyboard backend: evdev (device events)')

        # Publish an initial neutral Joy so subscribers see activity immediately
        self._publish_joy()

    def _pick_input_device(self, device_path: Optional[str]) -> Optional[InputDevice]:  # type: ignore
        if InputDevice is None or list_devices is None or ecodes is None:
            return None

        try:
            if device_path:
                return InputDevice(device_path)

            # Auto-pick: find first device that supports EV_KEY and common arrow keys
            for path in list_devices():
                try:
                    dev = InputDevice(path)
                    caps = dev.capabilities(verbose=False)
                    if ecodes.EV_KEY in caps:
                        # Heuristic: a keyboard typically has KEY_LEFT, KEY_RIGHT, KEY_UP
                        key_codes = caps.get(ecodes.EV_KEY, [])
                        keys = set(key_codes)
                        if {ecodes.KEY_LEFT, ecodes.KEY_RIGHT, ecodes.KEY_UP}.issubset(keys):
                            self.get_logger().info(f'Using keyboard device: {dev.path} ({dev.name})')
                            return dev
                except Exception:
                    continue
        except Exception as e:
            self.get_logger().error(f'Error while scanning input devices: {e}')
            return None

        return None

    def _start_pynput(self):
        assert pynput_keyboard is not None

        def on_press(key):
            print("Button pressed")
            changed = False
            with self._lock:
                if key == pynput_keyboard.Key.left:
                    prev = self.state.left
                    self.state.left = True
                    changed = changed or (self.state.left != prev)
                elif key == pynput_keyboard.Key.right:
                    prev = self.state.right
                    self.state.right = True
                    changed = changed or (self.state.right != prev)
                elif key == pynput_keyboard.Key.up:
                    prev = self.state.up
                    self.state.up = True
                    changed = changed or (self.state.up != prev)
            if changed:
                self._publish_joy()

        def on_release(key):
            changed = False
            with self._lock:
                if key == pynput_keyboard.Key.left:
                    prev = self.state.left
                    self.state.left = False
                    changed = changed or (self.state.left != prev)
                elif key == pynput_keyboard.Key.right:
                    prev = self.state.right
                    self.state.right = False
                    changed = changed or (self.state.right != prev)
                elif key == pynput_keyboard.Key.up:
                    prev = self.state.up
                    self.state.up = False
                    changed = changed or (self.state.up != prev)
            if changed:
                self._publish_joy()

        self._listener = pynput_keyboard.Listener(on_press=on_press, on_release=on_release)
        self._listener.start()

    def _reader_loop_evdev(self):
        dev = self.device
        assert dev is not None
        for event in dev.read_loop():  # blocking; no sleeps, event-driven
            if event.type != ecodes.EV_KEY:
                continue

            code = event.code
            val = event.value  # 1=down, 0=up, 2=repeat
            changed = False

            if code == ecodes.KEY_LEFT:
                with self._lock:
                    prev = self.state.left
                    self.state.left = (val == 1)
                    changed = (self.state.left != prev)
            elif code == ecodes.KEY_RIGHT:
                with self._lock:
                    prev = self.state.right
                    self.state.right = (val == 1)
                    changed = (self.state.right != prev)
            elif code == ecodes.KEY_UP:
                with self._lock:
                    prev = self.state.up
                    self.state.up = (val == 1)
                    changed = (self.state.up != prev)
            else:
                continue

            if changed:
                self._publish_joy()

    def _publish_joy(self):
        with self._lock:
            throttle, steer = self.state.compute_axes()

        msg = Joy()
        # Prepare arrays
        msg.axes = [0.0] * max(NUM_AXES, 8)  # allocate at least 8 axes as many consumers expect
        msg.buttons = [0] * NUM_BUTTONS
        msg.axes[AXIS_THROTTLE] = float(throttle)
        msg.axes[AXIS_STEER] = float(steer)

        # header stamp may be left default; many consumers only read axes/buttons
        self.pub.publish(msg)
        if self.verbose:
            self.get_logger().info(f'joy axes: [1]={msg.axes[AXIS_THROTTLE]:.2f}, [3]={msg.axes[AXIS_STEER]:.2f}')


def main(argv=None):
    """Entry point for the keyboard_to_joy_mix node."""
    parser = argparse.ArgumentParser(add_help=True)
    parser.add_argument('--device', type=str, default=None, help='evdev device path, e.g. /dev/input/event3')
    parser.add_argument('--backend', type=str, choices=['auto', 'pynput', 'evdev'], default='auto', help='Keyboard input backend to use')
    parser.add_argument('-v', '--verbose', action='store_true', help='Enable verbose logging')
    args, ros_args = parser.parse_known_args(argv)

    rclpy.init(args=ros_args)
    node = None
    try:
        node = KeyboardToJoyNode(device_path=args.device, backend=args.backend, verbose=args.verbose)
        rclpy.spin(node)  # spin keeps process alive; events come from input thread
    except Exception as e:
        if node is not None:
            node.get_logger().error(str(e))
        else:
            print(f'keyboard_to_joy_mix error: {e}')
    finally:
        if node is not None:
            node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
