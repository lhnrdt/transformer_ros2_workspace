// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from transformer_msp_bridge:msg/MspInavStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "transformer_msp_bridge/msg/msp_inav_status.hpp"


#ifndef TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__TRAITS_HPP_
#define TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "transformer_msp_bridge/msg/detail/msp_inav_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace transformer_msp_bridge
{

namespace msg
{

inline void to_flow_style_yaml(
  const MspInavStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: cycle_time_us
  {
    out << "cycle_time_us: ";
    rosidl_generator_traits::value_to_yaml(msg.cycle_time_us, out);
    out << ", ";
  }

  // member: i2c_errors
  {
    out << "i2c_errors: ";
    rosidl_generator_traits::value_to_yaml(msg.i2c_errors, out);
    out << ", ";
  }

  // member: sensor_status
  {
    out << "sensor_status: ";
    rosidl_generator_traits::value_to_yaml(msg.sensor_status, out);
    out << ", ";
  }

  // member: cpu_load_percent
  {
    out << "cpu_load_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.cpu_load_percent, out);
    out << ", ";
  }

  // member: config_profile
  {
    out << "config_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.config_profile, out);
    out << ", ";
  }

  // member: battery_profile
  {
    out << "battery_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_profile, out);
    out << ", ";
  }

  // member: mixer_profile
  {
    out << "mixer_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.mixer_profile, out);
    out << ", ";
  }

  // member: arming_flags
  {
    out << "arming_flags: ";
    rosidl_generator_traits::value_to_yaml(msg.arming_flags, out);
    out << ", ";
  }

  // member: active_modes
  {
    if (msg.active_modes.size() == 0) {
      out << "active_modes: []";
    } else {
      out << "active_modes: [";
      size_t pending_items = msg.active_modes.size();
      for (auto item : msg.active_modes) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MspInavStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: cycle_time_us
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cycle_time_us: ";
    rosidl_generator_traits::value_to_yaml(msg.cycle_time_us, out);
    out << "\n";
  }

  // member: i2c_errors
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "i2c_errors: ";
    rosidl_generator_traits::value_to_yaml(msg.i2c_errors, out);
    out << "\n";
  }

  // member: sensor_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sensor_status: ";
    rosidl_generator_traits::value_to_yaml(msg.sensor_status, out);
    out << "\n";
  }

  // member: cpu_load_percent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cpu_load_percent: ";
    rosidl_generator_traits::value_to_yaml(msg.cpu_load_percent, out);
    out << "\n";
  }

  // member: config_profile
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "config_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.config_profile, out);
    out << "\n";
  }

  // member: battery_profile
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_profile, out);
    out << "\n";
  }

  // member: mixer_profile
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mixer_profile: ";
    rosidl_generator_traits::value_to_yaml(msg.mixer_profile, out);
    out << "\n";
  }

  // member: arming_flags
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "arming_flags: ";
    rosidl_generator_traits::value_to_yaml(msg.arming_flags, out);
    out << "\n";
  }

  // member: active_modes
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.active_modes.size() == 0) {
      out << "active_modes: []\n";
    } else {
      out << "active_modes:\n";
      for (auto item : msg.active_modes) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MspInavStatus & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace transformer_msp_bridge

namespace rosidl_generator_traits
{

[[deprecated("use transformer_msp_bridge::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_msp_bridge::msg::MspInavStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_msp_bridge::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_msp_bridge::msg::to_yaml() instead")]]
inline std::string to_yaml(const transformer_msp_bridge::msg::MspInavStatus & msg)
{
  return transformer_msp_bridge::msg::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_msp_bridge::msg::MspInavStatus>()
{
  return "transformer_msp_bridge::msg::MspInavStatus";
}

template<>
inline const char * name<transformer_msp_bridge::msg::MspInavStatus>()
{
  return "transformer_msp_bridge/msg/MspInavStatus";
}

template<>
struct has_fixed_size<transformer_msp_bridge::msg::MspInavStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<transformer_msp_bridge::msg::MspInavStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<transformer_msp_bridge::msg::MspInavStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__TRAITS_HPP_
