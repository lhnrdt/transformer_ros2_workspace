// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from transformer_msp_bridge:msg/MspInavStatus.idl
// generated code does not contain a copyright notice
#include "transformer_msp_bridge/msg/detail/msp_inav_status__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "transformer_msp_bridge/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "transformer_msp_bridge/msg/detail/msp_inav_status__struct.h"
#include "transformer_msp_bridge/msg/detail/msp_inav_status__functions.h"
#include "fastcdr/Cdr.h"

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

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/primitives_sequence.h"  // active_modes
#include "rosidl_runtime_c/primitives_sequence_functions.h"  // active_modes

// forward declare type support functions


using _MspInavStatus__ros_msg_type = transformer_msp_bridge__msg__MspInavStatus;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_transformer_msp_bridge
bool cdr_serialize_transformer_msp_bridge__msg__MspInavStatus(
  const transformer_msp_bridge__msg__MspInavStatus * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: cycle_time_us
  {
    cdr << ros_message->cycle_time_us;
  }

  // Field name: i2c_errors
  {
    cdr << ros_message->i2c_errors;
  }

  // Field name: sensor_status
  {
    cdr << ros_message->sensor_status;
  }

  // Field name: cpu_load_percent
  {
    cdr << ros_message->cpu_load_percent;
  }

  // Field name: config_profile
  {
    cdr << ros_message->config_profile;
  }

  // Field name: battery_profile
  {
    cdr << ros_message->battery_profile;
  }

  // Field name: mixer_profile
  {
    cdr << ros_message->mixer_profile;
  }

  // Field name: arming_flags
  {
    cdr << ros_message->arming_flags;
  }

  // Field name: active_modes
  {
    size_t size = ros_message->active_modes.size;
    auto array_ptr = ros_message->active_modes.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serialize_array(array_ptr, size);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_transformer_msp_bridge
bool cdr_deserialize_transformer_msp_bridge__msg__MspInavStatus(
  eprosima::fastcdr::Cdr & cdr,
  transformer_msp_bridge__msg__MspInavStatus * ros_message)
{
  // Field name: cycle_time_us
  {
    cdr >> ros_message->cycle_time_us;
  }

  // Field name: i2c_errors
  {
    cdr >> ros_message->i2c_errors;
  }

  // Field name: sensor_status
  {
    cdr >> ros_message->sensor_status;
  }

  // Field name: cpu_load_percent
  {
    cdr >> ros_message->cpu_load_percent;
  }

  // Field name: config_profile
  {
    cdr >> ros_message->config_profile;
  }

  // Field name: battery_profile
  {
    cdr >> ros_message->battery_profile;
  }

  // Field name: mixer_profile
  {
    cdr >> ros_message->mixer_profile;
  }

  // Field name: arming_flags
  {
    cdr >> ros_message->arming_flags;
  }

  // Field name: active_modes
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);

    // Check there are at least 'size' remaining bytes in the CDR stream before resizing
    auto old_state = cdr.get_state();
    bool correct_size = cdr.jump(size);
    cdr.set_state(old_state);
    if (!correct_size) {
      fprintf(stderr, "sequence size exceeds remaining buffer\n");
      return false;
    }

    if (ros_message->active_modes.data) {
      rosidl_runtime_c__uint8__Sequence__fini(&ros_message->active_modes);
    }
    if (!rosidl_runtime_c__uint8__Sequence__init(&ros_message->active_modes, size)) {
      fprintf(stderr, "failed to create array for field 'active_modes'");
      return false;
    }
    auto array_ptr = ros_message->active_modes.data;
    cdr.deserialize_array(array_ptr, size);
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_transformer_msp_bridge
size_t get_serialized_size_transformer_msp_bridge__msg__MspInavStatus(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _MspInavStatus__ros_msg_type * ros_message = static_cast<const _MspInavStatus__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: cycle_time_us
  {
    size_t item_size = sizeof(ros_message->cycle_time_us);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: i2c_errors
  {
    size_t item_size = sizeof(ros_message->i2c_errors);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: sensor_status
  {
    size_t item_size = sizeof(ros_message->sensor_status);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: cpu_load_percent
  {
    size_t item_size = sizeof(ros_message->cpu_load_percent);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: config_profile
  {
    size_t item_size = sizeof(ros_message->config_profile);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: battery_profile
  {
    size_t item_size = sizeof(ros_message->battery_profile);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: mixer_profile
  {
    size_t item_size = sizeof(ros_message->mixer_profile);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: arming_flags
  {
    size_t item_size = sizeof(ros_message->arming_flags);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: active_modes
  {
    size_t array_size = ros_message->active_modes.size;
    auto array_ptr = ros_message->active_modes.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_transformer_msp_bridge
size_t max_serialized_size_transformer_msp_bridge__msg__MspInavStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Field name: cycle_time_us
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Field name: i2c_errors
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Field name: sensor_status
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Field name: cpu_load_percent
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Field name: config_profile
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: battery_profile
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: mixer_profile
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: arming_flags
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: active_modes
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = transformer_msp_bridge__msg__MspInavStatus;
    is_plain =
      (
      offsetof(DataType, active_modes) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_transformer_msp_bridge
bool cdr_serialize_key_transformer_msp_bridge__msg__MspInavStatus(
  const transformer_msp_bridge__msg__MspInavStatus * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: cycle_time_us
  {
    cdr << ros_message->cycle_time_us;
  }

  // Field name: i2c_errors
  {
    cdr << ros_message->i2c_errors;
  }

  // Field name: sensor_status
  {
    cdr << ros_message->sensor_status;
  }

  // Field name: cpu_load_percent
  {
    cdr << ros_message->cpu_load_percent;
  }

  // Field name: config_profile
  {
    cdr << ros_message->config_profile;
  }

  // Field name: battery_profile
  {
    cdr << ros_message->battery_profile;
  }

  // Field name: mixer_profile
  {
    cdr << ros_message->mixer_profile;
  }

  // Field name: arming_flags
  {
    cdr << ros_message->arming_flags;
  }

  // Field name: active_modes
  {
    size_t size = ros_message->active_modes.size;
    auto array_ptr = ros_message->active_modes.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serialize_array(array_ptr, size);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_transformer_msp_bridge
size_t get_serialized_size_key_transformer_msp_bridge__msg__MspInavStatus(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _MspInavStatus__ros_msg_type * ros_message = static_cast<const _MspInavStatus__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: cycle_time_us
  {
    size_t item_size = sizeof(ros_message->cycle_time_us);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: i2c_errors
  {
    size_t item_size = sizeof(ros_message->i2c_errors);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: sensor_status
  {
    size_t item_size = sizeof(ros_message->sensor_status);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: cpu_load_percent
  {
    size_t item_size = sizeof(ros_message->cpu_load_percent);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: config_profile
  {
    size_t item_size = sizeof(ros_message->config_profile);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: battery_profile
  {
    size_t item_size = sizeof(ros_message->battery_profile);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: mixer_profile
  {
    size_t item_size = sizeof(ros_message->mixer_profile);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: arming_flags
  {
    size_t item_size = sizeof(ros_message->arming_flags);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: active_modes
  {
    size_t array_size = ros_message->active_modes.size;
    auto array_ptr = ros_message->active_modes.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_transformer_msp_bridge
size_t max_serialized_size_key_transformer_msp_bridge__msg__MspInavStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;
  // Field name: cycle_time_us
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Field name: i2c_errors
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Field name: sensor_status
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Field name: cpu_load_percent
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Field name: config_profile
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: battery_profile
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: mixer_profile
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: arming_flags
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: active_modes
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = transformer_msp_bridge__msg__MspInavStatus;
    is_plain =
      (
      offsetof(DataType, active_modes) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _MspInavStatus__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const transformer_msp_bridge__msg__MspInavStatus * ros_message = static_cast<const transformer_msp_bridge__msg__MspInavStatus *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_transformer_msp_bridge__msg__MspInavStatus(ros_message, cdr);
}

static bool _MspInavStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  transformer_msp_bridge__msg__MspInavStatus * ros_message = static_cast<transformer_msp_bridge__msg__MspInavStatus *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_transformer_msp_bridge__msg__MspInavStatus(cdr, ros_message);
}

static uint32_t _MspInavStatus__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_transformer_msp_bridge__msg__MspInavStatus(
      untyped_ros_message, 0));
}

static size_t _MspInavStatus__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_transformer_msp_bridge__msg__MspInavStatus(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_MspInavStatus = {
  "transformer_msp_bridge::msg",
  "MspInavStatus",
  _MspInavStatus__cdr_serialize,
  _MspInavStatus__cdr_deserialize,
  _MspInavStatus__get_serialized_size,
  _MspInavStatus__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _MspInavStatus__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_MspInavStatus,
  get_message_typesupport_handle_function,
  &transformer_msp_bridge__msg__MspInavStatus__get_type_hash,
  &transformer_msp_bridge__msg__MspInavStatus__get_type_description,
  &transformer_msp_bridge__msg__MspInavStatus__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_msp_bridge, msg, MspInavStatus)() {
  return &_MspInavStatus__type_support;
}

#if defined(__cplusplus)
}
#endif
