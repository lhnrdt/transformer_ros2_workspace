// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from transformer_hw_servos:action/MoveServo.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "transformer_hw_servos/action/detail/move_servo__rosidl_typesupport_introspection_c.h"
#include "transformer_hw_servos/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "transformer_hw_servos/action/detail/move_servo__functions.h"
#include "transformer_hw_servos/action/detail/move_servo__struct.h"


// Include directives for member types
// Member `channels`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__MoveServo_Goal_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  transformer_hw_servos__action__MoveServo_Goal__init(message_memory);
}

void transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__MoveServo_Goal_fini_function(void * message_memory)
{
  transformer_hw_servos__action__MoveServo_Goal__fini(message_memory);
}

size_t transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__size_function__MoveServo_Goal__channels(
  const void * untyped_member)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return member->size;
}

const void * transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__get_const_function__MoveServo_Goal__channels(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__get_function__MoveServo_Goal__channels(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__fetch_function__MoveServo_Goal__channels(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int32_t * item =
    ((const int32_t *)
    transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__get_const_function__MoveServo_Goal__channels(untyped_member, index));
  int32_t * value =
    (int32_t *)(untyped_value);
  *value = *item;
}

void transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__assign_function__MoveServo_Goal__channels(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int32_t * item =
    ((int32_t *)
    transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__get_function__MoveServo_Goal__channels(untyped_member, index));
  const int32_t * value =
    (const int32_t *)(untyped_value);
  *item = *value;
}

bool transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__resize_function__MoveServo_Goal__channels(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  rosidl_runtime_c__int32__Sequence__fini(member);
  return rosidl_runtime_c__int32__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__MoveServo_Goal_message_member_array[5] = {
  {
    "channels",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_Goal, channels),  // bytes offset in struct
    NULL,  // default value
    transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__size_function__MoveServo_Goal__channels,  // size() function pointer
    transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__get_const_function__MoveServo_Goal__channels,  // get_const(index) function pointer
    transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__get_function__MoveServo_Goal__channels,  // get(index) function pointer
    transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__fetch_function__MoveServo_Goal__channels,  // fetch(index, &value) function pointer
    transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__assign_function__MoveServo_Goal__channels,  // assign(index, value) function pointer
    transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__resize_function__MoveServo_Goal__channels  // resize(index) function pointer
  },
  {
    "pulse_us",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_Goal, pulse_us),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "speed_us_per_s",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_Goal, speed_us_per_s),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "use_trapezoid",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_Goal, use_trapezoid),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "accel_us_per_s2",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_Goal, accel_us_per_s2),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__MoveServo_Goal_message_members = {
  "transformer_hw_servos__action",  // message namespace
  "MoveServo_Goal",  // message name
  5,  // number of fields
  sizeof(transformer_hw_servos__action__MoveServo_Goal),
  false,  // has_any_key_member_
  transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__MoveServo_Goal_message_member_array,  // message members
  transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__MoveServo_Goal_init_function,  // function to initialize message memory (memory has to be allocated)
  transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__MoveServo_Goal_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__MoveServo_Goal_message_type_support_handle = {
  0,
  &transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__MoveServo_Goal_message_members,
  get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_Goal__get_type_hash,
  &transformer_hw_servos__action__MoveServo_Goal__get_type_description,
  &transformer_hw_servos__action__MoveServo_Goal__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_transformer_hw_servos
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_Goal)() {
  if (!transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__MoveServo_Goal_message_type_support_handle.typesupport_identifier) {
    transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__MoveServo_Goal_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &transformer_hw_servos__action__MoveServo_Goal__rosidl_typesupport_introspection_c__MoveServo_Goal_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__rosidl_typesupport_introspection_c.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"
// Member `final_pulses_us`
// already included above
// #include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__MoveServo_Result_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  transformer_hw_servos__action__MoveServo_Result__init(message_memory);
}

void transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__MoveServo_Result_fini_function(void * message_memory)
{
  transformer_hw_servos__action__MoveServo_Result__fini(message_memory);
}

size_t transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__size_function__MoveServo_Result__final_pulses_us(
  const void * untyped_member)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return member->size;
}

const void * transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__get_const_function__MoveServo_Result__final_pulses_us(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__get_function__MoveServo_Result__final_pulses_us(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__fetch_function__MoveServo_Result__final_pulses_us(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int32_t * item =
    ((const int32_t *)
    transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__get_const_function__MoveServo_Result__final_pulses_us(untyped_member, index));
  int32_t * value =
    (int32_t *)(untyped_value);
  *value = *item;
}

void transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__assign_function__MoveServo_Result__final_pulses_us(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int32_t * item =
    ((int32_t *)
    transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__get_function__MoveServo_Result__final_pulses_us(untyped_member, index));
  const int32_t * value =
    (const int32_t *)(untyped_value);
  *item = *value;
}

bool transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__resize_function__MoveServo_Result__final_pulses_us(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  rosidl_runtime_c__int32__Sequence__fini(member);
  return rosidl_runtime_c__int32__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__MoveServo_Result_message_member_array[4] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_Result, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_Result, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "final_pulses_us",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_Result, final_pulses_us),  // bytes offset in struct
    NULL,  // default value
    transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__size_function__MoveServo_Result__final_pulses_us,  // size() function pointer
    transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__get_const_function__MoveServo_Result__final_pulses_us,  // get_const(index) function pointer
    transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__get_function__MoveServo_Result__final_pulses_us,  // get(index) function pointer
    transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__fetch_function__MoveServo_Result__final_pulses_us,  // fetch(index, &value) function pointer
    transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__assign_function__MoveServo_Result__final_pulses_us,  // assign(index, value) function pointer
    transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__resize_function__MoveServo_Result__final_pulses_us  // resize(index) function pointer
  },
  {
    "total_estimated_duration_s",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_Result, total_estimated_duration_s),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__MoveServo_Result_message_members = {
  "transformer_hw_servos__action",  // message namespace
  "MoveServo_Result",  // message name
  4,  // number of fields
  sizeof(transformer_hw_servos__action__MoveServo_Result),
  false,  // has_any_key_member_
  transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__MoveServo_Result_message_member_array,  // message members
  transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__MoveServo_Result_init_function,  // function to initialize message memory (memory has to be allocated)
  transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__MoveServo_Result_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__MoveServo_Result_message_type_support_handle = {
  0,
  &transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__MoveServo_Result_message_members,
  get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_Result__get_type_hash,
  &transformer_hw_servos__action__MoveServo_Result__get_type_description,
  &transformer_hw_servos__action__MoveServo_Result__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_transformer_hw_servos
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_Result)() {
  if (!transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__MoveServo_Result_message_type_support_handle.typesupport_identifier) {
    transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__MoveServo_Result_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &transformer_hw_servos__action__MoveServo_Result__rosidl_typesupport_introspection_c__MoveServo_Result_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__rosidl_typesupport_introspection_c.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"


// Include directives for member types
// Member `current_pulses_us`
// already included above
// #include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `phase`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__MoveServo_Feedback_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  transformer_hw_servos__action__MoveServo_Feedback__init(message_memory);
}

void transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__MoveServo_Feedback_fini_function(void * message_memory)
{
  transformer_hw_servos__action__MoveServo_Feedback__fini(message_memory);
}

size_t transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__size_function__MoveServo_Feedback__current_pulses_us(
  const void * untyped_member)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return member->size;
}

const void * transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__get_const_function__MoveServo_Feedback__current_pulses_us(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__get_function__MoveServo_Feedback__current_pulses_us(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__fetch_function__MoveServo_Feedback__current_pulses_us(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int32_t * item =
    ((const int32_t *)
    transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__get_const_function__MoveServo_Feedback__current_pulses_us(untyped_member, index));
  int32_t * value =
    (int32_t *)(untyped_value);
  *value = *item;
}

void transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__assign_function__MoveServo_Feedback__current_pulses_us(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int32_t * item =
    ((int32_t *)
    transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__get_function__MoveServo_Feedback__current_pulses_us(untyped_member, index));
  const int32_t * value =
    (const int32_t *)(untyped_value);
  *item = *value;
}

bool transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__resize_function__MoveServo_Feedback__current_pulses_us(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  rosidl_runtime_c__int32__Sequence__fini(member);
  return rosidl_runtime_c__int32__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__MoveServo_Feedback_message_member_array[4] = {
  {
    "current_pulses_us",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_Feedback, current_pulses_us),  // bytes offset in struct
    NULL,  // default value
    transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__size_function__MoveServo_Feedback__current_pulses_us,  // size() function pointer
    transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__get_const_function__MoveServo_Feedback__current_pulses_us,  // get_const(index) function pointer
    transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__get_function__MoveServo_Feedback__current_pulses_us,  // get(index) function pointer
    transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__fetch_function__MoveServo_Feedback__current_pulses_us,  // fetch(index, &value) function pointer
    transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__assign_function__MoveServo_Feedback__current_pulses_us,  // assign(index, value) function pointer
    transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__resize_function__MoveServo_Feedback__current_pulses_us  // resize(index) function pointer
  },
  {
    "progress",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_Feedback, progress),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "estimated_remaining_s",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_Feedback, estimated_remaining_s),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "phase",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_Feedback, phase),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__MoveServo_Feedback_message_members = {
  "transformer_hw_servos__action",  // message namespace
  "MoveServo_Feedback",  // message name
  4,  // number of fields
  sizeof(transformer_hw_servos__action__MoveServo_Feedback),
  false,  // has_any_key_member_
  transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__MoveServo_Feedback_message_member_array,  // message members
  transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__MoveServo_Feedback_init_function,  // function to initialize message memory (memory has to be allocated)
  transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__MoveServo_Feedback_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__MoveServo_Feedback_message_type_support_handle = {
  0,
  &transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__MoveServo_Feedback_message_members,
  get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_Feedback__get_type_hash,
  &transformer_hw_servos__action__MoveServo_Feedback__get_type_description,
  &transformer_hw_servos__action__MoveServo_Feedback__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_transformer_hw_servos
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_Feedback)() {
  if (!transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__MoveServo_Feedback_message_type_support_handle.typesupport_identifier) {
    transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__MoveServo_Feedback_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &transformer_hw_servos__action__MoveServo_Feedback__rosidl_typesupport_introspection_c__MoveServo_Feedback_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__rosidl_typesupport_introspection_c.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `goal`
#include "transformer_hw_servos/action/move_servo.h"
// Member `goal`
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void transformer_hw_servos__action__MoveServo_SendGoal_Request__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  transformer_hw_servos__action__MoveServo_SendGoal_Request__init(message_memory);
}

void transformer_hw_servos__action__MoveServo_SendGoal_Request__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Request_fini_function(void * message_memory)
{
  transformer_hw_servos__action__MoveServo_SendGoal_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember transformer_hw_servos__action__MoveServo_SendGoal_Request__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Request_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_SendGoal_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "goal",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_SendGoal_Request, goal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers transformer_hw_servos__action__MoveServo_SendGoal_Request__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Request_message_members = {
  "transformer_hw_servos__action",  // message namespace
  "MoveServo_SendGoal_Request",  // message name
  2,  // number of fields
  sizeof(transformer_hw_servos__action__MoveServo_SendGoal_Request),
  false,  // has_any_key_member_
  transformer_hw_servos__action__MoveServo_SendGoal_Request__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Request_message_member_array,  // message members
  transformer_hw_servos__action__MoveServo_SendGoal_Request__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  transformer_hw_servos__action__MoveServo_SendGoal_Request__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t transformer_hw_servos__action__MoveServo_SendGoal_Request__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Request_message_type_support_handle = {
  0,
  &transformer_hw_servos__action__MoveServo_SendGoal_Request__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Request_message_members,
  get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_SendGoal_Request__get_type_hash,
  &transformer_hw_servos__action__MoveServo_SendGoal_Request__get_type_description,
  &transformer_hw_servos__action__MoveServo_SendGoal_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_transformer_hw_servos
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_SendGoal_Request)() {
  transformer_hw_servos__action__MoveServo_SendGoal_Request__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  transformer_hw_servos__action__MoveServo_SendGoal_Request__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_Goal)();
  if (!transformer_hw_servos__action__MoveServo_SendGoal_Request__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Request_message_type_support_handle.typesupport_identifier) {
    transformer_hw_servos__action__MoveServo_SendGoal_Request__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &transformer_hw_servos__action__MoveServo_SendGoal_Request__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__rosidl_typesupport_introspection_c.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void transformer_hw_servos__action__MoveServo_SendGoal_Response__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  transformer_hw_servos__action__MoveServo_SendGoal_Response__init(message_memory);
}

void transformer_hw_servos__action__MoveServo_SendGoal_Response__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Response_fini_function(void * message_memory)
{
  transformer_hw_servos__action__MoveServo_SendGoal_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember transformer_hw_servos__action__MoveServo_SendGoal_Response__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Response_message_member_array[2] = {
  {
    "accepted",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_SendGoal_Response, accepted),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_SendGoal_Response, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers transformer_hw_servos__action__MoveServo_SendGoal_Response__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Response_message_members = {
  "transformer_hw_servos__action",  // message namespace
  "MoveServo_SendGoal_Response",  // message name
  2,  // number of fields
  sizeof(transformer_hw_servos__action__MoveServo_SendGoal_Response),
  false,  // has_any_key_member_
  transformer_hw_servos__action__MoveServo_SendGoal_Response__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Response_message_member_array,  // message members
  transformer_hw_servos__action__MoveServo_SendGoal_Response__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  transformer_hw_servos__action__MoveServo_SendGoal_Response__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t transformer_hw_servos__action__MoveServo_SendGoal_Response__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Response_message_type_support_handle = {
  0,
  &transformer_hw_servos__action__MoveServo_SendGoal_Response__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Response_message_members,
  get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_SendGoal_Response__get_type_hash,
  &transformer_hw_servos__action__MoveServo_SendGoal_Response__get_type_description,
  &transformer_hw_servos__action__MoveServo_SendGoal_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_transformer_hw_servos
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_SendGoal_Response)() {
  transformer_hw_servos__action__MoveServo_SendGoal_Response__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!transformer_hw_servos__action__MoveServo_SendGoal_Response__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Response_message_type_support_handle.typesupport_identifier) {
    transformer_hw_servos__action__MoveServo_SendGoal_Response__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &transformer_hw_servos__action__MoveServo_SendGoal_Response__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__rosidl_typesupport_introspection_c.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
// already included above
// #include "transformer_hw_servos/action/move_servo.h"
// Member `request`
// Member `response`
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  transformer_hw_servos__action__MoveServo_SendGoal_Event__init(message_memory);
}

void transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Event_fini_function(void * message_memory)
{
  transformer_hw_servos__action__MoveServo_SendGoal_Event__fini(message_memory);
}

size_t transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__size_function__MoveServo_SendGoal_Event__request(
  const void * untyped_member)
{
  const transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence * member =
    (const transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__MoveServo_SendGoal_Event__request(
  const void * untyped_member, size_t index)
{
  const transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence * member =
    (const transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__MoveServo_SendGoal_Event__request(
  void * untyped_member, size_t index)
{
  transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence * member =
    (transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__fetch_function__MoveServo_SendGoal_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const transformer_hw_servos__action__MoveServo_SendGoal_Request * item =
    ((const transformer_hw_servos__action__MoveServo_SendGoal_Request *)
    transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__MoveServo_SendGoal_Event__request(untyped_member, index));
  transformer_hw_servos__action__MoveServo_SendGoal_Request * value =
    (transformer_hw_servos__action__MoveServo_SendGoal_Request *)(untyped_value);
  *value = *item;
}

void transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__assign_function__MoveServo_SendGoal_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  transformer_hw_servos__action__MoveServo_SendGoal_Request * item =
    ((transformer_hw_servos__action__MoveServo_SendGoal_Request *)
    transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__MoveServo_SendGoal_Event__request(untyped_member, index));
  const transformer_hw_servos__action__MoveServo_SendGoal_Request * value =
    (const transformer_hw_servos__action__MoveServo_SendGoal_Request *)(untyped_value);
  *item = *value;
}

bool transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__resize_function__MoveServo_SendGoal_Event__request(
  void * untyped_member, size_t size)
{
  transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence * member =
    (transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence *)(untyped_member);
  transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence__fini(member);
  return transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence__init(member, size);
}

size_t transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__size_function__MoveServo_SendGoal_Event__response(
  const void * untyped_member)
{
  const transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence * member =
    (const transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__MoveServo_SendGoal_Event__response(
  const void * untyped_member, size_t index)
{
  const transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence * member =
    (const transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__MoveServo_SendGoal_Event__response(
  void * untyped_member, size_t index)
{
  transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence * member =
    (transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__fetch_function__MoveServo_SendGoal_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const transformer_hw_servos__action__MoveServo_SendGoal_Response * item =
    ((const transformer_hw_servos__action__MoveServo_SendGoal_Response *)
    transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__MoveServo_SendGoal_Event__response(untyped_member, index));
  transformer_hw_servos__action__MoveServo_SendGoal_Response * value =
    (transformer_hw_servos__action__MoveServo_SendGoal_Response *)(untyped_value);
  *value = *item;
}

void transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__assign_function__MoveServo_SendGoal_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  transformer_hw_servos__action__MoveServo_SendGoal_Response * item =
    ((transformer_hw_servos__action__MoveServo_SendGoal_Response *)
    transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__MoveServo_SendGoal_Event__response(untyped_member, index));
  const transformer_hw_servos__action__MoveServo_SendGoal_Response * value =
    (const transformer_hw_servos__action__MoveServo_SendGoal_Response *)(untyped_value);
  *item = *value;
}

bool transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__resize_function__MoveServo_SendGoal_Event__response(
  void * untyped_member, size_t size)
{
  transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence * member =
    (transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence *)(untyped_member);
  transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence__fini(member);
  return transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_SendGoal_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_SendGoal_Event, request),  // bytes offset in struct
    NULL,  // default value
    transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__size_function__MoveServo_SendGoal_Event__request,  // size() function pointer
    transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__MoveServo_SendGoal_Event__request,  // get_const(index) function pointer
    transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__MoveServo_SendGoal_Event__request,  // get(index) function pointer
    transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__fetch_function__MoveServo_SendGoal_Event__request,  // fetch(index, &value) function pointer
    transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__assign_function__MoveServo_SendGoal_Event__request,  // assign(index, value) function pointer
    transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__resize_function__MoveServo_SendGoal_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_SendGoal_Event, response),  // bytes offset in struct
    NULL,  // default value
    transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__size_function__MoveServo_SendGoal_Event__response,  // size() function pointer
    transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__MoveServo_SendGoal_Event__response,  // get_const(index) function pointer
    transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__MoveServo_SendGoal_Event__response,  // get(index) function pointer
    transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__fetch_function__MoveServo_SendGoal_Event__response,  // fetch(index, &value) function pointer
    transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__assign_function__MoveServo_SendGoal_Event__response,  // assign(index, value) function pointer
    transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__resize_function__MoveServo_SendGoal_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Event_message_members = {
  "transformer_hw_servos__action",  // message namespace
  "MoveServo_SendGoal_Event",  // message name
  3,  // number of fields
  sizeof(transformer_hw_servos__action__MoveServo_SendGoal_Event),
  false,  // has_any_key_member_
  transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Event_message_member_array,  // message members
  transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Event_message_type_support_handle = {
  0,
  &transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Event_message_members,
  get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_SendGoal_Event__get_type_hash,
  &transformer_hw_servos__action__MoveServo_SendGoal_Event__get_type_description,
  &transformer_hw_servos__action__MoveServo_SendGoal_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_transformer_hw_servos
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_SendGoal_Event)() {
  transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_SendGoal_Request)();
  transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_SendGoal_Response)();
  if (!transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Event_message_type_support_handle.typesupport_identifier) {
    transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_SendGoal_service_members = {
  "transformer_hw_servos__action",  // service namespace
  "MoveServo_SendGoal",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Request_message_type_support_handle,
  NULL,  // response message
  // transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Response_message_type_support_handle
  NULL  // event_message
  // transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Response_message_type_support_handle
};


static rosidl_service_type_support_t transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_SendGoal_service_type_support_handle = {
  0,
  &transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_SendGoal_service_members,
  get_service_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_SendGoal_Request__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Request_message_type_support_handle,
  &transformer_hw_servos__action__MoveServo_SendGoal_Response__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Response_message_type_support_handle,
  &transformer_hw_servos__action__MoveServo_SendGoal_Event__rosidl_typesupport_introspection_c__MoveServo_SendGoal_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    transformer_hw_servos,
    action,
    MoveServo_SendGoal
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    transformer_hw_servos,
    action,
    MoveServo_SendGoal
  ),
  &transformer_hw_servos__action__MoveServo_SendGoal__get_type_hash,
  &transformer_hw_servos__action__MoveServo_SendGoal__get_type_description,
  &transformer_hw_servos__action__MoveServo_SendGoal__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_SendGoal_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_SendGoal_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_SendGoal_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_transformer_hw_servos
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_SendGoal)(void) {
  if (!transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_SendGoal_service_type_support_handle.typesupport_identifier) {
    transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_SendGoal_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_SendGoal_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_SendGoal_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_SendGoal_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_SendGoal_Event)()->data;
  }

  return &transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_SendGoal_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__rosidl_typesupport_introspection_c.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void transformer_hw_servos__action__MoveServo_GetResult_Request__rosidl_typesupport_introspection_c__MoveServo_GetResult_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  transformer_hw_servos__action__MoveServo_GetResult_Request__init(message_memory);
}

void transformer_hw_servos__action__MoveServo_GetResult_Request__rosidl_typesupport_introspection_c__MoveServo_GetResult_Request_fini_function(void * message_memory)
{
  transformer_hw_servos__action__MoveServo_GetResult_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember transformer_hw_servos__action__MoveServo_GetResult_Request__rosidl_typesupport_introspection_c__MoveServo_GetResult_Request_message_member_array[1] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_GetResult_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers transformer_hw_servos__action__MoveServo_GetResult_Request__rosidl_typesupport_introspection_c__MoveServo_GetResult_Request_message_members = {
  "transformer_hw_servos__action",  // message namespace
  "MoveServo_GetResult_Request",  // message name
  1,  // number of fields
  sizeof(transformer_hw_servos__action__MoveServo_GetResult_Request),
  false,  // has_any_key_member_
  transformer_hw_servos__action__MoveServo_GetResult_Request__rosidl_typesupport_introspection_c__MoveServo_GetResult_Request_message_member_array,  // message members
  transformer_hw_servos__action__MoveServo_GetResult_Request__rosidl_typesupport_introspection_c__MoveServo_GetResult_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  transformer_hw_servos__action__MoveServo_GetResult_Request__rosidl_typesupport_introspection_c__MoveServo_GetResult_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t transformer_hw_servos__action__MoveServo_GetResult_Request__rosidl_typesupport_introspection_c__MoveServo_GetResult_Request_message_type_support_handle = {
  0,
  &transformer_hw_servos__action__MoveServo_GetResult_Request__rosidl_typesupport_introspection_c__MoveServo_GetResult_Request_message_members,
  get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_GetResult_Request__get_type_hash,
  &transformer_hw_servos__action__MoveServo_GetResult_Request__get_type_description,
  &transformer_hw_servos__action__MoveServo_GetResult_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_transformer_hw_servos
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_GetResult_Request)() {
  transformer_hw_servos__action__MoveServo_GetResult_Request__rosidl_typesupport_introspection_c__MoveServo_GetResult_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  if (!transformer_hw_servos__action__MoveServo_GetResult_Request__rosidl_typesupport_introspection_c__MoveServo_GetResult_Request_message_type_support_handle.typesupport_identifier) {
    transformer_hw_servos__action__MoveServo_GetResult_Request__rosidl_typesupport_introspection_c__MoveServo_GetResult_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &transformer_hw_servos__action__MoveServo_GetResult_Request__rosidl_typesupport_introspection_c__MoveServo_GetResult_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__rosidl_typesupport_introspection_c.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"


// Include directives for member types
// Member `result`
// already included above
// #include "transformer_hw_servos/action/move_servo.h"
// Member `result`
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void transformer_hw_servos__action__MoveServo_GetResult_Response__rosidl_typesupport_introspection_c__MoveServo_GetResult_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  transformer_hw_servos__action__MoveServo_GetResult_Response__init(message_memory);
}

void transformer_hw_servos__action__MoveServo_GetResult_Response__rosidl_typesupport_introspection_c__MoveServo_GetResult_Response_fini_function(void * message_memory)
{
  transformer_hw_servos__action__MoveServo_GetResult_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember transformer_hw_servos__action__MoveServo_GetResult_Response__rosidl_typesupport_introspection_c__MoveServo_GetResult_Response_message_member_array[2] = {
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_GetResult_Response, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_GetResult_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers transformer_hw_servos__action__MoveServo_GetResult_Response__rosidl_typesupport_introspection_c__MoveServo_GetResult_Response_message_members = {
  "transformer_hw_servos__action",  // message namespace
  "MoveServo_GetResult_Response",  // message name
  2,  // number of fields
  sizeof(transformer_hw_servos__action__MoveServo_GetResult_Response),
  false,  // has_any_key_member_
  transformer_hw_servos__action__MoveServo_GetResult_Response__rosidl_typesupport_introspection_c__MoveServo_GetResult_Response_message_member_array,  // message members
  transformer_hw_servos__action__MoveServo_GetResult_Response__rosidl_typesupport_introspection_c__MoveServo_GetResult_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  transformer_hw_servos__action__MoveServo_GetResult_Response__rosidl_typesupport_introspection_c__MoveServo_GetResult_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t transformer_hw_servos__action__MoveServo_GetResult_Response__rosidl_typesupport_introspection_c__MoveServo_GetResult_Response_message_type_support_handle = {
  0,
  &transformer_hw_servos__action__MoveServo_GetResult_Response__rosidl_typesupport_introspection_c__MoveServo_GetResult_Response_message_members,
  get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_GetResult_Response__get_type_hash,
  &transformer_hw_servos__action__MoveServo_GetResult_Response__get_type_description,
  &transformer_hw_servos__action__MoveServo_GetResult_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_transformer_hw_servos
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_GetResult_Response)() {
  transformer_hw_servos__action__MoveServo_GetResult_Response__rosidl_typesupport_introspection_c__MoveServo_GetResult_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_Result)();
  if (!transformer_hw_servos__action__MoveServo_GetResult_Response__rosidl_typesupport_introspection_c__MoveServo_GetResult_Response_message_type_support_handle.typesupport_identifier) {
    transformer_hw_servos__action__MoveServo_GetResult_Response__rosidl_typesupport_introspection_c__MoveServo_GetResult_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &transformer_hw_servos__action__MoveServo_GetResult_Response__rosidl_typesupport_introspection_c__MoveServo_GetResult_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__rosidl_typesupport_introspection_c.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"


// Include directives for member types
// Member `info`
// already included above
// #include "service_msgs/msg/service_event_info.h"
// Member `info`
// already included above
// #include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
// already included above
// #include "transformer_hw_servos/action/move_servo.h"
// Member `request`
// Member `response`
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__MoveServo_GetResult_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  transformer_hw_servos__action__MoveServo_GetResult_Event__init(message_memory);
}

void transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__MoveServo_GetResult_Event_fini_function(void * message_memory)
{
  transformer_hw_servos__action__MoveServo_GetResult_Event__fini(message_memory);
}

size_t transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__size_function__MoveServo_GetResult_Event__request(
  const void * untyped_member)
{
  const transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence * member =
    (const transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__MoveServo_GetResult_Event__request(
  const void * untyped_member, size_t index)
{
  const transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence * member =
    (const transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__get_function__MoveServo_GetResult_Event__request(
  void * untyped_member, size_t index)
{
  transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence * member =
    (transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__fetch_function__MoveServo_GetResult_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const transformer_hw_servos__action__MoveServo_GetResult_Request * item =
    ((const transformer_hw_servos__action__MoveServo_GetResult_Request *)
    transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__MoveServo_GetResult_Event__request(untyped_member, index));
  transformer_hw_servos__action__MoveServo_GetResult_Request * value =
    (transformer_hw_servos__action__MoveServo_GetResult_Request *)(untyped_value);
  *value = *item;
}

void transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__assign_function__MoveServo_GetResult_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  transformer_hw_servos__action__MoveServo_GetResult_Request * item =
    ((transformer_hw_servos__action__MoveServo_GetResult_Request *)
    transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__get_function__MoveServo_GetResult_Event__request(untyped_member, index));
  const transformer_hw_servos__action__MoveServo_GetResult_Request * value =
    (const transformer_hw_servos__action__MoveServo_GetResult_Request *)(untyped_value);
  *item = *value;
}

bool transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__resize_function__MoveServo_GetResult_Event__request(
  void * untyped_member, size_t size)
{
  transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence * member =
    (transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence *)(untyped_member);
  transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence__fini(member);
  return transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence__init(member, size);
}

size_t transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__size_function__MoveServo_GetResult_Event__response(
  const void * untyped_member)
{
  const transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence * member =
    (const transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__MoveServo_GetResult_Event__response(
  const void * untyped_member, size_t index)
{
  const transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence * member =
    (const transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__get_function__MoveServo_GetResult_Event__response(
  void * untyped_member, size_t index)
{
  transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence * member =
    (transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__fetch_function__MoveServo_GetResult_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const transformer_hw_servos__action__MoveServo_GetResult_Response * item =
    ((const transformer_hw_servos__action__MoveServo_GetResult_Response *)
    transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__MoveServo_GetResult_Event__response(untyped_member, index));
  transformer_hw_servos__action__MoveServo_GetResult_Response * value =
    (transformer_hw_servos__action__MoveServo_GetResult_Response *)(untyped_value);
  *value = *item;
}

void transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__assign_function__MoveServo_GetResult_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  transformer_hw_servos__action__MoveServo_GetResult_Response * item =
    ((transformer_hw_servos__action__MoveServo_GetResult_Response *)
    transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__get_function__MoveServo_GetResult_Event__response(untyped_member, index));
  const transformer_hw_servos__action__MoveServo_GetResult_Response * value =
    (const transformer_hw_servos__action__MoveServo_GetResult_Response *)(untyped_value);
  *item = *value;
}

bool transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__resize_function__MoveServo_GetResult_Event__response(
  void * untyped_member, size_t size)
{
  transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence * member =
    (transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence *)(untyped_member);
  transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence__fini(member);
  return transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__MoveServo_GetResult_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_GetResult_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_GetResult_Event, request),  // bytes offset in struct
    NULL,  // default value
    transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__size_function__MoveServo_GetResult_Event__request,  // size() function pointer
    transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__MoveServo_GetResult_Event__request,  // get_const(index) function pointer
    transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__get_function__MoveServo_GetResult_Event__request,  // get(index) function pointer
    transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__fetch_function__MoveServo_GetResult_Event__request,  // fetch(index, &value) function pointer
    transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__assign_function__MoveServo_GetResult_Event__request,  // assign(index, value) function pointer
    transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__resize_function__MoveServo_GetResult_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_GetResult_Event, response),  // bytes offset in struct
    NULL,  // default value
    transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__size_function__MoveServo_GetResult_Event__response,  // size() function pointer
    transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__MoveServo_GetResult_Event__response,  // get_const(index) function pointer
    transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__get_function__MoveServo_GetResult_Event__response,  // get(index) function pointer
    transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__fetch_function__MoveServo_GetResult_Event__response,  // fetch(index, &value) function pointer
    transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__assign_function__MoveServo_GetResult_Event__response,  // assign(index, value) function pointer
    transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__resize_function__MoveServo_GetResult_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__MoveServo_GetResult_Event_message_members = {
  "transformer_hw_servos__action",  // message namespace
  "MoveServo_GetResult_Event",  // message name
  3,  // number of fields
  sizeof(transformer_hw_servos__action__MoveServo_GetResult_Event),
  false,  // has_any_key_member_
  transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__MoveServo_GetResult_Event_message_member_array,  // message members
  transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__MoveServo_GetResult_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__MoveServo_GetResult_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__MoveServo_GetResult_Event_message_type_support_handle = {
  0,
  &transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__MoveServo_GetResult_Event_message_members,
  get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_GetResult_Event__get_type_hash,
  &transformer_hw_servos__action__MoveServo_GetResult_Event__get_type_description,
  &transformer_hw_servos__action__MoveServo_GetResult_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_transformer_hw_servos
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_GetResult_Event)() {
  transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__MoveServo_GetResult_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__MoveServo_GetResult_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_GetResult_Request)();
  transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__MoveServo_GetResult_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_GetResult_Response)();
  if (!transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__MoveServo_GetResult_Event_message_type_support_handle.typesupport_identifier) {
    transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__MoveServo_GetResult_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__MoveServo_GetResult_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_GetResult_service_members = {
  "transformer_hw_servos__action",  // service namespace
  "MoveServo_GetResult",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_GetResult_Request_message_type_support_handle,
  NULL,  // response message
  // transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_GetResult_Response_message_type_support_handle
  NULL  // event_message
  // transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_GetResult_Response_message_type_support_handle
};


static rosidl_service_type_support_t transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_GetResult_service_type_support_handle = {
  0,
  &transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_GetResult_service_members,
  get_service_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_GetResult_Request__rosidl_typesupport_introspection_c__MoveServo_GetResult_Request_message_type_support_handle,
  &transformer_hw_servos__action__MoveServo_GetResult_Response__rosidl_typesupport_introspection_c__MoveServo_GetResult_Response_message_type_support_handle,
  &transformer_hw_servos__action__MoveServo_GetResult_Event__rosidl_typesupport_introspection_c__MoveServo_GetResult_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    transformer_hw_servos,
    action,
    MoveServo_GetResult
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    transformer_hw_servos,
    action,
    MoveServo_GetResult
  ),
  &transformer_hw_servos__action__MoveServo_GetResult__get_type_hash,
  &transformer_hw_servos__action__MoveServo_GetResult__get_type_description,
  &transformer_hw_servos__action__MoveServo_GetResult__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_GetResult_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_GetResult_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_GetResult_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_transformer_hw_servos
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_GetResult)(void) {
  if (!transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_GetResult_service_type_support_handle.typesupport_identifier) {
    transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_GetResult_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_GetResult_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_GetResult_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_GetResult_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_GetResult_Event)()->data;
  }

  return &transformer_hw_servos__action__detail__move_servo__rosidl_typesupport_introspection_c__MoveServo_GetResult_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__rosidl_typesupport_introspection_c.h"
// already included above
// #include "transformer_hw_servos/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `feedback`
// already included above
// #include "transformer_hw_servos/action/move_servo.h"
// Member `feedback`
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void transformer_hw_servos__action__MoveServo_FeedbackMessage__rosidl_typesupport_introspection_c__MoveServo_FeedbackMessage_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  transformer_hw_servos__action__MoveServo_FeedbackMessage__init(message_memory);
}

void transformer_hw_servos__action__MoveServo_FeedbackMessage__rosidl_typesupport_introspection_c__MoveServo_FeedbackMessage_fini_function(void * message_memory)
{
  transformer_hw_servos__action__MoveServo_FeedbackMessage__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember transformer_hw_servos__action__MoveServo_FeedbackMessage__rosidl_typesupport_introspection_c__MoveServo_FeedbackMessage_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_FeedbackMessage, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "feedback",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(transformer_hw_servos__action__MoveServo_FeedbackMessage, feedback),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers transformer_hw_servos__action__MoveServo_FeedbackMessage__rosidl_typesupport_introspection_c__MoveServo_FeedbackMessage_message_members = {
  "transformer_hw_servos__action",  // message namespace
  "MoveServo_FeedbackMessage",  // message name
  2,  // number of fields
  sizeof(transformer_hw_servos__action__MoveServo_FeedbackMessage),
  false,  // has_any_key_member_
  transformer_hw_servos__action__MoveServo_FeedbackMessage__rosidl_typesupport_introspection_c__MoveServo_FeedbackMessage_message_member_array,  // message members
  transformer_hw_servos__action__MoveServo_FeedbackMessage__rosidl_typesupport_introspection_c__MoveServo_FeedbackMessage_init_function,  // function to initialize message memory (memory has to be allocated)
  transformer_hw_servos__action__MoveServo_FeedbackMessage__rosidl_typesupport_introspection_c__MoveServo_FeedbackMessage_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t transformer_hw_servos__action__MoveServo_FeedbackMessage__rosidl_typesupport_introspection_c__MoveServo_FeedbackMessage_message_type_support_handle = {
  0,
  &transformer_hw_servos__action__MoveServo_FeedbackMessage__rosidl_typesupport_introspection_c__MoveServo_FeedbackMessage_message_members,
  get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_FeedbackMessage__get_type_hash,
  &transformer_hw_servos__action__MoveServo_FeedbackMessage__get_type_description,
  &transformer_hw_servos__action__MoveServo_FeedbackMessage__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_transformer_hw_servos
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_FeedbackMessage)() {
  transformer_hw_servos__action__MoveServo_FeedbackMessage__rosidl_typesupport_introspection_c__MoveServo_FeedbackMessage_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  transformer_hw_servos__action__MoveServo_FeedbackMessage__rosidl_typesupport_introspection_c__MoveServo_FeedbackMessage_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_Feedback)();
  if (!transformer_hw_servos__action__MoveServo_FeedbackMessage__rosidl_typesupport_introspection_c__MoveServo_FeedbackMessage_message_type_support_handle.typesupport_identifier) {
    transformer_hw_servos__action__MoveServo_FeedbackMessage__rosidl_typesupport_introspection_c__MoveServo_FeedbackMessage_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &transformer_hw_servos__action__MoveServo_FeedbackMessage__rosidl_typesupport_introspection_c__MoveServo_FeedbackMessage_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
