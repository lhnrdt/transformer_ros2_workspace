#pragma once

#include <unordered_map>
#include <cstdint>

namespace transformer_msp_bridge {

struct CommandRuntimeConfig {
  bool enabled{true};
  double rate_hz{0.0};
};

using CommandConfigMap = std::unordered_map<uint16_t, CommandRuntimeConfig>;

} // namespace transformer_msp_bridge
