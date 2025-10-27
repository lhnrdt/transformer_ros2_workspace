#!/usr/bin/env python3
"""ROS 2 node: joystick_tank_to_rc.

Maps Joy axes to forward-only RC PWM for left/right tracks.

Defaults updated to match the provided Joy layout:
- input_mode = 'mix'
- throttle_axis = 1  (axes[1])
- steer_axis = 3     (axes[3], positive = steer left)
- left_axis = 2      (axes[2], direct mode; 1.0 = 0%, -1.0 = 100%)
- right_axis = 5     (axes[5], direct mode; 1.0 = 0%, -1.0 = 100%)
- steer_left_positive = True (invert steer sign internally to match mixing logic)
- direct_axes_invert = True  (invert direct axes so -1.0 -> full forward)
- left_channel_index = 10 (ch11)
- right_channel_index = 11 (ch12)
- channel_count = 16
"""
from typing import List

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from std_msgs.msg import UInt16MultiArray

# Fallback/default axes when Joy message is empty or too short.
# Intentionally all zeros to avoid unintended motion when joystick data is missing.
DEFAULT_AXES: List[float] = [0.0] * 8


def norm_to_pwm(x: float, deadzone: float = 0.00, min_pwm: int = 1000, max_pwm: int = 2000) -> int:
    """Forward-only mapping from joystick to PWM.

    - Input x in [-1, 1]
    - Apply deadzone around 0
    - For forward-only motors: x <= 0 maps to min_pwm (stop), x > 0 maps linearly to [min_pwm, max_pwm]
    """
    # Deadzone around 0 to avoid drift
    if abs(x) < deadzone:
        x = 0.0
    # Forward-only: negatives and zero -> 0, positives -> [0,1]
    y = max(0.0, x)  # [0,1]
    pwm = int(min_pwm + y * (max_pwm - min_pwm))
    return max(min_pwm, min(max_pwm, pwm))


