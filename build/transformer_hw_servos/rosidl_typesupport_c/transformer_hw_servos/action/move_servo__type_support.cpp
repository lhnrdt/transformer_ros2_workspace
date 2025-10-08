// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from transformer_hw_servos:action/MoveServo.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "transformer_hw_servos/action/detail/move_servo__struct.h"
#include "transformer_hw_servos/action/detail/move_servo__type_support.h"
#include "transformer_hw_servos/action/detail/move_servo__functions.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveServo_Goal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_Goal_type_support_ids_t;

static const _MoveServo_Goal_type_support_ids_t _MoveServo_Goal_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveServo_Goal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveServo_Goal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveServo_Goal_type_support_symbol_names_t _MoveServo_Goal_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_servos, action, MoveServo_Goal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_Goal)),
  }
};

typedef struct _MoveServo_Goal_type_support_data_t
{
  void * data[2];
} _MoveServo_Goal_type_support_data_t;

static _MoveServo_Goal_type_support_data_t _MoveServo_Goal_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveServo_Goal_message_typesupport_map = {
  2,
  "transformer_hw_servos",
  &_MoveServo_Goal_message_typesupport_ids.typesupport_identifier[0],
  &_MoveServo_Goal_message_typesupport_symbol_names.symbol_name[0],
  &_MoveServo_Goal_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveServo_Goal_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_Goal_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_Goal__get_type_hash,
  &transformer_hw_servos__action__MoveServo_Goal__get_type_description,
  &transformer_hw_servos__action__MoveServo_Goal__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_servos, action, MoveServo_Goal)() {
  return &::transformer_hw_servos::action::rosidl_typesupport_c::MoveServo_Goal_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__type_support.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveServo_Result_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_Result_type_support_ids_t;

static const _MoveServo_Result_type_support_ids_t _MoveServo_Result_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveServo_Result_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveServo_Result_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveServo_Result_type_support_symbol_names_t _MoveServo_Result_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_servos, action, MoveServo_Result)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_Result)),
  }
};

typedef struct _MoveServo_Result_type_support_data_t
{
  void * data[2];
} _MoveServo_Result_type_support_data_t;

static _MoveServo_Result_type_support_data_t _MoveServo_Result_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveServo_Result_message_typesupport_map = {
  2,
  "transformer_hw_servos",
  &_MoveServo_Result_message_typesupport_ids.typesupport_identifier[0],
  &_MoveServo_Result_message_typesupport_symbol_names.symbol_name[0],
  &_MoveServo_Result_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveServo_Result_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_Result_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_Result__get_type_hash,
  &transformer_hw_servos__action__MoveServo_Result__get_type_description,
  &transformer_hw_servos__action__MoveServo_Result__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_servos, action, MoveServo_Result)() {
  return &::transformer_hw_servos::action::rosidl_typesupport_c::MoveServo_Result_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__type_support.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveServo_Feedback_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_Feedback_type_support_ids_t;

static const _MoveServo_Feedback_type_support_ids_t _MoveServo_Feedback_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveServo_Feedback_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveServo_Feedback_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveServo_Feedback_type_support_symbol_names_t _MoveServo_Feedback_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_servos, action, MoveServo_Feedback)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_Feedback)),
  }
};

typedef struct _MoveServo_Feedback_type_support_data_t
{
  void * data[2];
} _MoveServo_Feedback_type_support_data_t;

static _MoveServo_Feedback_type_support_data_t _MoveServo_Feedback_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveServo_Feedback_message_typesupport_map = {
  2,
  "transformer_hw_servos",
  &_MoveServo_Feedback_message_typesupport_ids.typesupport_identifier[0],
  &_MoveServo_Feedback_message_typesupport_symbol_names.symbol_name[0],
  &_MoveServo_Feedback_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveServo_Feedback_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_Feedback_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_Feedback__get_type_hash,
  &transformer_hw_servos__action__MoveServo_Feedback__get_type_description,
  &transformer_hw_servos__action__MoveServo_Feedback__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_servos, action, MoveServo_Feedback)() {
  return &::transformer_hw_servos::action::rosidl_typesupport_c::MoveServo_Feedback_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__type_support.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveServo_SendGoal_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_SendGoal_Request_type_support_ids_t;

static const _MoveServo_SendGoal_Request_type_support_ids_t _MoveServo_SendGoal_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveServo_SendGoal_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveServo_SendGoal_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveServo_SendGoal_Request_type_support_symbol_names_t _MoveServo_SendGoal_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_servos, action, MoveServo_SendGoal_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_SendGoal_Request)),
  }
};

typedef struct _MoveServo_SendGoal_Request_type_support_data_t
{
  void * data[2];
} _MoveServo_SendGoal_Request_type_support_data_t;

