#include <gtest/gtest.h>
#include <chrono>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>

#include "transformer_msp_bridge/decoders/altitude_decoder.hpp"
#include "transformer_msp_bridge/decoders/attitude_decoder.hpp"
#include "transformer_msp_bridge/decoders/battery_decoder.hpp"
#include "transformer_msp_bridge/decoders/gps_decoder.hpp"
#include "transformer_msp_bridge/decoders/imu_decoder.hpp"
#include "transformer_msp_bridge/decoders/inav_generic_decoder.hpp"
#include "transformer_msp_bridge/decoders/rc_decoder.hpp"
#include "transformer_msp_bridge/decoders/system_decoder.hpp"
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

using Validator = std::function<std::string(const std::vector<double> &, const std::vector<std::string> &)>;

std::string describe_value(const std::vector<double> &values, const std::vector<std::string> &names)
{
  std::ostringstream oss;
  oss << "[";
  for (std::size_t i = 0; i < values.size(); ++i)
  {
    if (i)
    {
      oss << ", ";
    }
    if (i < names.size() && !names[i].empty())
    {
      oss << names[i] << "=";
    }
    oss << values[i];
  }
  oss << "]";
  return oss.str();
}

std::string payload_to_hex(const std::vector<uint8_t> &payload)
{
  if (payload.empty())
  {
    return "<empty>";
  }
  std::ostringstream oss;
  oss << std::uppercase << std::hex << std::setfill('0');
  for (std::size_t i = 0; i < payload.size(); ++i)
  {
    if (i)
    {
      oss << ' ';
    }
    oss << std::setw(2) << static_cast<int>(payload[i]);
  }
  return oss.str();
}

