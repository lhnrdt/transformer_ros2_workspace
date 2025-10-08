// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from transformer_hw_actuators:action/MoveActuator.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "transformer_hw_actuators/action/detail/move_actuator__struct.h"
#include "transformer_hw_actuators/action/detail/move_actuator__type_support.h"
#include "transformer_hw_actuators/action/detail/move_actuator__functions.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_actuators
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveActuator_Goal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveActuator_Goal_type_support_ids_t;

static const _MoveActuator_Goal_type_support_ids_t _MoveActuator_Goal_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveActuator_Goal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveActuator_Goal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveActuator_Goal_type_support_symbol_names_t _MoveActuator_Goal_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_actuators, action, MoveActuator_Goal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_actuators, action, MoveActuator_Goal)),
  }
};

typedef struct _MoveActuator_Goal_type_support_data_t
{
  void * data[2];
} _MoveActuator_Goal_type_support_data_t;

static _MoveActuator_Goal_type_support_data_t _MoveActuator_Goal_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveActuator_Goal_message_typesupport_map = {
  2,
  "transformer_hw_actuators",
  &_MoveActuator_Goal_message_typesupport_ids.typesupport_identifier[0],
  &_MoveActuator_Goal_message_typesupport_symbol_names.symbol_name[0],
  &_MoveActuator_Goal_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveActuator_Goal_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveActuator_Goal_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_actuators__action__MoveActuator_Goal__get_type_hash,
  &transformer_hw_actuators__action__MoveActuator_Goal__get_type_description,
  &transformer_hw_actuators__action__MoveActuator_Goal__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_actuators

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_actuators, action, MoveActuator_Goal)() {
  return &::transformer_hw_actuators::action::rosidl_typesupport_c::MoveActuator_Goal_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__type_support.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__functions.h"
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

namespace transformer_hw_actuators
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveActuator_Result_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveActuator_Result_type_support_ids_t;

static const _MoveActuator_Result_type_support_ids_t _MoveActuator_Result_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveActuator_Result_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveActuator_Result_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveActuator_Result_type_support_symbol_names_t _MoveActuator_Result_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_actuators, action, MoveActuator_Result)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_actuators, action, MoveActuator_Result)),
  }
};

typedef struct _MoveActuator_Result_type_support_data_t
{
  void * data[2];
} _MoveActuator_Result_type_support_data_t;

static _MoveActuator_Result_type_support_data_t _MoveActuator_Result_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveActuator_Result_message_typesupport_map = {
  2,
  "transformer_hw_actuators",
  &_MoveActuator_Result_message_typesupport_ids.typesupport_identifier[0],
  &_MoveActuator_Result_message_typesupport_symbol_names.symbol_name[0],
  &_MoveActuator_Result_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveActuator_Result_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveActuator_Result_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_actuators__action__MoveActuator_Result__get_type_hash,
  &transformer_hw_actuators__action__MoveActuator_Result__get_type_description,
  &transformer_hw_actuators__action__MoveActuator_Result__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_actuators

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_actuators, action, MoveActuator_Result)() {
  return &::transformer_hw_actuators::action::rosidl_typesupport_c::MoveActuator_Result_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__type_support.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__functions.h"
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

namespace transformer_hw_actuators
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveActuator_Feedback_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveActuator_Feedback_type_support_ids_t;

static const _MoveActuator_Feedback_type_support_ids_t _MoveActuator_Feedback_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveActuator_Feedback_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveActuator_Feedback_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveActuator_Feedback_type_support_symbol_names_t _MoveActuator_Feedback_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_actuators, action, MoveActuator_Feedback)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_actuators, action, MoveActuator_Feedback)),
  }
};

typedef struct _MoveActuator_Feedback_type_support_data_t
{
  void * data[2];
} _MoveActuator_Feedback_type_support_data_t;

