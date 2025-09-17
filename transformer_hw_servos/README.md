# transformer_hw_servos

Dual-servo software PWM controller at 50 Hz using libgpiod, exposing a simple service to set pulse widths per servo.

- Servo0 on `GPIO6`
- Servo1 on `GPIO27`
- Default pulse range: 500–2500 µs (clamped)
- Default initial position: 1500 µs (center)

## Build

```bash
cd ~/ros2_ws
colcon build --packages-select transformer_hw_servos
source install/setup.bash
```

## Run

```bash
ros2 launch transformer_hw_servos servos.launch.py
```

If your GPIO chip differs, override parameters:

```bash
ros2 launch transformer_hw_servos servos.launch.py gpiochip_name:=gpiochip4 gpio_servo0:=6 gpio_servo1:=27
```

## Set positions

Pulse widths are set per servo via the `SetServoPulse` service. Values are clamped to `[min_us, max_us]`.

- Set servo0 to 2000 µs:

```bash
ros2 service call /set_servo_pulse transformer_hw_servos/srv/SetServoPulse '{servo_index: 0, pulse_us: 2000}'
```

- Set servo1 to 1000 µs:

```bash
ros2 service call /set_servo_pulse transformer_hw_servos/srv/SetServoPulse '{servo_index: 1, pulse_us: 1000}'
```

## Notes

- This is software PWM; CPU timing jitter may affect precision. For best stability, avoid heavy CPU load.
- Requires access to `/dev/gpiochip*` (typically run as root or with appropriate udev rules).