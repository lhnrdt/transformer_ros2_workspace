"""Transformer bringup launch.

Starts core nodes and optionally:
- Intel RealSense D4xx pipeline (depth only) with IMU disabled.
- Wheeltec N100 IMU with configurable serial settings.
"""
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    """Generate the full bringup LaunchDescription with optional sensors."""
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

    # Optional start toggles for sensors
    start_realsense_arg = DeclareLaunchArgument(
        'start_realsense', default_value='false', description='Start Intel RealSense D4xx camera node')
    start_realsense = LaunchConfiguration('start_realsense')

    # RealSense color stream control (exposed so users can enable color via CLI)
    rs_enable_color_arg = DeclareLaunchArgument(
        'rs_enable_color', default_value='false', description='Enable RealSense color stream')
    rs_color_width_arg = DeclareLaunchArgument(
        'rs_color_width', default_value='640', description='Color stream width')
    rs_color_height_arg = DeclareLaunchArgument(
        'rs_color_height', default_value='480', description='Color stream height')
    rs_color_fps_arg = DeclareLaunchArgument(
        'rs_color_fps', default_value='30', description='Color stream FPS')
    rs_enable_color = LaunchConfiguration('rs_enable_color')
    rs_color_width = LaunchConfiguration('rs_color_width')
    rs_color_height = LaunchConfiguration('rs_color_height')
    rs_color_fps = LaunchConfiguration('rs_color_fps')

    start_wheeltec_imu_arg = DeclareLaunchArgument(
        'start_wheeltec_imu', default_value='false', description='Start Wheeltec N100 IMU node')
    start_wheeltec_imu = LaunchConfiguration('start_wheeltec_imu')

    # Wheeltec IMU serial settings (configurable via launch args)
    wheeltec_serial_port_arg = DeclareLaunchArgument(
        'wheeltec_serial_port', default_value='/dev/ttyUSB0',
        description='Serial port for Wheeltec N100 IMU')
    wheeltec_serial_baud_arg = DeclareLaunchArgument(
        'wheeltec_serial_baud', default_value='921600',
        description='Baud rate for Wheeltec N100 IMU')
    wheeltec_serial_port = LaunchConfiguration('wheeltec_serial_port')
    wheeltec_serial_baud = LaunchConfiguration('wheeltec_serial_baud')

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

    # Include RealSense pipeline launch with requested parameters
    realsense_include = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(
            get_package_share_directory('realsense2_camera'), 'launch', 'rs_launch.py'
        )),
        condition=IfCondition(start_realsense),
        launch_arguments={
            'unite_imu_method': 'none',
            'enable_color': rs_enable_color,
            # Color resolution/fps are only used when color is enabled
            'color_width': rs_color_width,
            'color_height': rs_color_height,
            'color_fps': rs_color_fps,
            'enable_gyro': 'false',
            'enable_accel': 'false',
            'depth_width': '640',
            'depth_height': '480',
            'depth_fps': '30',
        }.items()
    )

    # Add Wheeltec N100 IMU node with requested serial parameters
    wheeltec_imu_node = Node(
        package='wheeltec_n100_imu',
        executable='imu_node',
        name='wheeltec_n100_imu',
        output='screen',
        parameters=[{
            'serial_port': wheeltec_serial_port,
            'serial_baud': wheeltec_serial_baud,
        }],
        condition=IfCondition(start_wheeltec_imu)
    )

    rc_switch_pkg = get_package_share_directory('transformer_rc_mode_switch')
    rc_switch_launch = os.path.join(rc_switch_pkg, 'launch', 'rc_mode_switch.launch.py')
    rc_switch_include = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(rc_switch_launch),
        condition=IfCondition(start_rc_switch))

    return LaunchDescription([
        start_msp_arg,
        start_rc_switch_arg,
        start_realsense_arg,
        rs_enable_color_arg,
        rs_color_width_arg,
        rs_color_height_arg,
        rs_color_fps_arg,
        start_wheeltec_imu_arg,
        wheeltec_serial_port_arg,
        wheeltec_serial_baud_arg,
        custom_registry_arg,
        IncludeLaunchDescription(PythonLaunchDescriptionSource(servos_launch)),
        IncludeLaunchDescription(PythonLaunchDescriptionSource(actuators_launch)),
        IncludeLaunchDescription(PythonLaunchDescriptionSource(controller_launch)),
        msp_node,
        rc_switch_include,
        realsense_include,
        wheeltec_imu_node
    ])
