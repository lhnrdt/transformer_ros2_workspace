/**
 * @file actuator_node.hpp
 * @brief Declares the ActuatorNode responsible for driving hardware actuators via PWM and GPIO lines.
 */

#pragma once

#include <atomic>
#include <chrono>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <gpiod.h>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

#include "transformer_hw_actuators/action/move_actuator.hpp"

namespace transformer_hw_actuators {

/**
 * @brief Describes the logical direction that an actuator should drive.
 */
enum class ActuatorDirection : uint8_t {
  kForward = 0,
  kReverse = 1,
};

/**
 * @brief ROS 2 node that configures and drives PWM-based actuators with optional timing feedback.
 */
class ActuatorNode : public rclcpp::Node {
 public:
  using MoveActuator = transformer_hw_actuators::action::MoveActuator;
  using GoalHandleMove = rclcpp_action::ServerGoalHandle<MoveActuator>;

  /**
   * @brief Constructs the node and performs all hardware configuration.
   * @param options ROS 2 node options provided by the application or launch system.
   */
  explicit ActuatorNode(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());

  /**
   * @brief Releases all GPIO line resources and joins remaining worker threads.
   */
  ~ActuatorNode() override;

 private:
  // Parameter-derived configuration values
  int pwmchip_index_ = 0;                    // Index of the PWM chip exposed in sysfs.
  std::string gpiochip_name_;                // Name of the libgpiod chip that exposes direction lines.
  std::vector<int> pwm_channels_;            // PWM channel indices for each actuator.
  std::vector<int> direction_gpios_;         // GPIO line numbers controlling actuator direction.
  std::vector<bool> direction_active_high_;  // Whether logical forward equals a HIGH level per actuator.
  int64_t period_ns_ = 0;                    // PWM period length in nanoseconds.
  int initial_percent_ = 0;                  // Startup duty cycle percentage (-100..100) used for all actuators.
  bool brake_on_zero_ = false;               // Indicates whether the driver should brake when duty cycle is zero.
  int feedback_period_ms_ = 0;               // Feedback publishing period in milliseconds.
  int standby_gpio_ = -1;                    // Optional STBY control line (set negative to disable).
  int mode_gpio_ = -1;                       // Optional MODE control line (set negative to disable).

  std::string chip_path_;  // Absolute path to the PWM chip directory in sysfs.

  // GPIO handles (libgpiod)
  gpiod_chip* gpio_chip_ = nullptr;
  std::vector<gpiod_line*> direction_lines_;
  gpiod_line* standby_line_ = nullptr;
  gpiod_line* mode_line_ = nullptr;

  // Action server wiring
  rclcpp_action::Server<MoveActuator>::SharedPtr action_server_;

  // Concurrency helpers
  std::atomic<bool> shutting_down_{false};
  std::mutex active_goal_mutex_;
  std::shared_ptr<GoalHandleMove> active_goal_;
  std::mutex threads_mutex_;
  std::vector<std::thread> worker_threads_;

  /**
   * @brief Loads parameters and validates their relationships.
   */
  void LoadParameters();

  /**
   * @brief Opens the configured GPIO chip.
   */
  void ConfigureGpioChip();

  /**
   * @brief Requests direction GPIO lines for exclusive output control.
   */
  void ConfigureDirectionLines();

  /**
   * @brief Configures optional standby and mode GPIO control lines.
   */
  void ConfigureControlLines();

  /**
   * @brief Exports and configures each PWM channel prior to action usage.
   */
  void ConfigurePwmChannels();

  /**
   * @brief Applies the initial duty cycle and direction configuration.
   */
  void ApplyInitialDirections();

  /**
   * @brief Creates the action server that accepts actuator movement goals.
   */
  void ConfigureActionServer();

  /**
   * @brief Initiates an orderly shutdown by cancelling goals and stopping PWM output.
   */
  void BeginShutdown();

  /**
   * @brief Cancels an active goal if one exists while the node is shutting down.
   */
  void CancelActiveGoalForShutdown();

  /**
   * @brief Clears the tracked active goal if it matches the provided handle.
   * @param goal_handle Goal handle that might still be registered as active.
   */
  void ClearActiveGoalIfMatches(const std::shared_ptr<GoalHandleMove>& goal_handle);

