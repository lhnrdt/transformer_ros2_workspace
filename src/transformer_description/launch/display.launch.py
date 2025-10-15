"""Display the Transformer robot description with configurable sensor poses."""
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, Command
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    pkg_share = get_package_share_directory('transformer_description')
    xacro_file = os.path.join(pkg_share, 'urdf', 'transformer.urdf.xacro')

    # Pose args (as strings "x y z" and "r p y")
    msp_imu_xyz_arg = DeclareLaunchArgument('msp_imu_xyz', default_value='0 0 0')
    msp_imu_rpy_arg = DeclareLaunchArgument('msp_imu_rpy', default_value='0 0 0')

    n100_imu_xyz_arg = DeclareLaunchArgument('n100_imu_xyz', default_value='0 0 0')
    n100_imu_rpy_arg = DeclareLaunchArgument('n100_imu_rpy', default_value='0 0 0')

    gps_xyz_arg = DeclareLaunchArgument('gps_xyz', default_value='0 0 0')
    gps_rpy_arg = DeclareLaunchArgument('gps_rpy', default_value='0 0 0')

    d435i_xyz_arg = DeclareLaunchArgument('d435i_xyz', default_value='0 0 0')
    d435i_rpy_arg = DeclareLaunchArgument('d435i_rpy', default_value='0 0 0')

    robot_description_content = Command([
        'xacro ', xacro_file,
        ' msp_imu_xyz:=', LaunchConfiguration('msp_imu_xyz'),
        ' msp_imu_rpy:=', LaunchConfiguration('msp_imu_rpy'),
        ' n100_imu_xyz:=', LaunchConfiguration('n100_imu_xyz'),
        ' n100_imu_rpy:=', LaunchConfiguration('n100_imu_rpy'),
        ' gps_xyz:=', LaunchConfiguration('gps_xyz'),
        ' gps_rpy:=', LaunchConfiguration('gps_rpy'),
        ' d435i_xyz:=', LaunchConfiguration('d435i_xyz'),
        ' d435i_rpy:=', LaunchConfiguration('d435i_rpy'),
    ])

    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[{
            'use_sim_time': False,
            'robot_description': ParameterValue(robot_description_content, value_type=str)
        }]
    )

    # Optional: Launch joint_state_publisher_gui for interactive adjustments
    jsp = Node(
        package='joint_state_publisher_gui',
        executable='joint_state_publisher_gui',
        name='joint_state_publisher_gui',
        output='screen'
    )

    return LaunchDescription([
        msp_imu_xyz_arg, msp_imu_rpy_arg,
        n100_imu_xyz_arg, n100_imu_rpy_arg,
        gps_xyz_arg, gps_rpy_arg,
        d435i_xyz_arg, d435i_rpy_arg,
        robot_state_publisher,
        jsp
    ])
