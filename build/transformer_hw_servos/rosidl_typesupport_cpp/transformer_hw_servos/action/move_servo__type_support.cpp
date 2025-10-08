// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from transformer_hw_servos:action/MoveServo.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "transformer_hw_servos/action/detail/move_servo__functions.h"
#include "transformer_hw_servos/action/detail/move_servo__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _MoveServo_Goal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_Goal_type_support_ids_t;

static const _MoveServo_Goal_type_support_ids_t _MoveServo_Goal_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_Goal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, transformer_hw_servos, action, MoveServo_Goal)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_Goal_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_Goal__get_type_hash,
  &transformer_hw_servos__action__MoveServo_Goal__get_type_description,
  &transformer_hw_servos__action__MoveServo_Goal__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<transformer_hw_servos::action::MoveServo_Goal>()
{
  return &::transformer_hw_servos::action::rosidl_typesupport_cpp::MoveServo_Goal_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, transformer_hw_servos, action, MoveServo_Goal)() {
  return get_message_type_support_handle<transformer_hw_servos::action::MoveServo_Goal>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _MoveServo_Result_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_Result_type_support_ids_t;

static const _MoveServo_Result_type_support_ids_t _MoveServo_Result_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_Result)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, transformer_hw_servos, action, MoveServo_Result)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_Result_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_Result__get_type_hash,
  &transformer_hw_servos__action__MoveServo_Result__get_type_description,
  &transformer_hw_servos__action__MoveServo_Result__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<transformer_hw_servos::action::MoveServo_Result>()
{
  return &::transformer_hw_servos::action::rosidl_typesupport_cpp::MoveServo_Result_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, transformer_hw_servos, action, MoveServo_Result)() {
  return get_message_type_support_handle<transformer_hw_servos::action::MoveServo_Result>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _MoveServo_Feedback_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_Feedback_type_support_ids_t;

static const _MoveServo_Feedback_type_support_ids_t _MoveServo_Feedback_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_Feedback)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, transformer_hw_servos, action, MoveServo_Feedback)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_Feedback_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_Feedback__get_type_hash,
  &transformer_hw_servos__action__MoveServo_Feedback__get_type_description,
  &transformer_hw_servos__action__MoveServo_Feedback__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<transformer_hw_servos::action::MoveServo_Feedback>()
{
  return &::transformer_hw_servos::action::rosidl_typesupport_cpp::MoveServo_Feedback_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, transformer_hw_servos, action, MoveServo_Feedback)() {
  return get_message_type_support_handle<transformer_hw_servos::action::MoveServo_Feedback>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _MoveServo_SendGoal_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_SendGoal_Request_type_support_ids_t;

static const _MoveServo_SendGoal_Request_type_support_ids_t _MoveServo_SendGoal_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_SendGoal_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, transformer_hw_servos, action, MoveServo_SendGoal_Request)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_SendGoal_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_SendGoal_Request__get_type_hash,
  &transformer_hw_servos__action__MoveServo_SendGoal_Request__get_type_description,
  &transformer_hw_servos__action__MoveServo_SendGoal_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<transformer_hw_servos::action::MoveServo_SendGoal_Request>()
{
  return &::transformer_hw_servos::action::rosidl_typesupport_cpp::MoveServo_SendGoal_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, transformer_hw_servos, action, MoveServo_SendGoal_Request)() {
  return get_message_type_support_handle<transformer_hw_servos::action::MoveServo_SendGoal_Request>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _MoveServo_SendGoal_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_SendGoal_Response_type_support_ids_t;

static const _MoveServo_SendGoal_Response_type_support_ids_t _MoveServo_SendGoal_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_SendGoal_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, transformer_hw_servos, action, MoveServo_SendGoal_Response)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_SendGoal_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_SendGoal_Response__get_type_hash,
  &transformer_hw_servos__action__MoveServo_SendGoal_Response__get_type_description,
  &transformer_hw_servos__action__MoveServo_SendGoal_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<transformer_hw_servos::action::MoveServo_SendGoal_Response>()
{
  return &::transformer_hw_servos::action::rosidl_typesupport_cpp::MoveServo_SendGoal_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, transformer_hw_servos, action, MoveServo_SendGoal_Response)() {
  return get_message_type_support_handle<transformer_hw_servos::action::MoveServo_SendGoal_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _MoveServo_SendGoal_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_SendGoal_Event_type_support_ids_t;

static const _MoveServo_SendGoal_Event_type_support_ids_t _MoveServo_SendGoal_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_SendGoal_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, transformer_hw_servos, action, MoveServo_SendGoal_Event)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_SendGoal_Event_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_SendGoal_Event__get_type_hash,
  &transformer_hw_servos__action__MoveServo_SendGoal_Event__get_type_description,
  &transformer_hw_servos__action__MoveServo_SendGoal_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<transformer_hw_servos::action::MoveServo_SendGoal_Event>()
{
  return &::transformer_hw_servos::action::rosidl_typesupport_cpp::MoveServo_SendGoal_Event_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, transformer_hw_servos, action, MoveServo_SendGoal_Event)() {
  return get_message_type_support_handle<transformer_hw_servos::action::MoveServo_SendGoal_Event>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _MoveServo_SendGoal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_SendGoal_type_support_ids_t;

static const _MoveServo_SendGoal_type_support_ids_t _MoveServo_SendGoal_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_SendGoal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, transformer_hw_servos, action, MoveServo_SendGoal)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_SendGoal_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
  ::rosidl_typesupport_cpp::get_message_type_support_handle<transformer_hw_servos::action::MoveServo_SendGoal_Request>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<transformer_hw_servos::action::MoveServo_SendGoal_Response>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<transformer_hw_servos::action::MoveServo_SendGoal_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<transformer_hw_servos::action::MoveServo_SendGoal>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<transformer_hw_servos::action::MoveServo_SendGoal>,
  &transformer_hw_servos__action__MoveServo_SendGoal__get_type_hash,
  &transformer_hw_servos__action__MoveServo_SendGoal__get_type_description,
  &transformer_hw_servos__action__MoveServo_SendGoal__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<transformer_hw_servos::action::MoveServo_SendGoal>()
{
  return &::transformer_hw_servos::action::rosidl_typesupport_cpp::MoveServo_SendGoal_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, transformer_hw_servos, action, MoveServo_SendGoal)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<transformer_hw_servos::action::MoveServo_SendGoal>();
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _MoveServo_GetResult_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_GetResult_Request_type_support_ids_t;

