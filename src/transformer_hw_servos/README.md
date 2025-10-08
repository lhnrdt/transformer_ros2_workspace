# transformer_hw_servos

Single (or backend-capable multi) servo action-based controller with pluggable backends (default: PCA9685 hardware PWM):

1. `pca9685` – external 16‑channel PCA9685 I2C PWM expander (hardware timing)
2. `lgpio` – software PWM using lgpio's `lgTxServo` (Raspberry Pi GPIO)

The node logic now treats motions generically; action goals specify a 1-based channel index. Internally we currently track only the last commanded pulse but forward the requested channel to the backend (which may drive multiple outputs).

Default pulse range: 1350–2500 µs (clamped). Global safety envelope: 500–3000 µs. Default initial pulse: 1500 µs.

## Build

```bash
cd ~/ros2_ws
colcon build --packages-select transformer_hw_servos
source install/setup.bash
```

## Run (backend selection)

```bash
### Default (PCA9685 hardware PWM)
```bash
ros2 launch transformer_hw_servos servos.launch.py
```

### Force software PWM (lgpio)
```bash
ros2 launch transformer_hw_servos servos.launch.py backend_type:=lgpio
```

### Explicit PCA9685 parameters (if you changed address or bus)
```bash
ros2 launch transformer_hw_servos servos.launch.py backend_type:=pca9685 i2c_bus:=/dev/i2c-1 pca9685_address:=0x40
```

# PCA9685 using channels 4 and 5 instead of 0 and 1
ros2 launch transformer_hw_servos servos.launch.py backend_type:=pca9685 \
	pca9685_servo0_channel:=4 pca9685_servo1_channel:=5
```

If your GPIO chip differs, override parameters:

```bash
ros2 launch transformer_hw_servos servos.launch.py gpiochip_name:=gpiochip4 gpio_servo0:=6 gpio_servo1:=27
```

## Move Servo (Action Interface)

Action: `/move_servo` (`transformer_hw_servos/action/MoveServo`).

Updated Goal fields:
- `channel` (int32): logical channel (1-based)
- `pulse_us` (int32): target pulse width
- `speed_us_per_s` (int32): max slew magnitude; <=0 applies instantly
- `use_trapezoid` (bool): request trapezoidal (or triangular) motion profile for this goal (overrides node default)
- `accel_us_per_s2` (int32): acceleration for trapezoid; <=0 => node heuristic

Result fields:
- `success` / `message`
- `final_pulse_us`
- `total_estimated_duration_s` (float): precomputed plan duration (0 for instant)

Feedback fields:
- `current_pulse_us`
- `progress` (0..1)
- `estimated_remaining_s` (float)
- `phase` ("linear", "accel", "cruise", "decel", "done")

Examples:

Instant move:
```bash
ros2 action send_goal /move_servo transformer_hw_servos/action/MoveServo '{channel: 1, pulse_us: 1700, speed_us_per_s: 0, use_trapezoid: false, accel_us_per_s2: 0}'
```

Linear ramp (6000 µs/s):
```bash
ros2 action send_goal /move_servo transformer_hw_servos/action/MoveServo '{channel: 1, pulse_us: 1400, speed_us_per_s: 6000, use_trapezoid: false, accel_us_per_s2: 0}' --feedback
```

Trapezoidal motion (explicit accel):
```bash
ros2 action send_goal /move_servo transformer_hw_servos/action/MoveServo '{channel: 1, pulse_us: 1900, speed_us_per_s: 8000, use_trapezoid: true, accel_us_per_s2: 20000}' --feedback
```

## Hardware migration to PCA9685 (Raspberry Pi 5)

1. Enable I2C (if not already):
	- Run `sudo raspi-config`, Interface Options -> I2C -> Enable.
	- Or add `dtparam=i2c_arm=on` to `/boot/firmware/config.txt` (Pi 5) and reboot.
2. Wire PCA9685:
	- VCC -> Pi 3.3V
	- GND -> Pi GND
	- SDA -> Pi SDA (GPIO2)
	- SCL -> Pi SCL (GPIO3)
	- (Optional) External servo power: provide 5–6V to `V+` on PCA9685 board and common ground with Pi.
3. Verify device appears:
	- `sudo apt install -y i2c-tools`
	- `i2cdetect -y 1` should show `40` (or your jumper‑selected address).
4. Launch node with `backend_type:=pca9685` and parameters.
5. Use the same ROS2 services to command pulse widths; conversion to hardware ticks is automatic.

### Selecting a different PCA9685 address
Set jumpers A0..A5 on the board; compute address = 0x40 + value. Then pass `pca9685_address:=0x41` (for example).

### Performance Notes
Hardware PWM (PCA9685) offloads timing, eliminating CPU jitter and allowing stable multi‑channel expansion (up to 16 channels). Software PWM (`lgpio`) is lightweight but sensitive to system load.

## Notes

- Software PWM backend: CPU timing jitter may affect precision under heavy load.
- PCA9685 backend: ensure adequate servo power; large current surges require a dedicated 5V supply.
- Access requirements: `/dev/gpiochip*` for lgpio; `/dev/i2c-*` for PCA9685 (add user to `i2c` group or run with appropriate permissions).

## Parameters (current core)

- `backend_type` (string: `pca9685` | `lgpio`, default `pca9685`)
- `period_us` (int, default 20000 -> 50 Hz) clamped to 40..400 Hz
- `initial_us` (int, default 1500)
- `min_us` / `max_us` (global limits, default 1350 / 2500, safety envelope enforced 500..3000)
- `enable_trapezoid` (bool, default false) default profile if goal doesn't request
- `accel_us_per_s2` (int, default 0) default accel heuristic fallback

Backend specific parameters are declared inside each backend (e.g. `i2c_bus`, `pca9685_address`, GPIO pin numbers) and no longer appear here.

## Migration Steps Summary

1. Wire PCA9685 & enable I2C.
2. Build package (no additional dependency besides standard i2c-dev headers).
3. Launch with `backend_type:=pca9685`.
4. Test with service calls; observe stable hardware PWM.
5. (Optional) revert anytime by launching with `backend_type:=lgpio`.

## Selecting PCA9685 Channels

You can map logical servo indices to any PCA9685 output channel:

```bash
ros2 launch transformer_hw_servos servos.launch.py \
  backend_type:=pca9685 pca9685_servo0_channel:=4 pca9685_servo1_channel:=5
```

Ensure your servos are physically connected to those channel headers on the PCA9685 board.

## I2C Diagnostics

1. Detect device(s): `i2cdetect -y 1` (look for `40` or your chosen address)
2. Read MODE1 register (0x00) for basic sanity:
	```bash
	# Install i2c-tools if needed
	sudo apt install -y i2c-tools
	# Read one byte at register 0x00 from address 0x40 on bus 1
	sudo i2cget -y 1 0x40 0x00
	```
	Expected: a value typically `0x00` or with bits set if auto-increment/sleep toggled.
3. If communication fails:
	- Check SDA/SCL wiring and pull-ups (most breakout boards include them)
	- Confirm I2C enabled in firmware config
	- Make sure no other device shares the same address (change via A0..A5 jumpers if needed)