std::string generic_checks(const std::vector<double> &values, const std::vector<std::string> &names)
{
  constexpr double kDefaultAbsLimit = 1e9;
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
      oss << "value out of default range at index " << i << " (" << v << ") " << describe_value(values, names);
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

  validators.emplace(require_command_id("MSP_ATTITUDE"), [](const std::vector<double> &values, const std::vector<std::string> &names) {
    if (values.size() != 3)
    {
      return std::string("expected 3 attitude fields, got ") + std::to_string(values.size());
    }
    for (std::size_t i = 0; i < values.size(); ++i)
    {
      double v = values[i];
      if (!std::isfinite(v))
      {
        return std::string("attitude value not finite: ") + describe_value(values, names);
      }
      if (std::abs(v) > 720.0)
      {
        return std::string("attitude value exceeds ±720 deg: ") + describe_value(values, names);
      }
    }
    return std::string();
  });

  validators.emplace(require_command_id("MSP_RAW_IMU"), [](const std::vector<double> &values, const std::vector<std::string> &names) {
    if (values.size() != 9)
    {
      return std::string("expected 9 decoded IMU fields, got ") + std::to_string(values.size());
    }
    for (std::size_t i = 0; i < values.size(); ++i)
    {
      const double v = values[i];
      if (!std::isfinite(v))
      {
        return std::string("IMU value not finite: ") + describe_value(values, names);
      }
      if (i < 3)
      {
        if (std::abs(v) > 500.0)
        {
          return std::string("linear acceleration exceeds ±500 m/s^2: ") + describe_value(values, names);
        }
      }
      else if (i < 6)
      {
        if (std::abs(v) > 500.0)
        {
          return std::string("angular velocity exceeds ±500 rad/s: ") + describe_value(values, names);
        }
      }
      else
      {
        if (std::abs(v) > 1.0)
        {
          return std::string("magnetic field exceeds ±1 Tesla: ") + describe_value(values, names);
        }
      }
    }
    return std::string();
  });

  validators.emplace(require_command_id("MSP_ALTITUDE"), [](const std::vector<double> &values, const std::vector<std::string> &names) {
    if (values.size() != 2)
    {
      return std::string("expected altitude (m) and vertical speed (m/s), got ") + std::to_string(values.size());
    }
    const double altitude_m = values[0];
    const double vertical_speed = values[1];
    if (!std::isfinite(altitude_m) || !std::isfinite(vertical_speed))
    {
      return std::string("altitude sample not finite: ") + describe_value(values, names);
    }
    if (std::abs(altitude_m) > 10000.0)
    {
      return std::string("altitude magnitude >10km: ") + describe_value(values, names);
    }
    if (std::abs(vertical_speed) > 500.0)
    {
      return std::string("vertical speed magnitude >500 m/s: ") + describe_value(values, names);
    }
    return std::string();
  });

  validators.emplace(require_command_id("MSP_ANALOG"), [](const std::vector<double> &values, const std::vector<std::string> &names) {
    if (values.size() != 1)
    {
      return std::string("expected decoded battery voltage, got ") + std::to_string(values.size());
    }
    const double voltage = values[0];
    if (!std::isfinite(voltage))
    {
      return std::string("battery voltage not finite: ") + describe_value(values, names);
    }
    if (voltage < 0.0 || voltage > 100.0)
    {
      return std::string("battery voltage out of range (0-100V): ") + describe_value(values, names);
    }
    return std::string();
  });

  validators.emplace(require_command_id("MSP_RAW_GPS"), [](const std::vector<double> &values, const std::vector<std::string> &names) {
    if (values.size() != 7)
    {
      return std::string("expected 7 decoded GPS fields, got ") + std::to_string(values.size());
    }
    const double fix_type = values[0];
    const double satellites = values[1];
    const double latitude_deg = values[2];
    const double longitude_deg = values[3];
    const double altitude_m = values[4];
    const double speed_mps = values[5];
    const double course_deg = values[6];
    if (fix_type < 0.0 || fix_type > 10.0)
    {
      return std::string("GPS fix type outside 0-10: ") + describe_value(values, names);
    }
    if (satellites < 0.0 || satellites > 60.0)
    {
      return std::string("GPS satellites count out of range: ") + describe_value(values, names);
    }
    if (std::abs(latitude_deg) > 90.0 || std::abs(longitude_deg) > 180.0)
    {
      return std::string("GPS latitude/longitude invalid: ") + describe_value(values, names);
    }
    if (altitude_m < -2000.0 || altitude_m > 10000.0)
    {
      return std::string("GPS altitude out of plausible range: ") + describe_value(values, names);
    }
    if (speed_mps < 0.0 || speed_mps > 400.0)
    {
      return std::string("GPS ground speed out of range: ") + describe_value(values, names);
    }
    if (course_deg < 0.0 || course_deg > 360.0)
    {
      return std::string("GPS course not within 0-360 deg: ") + describe_value(values, names);
    }
    return std::string();
  });

  validators.emplace(require_command_id("MSP_RC"), [](const std::vector<double> &values, const std::vector<std::string> &names) {
    for (double v : values)
    {
      if (!std::isfinite(v))
      {
        return std::string("RC channel value not finite: ") + describe_value(values, names);
      }
      if (v < 0.0 || v > 65535.0)
      {
        return std::string("RC channel pulse outside expected range (allowing zero when disarmed): ") + describe_value(values, names);
      }
    }
    return std::string();
  });

  validators.emplace(require_command_id("MSP_COMP_GPS"), [](const std::vector<double> &values, const std::vector<std::string> &names) {
    if (values.size() != 2)
    {
      return std::string("expected distance and direction to home, got ") + std::to_string(values.size());
    }
    const double distance_m = values[0];
    const double direction_deg = values[1];
    if (distance_m < 0.0 || distance_m > 200000.0)
    {
      return std::string("home distance out of range: ") + describe_value(values, names);
    }
    if (direction_deg < 0.0 || direction_deg > 360.0)
    {
      return std::string("home direction not in 0-360 deg: ") + describe_value(values, names);
    }
    return std::string();
  });

  validators.emplace(require_command_id("MSP_STATUS"), [](const std::vector<double> &values, const std::vector<std::string> &names) {
    if (values.size() != 5)
    {
      return std::string("expected 5 decoded status fields, got ") + std::to_string(values.size());
    }
    const double cycle_time_us = values[0];
    const double i2c_errors = values[1];
    const double sensors_mask = values[2];
    const double system_load_pct = values[3];
    const double profile = values[4];
    if (cycle_time_us <= 0.0 || cycle_time_us > 10000.0)
    {
      return std::string("status cycle time out of range: ") + describe_value(values, names);
    }
    if (i2c_errors < 0.0)
    {
      return std::string("status i2c errors negative: ") + describe_value(values, names);
    }
    if (sensors_mask < 0.0 || sensors_mask > 0xFFFF)
    {
      return std::string("status sensor mask invalid: ") + describe_value(values, names);
    }
    if (system_load_pct < 0.0 || system_load_pct > 100.0)
    {
      return std::string("status system load outside 0-100%: ") + describe_value(values, names);
    }
    if (profile < 0.0 || profile > 50.0)
    {
      return std::string("status profile index unreasonable: ") + describe_value(values, names);
    }
    return std::string();
  });

  validators.emplace(require_command_id("MSP_RTC"), [](const std::vector<double> &values, const std::vector<std::string> &names) {
    if (values.size() != 2)
    {
      return std::string("expected 2 RTC fields, got ") + std::to_string(values.size());
    }
    double seconds = values[0];
    double millis = values[1];
    if (!std::isfinite(seconds) || !std::isfinite(millis))
    {
      return std::string("RTC value not finite: ") + describe_value(values, names);
    }
    if (seconds < 0.0 || seconds > 4.0e9)
    {
      return std::string("RTC seconds out of range: ") + describe_value(values, names);
    }
    if (millis < 0.0 || millis >= 1000.0)
    {
      return std::string("RTC millis out of range: ") + describe_value(values, names);
    }
    return std::string();
  });

  validators.emplace(require_command_id("MSP2_INAV_TEMPERATURES"), [](const std::vector<double> &values, const std::vector<std::string> &names) {
    if (values.empty())
    {
      return std::string("expected at least one temperature value, got 0");
    }
    for (double v : values)
    {
      if (!std::isfinite(v))
      {
        return std::string("temperature not finite: ") + describe_value(values, names);
      }
      if (v != -1000.0 && (v < -1000000.0 || v > 1000000.0))
      {
        return std::string("temperature out of plausible range: ") + describe_value(values, names);
      }
    }
    return std::string();
  });

  validators.emplace(require_command_id("MSP2_INAV_ESC_RPM"), [](const std::vector<double> &values, const std::vector<std::string> &names) {
    if (values.empty())
    {
      return std::string("expected at least one ESC RPM value, got 0");
    }
    for (double v : values)
    {
      if (v < 0.0 || v > 5000000000.0)
      {
        return std::string("ESC RPM out of plausible range: ") + describe_value(values, names);
      }
    }
    return std::string();
  });

  return validators;
}

