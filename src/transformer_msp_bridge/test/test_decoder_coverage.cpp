#include <gtest/gtest.h>
#include <fstream>
#include <set>
#include <string>
#include <vector>

#include "transformer_msp_bridge/msp_registry.hpp"

TEST(DecoderCoverage, DefaultPolledCommandsHaveDecoders)
{
  // Expected coverage by command name for v1 telemetry
  const std::set<std::string> covered_v1 = {
      "MSP_RAW_IMU",       // ImuDecoder
      "MSP_ATTITUDE",      // AttitudeDecoder
      "MSP_ALTITUDE",      // AltitudeDecoder
      "MSP_ANALOG",        // BatteryDecoder
      "MSP_RC",            // RcDecoder
      "MSP_RAW_GPS",       // GpsDecoder
      "MSP_COMP_GPS",      // GpsDecoder
      "MSP_SERVO",         // ServoMotorDecoder
      "MSP_MOTOR",         // ServoMotorDecoder
      "MSP_STATUS",        // SystemDecoder
      "MSP_GPSSTATISTICS", // SystemDecoder
      "MSP_RC_TUNING",     // SystemDecoder
      "MSP_RTC"            // SystemDecoder
  };
  // Expected coverage by name for v2 telemetry handled via SensorDecoder, InavStatusDecoder, InavGenericDecoder
  const std::set<std::string> covered_v2 = {
      "MSP2_SENSOR_RANGEFINDER",  // SensorDecoder
      "MSP2_SENSOR_COMPASS",      // SensorDecoder
      "MSP2_SENSOR_BAROMETER",    // SensorDecoder
      "MSP2_INAV_STATUS",         // InavStatusDecoder
      "MSP2_INAV_ANALOG",         // InavGenericDecoder
      "MSP2_INAV_BATTERY_CONFIG", // InavGenericDecoder
      "MSP2_INAV_AIR_SPEED",      // InavGenericDecoder
      "MSP2_INAV_TEMPERATURES",   // InavGenericDecoder
      "MSP2_INAV_ESC_RPM"         // InavGenericDecoder
  };

  std::vector<std::string> missing;
  auto view = transformer_msp_bridge::get_default_registry();
  for (const auto &d : view)
  {
    const double rate = d.poll_rate_hz;
    if (rate <= 0.0)
      continue;
    const std::string name = (d.name != nullptr) ? std::string(d.name) : std::string();
    const bool is_v2 = d.is_v2();
    if (!is_v2)
    {
      if (covered_v1.find(name) == covered_v1.end())
        missing.push_back(name.empty() ? std::string("id_" + std::to_string(d.id)) : name);
    }
    else
    {
      if (covered_v2.find(name) == covered_v2.end())
        missing.push_back(name.empty() ? std::string("id_" + std::to_string(d.id)) : name);
    }
  }

  if (!missing.empty())
  {
    std::ostringstream oss;
    oss << "Missing decoders for polled commands:";
    for (auto &nm : missing)
      oss << ' ' << nm;
    FAIL() << oss.str();
  }
}
