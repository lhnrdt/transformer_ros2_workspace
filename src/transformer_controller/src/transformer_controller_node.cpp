#include <atomic>
#include <chrono>
#include <future>
#include <memory>
#include <mutex>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <string>
#include <thread>
#include <utility>

#include "transformer_controller/action/transform_mode.hpp"
#include "transformer_hw_actuators/action/move_actuator.hpp"
#include "transformer_hw_servos/action/move_servo.hpp"

using namespace std::chrono_literals;

namespace {

constexpr char kNodeName[] = "transformer_controller";
constexpr char kTransformActionName[] = "transform_mode";
constexpr char kActuatorActionName[] = "move_actuator";
constexpr char kServoActionName[] = "move_servo";

constexpr char kModeUnknown[] = "unknown";
constexpr char kModeInit[] = "INIT";
constexpr char kModeIdle[] = "IDLE";
constexpr char kModeDrive[] = "drive";
constexpr char kModeFlight[] = "flight";

constexpr auto kStartupTimerPeriod = std::chrono::milliseconds(200);
constexpr auto kThrottleInterval = std::chrono::milliseconds(5000);
constexpr auto kActionServerWaitTimeout = std::chrono::seconds(3);
constexpr auto kActionServerPollInterval = std::chrono::milliseconds(50);
constexpr auto kGoalHandleTimeout = std::chrono::seconds(2);
constexpr auto kServoResultTimeout = std::chrono::seconds(10);
constexpr auto kResultGracePeriod = std::chrono::milliseconds(3000);

}  // namespace

class TransformerControllerNode : public rclcpp::Node {
 public:
  using MoveActuator = transformer_hw_actuators::action::MoveActuator;
  using MoveActuatorHandle = rclcpp_action::ClientGoalHandle<MoveActuator>;
  using MoveServo = transformer_hw_servos::action::MoveServo;
  using MoveServoHandle = rclcpp_action::ClientGoalHandle<MoveServo>;
  using TransformMode = transformer_controller::action::TransformMode;
  using TransformHandle = rclcpp_action::ServerGoalHandle<TransformMode>;

  TransformerControllerNode();
  ~TransformerControllerNode() override;

 private:
  void StartInitializationTick();
  void RunStartupRetract();
  void AdvertiseTransformServer();

  rclcpp_action::GoalResponse HandleGoal(const rclcpp_action::GoalUUID&,
                                         std::shared_ptr<const TransformMode::Goal> goal);
  rclcpp_action::CancelResponse HandleCancel(const std::shared_ptr<TransformHandle>& goal_handle);
  void HandleAccepted(const std::shared_ptr<TransformHandle> goal_handle);
  void ExecuteTransform(const std::shared_ptr<TransformHandle> goal_handle);

  [[nodiscard]] bool RunActuatorTimedGoal(int speed_percent, int duration_ms);
  [[nodiscard]] bool RetractActuators();
  [[nodiscard]] bool ExtendActuators();
  [[nodiscard]] bool MoveServos(int pulse);

  template <typename FutureT, typename Rep, typename Period>
  [[nodiscard]] bool WaitForFuture(FutureT& fut,
                                   const std::chrono::duration<Rep, Period>& timeout);

  void BeginShutdown();
  void CancelActiveGoalForShutdown();
  void ClearActiveGoal();
  void SetCurrentMode(std::string mode);
  std::string GetCurrentMode() const;

  rclcpp_action::Client<MoveActuator>::SharedPtr actuator_client_;
  rclcpp_action::Client<MoveServo>::SharedPtr servo_client_;
  rclcpp_action::Server<TransformMode>::SharedPtr action_server_;

  int retract_speed_percent_{-100};
  int retract_time_ms_{5000};
  int extend_speed_percent_{100};
  int extend_time_ms_{4000};
  int flight_servos_pulse_{2400};
  int drive_servos_pulse_{450};
  int servo_move_speed_us_per_s_{8000};
  const int retract_retry_delay_ms_{500};

  rclcpp::TimerBase::SharedPtr startup_timer_;
  std::thread worker_thread_;
  std::thread startup_thread_;

  std::atomic<bool> init_complete_{false};
  std::atomic<bool> init_failed_{false};
  std::atomic<bool> retract_started_{false};
  std::atomic<bool> startup_motion_active_{false};
  std::atomic<bool> shutting_down_{false};

