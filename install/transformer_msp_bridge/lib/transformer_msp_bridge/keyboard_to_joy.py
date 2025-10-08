#!/usr/bin/env python3
"""Keyboard-to-Joy helper that emulates a single joystick for tank steering.

Behavior (terminal must have focus):
    - Up (Forward): both tracks forward
    - Left: only right track forward
    - Up + Left: both forward but RIGHT faster (left slower)
    - Right: only left track forward (symmetry)
    - Up + Right: both forward but LEFT faster (right slower)
    - Keys must be held to drive; release returns to zero.
    - q = quit, SPACE = immediate stop

Parameters:
    - joy_topic (default '/joy')
    - left_axis_index (default 1)
    - right_axis_index (default 4)
    - axes_count (default 8)
    - publish_rate_hz (default 50.0)
    - forward_speed (default 1.0)         # value used for forward (maps to max RC by mapper)
    - turn_inside_factor (default 0.5)    # scale for inside track when turning with forward
    - hold_timeout_sec (default 0.60)     # consider key held if last repeat within this window
    - min_press_latch_sec (default 0.10)  # always hold for at least this after an initial press
"""
import sys
import termios
import tty
import fcntl
import os
import time


import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy


class TerminalRaw:
    """Put terminal in raw, non-blocking mode to read key sequences."""

    def __init__(self):
        """Save terminal state and prepare descriptors."""
        self.fd = sys.stdin.fileno()
        self.old_attrs = termios.tcgetattr(self.fd)
        self.old_flags = fcntl.fcntl(self.fd, fcntl.F_GETFL)

    def __enter__(self):
        """Enter raw mode and set non-blocking input."""
        tty.setcbreak(self.fd)
        fcntl.fcntl(self.fd, fcntl.F_SETFL, self.old_flags | os.O_NONBLOCK)
        return self

    def __exit__(self, exc_type, exc, tb):
        """Restore previous terminal state."""
        termios.tcsetattr(self.fd, termios.TCSADRAIN, self.old_attrs)
        fcntl.fcntl(self.fd, fcntl.F_SETFL, self.old_flags)


