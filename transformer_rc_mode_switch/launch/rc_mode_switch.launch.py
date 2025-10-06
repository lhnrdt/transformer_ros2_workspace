from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='transformer_rc_mode_switch',
            executable='rc_mode_switch_node',
            name='rc_mode_switch',
            output='screen',
            parameters=[{
                'channel_index': 5,  # CH6 (0-based)
                'drive_high_center': 2000,
                'flight_low_center': 1000,
                'tolerance': 300,
                'debounce_ms': 800,
                'min_channels': 6,
                'rc_topic': '/msp/rc_in'
            }]
        )
    ])
