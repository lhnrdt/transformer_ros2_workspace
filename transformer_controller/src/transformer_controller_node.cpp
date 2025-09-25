#include <algorithm>
#include <atomic>
#include <chrono>
#include <mutex>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <string>
#include <thread>

#include "transformer_controller/action/transform_mode.hpp"
#include "transformer_hw_actuators/action/move_actuator.hpp"
#include "transformer_hw_servos/action/move_servo.hpp"

using namespace std::chrono_literals;

class TransformerControllerNode : public rclcpp::Node {
 public:
  using MoveActuator = transformer_hw_actuators::action::MoveActuator;
  using MoveActuatorHandle = rclcpp_action::ClientGoalHandle<MoveActuator>;
  using MoveServo = transformer_hw_servos::action::MoveServo;
  using MoveServoHandle = rclcpp_action::ClientGoalHandle<MoveServo>;
  using TransformMode = transformer_controller::action::TransformMode;
  using TransformHandle = rclcpp_action::ServerGoalHandle<TransformMode>;

  TransformerControllerNode() : Node("transformer_controller") {
    actuator_client_ = rclcpp_action::create_client<MoveActuator>(this, "move_actuator");
    servo_client_ = rclcpp_action::create_client<MoveServo>(this, "move_servo");

    // Parameters controlling timings/pulses
    retract_speed_percent_ = this->declare_parameter<int>("retract_speed_percent", -100);  // negative direction
    retract_time_ms_ = this->declare_parameter<int>("retract_time_ms", 5000);
    extend_speed_percent_ = this->declare_parameter<int>("extend_speed_percent", 100);
    extend_time_ms_ = this->declare_parameter<int>("extend_time_ms", 4000);
    flight_servos_pulse_ = this->declare_parameter<int>("flight_servos_pulse", 2400);
    drive_servos_pulse_ = this->declare_parameter<int>("drive_servos_pulse", 450);
    servo_move_speed_us_per_s_ = this->declare_parameter<int>("servo_move_speed_us_per_s", 8000);
    // Safe servo gating fully removed; parameters no longer declared.

    RCLCPP_INFO(get_logger(),
                "TransformerControllerNode entering INIT state; will wait for action servers then retract actuators.");
    current_mode_ = "INIT";
    startup_timer_ = this->create_wall_timer(std::chrono::milliseconds(200), [this]() {
      if (init_complete_ || init_failed_)
        return;
      if (!actuator_client_->action_server_is_ready() || !servo_client_->action_server_is_ready()) {
        RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 5000,
                             "[INIT] Waiting for action servers (actuator=%s servo=%s)...",
                             actuator_client_->action_server_is_ready() ? "ready" : "waiting",
                             servo_client_->action_server_is_ready() ? "ready" : "waiting");
        return;
      }
      if (!retract_started_) {
        retract_started_ = true;
        RCLCPP_INFO(get_logger(), "[INIT] Action servers ready. Retracting actuators (%d ms @ %d%%).", retract_time_ms_,
                    retract_speed_percent_);
        startup_motion_active_.store(true);
        std::thread([this]() {
          bool ok = retract_actuators_blocking();
          startup_motion_active_.store(false);
          if (!ok) {
            RCLCPP_ERROR(get_logger(), "[INIT] Retract failed; retry once after %d ms", retract_retry_delay_ms_);
            std::this_thread::sleep_for(std::chrono::milliseconds(retract_retry_delay_ms_));
            startup_motion_active_.store(true);
            bool ok2 = retract_actuators_blocking();
            startup_motion_active_.store(false);
            if (!ok2) {
              RCLCPP_FATAL(get_logger(), "[INIT] Retract retry failed; initialization aborted");
              init_failed_ = true;
              return;
            }
            RCLCPP_WARN(get_logger(), "[INIT] Retract succeeded on retry");
          }
          current_mode_ = "IDLE";
          init_complete_ = true;
          RCLCPP_INFO(get_logger(), "[INIT] Initialization complete. Mode=IDLE (actuators retracted)");
          action_server_ = rclcpp_action::create_server<TransformMode>(
              this, "transform_mode",
              std::bind(&TransformerControllerNode::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
              std::bind(&TransformerControllerNode::handle_cancel, this, std::placeholders::_1),
              std::bind(&TransformerControllerNode::handle_accepted, this, std::placeholders::_1));
          RCLCPP_INFO(get_logger(), "Transform action server advertised.");
        }).detach();
      }
    });

    rclcpp::on_shutdown([this]() { begin_shutdown(); });
  }