class KeyboardToJoy(Node):
    """Publish Joy messages based on arrow keys with hold-only driving semantics."""

    def __init__(self):
        """Initialize parameters, state, and timers."""
        super().__init__('keyboard_to_joy')
        # Params
        self.declare_parameter('joy_topic', '/joy')
        self.declare_parameter('left_axis_index', 1)
        self.declare_parameter('right_axis_index', 4)
        self.declare_parameter('axes_count', 8)
        self.declare_parameter('publish_rate_hz', 50.0)
        self.declare_parameter('forward_speed', 1.0)
        self.declare_parameter('turn_inside_factor', 0.5)
        self.declare_parameter('hold_timeout_sec', 0.60)
        self.declare_parameter('min_press_latch_sec', 0.10)

        self.joy_topic = self.get_parameter('joy_topic').get_parameter_value().string_value
        self.left_axis = int(self.get_parameter('left_axis_index').value)
        self.right_axis = int(self.get_parameter('right_axis_index').value)
        self.axes_count = int(self.get_parameter('axes_count').value)
        self.rate_hz = float(self.get_parameter('publish_rate_hz').value)
        self.forward_speed = float(self.get_parameter('forward_speed').value)
        self.turn_inside_factor = float(self.get_parameter('turn_inside_factor').value)
        self.hold_timeout_sec = float(self.get_parameter('hold_timeout_sec').value)
        self.min_press_latch_sec = float(self.get_parameter('min_press_latch_sec').value)

        self.axes = [0.0] * self.axes_count
        self.buttons = []

        # Key state timestamps (monotonic seconds); 0.0 = not pressed
        self._t_up = 0.0
        self._t_left = 0.0
        self._t_right = 0.0
        # Latch windows to suppress immediate dropouts at press start
        self._lat_up = 0.0
        self._lat_left = 0.0
        self._lat_right = 0.0

        self.pub = self.create_publisher(Joy, self.joy_topic, 10)
        self.timer = self.create_timer(1.0 / max(1e-3, self.rate_hz), self._tick)
        self.get_logger().info('KeyboardToJoy: arrows drive while held; SPACE stop; q quit')

        self._term = TerminalRaw()
        self._term.__enter__()
        self._quit = False
        self._keybuf = ''  # accumulate partial escape sequences

    def destroy_node(self):
        """Tear down node and restore terminal settings."""
        try:
            self._term.__exit__(None, None, None)
        except Exception:
            pass
        super().destroy_node()

    def _read_keys(self) -> None:
        """Read any pending chars from stdin and append to buffer."""
        try:
            chunk = sys.stdin.read()
            if chunk:
                self._keybuf += chunk
        except Exception:
            pass

    @staticmethod
    def _clamp(x: float, lo: float, hi: float) -> float:
        return max(lo, min(hi, x))

    def _apply_key(self, ch: str):
        """Non-arrow simple keys: q quit, SPACE stop."""
        if ch == 'q':
            self._quit = True
            return
        if ch == ' ':
            self._t_up = self._t_left = self._t_right = 0.0
            if self.left_axis < self.axes_count:
                self.axes[self.left_axis] = 0.0
            if self.right_axis < self.axes_count:
                self.axes[self.right_axis] = 0.0
            return

    def _tick(self):
        if self._quit:
            rclpy.shutdown()
            return
        # Read and process any new keys
        self._read_keys()
        self._process_key_buffer()
        # Compute axes based on arrows held
        now = time.monotonic()
        up = (now <= self._lat_up) or ((now - self._t_up) <= self.hold_timeout_sec)
        left = (now <= self._lat_left) or ((now - self._t_left) <= self.hold_timeout_sec)
        right = (now <= self._lat_right) or ((now - self._t_right) <= self.hold_timeout_sec)

        left_val = 0.0
        right_val = 0.0
        base = self.forward_speed
        inside = max(0.0, min(1.0, self.turn_inside_factor)) * base

        if up:
            if left and not right:
                left_val, right_val = inside, base
            elif right and not left:
                left_val, right_val = base, inside
            else:
                left_val, right_val = base, base
        else:
            if left and not right:
                left_val, right_val = 0.0, base
            elif right and not left:
                left_val, right_val = base, 0.0
            else:
                left_val, right_val = 0.0, 0.0

        if self.left_axis < self.axes_count:
            self.axes[self.left_axis] = self._clamp(left_val, -1.0, 1.0)
        if self.right_axis < self.axes_count:
            self.axes[self.right_axis] = self._clamp(right_val, -1.0, 1.0)
        msg = Joy()
        msg.axes = self.axes
        msg.buttons = self.buttons
        self.pub.publish(msg)

    def _process_key_buffer(self):
        """Parse buffered keys, including ANSI arrow sequences (ESC [ A/B/C/D)."""
        s = self._keybuf
        i = 0
        n = len(s)
        while i < n:
            ch = s[i]
            if ch == '\x1b':  # ESC
                # Need at least ESC [ X
                if i + 2 >= n:
                    break  # incomplete, keep for next tick
                if s[i + 1] == '[':
                    code = s[i + 2]
                    handled = self._handle_arrow(code)
                    if handled:
                        i += 3
                        continue
                # Unrecognized sequence; skip ESC
                i += 1
                continue
            else:
                self._apply_key(ch)
                i += 1
        # Keep any unconsumed tail (partial sequence)
        self._keybuf = s[i:]

    def _handle_arrow(self, code: str) -> bool:
        """Handle ANSI arrow code: A=up, B=down, C=right, D=left."""
        # Record last-seen time for arrow keys (press/auto-repeat)
        t = time.monotonic()
        if code == 'A':  # Up
            self._t_up = t
            self._lat_up = max(self._lat_up, t + self.min_press_latch_sec)
            return True
        if code == 'B':  # Down (ignored for forward-only; treat as stop pulse)
            # Optionally could clear timers, but leaving as no-op is fine.
            return True
        if code == 'C':  # Right
            self._t_right = t
            self._lat_right = max(self._lat_right, t + self.min_press_latch_sec)
            return True
        if code == 'D':  # Left
            self._t_left = t
            self._lat_left = max(self._lat_left, t + self.min_press_latch_sec)
            return True
        return False


def main():
    """Entry point: start node and spin until quit or Ctrl-C."""
    rclpy.init()
    node = KeyboardToJoy()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
