// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from transformer_hw_actuators:action/MoveActuator.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "transformer_hw_actuators/action/move_actuator.hpp"


#ifndef TRANSFORMER_HW_ACTUATORS__ACTION__DETAIL__MOVE_ACTUATOR__BUILDER_HPP_
#define TRANSFORMER_HW_ACTUATORS__ACTION__DETAIL__MOVE_ACTUATOR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "transformer_hw_actuators/action/detail/move_actuator__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace transformer_hw_actuators
{

namespace action
{

namespace builder
{

class Init_MoveActuator_Goal_duration_ms
{
public:
  explicit Init_MoveActuator_Goal_duration_ms(::transformer_hw_actuators::action::MoveActuator_Goal & msg)
  : msg_(msg)
  {}
  ::transformer_hw_actuators::action::MoveActuator_Goal duration_ms(::transformer_hw_actuators::action::MoveActuator_Goal::_duration_ms_type arg)
  {
    msg_.duration_ms = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_Goal msg_;
};

class Init_MoveActuator_Goal_speed_percents
{
public:
  explicit Init_MoveActuator_Goal_speed_percents(::transformer_hw_actuators::action::MoveActuator_Goal & msg)
  : msg_(msg)
  {}
  Init_MoveActuator_Goal_duration_ms speed_percents(::transformer_hw_actuators::action::MoveActuator_Goal::_speed_percents_type arg)
  {
    msg_.speed_percents = std::move(arg);
    return Init_MoveActuator_Goal_duration_ms(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_Goal msg_;
};

class Init_MoveActuator_Goal_actuators
{
public:
  Init_MoveActuator_Goal_actuators()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveActuator_Goal_speed_percents actuators(::transformer_hw_actuators::action::MoveActuator_Goal::_actuators_type arg)
  {
    msg_.actuators = std::move(arg);
    return Init_MoveActuator_Goal_speed_percents(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_actuators::action::MoveActuator_Goal>()
{
  return transformer_hw_actuators::action::builder::Init_MoveActuator_Goal_actuators();
}

}  // namespace transformer_hw_actuators


namespace transformer_hw_actuators
{

namespace action
{

namespace builder
{

class Init_MoveActuator_Result_message
{
public:
  explicit Init_MoveActuator_Result_message(::transformer_hw_actuators::action::MoveActuator_Result & msg)
  : msg_(msg)
  {}
  ::transformer_hw_actuators::action::MoveActuator_Result message(::transformer_hw_actuators::action::MoveActuator_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_Result msg_;
};

class Init_MoveActuator_Result_success
{
public:
  Init_MoveActuator_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveActuator_Result_message success(::transformer_hw_actuators::action::MoveActuator_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_MoveActuator_Result_message(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_actuators::action::MoveActuator_Result>()
{
  return transformer_hw_actuators::action::builder::Init_MoveActuator_Result_success();
}

}  // namespace transformer_hw_actuators


namespace transformer_hw_actuators
{

namespace action
{

namespace builder
{

class Init_MoveActuator_Feedback_remaining_ms
{
public:
  explicit Init_MoveActuator_Feedback_remaining_ms(::transformer_hw_actuators::action::MoveActuator_Feedback & msg)
  : msg_(msg)
  {}
  ::transformer_hw_actuators::action::MoveActuator_Feedback remaining_ms(::transformer_hw_actuators::action::MoveActuator_Feedback::_remaining_ms_type arg)
  {
    msg_.remaining_ms = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_Feedback msg_;
};

class Init_MoveActuator_Feedback_elapsed_ms
{
public:
  explicit Init_MoveActuator_Feedback_elapsed_ms(::transformer_hw_actuators::action::MoveActuator_Feedback & msg)
  : msg_(msg)
  {}
  Init_MoveActuator_Feedback_remaining_ms elapsed_ms(::transformer_hw_actuators::action::MoveActuator_Feedback::_elapsed_ms_type arg)
  {
    msg_.elapsed_ms = std::move(arg);
    return Init_MoveActuator_Feedback_remaining_ms(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_Feedback msg_;
};

class Init_MoveActuator_Feedback_current_speed_percents
{
public:
  Init_MoveActuator_Feedback_current_speed_percents()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveActuator_Feedback_elapsed_ms current_speed_percents(::transformer_hw_actuators::action::MoveActuator_Feedback::_current_speed_percents_type arg)
  {
    msg_.current_speed_percents = std::move(arg);
    return Init_MoveActuator_Feedback_elapsed_ms(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_actuators::action::MoveActuator_Feedback>()
{
  return transformer_hw_actuators::action::builder::Init_MoveActuator_Feedback_current_speed_percents();
}

}  // namespace transformer_hw_actuators


namespace transformer_hw_actuators
{

namespace action
{

namespace builder
{

class Init_MoveActuator_SendGoal_Request_goal
{
public:
  explicit Init_MoveActuator_SendGoal_Request_goal(::transformer_hw_actuators::action::MoveActuator_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::transformer_hw_actuators::action::MoveActuator_SendGoal_Request goal(::transformer_hw_actuators::action::MoveActuator_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_SendGoal_Request msg_;
};

class Init_MoveActuator_SendGoal_Request_goal_id
{
public:
  Init_MoveActuator_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveActuator_SendGoal_Request_goal goal_id(::transformer_hw_actuators::action::MoveActuator_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_MoveActuator_SendGoal_Request_goal(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_actuators::action::MoveActuator_SendGoal_Request>()
{
  return transformer_hw_actuators::action::builder::Init_MoveActuator_SendGoal_Request_goal_id();
}

}  // namespace transformer_hw_actuators


namespace transformer_hw_actuators
{

namespace action
{

namespace builder
{

class Init_MoveActuator_SendGoal_Response_stamp
{
public:
  explicit Init_MoveActuator_SendGoal_Response_stamp(::transformer_hw_actuators::action::MoveActuator_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::transformer_hw_actuators::action::MoveActuator_SendGoal_Response stamp(::transformer_hw_actuators::action::MoveActuator_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_SendGoal_Response msg_;
};

class Init_MoveActuator_SendGoal_Response_accepted
{
public:
  Init_MoveActuator_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveActuator_SendGoal_Response_stamp accepted(::transformer_hw_actuators::action::MoveActuator_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_MoveActuator_SendGoal_Response_stamp(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_actuators::action::MoveActuator_SendGoal_Response>()
{
  return transformer_hw_actuators::action::builder::Init_MoveActuator_SendGoal_Response_accepted();
}

}  // namespace transformer_hw_actuators


namespace transformer_hw_actuators
{

namespace action
{

namespace builder
{

class Init_MoveActuator_SendGoal_Event_response
{
public:
  explicit Init_MoveActuator_SendGoal_Event_response(::transformer_hw_actuators::action::MoveActuator_SendGoal_Event & msg)
  : msg_(msg)
  {}
  ::transformer_hw_actuators::action::MoveActuator_SendGoal_Event response(::transformer_hw_actuators::action::MoveActuator_SendGoal_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_SendGoal_Event msg_;
};

class Init_MoveActuator_SendGoal_Event_request
{
public:
  explicit Init_MoveActuator_SendGoal_Event_request(::transformer_hw_actuators::action::MoveActuator_SendGoal_Event & msg)
  : msg_(msg)
  {}
  Init_MoveActuator_SendGoal_Event_response request(::transformer_hw_actuators::action::MoveActuator_SendGoal_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_MoveActuator_SendGoal_Event_response(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_SendGoal_Event msg_;
};

class Init_MoveActuator_SendGoal_Event_info
{
public:
  Init_MoveActuator_SendGoal_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveActuator_SendGoal_Event_request info(::transformer_hw_actuators::action::MoveActuator_SendGoal_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_MoveActuator_SendGoal_Event_request(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_SendGoal_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_actuators::action::MoveActuator_SendGoal_Event>()
{
  return transformer_hw_actuators::action::builder::Init_MoveActuator_SendGoal_Event_info();
}

}  // namespace transformer_hw_actuators


namespace transformer_hw_actuators
{

namespace action
{

namespace builder
{

class Init_MoveActuator_GetResult_Request_goal_id
{
public:
  Init_MoveActuator_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::transformer_hw_actuators::action::MoveActuator_GetResult_Request goal_id(::transformer_hw_actuators::action::MoveActuator_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_actuators::action::MoveActuator_GetResult_Request>()
{
  return transformer_hw_actuators::action::builder::Init_MoveActuator_GetResult_Request_goal_id();
}

}  // namespace transformer_hw_actuators


namespace transformer_hw_actuators
{

namespace action
{

namespace builder
{

class Init_MoveActuator_GetResult_Response_result
{
public:
  explicit Init_MoveActuator_GetResult_Response_result(::transformer_hw_actuators::action::MoveActuator_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::transformer_hw_actuators::action::MoveActuator_GetResult_Response result(::transformer_hw_actuators::action::MoveActuator_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_GetResult_Response msg_;
};

class Init_MoveActuator_GetResult_Response_status
{
public:
  Init_MoveActuator_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveActuator_GetResult_Response_result status(::transformer_hw_actuators::action::MoveActuator_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_MoveActuator_GetResult_Response_result(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_actuators::action::MoveActuator_GetResult_Response>()
{
  return transformer_hw_actuators::action::builder::Init_MoveActuator_GetResult_Response_status();
}

}  // namespace transformer_hw_actuators


namespace transformer_hw_actuators
{

namespace action
{

namespace builder
{

class Init_MoveActuator_GetResult_Event_response
{
public:
  explicit Init_MoveActuator_GetResult_Event_response(::transformer_hw_actuators::action::MoveActuator_GetResult_Event & msg)
  : msg_(msg)
  {}
  ::transformer_hw_actuators::action::MoveActuator_GetResult_Event response(::transformer_hw_actuators::action::MoveActuator_GetResult_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_GetResult_Event msg_;
};

class Init_MoveActuator_GetResult_Event_request
{
public:
  explicit Init_MoveActuator_GetResult_Event_request(::transformer_hw_actuators::action::MoveActuator_GetResult_Event & msg)
  : msg_(msg)
  {}
  Init_MoveActuator_GetResult_Event_response request(::transformer_hw_actuators::action::MoveActuator_GetResult_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_MoveActuator_GetResult_Event_response(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_GetResult_Event msg_;
};

class Init_MoveActuator_GetResult_Event_info
{
public:
  Init_MoveActuator_GetResult_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveActuator_GetResult_Event_request info(::transformer_hw_actuators::action::MoveActuator_GetResult_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_MoveActuator_GetResult_Event_request(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_GetResult_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_actuators::action::MoveActuator_GetResult_Event>()
{
  return transformer_hw_actuators::action::builder::Init_MoveActuator_GetResult_Event_info();
}

}  // namespace transformer_hw_actuators


namespace transformer_hw_actuators
{

namespace action
{

namespace builder
{

class Init_MoveActuator_FeedbackMessage_feedback
{
public:
  explicit Init_MoveActuator_FeedbackMessage_feedback(::transformer_hw_actuators::action::MoveActuator_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::transformer_hw_actuators::action::MoveActuator_FeedbackMessage feedback(::transformer_hw_actuators::action::MoveActuator_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_FeedbackMessage msg_;
};

class Init_MoveActuator_FeedbackMessage_goal_id
{
public:
  Init_MoveActuator_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveActuator_FeedbackMessage_feedback goal_id(::transformer_hw_actuators::action::MoveActuator_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_MoveActuator_FeedbackMessage_feedback(msg_);
  }

private:
  ::transformer_hw_actuators::action::MoveActuator_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_hw_actuators::action::MoveActuator_FeedbackMessage>()
{
  return transformer_hw_actuators::action::builder::Init_MoveActuator_FeedbackMessage_goal_id();
}

}  // namespace transformer_hw_actuators

#endif  // TRANSFORMER_HW_ACTUATORS__ACTION__DETAIL__MOVE_ACTUATOR__BUILDER_HPP_