 private:
  void wait_for_servers() {
    while (!actuator_client_->wait_for_action_server(1s)) {
      RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 5000, "Waiting for move_actuator action server...");
    }
    while (!servo_client_->wait_for_action_server(1s)) {
      RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 5000, "Waiting for move_servo action server...");
    }
  }

  rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID&,
                                          std::shared_ptr<const TransformMode::Goal> goal) {
    if (!init_complete_)
      return rclcpp_action::GoalResponse::REJECT;
    if (startup_motion_active_.load()) {
      RCLCPP_WARN(get_logger(), "Rejecting transform goal while startup motion active");
      return rclcpp_action::GoalResponse::REJECT;
    }
    if (goal->target_mode != "drive" && goal->target_mode != "flight")
      return rclcpp_action::GoalResponse::REJECT;
    if (goal->target_mode == current_mode_)
      return rclcpp_action::GoalResponse::REJECT;  // already there (could allow if adding repeat semantics)
    if (current_mode_ != "IDLE" && current_mode_ != "drive" && current_mode_ != "flight") {
      RCLCPP_WARN(get_logger(), "Rejecting transform goal: current mode %s is not a transformable state",
                  current_mode_.c_str());
      return rclcpp_action::GoalResponse::REJECT;
    }
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }
  rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<TransformHandle>&) {
    return rclcpp_action::CancelResponse::ACCEPT;
  }
  void handle_accepted(const std::shared_ptr<TransformHandle> gh) {
    if (shutting_down_.load()) {
      auto res = std::make_shared<TransformMode::Result>();
      res->success = false;
      res->message = "shutdown in progress";
      gh->abort(res);
      return;
    }
    // Reject if a transform goal is already active (avoid overlapping sequences)
    {
      std::lock_guard<std::mutex> lk(active_mutex_);
      if (active_transform_goal_) {
        auto res = std::make_shared<TransformMode::Result>();
        res->success = false;
        res->message = "another transform already active";
        gh->abort(res);
        return;
      }
    }
    // If previous worker thread finished but wasn't joined yet, join now to avoid std::terminate on reuse.
    if (worker_thread_.joinable()) {
      worker_thread_.join();
    }
    {
      std::lock_guard<std::mutex> lk(active_mutex_);
      active_transform_goal_ = gh;
    }
    worker_thread_ = std::thread(&TransformerControllerNode::execute, this, gh);
  }

  // Helper: send actuator move (blocking) for both actuators at same speed/time
  bool actuator_timed_run_blocking(int speed_percent, int duration_ms) {
    // Ensure actuator action server is ready (defensive in case transform goal arrives very early)
    if (!actuator_client_->action_server_is_ready()) {
      RCLCPP_WARN(get_logger(), "Actuator client not yet ready; waiting up to 3s before sending goal...");
      auto start = std::chrono::steady_clock::now();
      while (rclcpp::ok() && !actuator_client_->action_server_is_ready()) {
        if (std::chrono::steady_clock::now() - start > std::chrono::seconds(3)) {
          RCLCPP_ERROR(get_logger(), "Actuator action server not ready after wait; aborting timed run");
          return false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
      }
      if (actuator_client_->action_server_is_ready()) {
        RCLCPP_INFO(get_logger(), "Actuator client became ready after wait");
      }
    }
    // New multi-actuator action: single goal containing both actuators.
    MoveActuator::Goal goal;
    goal.actuators = {0, 1};
    goal.speed_percents = {speed_percent, speed_percent};
    goal.duration_ms = {duration_ms, duration_ms};  // Same time for each currently.
    // TODO: If future requirement needs different durations per actuator, expose separate params.
    RCLCPP_INFO(get_logger(), "Actuator timed run: speed=%d duration_ms=%d (submitting multi-actuator goal)",
                speed_percent, duration_ms);
    auto gh_future = actuator_client_->async_send_goal(goal);
    if (!wait_future(gh_future, std::chrono::seconds(2))) {
      RCLCPP_ERROR(get_logger(), "Timeout waiting for goal handle (multi-actuator) speed=%d duration=%d", speed_percent,
                   duration_ms);
      return false;
    }
    auto handle = gh_future.get();
    if (!handle) {
      RCLCPP_ERROR(get_logger(), "Null multi-actuator goal handle (speed=%d duration=%d)", speed_percent, duration_ms);
      return false;
    }
    auto res_future = actuator_client_->async_get_result(handle);
    if (!wait_future(res_future, std::chrono::milliseconds(duration_ms + 3000))) {
      RCLCPP_ERROR(get_logger(), "Timeout waiting multi-actuator result (duration=%d speed=%d)", duration_ms,
                   speed_percent);
      return false;
    }
    auto res = res_future.get();
    if (res.code != rclcpp_action::ResultCode::SUCCEEDED || !res.result->success) {
      RCLCPP_ERROR(get_logger(), "Multi-actuator run failed: %s",
                   res.result ? res.result->message.c_str() : "no result struct");
      return false;
    }
    RCLCPP_INFO(get_logger(), "Actuator timed run success (speed=%d duration_ms=%d)", speed_percent, duration_ms);
    return true;
  }

  bool retract_actuators_blocking() { return actuator_timed_run_blocking(retract_speed_percent_, retract_time_ms_); }
  bool extend_actuators_blocking() { return actuator_timed_run_blocking(extend_speed_percent_, extend_time_ms_); }

  bool move_servos_blocking(int pulse) {
    MoveServo::Goal goal;
    goal.channels = {1, 2};
    goal.pulse_us = pulse;
    goal.speed_us_per_s = servo_move_speed_us_per_s_;
    goal.use_trapezoid = false;
    goal.accel_us_per_s2 = 0;
    auto gh_future = servo_client_->async_send_goal(goal);
    if (!wait_future(gh_future, std::chrono::seconds(2))) {
      RCLCPP_ERROR(get_logger(), "Failed to send servo goal (timeout)");
      return false;
    }
    auto gh = gh_future.get();
    if (!gh) {
      RCLCPP_ERROR(get_logger(), "Null servo goal handle");
      return false;
    }
    auto res_future = servo_client_->async_get_result(gh);
    // Estimate duration: worst servo movement maybe (abs target - start)/speed; just provide generous timeout.
    if (!wait_future(res_future, std::chrono::seconds(10))) {
      RCLCPP_ERROR(get_logger(), "Servo result wait timeout");
      return false;
    }
    auto res = res_future.get();
    if (res.code != rclcpp_action::ResultCode::SUCCEEDED || !res.result->success) {
      RCLCPP_ERROR(get_logger(), "Servo move failed");
      return false;
    }
    last_servo_command_pulse_ = pulse;
    last_servo_motion_complete_ = true;
    return true;
  }

  // Safe servo gating removed

  template <typename FutureT, typename Rep, typename Period>
  bool wait_future(FutureT& fut, const std::chrono::duration<Rep, Period>& timeout) {
    auto start = std::chrono::steady_clock::now();
    while (rclcpp::ok()) {
      auto status = fut.wait_for(std::chrono::milliseconds(20));
      if (status == std::future_status::ready)
        return true;
      if (std::chrono::steady_clock::now() - start > timeout)
        return false;
      // Do not call spin_some here; main spin is already running this node.
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    return false;
  }

  void execute(const std::shared_ptr<TransformHandle> gh) {
    if (shutting_down_.load()) {
      auto res = std::make_shared<TransformMode::Result>();
      res->success = false;
      res->message = "node shutting down";
      gh->abort(res);
      clear_active_goal();
      return;
    }
    auto goal = gh->get_goal();
    auto fb = std::make_shared<TransformMode::Feedback>();
    auto res = std::make_shared<TransformMode::Result>();

    std::string target = goal->target_mode;
    RCLCPP_INFO(get_logger(), "Transform start: %s -> %s", current_mode_.c_str(), target.c_str());
    if (!init_complete_) {
      RCLCPP_ERROR(get_logger(), "Execute called before init_complete flag set; aborting");
      res->success = false;
      res->message = "init not complete";
      gh->abort(res);
      return;
    }

    // Simplified transform sequences (actuators already retracted in IDLE baseline)
    if (target == "drive") {
      // flight -> drive sequence now: retract actuators (if currently flight) then move servos to drive orientation
      if (current_mode_ == "flight") {
        fb->phase = "retracting_actuators";
        fb->progress = 0.2f;
        gh->publish_feedback(fb);
        if (!retract_actuators_blocking()) {
          res->success = false;
          res->message = "Actuator retract failed";
          gh->abort(res);
          return;
        }
      }
      fb->phase = "moving_servos_drive";
      fb->progress = 0.6f;
      gh->publish_feedback(fb);
      if (!move_servos_blocking(flight_servos_pulse_)) {
        res->success = false;
        res->message = "Servo move failed";
        gh->abort(res);
        return;
      }
      current_mode_ = "drive";
    } else {  // drive -> flight
      fb->phase = "moving_servos_flight";
      fb->progress = 0.4f;
      gh->publish_feedback(fb);
      if (!move_servos_blocking(drive_servos_pulse_)) {
        res->success = false;
        res->message = "Servo move failed";
        gh->abort(res);
        return;
      }
      fb->phase = "extending_actuators";
      fb->progress = 0.7f;
      gh->publish_feedback(fb);
      if (!extend_actuators_blocking()) {
        res->success = false;
        res->message = "Actuator extend failed";
        gh->abort(res);
        return;
      }
      current_mode_ = "flight";
    }

    fb->phase = "done";
    fb->progress = 1.0f;
    gh->publish_feedback(fb);
    res->success = true;
    res->message = "completed";
    res->final_mode = current_mode_;
    gh->succeed(res);
    RCLCPP_INFO(get_logger(), "Transform complete: now %s", current_mode_.c_str());
    clear_active_goal();
  }

  // Members
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
  int last_servo_command_pulse_{-1};
  bool last_servo_motion_complete_{false};
  // Initialization state machine flags
  bool startup_retract_{true};  // legacy param retained (could remove later)
  bool init_complete_{false};
  bool init_failed_{false};
  bool retract_started_{false};
  int retract_retry_delay_ms_{500};
  rclcpp::TimerBase::SharedPtr startup_timer_{};
  std::atomic<bool> startup_motion_active_{false};

  std::string current_mode_{"unknown"};

  // Shutdown/goal tracking
  std::atomic<bool> shutting_down_{false};
  std::mutex active_mutex_;
  std::shared_ptr<TransformHandle> active_transform_goal_{};  // only one at a time
  std::thread worker_thread_{};

  int64_t now_steady_ms() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch())
        .count();
  }

  // Shutdown helper declarations
  void begin_shutdown();
  void clear_active_goal();
  void cancel_active_goal_for_shutdown();
};

