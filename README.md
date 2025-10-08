# Transformer ROS 2 Workspace

Key points:
- Submodules:
  - `src/serial-ros2` (RoverRobotics fork)
  - `src/ros2_wheeltec_n100_imu`
  - `src/external/inav` (sparse/partial checkout of only `inav/src/main/msp`)
- Helper script: `scripts/setup_submodules.sh` ensures submodules are initialized shallowly and that only the MSP headers/sources from INAV are checked out.

## Prerequisites

- Linux (tested on Ubuntu; other distros should work with ROS 2 installed)
- ROS 2 (Humble or newer recommended)
- colcon and build tools

Install ROS 2 and colcon as per your platform’s official instructions:
- https://docs.ros.org/en/ (select your OS and distro)

Ensure environment is sourced before building:
```bash
source /opt/ros/<your_ros2_distro>/setup.bash
```

## Clone and initialize

```bash
# clone
git clone https://github.com/lhnrdt/transformer_ros2_workspace.git
cd transformer_ros2_workspace  # this is the ros2_ws root

# initialize submodules (shallow) and sparse-checkout INAV MSP only
bash scripts/setup_submodules.sh
```

What the script does:
- Initializes all submodules shallowly with a blob-less filter.
- Configures `src/external/inav` as a partial clone with sparse-checkout targeting only `src/main/msp`.
- Checks out the superproject-pinned commit if available, otherwise the latest `master` from INAV.

Notes on INAV sparse checkout:
- Only `src/main/msp` is present in the INAV working tree.
- You may still see `src/` directories at the top level of the submodule; that’s expected. Only the MSP files are materialized.

## Build

From the workspace root:
```bash
# Ensure your ROS 2 environment is sourced first
source /opt/ros/<your_ros2_distro>/setup.bash

# Build with colcon
colcon build --symlink-install

# Source the workspace
source install/local_setup.bash
```

## Run

This depends on your packages and launch files. Common options:
- Use the provided helper (if applicable):
  ```bash
  ./start_transformer.sh
  ```
- Or run/launch specific nodes (examples):
  ```bash
  # Example: bringup (adjust package/launch names as needed)
  ros2 launch transformer_bringup bringup.launch.py
  ```

## Updating the workspace

Pull latest changes and refresh submodules:
```bash
# Update the superproject
git pull --rebase

# Re-apply submodule init and sparse checkout
bash scripts/setup_submodules.sh
```

Updating the INAV submodule pointer:
```bash
# Enter the submodule
cd src/external/inav
# Optionally sync to latest master (sparse/shallow is preserved)
git fetch --depth=1 --filter=blob:none origin master
git checkout -f FETCH_HEAD
cd -
# Record new pointer in the superproject
git add src/external/inav
git commit -m "chore: bump INAV submodule"
```

## Cleaning the workspace

```bash
# From repo root
rm -rf build/ install/ log/

# Rebuild
colcon build --symlink-install
```