"""Transformer bringup launch.

Starts core nodes and optionally:
- Intel RealSense D4xx pipeline (depth + color enabled here) with IMU disabled.
- Wheeltec N100 IMU with configurable serial settings.
"""
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration, TextSubstitution, PathJoinSubstitution, Command
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
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

    # Camera naming used by realsense2_camera; expose as launch args so other nodes (relays) can derive topics from the same source of truth
    camera_namespace_arg = DeclareLaunchArgument(
        'camera_namespace', default_value='transformer', description='Namespace for the RealSense camera')
    camera_name_arg = DeclareLaunchArgument(
        'camera_name', default_value='D435I', description='Logical camera name')
    camera_namespace = LaunchConfiguration('camera_namespace')
    camera_name = LaunchConfiguration('camera_name')

    start_wheeltec_imu_arg = DeclareLaunchArgument(
        'start_wheeltec_imu', default_value='false', description='Start Wheeltec N100 IMU node')
    start_wheeltec_imu = LaunchConfiguration('start_wheeltec_imu')

    # Start robot description (URDF) publisher
    start_description_arg = DeclareLaunchArgument(
        'start_description', default_value='true', description='Start robot_state_publisher with transformer_description URDF')
    start_description = LaunchConfiguration('start_description')

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
    # Only include the ROS 2 parameters file. The registry JSON is NOT a ROS param file and passing it
    # caused node abort. We expose an optional launch arg for a future external registry path if/when
    # the node is extended to load it at runtime.
    msp_params = [os.path.join(msp_pkg_share, 'config', 'msp_bridge.yaml')]

    custom_registry_arg = DeclareLaunchArgument(
        'msp_registry_path', default_value='',
        description='(Optional) Path to MSP registry JSON (runtime loader already checks TRANSFORMER_MSP_REGISTRY_JSON)')

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
            # Flatten topics so RViz defaults find them: /camera/<stream>/...
            'camera_namespace': camera_namespace,
            'camera_name': camera_name,
            'enable_color': 'true',
            'enable_depth': 'true',

            # Profiles per docs
            'rgb_camera.profile': '1280x720x30',
            'depth_module.profile': '848x480x30',

            # Filters and sync
            'align_depth.enable': 'true',
            'enable_sync': 'true',
            'pointcloud.enable': 'true',
            'pointcloud.pointcloud_qos': 'SENSOR_DATA',
            
            # IMU disabled
            # 'enable_gyro': 'false',
            # 'enable_accel': 'false',
            
            # Disable IR streams to reduce load
            # 'enable_infra1': 'false',
            # 'enable_infra2': 'false',
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

    # Robot description (URDF via xacro) from transformer_description
    desc_share = get_package_share_directory('transformer_description')
    xacro_file = os.path.join(desc_share, 'urdf', 'transformer.urdf.xacro')
    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[{
            'use_sim_time': False,
            'robot_description': ParameterValue(Command(['xacro ', xacro_file]), value_type=str),
        }],
        condition=IfCondition(start_description)
    )

    # Build topic roots from camera_namespace and camera_name
    camera_root = PathJoinSubstitution([
        TextSubstitution(text='/'),
        camera_namespace,
        camera_name,
    ])

    # Relay CameraInfo to nested image_raw path so tools expecting
    # <image_topic>/camera_info can find it next to image_raw
    relay_aligned_info = Node(
        package='topic_tools',
        executable='relay',
        name='relay_aligned_depth_to_color_info',
        output='screen',
        arguments=[
            PathJoinSubstitution([camera_root, TextSubstitution(text='aligned_depth_to_color/camera_info')]),
            PathJoinSubstitution([camera_root, TextSubstitution(text='aligned_depth_to_color/image_raw/camera_info')]),
        ],
        parameters=[{'type': 'sensor_msgs/msg/CameraInfo'}],
        condition=IfCondition(start_realsense),
    )

    relay_color_info = Node(
        package='topic_tools',
        executable='relay',
        name='relay_color_info',
        output='screen',
        arguments=[
            PathJoinSubstitution([camera_root, TextSubstitution(text='color/camera_info')]),
            PathJoinSubstitution([camera_root, TextSubstitution(text='color/image_raw/camera_info')]),
        ],
        parameters=[{'type': 'sensor_msgs/msg/CameraInfo'}],
        condition=IfCondition(start_realsense),
    )

    return LaunchDescription([
        start_msp_arg,
        start_rc_switch_arg,
        start_realsense_arg,
        start_description_arg,
        camera_namespace_arg,
        camera_name_arg,
        start_wheeltec_imu_arg,
        wheeltec_serial_port_arg,
        wheeltec_serial_baud_arg,
        custom_registry_arg,
        IncludeLaunchDescription(PythonLaunchDescriptionSource(servos_launch)),
        IncludeLaunchDescription(PythonLaunchDescriptionSource(actuators_launch)),
        IncludeLaunchDescription(PythonLaunchDescriptionSource(controller_launch)),
        msp_node,
        rc_switch_include,
        robot_state_publisher,
        realsense_include,
        relay_aligned_info,
        relay_color_info,
        wheeltec_imu_node
    ])
