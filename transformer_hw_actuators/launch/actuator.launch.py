from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='transformer_hw_actuators',
            executable='actuator_node',
            name='actuator_node',
            parameters=[{
                'pwmchip_index': 0,
                'pwm_channels': [1, 0],    # actuator0→PWM1(GPIO13), actuator1→PWM0(GPIO12)
                'dir_gpios': [19, 5],      # actuator0 DIR→GPIO19,   actuator1 DIR→GPIO5
                'dir_active_high': [True, True],
                'gpiochip_name': 'gpiochip4',   # <-- NEW: RP1 bank on Pi 5
                'period_ns': 50000,
                'initial_percent': 0,
                'brake_on_zero': False,
            }]
        )
    ])
