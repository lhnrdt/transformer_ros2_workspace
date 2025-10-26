#include <gtest/gtest.h>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <filesystem>
#include <optional>
#include "transformer_msp_bridge/msp_builders.hpp"
#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include "transformer_msp_bridge/serial_port.hpp"

using transformer_msp_bridge::MSPPacket;
using transformer_msp_bridge::MSPParser;
using transformer_msp_bridge::SerialPort;
namespace registry = transformer_msp_bridge::msp;

namespace
{
  std::string resolve_registry_json()
  {
    namespace fs = std::filesystem;
    if (const char *env = std::getenv("TRANSFORMER_MSP_REGISTRY_JSON"))
    {
      fs::path candidate(env);
      if (fs::exists(candidate))
        return candidate.string();
    }
    fs::path fallback = fs::path(__FILE__).parent_path().parent_path() / "config" / "msp_messages_inav.json";
    if (fs::exists(fallback))
      return fallback.string();
    return {};
  }

  class RegistryEnvironment : public ::testing::Environment
  {
  public:
    void SetUp() override
    {
      const std::string path = resolve_registry_json();
      if (path.empty())
      {
        FAIL() << "Unable to locate msp_messages_inav.json for tests";
        return;
      }
      if (setenv("TRANSFORMER_MSP_REGISTRY_JSON", path.c_str(), 1) != 0)
      {
        FAIL() << "Failed to set TRANSFORMER_MSP_REGISTRY_JSON";
      }
    }
  };

  ::testing::Environment *const registry_env = ::testing::AddGlobalTestEnvironment(new RegistryEnvironment());

  using Validator = std::function<std::string(const std::vector<double> &, const std::vector<std::string> &)>;

  std::string describe_value(const std::vector<double> &values, const std::vector<std::string> &names)
  {
    std::ostringstream oss;
    oss << "[";
    for (std::size_t i = 0; i < values.size(); ++i)
    {
      if (i)
        oss << ", ";
      if (i < names.size() && !names[i].empty())
        oss << names[i] << "=";
      oss << values[i];
    }
    oss << "]";
    return oss.str();
  }

  std::string payload_to_hex(const std::vector<uint8_t> &payload)
  {
    if (payload.empty())
      return "<empty>";
    std::ostringstream oss;
    oss << std::uppercase << std::hex << std::setfill('0');
    for (std::size_t i = 0; i < payload.size(); ++i)
    {
      if (i)
        oss << ' ';
      oss << std::setw(2) << static_cast<int>(payload[i]);
    }
    return oss.str();
  }

  std::string generic_checks(const std::vector<double> &values, const std::vector<std::string> &names)
  {
    constexpr double kDefaultAbsLimit = 1e6;
    for (std::size_t i = 0; i < values.size(); ++i)
    {
      const double v = values[i];
      if (!std::isfinite(v))
      {
        std::ostringstream oss;
        oss << "non-finite value at index " << i << " " << describe_value(values, names);
        return oss.str();
      }
      if (std::abs(v) > kDefaultAbsLimit)
      {
        std::ostringstream oss;
        oss << "value out of default range at index " << i << " (" << v << ") "
            << describe_value(values, names);
        return oss.str();
      }
    }
    return {};
  }

  uint16_t require_command_id(const char *name)
  {
  const uint16_t id = registry::command_id(name);
    if (id == 0u)
    {
      ADD_FAILURE() << "Unknown MSP command name: " << name;
    }
    return id;
  }