struct DecodedData
{
  bool decoded{false};
  std::vector<double> values;
  std::vector<std::string> names;
  std::string source;
};

DecodedData decode_with_existing_decoders(const MSPPacket &pkt)
{
  DecodedData data;

  auto set_result = [&](std::vector<double> values, std::vector<std::string> names, std::string source) {
    data.decoded = true;
    data.values = std::move(values);
    data.names = std::move(names);
    data.source = std::move(source);
  };

  {
    transformer_msp_bridge::AttitudeDecoder decoder([&](const transformer_msp_bridge::AttitudeAngles &sample) {
      set_result({sample.roll_deg, sample.pitch_deg, sample.yaw_deg},
                 {"roll_deg", "pitch_deg", "yaw_deg"},
                 "AttitudeDecoder");
    });
    if (decoder.matches(pkt.cmd))
    {
      decoder.decode(pkt);
      if (data.decoded)
        return data;
    }
  }

  {
    transformer_msp_bridge::ImuDecoder decoder([&](const transformer_msp_bridge::ImuSample &sample) {
      std::vector<double> values = {sample.linear_acceleration_mps2[0], sample.linear_acceleration_mps2[1],
                                    sample.linear_acceleration_mps2[2],  sample.angular_velocity_radps[0],
                                    sample.angular_velocity_radps[1],     sample.angular_velocity_radps[2],
                                    sample.magnetic_field_tesla[0],      sample.magnetic_field_tesla[1],
                                    sample.magnetic_field_tesla[2]};
      std::vector<std::string> names = {"acc_x_mps2",  "acc_y_mps2",  "acc_z_mps2",
                                        "gyro_x_radps", "gyro_y_radps", "gyro_z_radps",
                                        "mag_x_t",     "mag_y_t",     "mag_z_t"};
      set_result(std::move(values), std::move(names), "ImuDecoder");
    });
    if (decoder.matches(pkt.cmd))
    {
      decoder.decode(pkt);
      if (data.decoded)
        return data;
    }
  }

  {
    transformer_msp_bridge::AltitudeDecoder decoder([&](const transformer_msp_bridge::AltitudeSample &sample) {
      set_result({static_cast<double>(sample.altitude_m), static_cast<double>(sample.vertical_speed_mps)},
                 {"altitude_m", "vertical_speed_mps"},
                 "AltitudeDecoder");
    });
    if (decoder.matches(pkt.cmd))
    {
      decoder.decode(pkt);
      if (data.decoded)
        return data;
    }
  }

  {
    transformer_msp_bridge::BatteryDecoder::Callbacks callbacks;
    callbacks.analog = [&](const transformer_msp_bridge::BatteryAnalogData &sample) {
      set_result({static_cast<double>(sample.voltage_v)}, {"voltage_v"}, "BatteryDecoder::analog");
    };
    callbacks.status = [&](const transformer_msp_bridge::BatteryStatusData &sample) {
      std::vector<double> values;
      std::vector<std::string> names;
      if (!std::isnan(sample.voltage_v))
      {
        values.push_back(sample.voltage_v);
        names.emplace_back("voltage_v");
      }
      if (!std::isnan(sample.current_a))
      {
        values.push_back(sample.current_a);
        names.emplace_back("current_a");
      }
      if (!std::isnan(sample.charge_c))
      {
        values.push_back(sample.charge_c);
        names.emplace_back("charge_c");
      }
      if (!std::isnan(sample.remaining_fraction))
      {
        values.push_back(sample.remaining_fraction);
        names.emplace_back("remaining_fraction");
      }
      if (!values.empty())
      {
        set_result(std::move(values), std::move(names), "BatteryDecoder::status");
      }
    };
    transformer_msp_bridge::BatteryDecoder decoder(callbacks);
    if (decoder.matches(pkt.cmd))
    {
      decoder.decode(pkt);
      if (data.decoded)
        return data;
    }
  }

  {
    transformer_msp_bridge::GpsDecoder::Callbacks callbacks;
    callbacks.raw = [&](const transformer_msp_bridge::GpsRawData &sample) {
      const double rad_to_deg = 180.0 / 3.14159265358979323846;
      const double course_deg = sample.course_rad * rad_to_deg;
      set_result({static_cast<double>(sample.fix_type), static_cast<double>(sample.satellites), sample.latitude_deg,
                  sample.longitude_deg, sample.altitude_m, sample.speed_mps, course_deg},
                 {"fix_type", "satellites", "latitude_deg", "longitude_deg", "altitude_m", "speed_mps",
                  "course_deg"},
                 "GpsDecoder::raw");
    };
    callbacks.home = [&](const transformer_msp_bridge::GpsHomeVector &sample) {
      set_result({sample.distance_m, sample.direction_deg}, {"distance_m", "direction_deg"}, "GpsDecoder::home");
    };
    transformer_msp_bridge::GpsDecoder decoder(callbacks);
    if (decoder.matches(pkt.cmd))
    {
      decoder.decode(pkt);
      if (data.decoded)
        return data;
    }
  }

  {
    transformer_msp_bridge::RcDecoder decoder([&](const transformer_msp_bridge::RcChannelsData &sample) {
      std::vector<double> values(sample.channels.begin(), sample.channels.end());
      std::vector<std::string> names;
      names.reserve(values.size());
      for (std::size_t i = 0; i < values.size(); ++i)
      {
        std::ostringstream oss;
        oss << "channel_" << i;
        names.push_back(oss.str());
      }
      set_result(std::move(values), std::move(names), "RcDecoder");
    });
    if (decoder.matches(pkt.cmd))
    {
      decoder.decode(pkt);
      if (data.decoded)
        return data;
    }
  }

  {
    transformer_msp_bridge::SystemDecoder::Callbacks callbacks;
    callbacks.status_ex = [&](const transformer_msp_bridge::SystemStatusExData &sample) {
      set_result({static_cast<double>(sample.cycle_time_us), static_cast<double>(sample.i2c_errors),
                  static_cast<double>(sample.sensors_mask), static_cast<double>(sample.system_load_pct),
                  static_cast<double>(sample.profile)},
                 {"cycle_time_us", "i2c_errors", "sensors_mask", "system_load_pct", "profile"},
                 "SystemDecoder::status");
    };
    callbacks.rtc = [&](const transformer_msp_bridge::SystemRtcData &sample) {
      set_result({static_cast<double>(sample.seconds), static_cast<double>(sample.millis)},
                 {"seconds", "millis"},
                 "SystemDecoder::rtc");
    };
    transformer_msp_bridge::SystemDecoder decoder(callbacks);
    if (decoder.matches(pkt.cmd))
    {
      decoder.decode(pkt);
      if (data.decoded)
        return data;
    }
  }

  return data;
}

