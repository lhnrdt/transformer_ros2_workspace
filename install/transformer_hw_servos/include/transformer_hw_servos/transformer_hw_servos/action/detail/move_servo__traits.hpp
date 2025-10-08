// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from transformer_hw_servos:action/MoveServo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "transformer_hw_servos/action/move_servo.hpp"


#ifndef TRANSFORMER_HW_SERVOS__ACTION__DETAIL__MOVE_SERVO__TRAITS_HPP_
#define TRANSFORMER_HW_SERVOS__ACTION__DETAIL__MOVE_SERVO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "transformer_hw_servos/action/detail/move_servo__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace transformer_hw_servos
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveServo_Goal & msg,
  std::ostream & out)
{
  out << "{";
  // member: channels
  {
    if (msg.channels.size() == 0) {
      out << "channels: []";
    } else {
      out << "channels: [";
      size_t pending_items = msg.channels.size();
      for (auto item : msg.channels) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: pulse_us
  {
    out << "pulse_us: ";
    rosidl_generator_traits::value_to_yaml(msg.pulse_us, out);
    out << ", ";
  }

  // member: speed_us_per_s
  {
    out << "speed_us_per_s: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_us_per_s, out);
    out << ", ";
  }

  // member: use_trapezoid
  {
    out << "use_trapezoid: ";
    rosidl_generator_traits::value_to_yaml(msg.use_trapezoid, out);
    out << ", ";
  }

  // member: accel_us_per_s2
  {
    out << "accel_us_per_s2: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_us_per_s2, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveServo_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: channels
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.channels.size() == 0) {
      out << "channels: []\n";
    } else {
      out << "channels:\n";
      for (auto item : msg.channels) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: pulse_us
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pulse_us: ";
    rosidl_generator_traits::value_to_yaml(msg.pulse_us, out);
    out << "\n";
  }

  // member: speed_us_per_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed_us_per_s: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_us_per_s, out);
    out << "\n";
  }

  // member: use_trapezoid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "use_trapezoid: ";
    rosidl_generator_traits::value_to_yaml(msg.use_trapezoid, out);
    out << "\n";
  }

  // member: accel_us_per_s2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accel_us_per_s2: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_us_per_s2, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveServo_Goal & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_servos::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_servos::action::MoveServo_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_servos::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_servos::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_servos::action::MoveServo_Goal & msg)
{
  return transformer_hw_servos::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_servos::action::MoveServo_Goal>()
{
  return "transformer_hw_servos::action::MoveServo_Goal";
}

template<>
inline const char * name<transformer_hw_servos::action::MoveServo_Goal>()
{
  return "transformer_hw_servos/action/MoveServo_Goal";
}

template<>
struct has_fixed_size<transformer_hw_servos::action::MoveServo_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<transformer_hw_servos::action::MoveServo_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<transformer_hw_servos::action::MoveServo_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace transformer_hw_servos
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveServo_Result & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << ", ";
  }

  // member: final_pulses_us
  {
    if (msg.final_pulses_us.size() == 0) {
      out << "final_pulses_us: []";
    } else {
      out << "final_pulses_us: [";
      size_t pending_items = msg.final_pulses_us.size();
      for (auto item : msg.final_pulses_us) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: total_estimated_duration_s
  {
    out << "total_estimated_duration_s: ";
    rosidl_generator_traits::value_to_yaml(msg.total_estimated_duration_s, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveServo_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }

  // member: final_pulses_us
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.final_pulses_us.size() == 0) {
      out << "final_pulses_us: []\n";
    } else {
      out << "final_pulses_us:\n";
      for (auto item : msg.final_pulses_us) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: total_estimated_duration_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_estimated_duration_s: ";
    rosidl_generator_traits::value_to_yaml(msg.total_estimated_duration_s, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveServo_Result & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_servos::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_servos::action::MoveServo_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_servos::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_servos::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_servos::action::MoveServo_Result & msg)
{
  return transformer_hw_servos::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_servos::action::MoveServo_Result>()
{
  return "transformer_hw_servos::action::MoveServo_Result";
}

template<>
inline const char * name<transformer_hw_servos::action::MoveServo_Result>()
{
  return "transformer_hw_servos/action/MoveServo_Result";
}

template<>
struct has_fixed_size<transformer_hw_servos::action::MoveServo_Result>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<transformer_hw_servos::action::MoveServo_Result>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<transformer_hw_servos::action::MoveServo_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace transformer_hw_servos
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveServo_Feedback & msg,
  std::ostream & out)
{
  out << "{";
  // member: current_pulses_us
  {
    if (msg.current_pulses_us.size() == 0) {
      out << "current_pulses_us: []";
    } else {
      out << "current_pulses_us: [";
      size_t pending_items = msg.current_pulses_us.size();
      for (auto item : msg.current_pulses_us) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: progress
  {
    out << "progress: ";
    rosidl_generator_traits::value_to_yaml(msg.progress, out);
    out << ", ";
  }

  // member: estimated_remaining_s
  {
    out << "estimated_remaining_s: ";
    rosidl_generator_traits::value_to_yaml(msg.estimated_remaining_s, out);
    out << ", ";
  }

  // member: phase
  {
    out << "phase: ";
    rosidl_generator_traits::value_to_yaml(msg.phase, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveServo_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: current_pulses_us
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.current_pulses_us.size() == 0) {
      out << "current_pulses_us: []\n";
    } else {
      out << "current_pulses_us:\n";
      for (auto item : msg.current_pulses_us) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: progress
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "progress: ";
    rosidl_generator_traits::value_to_yaml(msg.progress, out);
    out << "\n";
  }

  // member: estimated_remaining_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "estimated_remaining_s: ";
    rosidl_generator_traits::value_to_yaml(msg.estimated_remaining_s, out);
    out << "\n";
  }

  // member: phase
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "phase: ";
    rosidl_generator_traits::value_to_yaml(msg.phase, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveServo_Feedback & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_servos::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_servos::action::MoveServo_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_servos::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_servos::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_servos::action::MoveServo_Feedback & msg)
{
  return transformer_hw_servos::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_servos::action::MoveServo_Feedback>()
{
  return "transformer_hw_servos::action::MoveServo_Feedback";
}

template<>
inline const char * name<transformer_hw_servos::action::MoveServo_Feedback>()
{
  return "transformer_hw_servos/action/MoveServo_Feedback";
}

template<>
struct has_fixed_size<transformer_hw_servos::action::MoveServo_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<transformer_hw_servos::action::MoveServo_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<transformer_hw_servos::action::MoveServo_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "transformer_hw_servos/action/detail/move_servo__traits.hpp"

namespace transformer_hw_servos
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveServo_SendGoal_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: goal
  {
    out << "goal: ";
    to_flow_style_yaml(msg.goal, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveServo_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: goal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal:\n";
    to_block_style_yaml(msg.goal, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveServo_SendGoal_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_servos::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_servos::action::MoveServo_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_servos::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_servos::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_servos::action::MoveServo_SendGoal_Request & msg)
{
  return transformer_hw_servos::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_servos::action::MoveServo_SendGoal_Request>()
{
  return "transformer_hw_servos::action::MoveServo_SendGoal_Request";
}

template<>
inline const char * name<transformer_hw_servos::action::MoveServo_SendGoal_Request>()
{
  return "transformer_hw_servos/action/MoveServo_SendGoal_Request";
}

template<>
struct has_fixed_size<transformer_hw_servos::action::MoveServo_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<transformer_hw_servos::action::MoveServo_Goal>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<transformer_hw_servos::action::MoveServo_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<transformer_hw_servos::action::MoveServo_Goal>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<transformer_hw_servos::action::MoveServo_SendGoal_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace transformer_hw_servos
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveServo_SendGoal_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: accepted
  {
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << ", ";
  }

  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveServo_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: accepted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << "\n";
  }

  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveServo_SendGoal_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_servos::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_servos::action::MoveServo_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_servos::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_servos::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_servos::action::MoveServo_SendGoal_Response & msg)
{
  return transformer_hw_servos::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_servos::action::MoveServo_SendGoal_Response>()
{
  return "transformer_hw_servos::action::MoveServo_SendGoal_Response";
}

template<>
inline const char * name<transformer_hw_servos::action::MoveServo_SendGoal_Response>()
{
  return "transformer_hw_servos/action/MoveServo_SendGoal_Response";
}

template<>
struct has_fixed_size<transformer_hw_servos::action::MoveServo_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<transformer_hw_servos::action::MoveServo_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<transformer_hw_servos::action::MoveServo_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace transformer_hw_servos
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveServo_SendGoal_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
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
  const MoveServo_SendGoal_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveServo_SendGoal_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_servos::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_servos::action::MoveServo_SendGoal_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_servos::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_servos::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_servos::action::MoveServo_SendGoal_Event & msg)
{
  return transformer_hw_servos::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_servos::action::MoveServo_SendGoal_Event>()
{
  return "transformer_hw_servos::action::MoveServo_SendGoal_Event";
}

template<>
inline const char * name<transformer_hw_servos::action::MoveServo_SendGoal_Event>()
{
  return "transformer_hw_servos/action/MoveServo_SendGoal_Event";
}

template<>
struct has_fixed_size<transformer_hw_servos::action::MoveServo_SendGoal_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<transformer_hw_servos::action::MoveServo_SendGoal_Event>
  : std::integral_constant<bool, has_bounded_size<service_msgs::msg::ServiceEventInfo>::value && has_bounded_size<transformer_hw_servos::action::MoveServo_SendGoal_Request>::value && has_bounded_size<transformer_hw_servos::action::MoveServo_SendGoal_Response>::value> {};

template<>
struct is_message<transformer_hw_servos::action::MoveServo_SendGoal_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<transformer_hw_servos::action::MoveServo_SendGoal>()
{
  return "transformer_hw_servos::action::MoveServo_SendGoal";
}

template<>
inline const char * name<transformer_hw_servos::action::MoveServo_SendGoal>()
{
  return "transformer_hw_servos/action/MoveServo_SendGoal";
}

template<>
struct has_fixed_size<transformer_hw_servos::action::MoveServo_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<transformer_hw_servos::action::MoveServo_SendGoal_Request>::value &&
    has_fixed_size<transformer_hw_servos::action::MoveServo_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<transformer_hw_servos::action::MoveServo_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<transformer_hw_servos::action::MoveServo_SendGoal_Request>::value &&
    has_bounded_size<transformer_hw_servos::action::MoveServo_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<transformer_hw_servos::action::MoveServo_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<transformer_hw_servos::action::MoveServo_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<transformer_hw_servos::action::MoveServo_SendGoal_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"

namespace transformer_hw_servos
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveServo_GetResult_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveServo_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveServo_GetResult_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_servos::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_servos::action::MoveServo_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_servos::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_servos::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_servos::action::MoveServo_GetResult_Request & msg)
{
  return transformer_hw_servos::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_servos::action::MoveServo_GetResult_Request>()
{
  return "transformer_hw_servos::action::MoveServo_GetResult_Request";
}

template<>
inline const char * name<transformer_hw_servos::action::MoveServo_GetResult_Request>()
{
  return "transformer_hw_servos/action/MoveServo_GetResult_Request";
}

template<>
struct has_fixed_size<transformer_hw_servos::action::MoveServo_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<transformer_hw_servos::action::MoveServo_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<transformer_hw_servos::action::MoveServo_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__traits.hpp"

namespace transformer_hw_servos
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveServo_GetResult_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: status
  {
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << ", ";
  }

  // member: result
  {
    out << "result: ";
    to_flow_style_yaml(msg.result, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveServo_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << "\n";
  }

  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result:\n";
    to_block_style_yaml(msg.result, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveServo_GetResult_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_servos::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_servos::action::MoveServo_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_servos::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_servos::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_servos::action::MoveServo_GetResult_Response & msg)
{
  return transformer_hw_servos::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_servos::action::MoveServo_GetResult_Response>()
{
  return "transformer_hw_servos::action::MoveServo_GetResult_Response";
}

template<>
inline const char * name<transformer_hw_servos::action::MoveServo_GetResult_Response>()
{
  return "transformer_hw_servos/action/MoveServo_GetResult_Response";
}

template<>
struct has_fixed_size<transformer_hw_servos::action::MoveServo_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<transformer_hw_servos::action::MoveServo_Result>::value> {};

template<>
struct has_bounded_size<transformer_hw_servos::action::MoveServo_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<transformer_hw_servos::action::MoveServo_Result>::value> {};

template<>
struct is_message<transformer_hw_servos::action::MoveServo_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace transformer_hw_servos
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveServo_GetResult_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
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
  const MoveServo_GetResult_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveServo_GetResult_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_servos::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_servos::action::MoveServo_GetResult_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_servos::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_servos::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_servos::action::MoveServo_GetResult_Event & msg)
{
  return transformer_hw_servos::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_servos::action::MoveServo_GetResult_Event>()
{
  return "transformer_hw_servos::action::MoveServo_GetResult_Event";
}

template<>
inline const char * name<transformer_hw_servos::action::MoveServo_GetResult_Event>()
{
  return "transformer_hw_servos/action/MoveServo_GetResult_Event";
}

template<>
struct has_fixed_size<transformer_hw_servos::action::MoveServo_GetResult_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<transformer_hw_servos::action::MoveServo_GetResult_Event>
  : std::integral_constant<bool, has_bounded_size<service_msgs::msg::ServiceEventInfo>::value && has_bounded_size<transformer_hw_servos::action::MoveServo_GetResult_Request>::value && has_bounded_size<transformer_hw_servos::action::MoveServo_GetResult_Response>::value> {};

template<>
struct is_message<transformer_hw_servos::action::MoveServo_GetResult_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<transformer_hw_servos::action::MoveServo_GetResult>()
{
  return "transformer_hw_servos::action::MoveServo_GetResult";
}

template<>
inline const char * name<transformer_hw_servos::action::MoveServo_GetResult>()
{
  return "transformer_hw_servos/action/MoveServo_GetResult";
}

template<>
struct has_fixed_size<transformer_hw_servos::action::MoveServo_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<transformer_hw_servos::action::MoveServo_GetResult_Request>::value &&
    has_fixed_size<transformer_hw_servos::action::MoveServo_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<transformer_hw_servos::action::MoveServo_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<transformer_hw_servos::action::MoveServo_GetResult_Request>::value &&
    has_bounded_size<transformer_hw_servos::action::MoveServo_GetResult_Response>::value
  >
{
};

template<>
struct is_service<transformer_hw_servos::action::MoveServo_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<transformer_hw_servos::action::MoveServo_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<transformer_hw_servos::action::MoveServo_GetResult_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'feedback'
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__traits.hpp"

namespace transformer_hw_servos
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveServo_FeedbackMessage & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: feedback
  {
    out << "feedback: ";
    to_flow_style_yaml(msg.feedback, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveServo_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: feedback
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "feedback:\n";
    to_block_style_yaml(msg.feedback, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveServo_FeedbackMessage & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_servos::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_servos::action::MoveServo_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_servos::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_servos::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_servos::action::MoveServo_FeedbackMessage & msg)
{
  return transformer_hw_servos::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_servos::action::MoveServo_FeedbackMessage>()
{
  return "transformer_hw_servos::action::MoveServo_FeedbackMessage";
}

template<>
inline const char * name<transformer_hw_servos::action::MoveServo_FeedbackMessage>()
{
  return "transformer_hw_servos/action/MoveServo_FeedbackMessage";
}

template<>
struct has_fixed_size<transformer_hw_servos::action::MoveServo_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<transformer_hw_servos::action::MoveServo_Feedback>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<transformer_hw_servos::action::MoveServo_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<transformer_hw_servos::action::MoveServo_Feedback>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<transformer_hw_servos::action::MoveServo_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
struct is_action<transformer_hw_servos::action::MoveServo>
  : std::true_type
{
};

template<>
struct is_action_goal<transformer_hw_servos::action::MoveServo_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<transformer_hw_servos::action::MoveServo_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<transformer_hw_servos::action::MoveServo_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // TRANSFORMER_HW_SERVOS__ACTION__DETAIL__MOVE_SERVO__TRAITS_HPP_
