// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from transformer_hw_actuators:action/MoveActuator.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "transformer_hw_actuators/action/move_actuator.h"


#ifndef TRANSFORMER_HW_ACTUATORS__ACTION__DETAIL__MOVE_ACTUATOR__STRUCT_H_
#define TRANSFORMER_HW_ACTUATORS__ACTION__DETAIL__MOVE_ACTUATOR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'actuators'
// Member 'speed_percents'
// Member 'duration_ms'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in action/MoveActuator in the package transformer_hw_actuators.
typedef struct transformer_hw_actuators__action__MoveActuator_Goal
{
  rosidl_runtime_c__int32__Sequence actuators;
  rosidl_runtime_c__int32__Sequence speed_percents;
  rosidl_runtime_c__int32__Sequence duration_ms;
} transformer_hw_actuators__action__MoveActuator_Goal;

// Struct for a sequence of transformer_hw_actuators__action__MoveActuator_Goal.
typedef struct transformer_hw_actuators__action__MoveActuator_Goal__Sequence
{
  transformer_hw_actuators__action__MoveActuator_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_actuators__action__MoveActuator_Goal__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/MoveActuator in the package transformer_hw_actuators.
typedef struct transformer_hw_actuators__action__MoveActuator_Result
{
  bool success;
  rosidl_runtime_c__String message;
} transformer_hw_actuators__action__MoveActuator_Result;

// Struct for a sequence of transformer_hw_actuators__action__MoveActuator_Result.
typedef struct transformer_hw_actuators__action__MoveActuator_Result__Sequence
{
  transformer_hw_actuators__action__MoveActuator_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_actuators__action__MoveActuator_Result__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'current_speed_percents'
// Member 'elapsed_ms'
// Member 'remaining_ms'
// already included above
// #include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in action/MoveActuator in the package transformer_hw_actuators.
typedef struct transformer_hw_actuators__action__MoveActuator_Feedback
{
  rosidl_runtime_c__int32__Sequence current_speed_percents;
  rosidl_runtime_c__int32__Sequence elapsed_ms;
  rosidl_runtime_c__int32__Sequence remaining_ms;
} transformer_hw_actuators__action__MoveActuator_Feedback;

// Struct for a sequence of transformer_hw_actuators__action__MoveActuator_Feedback.
typedef struct transformer_hw_actuators__action__MoveActuator_Feedback__Sequence
{
  transformer_hw_actuators__action__MoveActuator_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_actuators__action__MoveActuator_Feedback__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "transformer_hw_actuators/action/detail/move_actuator__struct.h"

/// Struct defined in action/MoveActuator in the package transformer_hw_actuators.
typedef struct transformer_hw_actuators__action__MoveActuator_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  transformer_hw_actuators__action__MoveActuator_Goal goal;
} transformer_hw_actuators__action__MoveActuator_SendGoal_Request;

// Struct for a sequence of transformer_hw_actuators__action__MoveActuator_SendGoal_Request.
typedef struct transformer_hw_actuators__action__MoveActuator_SendGoal_Request__Sequence
{
  transformer_hw_actuators__action__MoveActuator_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_actuators__action__MoveActuator_SendGoal_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/MoveActuator in the package transformer_hw_actuators.
typedef struct transformer_hw_actuators__action__MoveActuator_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} transformer_hw_actuators__action__MoveActuator_SendGoal_Response;

// Struct for a sequence of transformer_hw_actuators__action__MoveActuator_SendGoal_Response.
typedef struct transformer_hw_actuators__action__MoveActuator_SendGoal_Response__Sequence
{
  transformer_hw_actuators__action__MoveActuator_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_actuators__action__MoveActuator_SendGoal_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  transformer_hw_actuators__action__MoveActuator_SendGoal_Event__request__MAX_SIZE = 1
};
// response
enum
{
  transformer_hw_actuators__action__MoveActuator_SendGoal_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/MoveActuator in the package transformer_hw_actuators.
typedef struct transformer_hw_actuators__action__MoveActuator_SendGoal_Event
{
  service_msgs__msg__ServiceEventInfo info;
  transformer_hw_actuators__action__MoveActuator_SendGoal_Request__Sequence request;
  transformer_hw_actuators__action__MoveActuator_SendGoal_Response__Sequence response;
} transformer_hw_actuators__action__MoveActuator_SendGoal_Event;

// Struct for a sequence of transformer_hw_actuators__action__MoveActuator_SendGoal_Event.
typedef struct transformer_hw_actuators__action__MoveActuator_SendGoal_Event__Sequence
{
  transformer_hw_actuators__action__MoveActuator_SendGoal_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_actuators__action__MoveActuator_SendGoal_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/MoveActuator in the package transformer_hw_actuators.
typedef struct transformer_hw_actuators__action__MoveActuator_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} transformer_hw_actuators__action__MoveActuator_GetResult_Request;

// Struct for a sequence of transformer_hw_actuators__action__MoveActuator_GetResult_Request.
typedef struct transformer_hw_actuators__action__MoveActuator_GetResult_Request__Sequence
{
  transformer_hw_actuators__action__MoveActuator_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_actuators__action__MoveActuator_GetResult_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__struct.h"

/// Struct defined in action/MoveActuator in the package transformer_hw_actuators.
typedef struct transformer_hw_actuators__action__MoveActuator_GetResult_Response
{
  int8_t status;
  transformer_hw_actuators__action__MoveActuator_Result result;
} transformer_hw_actuators__action__MoveActuator_GetResult_Response;

// Struct for a sequence of transformer_hw_actuators__action__MoveActuator_GetResult_Response.
typedef struct transformer_hw_actuators__action__MoveActuator_GetResult_Response__Sequence
{
  transformer_hw_actuators__action__MoveActuator_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_actuators__action__MoveActuator_GetResult_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  transformer_hw_actuators__action__MoveActuator_GetResult_Event__request__MAX_SIZE = 1
};
// response
enum
{
  transformer_hw_actuators__action__MoveActuator_GetResult_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/MoveActuator in the package transformer_hw_actuators.
typedef struct transformer_hw_actuators__action__MoveActuator_GetResult_Event
{
  service_msgs__msg__ServiceEventInfo info;
  transformer_hw_actuators__action__MoveActuator_GetResult_Request__Sequence request;
  transformer_hw_actuators__action__MoveActuator_GetResult_Response__Sequence response;
} transformer_hw_actuators__action__MoveActuator_GetResult_Event;

// Struct for a sequence of transformer_hw_actuators__action__MoveActuator_GetResult_Event.
typedef struct transformer_hw_actuators__action__MoveActuator_GetResult_Event__Sequence
{
  transformer_hw_actuators__action__MoveActuator_GetResult_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_actuators__action__MoveActuator_GetResult_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "transformer_hw_actuators/action/detail/move_actuator__struct.h"

/// Struct defined in action/MoveActuator in the package transformer_hw_actuators.
typedef struct transformer_hw_actuators__action__MoveActuator_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  transformer_hw_actuators__action__MoveActuator_Feedback feedback;
} transformer_hw_actuators__action__MoveActuator_FeedbackMessage;

// Struct for a sequence of transformer_hw_actuators__action__MoveActuator_FeedbackMessage.
typedef struct transformer_hw_actuators__action__MoveActuator_FeedbackMessage__Sequence
{
  transformer_hw_actuators__action__MoveActuator_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_actuators__action__MoveActuator_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TRANSFORMER_HW_ACTUATORS__ACTION__DETAIL__MOVE_ACTUATOR__STRUCT_H_