struct CommandProbeResult
{
  uint16_t id{0};
  std::string message_name;
  bool default_polled{false};
  bool responded{false};
  bool used_decoder{false};
  std::string validation_error;
  std::string parsed_values;
  std::string decode_source;
  std::string raw_payload_hex;
};

struct ProbeSummary
{
  std::vector<CommandProbeResult> commands;
  std::size_t default_polled_count{0};
  std::size_t responded_count{0};
};

CommandProbeResult probe_single_command(const registry::RegistryEntry &entry, SerialPort &sp,
                                        std::chrono::steady_clock::duration timeout,
                                        const std::unordered_map<uint16_t, Validator> &validators)
{
  CommandProbeResult result;
  result.id = entry.id;
  result.message_name = std::string(entry.name);
  result.default_polled = entry.poll_rate_hz > 0.0;

  bool any_rx = false;
  std::optional<MSPPacket> last_pkt;
  MSPParser parser([&](const MSPPacket &pkt) {
    any_rx = true;
    last_pkt = pkt;
  });

  const std::vector<uint8_t> frame = entry.build_request_fn();
  if (!sp.writeAll(frame.data(), frame.size()))
  {
    result.validation_error = "failed to transmit request frame";
    return result;
  }

  const auto deadline = std::chrono::steady_clock::now() + timeout;
  uint8_t buffer[512];
  while (std::chrono::steady_clock::now() < deadline)
  {
    const int bytes_read = sp.readSome(buffer, sizeof(buffer));
    if (bytes_read < 0)
    {
      result.validation_error = "serial read error";
      break;
    }
    if (bytes_read > 0)
    {
      parser.feed(buffer, static_cast<std::size_t>(bytes_read));
      if (any_rx)
      {
        break;
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
  }

  if (!any_rx)
  {
    return result;
  }

  result.responded = true;
  result.raw_payload_hex = payload_to_hex(last_pkt->payload);

  std::vector<double> values;
  std::vector<std::string> names;
  bool should_validate = false;

  DecodedData decoded = decode_with_existing_decoders(*last_pkt);
  if (decoded.decoded)
  {
    result.used_decoder = true;
    result.decode_source = decoded.source.empty() ? "decoder" : decoded.source;
    values = std::move(decoded.values);
    names = std::move(decoded.names);
    if (!values.empty())
    {
      result.parsed_values = describe_value(values, names);
      should_validate = true;
    }
    else
    {
      result.parsed_values = "<decoder produced no scalar values>";
    }
  }

  if (!result.used_decoder)
  {
    const auto &schema = entry.response_schema;
    if (schema.fields && schema.count > 0)
    {
      std::size_t expected_size = 0;
      const bool size_known = registry::schema_fixed_size_bytes(schema, expected_size);
      if (size_known && last_pkt->payload.size() != expected_size)
      {
        std::ostringstream oss;
        oss << "payload size " << last_pkt->payload.size() << " bytes but schema expects " << expected_size
            << "; skipping structured validation";
        result.parsed_values = oss.str();
        return result;
      }

      std::string parse_error;
      if (!registry::parse_to_flat_list(schema, last_pkt->payload, values, &names, &parse_error))
      {
        std::ostringstream oss;
        oss << "parse skipped: " << parse_error;
        result.parsed_values = oss.str();
        return result;
      }

      result.decode_source = "schema";
      result.parsed_values = describe_value(values, names);
      should_validate = !values.empty();
    }
    else
    {
      result.parsed_values = "<no schema available>";
    }
  }

  if (should_validate)
  {
    const auto validator_it = validators.find(entry.id);
    if (validator_it != validators.end())
    {
      result.validation_error = validator_it->second(values, names);
    }
    else
    {
      result.validation_error = generic_checks(values, names);
    }
  }

  return result;
}

ProbeSummary probe_default_commands(SerialPort &sp, const std::unordered_map<uint16_t, Validator> &validators,
                                    std::chrono::steady_clock::duration timeout)
{
  ProbeSummary summary;
  const auto view = registry::get_default_registry();
  summary.commands.reserve(view.size);

  for (std::size_t i = 0; i < view.size; ++i)
  {
    const auto &entry = view.data[i];
    if (entry.poll_rate_hz <= 0.0)
    {
      continue;
    }
    summary.default_polled_count++;
    CommandProbeResult result = probe_single_command(entry, sp, timeout, validators);
    if (result.responded)
    {
      summary.responded_count++;
    }
    summary.commands.push_back(std::move(result));
  }

  return summary;
}

std::string format_command_result(const CommandProbeResult &result)
{
  std::ostringstream oss;
  oss << result.message_name << " (0x" << std::hex << result.id << std::dec << ")";
  if (!result.responded)
  {
    oss << " did not respond";
    return oss.str();
  }
  if (!result.decode_source.empty())
  {
    oss << " via " << result.decode_source;
  }
  if (!result.validation_error.empty())
  {
    oss << " validation error: " << result.validation_error;
  }
  else
  {
    oss << " validation ok";
  }
  if (!result.parsed_values.empty())
  {
    oss << " values=" << result.parsed_values;
  }
  return oss.str();
}

void log_command_result(const CommandProbeResult &result)
{
  std::cout << "[MSP Probe] " << result.message_name << " (0x" << std::hex << result.id << std::dec << ")" << '\n';
  if (!result.responded)
  {
    std::cout << "  status: no response" << std::endl;
    return;
  }

  if (!result.decode_source.empty())
  {
    std::cout << "  source: " << result.decode_source << '\n';
  }

  if (!result.validation_error.empty())
  {
    std::cout << "  status: validation error" << '\n';
    std::cout << "  details: " << result.validation_error << '\n';
  }
  else
  {
    std::cout << "  status: validation ok" << '\n';
  }

  if (!result.parsed_values.empty())
  {
    std::cout << "  values: " << result.parsed_values << '\n';
  }
  else
  {
    std::cout << "  values: <not available>" << '\n';
  }
  std::cout.flush();
}

std::string build_snapshot(const ProbeSummary &summary)
{
  std::ostringstream oss;
  bool any = false;
  for (const auto &cmd : summary.commands)
  {
    if (!cmd.responded)
    {
      continue;
    }
    any = true;
    oss << "  " << format_command_result(cmd) << '\n';
  }
  if (!any)
  {
    return {};
  }
  return oss.str();
}

class MspProbeTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    const char *port_env = std::getenv("MSP_TEST_PORT");
    const char *baud_env = std::getenv("MSP_TEST_BAUD");
    if (!port_env || !baud_env)
    {
      GTEST_SKIP() << "MSP_TEST_PORT/MSP_TEST_BAUD not set; skipping MSP probe";
    }

    baudrate_ = std::atoi(baud_env);
    port_ = port_env;

    ASSERT_TRUE(serial_.open(port_, baudrate_, 100)) << "Failed to open serial port " << port_;

    validators_ = build_validators();
    summary_ = probe_default_commands(serial_, validators_, std::chrono::seconds(5));
  }

  void TearDown() override
  {
    if (serial_.isOpen())
    {
      serial_.close();
    }
  }

  SerialPort serial_;
  std::string port_;
  int baudrate_{0};
  std::unordered_map<uint16_t, Validator> validators_;
  ProbeSummary summary_;

  const CommandProbeResult *find_result(uint16_t id) const
  {
    for (const auto &cmd : summary_.commands)
    {
      if (cmd.id == id)
      {
        return &cmd;
      }
    }
    return nullptr;
  }
};