static _MoveActuator_Feedback_type_support_data_t _MoveActuator_Feedback_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveActuator_Feedback_message_typesupport_map = {
  2,
  "transformer_hw_actuators",
  &_MoveActuator_Feedback_message_typesupport_ids.typesupport_identifier[0],
  &_MoveActuator_Feedback_message_typesupport_symbol_names.symbol_name[0],
  &_MoveActuator_Feedback_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveActuator_Feedback_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveActuator_Feedback_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_actuators__action__MoveActuator_Feedback__get_type_hash,
  &transformer_hw_actuators__action__MoveActuator_Feedback__get_type_description,
  &transformer_hw_actuators__action__MoveActuator_Feedback__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_actuators

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_actuators, action, MoveActuator_Feedback)() {
  return &::transformer_hw_actuators::action::rosidl_typesupport_c::MoveActuator_Feedback_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__type_support.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__functions.h"
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

namespace transformer_hw_actuators
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveActuator_SendGoal_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveActuator_SendGoal_Request_type_support_ids_t;

static const _MoveActuator_SendGoal_Request_type_support_ids_t _MoveActuator_SendGoal_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveActuator_SendGoal_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveActuator_SendGoal_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveActuator_SendGoal_Request_type_support_symbol_names_t _MoveActuator_SendGoal_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_actuators, action, MoveActuator_SendGoal_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_actuators, action, MoveActuator_SendGoal_Request)),
  }
};

typedef struct _MoveActuator_SendGoal_Request_type_support_data_t
{
  void * data[2];
} _MoveActuator_SendGoal_Request_type_support_data_t;

static _MoveActuator_SendGoal_Request_type_support_data_t _MoveActuator_SendGoal_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveActuator_SendGoal_Request_message_typesupport_map = {
  2,
  "transformer_hw_actuators",
  &_MoveActuator_SendGoal_Request_message_typesupport_ids.typesupport_identifier[0],
  &_MoveActuator_SendGoal_Request_message_typesupport_symbol_names.symbol_name[0],
  &_MoveActuator_SendGoal_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveActuator_SendGoal_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveActuator_SendGoal_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_actuators__action__MoveActuator_SendGoal_Request__get_type_hash,
  &transformer_hw_actuators__action__MoveActuator_SendGoal_Request__get_type_description,
  &transformer_hw_actuators__action__MoveActuator_SendGoal_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_actuators

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_actuators, action, MoveActuator_SendGoal_Request)() {
  return &::transformer_hw_actuators::action::rosidl_typesupport_c::MoveActuator_SendGoal_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__type_support.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__functions.h"
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

namespace transformer_hw_actuators
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveActuator_SendGoal_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveActuator_SendGoal_Response_type_support_ids_t;

static const _MoveActuator_SendGoal_Response_type_support_ids_t _MoveActuator_SendGoal_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveActuator_SendGoal_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveActuator_SendGoal_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveActuator_SendGoal_Response_type_support_symbol_names_t _MoveActuator_SendGoal_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_actuators, action, MoveActuator_SendGoal_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_actuators, action, MoveActuator_SendGoal_Response)),
  }
};

typedef struct _MoveActuator_SendGoal_Response_type_support_data_t
{
  void * data[2];
} _MoveActuator_SendGoal_Response_type_support_data_t;

static _MoveActuator_SendGoal_Response_type_support_data_t _MoveActuator_SendGoal_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveActuator_SendGoal_Response_message_typesupport_map = {
  2,
  "transformer_hw_actuators",
  &_MoveActuator_SendGoal_Response_message_typesupport_ids.typesupport_identifier[0],
  &_MoveActuator_SendGoal_Response_message_typesupport_symbol_names.symbol_name[0],
  &_MoveActuator_SendGoal_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveActuator_SendGoal_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveActuator_SendGoal_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_actuators__action__MoveActuator_SendGoal_Response__get_type_hash,
  &transformer_hw_actuators__action__MoveActuator_SendGoal_Response__get_type_description,
  &transformer_hw_actuators__action__MoveActuator_SendGoal_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_actuators

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_actuators, action, MoveActuator_SendGoal_Response)() {
  return &::transformer_hw_actuators::action::rosidl_typesupport_c::MoveActuator_SendGoal_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__type_support.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__functions.h"
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

namespace transformer_hw_actuators
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveActuator_SendGoal_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveActuator_SendGoal_Event_type_support_ids_t;

static const _MoveActuator_SendGoal_Event_type_support_ids_t _MoveActuator_SendGoal_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveActuator_SendGoal_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveActuator_SendGoal_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveActuator_SendGoal_Event_type_support_symbol_names_t _MoveActuator_SendGoal_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_actuators, action, MoveActuator_SendGoal_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_actuators, action, MoveActuator_SendGoal_Event)),
  }
};

typedef struct _MoveActuator_SendGoal_Event_type_support_data_t
{
  void * data[2];
} _MoveActuator_SendGoal_Event_type_support_data_t;