static _MoveServo_SendGoal_Request_type_support_data_t _MoveServo_SendGoal_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveServo_SendGoal_Request_message_typesupport_map = {
  2,
  "transformer_hw_servos",
  &_MoveServo_SendGoal_Request_message_typesupport_ids.typesupport_identifier[0],
  &_MoveServo_SendGoal_Request_message_typesupport_symbol_names.symbol_name[0],
  &_MoveServo_SendGoal_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveServo_SendGoal_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_SendGoal_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_SendGoal_Request__get_type_hash,
  &transformer_hw_servos__action__MoveServo_SendGoal_Request__get_type_description,
  &transformer_hw_servos__action__MoveServo_SendGoal_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_servos, action, MoveServo_SendGoal_Request)() {
  return &::transformer_hw_servos::action::rosidl_typesupport_c::MoveServo_SendGoal_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__type_support.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveServo_SendGoal_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_SendGoal_Response_type_support_ids_t;

static const _MoveServo_SendGoal_Response_type_support_ids_t _MoveServo_SendGoal_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveServo_SendGoal_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveServo_SendGoal_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveServo_SendGoal_Response_type_support_symbol_names_t _MoveServo_SendGoal_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_servos, action, MoveServo_SendGoal_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_SendGoal_Response)),
  }
};

typedef struct _MoveServo_SendGoal_Response_type_support_data_t
{
  void * data[2];
} _MoveServo_SendGoal_Response_type_support_data_t;

static _MoveServo_SendGoal_Response_type_support_data_t _MoveServo_SendGoal_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveServo_SendGoal_Response_message_typesupport_map = {
  2,
  "transformer_hw_servos",
  &_MoveServo_SendGoal_Response_message_typesupport_ids.typesupport_identifier[0],
  &_MoveServo_SendGoal_Response_message_typesupport_symbol_names.symbol_name[0],
  &_MoveServo_SendGoal_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveServo_SendGoal_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_SendGoal_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_SendGoal_Response__get_type_hash,
  &transformer_hw_servos__action__MoveServo_SendGoal_Response__get_type_description,
  &transformer_hw_servos__action__MoveServo_SendGoal_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_servos, action, MoveServo_SendGoal_Response)() {
  return &::transformer_hw_servos::action::rosidl_typesupport_c::MoveServo_SendGoal_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__type_support.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveServo_SendGoal_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_SendGoal_Event_type_support_ids_t;

static const _MoveServo_SendGoal_Event_type_support_ids_t _MoveServo_SendGoal_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveServo_SendGoal_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveServo_SendGoal_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveServo_SendGoal_Event_type_support_symbol_names_t _MoveServo_SendGoal_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_servos, action, MoveServo_SendGoal_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_SendGoal_Event)),
  }
};

typedef struct _MoveServo_SendGoal_Event_type_support_data_t
{
  void * data[2];
} _MoveServo_SendGoal_Event_type_support_data_t;

static _MoveServo_SendGoal_Event_type_support_data_t _MoveServo_SendGoal_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveServo_SendGoal_Event_message_typesupport_map = {
  2,
  "transformer_hw_servos",
  &_MoveServo_SendGoal_Event_message_typesupport_ids.typesupport_identifier[0],
  &_MoveServo_SendGoal_Event_message_typesupport_symbol_names.symbol_name[0],
  &_MoveServo_SendGoal_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveServo_SendGoal_Event_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_SendGoal_Event_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_SendGoal_Event__get_type_hash,
  &transformer_hw_servos__action__MoveServo_SendGoal_Event__get_type_description,
  &transformer_hw_servos__action__MoveServo_SendGoal_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_servos, action, MoveServo_SendGoal_Event)() {
  return &::transformer_hw_servos::action::rosidl_typesupport_c::MoveServo_SendGoal_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
#include "service_msgs/msg/service_event_info.h"
#include "builtin_interfaces/msg/time.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_c
{
typedef struct _MoveServo_SendGoal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_SendGoal_type_support_ids_t;

static const _MoveServo_SendGoal_type_support_ids_t _MoveServo_SendGoal_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveServo_SendGoal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveServo_SendGoal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveServo_SendGoal_type_support_symbol_names_t _MoveServo_SendGoal_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_servos, action, MoveServo_SendGoal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_SendGoal)),
  }
};

typedef struct _MoveServo_SendGoal_type_support_data_t
{
  void * data[2];
} _MoveServo_SendGoal_type_support_data_t;

