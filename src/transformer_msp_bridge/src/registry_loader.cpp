#include "transformer_msp_bridge/registry_loader.hpp"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <optional>
#include <sstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include "ament_index_cpp/get_package_share_directory.hpp"
#include "msp/msp_protocol.h"
#include "msp/msp_protocol_v2_sensor.h"
#include "transformer_msp_bridge/msp_builders.hpp"

namespace transformer_msp_bridge
{

  namespace
  {
    using json = nlohmann::json;

    struct ParsedPrimitive
    {
      FieldType field_type;
      std::size_t element_size;
      std::size_t repeat;
    };

    std::string trim_copy(const std::string &input)
    {
      auto begin = input.begin();
      auto end = input.end();
      while (begin != end && std::isspace(static_cast<unsigned char>(*begin)))
        ++begin;
      while (end != begin && std::isspace(static_cast<unsigned char>(*(end - 1))))
        --end;
      return std::string(begin, end);
    }

    std::string strip_backticks(const std::string &input)
    {
      std::string out;
      out.reserve(input.size());
      for (char ch : input)
      {
        if (ch != '`')
          out.push_back(ch);
      }
      return trim_copy(out);
    }

    MessageDirection parse_direction_label(std::string label)
    {
      std::string lower;
      lower.reserve(label.size());
      for (char ch : label)
        lower.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));

