#!/usr/bin/env bash
set -euo pipefail

# Usage: scripts/build.sh [--release]

# Source ROS 2 if not already sourced
if [ -z "${ROS_DISTRO:-}" ]; then
  if [ -f "/opt/ros/jazzy/setup.bash" ]; then
    source /opt/ros/jazzy/setup.bash
  elif [ -n "${ROS_VERSION:-}" ]; then
    echo "ROS environment already sourced (ROS_VERSION=$ROS_VERSION)"
  else
    echo "Warning: ROS 2 environment not sourced. Source your distro setup.bash first." >&2
  fi
fi

# Clean bad prefixes (prevents colcon AMENT/CMAKE warnings)
"$(dirname "$0")/clean_env_prefixes.sh"

colcon build --symlink-install "$@"