static _MoveServo_SendGoal_type_support_data_t _MoveServo_SendGoal_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveServo_SendGoal_service_typesupport_map = {
  2,
  "transformer_hw_servos",
  &_MoveServo_SendGoal_service_typesupport_ids.typesupport_identifier[0],
  &_MoveServo_SendGoal_service_typesupport_symbol_names.symbol_name[0],
  &_MoveServo_SendGoal_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t MoveServo_SendGoal_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_SendGoal_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
  &MoveServo_SendGoal_Request_message_type_support_handle,
  &MoveServo_SendGoal_Response_message_type_support_handle,
  &MoveServo_SendGoal_Event_message_type_support_handle,
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

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_servos, action, MoveServo_SendGoal)() {
  return &::transformer_hw_servos::action::rosidl_typesupport_c::MoveServo_SendGoal_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__type_support.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveServo_GetResult_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_GetResult_Request_type_support_ids_t;

static const _MoveServo_GetResult_Request_type_support_ids_t _MoveServo_GetResult_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveServo_GetResult_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveServo_GetResult_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveServo_GetResult_Request_type_support_symbol_names_t _MoveServo_GetResult_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_servos, action, MoveServo_GetResult_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_GetResult_Request)),
  }
};

typedef struct _MoveServo_GetResult_Request_type_support_data_t
{
  void * data[2];
} _MoveServo_GetResult_Request_type_support_data_t;

static _MoveServo_GetResult_Request_type_support_data_t _MoveServo_GetResult_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveServo_GetResult_Request_message_typesupport_map = {
  2,
  "transformer_hw_servos",
  &_MoveServo_GetResult_Request_message_typesupport_ids.typesupport_identifier[0],
  &_MoveServo_GetResult_Request_message_typesupport_symbol_names.symbol_name[0],
  &_MoveServo_GetResult_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveServo_GetResult_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_GetResult_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_GetResult_Request__get_type_hash,
  &transformer_hw_servos__action__MoveServo_GetResult_Request__get_type_description,
  &transformer_hw_servos__action__MoveServo_GetResult_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_servos, action, MoveServo_GetResult_Request)() {
  return &::transformer_hw_servos::action::rosidl_typesupport_c::MoveServo_GetResult_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__type_support.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveServo_GetResult_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_GetResult_Response_type_support_ids_t;

static const _MoveServo_GetResult_Response_type_support_ids_t _MoveServo_GetResult_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveServo_GetResult_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveServo_GetResult_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveServo_GetResult_Response_type_support_symbol_names_t _MoveServo_GetResult_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_servos, action, MoveServo_GetResult_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_GetResult_Response)),
  }
};

typedef struct _MoveServo_GetResult_Response_type_support_data_t
{
  void * data[2];
} _MoveServo_GetResult_Response_type_support_data_t;

static _MoveServo_GetResult_Response_type_support_data_t _MoveServo_GetResult_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveServo_GetResult_Response_message_typesupport_map = {
  2,
  "transformer_hw_servos",
  &_MoveServo_GetResult_Response_message_typesupport_ids.typesupport_identifier[0],
  &_MoveServo_GetResult_Response_message_typesupport_symbol_names.symbol_name[0],
  &_MoveServo_GetResult_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveServo_GetResult_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_GetResult_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_GetResult_Response__get_type_hash,
  &transformer_hw_servos__action__MoveServo_GetResult_Response__get_type_description,
  &transformer_hw_servos__action__MoveServo_GetResult_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_servos, action, MoveServo_GetResult_Response)() {
  return &::transformer_hw_servos::action::rosidl_typesupport_c::MoveServo_GetResult_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__type_support.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveServo_GetResult_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_GetResult_Event_type_support_ids_t;

static const _MoveServo_GetResult_Event_type_support_ids_t _MoveServo_GetResult_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveServo_GetResult_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveServo_GetResult_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveServo_GetResult_Event_type_support_symbol_names_t _MoveServo_GetResult_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_servos, action, MoveServo_GetResult_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_GetResult_Event)),
  }
};

typedef struct _MoveServo_GetResult_Event_type_support_data_t
{
  void * data[2];
} _MoveServo_GetResult_Event_type_support_data_t;

static _MoveServo_GetResult_Event_type_support_data_t _MoveServo_GetResult_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveServo_GetResult_Event_message_typesupport_map = {
  2,
  "transformer_hw_servos",
  &_MoveServo_GetResult_Event_message_typesupport_ids.typesupport_identifier[0],
  &_MoveServo_GetResult_Event_message_typesupport_symbol_names.symbol_name[0],
  &_MoveServo_GetResult_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveServo_GetResult_Event_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_GetResult_Event_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_GetResult_Event__get_type_hash,
  &transformer_hw_servos__action__MoveServo_GetResult_Event__get_type_description,
  &transformer_hw_servos__action__MoveServo_GetResult_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_servos, action, MoveServo_GetResult_Event)() {
  return &::transformer_hw_servos::action::rosidl_typesupport_c::MoveServo_GetResult_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "service_msgs/msg/service_event_info.h"
// already included above
// #include "builtin_interfaces/msg/time.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_c
{
typedef struct _MoveServo_GetResult_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_GetResult_type_support_ids_t;

static const _MoveServo_GetResult_type_support_ids_t _MoveServo_GetResult_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveServo_GetResult_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveServo_GetResult_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveServo_GetResult_type_support_symbol_names_t _MoveServo_GetResult_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_servos, action, MoveServo_GetResult)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_GetResult)),
  }
};