  std::unordered_map<uint16_t, Validator> build_validators()
  {
    std::unordered_map<uint16_t, Validator> validators;

    validators.emplace(require_command_id("MSP_ATTITUDE"), [](const std::vector<double> &values, const std::vector<std::string> &names)
                       {
      if (values.size() != 3)
        return std::string("expected 3 attitude fields, got ") + std::to_string(values.size());
      for (std::size_t i = 0; i < values.size(); ++i)
      {
        double v = values[i];
        if (!std::isfinite(v))
          return std::string("attitude value not finite: ") + describe_value(values, names);
        if (std::abs(v) > 720.0)
          return std::string("attitude value exceeds ±720 deg: ") + describe_value(values, names);
      }
      return std::string();
    });

    validators.emplace(require_command_id("MSP_RAW_IMU"), [](const std::vector<double> &values, const std::vector<std::string> &names)
                       {
      if (values.size() != 9)
        return std::string("expected 9 raw IMU fields, got ") + std::to_string(values.size());
      for (double v : values)
      {
        if (!std::isfinite(v))
          return std::string("raw IMU value not finite: ") + describe_value(values, names);
        if (std::abs(v) > 200000.0)
          return std::string("raw IMU value too large: ") + describe_value(values, names);
      }
      return std::string();
    });

    validators.emplace(require_command_id("MSP_ALTITUDE"), [](const std::vector<double> &values, const std::vector<std::string> &names)
                       {
      if (values.size() != 3)
        return std::string("expected 3 altitude fields, got ") + std::to_string(values.size());
      double alt_cm = values[0];
      double vario = values[1];
      double baro = values[2];
      if (!std::isfinite(alt_cm) || !std::isfinite(vario) || !std::isfinite(baro))
        return std::string("altitude value not finite: ") + describe_value(values, names);
      if (std::abs(alt_cm) > 500000.0 || std::abs(baro) > 500000.0)
        return std::string("altitude magnitude unrealistic: ") + describe_value(values, names);
      if (std::abs(vario) > 20000.0)
        return std::string("vertical speed unrealistic: ") + describe_value(values, names);
      return std::string();
    });

    validators.emplace(require_command_id("MSP_ANALOG"), [](const std::vector<double> &values, const std::vector<std::string> &names)
                       {
      if (values.size() < 4)
        return std::string("expected at least 4 analog fields, got ") + std::to_string(values.size());
      if (values[0] < 0.0 || values[0] > 255.0)
        return std::string("battery voltage raw out of range: ") + describe_value(values, names);
      if (values[1] < 0.0 || values[1] > 100000.0)
        return std::string("mAh value out of range: ") + describe_value(values, names);
      return std::string();
    });

    validators.emplace(require_command_id("MSP_RAW_GPS"), [](const std::vector<double> &values, const std::vector<std::string> &names)
                       {
      if (values.size() != 8)
        return std::string("expected 8 GPS fields, got ") + std::to_string(values.size());
      double num_sats = values[1];
      if (num_sats < 0.0 || num_sats > 50.0)
        return std::string("GPS sats out of range: ") + describe_value(values, names);
      double lat = values[2];
      double lon = values[3];
      if (std::abs(lat) > 900000000.0 || std::abs(lon) > 1800000000.0)
        return std::string("GPS lat/lon out of range: ") + describe_value(values, names);
      double hdop = values[7];
      if (hdop < 0.0 || hdop > 2000.0)
        return std::string("GPS hdop out of range: ") + describe_value(values, names);
      return std::string();
    });

    validators.emplace(require_command_id("MSP_RC"), [](const std::vector<double> &values, const std::vector<std::string> &names)
                       {
      for (double v : values)
      {
        if (v < 250.0 || v > 2250.0)
          return std::string("RC channel pulse out of 250-2250us range: ") + describe_value(values, names);
      }
      return std::string();
    });

    validators.emplace(require_command_id("MSP_COMP_GPS"), [](const std::vector<double> &values, const std::vector<std::string> &names)
                       {
      if (values.size() != 3)
        return std::string("expected 3 compensated GPS fields, got ") + std::to_string(values.size());
      for (std::size_t i = 0; i < 2 && i < values.size(); ++i)
      {
        double v = values[i];
        if (v < 0.0 || v > 65000.0)
          return std::string("ground speed/course out of range: ") + describe_value(values, names);
      }
      double heartbeat = values[2];
      if (heartbeat != 0.0 && heartbeat != 1.0)
        return std::string("gps heartbeat not boolean: ") + describe_value(values, names);
      return std::string();
    });

    validators.emplace(require_command_id("MSP_STATUS"), [](const std::vector<double> &values, const std::vector<std::string> &names)
                       {
      if (values.size() != 5)
        return std::string("expected 5 status fields, got ") + std::to_string(values.size());
      if (values[0] < 0.0 || values[0] > 0xFFFF)
        return std::string("status cycleTime out of range: ") + describe_value(values, names);
      if (values[4] > 255.0)
        return std::string("status profile out of range: ") + describe_value(values, names);
      return std::string();
    });

    validators.emplace(require_command_id("MSP_RTC"), [](const std::vector<double> &values, const std::vector<std::string> &names)
                       {
      if (values.size() != 2)
        return std::string("expected 2 RTC fields, got ") + std::to_string(values.size());
      double seconds = values[0];
      double millis = values[1];
      if (!std::isfinite(seconds) || !std::isfinite(millis))
        return std::string("RTC value not finite: ") + describe_value(values, names);
      if (seconds < 0.0 || seconds > 4.0e9)
        return std::string("RTC seconds out of range: ") + describe_value(values, names);
      if (millis < 0.0 || millis >= 1000.0)
        return std::string("RTC millis out of range: ") + describe_value(values, names);
      return std::string();
    });

    validators.emplace(require_command_id("MSP2_INAV_TEMPERATURES"), [](const std::vector<double> &values, const std::vector<std::string> &names)
                       {
      if (values.empty())
        return std::string("expected at least one temperature value, got 0");
      for (double v : values)
      {
        if (!std::isfinite(v))
          return std::string("temperature not finite: ") + describe_value(values, names);
        if (v != -1000.0 && (v < -400.0 || v > 400.0))
          return std::string("temperature out of plausible range: ") + describe_value(values, names);
      }
      return std::string();
    });

    validators.emplace(require_command_id("MSP2_INAV_ESC_RPM"), [](const std::vector<double> &values, const std::vector<std::string> &names)
                       {
      if (values.empty())
        return std::string("expected at least one ESC RPM value, got 0");
      for (double v : values)
      {
        if (v < 0.0 || v > 200000.0)
          return std::string("ESC RPM out of plausible range: ") + describe_value(values, names);
      }
      return std::string();
    });

    return validators;
  }

} // namespace

