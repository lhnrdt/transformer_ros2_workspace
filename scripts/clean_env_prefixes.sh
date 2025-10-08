#!/usr/bin/env bash
set -euo pipefail

# Remove non-existent entries from AMENT_PREFIX_PATH and CMAKE_PREFIX_PATH
_filter_path_var() {
  local var_name="$1"
  local IFS=':'
  local -a parts
  local -a kept=()
  local val
  val="${!var_name:-}"
  [ -z "$val" ] && return 0
  read -r -a parts <<< "$val"
  for p in "${parts[@]}"; do
    if [ -n "$p" ] && [ -d "$p" ]; then
      kept+=("$p")
    fi
  done
  local new
  IFS=':' read -r -a _ <<< "${kept[*]}" # shellcheck disable=SC2034
  new="$(IFS=:; echo "${kept[*]:-}")"
  export "$var_name"="$new"
}

_filter_path_var AMENT_PREFIX_PATH
_filter_path_var CMAKE_PREFIX_PATH

echo "Cleaned AMENT_PREFIX_PATH and CMAKE_PREFIX_PATH of non-existent entries."
