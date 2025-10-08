// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from transformer_msp_bridge:msg/MspInavStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "transformer_msp_bridge/msg/msp_inav_status.hpp"


#ifndef TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__STRUCT_HPP_
#define TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__transformer_msp_bridge__msg__MspInavStatus __attribute__((deprecated))
#else
# define DEPRECATED__transformer_msp_bridge__msg__MspInavStatus __declspec(deprecated)
#endif

namespace transformer_msp_bridge
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MspInavStatus_
{
  using Type = MspInavStatus_<ContainerAllocator>;

  explicit MspInavStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->cycle_time_us = 0;
      this->i2c_errors = 0;
      this->sensor_status = 0;
      this->cpu_load_percent = 0;
      this->config_profile = 0;
      this->battery_profile = 0;
      this->mixer_profile = 0;
      this->arming_flags = 0ul;
    }
  }

  explicit MspInavStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->cycle_time_us = 0;
      this->i2c_errors = 0;
      this->sensor_status = 0;
      this->cpu_load_percent = 0;
      this->config_profile = 0;
      this->battery_profile = 0;
      this->mixer_profile = 0;
      this->arming_flags = 0ul;
    }
  }

  // field types and members
  using _cycle_time_us_type =
    uint16_t;
  _cycle_time_us_type cycle_time_us;
  using _i2c_errors_type =
    uint16_t;
  _i2c_errors_type i2c_errors;
  using _sensor_status_type =
    uint16_t;
  _sensor_status_type sensor_status;
  using _cpu_load_percent_type =
    uint16_t;
  _cpu_load_percent_type cpu_load_percent;
  using _config_profile_type =
    uint8_t;
  _config_profile_type config_profile;
  using _battery_profile_type =
    uint8_t;
  _battery_profile_type battery_profile;
  using _mixer_profile_type =
    uint8_t;
  _mixer_profile_type mixer_profile;
  using _arming_flags_type =
    uint32_t;
  _arming_flags_type arming_flags;
  using _active_modes_type =
    std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>>;
  _active_modes_type active_modes;

  // setters for named parameter idiom
  Type & set__cycle_time_us(
    const uint16_t & _arg)
  {
    this->cycle_time_us = _arg;
    return *this;
  }
  Type & set__i2c_errors(
    const uint16_t & _arg)
  {
    this->i2c_errors = _arg;
    return *this;
  }
  Type & set__sensor_status(
    const uint16_t & _arg)
  {
    this->sensor_status = _arg;
    return *this;
  }
  Type & set__cpu_load_percent(
    const uint16_t & _arg)
  {
    this->cpu_load_percent = _arg;
    return *this;
  }
  Type & set__config_profile(
    const uint8_t & _arg)
  {
    this->config_profile = _arg;
    return *this;
  }
  Type & set__battery_profile(
    const uint8_t & _arg)
  {
    this->battery_profile = _arg;
    return *this;
  }
  Type & set__mixer_profile(
    const uint8_t & _arg)
  {
    this->mixer_profile = _arg;
    return *this;
  }
  Type & set__arming_flags(
    const uint32_t & _arg)
  {
    this->arming_flags = _arg;
    return *this;
  }
  Type & set__active_modes(
    const std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> & _arg)
  {
    this->active_modes = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    transformer_msp_bridge::msg::MspInavStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const transformer_msp_bridge::msg::MspInavStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<transformer_msp_bridge::msg::MspInavStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<transformer_msp_bridge::msg::MspInavStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      transformer_msp_bridge::msg::MspInavStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<transformer_msp_bridge::msg::MspInavStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      transformer_msp_bridge::msg::MspInavStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<transformer_msp_bridge::msg::MspInavStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<transformer_msp_bridge::msg::MspInavStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<transformer_msp_bridge::msg::MspInavStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__transformer_msp_bridge__msg__MspInavStatus
    std::shared_ptr<transformer_msp_bridge::msg::MspInavStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__transformer_msp_bridge__msg__MspInavStatus
    std::shared_ptr<transformer_msp_bridge::msg::MspInavStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MspInavStatus_ & other) const
  {
    if (this->cycle_time_us != other.cycle_time_us) {
      return false;
    }
    if (this->i2c_errors != other.i2c_errors) {
      return false;
    }
    if (this->sensor_status != other.sensor_status) {
      return false;
    }
    if (this->cpu_load_percent != other.cpu_load_percent) {
      return false;
    }
    if (this->config_profile != other.config_profile) {
      return false;
    }
    if (this->battery_profile != other.battery_profile) {
      return false;
    }
    if (this->mixer_profile != other.mixer_profile) {
      return false;
    }
    if (this->arming_flags != other.arming_flags) {
      return false;
    }
    if (this->active_modes != other.active_modes) {
      return false;
    }
    return true;
  }
  bool operator!=(const MspInavStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MspInavStatus_

// alias to use template instance with default allocator
using MspInavStatus =
  transformer_msp_bridge::msg::MspInavStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace transformer_msp_bridge

#endif  // TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__STRUCT_HPP_
