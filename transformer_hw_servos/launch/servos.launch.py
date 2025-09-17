from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    """Launch dual servo node with parameters from YAML."""
    pkg_share = get_package_share_directory('transformer_hw_servos')
    params_file = os.path.join(pkg_share, 'config', 'servos.yaml')
    return LaunchDescription([
        Node(
            package='transformer_hw_servos',
            executable='servos_node',
            name='servos',
            output='screen',
            parameters=[params_file],
        )
    ])
