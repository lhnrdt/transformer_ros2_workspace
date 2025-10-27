// Implements registry lookups and default polling metadata for MSP commands.
#include "transformer_msp_bridge/msp_registry.hpp"

#include <algorithm>
#include <array>
#include <cstring>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

#include "transformer_msp_bridge/msp_builders.hpp"

namespace transformer_msp_bridge::msp
{
namespace
{

using transformer_msp_bridge::buildPacketRaw;
using transformer_msp_bridge::buildPacketV2;
using ::msp::all_messages;
using ::msp::MspMsg;

const std::vector<const MspMsg *> &messages()
{
  return all_messages();
}

const std::unordered_map<std::string_view, const MspMsg *, std::hash<std::string_view>, std::equal_to<>> &name_lookup()
{
  static const auto lookup = []() {
    std::unordered_map<std::string_view, const MspMsg *, std::hash<std::string_view>, std::equal_to<>> map;
    map.reserve(messages().size());
    for (const MspMsg *msg : messages())
    {
      if (msg && !msg->name.empty())
      {
        map.emplace(msg->name, msg);
      }
    }
    return map;
  }();
  return lookup;
}

const std::unordered_map<uint16_t, const MspMsg *> &id_lookup()
{
  static const auto lookup = []() {
    std::unordered_map<uint16_t, const MspMsg *> map;
    map.reserve(messages().size());
    for (const MspMsg *msg : messages())
    {
      if (msg)
      {
        const uint32_t id = msg->id_hex;
        map.emplace(static_cast<uint16_t>(id & 0xFFFFu), msg);
      }
    }
    return map;
  }();
  return lookup;
}

std::vector<uint8_t> build_request(uint16_t id)
{
  if (id <= 0xFFu)
  {
    return buildPacketRaw(static_cast<uint8_t>(id), {});
  }
  return buildPacketV2(id, {});
}

struct DefaultCommandDefinition
{
  const char *name;
  double rate_hz;
  bool default_polled;
};

constexpr std::array<DefaultCommandDefinition, 22> kDefaultCommands = {{
    {"MSP_RAW_IMU", 50.0, false},
    {"MSP_SERVO", 10.0, true},
    {"MSP_MOTOR", 10.0, true},
    {"MSP_RC", 5.0, true},
    {"MSP_RAW_GPS", 5.0, true},
    {"MSP_COMP_GPS", 2.0, true},
    {"MSP_ATTITUDE", 10.0, true},
    {"MSP_ALTITUDE", 5.0, true},
  {"MSP_ANALOG", 0.0, false},
    {"MSP_RC_TUNING", 0.2, false},
  {"MSP_BATTERY_STATE", 0.0, false},
    {"MSP_RTC", 0.5, false},
    {"MSP_STATUS_EX", 2.0, true},
    {"MSP_SENSOR_CONFIG", 2.0, true},
  {"MSP_SENSOR_STATUS", 2.0, true},
    {"MSP_GPSSTATISTICS", 1.0, true},
    {"MSP2_INAV_STATUS", 2.0, true},
  {"MSP2_INAV_ANALOG", 2.0, true},
  {"MSP2_INAV_BATTERY_CONFIG", 0.5, true},
    {"MSP2_INAV_AIR_SPEED", 5.0, true},
    {"MSP2_INAV_TEMPERATURES", 1.0, true},
    {"MSP2_INAV_ESC_RPM", 5.0, true},
}};

inline std::string_view trim(std::string_view text)
{
  const auto is_space = [](char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
  };
  while (!text.empty() && is_space(text.front()))
  {
    text.remove_prefix(1);
  }
  while (!text.empty() && is_space(text.back()))
  {
    text.remove_suffix(1);
  }
  return text;
}

bool parse_decimal(std::string_view text, std::size_t &value)
{
  text = trim(text);
  if (text.empty())
  {
    return false;
  }
  std::size_t result = 0;
  for (char ch : text)
  {
    if (ch < '0' || ch > '9')
    {
      return false;
    }
    result = result * 10u + static_cast<std::size_t>(ch - '0');
  }
  value = result;
  return true;
}

enum class BaseType
{
  kUnknown,
  kUnsigned8,
  kSigned8,
  kUnsigned16,
  kSigned16,
  kUnsigned32,
  kSigned32,
  kFloat,
  kSkip
};

struct TypeInfo
{
  BaseType base{BaseType::kUnknown};
  std::size_t element_size{0};
  std::size_t fixed_length{1};
  bool variable_length{false};
};

TypeInfo parse_type(std::string_view type_str)
{
  TypeInfo info;
  type_str = trim(type_str);
  const auto bracket_pos = type_str.find('[');
  if (bracket_pos != std::string_view::npos)
  {
    const auto close_pos = type_str.find(']', bracket_pos);
    if (close_pos != std::string_view::npos && close_pos > bracket_pos + 1)
    {
      const std::string_view interior = type_str.substr(bracket_pos + 1, close_pos - bracket_pos - 1);
      std::size_t parsed_length = 0;
      if (parse_decimal(interior, parsed_length))
      {
        info.fixed_length = parsed_length;
      }
      else
      {
        info.variable_length = true;
      }
    }
    else
    {
      info.variable_length = true;
    }
    type_str = type_str.substr(0, bracket_pos);
    type_str = trim(type_str);
  }

  if (type_str == "uint8_t" || type_str == "uint8" || type_str == "bool")
  {
    info.base = BaseType::kUnsigned8;
    info.element_size = 1;
  }
  else if (type_str == "int8_t" || type_str == "int8")
  {
    info.base = BaseType::kSigned8;
    info.element_size = 1;
  }
  else if (type_str == "uint16_t" || type_str == "uint16")
  {
    info.base = BaseType::kUnsigned16;
    info.element_size = 2;
  }
  else if (type_str == "int16_t" || type_str == "int16")
  {
    info.base = BaseType::kSigned16;
    info.element_size = 2;
  }
  else if (type_str == "uint32_t" || type_str == "uint32")
  {
    info.base = BaseType::kUnsigned32;
    info.element_size = 4;
  }
  else if (type_str == "int32_t" || type_str == "int32")
  {
    info.base = BaseType::kSigned32;
    info.element_size = 4;
  }
  else if (type_str == "float" || type_str == "float32")
  {
    info.base = BaseType::kFloat;
    info.element_size = 4;
  }
  else if (type_str == "char")
  {
    info.base = BaseType::kSkip;
    info.element_size = 1;
  }
  else
  {
    info.base = BaseType::kUnknown;
  }
  return info;
}

double load_value(const std::vector<uint8_t> &payload, std::size_t offset, BaseType base)
{
  switch (base)
  {
  case BaseType::kUnsigned8:
    return static_cast<double>(payload[offset]);
  case BaseType::kSigned8:
    return static_cast<double>(static_cast<int8_t>(payload[offset]));
  case BaseType::kUnsigned16:
    return static_cast<double>(static_cast<uint16_t>(payload[offset] | (payload[offset + 1] << 8)));
  case BaseType::kSigned16:
    return static_cast<double>(static_cast<int16_t>(payload[offset] | (payload[offset + 1] << 8)));
  case BaseType::kUnsigned32:
  {
    const uint32_t value = static_cast<uint32_t>(payload[offset] | (payload[offset + 1] << 8) |
                                                 (payload[offset + 2] << 16) | (payload[offset + 3] << 24));
    return static_cast<double>(value);
  }
  case BaseType::kSigned32:
  {
    const int32_t value = static_cast<int32_t>(payload[offset] | (payload[offset + 1] << 8) |
                                               (payload[offset + 2] << 16) | (payload[offset + 3] << 24));
    return static_cast<double>(value);
  }
  case BaseType::kFloat:
  {
    float value = 0.0f;
    std::memcpy(&value, payload.data() + offset, sizeof(float));
    return static_cast<double>(value);
  }
  case BaseType::kSkip:
  case BaseType::kUnknown:
  default:
    return 0.0;
  }
}

MessageSchema make_schema(const MspMsg &msg)
{
  if (!msg.fields || msg.field_count == 0)
  {
    MessageSchema empty{};
    empty.message = &msg;
    return empty;
  }

  for (std::size_t i = 0; i < msg.field_count; ++i)
  {
    const auto &field = msg.fields[i];
    TypeInfo info = parse_type(field.ctype);
    if (info.base == BaseType::kUnknown)
    {
      return {};
    }
  }
  MessageSchema schema{};
  schema.fields = msg.fields;
  schema.count = msg.field_count;
  schema.message = &msg;
  return schema;
}

} // namespace

uint16_t command_id(std::string_view name)
{
  const auto &map = name_lookup();
  const auto it = map.find(name);
  if (it == map.end())
  {
    return 0;
  }
  return static_cast<uint16_t>(it->second->id_hex & 0xFFFFu);
}

const MspMsg *find_message_by_name(std::string_view name)
{
  const auto &map = name_lookup();
  const auto it = map.find(name);
  if (it == map.end())
  {
    return nullptr;
  }
  return it->second;
}

const MspMsg *find_message_by_id(uint16_t id)
{
  const auto &map = id_lookup();
  const auto it = map.find(id);
  if (it == map.end())
  {
    return nullptr;
  }
  return it->second;
}

bool is_v2(uint16_t id)
{
  const MspMsg *msg = find_message_by_id(id);
  if (msg)
  {
    return (msg->id_hex > 0xFFu);
  }
  return id > 0xFFu;
}

std::string_view message_name(uint16_t id)
{
  const MspMsg *msg = find_message_by_id(id);
  if (msg)
  {
    return msg->name;
  }
  return {};
}

RegistryView get_default_registry()
{
  struct Holder
  {
    std::vector<RegistryEntry> entries;
    Holder()
    {
      entries.reserve(kDefaultCommands.size());
      for (const auto &def : kDefaultCommands)
      {
        const MspMsg *msg = find_message_by_name(def.name);
        if (!msg)
        {
          continue;
        }
        RegistryEntry entry;
        entry.name = msg->name;
        entry.id = static_cast<uint16_t>(msg->id_hex & 0xFFFFu);
        entry.poll_rate_hz = def.rate_hz;
        entry.default_polled = def.default_polled;
        entry.response_schema = make_schema(*msg);
        entry.build_request_fn = [id = entry.id]() { return build_request(id); };
        entries.push_back(std::move(entry));
      }
    }
  };

  static const Holder holder;
  return {holder.entries.data(), holder.entries.size()};
}

bool schema_fixed_size_bytes(const MessageSchema &schema, std::size_t &out_bytes)
{
  if (!schema.has_fields())
  {
    return false;
  }
  std::size_t total = 0;
  for (std::size_t i = 0; i < schema.count; ++i)
  {
    const auto &field = schema.fields[i];
    TypeInfo info = parse_type(field.ctype);
    if (info.base == BaseType::kUnknown)
    {
      return false;
    }
    if (info.variable_length)
    {
      return false;
    }
    total += info.element_size * info.fixed_length;
  }
  out_bytes = total;
  return true;
}

bool parse_to_flat_list(const MessageSchema &schema, const std::vector<uint8_t> &payload,
                        std::vector<double> &out_values,
                        std::vector<std::string> *field_names,
                        std::string *error)
{
  if (!schema.has_fields())
  {
    if (error)
    {
      *error = "Schema has no fields";
    }
    return false;
  }

  out_values.clear();
  if (field_names)
  {
    field_names->clear();
  }

  std::size_t offset = 0;
  for (std::size_t i = 0; i < schema.count; ++i)
  {
    const auto &field = schema.fields[i];
    TypeInfo info = parse_type(field.ctype);
    if (info.base == BaseType::kUnknown)
    {
      if (error)
      {
        *error = std::string("Unsupported field type: ") + std::string(field.ctype);
      }
      return false;
    }
    std::size_t element_count = info.fixed_length;
    if (info.variable_length)
    {
      if (i + 1 < schema.count)
      {
        if (error)
        {
          *error = std::string("Variable-length field not terminal: ") + std::string(field.name);
        }
        return false;
      }
      if (info.element_size == 0)
      {
        if (error)
        {
          *error = std::string("Cannot determine size for field: ") + std::string(field.name);
        }
        return false;
      }
      if (offset > payload.size())
      {
        if (error)
        {
          *error = "Payload shorter than expected";
        }
        return false;
      }
      element_count = (payload.size() - offset) / info.element_size;
    }

    const std::size_t required_bytes = element_count * info.element_size;
    if (offset + required_bytes > payload.size())
    {
      if (error)
      {
        *error = std::string("Payload too short for field: ") + std::string(field.name);
      }
      return false;
    }

    const bool collect_values = info.base != BaseType::kSkip;
    for (std::size_t idx = 0; idx < element_count; ++idx)
    {
      if (collect_values)
      {
        const std::size_t elem_offset = offset + idx * info.element_size;
        out_values.push_back(load_value(payload, elem_offset, info.base));
        if (field_names)
        {
          if (element_count > 1)
          {
            field_names->emplace_back(std::string(field.name) + "[" + std::to_string(idx) + "]");
          }
          else
          {
            field_names->emplace_back(field.name);
          }
        }
      }
    }

    offset += required_bytes;
  }
  return true;
}

} // namespace transformer_msp_bridge::msp
