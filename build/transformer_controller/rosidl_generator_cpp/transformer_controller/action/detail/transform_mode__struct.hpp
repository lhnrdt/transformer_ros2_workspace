// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from transformer_controller:action/TransformMode.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "transformer_controller/action/transform_mode.hpp"


#ifndef TRANSFORMER_CONTROLLER__ACTION__DETAIL__TRANSFORM_MODE__STRUCT_HPP_
#define TRANSFORMER_CONTROLLER__ACTION__DETAIL__TRANSFORM_MODE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__transformer_controller__action__TransformMode_Goal __attribute__((deprecated))
#else
# define DEPRECATED__transformer_controller__action__TransformMode_Goal __declspec(deprecated)
#endif

namespace transformer_controller
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct TransformMode_Goal_
{
  using Type = TransformMode_Goal_<ContainerAllocator>;

  explicit TransformMode_Goal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->target_mode = "";
    }
  }

  explicit TransformMode_Goal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : target_mode(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->target_mode = "";
    }
  }

  // field types and members
  using _target_mode_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _target_mode_type target_mode;

  // setters for named parameter idiom
  Type & set__target_mode(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->target_mode = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    transformer_controller::action::TransformMode_Goal_<ContainerAllocator> *;
  using ConstRawPtr =
    const transformer_controller::action::TransformMode_Goal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_Goal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_Goal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_Goal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_Goal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_Goal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_Goal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_Goal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_Goal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__transformer_controller__action__TransformMode_Goal
    std::shared_ptr<transformer_controller::action::TransformMode_Goal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__transformer_controller__action__TransformMode_Goal
    std::shared_ptr<transformer_controller::action::TransformMode_Goal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TransformMode_Goal_ & other) const
  {
    if (this->target_mode != other.target_mode) {
      return false;
    }
    return true;
  }
  bool operator!=(const TransformMode_Goal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TransformMode_Goal_

// alias to use template instance with default allocator
using TransformMode_Goal =
  transformer_controller::action::TransformMode_Goal_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace transformer_controller


#ifndef _WIN32
# define DEPRECATED__transformer_controller__action__TransformMode_Result __attribute__((deprecated))
#else
# define DEPRECATED__transformer_controller__action__TransformMode_Result __declspec(deprecated)
#endif

namespace transformer_controller
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct TransformMode_Result_
{
  using Type = TransformMode_Result_<ContainerAllocator>;

  explicit TransformMode_Result_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
      this->final_mode = "";
    }
  }

  explicit TransformMode_Result_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc),
    final_mode(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
      this->final_mode = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;
  using _final_mode_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _final_mode_type final_mode;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }
  Type & set__final_mode(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->final_mode = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    transformer_controller::action::TransformMode_Result_<ContainerAllocator> *;
  using ConstRawPtr =
    const transformer_controller::action::TransformMode_Result_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_Result_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_Result_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_Result_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_Result_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_Result_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_Result_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_Result_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_Result_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__transformer_controller__action__TransformMode_Result
    std::shared_ptr<transformer_controller::action::TransformMode_Result_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__transformer_controller__action__TransformMode_Result
    std::shared_ptr<transformer_controller::action::TransformMode_Result_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TransformMode_Result_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    if (this->final_mode != other.final_mode) {
      return false;
    }
    return true;
  }
  bool operator!=(const TransformMode_Result_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TransformMode_Result_

// alias to use template instance with default allocator
using TransformMode_Result =
  transformer_controller::action::TransformMode_Result_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace transformer_controller


#ifndef _WIN32
# define DEPRECATED__transformer_controller__action__TransformMode_Feedback __attribute__((deprecated))
#else
# define DEPRECATED__transformer_controller__action__TransformMode_Feedback __declspec(deprecated)
#endif

namespace transformer_controller
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct TransformMode_Feedback_
{
  using Type = TransformMode_Feedback_<ContainerAllocator>;

  explicit TransformMode_Feedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->progress = 0.0f;
      this->phase = "";
    }
  }

  explicit TransformMode_Feedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : phase(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->progress = 0.0f;
      this->phase = "";
    }
  }

  // field types and members
  using _progress_type =
    float;
  _progress_type progress;
  using _phase_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _phase_type phase;

  // setters for named parameter idiom
  Type & set__progress(
    const float & _arg)
  {
    this->progress = _arg;
    return *this;
  }
  Type & set__phase(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->phase = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    transformer_controller::action::TransformMode_Feedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const transformer_controller::action::TransformMode_Feedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_Feedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_Feedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_Feedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_Feedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_Feedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_Feedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_Feedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_Feedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__transformer_controller__action__TransformMode_Feedback
    std::shared_ptr<transformer_controller::action::TransformMode_Feedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__transformer_controller__action__TransformMode_Feedback
    std::shared_ptr<transformer_controller::action::TransformMode_Feedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TransformMode_Feedback_ & other) const
  {
    if (this->progress != other.progress) {
      return false;
    }
    if (this->phase != other.phase) {
      return false;
    }
    return true;
  }
  bool operator!=(const TransformMode_Feedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TransformMode_Feedback_

// alias to use template instance with default allocator
using TransformMode_Feedback =
  transformer_controller::action::TransformMode_Feedback_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace transformer_controller


// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'goal'
#include "transformer_controller/action/detail/transform_mode__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__transformer_controller__action__TransformMode_SendGoal_Request __attribute__((deprecated))
#else
# define DEPRECATED__transformer_controller__action__TransformMode_SendGoal_Request __declspec(deprecated)
#endif

namespace transformer_controller
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct TransformMode_SendGoal_Request_
{
  using Type = TransformMode_SendGoal_Request_<ContainerAllocator>;

  explicit TransformMode_SendGoal_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    goal(_init)
  {
    (void)_init;
  }

  explicit TransformMode_SendGoal_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    goal(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _goal_type =
    transformer_controller::action::TransformMode_Goal_<ContainerAllocator>;
  _goal_type goal;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__goal(
    const transformer_controller::action::TransformMode_Goal_<ContainerAllocator> & _arg)
  {
    this->goal = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    transformer_controller::action::TransformMode_SendGoal_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const transformer_controller::action::TransformMode_SendGoal_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_SendGoal_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_SendGoal_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_SendGoal_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_SendGoal_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_SendGoal_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_SendGoal_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_SendGoal_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_SendGoal_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__transformer_controller__action__TransformMode_SendGoal_Request
    std::shared_ptr<transformer_controller::action::TransformMode_SendGoal_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__transformer_controller__action__TransformMode_SendGoal_Request
    std::shared_ptr<transformer_controller::action::TransformMode_SendGoal_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TransformMode_SendGoal_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->goal != other.goal) {
      return false;
    }
    return true;
  }
  bool operator!=(const TransformMode_SendGoal_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TransformMode_SendGoal_Request_

// alias to use template instance with default allocator
using TransformMode_SendGoal_Request =
  transformer_controller::action::TransformMode_SendGoal_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace transformer_controller


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__transformer_controller__action__TransformMode_SendGoal_Response __attribute__((deprecated))
#else
# define DEPRECATED__transformer_controller__action__TransformMode_SendGoal_Response __declspec(deprecated)
#endif

namespace transformer_controller
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct TransformMode_SendGoal_Response_
{
  using Type = TransformMode_SendGoal_Response_<ContainerAllocator>;

  explicit TransformMode_SendGoal_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  explicit TransformMode_SendGoal_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  // field types and members
  using _accepted_type =
    bool;
  _accepted_type accepted;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;

  // setters for named parameter idiom
  Type & set__accepted(
    const bool & _arg)
  {
    this->accepted = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    transformer_controller::action::TransformMode_SendGoal_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const transformer_controller::action::TransformMode_SendGoal_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_SendGoal_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_SendGoal_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_SendGoal_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_SendGoal_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_SendGoal_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_SendGoal_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_SendGoal_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_SendGoal_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__transformer_controller__action__TransformMode_SendGoal_Response
    std::shared_ptr<transformer_controller::action::TransformMode_SendGoal_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__transformer_controller__action__TransformMode_SendGoal_Response
    std::shared_ptr<transformer_controller::action::TransformMode_SendGoal_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TransformMode_SendGoal_Response_ & other) const
  {
    if (this->accepted != other.accepted) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const TransformMode_SendGoal_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TransformMode_SendGoal_Response_

// alias to use template instance with default allocator
using TransformMode_SendGoal_Response =
  transformer_controller::action::TransformMode_SendGoal_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace transformer_controller


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__transformer_controller__action__TransformMode_SendGoal_Event __attribute__((deprecated))
#else
# define DEPRECATED__transformer_controller__action__TransformMode_SendGoal_Event __declspec(deprecated)
#endif

namespace transformer_controller
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct TransformMode_SendGoal_Event_
{
  using Type = TransformMode_SendGoal_Event_<ContainerAllocator>;

  explicit TransformMode_SendGoal_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit TransformMode_SendGoal_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<transformer_controller::action::TransformMode_SendGoal_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<transformer_controller::action::TransformMode_SendGoal_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<transformer_controller::action::TransformMode_SendGoal_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<transformer_controller::action::TransformMode_SendGoal_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<transformer_controller::action::TransformMode_SendGoal_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<transformer_controller::action::TransformMode_SendGoal_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<transformer_controller::action::TransformMode_SendGoal_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<transformer_controller::action::TransformMode_SendGoal_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    transformer_controller::action::TransformMode_SendGoal_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const transformer_controller::action::TransformMode_SendGoal_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_SendGoal_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_SendGoal_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_SendGoal_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_SendGoal_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_SendGoal_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_SendGoal_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_SendGoal_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_SendGoal_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__transformer_controller__action__TransformMode_SendGoal_Event
    std::shared_ptr<transformer_controller::action::TransformMode_SendGoal_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__transformer_controller__action__TransformMode_SendGoal_Event
    std::shared_ptr<transformer_controller::action::TransformMode_SendGoal_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TransformMode_SendGoal_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const TransformMode_SendGoal_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TransformMode_SendGoal_Event_

// alias to use template instance with default allocator
using TransformMode_SendGoal_Event =
  transformer_controller::action::TransformMode_SendGoal_Event_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace transformer_controller

namespace transformer_controller
{

namespace action
{

struct TransformMode_SendGoal
{
  using Request = transformer_controller::action::TransformMode_SendGoal_Request;
  using Response = transformer_controller::action::TransformMode_SendGoal_Response;
  using Event = transformer_controller::action::TransformMode_SendGoal_Event;
};

}  // namespace action

}  // namespace transformer_controller


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__transformer_controller__action__TransformMode_GetResult_Request __attribute__((deprecated))
#else
# define DEPRECATED__transformer_controller__action__TransformMode_GetResult_Request __declspec(deprecated)
#endif

namespace transformer_controller
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct TransformMode_GetResult_Request_
{
  using Type = TransformMode_GetResult_Request_<ContainerAllocator>;

  explicit TransformMode_GetResult_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init)
  {
    (void)_init;
  }

  explicit TransformMode_GetResult_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    transformer_controller::action::TransformMode_GetResult_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const transformer_controller::action::TransformMode_GetResult_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_GetResult_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_GetResult_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_GetResult_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_GetResult_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_GetResult_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_GetResult_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_GetResult_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_GetResult_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__transformer_controller__action__TransformMode_GetResult_Request
    std::shared_ptr<transformer_controller::action::TransformMode_GetResult_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__transformer_controller__action__TransformMode_GetResult_Request
    std::shared_ptr<transformer_controller::action::TransformMode_GetResult_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TransformMode_GetResult_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const TransformMode_GetResult_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TransformMode_GetResult_Request_

// alias to use template instance with default allocator
using TransformMode_GetResult_Request =
  transformer_controller::action::TransformMode_GetResult_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace transformer_controller


// Include directives for member types
// Member 'result'
// already included above
// #include "transformer_controller/action/detail/transform_mode__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__transformer_controller__action__TransformMode_GetResult_Response __attribute__((deprecated))
#else
# define DEPRECATED__transformer_controller__action__TransformMode_GetResult_Response __declspec(deprecated)
#endif

namespace transformer_controller
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct TransformMode_GetResult_Response_
{
  using Type = TransformMode_GetResult_Response_<ContainerAllocator>;

  explicit TransformMode_GetResult_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  explicit TransformMode_GetResult_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  // field types and members
  using _status_type =
    int8_t;
  _status_type status;
  using _result_type =
    transformer_controller::action::TransformMode_Result_<ContainerAllocator>;
  _result_type result;

  // setters for named parameter idiom
  Type & set__status(
    const int8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__result(
    const transformer_controller::action::TransformMode_Result_<ContainerAllocator> & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    transformer_controller::action::TransformMode_GetResult_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const transformer_controller::action::TransformMode_GetResult_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_GetResult_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_GetResult_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_GetResult_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_GetResult_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_GetResult_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_GetResult_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_GetResult_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_GetResult_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__transformer_controller__action__TransformMode_GetResult_Response
    std::shared_ptr<transformer_controller::action::TransformMode_GetResult_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__transformer_controller__action__TransformMode_GetResult_Response
    std::shared_ptr<transformer_controller::action::TransformMode_GetResult_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TransformMode_GetResult_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const TransformMode_GetResult_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TransformMode_GetResult_Response_

// alias to use template instance with default allocator
using TransformMode_GetResult_Response =
  transformer_controller::action::TransformMode_GetResult_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace transformer_controller


// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__transformer_controller__action__TransformMode_GetResult_Event __attribute__((deprecated))
#else
# define DEPRECATED__transformer_controller__action__TransformMode_GetResult_Event __declspec(deprecated)
#endif

namespace transformer_controller
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct TransformMode_GetResult_Event_
{
  using Type = TransformMode_GetResult_Event_<ContainerAllocator>;

  explicit TransformMode_GetResult_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit TransformMode_GetResult_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<transformer_controller::action::TransformMode_GetResult_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<transformer_controller::action::TransformMode_GetResult_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<transformer_controller::action::TransformMode_GetResult_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<transformer_controller::action::TransformMode_GetResult_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<transformer_controller::action::TransformMode_GetResult_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<transformer_controller::action::TransformMode_GetResult_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<transformer_controller::action::TransformMode_GetResult_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<transformer_controller::action::TransformMode_GetResult_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    transformer_controller::action::TransformMode_GetResult_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const transformer_controller::action::TransformMode_GetResult_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_GetResult_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_GetResult_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_GetResult_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_GetResult_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_GetResult_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_GetResult_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_GetResult_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_GetResult_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__transformer_controller__action__TransformMode_GetResult_Event
    std::shared_ptr<transformer_controller::action::TransformMode_GetResult_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__transformer_controller__action__TransformMode_GetResult_Event
    std::shared_ptr<transformer_controller::action::TransformMode_GetResult_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TransformMode_GetResult_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const TransformMode_GetResult_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TransformMode_GetResult_Event_

// alias to use template instance with default allocator
using TransformMode_GetResult_Event =
  transformer_controller::action::TransformMode_GetResult_Event_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace transformer_controller

namespace transformer_controller
{

namespace action
{

struct TransformMode_GetResult
{
  using Request = transformer_controller::action::TransformMode_GetResult_Request;
  using Response = transformer_controller::action::TransformMode_GetResult_Response;
  using Event = transformer_controller::action::TransformMode_GetResult_Event;
};

}  // namespace action

}  // namespace transformer_controller


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'feedback'
// already included above
// #include "transformer_controller/action/detail/transform_mode__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__transformer_controller__action__TransformMode_FeedbackMessage __attribute__((deprecated))
#else
# define DEPRECATED__transformer_controller__action__TransformMode_FeedbackMessage __declspec(deprecated)
#endif

namespace transformer_controller
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct TransformMode_FeedbackMessage_
{
  using Type = TransformMode_FeedbackMessage_<ContainerAllocator>;

  explicit TransformMode_FeedbackMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    feedback(_init)
  {
    (void)_init;
  }

  explicit TransformMode_FeedbackMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    feedback(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _feedback_type =
    transformer_controller::action::TransformMode_Feedback_<ContainerAllocator>;
  _feedback_type feedback;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__feedback(
    const transformer_controller::action::TransformMode_Feedback_<ContainerAllocator> & _arg)
  {
    this->feedback = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    transformer_controller::action::TransformMode_FeedbackMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const transformer_controller::action::TransformMode_FeedbackMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_FeedbackMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<transformer_controller::action::TransformMode_FeedbackMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_FeedbackMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_FeedbackMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      transformer_controller::action::TransformMode_FeedbackMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<transformer_controller::action::TransformMode_FeedbackMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_FeedbackMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<transformer_controller::action::TransformMode_FeedbackMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__transformer_controller__action__TransformMode_FeedbackMessage
    std::shared_ptr<transformer_controller::action::TransformMode_FeedbackMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__transformer_controller__action__TransformMode_FeedbackMessage
    std::shared_ptr<transformer_controller::action::TransformMode_FeedbackMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TransformMode_FeedbackMessage_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->feedback != other.feedback) {
      return false;
    }
    return true;
  }
  bool operator!=(const TransformMode_FeedbackMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TransformMode_FeedbackMessage_

// alias to use template instance with default allocator
using TransformMode_FeedbackMessage =
  transformer_controller::action::TransformMode_FeedbackMessage_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace transformer_controller

#include "action_msgs/srv/cancel_goal.hpp"
#include "action_msgs/msg/goal_info.hpp"
#include "action_msgs/msg/goal_status_array.hpp"

namespace transformer_controller
{

namespace action
{

struct TransformMode
{
  /// The goal message defined in the action definition.
  using Goal = transformer_controller::action::TransformMode_Goal;
  /// The result message defined in the action definition.
  using Result = transformer_controller::action::TransformMode_Result;
  /// The feedback message defined in the action definition.
  using Feedback = transformer_controller::action::TransformMode_Feedback;

  struct Impl
  {
    /// The send_goal service using a wrapped version of the goal message as a request.
    using SendGoalService = transformer_controller::action::TransformMode_SendGoal;
    /// The get_result service using a wrapped version of the result message as a response.
    using GetResultService = transformer_controller::action::TransformMode_GetResult;
    /// The feedback message with generic fields which wraps the feedback message.
    using FeedbackMessage = transformer_controller::action::TransformMode_FeedbackMessage;

    /// The generic service to cancel a goal.
    using CancelGoalService = action_msgs::srv::CancelGoal;
    /// The generic message for the status of a goal.
    using GoalStatusMessage = action_msgs::msg::GoalStatusArray;
  };
};

typedef struct TransformMode TransformMode;

}  // namespace action

}  // namespace transformer_controller

#endif  // TRANSFORMER_CONTROLLER__ACTION__DETAIL__TRANSFORM_MODE__STRUCT_HPP_
