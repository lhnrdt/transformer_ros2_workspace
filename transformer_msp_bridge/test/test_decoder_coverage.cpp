#include <gtest/gtest.h>
#include <fstream>
#include <set>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>
#include "ament_index_cpp/get_package_share_directory.hpp"

TEST(DecoderCoverage, DefaultPolledCommandsHaveDecoders) {
  // Expected coverage by command name for v1 telemetry
  const std::set<std::string> covered_v1 = {
      "MSP_RAW_IMU",        // ImuDecoder
      "MSP_ATTITUDE",       // AttitudeDecoder
      "MSP_ALTITUDE",       // AltitudeDecoder
      "MSP_ANALOG",         // BatteryDecoder
      "MSP_RC",             // RcDecoder
      "MSP_RAW_GPS",        // GpsDecoder
      "MSP_COMP_GPS",       // GpsDecoder
      "MSP_SERVO",          // ServoMotorDecoder
      "MSP_MOTOR",          // ServoMotorDecoder
      "MSP_STATUS",         // SystemDecoder
      "MSP_GPSSTATISTICS",  // SystemDecoder
      "MSP_RC_TUNING",      // SystemDecoder
      "MSP_RTC"             // SystemDecoder
  };
  // Expected coverage by name for v2 telemetry handled via SensorDecoder, InavStatusDecoder, InavGenericDecoder
  const std::set<std::string> covered_v2 = {
      "MSP2_SENSOR_RANGEFINDER",   // SensorDecoder
      "MSP2_SENSOR_COMPASS",       // SensorDecoder
      "MSP2_SENSOR_BAROMETER",     // SensorDecoder
      "MSP2_INAV_STATUS",          // InavStatusDecoder
      "MSP2_INAV_ANALOG",          // InavGenericDecoder
      "MSP2_INAV_BATTERY_CONFIG",  // InavGenericDecoder
      "MSP2_INAV_AIR_SPEED",       // InavGenericDecoder
      "MSP2_INAV_TEMPERATURES",    // InavGenericDecoder
      "MSP2_INAV_ESC_RPM"          // InavGenericDecoder
  };

  std::string share;
  try {
    share = ament_index_cpp::get_package_share_directory("transformer_msp_bridge");
  } catch (const std::exception&) {
    FAIL() << "Package share directory not found";
  }
  const std::string path = share + "/config/registry.yaml";
  YAML::Node root = YAML::LoadFile(path);
  ASSERT_TRUE(root && root.IsMap());
  YAML::Node regs = root["registry"];
  ASSERT_TRUE(regs && regs.IsSequence());

  std::vector<std::string> missing;
  for (const auto& n : regs) {
    const double rate = n["poll_rate_hz"].as<double>(0.0);
    if (rate <= 0.0)
      continue;
    const std::string name = n["name"].as<std::string>("");
    const std::string id_str = n["id"].IsScalar() ? n["id"].as<std::string>("") : std::string();
    // Treat as v1 if id does not start with "MSP2_"
    const bool is_v2 = (!id_str.empty() && id_str.rfind("MSP2_", 0) == 0);
    if (!is_v2) {
      if (covered_v1.find(name) == covered_v1.end())
        missing.push_back(name.empty() ? id_str : name);
    } else {
      if (covered_v2.find(name) == covered_v2.end())
        missing.push_back(name.empty() ? id_str : name);
    }
  }

  if (!missing.empty()) {
    std::ostringstream oss;
    oss << "Missing decoders for polled commands:";
    for (auto& nm : missing)
      oss << ' ' << nm;
    FAIL() << oss.str();
  }
}