  mutable std::mutex active_mutex_;
  std::shared_ptr<TransformHandle> active_transform_goal_;

  mutable std::mutex mode_mutex_;
  std::string current_mode_{kModeUnknown};
};

TransformerControllerNode::TransformerControllerNode() : Node(kNodeName) {
  actuator_client_ = rclcpp_action::create_client<MoveActuator>(this, kActuatorActionName);
  servo_client_ = rclcpp_action::create_client<MoveServo>(this, kServoActionName);

  retract_speed_percent_ = declare_parameter<int>("retract_speed_percent", -100);
  retract_time_ms_ = declare_parameter<int>("retract_time_ms", 5000);
  extend_speed_percent_ = declare_parameter<int>("extend_speed_percent", 100);
  extend_time_ms_ = declare_parameter<int>("extend_time_ms", 4000);
  flight_servos_pulse_ = declare_parameter<int>("flight_servos_pulse", 2400);
  drive_servos_pulse_ = declare_parameter<int>("drive_servos_pulse", 450);
  servo_move_speed_us_per_s_ = declare_parameter<int>("servo_move_speed_us_per_s", 8000);

  RCLCPP_INFO(get_logger(),
              "TransformerControllerNode entering INIT state; will wait for action servers then retract actuators.");

  SetCurrentMode(kModeInit);

  startup_timer_ = create_wall_timer(kStartupTimerPeriod, [this]() { StartInitializationTick(); });

  rclcpp::on_shutdown([this]() { BeginShutdown(); });
}

TransformerControllerNode::~TransformerControllerNode() {
  BeginShutdown();
}

// Poll action servers until they are ready, then launch the baseline retract.
void TransformerControllerNode::StartInitializationTick() {
  if (init_complete_.load() || init_failed_.load()) {
    return;
  }

  const bool actuator_ready = actuator_client_->action_server_is_ready();
  const bool servo_ready = servo_client_->action_server_is_ready();

  if (!actuator_ready || !servo_ready) {
    RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), kThrottleInterval.count(),
                         "[INIT] Waiting for action servers (actuator=%s servo=%s)...",
                         actuator_ready ? "ready" : "waiting", servo_ready ? "ready" : "waiting");
    return;
  }

  bool expected = false;
  if (!retract_started_.compare_exchange_strong(expected, true)) {
    return;
  }

  RCLCPP_INFO(get_logger(), "[INIT] Action servers ready. Retracting actuators (%d ms @ %d%%).", retract_time_ms_,
              retract_speed_percent_);

  startup_motion_active_.store(true);
  startup_thread_ = std::thread(&TransformerControllerNode::RunStartupRetract, this);
}

// Perform the blocking retract in a worker thread so the timer stays responsive.
void TransformerControllerNode::RunStartupRetract() {
  auto clear_motion_flag = [this]() { startup_motion_active_.store(false); };

  bool success = RetractActuators();
  clear_motion_flag();

  if (!success) {
    RCLCPP_ERROR(get_logger(), "[INIT] Retract failed; retry once after %d ms", retract_retry_delay_ms_);
    std::this_thread::sleep_for(std::chrono::milliseconds(retract_retry_delay_ms_));

    startup_motion_active_.store(true);
    success = RetractActuators();
    clear_motion_flag();

    if (!success) {
      RCLCPP_FATAL(get_logger(), "[INIT] Retract retry failed; initialization aborted");
      init_failed_.store(true);
      return;
    }

    RCLCPP_WARN(get_logger(), "[INIT] Retract succeeded on retry");
  }

  SetCurrentMode(kModeIdle);
  init_complete_.store(true);
  RCLCPP_INFO(get_logger(), "[INIT] Initialization complete. Mode=IDLE (actuators retracted)");

  if (startup_timer_) {
    startup_timer_->cancel();
  }

  AdvertiseTransformServer();
}

