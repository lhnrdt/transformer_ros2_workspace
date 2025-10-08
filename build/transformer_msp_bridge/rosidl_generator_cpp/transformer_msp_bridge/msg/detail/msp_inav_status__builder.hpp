// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from transformer_msp_bridge:msg/MspInavStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "transformer_msp_bridge/msg/msp_inav_status.hpp"


#ifndef TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__BUILDER_HPP_
#define TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "transformer_msp_bridge/msg/detail/msp_inav_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace transformer_msp_bridge
{

namespace msg
{

namespace builder
{

class Init_MspInavStatus_active_modes
{
public:
  explicit Init_MspInavStatus_active_modes(::transformer_msp_bridge::msg::MspInavStatus & msg)
  : msg_(msg)
  {}
  ::transformer_msp_bridge::msg::MspInavStatus active_modes(::transformer_msp_bridge::msg::MspInavStatus::_active_modes_type arg)
  {
    msg_.active_modes = std::move(arg);
    return std::move(msg_);
  }

private:
  ::transformer_msp_bridge::msg::MspInavStatus msg_;
};

class Init_MspInavStatus_arming_flags
{
public:
  explicit Init_MspInavStatus_arming_flags(::transformer_msp_bridge::msg::MspInavStatus & msg)
  : msg_(msg)
  {}
  Init_MspInavStatus_active_modes arming_flags(::transformer_msp_bridge::msg::MspInavStatus::_arming_flags_type arg)
  {
    msg_.arming_flags = std::move(arg);
    return Init_MspInavStatus_active_modes(msg_);
  }

private:
  ::transformer_msp_bridge::msg::MspInavStatus msg_;
};

class Init_MspInavStatus_mixer_profile
{
public:
  explicit Init_MspInavStatus_mixer_profile(::transformer_msp_bridge::msg::MspInavStatus & msg)
  : msg_(msg)
  {}
  Init_MspInavStatus_arming_flags mixer_profile(::transformer_msp_bridge::msg::MspInavStatus::_mixer_profile_type arg)
  {
    msg_.mixer_profile = std::move(arg);
    return Init_MspInavStatus_arming_flags(msg_);
  }

private:
  ::transformer_msp_bridge::msg::MspInavStatus msg_;
};

class Init_MspInavStatus_battery_profile
{
public:
  explicit Init_MspInavStatus_battery_profile(::transformer_msp_bridge::msg::MspInavStatus & msg)
  : msg_(msg)
  {}
  Init_MspInavStatus_mixer_profile battery_profile(::transformer_msp_bridge::msg::MspInavStatus::_battery_profile_type arg)
  {
    msg_.battery_profile = std::move(arg);
    return Init_MspInavStatus_mixer_profile(msg_);
  }

private:
  ::transformer_msp_bridge::msg::MspInavStatus msg_;
};

class Init_MspInavStatus_config_profile
{
public:
  explicit Init_MspInavStatus_config_profile(::transformer_msp_bridge::msg::MspInavStatus & msg)
  : msg_(msg)
  {}
  Init_MspInavStatus_battery_profile config_profile(::transformer_msp_bridge::msg::MspInavStatus::_config_profile_type arg)
  {
    msg_.config_profile = std::move(arg);
    return Init_MspInavStatus_battery_profile(msg_);
  }

private:
  ::transformer_msp_bridge::msg::MspInavStatus msg_;
};

class Init_MspInavStatus_cpu_load_percent
{
public:
  explicit Init_MspInavStatus_cpu_load_percent(::transformer_msp_bridge::msg::MspInavStatus & msg)
  : msg_(msg)
  {}
  Init_MspInavStatus_config_profile cpu_load_percent(::transformer_msp_bridge::msg::MspInavStatus::_cpu_load_percent_type arg)
  {
    msg_.cpu_load_percent = std::move(arg);
    return Init_MspInavStatus_config_profile(msg_);
  }

private:
  ::transformer_msp_bridge::msg::MspInavStatus msg_;
};

class Init_MspInavStatus_sensor_status
{
public:
  explicit Init_MspInavStatus_sensor_status(::transformer_msp_bridge::msg::MspInavStatus & msg)
  : msg_(msg)
  {}
  Init_MspInavStatus_cpu_load_percent sensor_status(::transformer_msp_bridge::msg::MspInavStatus::_sensor_status_type arg)
  {
    msg_.sensor_status = std::move(arg);
    return Init_MspInavStatus_cpu_load_percent(msg_);
  }

private:
  ::transformer_msp_bridge::msg::MspInavStatus msg_;
};

class Init_MspInavStatus_i2c_errors
{
public:
  explicit Init_MspInavStatus_i2c_errors(::transformer_msp_bridge::msg::MspInavStatus & msg)
  : msg_(msg)
  {}
  Init_MspInavStatus_sensor_status i2c_errors(::transformer_msp_bridge::msg::MspInavStatus::_i2c_errors_type arg)
  {
    msg_.i2c_errors = std::move(arg);
    return Init_MspInavStatus_sensor_status(msg_);
  }

private:
  ::transformer_msp_bridge::msg::MspInavStatus msg_;
};

class Init_MspInavStatus_cycle_time_us
{
public:
  Init_MspInavStatus_cycle_time_us()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MspInavStatus_i2c_errors cycle_time_us(::transformer_msp_bridge::msg::MspInavStatus::_cycle_time_us_type arg)
  {
    msg_.cycle_time_us = std::move(arg);
    return Init_MspInavStatus_i2c_errors(msg_);
  }

private:
  ::transformer_msp_bridge::msg::MspInavStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::transformer_msp_bridge::msg::MspInavStatus>()
{
  return transformer_msp_bridge::msg::builder::Init_MspInavStatus_cycle_time_us();
}

}  // namespace transformer_msp_bridge

#endif  // TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__BUILDER_HPP_
