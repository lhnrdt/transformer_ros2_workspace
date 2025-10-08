// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from transformer_hw_servos:action/MoveServo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "transformer_hw_servos/action/move_servo.hpp"


#ifndef TRANSFORMER_HW_SERVOS__ACTION__DETAIL__MOVE_SERVO__BUILDER_HPP_
#define TRANSFORMER_HW_SERVOS__ACTION__DETAIL__MOVE_SERVO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "transformer_hw_servos/action/detail/move_servo__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace transformer_hw_servos
{

namespace action
{

namespace builder
{

class Init_MoveServo_Goal_accel_us_per_s2
{
public:
  explicit Init_MoveServo_Goal_accel_us_per_s2(::transformer_hw_servos::action::MoveServo_Goal & msg)
  : msg_(msg)
  {}
  ::transformer_hw_servos::action::MoveServo_Goal accel_us_per_s2(::transformer_hw_servos::action::MoveServo_Goal::_accel_us_per_s2_type arg)
  {
    msg_.accel_us_per_s2 = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_Goal msg_;
};

class Init_MoveServo_Goal_use_trapezoid
{
public:
  explicit Init_MoveServo_Goal_use_trapezoid(::transformer_hw_servos::action::MoveServo_Goal & msg)
  : msg_(msg)
  {}
  Init_MoveServo_Goal_accel_us_per_s2 use_trapezoid(::transformer_hw_servos::action::MoveServo_Goal::_use_trapezoid_type arg)
  {
    msg_.use_trapezoid = std::move(arg);
    return Init_MoveServo_Goal_accel_us_per_s2(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_Goal msg_;
};

class Init_MoveServo_Goal_speed_us_per_s
{
public:
  explicit Init_MoveServo_Goal_speed_us_per_s(::transformer_hw_servos::action::MoveServo_Goal & msg)
  : msg_(msg)
  {}
  Init_MoveServo_Goal_use_trapezoid speed_us_per_s(::transformer_hw_servos::action::MoveServo_Goal::_speed_us_per_s_type arg)
  {
    msg_.speed_us_per_s = std::move(arg);
    return Init_MoveServo_Goal_use_trapezoid(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_Goal msg_;
};

class Init_MoveServo_Goal_pulse_us
{
public:
  explicit Init_MoveServo_Goal_pulse_us(::transformer_hw_servos::action::MoveServo_Goal & msg)
  : msg_(msg)
  {}
  Init_MoveServo_Goal_speed_us_per_s pulse_us(::transformer_hw_servos::action::MoveServo_Goal::_pulse_us_type arg)
  {
    msg_.pulse_us = std::move(arg);
    return Init_MoveServo_Goal_speed_us_per_s(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_Goal msg_;
};

class Init_MoveServo_Goal_channels
{
public:
  Init_MoveServo_Goal_channels()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveServo_Goal_pulse_us channels(::transformer_hw_servos::action::MoveServo_Goal::_channels_type arg)
  {
    msg_.channels = std::move(arg);
    return Init_MoveServo_Goal_pulse_us(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_servos::action::MoveServo_Goal>()
{
  return transformer_hw_servos::action::builder::Init_MoveServo_Goal_channels();
}

}  // namespace transformer_hw_servos


namespace transformer_hw_servos
{

namespace action
{

namespace builder
{

class Init_MoveServo_Result_total_estimated_duration_s
{
public:
  explicit Init_MoveServo_Result_total_estimated_duration_s(::transformer_hw_servos::action::MoveServo_Result & msg)
  : msg_(msg)
  {}
  ::transformer_hw_servos::action::MoveServo_Result total_estimated_duration_s(::transformer_hw_servos::action::MoveServo_Result::_total_estimated_duration_s_type arg)
  {
    msg_.total_estimated_duration_s = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_Result msg_;
};

class Init_MoveServo_Result_final_pulses_us
{
public:
  explicit Init_MoveServo_Result_final_pulses_us(::transformer_hw_servos::action::MoveServo_Result & msg)
  : msg_(msg)
  {}
  Init_MoveServo_Result_total_estimated_duration_s final_pulses_us(::transformer_hw_servos::action::MoveServo_Result::_final_pulses_us_type arg)
  {
    msg_.final_pulses_us = std::move(arg);
    return Init_MoveServo_Result_total_estimated_duration_s(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_Result msg_;
};

class Init_MoveServo_Result_message
{
public:
  explicit Init_MoveServo_Result_message(::transformer_hw_servos::action::MoveServo_Result & msg)
  : msg_(msg)
  {}
  Init_MoveServo_Result_final_pulses_us message(::transformer_hw_servos::action::MoveServo_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_MoveServo_Result_final_pulses_us(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_Result msg_;
};

class Init_MoveServo_Result_success
{
public:
  Init_MoveServo_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveServo_Result_message success(::transformer_hw_servos::action::MoveServo_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_MoveServo_Result_message(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_servos::action::MoveServo_Result>()
{
  return transformer_hw_servos::action::builder::Init_MoveServo_Result_success();
}

}  // namespace transformer_hw_servos


namespace transformer_hw_servos
{

namespace action
{

namespace builder
{

class Init_MoveServo_Feedback_phase
{
public:
  explicit Init_MoveServo_Feedback_phase(::transformer_hw_servos::action::MoveServo_Feedback & msg)
  : msg_(msg)
  {}
  ::transformer_hw_servos::action::MoveServo_Feedback phase(::transformer_hw_servos::action::MoveServo_Feedback::_phase_type arg)
  {
    msg_.phase = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_Feedback msg_;
};

class Init_MoveServo_Feedback_estimated_remaining_s
{
public:
  explicit Init_MoveServo_Feedback_estimated_remaining_s(::transformer_hw_servos::action::MoveServo_Feedback & msg)
  : msg_(msg)
  {}
  Init_MoveServo_Feedback_phase estimated_remaining_s(::transformer_hw_servos::action::MoveServo_Feedback::_estimated_remaining_s_type arg)
  {
    msg_.estimated_remaining_s = std::move(arg);
    return Init_MoveServo_Feedback_phase(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_Feedback msg_;
};

class Init_MoveServo_Feedback_progress
{
public:
  explicit Init_MoveServo_Feedback_progress(::transformer_hw_servos::action::MoveServo_Feedback & msg)
  : msg_(msg)
  {}
  Init_MoveServo_Feedback_estimated_remaining_s progress(::transformer_hw_servos::action::MoveServo_Feedback::_progress_type arg)
  {
    msg_.progress = std::move(arg);
    return Init_MoveServo_Feedback_estimated_remaining_s(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_Feedback msg_;
};

class Init_MoveServo_Feedback_current_pulses_us
{
public:
  Init_MoveServo_Feedback_current_pulses_us()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveServo_Feedback_progress current_pulses_us(::transformer_hw_servos::action::MoveServo_Feedback::_current_pulses_us_type arg)
  {
    msg_.current_pulses_us = std::move(arg);
    return Init_MoveServo_Feedback_progress(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_servos::action::MoveServo_Feedback>()
{
  return transformer_hw_servos::action::builder::Init_MoveServo_Feedback_current_pulses_us();
}

}  // namespace transformer_hw_servos


namespace transformer_hw_servos
{

namespace action
{

namespace builder
{

class Init_MoveServo_SendGoal_Request_goal
{
public:
  explicit Init_MoveServo_SendGoal_Request_goal(::transformer_hw_servos::action::MoveServo_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::transformer_hw_servos::action::MoveServo_SendGoal_Request goal(::transformer_hw_servos::action::MoveServo_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_SendGoal_Request msg_;
};

class Init_MoveServo_SendGoal_Request_goal_id
{
public:
  Init_MoveServo_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveServo_SendGoal_Request_goal goal_id(::transformer_hw_servos::action::MoveServo_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_MoveServo_SendGoal_Request_goal(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_servos::action::MoveServo_SendGoal_Request>()
{
  return transformer_hw_servos::action::builder::Init_MoveServo_SendGoal_Request_goal_id();
}

}  // namespace transformer_hw_servos


namespace transformer_hw_servos
{

namespace action
{

namespace builder
{

class Init_MoveServo_SendGoal_Response_stamp
{
public:
  explicit Init_MoveServo_SendGoal_Response_stamp(::transformer_hw_servos::action::MoveServo_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::transformer_hw_servos::action::MoveServo_SendGoal_Response stamp(::transformer_hw_servos::action::MoveServo_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_SendGoal_Response msg_;
};

class Init_MoveServo_SendGoal_Response_accepted
{
public:
  Init_MoveServo_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveServo_SendGoal_Response_stamp accepted(::transformer_hw_servos::action::MoveServo_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_MoveServo_SendGoal_Response_stamp(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_servos::action::MoveServo_SendGoal_Response>()
{
  return transformer_hw_servos::action::builder::Init_MoveServo_SendGoal_Response_accepted();
}

}  // namespace transformer_hw_servos


namespace transformer_hw_servos
{

namespace action
{

namespace builder
{

class Init_MoveServo_SendGoal_Event_response
{
public:
  explicit Init_MoveServo_SendGoal_Event_response(::transformer_hw_servos::action::MoveServo_SendGoal_Event & msg)
  : msg_(msg)
  {}
  ::transformer_hw_servos::action::MoveServo_SendGoal_Event response(::transformer_hw_servos::action::MoveServo_SendGoal_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_SendGoal_Event msg_;
};

class Init_MoveServo_SendGoal_Event_request
{
public:
  explicit Init_MoveServo_SendGoal_Event_request(::transformer_hw_servos::action::MoveServo_SendGoal_Event & msg)
  : msg_(msg)
  {}
  Init_MoveServo_SendGoal_Event_response request(::transformer_hw_servos::action::MoveServo_SendGoal_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_MoveServo_SendGoal_Event_response(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_SendGoal_Event msg_;
};

class Init_MoveServo_SendGoal_Event_info
{
public:
  Init_MoveServo_SendGoal_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveServo_SendGoal_Event_request info(::transformer_hw_servos::action::MoveServo_SendGoal_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_MoveServo_SendGoal_Event_request(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_SendGoal_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_servos::action::MoveServo_SendGoal_Event>()
{
  return transformer_hw_servos::action::builder::Init_MoveServo_SendGoal_Event_info();
}

}  // namespace transformer_hw_servos


namespace transformer_hw_servos
{

namespace action
{

namespace builder
{

class Init_MoveServo_GetResult_Request_goal_id
{
public:
  Init_MoveServo_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::transformer_hw_servos::action::MoveServo_GetResult_Request goal_id(::transformer_hw_servos::action::MoveServo_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_servos::action::MoveServo_GetResult_Request>()
{
  return transformer_hw_servos::action::builder::Init_MoveServo_GetResult_Request_goal_id();
}

}  // namespace transformer_hw_servos


namespace transformer_hw_servos
{

namespace action
{

namespace builder
{

class Init_MoveServo_GetResult_Response_result
{
public:
  explicit Init_MoveServo_GetResult_Response_result(::transformer_hw_servos::action::MoveServo_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::transformer_hw_servos::action::MoveServo_GetResult_Response result(::transformer_hw_servos::action::MoveServo_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_GetResult_Response msg_;
};

class Init_MoveServo_GetResult_Response_status
{
public:
  Init_MoveServo_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveServo_GetResult_Response_result status(::transformer_hw_servos::action::MoveServo_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_MoveServo_GetResult_Response_result(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_servos::action::MoveServo_GetResult_Response>()
{
  return transformer_hw_servos::action::builder::Init_MoveServo_GetResult_Response_status();
}

}  // namespace transformer_hw_servos


namespace transformer_hw_servos
{

namespace action
{

namespace builder
{

class Init_MoveServo_GetResult_Event_response
{
public:
  explicit Init_MoveServo_GetResult_Event_response(::transformer_hw_servos::action::MoveServo_GetResult_Event & msg)
  : msg_(msg)
  {}
  ::transformer_hw_servos::action::MoveServo_GetResult_Event response(::transformer_hw_servos::action::MoveServo_GetResult_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_GetResult_Event msg_;
};

class Init_MoveServo_GetResult_Event_request
{
public:
  explicit Init_MoveServo_GetResult_Event_request(::transformer_hw_servos::action::MoveServo_GetResult_Event & msg)
  : msg_(msg)
  {}
  Init_MoveServo_GetResult_Event_response request(::transformer_hw_servos::action::MoveServo_GetResult_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_MoveServo_GetResult_Event_response(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_GetResult_Event msg_;
};

class Init_MoveServo_GetResult_Event_info
{
public:
  Init_MoveServo_GetResult_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveServo_GetResult_Event_request info(::transformer_hw_servos::action::MoveServo_GetResult_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_MoveServo_GetResult_Event_request(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_GetResult_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_servos::action::MoveServo_GetResult_Event>()
{
  return transformer_hw_servos::action::builder::Init_MoveServo_GetResult_Event_info();
}

}  // namespace transformer_hw_servos


namespace transformer_hw_servos
{

namespace action
{

namespace builder
{

class Init_MoveServo_FeedbackMessage_feedback
{
public:
  explicit Init_MoveServo_FeedbackMessage_feedback(::transformer_hw_servos::action::MoveServo_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::transformer_hw_servos::action::MoveServo_FeedbackMessage feedback(::transformer_hw_servos::action::MoveServo_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_FeedbackMessage msg_;
};

class Init_MoveServo_FeedbackMessage_goal_id
{
public:
  Init_MoveServo_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveServo_FeedbackMessage_feedback goal_id(::transformer_hw_servos::action::MoveServo_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_MoveServo_FeedbackMessage_feedback(msg_);
  }

private:
  ::transformer_hw_servos::action::MoveServo_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_servos::action::MoveServo_FeedbackMessage>()
{
  return transformer_hw_servos::action::builder::Init_MoveServo_FeedbackMessage_goal_id();
}

}  // namespace transformer_hw_servos

#endif  // TRANSFORMER_HW_SERVOS__ACTION__DETAIL__MOVE_SERVO__BUILDER_HPP_
