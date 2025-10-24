from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='transformer_controller',
            executable='transformer_controller_node',
            name='transformer_controller',
            output='screen',
            parameters=[{
                'retract_speed_percent': -100,
                'retract_time_ms': 5000,
                'extend_speed_percent': 100,
                'extend_time_ms': 6000,
                'flight_servos_pulse': 2200,
                'drive_servos_pulse': 450,
                'servo_move_speed_us_per_s': 1300,
                'startup_retract': True,
            }]
        )
    ])
