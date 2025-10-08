from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
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

    start_msp_arg = DeclareLaunchArgument(
        'start_msp', default_value='true', description='Start the MSP bridge node')
    start_msp = LaunchConfiguration('start_msp')

    start_rc_switch_arg = DeclareLaunchArgument(
        'start_rc_switch', default_value='true', description='Start the RC mode switch node')
    start_rc_switch = LaunchConfiguration('start_rc_switch')

    msp_pkg_share = get_package_share_directory('transformer_msp_bridge')
    # Only include the ROS 2 parameters file. The registry.yaml is NOT a ROS param file and passing it
    # caused node abort. We expose an optional launch arg for a future external registry path if/when
    # the node is extended to load it at runtime.
    msp_params = [os.path.join(msp_pkg_share, 'config', 'msp_bridge.yaml')]

    custom_registry_arg = DeclareLaunchArgument(
        'msp_registry_path', default_value='',
        description='(Optional) Path to MSP registry YAML (not loaded by node yet; reserved for future)')

    msp_node = Node(
        package='transformer_msp_bridge',
        executable='transformer_msp_bridge_node',
        name='transformer_msp_bridge',
        output='screen',
        parameters=msp_params,
        condition=IfCondition(start_msp)
    )

    rc_switch_pkg = get_package_share_directory('transformer_rc_mode_switch')
    rc_switch_launch = os.path.join(rc_switch_pkg, 'launch', 'rc_mode_switch.launch.py')
    rc_switch_include = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(rc_switch_launch),
        condition=IfCondition(start_rc_switch))

    return LaunchDescription([
        start_msp_arg,
        start_rc_switch_arg,
        custom_registry_arg,
        IncludeLaunchDescription(PythonLaunchDescriptionSource(servos_launch)),
        IncludeLaunchDescription(PythonLaunchDescriptionSource(actuators_launch)),
        IncludeLaunchDescription(PythonLaunchDescriptionSource(controller_launch)),
        msp_node,
        rc_switch_include
    ])
