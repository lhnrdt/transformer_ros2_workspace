// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from transformer_msp_bridge:msg/MspInavStatus.idl
// generated code does not contain a copyright notice

#ifndef TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include <cstddef>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "transformer_msp_bridge/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "transformer_msp_bridge/msg/detail/msp_inav_status__struct.hpp"

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

namespace transformer_msp_bridge
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_msp_bridge
cdr_serialize(
  const transformer_msp_bridge::msg::MspInavStatus & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_msp_bridge
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  transformer_msp_bridge::msg::MspInavStatus & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_msp_bridge
get_serialized_size(
  const transformer_msp_bridge::msg::MspInavStatus & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_msp_bridge
max_serialized_size_MspInavStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_msp_bridge
cdr_serialize_key(
  const transformer_msp_bridge::msg::MspInavStatus & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_msp_bridge
get_serialized_size_key(
  const transformer_msp_bridge::msg::MspInavStatus & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_msp_bridge
max_serialized_size_key_MspInavStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace transformer_msp_bridge

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_msp_bridge
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_msp_bridge, msg, MspInavStatus)();

#ifdef __cplusplus
}
#endif

#endif  // TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