void TransformerControllerNode::AdvertiseTransformServer() {
  if (action_server_) {
    return;
  }

  action_server_ = rclcpp_action::create_server<TransformMode>(
      this, kTransformActionName,
      [this](const rclcpp_action::GoalUUID& uuid,
             std::shared_ptr<const TransformMode::Goal> goal) {
        return HandleGoal(uuid, goal);
      },
      [this](const std::shared_ptr<TransformHandle>& goal_handle) {
        return HandleCancel(goal_handle);
      },
      [this](const std::shared_ptr<TransformHandle>& goal_handle) {
        HandleAccepted(goal_handle);
      });

  RCLCPP_INFO(get_logger(), "Transform action server advertised.");
}

rclcpp_action::GoalResponse TransformerControllerNode::HandleGoal(
    const rclcpp_action::GoalUUID&, std::shared_ptr<const TransformMode::Goal> goal) {
  if (!init_complete_.load()) {
    return rclcpp_action::GoalResponse::REJECT;
  }

  if (startup_motion_active_.load()) {
    RCLCPP_WARN(get_logger(), "Rejecting transform goal while startup motion active");
    return rclcpp_action::GoalResponse::REJECT;
  }

  {
    std::lock_guard<std::mutex> lock(active_mutex_);
    if (active_transform_goal_) {
      RCLCPP_WARN(get_logger(), "Rejecting transform goal: another transform already active");
      return rclcpp_action::GoalResponse::REJECT;
    }
  }

  const std::string& target_mode = goal->target_mode;
  if (target_mode != kModeDrive && target_mode != kModeFlight) {
    return rclcpp_action::GoalResponse::REJECT;
  }

  const std::string current_mode = GetCurrentMode();
  if (target_mode == current_mode) {
    return rclcpp_action::GoalResponse::REJECT;
  }

  if (current_mode != kModeIdle && current_mode != kModeDrive && current_mode != kModeFlight) {
    RCLCPP_WARN(get_logger(), "Rejecting transform goal: current mode %s is not transformable", current_mode.c_str());
    return rclcpp_action::GoalResponse::REJECT;
  }

  return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse TransformerControllerNode::HandleCancel(
    const std::shared_ptr<TransformHandle>&) {
  return rclcpp_action::CancelResponse::ACCEPT;
}

void TransformerControllerNode::HandleAccepted(const std::shared_ptr<TransformHandle> goal_handle) {
  if (shutting_down_.load()) {
    auto result = std::make_shared<TransformMode::Result>();
    result->success = false;
    result->message = "shutdown in progress";
    goal_handle->abort(result);
    return;
  }

  {
    std::lock_guard<std::mutex> lock(active_mutex_);
    if (active_transform_goal_) {
      auto result = std::make_shared<TransformMode::Result>();
      result->success = false;
      result->message = "another transform already active";
      goal_handle->abort(result);
      return;
    }
  }

  if (worker_thread_.joinable()) {
    worker_thread_.join();
  }

  {
    std::lock_guard<std::mutex> lock(active_mutex_);
    active_transform_goal_ = goal_handle;
  }

  worker_thread_ = std::thread(&TransformerControllerNode::ExecuteTransform, this, goal_handle);
}

void TransformerControllerNode::ExecuteTransform(const std::shared_ptr<TransformHandle> goal_handle) {
  // Ensure the active goal slot is cleared regardless of how this worker exits.
  struct ScopedGoalCleanup {
    TransformerControllerNode* node;
    ~ScopedGoalCleanup() {
      if (node != nullptr) {
        node->ClearActiveGoal();
      }
    }
  } goal_guard{this};

  if (shutting_down_.load()) {
    auto result = std::make_shared<TransformMode::Result>();
    result->success = false;
    result->message = "node shutting down";
    goal_handle->abort(result);
    return;
  }

  auto goal = goal_handle->get_goal();
  auto feedback = std::make_shared<TransformMode::Feedback>();
  auto result = std::make_shared<TransformMode::Result>();

  const std::string target_mode = goal->target_mode;
  const std::string starting_mode = GetCurrentMode();

  RCLCPP_INFO(get_logger(), "Transform start: %s -> %s", starting_mode.c_str(), target_mode.c_str());

  if (!init_complete_.load()) {
    RCLCPP_ERROR(get_logger(), "Execute called before init_complete flag set; aborting");
    result->success = false;
    result->message = "init not complete";
    goal_handle->abort(result);
    return;
  }

  if (target_mode == kModeDrive) {
    if (starting_mode == kModeFlight) {
      feedback->phase = "retracting_actuators";
      feedback->progress = 0.2F;
      goal_handle->publish_feedback(feedback);
      if (!RetractActuators()) {
        result->success = false;
        result->message = "actuator retract failed";
        goal_handle->abort(result);
        return;
      }
    }

    feedback->phase = "moving_servos_drive";
    feedback->progress = 0.6F;
    goal_handle->publish_feedback(feedback);

    if (!MoveServos(drive_servos_pulse_)) {
      result->success = false;
      result->message = "servo move failed";
      goal_handle->abort(result);
      return;
    }

    SetCurrentMode(kModeDrive);
  } else {
    feedback->phase = "moving_servos_flight";
    feedback->progress = 0.4F;
    goal_handle->publish_feedback(feedback);

    if (!MoveServos(flight_servos_pulse_)) {
      result->success = false;
      result->message = "servo move failed";
      goal_handle->abort(result);
      return;
    }

    feedback->phase = "extending_actuators";
    feedback->progress = 0.7F;
    goal_handle->publish_feedback(feedback);

    if (!ExtendActuators()) {
      result->success = false;
      result->message = "actuator extend failed";
      goal_handle->abort(result);
      return;
    }

    SetCurrentMode(kModeFlight);
  }

  feedback->phase = "done";
  feedback->progress = 1.0F;
  goal_handle->publish_feedback(feedback);

  const std::string final_mode = GetCurrentMode();
  result->success = true;
  result->message = "completed";
  result->final_mode = final_mode;
  goal_handle->succeed(result);

  RCLCPP_INFO(get_logger(), "Transform complete: now %s", final_mode.c_str());
}

template <typename FutureT, typename Rep, typename Period>
bool TransformerControllerNode::WaitForFuture(
    FutureT& fut, const std::chrono::duration<Rep, Period>& timeout) {
  auto start = std::chrono::steady_clock::now();
  while (rclcpp::ok()) {
    if (fut.wait_for(std::chrono::milliseconds(20)) == std::future_status::ready) {
      return true;
    }
    if (std::chrono::steady_clock::now() - start > timeout) {
      return false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  return false;
}

// Issue a synchronous actuator command for both cylinders with symmetric timing.
bool TransformerControllerNode::RunActuatorTimedGoal(int speed_percent, int duration_ms) {
  if (!actuator_client_->action_server_is_ready()) {
    const auto wait_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(kActionServerWaitTimeout).count();
    RCLCPP_WARN(get_logger(), "Actuator client not yet ready; waiting up to %ld ms before sending goal...", wait_ms);

    auto start = std::chrono::steady_clock::now();

    while (rclcpp::ok() && !actuator_client_->action_server_is_ready()) {
      if (std::chrono::steady_clock::now() - start > kActionServerWaitTimeout) {
        RCLCPP_ERROR(get_logger(), "Actuator action server not ready after wait; aborting timed run");
        return false;
      }
      std::this_thread::sleep_for(kActionServerPollInterval);
    }

    if (actuator_client_->action_server_is_ready()) {
      RCLCPP_INFO(get_logger(), "Actuator client became ready after wait");
    }
  }

  MoveActuator::Goal goal;
  goal.actuators = {0, 1};
  goal.speed_percents = {speed_percent, speed_percent};
  goal.duration_ms = {duration_ms, duration_ms};

  RCLCPP_INFO(get_logger(), "Actuator timed run: speed=%d duration_ms=%d", speed_percent, duration_ms);

  auto goal_future = actuator_client_->async_send_goal(goal);
  if (!WaitForFuture(goal_future, kGoalHandleTimeout)) {
    RCLCPP_ERROR(get_logger(), "Timeout waiting for actuator goal handle (speed=%d duration=%d)", speed_percent,
                 duration_ms);
    return false;
  }

  auto goal_handle = goal_future.get();
  if (!goal_handle) {
    RCLCPP_ERROR(get_logger(), "Null actuator goal handle (speed=%d duration=%d)", speed_percent, duration_ms);
    return false;
  }

  auto result_future = actuator_client_->async_get_result(goal_handle);
  const auto timeout = std::chrono::milliseconds(duration_ms) + kResultGracePeriod;
  if (!WaitForFuture(result_future, timeout)) {
    RCLCPP_ERROR(get_logger(), "Timeout waiting for actuator result (duration=%d speed=%d)", duration_ms, speed_percent);
    return false;
  }

  auto result = result_future.get();
  if (result.code != rclcpp_action::ResultCode::SUCCEEDED || !result.result || !result.result->success) {
    const char* message = result.result ? result.result->message.c_str() : "no result";
    RCLCPP_ERROR(get_logger(), "Actuator run failed: %s", message);
    return false;
  }

  RCLCPP_INFO(get_logger(), "Actuator timed run success (speed=%d duration_ms=%d)", speed_percent, duration_ms);
  return true;
}

bool TransformerControllerNode::RetractActuators() {
  return RunActuatorTimedGoal(retract_speed_percent_, retract_time_ms_);
}

bool TransformerControllerNode::ExtendActuators() {
  return RunActuatorTimedGoal(extend_speed_percent_, extend_time_ms_);
}

// Drive paired servos to a target PWM pulse width with bounded speed.
bool TransformerControllerNode::MoveServos(int pulse) {
  MoveServo::Goal goal;
  goal.channels = {1, 2};
  goal.pulse_us = pulse;
  goal.speed_us_per_s = servo_move_speed_us_per_s_;
  goal.use_trapezoid = true;
  goal.accel_us_per_s2 = 1000;

  auto goal_future = servo_client_->async_send_goal(goal);
  if (!WaitForFuture(goal_future, kGoalHandleTimeout)) {
    RCLCPP_ERROR(get_logger(), "Failed to send servo goal (timeout)");
    return false;
  }

  auto goal_handle = goal_future.get();
  if (!goal_handle) {
    RCLCPP_ERROR(get_logger(), "Null servo goal handle");
    return false;
  }

  auto result_future = servo_client_->async_get_result(goal_handle);
  if (!WaitForFuture(result_future, kServoResultTimeout)) {
    RCLCPP_ERROR(get_logger(), "Servo result wait timeout");
    return false;
  }

  auto result = result_future.get();
  if (result.code != rclcpp_action::ResultCode::SUCCEEDED || !result.result || !result.result->success) {
    RCLCPP_ERROR(get_logger(), "Servo move failed");
    return false;
  }

  return true;
}

void TransformerControllerNode::BeginShutdown() {
  bool expected = false;
  if (!shutting_down_.compare_exchange_strong(expected, true)) {
    return;
  }

  RCLCPP_INFO(get_logger(), "Controller beginning shutdown: aborting active transform goal");
  CancelActiveGoalForShutdown();

  if (worker_thread_.joinable()) {
    if (worker_thread_.get_id() == std::this_thread::get_id()) {
      RCLCPP_WARN(get_logger(), "Worker thread is current thread during shutdown; skip join to avoid deadlock");
    } else {
      worker_thread_.join();
    }
  }

  if (startup_thread_.joinable()) {
    if (startup_thread_.get_id() == std::this_thread::get_id()) {
      RCLCPP_WARN(get_logger(), "Startup thread is current thread during shutdown; skipping join");
    } else {
      startup_thread_.join();
    }
  }

  RCLCPP_INFO(get_logger(), "Controller shutdown complete");
}

void TransformerControllerNode::CancelActiveGoalForShutdown() {
  std::shared_ptr<TransformHandle> goal_handle;
  {
    std::lock_guard<std::mutex> lock(active_mutex_);
    goal_handle = active_transform_goal_;
  }

  if (goal_handle) {
    auto result = std::make_shared<TransformMode::Result>();
    result->success = false;
    result->message = "aborted due to shutdown";
    goal_handle->abort(result);
  }

  ClearActiveGoal();
}

void TransformerControllerNode::ClearActiveGoal() {
  std::lock_guard<std::mutex> lock(active_mutex_);
  active_transform_goal_.reset();
}

void TransformerControllerNode::SetCurrentMode(std::string mode) {
  std::lock_guard<std::mutex> lock(mode_mutex_);
  current_mode_ = std::move(mode);
}

std::string TransformerControllerNode::GetCurrentMode() const {
  std::lock_guard<std::mutex> lock(mode_mutex_);
  return current_mode_;
}

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TransformerControllerNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