static const _MoveServo_GetResult_Request_type_support_ids_t _MoveServo_GetResult_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_GetResult_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, transformer_hw_servos, action, MoveServo_GetResult_Request)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_GetResult_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_GetResult_Request__get_type_hash,
  &transformer_hw_servos__action__MoveServo_GetResult_Request__get_type_description,
  &transformer_hw_servos__action__MoveServo_GetResult_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<transformer_hw_servos::action::MoveServo_GetResult_Request>()
{
  return &::transformer_hw_servos::action::rosidl_typesupport_cpp::MoveServo_GetResult_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, transformer_hw_servos, action, MoveServo_GetResult_Request)() {
  return get_message_type_support_handle<transformer_hw_servos::action::MoveServo_GetResult_Request>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _MoveServo_GetResult_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_GetResult_Response_type_support_ids_t;

static const _MoveServo_GetResult_Response_type_support_ids_t _MoveServo_GetResult_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_GetResult_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, transformer_hw_servos, action, MoveServo_GetResult_Response)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_GetResult_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_GetResult_Response__get_type_hash,
  &transformer_hw_servos__action__MoveServo_GetResult_Response__get_type_description,
  &transformer_hw_servos__action__MoveServo_GetResult_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<transformer_hw_servos::action::MoveServo_GetResult_Response>()
{
  return &::transformer_hw_servos::action::rosidl_typesupport_cpp::MoveServo_GetResult_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, transformer_hw_servos, action, MoveServo_GetResult_Response)() {
  return get_message_type_support_handle<transformer_hw_servos::action::MoveServo_GetResult_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _MoveServo_GetResult_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_GetResult_Event_type_support_ids_t;

static const _MoveServo_GetResult_Event_type_support_ids_t _MoveServo_GetResult_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_GetResult_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, transformer_hw_servos, action, MoveServo_GetResult_Event)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_GetResult_Event_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_GetResult_Event__get_type_hash,
  &transformer_hw_servos__action__MoveServo_GetResult_Event__get_type_description,
  &transformer_hw_servos__action__MoveServo_GetResult_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<transformer_hw_servos::action::MoveServo_GetResult_Event>()
{
  return &::transformer_hw_servos::action::rosidl_typesupport_cpp::MoveServo_GetResult_Event_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, transformer_hw_servos, action, MoveServo_GetResult_Event)() {
  return get_message_type_support_handle<transformer_hw_servos::action::MoveServo_GetResult_Event>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _MoveServo_GetResult_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_GetResult_type_support_ids_t;

static const _MoveServo_GetResult_type_support_ids_t _MoveServo_GetResult_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_GetResult)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, transformer_hw_servos, action, MoveServo_GetResult)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_GetResult_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
  ::rosidl_typesupport_cpp::get_message_type_support_handle<transformer_hw_servos::action::MoveServo_GetResult_Request>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<transformer_hw_servos::action::MoveServo_GetResult_Response>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<transformer_hw_servos::action::MoveServo_GetResult_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<transformer_hw_servos::action::MoveServo_GetResult>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<transformer_hw_servos::action::MoveServo_GetResult>,
  &transformer_hw_servos__action__MoveServo_GetResult__get_type_hash,
  &transformer_hw_servos__action__MoveServo_GetResult__get_type_description,
  &transformer_hw_servos__action__MoveServo_GetResult__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<transformer_hw_servos::action::MoveServo_GetResult>()
{
  return &::transformer_hw_servos::action::rosidl_typesupport_cpp::MoveServo_GetResult_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, transformer_hw_servos, action, MoveServo_GetResult)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<transformer_hw_servos::action::MoveServo_GetResult>();
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _MoveServo_FeedbackMessage_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _MoveServo_FeedbackMessage_type_support_ids_t;

