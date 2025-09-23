#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "transformer_msp_bridge/msp_parser.hpp"  // for MSPPacket

namespace transformer_msp_bridge {

// CommandDescriptor
//  Description: Metadata + request frame builder for an MSP command the bridge polls or can issue.
//  Invariants:
//   * id must correspond to an upstream-defined MSP_* constant (no local invention except where
//     upstream has not yet published a symbol; such cases should be rare and clearly commented).
//   * poll_rate_hz >= 0.0. A value of 0.0 means disabled by default (no periodic polling) but the
//     command is still exposed via parameters for manual enabling.
//   * MSPv2 usage is inferred automatically as (id > 255); no manual flag required.
//   * build_request_fn must be deterministic and return a fully framed MSPv1 or MSPv2 request.
//  Extension procedure (see also comments near kRegistry definition):
//   1. Add a new entry to kRegistry (keeping category grouping and ordering stable).
//   2. If the command should auto-poll, choose a conservative poll_rate_hz.
//   3. Update test `StableEntryCountAndOrder` expected count and any other assertions if needed.
//   4. Ensure decoding support exists (implement a decoder if telemetry is expected inbound).
//   5. Avoid large lambdas capturing state; builder lambdas here are non-capturing.
using BuildFn = std::vector<uint8_t> (*)();

struct CommandDescriptor {
  uint16_t id;               // Upstream MSP_* constant.
  const char* name;          // Human-readable identifier (stable; used for param name derivation).
  double poll_rate_hz;       // 0 = not auto-polled; otherwise target frequency.
  BuildFn build_request_fn;  // Deterministic builder for outbound request frame.
  constexpr bool is_v2() const { return id > 255; }
};

struct RegistryView {
  const CommandDescriptor* data;
  std::size_t size;
  const CommandDescriptor* begin() const { return data; }
  const CommandDescriptor* end() const { return data + size; }
};

// Returns a lightweight view over the immutable static registry array. Copy into a std::vector if
// mutation (e.g., parameter-driven rate adjustments) is required by the caller.
RegistryView get_default_registry();

// Number of entries in the default registry (update tests if this changes intentionally).
// Implemented inline because registry array is TU-local; we expose size as constexpr value.
inline constexpr std::size_t kDefaultRegistrySize() {
  return 26;
}

}  // namespace transformer_msp_bridge