TEST(MspProbe, AllDefaultPolledRespondAndValidate)
{
  const char *port = std::getenv("MSP_TEST_PORT");
  const char *baud = std::getenv("MSP_TEST_BAUD");
  if (!port || !baud)
  {
    GTEST_SKIP() << "MSP_TEST_PORT/MSP_TEST_BAUD not set; skipping probe test";
  }
  int baud_i = std::atoi(baud);

  SerialPort sp;
  ASSERT_TRUE(sp.open(port, baud_i, 100)) << "Failed to open serial port";

  bool any_rx = false;
  std::optional<MSPPacket> last_pkt;
  MSPParser parser([&](const MSPPacket &pkt)
                   {
    any_rx = true;
    last_pkt = pkt; });

  auto view = registry::get_default_registry();
  size_t total = 0, ok = 0;
  std::set<uint16_t> missing_ids;
  std::map<uint16_t, std::string> validation_errors;
  std::map<uint16_t, std::string> last_value_strings;
  std::map<uint16_t, std::string> last_raw_payloads;
  const auto validators = build_validators();

  auto now = std::chrono::steady_clock::now;
  auto deadline_offset = std::chrono::duration<double>(5.0);

  for (size_t i = 0; i < view.size; ++i)
  {
    const auto &d = view.data[i];
    if (d.poll_rate_hz <= 0.0)
      continue; // only default-polled
    total++;
    any_rx = false;
    last_pkt.reset();
    auto frame = d.build_request_fn();
    ASSERT_TRUE(sp.writeAll(frame.data(), frame.size()));
    auto deadline = now() + deadline_offset;
    uint8_t buf[512];
    while (now() < deadline)
    {
      int n = sp.readSome(buf, sizeof(buf));
      if (n < 0)
        break;
      if (n > 0)
      {
        parser.feed(buf, static_cast<size_t>(n));
        if (any_rx)
          break;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    if (!any_rx)
    {
      missing_ids.insert(d.id);
      continue;
    }
    ok++;
    last_raw_payloads[d.id] = payload_to_hex(last_pkt->payload);

    const auto &schema = d.response_schema;
    if (schema.fields && schema.count > 0)
    {
      std::size_t expected_size = 0;
      if (registry::schema_fixed_size_bytes(schema, expected_size))
      {
        if (last_pkt->payload.size() != expected_size)
        {
          std::ostringstream oss;
          oss << "payload size " << last_pkt->payload.size()
              << " bytes but expected " << expected_size
              << " per schema";
          validation_errors[d.id] = oss.str();
          std::cout << "[MSP Probe] 0x" << std::hex << d.id << std::dec
                    << " payload length mismatch: expected " << expected_size
                    << ", got " << last_pkt->payload.size()
                    << " | raw=" << last_raw_payloads[d.id] << std::endl;
          continue;
        }
      }
    std::vector<double> values;
    std::vector<std::string> names;
    std::string err;
    if (!registry::parse_to_flat_list(schema, last_pkt->payload, values, &names, &err))
      {
        validation_errors[d.id] = std::string("parse failed: ") + err;
        std::cout << "[MSP Probe] 0x" << std::hex << d.id << std::dec
                  << " parse failed: " << err
                  << " | raw=" << last_raw_payloads[d.id] << std::endl;
        continue;
      }
      std::string msg;
      auto it = validators.find(d.id);
      if (it != validators.end())
      {
        msg = it->second(values, names);
      }
      else
      {
        msg = generic_checks(values, names);
      }
      if (!msg.empty())
      {
        validation_errors[d.id] = msg;
        std::cout << "[MSP Probe] 0x" << std::hex << d.id << std::dec
                  << " schema validation failed: " << msg
                  << " | raw=" << last_raw_payloads[d.id] << std::endl;
      }
      else
      {
        const std::string formatted = describe_value(values, names);
        last_value_strings[d.id] = formatted;
        std::cout << "[MSP Probe] 0x" << std::hex << d.id << std::dec
                  << " : " << formatted
                  << " | raw=" << last_raw_payloads[d.id] << std::endl;
      }
    }
    else
    {
      std::cout << "[MSP Probe] 0x" << std::hex << d.id << std::dec
                << " (no schema) raw=" << last_raw_payloads[d.id] << std::endl;
    }
  }

  auto snapshot_to_string = [&]() -> std::string {
    if (last_value_strings.empty())
      return {};
    std::ostringstream oss;
    oss << "Parsed telemetry snapshot (ID -> values):\n";
    for (const auto &entry : last_value_strings)
    {
      oss << "  0x" << std::hex << entry.first << std::dec << " : " << entry.second << "\n";
    }
    if (!last_raw_payloads.empty())
    {
      oss << "Raw payloads:\n";
      for (const auto &entry : last_raw_payloads)
      {
        oss << "  0x" << std::hex << entry.first << std::dec
            << " : " << entry.second << "\n";
      }
    }
    return oss.str();
  };

  const std::string snapshot_str = snapshot_to_string();

  if (!missing_ids.empty())
  {
    std::ostringstream msg;
    msg << "Probe summary: total=" << total << " ok=" << ok << " missing=" << missing_ids.size() << "\n";
    if (!missing_ids.empty())
    {
      msg << "Missing responses:";
      for (auto id : missing_ids)
        msg << " 0x" << std::hex << id;
      msg << "\n";
    }
    if (!snapshot_str.empty())
    {
      msg << snapshot_str;
    }
    FAIL() << msg.str();
  }

  if (!validation_errors.empty())
  {
    std::ostringstream msg;
    msg << "Validation errors for ";
    for (const auto &kv : validation_errors)
    {
      msg << "0x" << std::hex << kv.first << ": " << kv.second << "\n";
    }
    if (!snapshot_str.empty())
    {
      msg << snapshot_str;
    }
    FAIL() << msg.str();
  }
}
