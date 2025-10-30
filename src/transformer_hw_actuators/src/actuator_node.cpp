/**
 * @file actuator_node.cpp
 * @brief Implements the ActuatorNode hardware driver and its action callbacks.
 */

#include "transformer_hw_actuators/actuator_node.hpp"

#include <algorithm>
#include <cerrno>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <system_error>
#include <thread>
#include <utility>
#include <vector>

#include <rclcpp/rclcpp.hpp>

namespace transformer_hw_actuators {

namespace {

/**
 * @brief Internal constants and helper structures limited to this translation unit.
 */
constexpr char kNodeName[] = "actuator_node";
constexpr char kActionName[] = "move_actuator";
constexpr char kGpioConsumerName[] = "transformer_hw_actuators";
constexpr int kMaxDutyPercent = 100;
constexpr int kMinDutyPercent = 0;
const std::chrono::milliseconds kGpioRetryDelay{150};
const std::chrono::milliseconds kPwmExportDelay{50};

/**
 * @brief Captures all command parameters used while executing a goal.
 */
struct CommandState {
  int actuator_index;
  int pwm_channel;
  int clamped_speed;
  ActuatorDirection direction;
  int duration_ms;
};

/**
 * @brief Converts an actuator speed percentage into a logical direction.
 * @param percent Signed duty cycle percentage requested for the actuator.
 * @return Forward when the request is non-negative, otherwise reverse.
 */
ActuatorDirection DirectionFromPercent(int percent) {
  return percent >= 0 ? ActuatorDirection::kForward : ActuatorDirection::kReverse;
}

/**
 * @brief Ensures a duration vector matches actuator count.
 * @param goal_duration Raw duration array provided with the goal.
 * @param actuator_count Number of actuators referenced by the goal.
 * @return Expanded duration vector with one entry per actuator.
 */
std::vector<int> NormalizeDurations(const std::vector<int32_t>& goal_duration, size_t actuator_count) {
  std::vector<int> durations(actuator_count, 0);
  if (goal_duration.empty()) {
    // Without duration data every command becomes "set and hold" (until the next goal).
    return durations;
  }
  if (goal_duration.size() == 1U) {
    // A single entry is broadcast to all actuators to avoid duplicate configuration.
    std::fill(durations.begin(), durations.end(), static_cast<int>(goal_duration.front()));
    return durations;
  }
  for (size_t i = 0; i < actuator_count; ++i) {
    // One-to-one mapping; truncation is not permitted thanks to prior validation.
    durations[i] = static_cast<int>(goal_duration[i]);
  }
  return durations;
}

}  // namespace

ActuatorNode::ActuatorNode(const rclcpp::NodeOptions& options) : Node(kNodeName, options) {
  // Register the shutdown hook before any heavy initialisation to guarantee cleanup even on early exits.
  rclcpp::on_shutdown([this]() { BeginShutdown(); });

  // Configuration happens in well-scoped phases, each throwing if a hard failure is detected.
  LoadParameters();
  ConfigureGpioChip();
  ConfigureDirectionLines();
  ConfigureControlLines();
  ConfigurePwmChannels();
  ApplyInitialDirections();
  ConfigureActionServer();

  RCLCPP_INFO(get_logger(), "\033[32m[READY] Actuator node ready: pwmchip=%d period=%ldns\033[0m", pwmchip_index_,
              static_cast<long>(period_ns_));
}

ActuatorNode::~ActuatorNode() {
  BeginShutdown();

  for (auto* line : direction_lines_) {
    if (line != nullptr) {
      gpiod_line_release(line);
    }
  }

  if (standby_line_ != nullptr) {
    gpiod_line_release(standby_line_);
  }

  if (mode_line_ != nullptr) {
    gpiod_line_release(mode_line_);
  }

  if (gpio_chip_ != nullptr) {
    gpiod_chip_close(gpio_chip_);
    gpio_chip_ = nullptr;
  }
}

void ActuatorNode::LoadParameters() {
  pwmchip_index_ = declare_parameter<int>("pwmchip_index", 0);
  gpiochip_name_ = declare_parameter<std::string>("gpiochip_name", "gpiochip4");
  standby_gpio_ = declare_parameter<int>("stby_gpio", 26);
  mode_gpio_ = declare_parameter<int>("mode_gpio", 0);

  // ROS 2 still stores integer arrays as int64; narrow to int for sysfs access immediately.
  const auto pwm_channels_param = declare_parameter<std::vector<int64_t>>("pwm_channels", {1, 0});
  pwm_channels_.assign(pwm_channels_param.begin(), pwm_channels_param.end());

  const auto direction_gpios_param = declare_parameter<std::vector<int64_t>>("dir_gpios", {19, 5});
  direction_gpios_.assign(direction_gpios_param.begin(), direction_gpios_param.end());

  direction_active_high_ = declare_parameter<std::vector<bool>>("dir_active_high", {true, true});
  period_ns_ = declare_parameter<int64_t>("period_ns", 50'000);
  initial_percent_ = declare_parameter<int>("initial_percent", 0);
  brake_on_zero_ = declare_parameter<bool>("brake_on_zero", false);
  feedback_period_ms_ = declare_parameter<int>("feedback_period_ms", 50);

  // Parameter relationship checks provide clear fault messages rather than failing at runtime.
  if (pwm_channels_.empty()) {
    RCLCPP_FATAL(get_logger(), "Parameter pwm_channels must contain at least one channel");
    throw std::runtime_error("pwm_channels empty");
  }
  if (pwm_channels_.size() != direction_gpios_.size()) {
    RCLCPP_FATAL(get_logger(), "pwm_channels and dir_gpios must have identical lengths");
    throw std::runtime_error("parameter size mismatch");
  }
  if (direction_active_high_.size() != direction_gpios_.size()) {
    RCLCPP_FATAL(get_logger(), "dir_active_high length must match dir_gpios");
    throw std::runtime_error("active_high size mismatch");
  }

  chip_path_ = "/sys/class/pwm/pwmchip" + std::to_string(pwmchip_index_);
  direction_lines_.assign(direction_gpios_.size(), nullptr);
}

void ActuatorNode::ConfigureGpioChip() {
  // The libgpiod C API returns nullptr on failure; surface errno to the log for operator visibility.
  gpio_chip_ = gpiod_chip_open_by_name(gpiochip_name_.c_str());
  if (gpio_chip_ == nullptr) {
    RCLCPP_FATAL(get_logger(), "Failed to open GPIO chip '%s': %s", gpiochip_name_.c_str(), std::strerror(errno));
    throw std::runtime_error("gpiod_chip_open_by_name failed");
  }
}

void ActuatorNode::ConfigureDirectionLines() {
  // Each direction line is requested individually to provide granular error reporting.
  for (size_t i = 0; i < direction_gpios_.size(); ++i) {
    direction_lines_[i] = RequestOutputLine(direction_gpios_[i], kMinDutyPercent);
  }
}

void ActuatorNode::ConfigureControlLines() {
  // Not all drivers expose STBY/MODE pins; we only touch them when configured.
  if (standby_gpio_ >= 0) {
    standby_line_ = RequestOutputLine(standby_gpio_, 1);
  }
  if (mode_gpio_ >= 0) {
    mode_line_ = RequestOutputLine(mode_gpio_, 1);
  }
}

void ActuatorNode::ConfigurePwmChannels() {
  // Prepare every PWM channel synchronously so the action server never sees a partially initialised setup.
  for (int channel : pwm_channels_) {
    std::string err;
    if (!ExportChannel(channel, err)) {
      RCLCPP_FATAL(get_logger(), "Failed to export PWM channel %d: %s", channel, err.c_str());
      throw std::runtime_error("exportChannel failed");
    }
    if (!EnsurePeriod(channel, err)) {
      RCLCPP_FATAL(get_logger(), "Failed to set period for PWM channel %d: %s", channel, err.c_str());
      throw std::runtime_error("ensurePeriod failed");
    }
    if (!SetDutyPercent(channel, std::abs(initial_percent_), err)) {
      RCLCPP_FATAL(get_logger(), "Failed to set initial duty for PWM channel %d: %s", channel, err.c_str());
      throw std::runtime_error("setDutyPercent failed");
    }
    if (!EnableChannel(channel, true, err)) {
      RCLCPP_FATAL(get_logger(), "Failed to enable PWM channel %d: %s", channel, err.c_str());
      throw std::runtime_error("enableChannel failed");
    }
  }
}

void ActuatorNode::ApplyInitialDirections() {
  const ActuatorDirection initial_direction = DirectionFromPercent(initial_percent_);
  for (size_t index = 0; index < direction_lines_.size(); ++index) {
    std::string err;
    if (!SetDirection(index, initial_direction, err)) {
      RCLCPP_FATAL(get_logger(), "Failed to set initial direction for actuator %zu: %s", index, err.c_str());
      throw std::runtime_error("setDirection failed");
    }
  }
}

void ActuatorNode::ConfigureActionServer() {
  // Using the explicit node interface overload avoids relying on shared_from_this() inside the constructor.
  action_server_ = rclcpp_action::create_server<MoveActuator>(
      get_node_base_interface(), get_node_clock_interface(), get_node_logging_interface(),
      get_node_waitables_interface(), kActionName,
      std::bind(&ActuatorNode::HandleGoal, this, std::placeholders::_1, std::placeholders::_2),
      std::bind(&ActuatorNode::HandleCancel, this, std::placeholders::_1),
      std::bind(&ActuatorNode::HandleAccepted, this, std::placeholders::_1));

  RCLCPP_INFO(get_logger(), "\033[32m[READY] Actuator action server advertised name=%s\033[0m", kActionName);
}

void ActuatorNode::BeginShutdown() {
  if (shutting_down_.exchange(true)) {
    return;
  }

  RCLCPP_INFO(get_logger(), "Shutdown: cancelling active goal and stopping PWM outputs");
  CancelActiveGoalForShutdown();

  std::string err;
  for (int channel : pwm_channels_) {
    if (!SetDutyPercent(channel, kMinDutyPercent, err)) {
      RCLCPP_WARN(get_logger(), "Failed to set duty cycle to zero for channel %d during shutdown: %s", channel,
                  err.c_str());
    }
  }

  std::lock_guard<std::mutex> threads_lock(threads_mutex_);
  for (auto& worker : worker_threads_) {
    if (worker.joinable()) {
      // Spinning threads must not outlive the node; ensure clean termination for determinism.
      worker.join();
    }
  }
  worker_threads_.clear();

  RCLCPP_INFO(get_logger(), "Shutdown: PWM outputs disabled and worker threads stopped");
}

void ActuatorNode::CancelActiveGoalForShutdown() {
  std::lock_guard<std::mutex> lock(active_goal_mutex_);
  if (active_goal_ != nullptr && active_goal_->is_active()) {
    auto result = std::make_shared<MoveActuator::Result>();
    result->success = false;
    result->message = "Node shutting down";
    active_goal_->abort(result);
  }
  active_goal_.reset();
}

void ActuatorNode::ClearActiveGoalIfMatches(const std::shared_ptr<GoalHandleMove>& goal_handle) {
  std::lock_guard<std::mutex> lock(active_goal_mutex_);
  if (active_goal_ == goal_handle) {
    active_goal_.reset();
  }
}

std::string ActuatorNode::ChannelPath(int channel, const std::string& leaf) const {
  std::ostringstream stream;
  stream << "/pwm" << channel << "/" << leaf;
  return stream.str();
}

bool ActuatorNode::WriteFile(const std::string& path, const std::string& value, std::string& err) {
  std::ofstream file(path);
  if (!file.is_open()) {
    err = std::string("open failed: ") + std::strerror(errno);
    return false;
  }
  file << value;
  if (!file.good()) {
    err = std::string("write failed: ") + std::strerror(errno);
    return false;
  }
  return true;
}

bool ActuatorNode::PathExists(const std::string& path) {
  // Avoid throwing on permission errors; callers manage degraded behaviour.
  std::error_code ec;
  return std::filesystem::exists(path, ec);
}

gpiod_line* ActuatorNode::RequestOutputLine(int gpio_number, int initial_level) {
  gpiod_line* line = gpiod_chip_get_line(gpio_chip_, gpio_number);
  if (line == nullptr) {
    RCLCPP_FATAL(get_logger(), "Failed to get GPIO line %d: %s", gpio_number, std::strerror(errno));
    throw std::runtime_error("gpiod_chip_get_line failed");
  }

  int request_result = gpiod_line_request_output(line, kGpioConsumerName, initial_level);
  if (request_result == 0) {
    return line;
  }

  if (errno == EBUSY) {
    RCLCPP_WARN(get_logger(), "GPIO %d busy, retrying after %lld ms", gpio_number,
                static_cast<long long>(kGpioRetryDelay.count()));
    rclcpp::sleep_for(kGpioRetryDelay);
    request_result = gpiod_line_request_output(line, kGpioConsumerName, initial_level);
    if (request_result == 0) {
      RCLCPP_INFO(get_logger(), "GPIO %d request succeeded after retry", gpio_number);
      return line;
    }
  }

  RCLCPP_FATAL(get_logger(), "Failed to request GPIO line %d: %s", gpio_number, std::strerror(errno));
  throw std::runtime_error("gpiod_line_request_output failed");
}

bool ActuatorNode::ExportChannel(int channel, std::string& err) {
  const std::string pwm_path = chip_path_ + "/pwm" + std::to_string(channel);
  if (PathExists(pwm_path)) {
    // Channel already exported by another process; treat as success for idempotence.
    return true;
  }

  const std::string export_path = chip_path_ + "/export";
  const bool exported = WriteFile(export_path, std::to_string(channel), err);
  if (exported) {
    rclcpp::sleep_for(kPwmExportDelay);
  }
  return exported;
}

bool ActuatorNode::EnsurePeriod(int channel, std::string& err) {
  const std::string period_path = chip_path_ + ChannelPath(channel, "period");
  return WriteFile(period_path, std::to_string(period_ns_), err);
}

bool ActuatorNode::EnableChannel(int channel, bool enable, std::string& err) {
  const std::string enable_path = chip_path_ + ChannelPath(channel, "enable");
  return WriteFile(enable_path, enable ? "1" : "0", err);
}

bool ActuatorNode::SetDutyPercent(int channel, int percent, std::string& err) {
  const int clamped_percent = std::clamp(percent, kMinDutyPercent, kMaxDutyPercent);
  const int64_t duty_ns = (period_ns_ * static_cast<int64_t>(clamped_percent)) / kMaxDutyPercent;
  const std::string duty_path = chip_path_ + ChannelPath(channel, "duty_cycle");
  return WriteFile(duty_path, std::to_string(duty_ns), err);
}

bool ActuatorNode::SetDirection(size_t actuator_index, ActuatorDirection direction, std::string& err) {
  if (actuator_index >= direction_lines_.size()) {
    err = "invalid actuator index";
    return false;
  }

  const bool active_high = direction_active_high_.at(actuator_index);
  int level = (direction == ActuatorDirection::kForward) ? 1 : 0;
  if (!active_high) {
    level = 1 - level;
  }

  const int result = gpiod_line_set_value(direction_lines_.at(actuator_index), level);
  if (result < 0) {
    err = std::string("gpiod_line_set_value failed: ") + std::strerror(errno);
    return false;
  }
  return true;
}

rclcpp_action::GoalResponse ActuatorNode::HandleGoal(const rclcpp_action::GoalUUID& uuid,
                                                     std::shared_ptr<const MoveActuator::Goal> goal) {
  (void)uuid;

  const auto now_ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch())
          .count();
  std::ostringstream summary;
  summary << "handleGoal actuators=" << goal->actuators.size() << " speeds=";
  summary << '[';
  for (size_t i = 0; i < goal->speed_percents.size(); ++i) {
    if (i != 0U) {
      summary << ',';
    }
    summary << goal->speed_percents[i];
  }
  summary << "] durations=[";
  for (size_t i = 0; i < goal->duration_ms.size(); ++i) {
    if (i != 0U) {
      summary << ',';
    }
    summary << goal->duration_ms[i];
  }
  summary << ']';
  RCLCPP_INFO(get_logger(), "[%lld ms] %s", static_cast<long long>(now_ms), summary.str().c_str());

  const size_t actuator_count = goal->actuators.size();
  if (actuator_count == 0U) {
    RCLCPP_WARN(get_logger(), "Rejecting goal: no actuators provided");
    return rclcpp_action::GoalResponse::REJECT;
  }

  if (goal->speed_percents.size() != actuator_count) {
    RCLCPP_WARN(get_logger(), "Rejecting goal: speed_percents size (%zu) does not match actuators (%zu)",
                goal->speed_percents.size(), actuator_count);
    return rclcpp_action::GoalResponse::REJECT;
  }

  const size_t duration_size = goal->duration_ms.size();
  if (!(duration_size == 0U || duration_size == 1U || duration_size == actuator_count)) {
    RCLCPP_WARN(get_logger(), "Rejecting goal: duration_ms length must be 0, 1, or match the actuator count (%zu)",
                actuator_count);
    return rclcpp_action::GoalResponse::REJECT;
  }

  std::vector<int32_t> seen;
  seen.reserve(actuator_count);
  for (size_t i = 0; i < actuator_count; ++i) {
    const int actuator_index = goal->actuators[i];
    if (actuator_index < 0 || actuator_index >= static_cast<int>(pwm_channels_.size())) {
      RCLCPP_WARN(get_logger(), "Rejecting goal: actuator index %d out of range [0, %zu)", actuator_index,
                  pwm_channels_.size());
      return rclcpp_action::GoalResponse::REJECT;
    }
    if (std::find(seen.begin(), seen.end(), actuator_index) != seen.end()) {
      RCLCPP_WARN(get_logger(), "Rejecting goal: duplicate actuator index %d", actuator_index);
      return rclcpp_action::GoalResponse::REJECT;
    }
    seen.push_back(actuator_index);
  }

  return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse ActuatorNode::HandleCancel(const std::shared_ptr<GoalHandleMove> goal_handle) {
  (void)goal_handle;
  return rclcpp_action::CancelResponse::ACCEPT;
}

void ActuatorNode::HandleAccepted(const std::shared_ptr<GoalHandleMove> goal_handle) {
  {
    std::lock_guard<std::mutex> lock(active_goal_mutex_);
    active_goal_ = goal_handle;
  }

  std::thread worker(&ActuatorNode::Execute, this, goal_handle);
  {
    std::lock_guard<std::mutex> lock(threads_mutex_);
    worker_threads_.push_back(std::move(worker));
  }
}

void ActuatorNode::Execute(const std::shared_ptr<GoalHandleMove> goal_handle) {
  if (shutting_down_) {
    auto result = std::make_shared<MoveActuator::Result>();
    result->success = false;
    result->message = "Node is shutting down";
    goal_handle->abort(result);
    ClearActiveGoalIfMatches(goal_handle);
    return;
  }

  const auto goal = goal_handle->get_goal();
  const size_t actuator_count = goal->actuators.size();

  std::vector<int> durations = NormalizeDurations(goal->duration_ms, actuator_count);

  std::vector<CommandState> commands;
  commands.reserve(actuator_count);

  // Pre-compute command metadata so execution loops rely on a single source of truth.

  std::string err;
  for (size_t i = 0; i < actuator_count; ++i) {
    const int actuator_index = goal->actuators[i];
    const int requested_speed = goal->speed_percents[i];
    const int clamped_speed = std::clamp(requested_speed, -kMaxDutyPercent, kMaxDutyPercent);
    const ActuatorDirection direction = DirectionFromPercent(clamped_speed);

    // Apply direction before duty to avoid transient reverse spikes on H-bridge hardware.
    if (!SetDirection(static_cast<size_t>(actuator_index), direction, err)) {
      auto result = std::make_shared<MoveActuator::Result>();
      result->success = false;
      result->message = "Failed to set direction: " + err;
      goal_handle->abort(result);
      ClearActiveGoalIfMatches(goal_handle);
      return;
    }

    if (!SetDutyPercent(pwm_channels_.at(actuator_index), std::abs(clamped_speed), err)) {
      auto result = std::make_shared<MoveActuator::Result>();
      result->success = false;
      result->message = "Failed to set duty cycle: " + err;
      goal_handle->abort(result);
      ClearActiveGoalIfMatches(goal_handle);
      return;
    }

    commands.push_back(
        CommandState{actuator_index, pwm_channels_.at(actuator_index), clamped_speed, direction, durations[i]});
  }

  RCLCPP_INFO_STREAM(get_logger(), "Execute goal with " << commands.size() << " actuators");

  auto feedback = std::make_shared<MoveActuator::Feedback>();
  feedback->current_speed_percents.assign(commands.size(), 0);
  feedback->elapsed_ms.assign(commands.size(), 0);
  feedback->remaining_ms.assign(commands.size(), 0);

  for (size_t index = 0; index < commands.size(); ++index) {
    feedback->current_speed_percents[index] = commands[index].clamped_speed;
    feedback->remaining_ms[index] = std::max(0, commands[index].duration_ms);
  }

  goal_handle->publish_feedback(feedback);

  const bool has_timed_commands = std::any_of(commands.begin(), commands.end(),
                                              [](const CommandState& command) { return command.duration_ms > 0; });

  if (!has_timed_commands) {
    // With no durations the call devolves to a synchronous "set outputs" request.
    auto result = std::make_shared<MoveActuator::Result>();
    result->success = true;
    result->message = "Duty cycles applied immediately";
    goal_handle->succeed(result);
    ClearActiveGoalIfMatches(goal_handle);
    return;
  }

  const std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
  const int safe_feedback_period_ms = std::max(1, feedback_period_ms_);
  // rclcpp::Rate enforces a uniform feedback cadence that downstream consumers can rely on.
  rclcpp::Rate rate{std::chrono::milliseconds(safe_feedback_period_ms)};

  while (rclcpp::ok()) {
    if (goal_handle->is_canceling()) {
      // Immediately request a stop on all actuators before acknowledging cancellation.
      for (const auto& command : commands) {
        if (!SetDutyPercent(command.pwm_channel, kMinDutyPercent, err)) {
          RCLCPP_WARN(get_logger(), "Failed to zero duty cycle for actuator %d while cancelling: %s",
                      command.actuator_index, err.c_str());
        }
      }
      auto cancel_result = std::make_shared<MoveActuator::Result>();
      cancel_result->success = false;
      cancel_result->message = "Goal cancelled";
      goal_handle->canceled(cancel_result);
      ClearActiveGoalIfMatches(goal_handle);
      return;
    }

    const auto now = std::chrono::steady_clock::now();
    const int elapsed_ms =
        static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count());

    bool all_completed = true;
    // Update elapsed/remaining timing per actuator and stop outputs once their duration elapses.
    for (size_t index = 0; index < commands.size(); ++index) {
      const auto& command = commands[index];
      if (command.duration_ms <= 0) {
        // Untimed commands retain their "hold" semantics while still delivering feedback consistency.
        feedback->elapsed_ms[index] = 0;
        feedback->remaining_ms[index] = 0;
        continue;
      }

      const int clamped_elapsed = std::min(elapsed_ms, command.duration_ms);
      feedback->elapsed_ms[index] = clamped_elapsed;
      feedback->remaining_ms[index] = std::max(0, command.duration_ms - clamped_elapsed);
      if (clamped_elapsed < command.duration_ms) {
        all_completed = false;
      } else if (feedback->current_speed_percents[index] != 0) {
        // For timed commands, stopping the PWM once duration is met prevents drift and overheating.
        if (!SetDutyPercent(command.pwm_channel, kMinDutyPercent, err)) {
          RCLCPP_WARN(get_logger(), "Failed to zero duty cycle for actuator %d on completion: %s",
                      command.actuator_index, err.c_str());
        }
        feedback->current_speed_percents[index] = 0;
        RCLCPP_DEBUG(get_logger(), "Actuator %d duration elapsed; duty set to zero", command.actuator_index);
      }
    }

    goal_handle->publish_feedback(feedback);

    if (all_completed) {
      break;
    }
    rate.sleep();
  }

  auto result = std::make_shared<MoveActuator::Result>();
  result->success = true;
  result->message = "Goal completed";
  goal_handle->succeed(result);
  ClearActiveGoalIfMatches(goal_handle);
}

/**
 * @brief Runs the actuator node within its executor until shutdown is requested.
 * @param argc Command line argument count.
 * @param argv Command line argument values.
 * @return Zero when shutdown completes successfully.
 */
int RunActuatorNode(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ActuatorNode>();
  rclcpp::executors::MultiThreadedExecutor executor;
  executor.add_node(node);
  executor.spin();
  rclcpp::shutdown();
  return 0;
}

}  // namespace transformer_hw_actuators

/**
 * @brief Application entry point responsible for delegating to the ROS node runner.
 * @param argc Command line argument count.
 * @param argv Command line argument values.
 * @return Process exit code propagated from the node runner.
 */
int main(int argc, char** argv) {
  return transformer_hw_actuators::RunActuatorNode(argc, argv);
}