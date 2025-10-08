// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from transformer_hw_actuators:action/MoveActuator.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "transformer_hw_actuators/action/move_actuator.hpp"


#ifndef TRANSFORMER_HW_ACTUATORS__ACTION__DETAIL__MOVE_ACTUATOR__TRAITS_HPP_
#define TRANSFORMER_HW_ACTUATORS__ACTION__DETAIL__MOVE_ACTUATOR__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "transformer_hw_actuators/action/detail/move_actuator__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace transformer_hw_actuators
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveActuator_Goal & msg,
  std::ostream & out)
{
  out << "{";
  // member: actuators
  {
    if (msg.actuators.size() == 0) {
      out << "actuators: []";
    } else {
      out << "actuators: [";
      size_t pending_items = msg.actuators.size();
      for (auto item : msg.actuators) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: speed_percents
  {
    if (msg.speed_percents.size() == 0) {
      out << "speed_percents: []";
    } else {
      out << "speed_percents: [";
      size_t pending_items = msg.speed_percents.size();
      for (auto item : msg.speed_percents) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: duration_ms
  {
    if (msg.duration_ms.size() == 0) {
      out << "duration_ms: []";
    } else {
      out << "duration_ms: [";
      size_t pending_items = msg.duration_ms.size();
      for (auto item : msg.duration_ms) {
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
  const MoveActuator_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: actuators
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.actuators.size() == 0) {
      out << "actuators: []\n";
    } else {
      out << "actuators:\n";
      for (auto item : msg.actuators) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: speed_percents
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.speed_percents.size() == 0) {
      out << "speed_percents: []\n";
    } else {
      out << "speed_percents:\n";
      for (auto item : msg.speed_percents) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: duration_ms
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.duration_ms.size() == 0) {
      out << "duration_ms: []\n";
    } else {
      out << "duration_ms:\n";
      for (auto item : msg.duration_ms) {
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

inline std::string to_yaml(const MoveActuator_Goal & msg, bool use_flow_style = false)
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

}  // namespace transformer_hw_actuators

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_actuators::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_actuators::action::MoveActuator_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_actuators::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_actuators::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_actuators::action::MoveActuator_Goal & msg)
{
  return transformer_hw_actuators::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_actuators::action::MoveActuator_Goal>()
{
  return "transformer_hw_actuators::action::MoveActuator_Goal";
}

template<>
inline const char * name<transformer_hw_actuators::action::MoveActuator_Goal>()
{
  return "transformer_hw_actuators/action/MoveActuator_Goal";
}

template<>
struct has_fixed_size<transformer_hw_actuators::action::MoveActuator_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<transformer_hw_actuators::action::MoveActuator_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<transformer_hw_actuators::action::MoveActuator_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace transformer_hw_actuators
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveActuator_Result & msg,
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
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveActuator_Result & msg,
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveActuator_Result & msg, bool use_flow_style = false)
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

}  // namespace transformer_hw_actuators

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_actuators::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_actuators::action::MoveActuator_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_actuators::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_actuators::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_actuators::action::MoveActuator_Result & msg)
{
  return transformer_hw_actuators::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_actuators::action::MoveActuator_Result>()
{
  return "transformer_hw_actuators::action::MoveActuator_Result";
}

template<>
inline const char * name<transformer_hw_actuators::action::MoveActuator_Result>()
{
  return "transformer_hw_actuators/action/MoveActuator_Result";
}

template<>
struct has_fixed_size<transformer_hw_actuators::action::MoveActuator_Result>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<transformer_hw_actuators::action::MoveActuator_Result>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<transformer_hw_actuators::action::MoveActuator_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace transformer_hw_actuators
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveActuator_Feedback & msg,
  std::ostream & out)
{
  out << "{";
  // member: current_speed_percents
  {
    if (msg.current_speed_percents.size() == 0) {
      out << "current_speed_percents: []";
    } else {
      out << "current_speed_percents: [";
      size_t pending_items = msg.current_speed_percents.size();
      for (auto item : msg.current_speed_percents) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: elapsed_ms
  {
    if (msg.elapsed_ms.size() == 0) {
      out << "elapsed_ms: []";
    } else {
      out << "elapsed_ms: [";
      size_t pending_items = msg.elapsed_ms.size();
      for (auto item : msg.elapsed_ms) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: remaining_ms
  {
    if (msg.remaining_ms.size() == 0) {
      out << "remaining_ms: []";
    } else {
      out << "remaining_ms: [";
      size_t pending_items = msg.remaining_ms.size();
      for (auto item : msg.remaining_ms) {
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
  const MoveActuator_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: current_speed_percents
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.current_speed_percents.size() == 0) {
      out << "current_speed_percents: []\n";
    } else {
      out << "current_speed_percents:\n";
      for (auto item : msg.current_speed_percents) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: elapsed_ms
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.elapsed_ms.size() == 0) {
      out << "elapsed_ms: []\n";
    } else {
      out << "elapsed_ms:\n";
      for (auto item : msg.elapsed_ms) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: remaining_ms
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.remaining_ms.size() == 0) {
      out << "remaining_ms: []\n";
    } else {
      out << "remaining_ms:\n";
      for (auto item : msg.remaining_ms) {
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

inline std::string to_yaml(const MoveActuator_Feedback & msg, bool use_flow_style = false)
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

}  // namespace transformer_hw_actuators

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_actuators::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_actuators::action::MoveActuator_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_actuators::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_actuators::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_actuators::action::MoveActuator_Feedback & msg)
{
  return transformer_hw_actuators::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_actuators::action::MoveActuator_Feedback>()
{
  return "transformer_hw_actuators::action::MoveActuator_Feedback";
}

template<>
inline const char * name<transformer_hw_actuators::action::MoveActuator_Feedback>()
{
  return "transformer_hw_actuators/action/MoveActuator_Feedback";
}

template<>
struct has_fixed_size<transformer_hw_actuators::action::MoveActuator_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<transformer_hw_actuators::action::MoveActuator_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<transformer_hw_actuators::action::MoveActuator_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "transformer_hw_actuators/action/detail/move_actuator__traits.hpp"

namespace transformer_hw_actuators
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveActuator_SendGoal_Request & msg,
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
  const MoveActuator_SendGoal_Request & msg,
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

inline std::string to_yaml(const MoveActuator_SendGoal_Request & msg, bool use_flow_style = false)
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

}  // namespace transformer_hw_actuators

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_actuators::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_actuators::action::MoveActuator_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_actuators::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_actuators::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_actuators::action::MoveActuator_SendGoal_Request & msg)
{
  return transformer_hw_actuators::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_actuators::action::MoveActuator_SendGoal_Request>()
{
  return "transformer_hw_actuators::action::MoveActuator_SendGoal_Request";
}

template<>
inline const char * name<transformer_hw_actuators::action::MoveActuator_SendGoal_Request>()
{
  return "transformer_hw_actuators/action/MoveActuator_SendGoal_Request";
}

template<>
struct has_fixed_size<transformer_hw_actuators::action::MoveActuator_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<transformer_hw_actuators::action::MoveActuator_Goal>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<transformer_hw_actuators::action::MoveActuator_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<transformer_hw_actuators::action::MoveActuator_Goal>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<transformer_hw_actuators::action::MoveActuator_SendGoal_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace transformer_hw_actuators
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveActuator_SendGoal_Response & msg,
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
  const MoveActuator_SendGoal_Response & msg,
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

inline std::string to_yaml(const MoveActuator_SendGoal_Response & msg, bool use_flow_style = false)
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

}  // namespace transformer_hw_actuators

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_actuators::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_actuators::action::MoveActuator_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_actuators::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_actuators::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_actuators::action::MoveActuator_SendGoal_Response & msg)
{
  return transformer_hw_actuators::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_actuators::action::MoveActuator_SendGoal_Response>()
{
  return "transformer_hw_actuators::action::MoveActuator_SendGoal_Response";
}

template<>
inline const char * name<transformer_hw_actuators::action::MoveActuator_SendGoal_Response>()
{
  return "transformer_hw_actuators/action/MoveActuator_SendGoal_Response";
}

template<>
struct has_fixed_size<transformer_hw_actuators::action::MoveActuator_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<transformer_hw_actuators::action::MoveActuator_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<transformer_hw_actuators::action::MoveActuator_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace transformer_hw_actuators
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveActuator_SendGoal_Event & msg,
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
  const MoveActuator_SendGoal_Event & msg,
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

inline std::string to_yaml(const MoveActuator_SendGoal_Event & msg, bool use_flow_style = false)
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

}  // namespace transformer_hw_actuators

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_actuators::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_actuators::action::MoveActuator_SendGoal_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_actuators::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_actuators::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_actuators::action::MoveActuator_SendGoal_Event & msg)
{
  return transformer_hw_actuators::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_actuators::action::MoveActuator_SendGoal_Event>()
{
  return "transformer_hw_actuators::action::MoveActuator_SendGoal_Event";
}

template<>
inline const char * name<transformer_hw_actuators::action::MoveActuator_SendGoal_Event>()
{
  return "transformer_hw_actuators/action/MoveActuator_SendGoal_Event";
}

template<>
struct has_fixed_size<transformer_hw_actuators::action::MoveActuator_SendGoal_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<transformer_hw_actuators::action::MoveActuator_SendGoal_Event>
  : std::integral_constant<bool, has_bounded_size<service_msgs::msg::ServiceEventInfo>::value && has_bounded_size<transformer_hw_actuators::action::MoveActuator_SendGoal_Request>::value && has_bounded_size<transformer_hw_actuators::action::MoveActuator_SendGoal_Response>::value> {};

template<>
struct is_message<transformer_hw_actuators::action::MoveActuator_SendGoal_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<transformer_hw_actuators::action::MoveActuator_SendGoal>()
{
  return "transformer_hw_actuators::action::MoveActuator_SendGoal";
}

template<>
inline const char * name<transformer_hw_actuators::action::MoveActuator_SendGoal>()
{
  return "transformer_hw_actuators/action/MoveActuator_SendGoal";
}

template<>
struct has_fixed_size<transformer_hw_actuators::action::MoveActuator_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<transformer_hw_actuators::action::MoveActuator_SendGoal_Request>::value &&
    has_fixed_size<transformer_hw_actuators::action::MoveActuator_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<transformer_hw_actuators::action::MoveActuator_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<transformer_hw_actuators::action::MoveActuator_SendGoal_Request>::value &&
    has_bounded_size<transformer_hw_actuators::action::MoveActuator_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<transformer_hw_actuators::action::MoveActuator_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<transformer_hw_actuators::action::MoveActuator_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<transformer_hw_actuators::action::MoveActuator_SendGoal_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"

namespace transformer_hw_actuators
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveActuator_GetResult_Request & msg,
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
  const MoveActuator_GetResult_Request & msg,
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

inline std::string to_yaml(const MoveActuator_GetResult_Request & msg, bool use_flow_style = false)
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

}  // namespace transformer_hw_actuators

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_actuators::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_actuators::action::MoveActuator_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_actuators::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_actuators::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_actuators::action::MoveActuator_GetResult_Request & msg)
{
  return transformer_hw_actuators::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_actuators::action::MoveActuator_GetResult_Request>()
{
  return "transformer_hw_actuators::action::MoveActuator_GetResult_Request";
}

template<>
inline const char * name<transformer_hw_actuators::action::MoveActuator_GetResult_Request>()
{
  return "transformer_hw_actuators/action/MoveActuator_GetResult_Request";
}

template<>
struct has_fixed_size<transformer_hw_actuators::action::MoveActuator_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<transformer_hw_actuators::action::MoveActuator_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<transformer_hw_actuators::action::MoveActuator_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__traits.hpp"

namespace transformer_hw_actuators
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveActuator_GetResult_Response & msg,
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
  const MoveActuator_GetResult_Response & msg,
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

inline std::string to_yaml(const MoveActuator_GetResult_Response & msg, bool use_flow_style = false)
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

}  // namespace transformer_hw_actuators

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_actuators::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_actuators::action::MoveActuator_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_actuators::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_actuators::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_actuators::action::MoveActuator_GetResult_Response & msg)
{
  return transformer_hw_actuators::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_actuators::action::MoveActuator_GetResult_Response>()
{
  return "transformer_hw_actuators::action::MoveActuator_GetResult_Response";
}

template<>
inline const char * name<transformer_hw_actuators::action::MoveActuator_GetResult_Response>()
{
  return "transformer_hw_actuators/action/MoveActuator_GetResult_Response";
}

template<>
struct has_fixed_size<transformer_hw_actuators::action::MoveActuator_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<transformer_hw_actuators::action::MoveActuator_Result>::value> {};

template<>
struct has_bounded_size<transformer_hw_actuators::action::MoveActuator_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<transformer_hw_actuators::action::MoveActuator_Result>::value> {};

template<>
struct is_message<transformer_hw_actuators::action::MoveActuator_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace transformer_hw_actuators
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveActuator_GetResult_Event & msg,
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
  const MoveActuator_GetResult_Event & msg,
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

inline std::string to_yaml(const MoveActuator_GetResult_Event & msg, bool use_flow_style = false)
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

}  // namespace transformer_hw_actuators

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_actuators::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_actuators::action::MoveActuator_GetResult_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_actuators::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_actuators::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_actuators::action::MoveActuator_GetResult_Event & msg)
{
  return transformer_hw_actuators::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_actuators::action::MoveActuator_GetResult_Event>()
{
  return "transformer_hw_actuators::action::MoveActuator_GetResult_Event";
}

template<>
inline const char * name<transformer_hw_actuators::action::MoveActuator_GetResult_Event>()
{
  return "transformer_hw_actuators/action/MoveActuator_GetResult_Event";
}

template<>
struct has_fixed_size<transformer_hw_actuators::action::MoveActuator_GetResult_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<transformer_hw_actuators::action::MoveActuator_GetResult_Event>
  : std::integral_constant<bool, has_bounded_size<service_msgs::msg::ServiceEventInfo>::value && has_bounded_size<transformer_hw_actuators::action::MoveActuator_GetResult_Request>::value && has_bounded_size<transformer_hw_actuators::action::MoveActuator_GetResult_Response>::value> {};

template<>
struct is_message<transformer_hw_actuators::action::MoveActuator_GetResult_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<transformer_hw_actuators::action::MoveActuator_GetResult>()
{
  return "transformer_hw_actuators::action::MoveActuator_GetResult";
}

template<>
inline const char * name<transformer_hw_actuators::action::MoveActuator_GetResult>()
{
  return "transformer_hw_actuators/action/MoveActuator_GetResult";
}

template<>
struct has_fixed_size<transformer_hw_actuators::action::MoveActuator_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<transformer_hw_actuators::action::MoveActuator_GetResult_Request>::value &&
    has_fixed_size<transformer_hw_actuators::action::MoveActuator_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<transformer_hw_actuators::action::MoveActuator_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<transformer_hw_actuators::action::MoveActuator_GetResult_Request>::value &&
    has_bounded_size<transformer_hw_actuators::action::MoveActuator_GetResult_Response>::value
  >
{
};

template<>
struct is_service<transformer_hw_actuators::action::MoveActuator_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<transformer_hw_actuators::action::MoveActuator_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<transformer_hw_actuators::action::MoveActuator_GetResult_Response>
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
// #include "transformer_hw_actuators/action/detail/move_actuator__traits.hpp"

namespace transformer_hw_actuators
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveActuator_FeedbackMessage & msg,
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
  const MoveActuator_FeedbackMessage & msg,
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

inline std::string to_yaml(const MoveActuator_FeedbackMessage & msg, bool use_flow_style = false)
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

}  // namespace transformer_hw_actuators

namespace rosidl_generator_traits
{

[[deprecated("use transformer_hw_actuators::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const transformer_hw_actuators::action::MoveActuator_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  transformer_hw_actuators::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use transformer_hw_actuators::action::to_yaml() instead")]]
inline std::string to_yaml(const transformer_hw_actuators::action::MoveActuator_FeedbackMessage & msg)
{
  return transformer_hw_actuators::action::to_yaml(msg);
}

template<>
inline const char * data_type<transformer_hw_actuators::action::MoveActuator_FeedbackMessage>()
{
  return "transformer_hw_actuators::action::MoveActuator_FeedbackMessage";
}

template<>
inline const char * name<transformer_hw_actuators::action::MoveActuator_FeedbackMessage>()
{
  return "transformer_hw_actuators/action/MoveActuator_FeedbackMessage";
}

template<>
struct has_fixed_size<transformer_hw_actuators::action::MoveActuator_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<transformer_hw_actuators::action::MoveActuator_Feedback>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<transformer_hw_actuators::action::MoveActuator_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<transformer_hw_actuators::action::MoveActuator_Feedback>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<transformer_hw_actuators::action::MoveActuator_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
struct is_action<transformer_hw_actuators::action::MoveActuator>
  : std::true_type
{
};

template<>
struct is_action_goal<transformer_hw_actuators::action::MoveActuator_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<transformer_hw_actuators::action::MoveActuator_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<transformer_hw_actuators::action::MoveActuator_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // TRANSFORMER_HW_ACTUATORS__ACTION__DETAIL__MOVE_ACTUATOR__TRAITS_HPP_
