#!/bin/bash
source /opt/ros/jazzy/setup.bash
source /home/atvpi/ros2_ws/install/setup.bash

exec ros2 launch transformer_bringup transformer_bringup.launch.py