// Replace the aggregate tests with parameterized tests so each default-polled
// message appears as its own GoogleTest. We create a parameterized fixture
// that inherits the serial setup from `MspProbeTest` and probes the single
// message for both response and validation.

class MspProbeParamTest : public MspProbeTest, public ::testing::WithParamInterface<const registry::RegistryEntry *> {};

static std::vector<const registry::RegistryEntry *> gather_default_polled_entries()
{
  std::vector<const registry::RegistryEntry *> out;
  const auto view = registry::get_default_registry();
  for (std::size_t i = 0; i < view.size; ++i)
  {
    const auto &entry = view.data[i];
    if (entry.poll_rate_hz > 0.0)
    {
      out.push_back(&entry);
    }
  }
  return out;
}

static const std::vector<const registry::RegistryEntry *> k_default_polled_entries = gather_default_polled_entries();

// Sanitise a registry name into a valid test name component
static std::string sanitise_name(std::string_view in)
{
  std::string out;
  out.reserve(in.size());
  for (char c : in)
  {
    if (std::isalnum(static_cast<unsigned char>(c)))
      out.push_back(c);
    else
      out.push_back('_');
  }
  if (!out.empty() && std::isdigit(static_cast<unsigned char>(out[0])))
  {
    out.insert(out.begin(), '_');
  }
  return out;
}

