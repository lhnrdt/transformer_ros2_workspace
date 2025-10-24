#include "transformer_msp_bridge/msp_registry.hpp"
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include "msp/msp_protocol.h"                      // external constants (v1 IDs)
#include "msp/msp_protocol_v2_sensor.h"            // v2 sensor IDs
#include "transformer_msp_bridge/msp_builders.hpp" // buildPacketRaw / buildPacketV2
#include "transformer_msp_bridge/msp_utils.hpp"    // LE readers for validators
#include "transformer_msp_bridge/registry_loader.hpp"

namespace transformer_msp_bridge
{

  namespace
  {
    // Schema helpers implementation
    static inline std::size_t field_type_size(FieldType t)
    {
      switch (t)
      {
      case FieldType::U8:
      case FieldType::I8:
        return 1;
      case FieldType::U16:
      case FieldType::I16:
        return 2;
      case FieldType::U32:
      case FieldType::I32:
        return 4;
      case FieldType::F32:
        return 4;
      default:
        return 0;
      }
    }

    static bool read_primitive(FieldType t, const std::vector<uint8_t> &p, std::size_t off, double scale, double &out_val)
    {
      switch (t)
      {
      case FieldType::U8:
      {
        uint8_t v;
        if (!readU8(p, off, v))
          return false;
        out_val = static_cast<double>(v) * scale;
        return true;
      }
      case FieldType::I8:
      {
        int8_t v;
        if (!readI8(p, off, v))
          return false;
        out_val = static_cast<double>(v) * scale;
        return true;
      }
      case FieldType::U16:
      {
        uint16_t v;
        if (!readU16LE(p, off, v))
          return false;
        out_val = static_cast<double>(v) * scale;
        return true;
      }
      case FieldType::I16:
      {
        int16_t v;
        if (!readI16LE(p, off, v))
          return false;
        out_val = static_cast<double>(v) * scale;
        return true;
      }
      case FieldType::U32:
      {
        uint32_t v;
        if (!readU32LE(p, off, v))
          return false;
        out_val = static_cast<double>(v) * scale;
        return true;
      }
      case FieldType::I32:
      {
        int32_t v;
        if (!readI32LE(p, off, v))
          return false;
        out_val = static_cast<double>(v) * scale;
        return true;
      }
      case FieldType::F32:
      {
        if (p.size() < off + 4)
          return false;
        float fv = 0.0F;
        std::memcpy(&fv, p.data() + off, sizeof(float));
        out_val = static_cast<double>(fv) * scale;
        return true;
      }
      }
      return false;
    }

  } // namespace

  // Implement schema helpers in the transformer_msp_bridge namespace scope
  bool schema_fixed_size_bytes(const ResponseSchema &schema, std::size_t &out_size)
  {
    std::size_t total = 0;
    for (std::size_t i = 0; i < schema.count; ++i)
    {
      const FieldSpec &f = schema.fields[i];
      const std::size_t elem = field_type_size(f.type);
      if (elem == 0 || f.repeat == 0)
        return false;
      if (total > SIZE_MAX / elem)
        return false;
      const std::size_t add = elem * f.repeat;
      if (total > SIZE_MAX - add)
        return false;
      total += add;
    }
    out_size = total;
    return true;
  }

  bool parse_to_flat_list(const ResponseSchema &schema, const std::vector<uint8_t> &payload,
                          std::vector<double> &out_values, std::vector<std::string> *out_names, std::string *err)
  {
    std::size_t need = 0;
    if (!schema_fixed_size_bytes(schema, need))
    {
      if (err)
        *err = "invalid schema";
      return false;
    }
    if (payload.size() < need)
    {
      if (err)
        *err = "payload too short for schema";
      return false;
    }
    out_values.clear();
    if (out_names)
      out_names->clear();
    std::size_t off = 0;
    for (std::size_t i = 0; i < schema.count; ++i)
    {
      const FieldSpec &f = schema.fields[i];
      const std::size_t elem_size = field_type_size(f.type);
      for (std::size_t r = 0; r < f.repeat; ++r)
      {
        double v{};
        if (!read_primitive(f.type, payload, off, f.scale, v))
        {
          if (err)
            *err = "failed to read field";
          return false;
        }
        out_values.push_back(v);
        if (out_names)
        {
          if (f.repeat == 1)
          {
            out_names->emplace_back(f.name);
          }
          else
          {
            out_names->emplace_back(std::string(f.name) + "[" + std::to_string(r) + "]");
          }
        }
        off += elem_size;
      }
    }
    return true;
  }

