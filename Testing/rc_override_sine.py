#!/usr/bin/env python3
import math
import time

import rclpy
from rclpy.node import Node
from std_msgs.msg import UInt16MultiArray


class RcOverrideSine(Node):
    def __init__(self, rate_hz: float = 50.0, channel_index: int = 9):
        super().__init__('rc_override_sine')
        self.pub = self.create_publisher(UInt16MultiArray, '/msp/rc_override', 10)
        self.rate_hz = rate_hz
        self.dt = 1.0 / rate_hz
        self.t = 0.0
        # Channel index is zero-based. channel_index=9 corresponds to channel 10.
        self.channel_index = channel_index
        # Number of channels to publish (adjust to match node param rc_channel_count)
        self.channel_count = 16
        self.timer = self.create_timer(self.dt, self.tick)
        self.get_logger().info(
            f'Publishing sine on channel {self.channel_index+1} at {self.rate_hz:.1f} Hz'
        )

    def tick(self):
        # Generate sinusoid around 1500 with amplitude 400 (range 1100..1900)
        val = 1500 + int(400 * math.sin(2.0 * math.pi * 0.2 * self.t))  # 0.2 Hz sine
        self.t += self.dt
        arr = [1500] * self.channel_count
        # Clamp to valid PWM range
        val = max(1000, min(2000, val))
        arr[self.channel_index] = val
        msg = UInt16MultiArray()
        msg.data = arr
        self.pub.publish(msg)


def main():
    rclpy.init()
    node = RcOverrideSine()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