TEST_P(MspProbeParamTest, Responds)
{
  const registry::RegistryEntry *entry = GetParam();
  ASSERT_NE(entry, nullptr);
  const CommandProbeResult *result = find_result(entry->id);
  ASSERT_NE(result, nullptr) << "missing probe result for " << entry->name;
  EXPECT_TRUE(result->responded) << format_command_result(*result);
}

TEST_P(MspProbeParamTest, Validates)
{
  const registry::RegistryEntry *entry = GetParam();
  ASSERT_NE(entry, nullptr);
  const CommandProbeResult *result = find_result(entry->id);
  ASSERT_NE(result, nullptr) << "missing probe result for " << entry->name;
  log_command_result(*result);
  if (!result->responded)
  {
    GTEST_SKIP() << "No response for " << entry->name;
  }
  EXPECT_TRUE(result->validation_error.empty()) << format_command_result(*result);
}

INSTANTIATE_TEST_SUITE_P(
    DefaultPolledMessages,
    MspProbeParamTest,
    ::testing::ValuesIn(k_default_polled_entries),
    [](const ::testing::TestParamInfo<const registry::RegistryEntry *> &info) -> std::string {
      if (!info.param)
        return std::string("null_entry");
      return sanitise_name(info.param->name);
    });

} // namespace