static const _MoveServo_FeedbackMessage_type_support_ids_t _MoveServo_FeedbackMessage_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
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
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, transformer_hw_servos, action, MoveServo_FeedbackMessage)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, transformer_hw_servos, action, MoveServo_FeedbackMessage)),
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
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_MoveServo_FeedbackMessage_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &transformer_hw_servos__action__MoveServo_FeedbackMessage__get_type_hash,
  &transformer_hw_servos__action__MoveServo_FeedbackMessage__get_type_description,
  &transformer_hw_servos__action__MoveServo_FeedbackMessage__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<transformer_hw_servos::action::MoveServo_FeedbackMessage>()
{
  return &::transformer_hw_servos::action::rosidl_typesupport_cpp::MoveServo_FeedbackMessage_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, transformer_hw_servos, action, MoveServo_FeedbackMessage)() {
  return get_message_type_support_handle<transformer_hw_servos::action::MoveServo_FeedbackMessage>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

#include "action_msgs/msg/goal_status_array.hpp"
#include "action_msgs/srv/cancel_goal.hpp"
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_typesupport_cpp/action_type_support.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_cpp/service_type_support.hpp"

namespace transformer_hw_servos
{

namespace action
{

namespace rosidl_typesupport_cpp
{

static rosidl_action_type_support_t MoveServo_action_type_support_handle = {
  NULL, NULL, NULL, NULL, NULL,
  &transformer_hw_servos__action__MoveServo__get_type_hash,
  &transformer_hw_servos__action__MoveServo__get_type_description,
  &transformer_hw_servos__action__MoveServo__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace transformer_hw_servos

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_action_type_support_t *
get_action_type_support_handle<transformer_hw_servos::action::MoveServo>()
{
  using ::transformer_hw_servos::action::rosidl_typesupport_cpp::MoveServo_action_type_support_handle;
  // Thread-safe by always writing the same values to the static struct
  MoveServo_action_type_support_handle.goal_service_type_support = get_service_type_support_handle<::transformer_hw_servos::action::MoveServo::Impl::SendGoalService>();
  MoveServo_action_type_support_handle.result_service_type_support = get_service_type_support_handle<::transformer_hw_servos::action::MoveServo::Impl::GetResultService>();
  MoveServo_action_type_support_handle.cancel_service_type_support = get_service_type_support_handle<::transformer_hw_servos::action::MoveServo::Impl::CancelGoalService>();
  MoveServo_action_type_support_handle.feedback_message_type_support = get_message_type_support_handle<::transformer_hw_servos::action::MoveServo::Impl::FeedbackMessage>();
  MoveServo_action_type_support_handle.status_message_type_support = get_message_type_support_handle<::transformer_hw_servos::action::MoveServo::Impl::GoalStatusMessage>();
  return &MoveServo_action_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_action_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__ACTION_SYMBOL_NAME(rosidl_typesupport_cpp, transformer_hw_servos, action, MoveServo)() {
  return ::rosidl_typesupport_cpp::get_action_type_support_handle<transformer_hw_servos::action::MoveServo>();
}

#ifdef __cplusplus
}
#endif
