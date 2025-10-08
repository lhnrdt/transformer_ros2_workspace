from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    """Launch actuator node with parameters from YAML."""
    pkg_share = get_package_share_directory('transformer_hw_actuators')
    params_file = os.path.join(pkg_share, 'config', 'actuator.yaml')
    return LaunchDescription([
        Node(
            package='transformer_hw_actuators',
            executable='actuator_node',
            name='actuator_node',
            parameters=[params_file]
        )
    ])
