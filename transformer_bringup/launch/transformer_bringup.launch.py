from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    servos_pkg = get_package_share_directory('transformer_hw_servos')
    actuators_pkg = get_package_share_directory('transformer_hw_actuators')
    controller_pkg = get_package_share_directory('transformer_controller')

    servos_launch = os.path.join(servos_pkg, 'launch', 'servos.launch.py')
    actuators_launch = os.path.join(actuators_pkg, 'launch', 'actuator.launch.py')
    controller_launch = os.path.join(controller_pkg, 'launch', 'transformer_controller.launch.py')

    return LaunchDescription([
        IncludeLaunchDescription(PythonLaunchDescriptionSource(servos_launch)),
        IncludeLaunchDescription(PythonLaunchDescriptionSource(actuators_launch)),
        IncludeLaunchDescription(PythonLaunchDescriptionSource(controller_launch)),
    ])
