# Transformer ROS 2 Workspace

This repository bundles the bringup, hardware interfaces, and controller logic for the Transformer hybrid ground/flight robot. The instructions below focus on making sure every required dependency is in place before you build or launch the stack.

> **Tested with:** Ubuntu 24.04 (Noble) + ROS 2 Jazzy Jalisco

## 1. Install ROS 2 Jazzy and system prerequisites

```bash
sudo apt update
sudo apt install curl gnupg lsb-release software-properties-common
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list
sudo apt update
sudo apt install ros-jazzy-desktop
```

Add the ROS environment to your shell profile so new terminals source it automatically:

```bash
echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

## 2. Install build and tooling dependencies

```bash
sudo apt install \
  python3-colcon-common-extensions \
  python3-vcstool \
  python3-rosdep \
  build-essential \
  cmake \
  git
```

Initialize `rosdep` once (per machine) so it can resolve package dependencies:

```bash
sudo rosdep init  # skip if this machine has been initialized before
rosdep update
```

## 3. Clone the workspace

```bash
cd ~
git clone https://github.com/lhnrdt/transformer_ros2_workspace.git
cd transformer_ros2_workspace
# If you already have a clone, pull the latest changes instead.
```

## 4. Resolve package dependencies

From the workspace root:

```bash
cd ~/transformer_ros2_workspace
rosdep install --from-paths src --ignore-src -r -y
```

`rosdep` will pull every ROS package listed in each `package.xml`. Pay special attention to the following system libraries and optional sensor stacks:

- `libgpiod-dev`: required for the servo backend (`transformer_hw_servos`). If rosdep cannot find it automatically, install manually: `sudo apt install libgpiod-dev`.
- `realsense2_camera`: optional but enabled by default in `start_transformer.sh`. Install via `sudo apt install ros-jazzy-realsense2-camera librealsense2-udev-rules`.
- `wheeltec_n100_imu`: built from source in this workspace. Ensure your user is in the `dialout` group (`sudo usermod -a -G dialout $USER`), then re-login so the IMU serial device is accessible.

After installing new udev rules (e.g., from RealSense) unplug/replug the device or reboot to apply them.

## 5. Build the workspace

```bash
cd ~/transformer_ros2_workspace
source /opt/ros/jazzy/setup.bash
colcon build --symlink-install
```

Re-source the workspace overlay whenever you open a new shell:

```bash
source install/setup.bash
```

## 6. Launch the bringup

Once the build completes and dependencies are satisfied, the main bringup launch file can be started via the provided helper script:

```bash
./start_transformer.sh
```

The script sources the installed overlay and launches `transformer_bringup`, enabling the RealSense and Wheeltec IMU drivers by default. Override launch arguments as needed, for example to disable sensors on headless rigs:

```bash
ros2 launch transformer_bringup transformer_bringup.launch.py start_realsense:=false start_wheeltec_imu:=false
```

## Troubleshooting checklist

- Re-run `rosdep install --from-paths src --ignore-src -r -y` after adding ROS packages or enabling new options in launch files.
- Confirm devices are enumerated: `ls /dev/ttyUSB*` (for IMU) and `rs-enumerate-devices` (for RealSense).
- Verify the correct ROS environment is active: `echo $ROS_DISTRO` should return `jazzy` before building or launching.
