# transformer_msp_bridge

ROS 2 C++ bridge node for MSP (Multiwii / iNav) flight controller communication.

## Features
- Sends RC override values via `MSP_SET_RAW_RC`.
- Requests and publishes ATTITUDE (`/msp/attitude`, `geometry_msgs/Vector3`).
- Publishes echo of last RC values on `/msp/rc_out` (`std_msgs/UInt16MultiArray`).
- Subscribes to `/msp/rc_override` (`std_msgs/UInt16MultiArray`) to immediately send RC commands.
- Parameters for serial port, baud, channel count, poll rates.

## Parameters
- `port` (string, default `/dev/ttyAMA0`)
- `baudrate` (int, default 115200)
- `timeout_ms` (int, default 50)
- `rc_channel_count` (int, default 8)
- `telemetry_poll_rate_hz` (double, default 10.0)
- `rc_publish_rate_hz` (double, default 10.0)

## Build
```bash
cd ~/ros2_ws
colcon build --packages-select transformer_msp_bridge
source install/setup.bash
```

## Run
```bash
ros2 run transformer_msp_bridge transformer_msp_bridge_node
```

Publish RC override example:
```bash
ros2 topic pub /msp/rc_override std_msgs/UInt16MultiArray '{data: [1500,1500,1500,1500,1500,1500,1500,1500]}' -1
```

View attitude:
```bash
ros2 topic echo /msp/attitude
```

## Notes
- Only ATTITUDE telemetry implemented initially; extend by adding more MSP IDs in `msp_protocol.hpp` and requesting them in `pollTelemetry()`.
- Serial is opened non-blocking; read timer polls every 5 ms.
