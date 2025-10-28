/**
 * @brief Declares the RC mode switch node responsible for translating radio control inputs
 *        into transformer mode transition requests.
 */
#ifndef TRANSFORMER_RC_MODE_SWITCH__RC_MODE_SWITCH_NODE_HPP_
#define TRANSFORMER_RC_MODE_SWITCH__RC_MODE_SWITCH_NODE_HPP_

#include <chrono>
#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <std_msgs/msg/u_int16_multi_array.hpp>
#include <transformer_controller/action/transform_mode.hpp>

namespace transformer_rc_mode_switch {

/**
 * @brief Provides the ROS 2 node that converts RC channel commands into transformer mode goals.
 */
class RcModeSwitchNode : public rclcpp::Node {
 public:
  using TransformMode = transformer_controller::action::TransformMode;
  using TransformGoalHandle = rclcpp_action::ClientGoalHandle<TransformMode>;

  /**
   * @brief Constructs the node, loading configuration and wiring ROS interfaces.
   */
  RcModeSwitchNode();

  /**
   * @brief Tears down the node instance.
   */
  ~RcModeSwitchNode() override = default;

 private:
  /**
   * @brief Strongly typed modes that can be commanded to the transformer controller.
   */
  enum class Mode { kUnknown = 0, kDrive, kFlight };

  /**
   * @brief Loads user-configurable parameters and sanitizes their values.
   *
   * @return void
   */
  void InitializeParameters();

  /**
   * @brief Creates the action client used for transformer mode transitions.
   *
   * @return void
   */
  void InitializeActionClient();

  /**
   * @brief Subscribes to the RC topic to receive channel updates.
   *
   * @return void
   */
  void InitializeSubscription();

  /**
   * @brief Processes incoming RC channel data to decide whether to issue a mode change.
   *
   * @param msg Shared pointer to the UInt16 array message containing channel values.
   * @return void
   */
  void OnRcMessage(const std_msgs::msg::UInt16MultiArray::SharedPtr& msg);

  /**
   * @brief Infers which mode the RC channel currently requests.
   *
   * @param channel_value The raw RC channel pulse width.
   * @return Mode The interpreted transformer mode.
   */
  Mode DetermineRequestedMode(int channel_value) const;

  /**
   * @brief Evaluates whether enough time has passed since the last command to respect debouncing.
   *
   * @param now The current steady clock timestamp.
   * @return bool True if a new command may be issued.
   */
  bool IsDebounced(std::chrono::steady_clock::time_point now) const;

  /**
   * @brief Sends a goal to the transformer action server and updates internal bookkeeping.
   *
   * @param mode The mode to command.
   * @param channel_value The RC channel value that triggered the command.
   * @param now The current steady clock timestamp used for debounce tracking.
   * @return void
   */
  void DispatchGoal(Mode mode, int channel_value, std::chrono::steady_clock::time_point now);

  /**
   * @brief Converts the strongly typed mode into its string representation for the action goal.
   *
   * @param mode The mode to convert.
   * @return std::string String literal expected by the action server.
   */
  static std::string ModeToString(Mode mode);

  int channel_index_{};
  int drive_high_center_{};
  int flight_low_center_{};
  int tolerance_{};
  std::chrono::milliseconds debounce_period_{};
  int min_publish_channels_{};
  std::string rc_topic_;

  Mode last_sent_mode_{Mode::kUnknown};
  std::chrono::steady_clock::time_point last_goal_time_{std::chrono::steady_clock::time_point::min()};

  rclcpp_action::Client<TransformMode>::SharedPtr transform_client_;
  rclcpp::Subscription<std_msgs::msg::UInt16MultiArray>::SharedPtr rc_subscription_;
};

}  // namespace transformer_rc_mode_switch

#endif  // TRANSFORMER_RC_MODE_SWITCH__RC_MODE_SWITCH_NODE_HPP_