  // Public helper: find descriptor by id
  const CommandDescriptor *find_descriptor(uint16_t id)
  {
    auto view = get_default_registry();
    for (std::size_t i = 0; i < view.size; ++i)
      if (view.data[i].id == id)
        return &view.data[i];
    return nullptr;
  }

  namespace
  {

    // Registry Implementation Notes
    // =============================
    // The bridge maintains a fixed ordered table (`kRegistry`) describing each MSP command the node
    // knows how to request/poll. This replaces the previous runtime push_back construction so that:
    //  * Ordering is explicit and stable (important for deterministic parameter name mapping and tests).
    //  * The intent & grouping (MSPv1 core vs MSPv2 sensors vs INAV extensions) is visually apparent.
    //  * Duplicate IDs or incorrect v1/v2 labeling is caught very early (validator below).
    //
    // Formatting: The `kRegistry` array columns are manually aligned for readability across reviews.
    // A clang-format guard is used to prevent automatic reflow; if you must reformat, do so manually.
    //
    // Adding / Modifying Entries
    // --------------------------
    // 1. Ensure the MSP ID macro exists in the upstream headers included from external/inav. Do NOT
    //    introduce new numeric literals unless upstream truly lacks a symbol; if so, add a TODO comment.
    // 2. Choose a conservative poll_rate_hz. High rates (e.g., 50 Hz for IMU) should be justified.
    // 3. MSPv2 usage is now inferred automatically (id > 255). No manual flag required.
    // 4. Update the EXPECTED COUNT in test `StableEntryCountAndOrder` (test_msp_registry.cpp).
    // 5. Add / update a decoder to interpret responses if telemetry is expected.
    // 6. Keep ordering stable unless there is a strong reason; append new commands at the end of their
    //    logical category block to minimize churn.
    // 7. Run the full test suite; duplicate IDs will trigger a static_assert.
    //
    // Why not constexpr std::array with compile-time lambda evaluation? Because std::function is not
    // constexpr constructible pre-C++20. We accept static initialization for the small set of lambdas
    // while still making the structural fields (id/name/rate/flag) trivially inspectable.
    //
    // Builder helpers (template functions to produce function pointers, no allocations)
    template <uint16_t Id>
    std::vector<uint8_t> build_v1()
    {
      return buildPacketRaw(static_cast<uint8_t>(Id), {});
    }
    template <uint16_t Id>
    std::vector<uint8_t> build_v2()
    {
      return buildPacketV2(Id, {}, 0);
    }
    template <uint16_t Id>
    std::vector<uint8_t> build_v2_sensor()
    {
      return buildPacketV2(Id, {}, 0);
    }

    // Runtime registry: loaded from JSON at first use. No fallback.
    static const RuntimeRegistry &runtime_registry()
    {
      static const RuntimeRegistry rr = []
      {
        const std::string path = resolve_default_registry_json_path();
        if (path.empty())
        {
          throw std::runtime_error("No msp_messages_inav.json found (and no TRANSFORMER_MSP_REGISTRY_JSON set)");
        }
        return RuntimeRegistry::from_json_file(path);
      }();
      return rr;
    }

  } // namespace

  RegistryView get_default_registry()
  {
    const auto &rr = runtime_registry();
    return rr.view();
  }

  // Static validation (runtime asserts via if constexpr style not available; manually check uniqueness at startup if desired)
  // Compile-time validation utilities
  template <std::size_t N>
  constexpr bool ids_unique(const CommandDescriptor (&arr)[N])
  {
    for (std::size_t i = 0; i < N; ++i)
    {
      for (std::size_t j = i + 1; j < N; ++j)
      {
        if (arr[i].id == arr[j].id)
          return false;
      }
    }
    return true;
  }

  // NOTE: Can't static_assert uniqueness with non-constexpr std::function in runtime registry.
  // Consider adding a runtime check in debug builds if needed.
  // No explicit requires_v2 field anymore; correctness is implicit via CommandDescriptor::is_v2().

} // namespace transformer_msp_bridge
