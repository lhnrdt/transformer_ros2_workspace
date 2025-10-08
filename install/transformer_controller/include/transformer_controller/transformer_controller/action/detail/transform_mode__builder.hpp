// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from transformer_controller:action/TransformMode.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "transformer_controller/action/transform_mode.hpp"


#ifndef TRANSFORMER_CONTROLLER__ACTION__DETAIL__TRANSFORM_MODE__BUILDER_HPP_
#define TRANSFORMER_CONTROLLER__ACTION__DETAIL__TRANSFORM_MODE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "transformer_controller/action/detail/transform_mode__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace transformer_controller
{

namespace action
{

namespace builder
{

class Init_TransformMode_Goal_target_mode
{
public:
  Init_TransformMode_Goal_target_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::transformer_controller::action::TransformMode_Goal target_mode(::transformer_controller::action::TransformMode_Goal::_target_mode_type arg)
  {
    msg_.target_mode = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_controller::action::TransformMode_Goal>()
{
  return transformer_controller::action::builder::Init_TransformMode_Goal_target_mode();
}

}  // namespace transformer_controller


namespace transformer_controller
{

namespace action
{

namespace builder
{

class Init_TransformMode_Result_final_mode
{
public:
  explicit Init_TransformMode_Result_final_mode(::transformer_controller::action::TransformMode_Result & msg)
  : msg_(msg)
  {}
  ::transformer_controller::action::TransformMode_Result final_mode(::transformer_controller::action::TransformMode_Result::_final_mode_type arg)
  {
    msg_.final_mode = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_Result msg_;
};

class Init_TransformMode_Result_message
{
public:
  explicit Init_TransformMode_Result_message(::transformer_controller::action::TransformMode_Result & msg)
  : msg_(msg)
  {}
  Init_TransformMode_Result_final_mode message(::transformer_controller::action::TransformMode_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_TransformMode_Result_final_mode(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_Result msg_;
};

class Init_TransformMode_Result_success
{
public:
  Init_TransformMode_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TransformMode_Result_message success(::transformer_controller::action::TransformMode_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_TransformMode_Result_message(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_controller::action::TransformMode_Result>()
{
  return transformer_controller::action::builder::Init_TransformMode_Result_success();
}

}  // namespace transformer_controller


namespace transformer_controller
{

namespace action
{

namespace builder
{

class Init_TransformMode_Feedback_phase
{
public:
  explicit Init_TransformMode_Feedback_phase(::transformer_controller::action::TransformMode_Feedback & msg)
  : msg_(msg)
  {}
  ::transformer_controller::action::TransformMode_Feedback phase(::transformer_controller::action::TransformMode_Feedback::_phase_type arg)
  {
    msg_.phase = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_Feedback msg_;
};

class Init_TransformMode_Feedback_progress
{
public:
  Init_TransformMode_Feedback_progress()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TransformMode_Feedback_phase progress(::transformer_controller::action::TransformMode_Feedback::_progress_type arg)
  {
    msg_.progress = std::move(arg);
    return Init_TransformMode_Feedback_phase(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_controller::action::TransformMode_Feedback>()
{
  return transformer_controller::action::builder::Init_TransformMode_Feedback_progress();
}

}  // namespace transformer_controller


namespace transformer_controller
{

namespace action
{

namespace builder
{

class Init_TransformMode_SendGoal_Request_goal
{
public:
  explicit Init_TransformMode_SendGoal_Request_goal(::transformer_controller::action::TransformMode_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::transformer_controller::action::TransformMode_SendGoal_Request goal(::transformer_controller::action::TransformMode_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_SendGoal_Request msg_;
};

class Init_TransformMode_SendGoal_Request_goal_id
{
public:
  Init_TransformMode_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TransformMode_SendGoal_Request_goal goal_id(::transformer_controller::action::TransformMode_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_TransformMode_SendGoal_Request_goal(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_controller::action::TransformMode_SendGoal_Request>()
{
  return transformer_controller::action::builder::Init_TransformMode_SendGoal_Request_goal_id();
}

}  // namespace transformer_controller


namespace transformer_controller
{

namespace action
{

namespace builder
{

class Init_TransformMode_SendGoal_Response_stamp
{
public:
  explicit Init_TransformMode_SendGoal_Response_stamp(::transformer_controller::action::TransformMode_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::transformer_controller::action::TransformMode_SendGoal_Response stamp(::transformer_controller::action::TransformMode_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_SendGoal_Response msg_;
};

class Init_TransformMode_SendGoal_Response_accepted
{
public:
  Init_TransformMode_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TransformMode_SendGoal_Response_stamp accepted(::transformer_controller::action::TransformMode_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_TransformMode_SendGoal_Response_stamp(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_controller::action::TransformMode_SendGoal_Response>()
{
  return transformer_controller::action::builder::Init_TransformMode_SendGoal_Response_accepted();
}

}  // namespace transformer_controller


namespace transformer_controller
{

namespace action
{

namespace builder
{

class Init_TransformMode_SendGoal_Event_response
{
public:
  explicit Init_TransformMode_SendGoal_Event_response(::transformer_controller::action::TransformMode_SendGoal_Event & msg)
  : msg_(msg)
  {}
  ::transformer_controller::action::TransformMode_SendGoal_Event response(::transformer_controller::action::TransformMode_SendGoal_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_SendGoal_Event msg_;
};

class Init_TransformMode_SendGoal_Event_request
{
public:
  explicit Init_TransformMode_SendGoal_Event_request(::transformer_controller::action::TransformMode_SendGoal_Event & msg)
  : msg_(msg)
  {}
  Init_TransformMode_SendGoal_Event_response request(::transformer_controller::action::TransformMode_SendGoal_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_TransformMode_SendGoal_Event_response(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_SendGoal_Event msg_;
};

class Init_TransformMode_SendGoal_Event_info
{
public:
  Init_TransformMode_SendGoal_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TransformMode_SendGoal_Event_request info(::transformer_controller::action::TransformMode_SendGoal_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_TransformMode_SendGoal_Event_request(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_SendGoal_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_controller::action::TransformMode_SendGoal_Event>()
{
  return transformer_controller::action::builder::Init_TransformMode_SendGoal_Event_info();
}

}  // namespace transformer_controller


namespace transformer_controller
{

namespace action
{

namespace builder
{

class Init_TransformMode_GetResult_Request_goal_id
{
public:
  Init_TransformMode_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::transformer_controller::action::TransformMode_GetResult_Request goal_id(::transformer_controller::action::TransformMode_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_controller::action::TransformMode_GetResult_Request>()
{
  return transformer_controller::action::builder::Init_TransformMode_GetResult_Request_goal_id();
}

}  // namespace transformer_controller


namespace transformer_controller
{

namespace action
{

namespace builder
{

class Init_TransformMode_GetResult_Response_result
{
public:
  explicit Init_TransformMode_GetResult_Response_result(::transformer_controller::action::TransformMode_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::transformer_controller::action::TransformMode_GetResult_Response result(::transformer_controller::action::TransformMode_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_GetResult_Response msg_;
};

class Init_TransformMode_GetResult_Response_status
{
public:
  Init_TransformMode_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TransformMode_GetResult_Response_result status(::transformer_controller::action::TransformMode_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_TransformMode_GetResult_Response_result(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_controller::action::TransformMode_GetResult_Response>()
{
  return transformer_controller::action::builder::Init_TransformMode_GetResult_Response_status();
}

}  // namespace transformer_controller


namespace transformer_controller
{

namespace action
{

namespace builder
{

class Init_TransformMode_GetResult_Event_response
{
public:
  explicit Init_TransformMode_GetResult_Event_response(::transformer_controller::action::TransformMode_GetResult_Event & msg)
  : msg_(msg)
  {}
  ::transformer_controller::action::TransformMode_GetResult_Event response(::transformer_controller::action::TransformMode_GetResult_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_GetResult_Event msg_;
};

class Init_TransformMode_GetResult_Event_request
{
public:
  explicit Init_TransformMode_GetResult_Event_request(::transformer_controller::action::TransformMode_GetResult_Event & msg)
  : msg_(msg)
  {}
  Init_TransformMode_GetResult_Event_response request(::transformer_controller::action::TransformMode_GetResult_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_TransformMode_GetResult_Event_response(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_GetResult_Event msg_;
};

class Init_TransformMode_GetResult_Event_info
{
public:
  Init_TransformMode_GetResult_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TransformMode_GetResult_Event_request info(::transformer_controller::action::TransformMode_GetResult_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_TransformMode_GetResult_Event_request(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_GetResult_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_controller::action::TransformMode_GetResult_Event>()
{
  return transformer_controller::action::builder::Init_TransformMode_GetResult_Event_info();
}

}  // namespace transformer_controller


namespace transformer_controller
{

namespace action
{

namespace builder
{

class Init_TransformMode_FeedbackMessage_feedback
{
public:
  explicit Init_TransformMode_FeedbackMessage_feedback(::transformer_controller::action::TransformMode_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::transformer_controller::action::TransformMode_FeedbackMessage feedback(::transformer_controller::action::TransformMode_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_FeedbackMessage msg_;
};

class Init_TransformMode_FeedbackMessage_goal_id
{
public:
  Init_TransformMode_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TransformMode_FeedbackMessage_feedback goal_id(::transformer_controller::action::TransformMode_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_TransformMode_FeedbackMessage_feedback(msg_);
  }

private:
  ::transformer_controller::action::TransformMode_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_controller::action::TransformMode_FeedbackMessage>()
{
  return transformer_controller::action::builder::Init_TransformMode_FeedbackMessage_goal_id();
}

}  // namespace transformer_controller

#endif  // TRANSFORMER_CONTROLLER__ACTION__DETAIL__TRANSFORM_MODE__BUILDER_HPP_
