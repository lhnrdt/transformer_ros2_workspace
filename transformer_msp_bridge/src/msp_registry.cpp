#include "transformer_msp_bridge/msp_registry.hpp"
#include "msp/msp_protocol.h"                       // external constants (v1 IDs)
#include "msp/msp_protocol_v2_sensor.h"             // v2 sensor IDs
#include "transformer_msp_bridge/msp_builders.hpp"  // buildPacketRaw / buildPacketV2

namespace transformer_msp_bridge {

namespace {

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
// 3. Set requires_v2 = true for any id > 255 or if protocol requires MSPv2.
// 4. Update the EXPECTED COUNT in test `StableEntryCountAndOrder` (test_msp_registry.cpp).
// 5. Add / update a decoder to interpret responses if telemetry is expected.
// 6. Keep ordering stable unless there is a strong reason; append new commands at the end of their
//    logical category block to minimize churn.
// 7. Run the full test suite; duplicate IDs or mis-labeled requires_v2 will abort at startup.
//
// Why not constexpr std::array with compile-time lambda evaluation? Because std::function is not
// constexpr constructible pre-C++20. We accept static initialization for the small set of lambdas
// while still making the structural fields (id/name/rate/flag) trivially inspectable.
//
// Helper lambdas must be non-capturing so their types remain simple and copyable into std::function.

inline std::function<std::vector<uint8_t>()> make_v1(uint16_t id) {
  return [id]() {
    return buildPacketRaw(static_cast<uint8_t>(id), {});
  };
}
inline std::function<std::vector<uint8_t>()> make_v2(uint16_t id) {
  return [id]() {
    return buildPacketV2(id, {}, 0);
  };
}

// NOTE: If you add or remove entries:
// 1. Update tests referencing kDefaultRegistrySize.
// 2. Keep ordering stable (used by deterministic polling parameter mapping).
// 3. Ensure ID is defined in external headers (do NOT locally invent IDs).
// 4. Set requires_v2=true for any id > 255 or native MSPv2 only command.

// clang-format off
static const CommandDescriptor kRegistry[] = {
  // ---- MSPv1 Core Telemetry ----
  {MSP_RAW_IMU,          "MSP_RAW_IMU",          50.0, make_v1(MSP_RAW_IMU), false},
  {MSP_SERVO,            "MSP_SERVO",            10.0, make_v1(MSP_SERVO), false},
  {MSP_MOTOR,            "MSP_MOTOR",            10.0, make_v1(MSP_MOTOR), false},
  {MSP_RC,               "MSP_RC",                5.0, make_v1(MSP_RC), false},
  {MSP_RAW_GPS,          "MSP_RAW_GPS",           5.0, make_v1(MSP_RAW_GPS), false},
  {MSP_COMP_GPS,         "MSP_COMP_GPS",          2.0, make_v1(MSP_COMP_GPS), false},
  {MSP_ATTITUDE,         "MSP_ATTITUDE",         10.0, make_v1(MSP_ATTITUDE), false},
  {MSP_ALTITUDE,         "MSP_ALTITUDE",          5.0, make_v1(MSP_ALTITUDE), false},
  {MSP_ANALOG,           "MSP_ANALOG",            2.0, make_v1(MSP_ANALOG), false},
  {MSP_RC_TUNING,        "MSP_RC_TUNING",         0.2, make_v1(MSP_RC_TUNING), false},
  {MSP_BATTERY_STATE,    "MSP_BATTERY_STATE",     1.0, make_v1(MSP_BATTERY_STATE), false},
  {MSP_RTC,              "MSP_RTC",               0.5, make_v1(MSP_RTC), false},
  {MSP_STATUS,           "MSP_STATUS",            2.0, make_v1(MSP_STATUS), false},
  {MSP_SENSOR_CONFIG,    "MSP_SENSOR_CONFIG",     2.0, make_v1(MSP_SENSOR_CONFIG), false},
  {MSP_GPSSTATISTICS,    "MSP_GPSSTATISTICS",     1.0, make_v1(MSP_GPSSTATISTICS), false},
  // ---- MSPv2 Sensors ----
  {MSP2_SENSOR_RANGEFINDER,  "MSP2_SENSOR_RANGEFINDER", 5.0, make_v2(MSP2_SENSOR_RANGEFINDER), true},
  {MSP2_SENSOR_COMPASS,      "MSP2_SENSOR_COMPASS",     5.0, make_v2(MSP2_SENSOR_COMPASS), true},
  {MSP2_SENSOR_BAROMETER,    "MSP2_SENSOR_BAROMETER",   5.0, make_v2(MSP2_SENSOR_BAROMETER), true},
  {MSP2_INAV_STATUS,         "MSP2_INAV_STATUS",        2.0, make_v2(MSP2_INAV_STATUS), true},
  {MSP2_INAV_ANALOG,         "MSP2_INAV_ANALOG",        2.0, make_v2(MSP2_INAV_ANALOG), true},
  {MSP2_INAV_BATTERY_CONFIG, "MSP2_INAV_BATTERY_CONFIG",0.05,make_v2(MSP2_INAV_BATTERY_CONFIG), true},
  {MSP2_INAV_AIR_SPEED,      "MSP2_INAV_AIR_SPEED",     5.0, make_v2(MSP2_INAV_AIR_SPEED), true},
  {MSP2_INAV_TEMPERATURES,   "MSP2_INAV_TEMPERATURES",  1.0, make_v2(MSP2_INAV_TEMPERATURES), true},
  {MSP2_INAV_ESC_RPM,        "MSP2_INAV_ESC_RPM",       5.0, make_v2(MSP2_INAV_ESC_RPM), true},
  {MSP2_COMMON_SETTING,      "MSP2_COMMON_SETTING",     0.0, make_v2(MSP2_COMMON_SETTING), true},
  {MSP2_COMMON_SET_SETTING,  "MSP2_COMMON_SET_SETTING", 0.0, make_v2(MSP2_COMMON_SET_SETTING), true},
};
// clang-format on

}  // namespace

// Compile-time size accessor (cannot be constexpr variable with inline due to ODR concerns across TUs before C++17 inline variables; using function instead)
constexpr std::size_t kDefaultRegistrySize() {
  return sizeof(kRegistry) / sizeof(kRegistry[0]);
}

RegistryView get_default_registry() {
  return RegistryView{kRegistry, kDefaultRegistrySize()};
}

// Static validation (runtime asserts via if constexpr style not available; manually check uniqueness at startup if desired)
namespace {
struct RegistryValidator {
  RegistryValidator() {
    // Uniqueness O(N^2) check (N small)
    for (std::size_t i = 0; i < kDefaultRegistrySize(); ++i) {
      for (std::size_t j = i + 1; j < kDefaultRegistrySize(); ++j) {
        if (kRegistry[i].id == kRegistry[j].id) {
          // Intentional assert style abort; could use throw but this is programming error.
          fprintf(stderr, "Duplicate MSP command id %u between %s and %s\n", kRegistry[i].id, kRegistry[i].name,
                  kRegistry[j].name);
          std::abort();
        }
      }
    }
    // requires_v2 correctness: any id >255 must have requires_v2 true
    for (auto& d : kRegistry) {
      if (d.id > 255 && !d.requires_v2) {
        fprintf(stderr, "MSP id %u (%s) >255 but requires_v2=false\n", d.id, d.name);
        std::abort();
      }
    }
  }
};
static RegistryValidator g_registry_validator;  // NOLINT
}  // namespace

}  // namespace transformer_msp_bridge
