#include "transformer_msp_bridge/registry_loader.hpp"

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <utility>

#include <yaml-cpp/yaml.h>

#include "ament_index_cpp/get_package_share_directory.hpp"
#include "msp/msp_protocol.h"
#include "msp/msp_protocol_v2_sensor.h"
#include "transformer_msp_bridge/msp_builders.hpp"

namespace transformer_msp_bridge {

namespace {

FieldType parse_field_type(std::string s) {
  // Accept common aliases and C type names; case-insensitive
  for (auto& ch : s)
    ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
  if (s == "i8" || s == "int8_t")
    return FieldType::I8;
  if (s == "u8" || s == "uint8_t")
    return FieldType::U8;
  if (s == "i16" || s == "int16_t")
    return FieldType::I16;
  if (s == "u16" || s == "uint16_t")
    return FieldType::U16;
  if (s == "i32" || s == "int32_t")
    return FieldType::I32;
  if (s == "u32" || s == "uint32_t")
    return FieldType::U32;
  throw std::runtime_error("Unknown field type: " + s);
}

uint16_t parse_id_scalar(const YAML::Node& n) {
  // Accept integer or string forms. Strings may be decimal, hex (0x...), or MSP macro names.
  if (n.IsScalar()) {
    const std::string s = n.as<std::string>();
    // Try numeric first
    char* endp = nullptr;
    unsigned long v = 0;
    if (!s.empty()) {
      if (s.size() > 2 && (s[0] == '0') && (s[1] == 'x' || s[1] == 'X')) {
        v = std::strtoul(s.c_str(), &endp, 16);
      } else if (std::isdigit(static_cast<unsigned char>(s[0]))) {
        v = std::strtoul(s.c_str(), &endp, 10);
      }
      if (endp && *endp == '\0' && v <= 0xFFFFUL) {
        return static_cast<uint16_t>(v);
      }
    }
    // Fallback to name -> id mapping for known MSP symbols
    static const std::pair<const char*, uint16_t> kPairs[] = {
        {"MSP_RAW_IMU", MSP_RAW_IMU},
        {"MSP_SERVO", MSP_SERVO},
        {"MSP_MOTOR", MSP_MOTOR},
        {"MSP_RC", MSP_RC},
        {"MSP_RAW_GPS", MSP_RAW_GPS},
        {"MSP_COMP_GPS", MSP_COMP_GPS},
        {"MSP_ATTITUDE", MSP_ATTITUDE},
        {"MSP_ALTITUDE", MSP_ALTITUDE},
        {"MSP_ANALOG", MSP_ANALOG},
        {"MSP_RC_TUNING", MSP_RC_TUNING},
        {"MSP_BATTERY_STATE", MSP_BATTERY_STATE},
        {"MSP_RTC", MSP_RTC},
        {"MSP_STATUS", MSP_STATUS},
        {"MSP_SENSOR_CONFIG", MSP_SENSOR_CONFIG},
        {"MSP_GPSSTATISTICS", MSP_GPSSTATISTICS},
        {"MSP2_SENSOR_RANGEFINDER", MSP2_SENSOR_RANGEFINDER},
        {"MSP2_SENSOR_COMPASS", MSP2_SENSOR_COMPASS},
        {"MSP2_SENSOR_BAROMETER", MSP2_SENSOR_BAROMETER},
        {"MSP2_INAV_STATUS", MSP2_INAV_STATUS},
        {"MSP2_INAV_ANALOG", MSP2_INAV_ANALOG},
        {"MSP2_INAV_BATTERY_CONFIG", MSP2_INAV_BATTERY_CONFIG},
        {"MSP2_INAV_AIR_SPEED", MSP2_INAV_AIR_SPEED},
        {"MSP2_INAV_TEMPERATURES", MSP2_INAV_TEMPERATURES},
        {"MSP2_INAV_ESC_RPM", MSP2_INAV_ESC_RPM},
        {"MSP2_COMMON_SETTING", MSP2_COMMON_SETTING},
        {"MSP2_COMMON_SET_SETTING", MSP2_COMMON_SET_SETTING},
    };
    static const std::unordered_map<std::string, uint16_t> kMap = [] {
      std::unordered_map<std::string, uint16_t> m;
      for (const auto& p : kPairs)
        m.emplace(p.first, p.second);
      return m;
    }();
    auto it = kMap.find(s);
    if (it != kMap.end())
      return it->second;
    throw std::runtime_error("Unknown MSP id: " + s);
  }
  if (n.IsScalar() || n.IsNull()) {
    throw std::runtime_error("id must be a scalar");
  }
  return n.as<uint16_t>();
}

RuntimeRegistry::OwnedSchema parse_schema(const YAML::Node& n) {
  // Minimal schema: a sequence of C type names in wire order.
  if (!n || !n.IsSequence()) {
    throw std::runtime_error("schema must be a sequence of type strings");
  }
  const std::size_t N = n.size();
  RuntimeRegistry::OwnedSchema os;
  os.fields = std::make_unique<FieldSpec[]>(N);
  os.names = std::make_unique<std::string[]>(N);
  os.units = std::make_unique<std::string[]>(N);
  os.count = N;
  for (std::size_t i = 0; i < N; ++i) {
    const auto& item = n[i];
    if (!item.IsScalar()) {
      throw std::runtime_error("schema entries must be scalar type names");
    }
    const std::string type_str = item.as<std::string>();
    const FieldType type = parse_field_type(type_str);
    // Minimal spec: no names/units/scales/repeats; defaults only
    os.names[i] = std::string();
    os.units[i] = std::string();
    os.fields[i] = FieldSpec{os.names[i].c_str(), type, nullptr, 1.0, 1};
  }
  return os;
}

// Helper to build request based on id (v1 for id <= 255, v2 otherwise)
using BuildArgFn = std::function<std::vector<uint8_t>(uint16_t)>;
static BuildArgFn builder_for_id(uint16_t id) {
  if (id <= 255) {
    return [](uint16_t cmd) {
      return buildPacketRaw(static_cast<uint8_t>(cmd), {});
    };
  }
  return [](uint16_t cmd) {
    return buildPacketV2(cmd, {}, 0);
  };
}

}  // namespace

RuntimeRegistry RuntimeRegistry::from_yaml_file(const std::string& yaml_path) {
  RuntimeRegistry rr;

  YAML::Node root = YAML::LoadFile(yaml_path);
  if (!root || !root.IsMap()) {
    throw std::runtime_error("registry YAML root must be a map");
  }

  // Canonical key is "registry"; accept legacy "commands" as fallback
  YAML::Node cmds = root["registry"];
  if (!cmds || !cmds.IsSequence()) {
    cmds = root["commands"];  // accept alternative key
  }
  if (!cmds || !cmds.IsSequence()) {
    throw std::runtime_error("registry YAML must contain a 'registry' (or legacy 'commands') sequence");
  }

  rr.descriptors_.reserve(cmds.size());
  rr.owned_names_.reserve(cmds.size());
  std::vector<RuntimeRegistry::OwnedSchema> owned;
  owned.reserve(cmds.size());
  for (const auto& c : cmds) {
    CommandDescriptor d{};
    d.id = parse_id_scalar(c["id"]);
    rr.owned_names_.push_back(c["name"].as<std::string>(""));
    d.name = rr.owned_names_.back().c_str();
    // Infer builder from id
    const auto build = builder_for_id(d.id);
    d.build_request_fn = [build, id = d.id]() {
      return build(id);
    };
    // Polling rate: canonical key is poll_rate_hz; accept legacy rate_hz
    d.poll_rate_hz = c["poll_rate_hz"].as<double>(c["rate_hz"].as<double>(0.0));

    if (c["schema"]) {
      const YAML::Node schemaNode = c["schema"];  // minimal spec: direct list of types
      if (!schemaNode || !schemaNode.IsSequence())
        throw std::runtime_error("schema must be a sequence of type strings");
      owned.emplace_back(parse_schema(schemaNode));
      const RuntimeRegistry::OwnedSchema& os = owned.back();
      d.response_schema = os.fields.get();
      d.response_schema_count = os.count;
    } else {
      d.response_schema = nullptr;
      d.response_schema_count = 0;
    }

    rr.descriptors_.push_back(std::move(d));
  }

  // Transfer ownership to member storage to keep pointers valid
  rr.owned_schemas_ = std::move(owned);
  return rr;
}

const CommandDescriptor* RuntimeRegistry::find(uint16_t id, bool v2) const {
  for (const auto& d : descriptors_) {
    if (d.id == id && d.is_v2() == v2)
      return &d;
  }
  return nullptr;
}

std::string resolve_default_registry_yaml_path() {
  // Allow override via env var
  if (const char* env = std::getenv("TRANSFORMER_MSP_REGISTRY_YAML")) {
    return std::string(env);
  }
  try {
    const auto share = ament_index_cpp::get_package_share_directory("transformer_msp_bridge");
    return share + "/config/registry.yaml";
  } catch (const std::exception&) {
    return std::string();
  }
}

}  // namespace transformer_msp_bridge