typedef struct _MoveServo_GetResult_type_support_data_t
{
  void * data[2];
} _MoveServo_GetResult_type_support_data_t;

static _MoveServo_GetResult_type_support_data_t _MoveServo_GetResult_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveServo_GetResult_service_typesupport_map = {
  2,
  "transformer_hw_servos",
  &_MoveServo_GetResult_service_typesupport_ids.typesupport_identifier[0],
  &_MoveServo_GetResult_service_typesupport_symbol_names.symbol_name[0],
  &_MoveServo_GetResult_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t MoveServo_GetResult_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_GetResult_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
  &MoveServo_GetResult_Request_message_type_support_handle,
  &MoveServo_GetResult_Response_message_type_support_handle,
  &MoveServo_GetResult_Event_message_type_support_handle,
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

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_servos, action, MoveServo_GetResult)() {
  return &::transformer_hw_servos::action::rosidl_typesupport_c::MoveServo_GetResult_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__type_support.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveServo_FeedbackMessage_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_FeedbackMessage_type_support_ids_t;

static const _MoveServo_FeedbackMessage_type_support_ids_t _MoveServo_FeedbackMessage_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveServo_FeedbackMessage_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveServo_FeedbackMessage_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveServo_FeedbackMessage_type_support_symbol_names_t _MoveServo_FeedbackMessage_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_servos, action, MoveServo_FeedbackMessage)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_servos, action, MoveServo_FeedbackMessage)),
  }
};

typedef struct _MoveServo_FeedbackMessage_type_support_data_t
{
  void * data[2];
} _MoveServo_FeedbackMessage_type_support_data_t;

static _MoveServo_FeedbackMessage_type_support_data_t _MoveServo_FeedbackMessage_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveServo_FeedbackMessage_message_typesupport_map = {
  2,
  "transformer_hw_servos",
  &_MoveServo_FeedbackMessage_message_typesupport_ids.typesupport_identifier[0],
  &_MoveServo_FeedbackMessage_message_typesupport_symbol_names.symbol_name[0],
  &_MoveServo_FeedbackMessage_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveServo_FeedbackMessage_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_FeedbackMessage_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_FeedbackMessage__get_type_hash,
  &transformer_hw_servos__action__MoveServo_FeedbackMessage__get_type_description,
  &transformer_hw_servos__action__MoveServo_FeedbackMessage__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_servos

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_servos, action, MoveServo_FeedbackMessage)() {
  return &::transformer_hw_servos::action::rosidl_typesupport_c::MoveServo_FeedbackMessage_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

#include "action_msgs/msg/goal_status_array.h"
#include "action_msgs/srv/cancel_goal.h"
#include "transformer_hw_servos/action/move_servo.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__type_support.h"

static rosidl_action_type_support_t _transformer_hw_servos__action__MoveServo__typesupport_c = {
  NULL, NULL, NULL, NULL, NULL,
  &transformer_hw_servos__action__MoveServo__get_type_hash,
  &transformer_hw_servos__action__MoveServo__get_type_description,
  &transformer_hw_servos__action__MoveServo__get_type_description_sources,
};

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_action_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__ACTION_SYMBOL_NAME(
  rosidl_typesupport_c, transformer_hw_servos, action, MoveServo)()
{
  // Thread-safe by always writing the same values to the static struct
  _transformer_hw_servos__action__MoveServo__typesupport_c.goal_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, transformer_hw_servos, action, MoveServo_SendGoal)();
  _transformer_hw_servos__action__MoveServo__typesupport_c.result_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, transformer_hw_servos, action, MoveServo_GetResult)();
  _transformer_hw_servos__action__MoveServo__typesupport_c.cancel_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, action_msgs, srv, CancelGoal)();
  _transformer_hw_servos__action__MoveServo__typesupport_c.feedback_message_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, transformer_hw_servos, action, MoveServo_FeedbackMessage)();
  _transformer_hw_servos__action__MoveServo__typesupport_c.status_message_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, action_msgs, msg, GoalStatusArray)();

  return &_transformer_hw_servos__action__MoveServo__typesupport_c;
}

#ifdef __cplusplus
}
#endif
