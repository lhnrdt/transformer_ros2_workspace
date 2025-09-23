#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <functional>

#include "transformer_msp_bridge/msp_protocol.hpp" // for MSPPacket

namespace transformer_msp_bridge {

// Simple descriptor for manually maintained MSP command metadata.
struct CommandDescriptor {
  uint16_t id;                 // MSP_* constant from external headers
  const char * name;           // Human-readable
  double poll_rate_hz;         // 0 = do not auto-poll
  std::function<std::vector<uint8_t>()> build_request_cb; // Build outbound frame (no payload typical)
  bool requires_v2{false};     // Mark commands that need native v2 capability
};

// Build a vector of descriptors; node supplies lambdas for decode/publish.
std::vector<CommandDescriptor> build_default_registry();

} // namespace transformer_msp_bridge
