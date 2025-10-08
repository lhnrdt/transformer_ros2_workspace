// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from transformer_controller:action/TransformMode.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "transformer_controller/action/transform_mode.h"


#ifndef TRANSFORMER_CONTROLLER__ACTION__DETAIL__TRANSFORM_MODE__STRUCT_H_
#define TRANSFORMER_CONTROLLER__ACTION__DETAIL__TRANSFORM_MODE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'target_mode'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/TransformMode in the package transformer_controller.
typedef struct transformer_controller__action__TransformMode_Goal
{
  rosidl_runtime_c__String target_mode;
} transformer_controller__action__TransformMode_Goal;

// Struct for a sequence of transformer_controller__action__TransformMode_Goal.
typedef struct transformer_controller__action__TransformMode_Goal__Sequence
{
  transformer_controller__action__TransformMode_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_controller__action__TransformMode_Goal__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
// Member 'final_mode'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/TransformMode in the package transformer_controller.
typedef struct transformer_controller__action__TransformMode_Result
{
  bool success;
  rosidl_runtime_c__String message;
  rosidl_runtime_c__String final_mode;
} transformer_controller__action__TransformMode_Result;

// Struct for a sequence of transformer_controller__action__TransformMode_Result.
typedef struct transformer_controller__action__TransformMode_Result__Sequence
{
  transformer_controller__action__TransformMode_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_controller__action__TransformMode_Result__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'phase'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/TransformMode in the package transformer_controller.
typedef struct transformer_controller__action__TransformMode_Feedback
{
  /// 0..1 overall
  float progress;
  /// e.g. retracting_actuators, moving_servos, extending_actuators, done
  rosidl_runtime_c__String phase;
} transformer_controller__action__TransformMode_Feedback;

// Struct for a sequence of transformer_controller__action__TransformMode_Feedback.
typedef struct transformer_controller__action__TransformMode_Feedback__Sequence
{
  transformer_controller__action__TransformMode_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_controller__action__TransformMode_Feedback__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "transformer_controller/action/detail/transform_mode__struct.h"

/// Struct defined in action/TransformMode in the package transformer_controller.
typedef struct transformer_controller__action__TransformMode_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  transformer_controller__action__TransformMode_Goal goal;
} transformer_controller__action__TransformMode_SendGoal_Request;

// Struct for a sequence of transformer_controller__action__TransformMode_SendGoal_Request.
typedef struct transformer_controller__action__TransformMode_SendGoal_Request__Sequence
{
  transformer_controller__action__TransformMode_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_controller__action__TransformMode_SendGoal_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/TransformMode in the package transformer_controller.
typedef struct transformer_controller__action__TransformMode_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} transformer_controller__action__TransformMode_SendGoal_Response;

// Struct for a sequence of transformer_controller__action__TransformMode_SendGoal_Response.
typedef struct transformer_controller__action__TransformMode_SendGoal_Response__Sequence
{
  transformer_controller__action__TransformMode_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_controller__action__TransformMode_SendGoal_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  transformer_controller__action__TransformMode_SendGoal_Event__request__MAX_SIZE = 1
};
// response
enum
{
  transformer_controller__action__TransformMode_SendGoal_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/TransformMode in the package transformer_controller.
typedef struct transformer_controller__action__TransformMode_SendGoal_Event
{
  service_msgs__msg__ServiceEventInfo info;
  transformer_controller__action__TransformMode_SendGoal_Request__Sequence request;
  transformer_controller__action__TransformMode_SendGoal_Response__Sequence response;
} transformer_controller__action__TransformMode_SendGoal_Event;

// Struct for a sequence of transformer_controller__action__TransformMode_SendGoal_Event.
typedef struct transformer_controller__action__TransformMode_SendGoal_Event__Sequence
{
  transformer_controller__action__TransformMode_SendGoal_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_controller__action__TransformMode_SendGoal_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/TransformMode in the package transformer_controller.
typedef struct transformer_controller__action__TransformMode_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} transformer_controller__action__TransformMode_GetResult_Request;

// Struct for a sequence of transformer_controller__action__TransformMode_GetResult_Request.
typedef struct transformer_controller__action__TransformMode_GetResult_Request__Sequence
{
  transformer_controller__action__TransformMode_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_controller__action__TransformMode_GetResult_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "transformer_controller/action/detail/transform_mode__struct.h"

/// Struct defined in action/TransformMode in the package transformer_controller.
typedef struct transformer_controller__action__TransformMode_GetResult_Response
{
  int8_t status;
  transformer_controller__action__TransformMode_Result result;
} transformer_controller__action__TransformMode_GetResult_Response;

// Struct for a sequence of transformer_controller__action__TransformMode_GetResult_Response.
typedef struct transformer_controller__action__TransformMode_GetResult_Response__Sequence
{
  transformer_controller__action__TransformMode_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_controller__action__TransformMode_GetResult_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  transformer_controller__action__TransformMode_GetResult_Event__request__MAX_SIZE = 1
};
// response
enum
{
  transformer_controller__action__TransformMode_GetResult_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/TransformMode in the package transformer_controller.
typedef struct transformer_controller__action__TransformMode_GetResult_Event
{
  service_msgs__msg__ServiceEventInfo info;
  transformer_controller__action__TransformMode_GetResult_Request__Sequence request;
  transformer_controller__action__TransformMode_GetResult_Response__Sequence response;
} transformer_controller__action__TransformMode_GetResult_Event;

// Struct for a sequence of transformer_controller__action__TransformMode_GetResult_Event.
typedef struct transformer_controller__action__TransformMode_GetResult_Event__Sequence
{
  transformer_controller__action__TransformMode_GetResult_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_controller__action__TransformMode_GetResult_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "transformer_controller/action/detail/transform_mode__struct.h"

/// Struct defined in action/TransformMode in the package transformer_controller.
typedef struct transformer_controller__action__TransformMode_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  transformer_controller__action__TransformMode_Feedback feedback;
} transformer_controller__action__TransformMode_FeedbackMessage;

// Struct for a sequence of transformer_controller__action__TransformMode_FeedbackMessage.
typedef struct transformer_controller__action__TransformMode_FeedbackMessage__Sequence
{
  transformer_controller__action__TransformMode_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_controller__action__TransformMode_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TRANSFORMER_CONTROLLER__ACTION__DETAIL__TRANSFORM_MODE__STRUCT_H_