static _MoveActuator_SendGoal_Event_type_support_data_t _MoveActuator_SendGoal_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveActuator_SendGoal_Event_message_typesupport_map = {
  2,
  "transformer_hw_actuators",
  &_MoveActuator_SendGoal_Event_message_typesupport_ids.typesupport_identifier[0],
  &_MoveActuator_SendGoal_Event_message_typesupport_symbol_names.symbol_name[0],
  &_MoveActuator_SendGoal_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveActuator_SendGoal_Event_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveActuator_SendGoal_Event_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_actuators__action__MoveActuator_SendGoal_Event__get_type_hash,
  &transformer_hw_actuators__action__MoveActuator_SendGoal_Event__get_type_description,
  &transformer_hw_actuators__action__MoveActuator_SendGoal_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_actuators

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_actuators, action, MoveActuator_SendGoal_Event)() {
  return &::transformer_hw_actuators::action::rosidl_typesupport_c::MoveActuator_SendGoal_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
#include "service_msgs/msg/service_event_info.h"
#include "builtin_interfaces/msg/time.h"

namespace transformer_hw_actuators
{

namespace action
{

namespace rosidl_typesupport_c
{
typedef struct _MoveActuator_SendGoal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveActuator_SendGoal_type_support_ids_t;

static const _MoveActuator_SendGoal_type_support_ids_t _MoveActuator_SendGoal_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveActuator_SendGoal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveActuator_SendGoal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveActuator_SendGoal_type_support_symbol_names_t _MoveActuator_SendGoal_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_actuators, action, MoveActuator_SendGoal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_actuators, action, MoveActuator_SendGoal)),
  }
};

typedef struct _MoveActuator_SendGoal_type_support_data_t
{
  void * data[2];
} _MoveActuator_SendGoal_type_support_data_t;

static _MoveActuator_SendGoal_type_support_data_t _MoveActuator_SendGoal_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveActuator_SendGoal_service_typesupport_map = {
  2,
  "transformer_hw_actuators",
  &_MoveActuator_SendGoal_service_typesupport_ids.typesupport_identifier[0],
  &_MoveActuator_SendGoal_service_typesupport_symbol_names.symbol_name[0],
  &_MoveActuator_SendGoal_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t MoveActuator_SendGoal_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveActuator_SendGoal_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
  &MoveActuator_SendGoal_Request_message_type_support_handle,
  &MoveActuator_SendGoal_Response_message_type_support_handle,
  &MoveActuator_SendGoal_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    transformer_hw_actuators,
    action,
    MoveActuator_SendGoal
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    transformer_hw_actuators,
    action,
    MoveActuator_SendGoal
  ),
  &transformer_hw_actuators__action__MoveActuator_SendGoal__get_type_hash,
  &transformer_hw_actuators__action__MoveActuator_SendGoal__get_type_description,
  &transformer_hw_actuators__action__MoveActuator_SendGoal__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_actuators

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_actuators, action, MoveActuator_SendGoal)() {
  return &::transformer_hw_actuators::action::rosidl_typesupport_c::MoveActuator_SendGoal_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__type_support.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__functions.h"
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

namespace transformer_hw_actuators
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveActuator_GetResult_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveActuator_GetResult_Request_type_support_ids_t;

static const _MoveActuator_GetResult_Request_type_support_ids_t _MoveActuator_GetResult_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveActuator_GetResult_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveActuator_GetResult_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveActuator_GetResult_Request_type_support_symbol_names_t _MoveActuator_GetResult_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_actuators, action, MoveActuator_GetResult_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_actuators, action, MoveActuator_GetResult_Request)),
  }
};

typedef struct _MoveActuator_GetResult_Request_type_support_data_t
{
  void * data[2];
} _MoveActuator_GetResult_Request_type_support_data_t;

static _MoveActuator_GetResult_Request_type_support_data_t _MoveActuator_GetResult_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveActuator_GetResult_Request_message_typesupport_map = {
  2,
  "transformer_hw_actuators",
  &_MoveActuator_GetResult_Request_message_typesupport_ids.typesupport_identifier[0],
  &_MoveActuator_GetResult_Request_message_typesupport_symbol_names.symbol_name[0],
  &_MoveActuator_GetResult_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveActuator_GetResult_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveActuator_GetResult_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_actuators__action__MoveActuator_GetResult_Request__get_type_hash,
  &transformer_hw_actuators__action__MoveActuator_GetResult_Request__get_type_description,
  &transformer_hw_actuators__action__MoveActuator_GetResult_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_actuators

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_actuators, action, MoveActuator_GetResult_Request)() {
  return &::transformer_hw_actuators::action::rosidl_typesupport_c::MoveActuator_GetResult_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__type_support.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__functions.h"
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

namespace transformer_hw_actuators
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveActuator_GetResult_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveActuator_GetResult_Response_type_support_ids_t;

static const _MoveActuator_GetResult_Response_type_support_ids_t _MoveActuator_GetResult_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveActuator_GetResult_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveActuator_GetResult_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveActuator_GetResult_Response_type_support_symbol_names_t _MoveActuator_GetResult_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_actuators, action, MoveActuator_GetResult_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_actuators, action, MoveActuator_GetResult_Response)),
  }
};