class JoystickTankToRC(Node):
    """Map Joy axes to forward-only RC PWM for left/right tracks."""

    def __init__(self):
        """Declare parameters, subscribe to Joy, and publish RC override."""
        super().__init__('joystick_tank_to_rc')
        # Parameters
        self.declare_parameter('joy_topic', '/joy')
        self.declare_parameter('rc_topic', '/msp/rc_override')
        # Input mode: 'direct' uses left_axis/right_axis directly;
        # 'mix' uses throttle_axis and steer_axis to compute left/right.
        self.declare_parameter('input_mode', 'mix')  # 'direct' or 'mix'
        # Updated axes to match annotated message
        self.declare_parameter('left_axis', 2)          # direct mode: left motor throttle (axes[2])
        self.declare_parameter('right_axis', 5)         # direct mode: right motor throttle (axes[5])
        self.declare_parameter('throttle_axis', 1)      # mix mode: forward throttle axis (axes[1])
        self.declare_parameter('steer_axis', 3)         # mix mode: steering axis (axes[3])
        # Axis interpretation options (defaults chosen to match provided semantics)
        self.declare_parameter('steer_left_positive', True)  # Positive steer means 'left' per sample
        self.declare_parameter('direct_axes_invert', True)   # Direct axes: 1.0->0%, -1.0->100%
        self.declare_parameter('min_pwm', 1540)
        self.declare_parameter('max_pwm', 1600)
        self.declare_parameter('deadzone', 0.05)
        self.declare_parameter('channel_count', 16)
        self.declare_parameter('left_channel_index', 10)   # ch11 -> index 10
        self.declare_parameter('right_channel_index', 11)  # ch12 -> index 11

        self.joy_topic = self.get_parameter('joy_topic').get_parameter_value().string_value
        self.rc_topic = self.get_parameter('rc_topic').get_parameter_value().string_value
        self.input_mode = self.get_parameter('input_mode').get_parameter_value().string_value
        self.left_axis = int(self.get_parameter('left_axis').value)
        self.right_axis = int(self.get_parameter('right_axis').value)
        self.throttle_axis = int(self.get_parameter('throttle_axis').value)
        self.steer_axis = int(self.get_parameter('steer_axis').value)
        self.steer_left_positive = bool(self.get_parameter('steer_left_positive').value)
        self.direct_axes_invert = bool(self.get_parameter('direct_axes_invert').value)
        self.min_pwm = int(self.get_parameter('min_pwm').value)
        self.max_pwm = int(self.get_parameter('max_pwm').value)
        if self.max_pwm < self.min_pwm:
            self.get_logger().warn('max_pwm is less than min_pwm; adjusting max_pwm to match min_pwm')
            self.max_pwm = self.min_pwm
        self.deadzone = float(self.get_parameter('deadzone').value)
        self.channel_count = int(self.get_parameter('channel_count').value)
        self.left_channel = int(self.get_parameter('left_channel_index').value)
        self.right_channel = int(self.get_parameter('right_channel_index').value)

        self.pub = self.create_publisher(UInt16MultiArray, self.rc_topic, 10)
        self.sub = self.create_subscription(Joy, self.joy_topic, self.on_joy, 10)
        self.get_logger().info(
            f'Listening to {self.joy_topic} -> publishing RC to {self.rc_topic} (left ch {self.left_channel+1}, right ch {self.right_channel+1})'
        )

    def on_joy(self, msg: Joy):
        """Convert Joy axes to left/right PWM values and publish RC."""
        axes: List[float] = msg.axes if msg.axes else DEFAULT_AXES

        # Helper to safely access an axis with fallback to DEFAULT_AXES (then 0.0)
        def get_axis(idx: int) -> float:
            if 0 <= idx < len(axes):
                return axes[idx]
            if 0 <= idx < len(DEFAULT_AXES):
                return DEFAULT_AXES[idx]
            return 0.0

        if self.input_mode == 'mix':
            # Read throttle and steer, guard indices
            thr = get_axis(self.throttle_axis)
            steer = get_axis(self.steer_axis)
            # By default, sample indicates positive steer = left, but mix logic assumes negative = left
            # So invert steer to align with internal logic when configured
            if self.steer_left_positive:
                steer = -steer
            # Apply deadzone around zero
            thr = 0.0 if abs(thr) < self.deadzone else thr
            steer = 0.0 if abs(steer) < self.deadzone else steer

            # Forward-only: negative throttle is treated as zero
            thr = max(0.0, thr)

            # Compute left/right in [0,1]
            left_n = 0.0
            right_n = 0.0
            if thr > 0.0:
                left_n = thr
                right_n = thr
                if steer < 0.0:
                    # Turning left: reduce left track proportionally to |steer|
                    left_n = thr * (1.0 + steer)  # steer negative
                elif steer > 0.0:
                    # Turning right: reduce right track
                    right_n = thr * (1.0 - steer)
                # clamp
                left_n = max(0.0, min(1.0, left_n))
                right_n = max(0.0, min(1.0, right_n))
            else:
                # No throttle: allow in-place bias for forward-only motors
                if steer < 0.0:
                    left_n = 0.0
                    right_n = min(1.0, -steer)
                elif steer > 0.0:
                    left_n = min(1.0, steer)
                    right_n = 0.0
                else:
                    left_n = right_n = 0.0

            left_pwm = norm_to_pwm(left_n, 0.0, self.min_pwm, self.max_pwm)
            right_pwm = norm_to_pwm(right_n, 0.0, self.min_pwm, self.max_pwm)
        else:
            # Direct mode: read left/right axes directly
            lx = get_axis(self.left_axis)
            rx = get_axis(self.right_axis)
            # Invert per provided semantics (1.0 -> 0%, -1.0 -> 100%)
            if self.direct_axes_invert:
                lx = -lx
                rx = -rx
            left_pwm = norm_to_pwm(lx, self.deadzone, self.min_pwm, self.max_pwm)
            right_pwm = norm_to_pwm(rx, self.deadzone, self.min_pwm, self.max_pwm)

        arr = [self.min_pwm] * self.channel_count
        # Forward-only tank: map to channels 11 and 12 (indices 10, 11)
        if self.left_channel < self.channel_count:
            arr[self.left_channel] = left_pwm
        if self.right_channel < self.channel_count:
            arr[self.right_channel] = right_pwm

        out = UInt16MultiArray()
        out.data = arr
        self.pub.publish(out)


def main():
    """Entry point to start the node and spin it."""
    rclpy.init()
    node = JoystickTankToRC()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