      if (lower == "out" || lower == "outbound")
        return MessageDirection::Outbound;
      if (lower == "in" || lower == "inbound")
        return MessageDirection::Inbound;
      if (lower == "both" || lower == "bidirectional" || lower == "in/out")
        return MessageDirection::Bidirectional;
      if (lower.find("indicator") != std::string::npos)
        return MessageDirection::Indicator;
      return MessageDirection::Unknown;
    }

    bool parse_unsigned(const std::string &text, unsigned long &value)
    {
      const std::string trimmed = trim_copy(text);
      if (trimmed.empty())
        return false;
      char *end_ptr = nullptr;
      int base = 10;
      if (trimmed.size() > 2 && trimmed[0] == '0' && (trimmed[1] == 'x' || trimmed[1] == 'X'))
        base = 16;
      value = std::strtoul(trimmed.c_str(), &end_ptr, base);
      return end_ptr && *end_ptr == '\0';
    }

    uint16_t parse_message_id(const json &node)
    {
      if (node.is_number_unsigned())
      {
        const auto v = node.get<uint64_t>();
        if (v > 0xFFFFULL)
          throw std::runtime_error("MSP id exceeds 16-bit range");
        return static_cast<uint16_t>(v);
      }
      if (node.is_number_integer())
      {
        const auto v = node.get<int64_t>();
        if (v < 0 || v > 0xFFFFLL)
          throw std::runtime_error("MSP id out of range");
        return static_cast<uint16_t>(v);
      }
      if (node.is_string())
      {
        unsigned long parsed = 0;
        const std::string text = node.get<std::string>();
        if (!parse_unsigned(text, parsed) || parsed > 0xFFFFUL)
          throw std::runtime_error("Unable to parse MSP id: " + text);
        return static_cast<uint16_t>(parsed);
      }
      throw std::runtime_error("MSP id must be numeric or string");
    }

    std::optional<std::size_t> parse_repeated_count(const std::string &raw)
    {
      const auto open = raw.find('[');
      if (open == std::string::npos)
        return std::nullopt;
      const auto close = raw.find(']', open);
      if (close == std::string::npos)
        return std::nullopt;
      std::string inside = raw.substr(open + 1, close - open - 1);
      unsigned long parsed = 0;
      if (!parse_unsigned(inside, parsed))
        return std::nullopt;
      return static_cast<std::size_t>(parsed);
    }

    std::optional<ParsedPrimitive> parse_primitive_ctype(const std::string &raw_ctype)
    {
      if (raw_ctype.empty())
        return std::nullopt;

      std::string cleaned;
      cleaned.reserve(raw_ctype.size());
      for (char ch : raw_ctype)
      {
        if (!std::isspace(static_cast<unsigned char>(ch)))
          cleaned.push_back(ch);
      }

      const auto repeat = parse_repeated_count(cleaned);
      std::size_t multiplicity = 1;
      if (repeat.has_value())
      {
        multiplicity = *repeat;
        const auto bracket = cleaned.find('[');
        cleaned.erase(bracket, cleaned.size() - bracket);
      }

      std::string lower;
      lower.reserve(cleaned.size());
      for (char ch : cleaned)
        lower.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));

      ParsedPrimitive parsed{};
      parsed.repeat = multiplicity;

      if (lower == "uint8_t" || lower == "uint8" || lower == "u8" || lower == "char")
      {
        parsed.field_type = FieldType::U8;
        parsed.element_size = 1;
        return parsed;
      }
      if (lower == "int8_t" || lower == "int8" || lower == "i8")
      {
        parsed.field_type = FieldType::I8;
        parsed.element_size = 1;
        return parsed;
      }
      if (lower == "uint16_t" || lower == "uint16" || lower == "u16")
      {
        parsed.field_type = FieldType::U16;
        parsed.element_size = 2;
        return parsed;
      }
      if (lower == "int16_t" || lower == "int16" || lower == "i16")
      {
        parsed.field_type = FieldType::I16;
        parsed.element_size = 2;
        return parsed;
      }
      if (lower == "uint32_t" || lower == "uint32" || lower == "u32")
      {
        parsed.field_type = FieldType::U32;
        parsed.element_size = 4;
        return parsed;
      }
      if (lower == "int32_t" || lower == "int32" || lower == "i32")
      {
        parsed.field_type = FieldType::I32;
        parsed.element_size = 4;
        return parsed;
      }
      if (lower == "float" || lower == "float32" || lower == "float32_t")
      {
        parsed.field_type = FieldType::F32;
        parsed.element_size = 4;
        return parsed;
      }
      return std::nullopt;
    }

    std::optional<std::size_t> parse_declared_size(const std::string &raw_size)
    {
      if (raw_size.empty())
        return std::nullopt;
      unsigned long parsed = 0;
      if (!parse_unsigned(raw_size, parsed))
        return std::nullopt;
      return static_cast<std::size_t>(parsed);
    }

    RuntimeRegistry::OwnedSchema build_schema_from_definition(const MessageDefinition &def)
    {
      RuntimeRegistry::OwnedSchema schema;
      const std::size_t count = def.fields.size();
      schema.count = count;
      schema.fields = std::make_unique<FieldSpec[]>(count);
      schema.names = std::make_unique<std::string[]>(count);
      schema.units = std::make_unique<std::string[]>(count);

      for (std::size_t i = 0; i < count; ++i)
      {
        const auto &field = def.fields[i];
        const auto primitive = parse_primitive_ctype(field.ctype);
        if (!primitive.has_value() || primitive->repeat == 0)
          throw std::runtime_error("Unsupported field type for schema: " + field.ctype);

        if (const auto declared_size = parse_declared_size(field.size))
        {
          const std::size_t expected = primitive->element_size * primitive->repeat;
          if (*declared_size != expected)
          {
            std::ostringstream oss;
            oss << "Declared size mismatch for field '" << field.name << "' (expected " << expected
                << ", got " << *declared_size << ")";
            throw std::runtime_error(oss.str());
          }
        }

        schema.names[i] = field.name;
        schema.units[i] = field.units;

        FieldSpec spec{};
        spec.name = schema.names[i].c_str();
        spec.type = primitive->field_type;
        spec.unit = schema.units[i].empty() ? nullptr : schema.units[i].c_str();
        spec.scale = 1.0;
        spec.repeat = primitive->repeat;
        schema.fields[i] = spec;
      }

      return schema;
    }

    using BuildArgFn = std::function<std::vector<uint8_t>(uint16_t)>;

    BuildArgFn builder_for_id(uint16_t id)
    {
      if (id <= 255)
      {
        return [](uint16_t cmd)
        {
          return buildPacketRaw(static_cast<uint8_t>(cmd), {});
        };
      }
      return [](uint16_t cmd)
      {
        return buildPacketV2(cmd, {}, 0);
      };
    }

    struct DefaultCommand
    {
      const char *name;
      double poll_rate_hz;
    };

    constexpr DefaultCommand kDefaultCommands[] = {
        {"MSP_RAW_IMU", 50.0},
        {"MSP_SERVO", 10.0},
        {"MSP_MOTOR", 10.0},
        {"MSP_RC", 5.0},
        {"MSP_RAW_GPS", 5.0},
        {"MSP_COMP_GPS", 2.0},
        {"MSP_ATTITUDE", 10.0},
        {"MSP_ALTITUDE", 5.0},
        {"MSP_ANALOG", 2.0},
        {"MSP_RC_TUNING", 0.2},
        {"MSP_BATTERY_STATE", 1.0},
        {"MSP_RTC", 0.5},
        {"MSP_STATUS", 2.0},
        {"MSP_SENSOR_CONFIG", 2.0},
        {"MSP_GPSSTATISTICS", 1.0},
        {"MSP2_SENSOR_RANGEFINDER", 5.0},
        {"MSP2_SENSOR_COMPASS", 5.0},
        {"MSP2_SENSOR_BAROMETER", 5.0},
        {"MSP2_INAV_STATUS", 2.0},
        {"MSP2_INAV_ANALOG", 2.0},
        {"MSP2_INAV_BATTERY_CONFIG", 0.05},
        {"MSP2_INAV_AIR_SPEED", 5.0},
        {"MSP2_INAV_TEMPERATURES", 1.0},
        {"MSP2_INAV_ESC_RPM", 5.0},
        {"MSP2_COMMON_SETTING", 0.0},
        {"MSP2_COMMON_SET_SETTING", 0.0},
    };

    const MessageDefinition *find_message_by_name(const std::vector<MessageDefinition> &defs, const std::string &name)
    {
      for (const auto &def : defs)
        if (def.name == name)
          return &def;
      return nullptr;
    }

  } // namespace

  RuntimeRegistry RuntimeRegistry::from_json_file(const std::string &json_path)
  {
    RuntimeRegistry rr;

    std::ifstream stream(json_path);
    if (!stream)
      throw std::runtime_error("Failed to open registry JSON: " + json_path);

    json root;
    try
    {
      stream >> root;
    }
    catch (const json::parse_error &e)
    {
      throw std::runtime_error(std::string("Failed to parse registry JSON: ") + e.what());
    }

    if (!root.is_array())
      throw std::runtime_error("Registry JSON root must be an array");

    rr.definitions_.reserve(root.size());
    for (const auto &entry : root)
    {
      if (!entry.is_object())
        throw std::runtime_error("Registry entry must be an object");

      MessageDefinition def;
      def.id = parse_message_id(entry.at("id"));
      def.name = trim_copy(entry.value("name", std::string{}));
      if (def.name.empty())
        throw std::runtime_error("Registry entry missing name");

      def.id_hex = trim_copy(entry.value("id_hex", std::string{}));
      def.description = trim_copy(entry.value("description", std::string{}));
      def.direction_label = trim_copy(entry.value("direction", std::string{}));
      def.direction = parse_direction_label(def.direction_label);
      def.has_variable_length = entry.value("has_variable_length", false);

      if (entry.contains("fields") && entry["fields"].is_array())
      {
        const auto &fields = entry["fields"];
        def.fields.reserve(fields.size());
        for (const auto &field_node : fields)
        {
          if (!field_node.is_object())
            throw std::runtime_error("Field entry must be an object");
          MessageField field;
          field.name = strip_backticks(field_node.value("name", std::string{}));
          field.ctype = strip_backticks(field_node.value("ctype", std::string{}));
          field.size = strip_backticks(field_node.value("size", std::string{}));
          field.units = strip_backticks(field_node.value("units", std::string{}));
          field.description = trim_copy(field_node.value("description", std::string{}));
          def.fields.push_back(std::move(field));
        }
      }

      rr.definitions_.push_back(std::move(def));
    }

    rr.owned_names_.reserve(std::size(kDefaultCommands));
    rr.descriptors_.reserve(std::size(kDefaultCommands));

    for (const auto &command : kDefaultCommands)
    {
      const MessageDefinition *def = find_message_by_name(rr.definitions_, command.name);
      if (!def)
      {
        throw std::runtime_error(std::string("Registry JSON missing definition for ") + command.name);
      }

      CommandDescriptor descriptor{};
      descriptor.id = def->id;
      rr.owned_names_.push_back(def->name);
      descriptor.name = rr.owned_names_.back().c_str();
      descriptor.poll_rate_hz = command.poll_rate_hz;
      const auto builder = builder_for_id(descriptor.id);
      descriptor.build_request_fn = [builder, id = descriptor.id]()
      {
        return builder(id);
      };

      bool schema_assigned = false;
      if (!def->has_variable_length && !def->fields.empty())
      {
        try
        {
          RuntimeRegistry::OwnedSchema schema = build_schema_from_definition(*def);
          rr.owned_schemas_.push_back(std::move(schema));
          const auto &stored = rr.owned_schemas_.back();
          descriptor.response_schema = stored.fields.get();
          descriptor.response_schema_count = stored.count;
          schema_assigned = true;
        }
        catch (const std::exception &)
        {
          // Leave schema unset if parsing fails; decoder may still handle payload manually.
        }
      }

      if (!schema_assigned)
      {
        descriptor.response_schema = nullptr;
        descriptor.response_schema_count = 0;
      }

      rr.descriptors_.push_back(std::move(descriptor));
    }

    return rr;
  }

  const MessageDefinition *RuntimeRegistry::find_definition(uint16_t id) const
  {
    for (const auto &def : definitions_)
      if (def.id == id)
        return &def;
    return nullptr;
  }

  std::string resolve_default_registry_json_path()
  {
    if (const char *env = std::getenv("TRANSFORMER_MSP_REGISTRY_JSON"))
      return std::string(env);
    try
    {
      const auto share = ament_index_cpp::get_package_share_directory("transformer_msp_bridge");
      return share + "/config/msp_messages_inav.json";
    }
    catch (const std::exception &)
    {
      return std::string();
    }
  }

} // namespace transformer_msp_bridge