typedef struct _MoveActuator_GetResult_Response_type_support_data_t
{
  void * data[2];
} _MoveActuator_GetResult_Response_type_support_data_t;

static _MoveActuator_GetResult_Response_type_support_data_t _MoveActuator_GetResult_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveActuator_GetResult_Response_message_typesupport_map = {
  2,
  "transformer_hw_actuators",
  &_MoveActuator_GetResult_Response_message_typesupport_ids.typesupport_identifier[0],
  &_MoveActuator_GetResult_Response_message_typesupport_symbol_names.symbol_name[0],
  &_MoveActuator_GetResult_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveActuator_GetResult_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveActuator_GetResult_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_actuators__action__MoveActuator_GetResult_Response__get_type_hash,
  &transformer_hw_actuators__action__MoveActuator_GetResult_Response__get_type_description,
  &transformer_hw_actuators__action__MoveActuator_GetResult_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_actuators

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_actuators, action, MoveActuator_GetResult_Response)() {
  return &::transformer_hw_actuators::action::rosidl_typesupport_c::MoveActuator_GetResult_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__type_support.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__functions.h"
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

namespace transformer_hw_actuators
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveActuator_GetResult_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveActuator_GetResult_Event_type_support_ids_t;

static const _MoveActuator_GetResult_Event_type_support_ids_t _MoveActuator_GetResult_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveActuator_GetResult_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveActuator_GetResult_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveActuator_GetResult_Event_type_support_symbol_names_t _MoveActuator_GetResult_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_actuators, action, MoveActuator_GetResult_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_actuators, action, MoveActuator_GetResult_Event)),
  }
};

typedef struct _MoveActuator_GetResult_Event_type_support_data_t
{
  void * data[2];
} _MoveActuator_GetResult_Event_type_support_data_t;

static _MoveActuator_GetResult_Event_type_support_data_t _MoveActuator_GetResult_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveActuator_GetResult_Event_message_typesupport_map = {
  2,
  "transformer_hw_actuators",
  &_MoveActuator_GetResult_Event_message_typesupport_ids.typesupport_identifier[0],
  &_MoveActuator_GetResult_Event_message_typesupport_symbol_names.symbol_name[0],
  &_MoveActuator_GetResult_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveActuator_GetResult_Event_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveActuator_GetResult_Event_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_actuators__action__MoveActuator_GetResult_Event__get_type_hash,
  &transformer_hw_actuators__action__MoveActuator_GetResult_Event__get_type_description,
  &transformer_hw_actuators__action__MoveActuator_GetResult_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_actuators

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_actuators, action, MoveActuator_GetResult_Event)() {
  return &::transformer_hw_actuators::action::rosidl_typesupport_c::MoveActuator_GetResult_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__type_support.h"
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

namespace transformer_hw_actuators
{

namespace action
{

namespace rosidl_typesupport_c
{
typedef struct _MoveActuator_GetResult_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveActuator_GetResult_type_support_ids_t;

static const _MoveActuator_GetResult_type_support_ids_t _MoveActuator_GetResult_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveActuator_GetResult_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveActuator_GetResult_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveActuator_GetResult_type_support_symbol_names_t _MoveActuator_GetResult_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_actuators, action, MoveActuator_GetResult)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_actuators, action, MoveActuator_GetResult)),
  }
};

typedef struct _MoveActuator_GetResult_type_support_data_t
{
  void * data[2];
} _MoveActuator_GetResult_type_support_data_t;

