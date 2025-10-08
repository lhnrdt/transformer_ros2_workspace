// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from transformer_msp_bridge:msg/MspInavStatus.idl
// generated code does not contain a copyright notice
#include "transformer_msp_bridge/msg/detail/msp_inav_status__rosidl_typesupport_fastrtps_cpp.hpp"
#include "transformer_msp_bridge/msg/detail/msp_inav_status__functions.h"
#include "transformer_msp_bridge/msg/detail/msp_inav_status__struct.hpp"

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

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
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: cycle_time_us
  cdr << ros_message.cycle_time_us;

  // Member: i2c_errors
  cdr << ros_message.i2c_errors;

  // Member: sensor_status
  cdr << ros_message.sensor_status;

  // Member: cpu_load_percent
  cdr << ros_message.cpu_load_percent;

  // Member: config_profile
  cdr << ros_message.config_profile;

  // Member: battery_profile
  cdr << ros_message.battery_profile;

  // Member: mixer_profile
  cdr << ros_message.mixer_profile;

  // Member: arming_flags
  cdr << ros_message.arming_flags;

  // Member: active_modes
  {
    cdr << ros_message.active_modes;
  }

  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_msp_bridge
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  transformer_msp_bridge::msg::MspInavStatus & ros_message)
{
  // Member: cycle_time_us
  cdr >> ros_message.cycle_time_us;

  // Member: i2c_errors
  cdr >> ros_message.i2c_errors;

  // Member: sensor_status
  cdr >> ros_message.sensor_status;

  // Member: cpu_load_percent
  cdr >> ros_message.cpu_load_percent;

  // Member: config_profile
  cdr >> ros_message.config_profile;

  // Member: battery_profile
  cdr >> ros_message.battery_profile;

  // Member: mixer_profile
  cdr >> ros_message.mixer_profile;

  // Member: arming_flags
  cdr >> ros_message.arming_flags;

  // Member: active_modes
  {
    cdr >> ros_message.active_modes;
  }

  return true;
}  // NOLINT(readability/fn_size)


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_msp_bridge
get_serialized_size(
  const transformer_msp_bridge::msg::MspInavStatus & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: cycle_time_us
  {
    size_t item_size = sizeof(ros_message.cycle_time_us);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: i2c_errors
  {
    size_t item_size = sizeof(ros_message.i2c_errors);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: sensor_status
  {
    size_t item_size = sizeof(ros_message.sensor_status);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: cpu_load_percent
  {
    size_t item_size = sizeof(ros_message.cpu_load_percent);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: config_profile
  {
    size_t item_size = sizeof(ros_message.config_profile);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: battery_profile
  {
    size_t item_size = sizeof(ros_message.battery_profile);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: mixer_profile
  {
    size_t item_size = sizeof(ros_message.mixer_profile);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: arming_flags
  {
    size_t item_size = sizeof(ros_message.arming_flags);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: active_modes
  {
    size_t array_size = ros_message.active_modes.size();
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    size_t item_size = sizeof(ros_message.active_modes[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_msp_bridge
max_serialized_size_MspInavStatus(
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

  // Member: cycle_time_us
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // Member: i2c_errors
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // Member: sensor_status
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // Member: cpu_load_percent
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // Member: config_profile
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // Member: battery_profile
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // Member: mixer_profile
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // Member: arming_flags
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // Member: active_modes
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
    using DataType = transformer_msp_bridge::msg::MspInavStatus;
    is_plain =
      (
      offsetof(DataType, active_modes) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_msp_bridge
cdr_serialize_key(
  const transformer_msp_bridge::msg::MspInavStatus & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: cycle_time_us
  cdr << ros_message.cycle_time_us;

  // Member: i2c_errors
  cdr << ros_message.i2c_errors;

  // Member: sensor_status
  cdr << ros_message.sensor_status;

  // Member: cpu_load_percent
  cdr << ros_message.cpu_load_percent;

  // Member: config_profile
  cdr << ros_message.config_profile;

  // Member: battery_profile
  cdr << ros_message.battery_profile;

  // Member: mixer_profile
  cdr << ros_message.mixer_profile;

  // Member: arming_flags
  cdr << ros_message.arming_flags;

  // Member: active_modes
  {
    cdr << ros_message.active_modes;
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_msp_bridge
get_serialized_size_key(
  const transformer_msp_bridge::msg::MspInavStatus & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: cycle_time_us
  {
    size_t item_size = sizeof(ros_message.cycle_time_us);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: i2c_errors
  {
    size_t item_size = sizeof(ros_message.i2c_errors);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: sensor_status
  {
    size_t item_size = sizeof(ros_message.sensor_status);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: cpu_load_percent
  {
    size_t item_size = sizeof(ros_message.cpu_load_percent);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: config_profile
  {
    size_t item_size = sizeof(ros_message.config_profile);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: battery_profile
  {
    size_t item_size = sizeof(ros_message.battery_profile);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: mixer_profile
  {
    size_t item_size = sizeof(ros_message.mixer_profile);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: arming_flags
  {
    size_t item_size = sizeof(ros_message.arming_flags);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Member: active_modes
  {
    size_t array_size = ros_message.active_modes.size();
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    size_t item_size = sizeof(ros_message.active_modes[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_transformer_msp_bridge
max_serialized_size_key_MspInavStatus(
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

  // Member: cycle_time_us
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: i2c_errors
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: sensor_status
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: cpu_load_percent
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: config_profile
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: battery_profile
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: mixer_profile
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: arming_flags
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: active_modes
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
    using DataType = transformer_msp_bridge::msg::MspInavStatus;
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
  auto typed_message =
    static_cast<const transformer_msp_bridge::msg::MspInavStatus *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _MspInavStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<transformer_msp_bridge::msg::MspInavStatus *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _MspInavStatus__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const transformer_msp_bridge::msg::MspInavStatus *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _MspInavStatus__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_MspInavStatus(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _MspInavStatus__callbacks = {
  "transformer_msp_bridge::msg",
  "MspInavStatus",
  _MspInavStatus__cdr_serialize,
  _MspInavStatus__cdr_deserialize,
  _MspInavStatus__get_serialized_size,
  _MspInavStatus__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _MspInavStatus__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_MspInavStatus__callbacks,
  get_message_typesupport_handle_function,
  &transformer_msp_bridge__msg__MspInavStatus__get_type_hash,
  &transformer_msp_bridge__msg__MspInavStatus__get_type_description,
  &transformer_msp_bridge__msg__MspInavStatus__get_type_description_sources,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace transformer_msp_bridge

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_transformer_msp_bridge
const rosidl_message_type_support_t *
get_message_type_support_handle<transformer_msp_bridge::msg::MspInavStatus>()
{
  return &transformer_msp_bridge::msg::typesupport_fastrtps_cpp::_MspInavStatus__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_msp_bridge, msg, MspInavStatus)() {
  return &transformer_msp_bridge::msg::typesupport_fastrtps_cpp::_MspInavStatus__handle;
}

#ifdef __cplusplus
}
#endif