  /**
   * @brief Retrieves a channel-specific relative path.
   * @param channel PWM channel index.
   * @param leaf Final leaf path, e.g. "period".
   * @return Relative sysfs path portion for the channel.
   */
  [[nodiscard]] std::string ChannelPath(int channel, const std::string& leaf) const;

  /**
   * @brief Writes a string value to the given sysfs file.
   * @param path Absolute path to the destination file.
   * @param value Content to write.
   * @param err Error message populated on failure.
   * @return True when writing succeeds.
   */
  static bool WriteFile(const std::string& path, const std::string& value, std::string& err);

  /**
   * @brief Checks whether a sysfs path exists.
   * @param path Absolute path to confirm.
   * @return True when the path exists on the filesystem.
   */
  static bool PathExists(const std::string& path);

  /**
   * @brief Requests a GPIO line for output, retrying when the line is temporarily busy.
   * @param gpio_number Numerical identifier of the GPIO line.
   * @param initial_level Logic level set immediately after acquisition (0 or 1).
   * @return Pointer to the acquired line, guaranteed non-null.
   */
  gpiod_line* RequestOutputLine(int gpio_number, int initial_level);

  /**
   * @brief Exports a PWM channel when required by sysfs.
   * @param channel PWM channel index.
   * @param err Error message populated on failure.
   * @return True when the channel is ready.
   */
  bool ExportChannel(int channel, std::string& err);

  /**
   * @brief Writes the configured PWM period for a channel.
   * @param channel PWM channel index.
   * @param err Error message populated on failure.
   * @return True when the period file is updated.
   */
  bool EnsurePeriod(int channel, std::string& err);

  /**
   * @brief Enables or disables a PWM channel.
   * @param channel PWM channel index.
   * @param enable True to enable, false to disable.
   * @param err Error message populated on failure.
   * @return True when the operation succeeds.
   */
  bool EnableChannel(int channel, bool enable, std::string& err);

  /**
   * @brief Applies a duty cycle percentage to the given channel.
   * @param channel PWM channel index.
   * @param percent Duty cycle percentage in the range 0..100.
   * @param err Error message populated on failure.
   * @return True when the duty cycle is written.
   */
  bool SetDutyPercent(int channel, int percent, std::string& err);

  /**
   * @brief Applies the desired direction to an actuator control GPIO.
   * @param actuator_index Index of the actuator in the configuration vectors.
   * @param direction Desired logical direction.
   * @param err Error message populated on failure.
   * @return True when the GPIO is updated.
   */
  bool SetDirection(size_t actuator_index, ActuatorDirection direction, std::string& err);

  /**
   * @brief Validates incoming action goals and decides whether to accept execution.
   * @param uuid Unique identifier of the goal request.
   * @param goal Requested actuator movement parameters.
   * @return Response that either rejects the goal or proceeds to execution.
   */
  rclcpp_action::GoalResponse HandleGoal(const rclcpp_action::GoalUUID& uuid,
                                         std::shared_ptr<const MoveActuator::Goal> goal);

  /**
   * @brief Accepts cancellation requests for in-flight goals.
   * @param goal_handle Handle corresponding to the goal to cancel.
   * @return Always accepts, enabling deterministic shutdown behaviour.
   */
  rclcpp_action::CancelResponse HandleCancel(const std::shared_ptr<GoalHandleMove> goal_handle);

  /**
   * @brief Spawns an execution thread to service the accepted goal.
   * @param goal_handle Handle for the newly accepted goal.
   */
  void HandleAccepted(const std::shared_ptr<GoalHandleMove> goal_handle);

  /**
   * @brief Executes the goal request, publishes feedback, and finalises the result.
   * @param goal_handle Handle that exposes goal data and result interfaces.
   */
  void Execute(const std::shared_ptr<GoalHandleMove> goal_handle);
};

/**
 * @brief Runs the actuator node inside a multi-threaded executor until shutdown.
 * @param argc Command line argument count.
 * @param argv Command line argument vector.
 * @return Zero on successful shutdown; non-zero if initialisation fails.
 */
int RunActuatorNode(int argc, char** argv);

}  // namespace transformer_hw_actuators