// --- Shutdown helpers implementation section appended near end of file (keep file single TU) ---
// We keep them inline above for simplicity; add member functions here if needed in future.

void TransformerControllerNode::clear_active_goal() {
  std::lock_guard<std::mutex> lk(active_mutex_);
  active_transform_goal_.reset();
}

void TransformerControllerNode::cancel_active_goal_for_shutdown() {
  std::shared_ptr<TransformHandle> gh;
  {
    std::lock_guard<std::mutex> lk(active_mutex_);
    gh = active_transform_goal_;
  }
  if (gh) {
    auto res = std::make_shared<TransformMode::Result>();
    res->success = false;
    res->message = "aborted due to shutdown";
    gh->abort(res);
  }
  clear_active_goal();
}

void TransformerControllerNode::begin_shutdown() {
  bool expected = false;
  if (!shutting_down_.compare_exchange_strong(expected, true))
    return;  // already running
  RCLCPP_INFO(get_logger(), "Controller beginning shutdown: aborting active transform goal");
  cancel_active_goal_for_shutdown();
  if (worker_thread_.joinable()) {
    if (worker_thread_.get_id() == std::this_thread::get_id()) {
      RCLCPP_WARN(get_logger(), "Worker thread is current thread during shutdown; skip join to avoid deadlock");
    } else {
      worker_thread_.join();
    }
  }
  RCLCPP_INFO(get_logger(), "Controller shutdown complete");
}

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TransformerControllerNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
