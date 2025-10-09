#!/bin/bash
source /opt/ros/jazzy/setup.bash
source /home/atvpi/transformer_ros2_workspace/install/setup.bash

exec ros2 launch transformer_bringup transformer_bringup.launch.py
