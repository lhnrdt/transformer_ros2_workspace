// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from transformer_msp_bridge:msg/MspInavStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "transformer_msp_bridge/msg/detail/msp_inav_status__rosidl_typesupport_introspection_c.h"
#include "transformer_msp_bridge/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "transformer_msp_bridge/msg/detail/msp_inav_status__functions.h"
#include "transformer_msp_bridge/msg/detail/msp_inav_status__struct.h"


// Include directives for member types
// Member `active_modes`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__MspInavStatus_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  transformer_msp_bridge__msg__MspInavStatus__init(message_memory);
}

void transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__MspInavStatus_fini_function(void * message_memory)
{
  transformer_msp_bridge__msg__MspInavStatus__fini(message_memory);
}

size_t transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__size_function__MspInavStatus__active_modes(
  const void * untyped_member)
{
  const rosidl_runtime_c__uint8__Sequence * member =
    (const rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return member->size;
}

const void * transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__get_const_function__MspInavStatus__active_modes(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__uint8__Sequence * member =
    (const rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return &member->data[index];
}

void * transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__get_function__MspInavStatus__active_modes(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__uint8__Sequence * member =
    (rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return &member->data[index];
}

void transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__fetch_function__MspInavStatus__active_modes(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__get_const_function__MspInavStatus__active_modes(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__assign_function__MspInavStatus__active_modes(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__get_function__MspInavStatus__active_modes(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

bool transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__resize_function__MspInavStatus__active_modes(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__uint8__Sequence * member =
    (rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  rosidl_runtime_c__uint8__Sequence__fini(member);
  return rosidl_runtime_c__uint8__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__MspInavStatus_message_member_array[9] = {
  {
    "cycle_time_us",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_msp_bridge__msg__MspInavStatus, cycle_time_us),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "i2c_errors",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_msp_bridge__msg__MspInavStatus, i2c_errors),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "sensor_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_msp_bridge__msg__MspInavStatus, sensor_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "cpu_load_percent",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_msp_bridge__msg__MspInavStatus, cpu_load_percent),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "config_profile",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_msp_bridge__msg__MspInavStatus, config_profile),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "battery_profile",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_msp_bridge__msg__MspInavStatus, battery_profile),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mixer_profile",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_msp_bridge__msg__MspInavStatus, mixer_profile),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "arming_flags",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_msp_bridge__msg__MspInavStatus, arming_flags),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "active_modes",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_msp_bridge__msg__MspInavStatus, active_modes),  // bytes offset in struct
    NULL,  // default value
    transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__size_function__MspInavStatus__active_modes,  // size() function pointer
    transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__get_const_function__MspInavStatus__active_modes,  // get_const(index) function pointer
    transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__get_function__MspInavStatus__active_modes,  // get(index) function pointer
    transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__fetch_function__MspInavStatus__active_modes,  // fetch(index, &value) function pointer
    transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__assign_function__MspInavStatus__active_modes,  // assign(index, value) function pointer
    transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__resize_function__MspInavStatus__active_modes  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__MspInavStatus_message_members = {
  "transformer_msp_bridge__msg",  // message namespace
  "MspInavStatus",  // message name
  9,  // number of fields
  sizeof(transformer_msp_bridge__msg__MspInavStatus),
  false,  // has_any_key_member_
  transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__MspInavStatus_message_member_array,  // message members
  transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__MspInavStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__MspInavStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__MspInavStatus_message_type_support_handle = {
  0,
  &transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__MspInavStatus_message_members,
  get_message_typesupport_handle_function,
  &transformer_msp_bridge__msg__MspInavStatus__get_type_hash,
  &transformer_msp_bridge__msg__MspInavStatus__get_type_description,
  &transformer_msp_bridge__msg__MspInavStatus__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_transformer_msp_bridge
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_msp_bridge, msg, MspInavStatus)() {
  if (!transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__MspInavStatus_message_type_support_handle.typesupport_identifier) {
    transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__MspInavStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &transformer_msp_bridge__msg__MspInavStatus__rosidl_typesupport_introspection_c__MspInavStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
