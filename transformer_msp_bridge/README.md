## transformer_msp_bridge

ROS 2 C++ bridge node for MSP (MultiWii / iNav) flight controller communication with dynamic, per-command polling control and MSP v1 + v2 (native & tunneled) support.

### Key Features
* Serial link to flight controller (MSP v1 and v2, including v2-over-v1 tunneling).
* Modular decoders for IMU, GPS, altitude, servo/motor, rangefinder, compass, barometer, and INAV status.
* Per-command ROS parameters: `command.<name>.enabled` + `command.<name>.rate_hz` (runtime adjustable via `ros2 param set`).
* Automatic negotiation with protocol version / fallback disabling v2-only commands if unsupported.
* RC override publishing and echo (`/msp/rc_override`, `/msp/rc_out`, `/msp/rc_in`).
* Topics for attitude, raw IMU, magnetometer, GPS, altitude, rangefinder, compass, barometer, INAV status (and placeholders for extended telemetry under development).

### Installed Parameter File
A default YAML config is installed at:
```
$(ros2 pkg prefix transformer_msp_bridge)/share/transformer_msp_bridge/config/msp_bridge.yaml
```
Edit a copy of this file to tailor enabled commands and polling rates.

### Running with Config File
```bash
ros2 run transformer_msp_bridge transformer_msp_bridge_node --ros-args \
	--params-file $(ros2 pkg prefix transformer_msp_bridge)/share/transformer_msp_bridge/config/msp_bridge.yaml
```

### Adjusting At Runtime
Disable a command:
```bash
ros2 param set /transformer_msp_bridge command.msp_raw_gps.enabled false
```
Change the rate (Hz):
```bash
ros2 param set /transformer_msp_bridge command.msp_attitude.rate_hz 25.0
```

If you re-enable a command whose `rate_hz` is 0, also set a positive rate first:
```bash
ros2 param set /transformer_msp_bridge command.msp_rc_tuning.rate_hz 0.5
ros2 param set /transformer_msp_bridge command.msp_rc_tuning.enabled true
```

### Core Parameters
| Name | Type | Default | Description |
|------|------|---------|-------------|
| `port` | string | `/dev/ttyAMA0` | Serial device path |
| `baudrate` | int | 115200 | Serial baud rate |
| `timeout_ms` | int | 50 | Serial read timeout |
| `rc_channel_count` | int | 8 | Number of RC channels handled |
| `rc_publish_rate_hz` | double | 10.0 | Rate to echo RC output |
| `debug_msp` | bool | false | Verbose internal statistics logging |
| `log_msp_tx` | bool | false | Log raw hex TX frames |
| `log_msp_rx` | bool | false | Log raw hex RX frames |
| `v2_fallback_timeout_sec` | double | 5.0 | Time before disabling v2-only polling if no v2 frames seen |
| `force_msp_v2` | bool | false | Keep v2 polling even without confirmation |
| `use_v2_tunnel` | bool | false | Use v2-over-v1 tunnel for v2 commands |
| `use_v2_for_legacy` | bool | false | Attempt native v2 for legacy (<256) IDs when supported |
| `command.*.enabled` | bool | registry dependent | Per-command on/off |
| `command.*.rate_hz` | double | registry dependent | Per-command polling rate |

### Build
```bash
cd ~/ros2_ws
colcon build --packages-select transformer_msp_bridge
source install/setup.bash
```

### Tests
Unit tests (Google Test) are provided for initial decoder coverage (battery & system decoders).

Build & run tests:
```bash
colcon build --packages-select transformer_msp_bridge --cmake-args -DBUILD_TESTING=ON
colcon test --packages-select transformer_msp_bridge
colcon test-result --verbose
```

Run a single test binary manually (after build):
```bash
./install/transformer_msp_bridge/lib/transformer_msp_bridge/test_battery_decoder
```

Add new decoder tests under `test/` and register them in the package `CMakeLists.txt` using `ament_add_gtest()` linking against `${PROJECT_NAME}_decoders`.

### Basic Run (defaults)
```bash
ros2 run transformer_msp_bridge transformer_msp_bridge_node
```

### Publish RC Override Example
```bash
ros2 topic pub /msp/rc_override std_msgs/UInt16MultiArray '{data: [1500,1500,1500,1500,1500,1500,1500,1500]}' -1
```

### View Attitude
```bash
ros2 topic echo /msp/attitude
```

### Extending
Additional MSP commands can be introduced by editing `msp_registry.cpp` (add descriptor with build callback) and binding a decode callback in `transformer_msp_bridge_node.cpp` or via a new decoder class. Poll rate and enable state become automatically exposed as parameters on startup.

#### Regenerating Registry Documentation
The file `REGISTRY.md` can be auto-generated from the compiled registry:
```bash
colcon build --packages-select transformer_msp_bridge --cmake-target generate_registry_md
```
This builds the helper tool `registry_dump` and rewrites `REGISTRY.md`. Commit the updated file if the registry changed.

### Roadmap / TODO
* Bandwidth throttling (byte/token bucket)
* Priority scheduler (min-heap by next due time)
* Expand unit test coverage to remaining decoders (IMU, GPS, altitude, attitude, RC, battery edge cases, RTC) and parser logic
* Documentation of message semantics and frames

### License
BSD-3-Clause
