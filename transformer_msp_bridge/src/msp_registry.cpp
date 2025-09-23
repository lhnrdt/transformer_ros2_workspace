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
std::vector<uint8_t> build_v1() {
  return buildPacketRaw(static_cast<uint8_t>(Id), {});
}
template <uint16_t Id>
std::vector<uint8_t> build_v2() {
  return buildPacketV2(Id, {}, 0);
}

// NOTE: If you add or remove entries:
// 1. Update tests referencing kDefaultRegistrySize.
// 2. Keep ordering stable (used by deterministic polling parameter mapping).
// 3. Ensure ID is defined in external headers (do NOT locally invent IDs).
// 4. No requires_v2 field to set; MSPv2 is inferred by (id > 255).

// clang-format off
static constexpr CommandDescriptor kRegistry[] = {
  // ---- MSPv1 Core Telemetry ----
  {MSP_RAW_IMU,          "MSP_RAW_IMU",          50.0, &build_v1<MSP_RAW_IMU>},
  {MSP_SERVO,            "MSP_SERVO",            10.0, &build_v1<MSP_SERVO>},
  {MSP_MOTOR,            "MSP_MOTOR",            10.0, &build_v1<MSP_MOTOR>},
  {MSP_RC,               "MSP_RC",                5.0, &build_v1<MSP_RC>},
  {MSP_RAW_GPS,          "MSP_RAW_GPS",           5.0, &build_v1<MSP_RAW_GPS>},
  {MSP_COMP_GPS,         "MSP_COMP_GPS",          2.0, &build_v1<MSP_COMP_GPS>},
  {MSP_ATTITUDE,         "MSP_ATTITUDE",         10.0, &build_v1<MSP_ATTITUDE>},
  {MSP_ALTITUDE,         "MSP_ALTITUDE",          5.0, &build_v1<MSP_ALTITUDE>},
  {MSP_ANALOG,           "MSP_ANALOG",            2.0, &build_v1<MSP_ANALOG>},
  {MSP_RC_TUNING,        "MSP_RC_TUNING",         0.2, &build_v1<MSP_RC_TUNING>},
  {MSP_BATTERY_STATE,    "MSP_BATTERY_STATE",     1.0, &build_v1<MSP_BATTERY_STATE>},
  {MSP_RTC,              "MSP_RTC",               0.5, &build_v1<MSP_RTC>},
  {MSP_STATUS,           "MSP_STATUS",            2.0, &build_v1<MSP_STATUS>},
  {MSP_SENSOR_CONFIG,    "MSP_SENSOR_CONFIG",     2.0, &build_v1<MSP_SENSOR_CONFIG>},
  {MSP_GPSSTATISTICS,    "MSP_GPSSTATISTICS",     1.0, &build_v1<MSP_GPSSTATISTICS>},
  // ---- MSPv2 Sensors ----
  {MSP2_SENSOR_RANGEFINDER,  "MSP2_SENSOR_RANGEFINDER", 5.0, &build_v2<MSP2_SENSOR_RANGEFINDER>},
  {MSP2_SENSOR_COMPASS,      "MSP2_SENSOR_COMPASS",     5.0, &build_v2<MSP2_SENSOR_COMPASS>},
  {MSP2_SENSOR_BAROMETER,    "MSP2_SENSOR_BAROMETER",   5.0, &build_v2<MSP2_SENSOR_BAROMETER>},
  {MSP2_INAV_STATUS,         "MSP2_INAV_STATUS",        2.0, &build_v2<MSP2_INAV_STATUS>},
  {MSP2_INAV_ANALOG,         "MSP2_INAV_ANALOG",        2.0, &build_v2<MSP2_INAV_ANALOG>},
  {MSP2_INAV_BATTERY_CONFIG, "MSP2_INAV_BATTERY_CONFIG",0.05,&build_v2<MSP2_INAV_BATTERY_CONFIG>},
  {MSP2_INAV_AIR_SPEED,      "MSP2_INAV_AIR_SPEED",     5.0, &build_v2<MSP2_INAV_AIR_SPEED>},
  {MSP2_INAV_TEMPERATURES,   "MSP2_INAV_TEMPERATURES",  1.0, &build_v2<MSP2_INAV_TEMPERATURES>},
  {MSP2_INAV_ESC_RPM,        "MSP2_INAV_ESC_RPM",       5.0, &build_v2<MSP2_INAV_ESC_RPM>},
  {MSP2_COMMON_SETTING,      "MSP2_COMMON_SETTING",     0.0, &build_v2<MSP2_COMMON_SETTING>},
  {MSP2_COMMON_SET_SETTING,  "MSP2_COMMON_SET_SETTING", 0.0, &build_v2<MSP2_COMMON_SET_SETTING>},
};
// clang-format on

}  // namespace

// Size accessor now provided inline in header (kDefaultRegistrySize). Ensure header value matches array length.
static_assert(kDefaultRegistrySize() == (sizeof(kRegistry) / sizeof(kRegistry[0])), "kDefaultRegistrySize mismatch");

RegistryView get_default_registry() {
  return RegistryView{kRegistry, kDefaultRegistrySize()};
}

// Static validation (runtime asserts via if constexpr style not available; manually check uniqueness at startup if desired)
// Compile-time validation utilities
template <std::size_t N>
constexpr bool ids_unique(const CommandDescriptor (&arr)[N]) {
  for (std::size_t i = 0; i < N; ++i) {
    for (std::size_t j = i + 1; j < N; ++j) {
      if (arr[i].id == arr[j].id)
        return false;
    }
  }
  return true;
}

static_assert(ids_unique(kRegistry), "Duplicate MSP command id detected in registry");
// No explicit requires_v2 field anymore; correctness is implicit via CommandDescriptor::is_v2().

}  // namespace transformer_msp_bridge
