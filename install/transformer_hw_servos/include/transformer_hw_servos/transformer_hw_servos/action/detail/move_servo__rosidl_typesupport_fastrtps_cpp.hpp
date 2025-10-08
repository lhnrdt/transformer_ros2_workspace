// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from transformer_hw_servos:action/MoveServo.idl
// generated code does not contain a copyright notice

#ifndef TRANSFORMER_HW_SERVOS__ACTION__DETAIL__MOVE_SERVO__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define TRANSFORMER_HW_SERVOS__ACTION__DETAIL__MOVE_SERVO__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include <cstddef>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "transformer_hw_servos/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "transformer_hw_servos/action/detail/move_servo__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace transformer_hw_servos
{

namespace action
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize(
  const transformer_hw_servos::action::MoveServo_Goal & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  transformer_hw_servos::action::MoveServo_Goal & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size(
  const transformer_hw_servos::action::MoveServo_Goal & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_MoveServo_Goal(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize_key(
  const transformer_hw_servos::action::MoveServo_Goal & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size_key(
  const transformer_hw_servos::action::MoveServo_Goal & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_key_MoveServo_Goal(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_Goal)();

#ifdef __cplusplus
}
#endif
// already included above
// #include <cstddef>
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// already included above
// #include "fastcdr/Cdr.h"

namespace transformer_hw_servos
{

namespace action
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize(
  const transformer_hw_servos::action::MoveServo_Result & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  transformer_hw_servos::action::MoveServo_Result & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size(
  const transformer_hw_servos::action::MoveServo_Result & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_MoveServo_Result(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize_key(
  const transformer_hw_servos::action::MoveServo_Result & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size_key(
  const transformer_hw_servos::action::MoveServo_Result & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_key_MoveServo_Result(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_Result)();

#ifdef __cplusplus
}
#endif
// already included above
// #include <cstddef>
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// already included above
// #include "fastcdr/Cdr.h"

namespace transformer_hw_servos
{

namespace action
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize(
  const transformer_hw_servos::action::MoveServo_Feedback & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  transformer_hw_servos::action::MoveServo_Feedback & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size(
  const transformer_hw_servos::action::MoveServo_Feedback & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_MoveServo_Feedback(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize_key(
  const transformer_hw_servos::action::MoveServo_Feedback & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size_key(
  const transformer_hw_servos::action::MoveServo_Feedback & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_key_MoveServo_Feedback(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_Feedback)();

#ifdef __cplusplus
}
#endif
// already included above
// #include <cstddef>
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// already included above
// #include "fastcdr/Cdr.h"

namespace transformer_hw_servos
{

namespace action
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize(
  const transformer_hw_servos::action::MoveServo_SendGoal_Request & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  transformer_hw_servos::action::MoveServo_SendGoal_Request & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size(
  const transformer_hw_servos::action::MoveServo_SendGoal_Request & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_MoveServo_SendGoal_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize_key(
  const transformer_hw_servos::action::MoveServo_SendGoal_Request & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size_key(
  const transformer_hw_servos::action::MoveServo_SendGoal_Request & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_key_MoveServo_SendGoal_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_SendGoal_Request)();

#ifdef __cplusplus
}
#endif

// already included above
// #include <cstddef>
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// already included above
// #include "fastcdr/Cdr.h"

namespace transformer_hw_servos
{

namespace action
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize(
  const transformer_hw_servos::action::MoveServo_SendGoal_Response & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  transformer_hw_servos::action::MoveServo_SendGoal_Response & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size(
  const transformer_hw_servos::action::MoveServo_SendGoal_Response & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_MoveServo_SendGoal_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize_key(
  const transformer_hw_servos::action::MoveServo_SendGoal_Response & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size_key(
  const transformer_hw_servos::action::MoveServo_SendGoal_Response & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_key_MoveServo_SendGoal_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_SendGoal_Response)();

#ifdef __cplusplus
}
#endif

// already included above
// #include <cstddef>
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// already included above
// #include "fastcdr/Cdr.h"

namespace transformer_hw_servos
{

namespace action
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize(
  const transformer_hw_servos::action::MoveServo_SendGoal_Event & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  transformer_hw_servos::action::MoveServo_SendGoal_Event & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size(
  const transformer_hw_servos::action::MoveServo_SendGoal_Event & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_MoveServo_SendGoal_Event(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize_key(
  const transformer_hw_servos::action::MoveServo_SendGoal_Event & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size_key(
  const transformer_hw_servos::action::MoveServo_SendGoal_Event & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_key_MoveServo_SendGoal_Event(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_SendGoal_Event)();

#ifdef __cplusplus
}
#endif

#include "rmw/types.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
const rosidl_service_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_SendGoal)();

#ifdef __cplusplus
}
#endif
// already included above
// #include <cstddef>
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// already included above
// #include "fastcdr/Cdr.h"

namespace transformer_hw_servos
{

namespace action
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize(
  const transformer_hw_servos::action::MoveServo_GetResult_Request & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  transformer_hw_servos::action::MoveServo_GetResult_Request & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size(
  const transformer_hw_servos::action::MoveServo_GetResult_Request & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_MoveServo_GetResult_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize_key(
  const transformer_hw_servos::action::MoveServo_GetResult_Request & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size_key(
  const transformer_hw_servos::action::MoveServo_GetResult_Request & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_key_MoveServo_GetResult_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_GetResult_Request)();

#ifdef __cplusplus
}
#endif

// already included above
// #include <cstddef>
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// already included above
// #include "fastcdr/Cdr.h"

namespace transformer_hw_servos
{

namespace action
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize(
  const transformer_hw_servos::action::MoveServo_GetResult_Response & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  transformer_hw_servos::action::MoveServo_GetResult_Response & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size(
  const transformer_hw_servos::action::MoveServo_GetResult_Response & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_MoveServo_GetResult_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize_key(
  const transformer_hw_servos::action::MoveServo_GetResult_Response & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size_key(
  const transformer_hw_servos::action::MoveServo_GetResult_Response & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_key_MoveServo_GetResult_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_GetResult_Response)();

#ifdef __cplusplus
}
#endif

// already included above
// #include <cstddef>
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// already included above
// #include "fastcdr/Cdr.h"

namespace transformer_hw_servos
{

namespace action
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize(
  const transformer_hw_servos::action::MoveServo_GetResult_Event & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  transformer_hw_servos::action::MoveServo_GetResult_Event & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size(
  const transformer_hw_servos::action::MoveServo_GetResult_Event & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_MoveServo_GetResult_Event(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize_key(
  const transformer_hw_servos::action::MoveServo_GetResult_Event & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size_key(
  const transformer_hw_servos::action::MoveServo_GetResult_Event & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_key_MoveServo_GetResult_Event(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_GetResult_Event)();

#ifdef __cplusplus
}
#endif

// already included above
// #include "rmw/types.h"
// already included above
// #include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
const rosidl_service_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_GetResult)();

#ifdef __cplusplus
}
#endif
// already included above
// #include <cstddef>
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// already included above
// #include "fastcdr/Cdr.h"

namespace transformer_hw_servos
{

namespace action
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize(
  const transformer_hw_servos::action::MoveServo_FeedbackMessage & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  transformer_hw_servos::action::MoveServo_FeedbackMessage & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size(
  const transformer_hw_servos::action::MoveServo_FeedbackMessage & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_MoveServo_FeedbackMessage(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
cdr_serialize_key(
  const transformer_hw_servos::action::MoveServo_FeedbackMessage & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
get_serialized_size_key(
  const transformer_hw_servos::action::MoveServo_FeedbackMessage & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
max_serialized_size_key_MoveServo_FeedbackMessage(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_hw_servos
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_FeedbackMessage)();

#ifdef __cplusplus
}
#endif

#endif  // TRANSFORMER_HW_SERVOS__ACTION__DETAIL__MOVE_SERVO__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
