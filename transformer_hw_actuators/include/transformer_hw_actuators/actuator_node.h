#pragma once

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include "transformer_hw_actuators/action/move_actuator.hpp"

#include <gpiod.h>  // libgpiod (C API)
#include <string>
#include <vector>

namespace transformer_hw_actuators {

class ActuatorNode : public rclcpp::Node {
public:
  using MoveActuator = transformer_hw_actuators::action::MoveActuator;
  using GoalHandleMove = rclcpp_action::ServerGoalHandle<MoveActuator>;

  explicit ActuatorNode(const rclcpp::NodeOptions &options = rclcpp::NodeOptions());
  ~ActuatorNode() override;

private:
  // Parameters
  int pwmchip_index_;                 // e.g., 0
  std::string gpiochip_name_;  // e.g., "gpiochip4" on Pi 5 (RP1)
  std::vector<int> pwm_channels_;     // e.g., [1,0] → PWM1 for actuator0, PWM0 for actuator1
  std::vector<int> dir_gpios_;        // e.g., [19,5]
  std::vector<bool> dir_active_high_; // if false, logic is inverted per actuator
  int64_t period_ns_;                 // e.g., 50'000 for 20 kHz (recommended for DC motors)
  int initial_percent_;               // -100..100 startup value (default 0)
  bool brake_on_zero_;                // if true, request braking behavior at 0 (see notes)

  // Paths derived from params
  std::string chip_path_;             // /sys/class/pwm/pwmchipX

  // GPIO (libgpiod)
  gpiod_chip* gpio_chip_ = nullptr;
  std::vector<gpiod_line*> dir_lines_;

  // Action server
  rclcpp_action::Server<MoveActuator>::SharedPtr action_server_;

  // Core helpers
  static bool writeFile(const std::string &path, const std::string &value, std::string &err);
  static bool pathExists(const std::string &path);
  std::string chPath(int channel, const std::string &leaf) const;

  // PWM init/control
  bool exportChannel(int channel, std::string &err);
  bool ensurePeriod(int channel, std::string &err);
  bool enableChannel(int channel, bool enable, std::string &err);
  bool setDutyPercent(int channel, int percent, std::string &err); // 0..100

  // Direction control
  bool setDirection(size_t actuator_idx, bool forward, std::string &err);

  // Action callbacks
  rclcpp_action::GoalResponse handleGoal(const rclcpp_action::GoalUUID &uuid,
                                         std::shared_ptr<const MoveActuator::Goal> goal);
  rclcpp_action::CancelResponse handleCancel(const std::shared_ptr<GoalHandleMove> goal_handle);
  void handleAccepted(const std::shared_ptr<GoalHandleMove> goal_handle);
  void execute(const std::shared_ptr<GoalHandleMove> goal_handle);
};

} // namespace transformer_hw_actuators