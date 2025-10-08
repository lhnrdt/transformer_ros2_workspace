// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from transformer_msp_bridge:msg/MspInavStatus.idl
// generated code does not contain a copyright notice
#ifndef TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "transformer_msp_bridge/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "transformer_msp_bridge/msg/detail/msp_inav_status__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_transformer_msp_bridge
bool cdr_serialize_transformer_msp_bridge__msg__MspInavStatus(
  const transformer_msp_bridge__msg__MspInavStatus * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_transformer_msp_bridge
bool cdr_deserialize_transformer_msp_bridge__msg__MspInavStatus(
  eprosima::fastcdr::Cdr &,
  transformer_msp_bridge__msg__MspInavStatus * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_transformer_msp_bridge
size_t get_serialized_size_transformer_msp_bridge__msg__MspInavStatus(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_transformer_msp_bridge
size_t max_serialized_size_transformer_msp_bridge__msg__MspInavStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_transformer_msp_bridge
bool cdr_serialize_key_transformer_msp_bridge__msg__MspInavStatus(
  const transformer_msp_bridge__msg__MspInavStatus * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_transformer_msp_bridge
size_t get_serialized_size_key_transformer_msp_bridge__msg__MspInavStatus(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_transformer_msp_bridge
size_t max_serialized_size_key_transformer_msp_bridge__msg__MspInavStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_transformer_msp_bridge
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_msp_bridge, msg, MspInavStatus)();

#ifdef __cplusplus
}
#endif

#endif  // TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
