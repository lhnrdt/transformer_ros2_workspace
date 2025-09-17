from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='transformer_hw_actuators',
            executable='actuator_node',
            name='actuator_node',
            parameters=[{
                'pwmchip_index': 0,        # /sys/class/pwm/pwmchip0
                'pwm_channels': [1, 0],    # actuator0→PWM1(GPIO13), actuator1→PWM0(GPIO12)
                'dir_gpios': [19, 5],      # actuator0 DIR→GPIO19, actuator1 DIR→GPIO5
                'dir_active_high': [True, True],
                'period_ns': 50000,        # 20 kHz
                'initial_percent': 0,
                'brake_on_zero': False,
            }]
        )
    ])