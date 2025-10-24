#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "transformer_msp_bridge/msp_parser.hpp" // for MSPPacket

namespace transformer_msp_bridge
{

  // Unified response schema types for MSP payloads.
  enum class FieldType : uint8_t
  {
    U8,
    I8,
    U16,
    I16,
    U32,
    I32,
    F32
  };

  struct FieldSpec
  {
    const char *name;   // field name, e.g. "roll"
    FieldType type;     // storage type on the wire
    const char *unit;   // optional unit string, e.g. "deg", can be nullptr
    double scale;       // multiplier to convert raw to unit (e.g. 0.1 for deci-deg to deg)
    std::size_t repeat; // number of repeated elements (arrays). 1 = scalar
  };

  struct ResponseSchema
  {
    const FieldSpec *fields; // pointer to static array of FieldSpec
    std::size_t count;       // number of FieldSpec entries
  };

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
  using BuildFn = std::function<std::vector<uint8_t>()>;

  struct CommandDescriptor
  {
    uint16_t id;                       // Upstream MSP_* constant.
    const char *name;                  // Human-readable identifier (stable; used for param name derivation).
    double poll_rate_hz;               // 0 = not auto-polled; otherwise target frequency.
    BuildFn build_request_fn;          // Deterministic builder for outbound request frame.
    const FieldSpec *response_schema;  // Optional pointer to response schema fields (nullptr if none)
    std::size_t response_schema_count; // Number of fields in schema (0 if none)
    constexpr bool is_v2() const { return id > 255; }
  };

  struct RegistryView
  {
    const CommandDescriptor *data;
    std::size_t size;
    const CommandDescriptor *begin() const { return data; }
    const CommandDescriptor *end() const { return data + size; }
  };

  // Returns a lightweight view over the immutable static registry array. Copy into a std::vector if
  // mutation (e.g., parameter-driven rate adjustments) is required by the caller.
  RegistryView get_default_registry();

  // Convenience: find a descriptor by ID (nullptr if not found)
  const CommandDescriptor *find_descriptor(uint16_t id);

  // Number of entries in the default registry (update tests if this changes intentionally).
  // Implemented inline because registry array is TU-local; we expose size as constexpr value.
  inline constexpr std::size_t kDefaultRegistrySize()
  {
    return 26;
  }

  // Schema helpers:
  //  - compute the total byte size implied by a schema (fixed-length only). Returns true and sets out_size.
  bool schema_fixed_size_bytes(const ResponseSchema &schema, std::size_t &out_size);

  // Parse payload according to schema and output flattened, scaled values in field order.
  // If out_names is non-null, it will be filled with names (arrays are suffixed with [i]).
  bool parse_to_flat_list(const ResponseSchema &schema, const std::vector<uint8_t> &payload,
                          std::vector<double> &out_values, std::vector<std::string> *out_names = nullptr,
                          std::string *err = nullptr);

} // namespace transformer_msp_bridge
