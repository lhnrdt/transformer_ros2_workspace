// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from transformer_hw_servos:action/MoveServo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "transformer_hw_servos/action/move_servo.h"


#ifndef TRANSFORMER_HW_SERVOS__ACTION__DETAIL__MOVE_SERVO__STRUCT_H_
#define TRANSFORMER_HW_SERVOS__ACTION__DETAIL__MOVE_SERVO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'channels'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in action/MoveServo in the package transformer_hw_servos.
typedef struct transformer_hw_servos__action__MoveServo_Goal
{
  rosidl_runtime_c__int32__Sequence channels;
  /// Target logical pulse width (microseconds) applied to every listed channel.
  int32_t pulse_us;
  /// Speed in microseconds per second (rate of change). If <=0 apply immediately.
  /// Requested max slew speed (|dPulse|/s). If <=0 apply instantly.
  int32_t speed_us_per_s;
  /// If true, use trapezoidal (or triangular) profile for this goal; else constant speed.
  bool use_trapezoid;
  /// Acceleration for trapezoid (µs/s^2). If <=0, node picks heuristic.
  int32_t accel_us_per_s2;
} transformer_hw_servos__action__MoveServo_Goal;

// Struct for a sequence of transformer_hw_servos__action__MoveServo_Goal.
typedef struct transformer_hw_servos__action__MoveServo_Goal__Sequence
{
  transformer_hw_servos__action__MoveServo_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_servos__action__MoveServo_Goal__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"
// Member 'final_pulses_us'
// already included above
// #include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in action/MoveServo in the package transformer_hw_servos.
typedef struct transformer_hw_servos__action__MoveServo_Result
{
  bool success;
  rosidl_runtime_c__String message;
  /// Logical final pulses (same size/order as channels array)
  rosidl_runtime_c__int32__Sequence final_pulses_us;
  /// Planned total motion duration (0 for instant moves)
  float total_estimated_duration_s;
} transformer_hw_servos__action__MoveServo_Result;

// Struct for a sequence of transformer_hw_servos__action__MoveServo_Result.
typedef struct transformer_hw_servos__action__MoveServo_Result__Sequence
{
  transformer_hw_servos__action__MoveServo_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_servos__action__MoveServo_Result__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'current_pulses_us'
// already included above
// #include "rosidl_runtime_c/primitives_sequence.h"
// Member 'phase'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/MoveServo in the package transformer_hw_servos.
typedef struct transformer_hw_servos__action__MoveServo_Feedback
{
  /// Current logical pulses (same size/order as channels array)
  rosidl_runtime_c__int32__Sequence current_pulses_us;
  /// 0.0 .. 1.0 (if speed>0, else 1.0)
  float progress;
  /// Remaining motion time estimate (0 when complete/instant)
  float estimated_remaining_s;
  /// "accel","cruise","decel","done" (or "linear")
  rosidl_runtime_c__String phase;
} transformer_hw_servos__action__MoveServo_Feedback;

// Struct for a sequence of transformer_hw_servos__action__MoveServo_Feedback.
typedef struct transformer_hw_servos__action__MoveServo_Feedback__Sequence
{
  transformer_hw_servos__action__MoveServo_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_servos__action__MoveServo_Feedback__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "transformer_hw_servos/action/detail/move_servo__struct.h"

/// Struct defined in action/MoveServo in the package transformer_hw_servos.
typedef struct transformer_hw_servos__action__MoveServo_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  transformer_hw_servos__action__MoveServo_Goal goal;
} transformer_hw_servos__action__MoveServo_SendGoal_Request;

// Struct for a sequence of transformer_hw_servos__action__MoveServo_SendGoal_Request.
typedef struct transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence
{
  transformer_hw_servos__action__MoveServo_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/MoveServo in the package transformer_hw_servos.
typedef struct transformer_hw_servos__action__MoveServo_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} transformer_hw_servos__action__MoveServo_SendGoal_Response;

// Struct for a sequence of transformer_hw_servos__action__MoveServo_SendGoal_Response.
typedef struct transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence
{
  transformer_hw_servos__action__MoveServo_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  transformer_hw_servos__action__MoveServo_SendGoal_Event__request__MAX_SIZE = 1
};
// response
enum
{
  transformer_hw_servos__action__MoveServo_SendGoal_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/MoveServo in the package transformer_hw_servos.
typedef struct transformer_hw_servos__action__MoveServo_SendGoal_Event
{
  service_msgs__msg__ServiceEventInfo info;
  transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence request;
  transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence response;
} transformer_hw_servos__action__MoveServo_SendGoal_Event;

// Struct for a sequence of transformer_hw_servos__action__MoveServo_SendGoal_Event.
typedef struct transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence
{
  transformer_hw_servos__action__MoveServo_SendGoal_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/MoveServo in the package transformer_hw_servos.
typedef struct transformer_hw_servos__action__MoveServo_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} transformer_hw_servos__action__MoveServo_GetResult_Request;

// Struct for a sequence of transformer_hw_servos__action__MoveServo_GetResult_Request.
typedef struct transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence
{
  transformer_hw_servos__action__MoveServo_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"

/// Struct defined in action/MoveServo in the package transformer_hw_servos.
typedef struct transformer_hw_servos__action__MoveServo_GetResult_Response
{
  int8_t status;
  transformer_hw_servos__action__MoveServo_Result result;
} transformer_hw_servos__action__MoveServo_GetResult_Response;

// Struct for a sequence of transformer_hw_servos__action__MoveServo_GetResult_Response.
typedef struct transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence
{
  transformer_hw_servos__action__MoveServo_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  transformer_hw_servos__action__MoveServo_GetResult_Event__request__MAX_SIZE = 1
};
// response
enum
{
  transformer_hw_servos__action__MoveServo_GetResult_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/MoveServo in the package transformer_hw_servos.
typedef struct transformer_hw_servos__action__MoveServo_GetResult_Event
{
  service_msgs__msg__ServiceEventInfo info;
  transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence request;
  transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence response;
} transformer_hw_servos__action__MoveServo_GetResult_Event;

// Struct for a sequence of transformer_hw_servos__action__MoveServo_GetResult_Event.
typedef struct transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence
{
  transformer_hw_servos__action__MoveServo_GetResult_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__struct.h"

/// Struct defined in action/MoveServo in the package transformer_hw_servos.
typedef struct transformer_hw_servos__action__MoveServo_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  transformer_hw_servos__action__MoveServo_Feedback feedback;
} transformer_hw_servos__action__MoveServo_FeedbackMessage;

// Struct for a sequence of transformer_hw_servos__action__MoveServo_FeedbackMessage.
typedef struct transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence
{
  transformer_hw_servos__action__MoveServo_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TRANSFORMER_HW_SERVOS__ACTION__DETAIL__MOVE_SERVO__STRUCT_H_
