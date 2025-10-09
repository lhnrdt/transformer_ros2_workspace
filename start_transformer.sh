#!/bin/bash
source /opt/ros/jazzy/setup.bash
source /home/atvpi/transformer_ros2_workspace/install/setup.bash

exec ros2 launch transformer_bringup transformer_bringup.launch.py \
	start_realsense:=true \
	start_wheeltec_imu:=true \
	rs_enable_color:=true \
	rs_color_width:=640 \
	rs_color_height:=480 \
	rs_color_fps:=30 \
	wheeltec_serial_port:=/dev/ttyUSB0 \
	wheeltec_serial_baud:=921600