static _MoveActuator_GetResult_type_support_data_t _MoveActuator_GetResult_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveActuator_GetResult_service_typesupport_map = {
  2,
  "transformer_hw_actuators",
  &_MoveActuator_GetResult_service_typesupport_ids.typesupport_identifier[0],
  &_MoveActuator_GetResult_service_typesupport_symbol_names.symbol_name[0],
  &_MoveActuator_GetResult_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t MoveActuator_GetResult_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveActuator_GetResult_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
  &MoveActuator_GetResult_Request_message_type_support_handle,
  &MoveActuator_GetResult_Response_message_type_support_handle,
  &MoveActuator_GetResult_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    transformer_hw_actuators,
    action,
    MoveActuator_GetResult
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    transformer_hw_actuators,
    action,
    MoveActuator_GetResult
  ),
  &transformer_hw_actuators__action__MoveActuator_GetResult__get_type_hash,
  &transformer_hw_actuators__action__MoveActuator_GetResult__get_type_description,
  &transformer_hw_actuators__action__MoveActuator_GetResult__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_actuators

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_actuators, action, MoveActuator_GetResult)() {
  return &::transformer_hw_actuators::action::rosidl_typesupport_c::MoveActuator_GetResult_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__struct.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__type_support.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__functions.h"
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

namespace transformer_hw_actuators
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _MoveActuator_FeedbackMessage_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveActuator_FeedbackMessage_type_support_ids_t;

static const _MoveActuator_FeedbackMessage_type_support_ids_t _MoveActuator_FeedbackMessage_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _MoveActuator_FeedbackMessage_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _MoveActuator_FeedbackMessage_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _MoveActuator_FeedbackMessage_type_support_symbol_names_t _MoveActuator_FeedbackMessage_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, transformer_hw_actuators, action, MoveActuator_FeedbackMessage)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, transformer_hw_actuators, action, MoveActuator_FeedbackMessage)),
  }
};

typedef struct _MoveActuator_FeedbackMessage_type_support_data_t
{
  void * data[2];
} _MoveActuator_FeedbackMessage_type_support_data_t;

static _MoveActuator_FeedbackMessage_type_support_data_t _MoveActuator_FeedbackMessage_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _MoveActuator_FeedbackMessage_message_typesupport_map = {
  2,
  "transformer_hw_actuators",
  &_MoveActuator_FeedbackMessage_message_typesupport_ids.typesupport_identifier[0],
  &_MoveActuator_FeedbackMessage_message_typesupport_symbol_names.symbol_name[0],
  &_MoveActuator_FeedbackMessage_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t MoveActuator_FeedbackMessage_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveActuator_FeedbackMessage_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &transformer_hw_actuators__action__MoveActuator_FeedbackMessage__get_type_hash,
  &transformer_hw_actuators__action__MoveActuator_FeedbackMessage__get_type_description,
  &transformer_hw_actuators__action__MoveActuator_FeedbackMessage__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace transformer_hw_actuators

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, transformer_hw_actuators, action, MoveActuator_FeedbackMessage)() {
  return &::transformer_hw_actuators::action::rosidl_typesupport_c::MoveActuator_FeedbackMessage_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

#include "action_msgs/msg/goal_status_array.h"
#include "action_msgs/srv/cancel_goal.h"
#include "transformer_hw_actuators/action/move_actuator.h"
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__type_support.h"

static rosidl_action_type_support_t _transformer_hw_actuators__action__MoveActuator__typesupport_c = {
  NULL, NULL, NULL, NULL, NULL,
  &transformer_hw_actuators__action__MoveActuator__get_type_hash,
  &transformer_hw_actuators__action__MoveActuator__get_type_description,
  &transformer_hw_actuators__action__MoveActuator__get_type_description_sources,
};

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_action_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__ACTION_SYMBOL_NAME(
  rosidl_typesupport_c, transformer_hw_actuators, action, MoveActuator)()
{
  // Thread-safe by always writing the same values to the static struct
  _transformer_hw_actuators__action__MoveActuator__typesupport_c.goal_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, transformer_hw_actuators, action, MoveActuator_SendGoal)();
  _transformer_hw_actuators__action__MoveActuator__typesupport_c.result_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, transformer_hw_actuators, action, MoveActuator_GetResult)();
  _transformer_hw_actuators__action__MoveActuator__typesupport_c.cancel_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, action_msgs, srv, CancelGoal)();
  _transformer_hw_actuators__action__MoveActuator__typesupport_c.feedback_message_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, transformer_hw_actuators, action, MoveActuator_FeedbackMessage)();
  _transformer_hw_actuators__action__MoveActuator__typesupport_c.status_message_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, action_msgs, msg, GoalStatusArray)();

  return &_transformer_hw_actuators__action__MoveActuator__typesupport_c;
}

#ifdef __cplusplus
}
#endif
