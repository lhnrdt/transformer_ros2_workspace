from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='transformer_hw_servos',
            executable='servos_node',
            name='servos',
            output='screen',
            parameters=[
                {
                    'gpiochip_name': 'gpiochip4',
                    'gpio_servo0': 6,
                    'gpio_servo1': 27,
                    'period_us': 20000,
                    'initial_us': 1500,
                    'min_us': 500,
                    'max_us': 2500,
                }
            ],
        )
    ])
