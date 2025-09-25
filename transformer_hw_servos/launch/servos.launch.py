from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    """Launch dual servo node with parameters from YAML."""
    pkg_share = get_package_share_directory('transformer_hw_servos')
    params_file = os.path.join(pkg_share, 'config', 'servos.yaml')
    backend_type = LaunchConfiguration('backend_type')
    i2c_bus = LaunchConfiguration('i2c_bus')
    pca_addr = LaunchConfiguration('pca9685_address')
    ch0 = LaunchConfiguration('pca9685_servo0_channel')
    ch1 = LaunchConfiguration('pca9685_servo1_channel')

    return LaunchDescription([
        DeclareLaunchArgument('backend_type', default_value='pca9685', description='Servo backend (default pca9685, can set lgpio)'),
        DeclareLaunchArgument('i2c_bus', default_value='/dev/i2c-1', description='I2C bus for PCA9685'),
        DeclareLaunchArgument('pca9685_address', default_value='0x40', description='I2C address of PCA9685'),
        DeclareLaunchArgument('pca9685_servo0_channel', default_value='0', description='PCA9685 channel for logical servo 0'),
        DeclareLaunchArgument('pca9685_servo1_channel', default_value='1', description='PCA9685 channel for logical servo 1'),
        Node(
            package='transformer_hw_servos',
            executable='servos_node',
            name='transformer_hw_servos',
            output='screen',
            parameters=[
                params_file,
                {
                    'backend_type': backend_type,
                    'i2c_bus': i2c_bus,
                    'pca9685_address': pca_addr,
                    'pca9685_servo0_channel': ch0,
                    'pca9685_servo1_channel': ch1,
                }
            ],
        )
    ])
