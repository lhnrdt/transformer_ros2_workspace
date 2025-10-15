# transformer_description

URDF/Xacro package for the Transformer robot. Defines positions for sensors:
- MSP IMU
- Wheeltec N100 IMU
- GPS module
- Intel RealSense D435i

## Files
- `urdf/transformer.urdf.xacro` — Base link and fixed joints to sensors with placeholder poses.
- `launch/display.launch.py` — Visualize the robot in RViz via robot_state_publisher. Accepts pose args.

## Usage
Launch with default poses:

```bash
ros2 launch transformer_description display.launch.py
```

Override poses (values are space-separated "x y z" and "roll pitch yaw" in radians):

```bash
ros2 launch transformer_description display.launch.py \
  msp_imu_xyz:="0.10 0.00 0.05" msp_imu_rpy:="0 0 0" \
  n100_imu_xyz:="-0.05 0.00 0.05" n100_imu_rpy:="0 0 0" \
  gps_xyz:="0.00 0.00 0.15" gps_rpy:="0 0 0" \
  d435i_xyz:="0.12 0.00 0.10" d435i_rpy:="0 0 0"
```

To integrate with other packages, load `robot_description` from this xacro and set poses accordingly.
