// Single-channel (configurable multi-channel) servo controller node.
// Simplified: removes previous optional profiled startup move logic. We assume hardware powers up
// and reaches its initial commanded position autonomously. We just wait a fixed delay before
// advertising the action server so the transformer_controller can reliably connect.

#include <atomic>
#include <cmath>
#include <memory>
#include <mutex>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <string>
#include <thread>

#include "transformer_hw_servos/action/move_servo.hpp"
#include "transformer_hw_servos/servo_backend.hpp"

#define HARDWARE_US_MIN 400
#define HARDWARE_US_MAX 2500
#define HARDWARE_HZ_MIN 40
#define HARDWARE_HZ_MAX 400

class ServoControllerNode : public rclcpp::Node {
 public:
  using MoveServo = transformer_hw_servos::action::MoveServo;
  using GoalHandleMove = rclcpp_action::ServerGoalHandle<MoveServo>;

  ServoControllerNode() : Node("transformer_hw_servos") {
    backend_type_ = this->declare_parameter<std::string>("backend_type", "pca9685");
    period_us_ = this->declare_parameter<int>("period_us", 20000);  // 50Hz default
    min_us_ = this->declare_parameter<int>("min_us", 1350);
    max_us_ = this->declare_parameter<int>("max_us", 2500);
    initial_us_ = this->declare_parameter<int>("initial_us", 1500);
    // Additive mechanical position offsets (logical -> physical = logical + offset).
    // Length may be 0..16; we only consume index 0 for now (channel 1).
    channels_in_use_ = this->declare_parameter<int>("channels_in_use", 1);
    if (channels_in_use_ < 1)
      channels_in_use_ = 1;
    if (channels_in_use_ > 16)
      channels_in_use_ = 16;
    {
      auto raw_offsets = this->declare_parameter<std::vector<int64_t>>("position_offsets_us", std::vector<int64_t>{});
      position_offsets_us_.assign(raw_offsets.begin(), raw_offsets.end());
      if (position_offsets_us_.size() < static_cast<size_t>(channels_in_use_))
        position_offsets_us_.resize(channels_in_use_, 0);
    }
    // Remove all startup_move parameters (deprecated). Any provided values are ignored.
    (void)this->declare_parameter<bool>("startup_move.enable", false);
    (void)this->declare_parameter<int>("startup_move.speed_us_per_s", 0);
    (void)this->declare_parameter<int>("startup_move.accel_us_per_s2", 0);
    (void)this->declare_parameter<bool>("startup_move.use_trapezoid", false);
    enable_trapezoid_ = this->declare_parameter<bool>("enable_trapezoid", false);
    accel_us_per_s2_ = this->declare_parameter<int>("accel_us_per_s2", 0);

    if (min_us_ < HARDWARE_US_MIN)
      min_us_ = HARDWARE_US_MIN;
    if (max_us_ > HARDWARE_US_MAX)
      max_us_ = HARDWARE_US_MAX;
    if (min_us_ > max_us_)
      std::swap(min_us_, max_us_);

    freq_hz_ = period_us_ > 0 ? static_cast<int>(1000000 / period_us_) : 50;
    int orig = freq_hz_;
    if (freq_hz_ < HARDWARE_HZ_MIN)
      freq_hz_ = HARDWARE_HZ_MIN;
    if (freq_hz_ > HARDWARE_HZ_MAX)
      freq_hz_ = HARDWARE_HZ_MAX;
    if (freq_hz_ != orig) {
      RCLCPP_WARN(get_logger(), "Requested frequency %dHz clamped to %dHz", orig, freq_hz_);
    }

    // Store initial logical pulses (user-clamped). Physical pulses (with offset) are applied later.
    logical_pulses_.assign(channels_in_use_, clampLogical(initial_us_));

    transformer_hw_servos::ServoBackendConfig
        cfg;  // Provide uniform values; backend may support >1 channels internally.
    cfg.freq_hz = freq_hz_;
    // Backend should always be given the true hardware-safe range so that physical values that
    // exceed the user logical bounds (due to mechanical offsets) are still permitted.
    cfg.min_us_global = HARDWARE_US_MIN;
    cfg.max_us_global = HARDWARE_US_MAX;
    cfg.channels_in_use = channels_in_use_;

    for (int i = 0; i < channels_in_use_ && i < 16; i++) {
      cfg.min_us_per_servo[i] = HARDWARE_US_MIN;
      cfg.max_us_per_servo[i] = HARDWARE_US_MAX;
      cfg.offset_us[i] = 0;  // backend phase offset (not position offset)
      cfg.initial_pulse_us[i] = clampHardware(logical_pulses_[i]);
    }

    if (backend_type_ == "lgpio")
      backend_ = transformer_hw_servos::create_lgpio_backend();
    else if (backend_type_ == "pca9685")
      backend_ = transformer_hw_servos::create_pca9685_backend();
    else
      throw std::runtime_error("Unsupported backend_type: " + backend_type_);
    if (!backend_->init(cfg))
      throw std::runtime_error("Backend init failed");

    // Fixed delay before advertising the action server (replaces earlier startup move gating).
    gate_action_server_ = true;  // now always gated for a fixed delay
    settle_delay_ms_ = 1000;     // 1 second as requested

    RCLCPP_INFO(get_logger(),
                "Servo controller (pre-advertise) backend=%s freq=%dHz channels=%d fixed_delay_before_advertise=%dms",
                backend_type_.c_str(), freq_hz_, channels_in_use_, settle_delay_ms_);

    // Apply any static offsets immediately.
    for (int ch = 0; ch < channels_in_use_; ++ch) {
      int offset = get_position_offset(ch);
      if (offset != 0) {
        backend_->setPulse(ch, clampHardware(logical_pulses_[ch] + offset));
      }
    }

    startup_completed_ = true;
    startup_done_time_ms_ = now_ms();

    // Single timer: after 1s advertise the action server.
    monitor_timer_ = this->create_wall_timer(std::chrono::milliseconds(50), [this]() {
      if (action_server_)
        return;
      if ((now_ms() - startup_done_time_ms_) < settle_delay_ms_)
        return;
      create_action_server();
    });

    // Register shutdown hook (Ctrl+C) to ensure we abort any active goal and put servos in safe state.
    rclcpp::on_shutdown([this]() { begin_shutdown(); });
  }

  ~ServoControllerNode() override {
    // Destructor should already be post-shutdown hook, but call again defensively.
    begin_shutdown();
    if (backend_) {
      backend_->shutdown();
    }
  }

 private:
  rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID&, std::shared_ptr<const MoveServo::Goal> goal) {
    // Validate goal
    if (goal->channels.empty()) {
      return rclcpp_action::GoalResponse::REJECT;
    }

    if (shutting_down_.load()) {
      RCLCPP_WARN(get_logger(), "Rejecting servo goal: shutting down");
      return rclcpp_action::GoalResponse::REJECT;
    }

    {
      std::lock_guard<std::mutex> lk(active_mutex_);
      if (active_goal_) {
        RCLCPP_WARN(get_logger(), "Rejecting servo goal: another goal active");
        return rclcpp_action::GoalResponse::REJECT;
      }
    }

    // Validate uniqueness and bounds
    std::vector<int32_t> seen;
    seen.reserve(goal->channels.size());

    for (auto ch : goal->channels) {
      if (ch < 1 || ch > channels_in_use_)
        return rclcpp_action::GoalResponse::REJECT;
      if (std::find(seen.begin(), seen.end(), ch) != seen.end())
        return rclcpp_action::GoalResponse::REJECT;
      seen.push_back(ch);
    }

    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }

  rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<GoalHandleMove>&) {
    return rclcpp_action::CancelResponse::ACCEPT;
  }

  void handle_accepted(const std::shared_ptr<GoalHandleMove> gh) {
    if (shutting_down_.load()) {
      auto res = std::make_shared<MoveServo::Result>();
      res->success = false;
      res->message = "shutdown in progress";
      gh->abort(res);
      return;
    }

    {
      std::lock_guard<std::mutex> lk(active_mutex_);
      active_goal_ = gh;
    }

    if (worker_thread_.joinable()) {
      RCLCPP_WARN(get_logger(), "Joining previous servo worker thread before starting new");
      worker_thread_.join();
    }

    worker_thread_ = std::thread(&ServoControllerNode::execute_goal, this, gh);
  }

  void execute_goal(const std::shared_ptr<GoalHandleMove> gh) {
    if (shutting_down_.load()) {
      auto res = std::make_shared<MoveServo::Result>();
      res->success = false;
      res->message = "node shutting down";
      gh->abort(res);
      clear_active_goal();
      return;
    }

    auto goal = gh->get_goal();

    // Normalize and prepare channel list
    std::vector<int> indices;
    indices.reserve(goal->channels.size());

    for (auto ch : goal->channels)
      indices.push_back(ch - 1);  // convert to 0-based

    int logical_target = clampLogical(goal->pulse_us);
    int speed = goal->speed_us_per_s;
    bool use_trap = goal->use_trapezoid || (!goal->use_trapezoid && enable_trapezoid_);
    int goal_accel = goal->accel_us_per_s2 > 0 ? goal->accel_us_per_s2 : accel_us_per_s2_;

    struct ChannelState {
      int logical_start;
      int physical_start;
      int physical_target;
      int offset;
      double distance;
      double dir;
    };

    std::vector<ChannelState> cs;
    cs.reserve(indices.size());
    double worst = 0.0;

    for (int idx : indices) {
      int logical_start = logical_pulses_[idx];
      int offset = get_position_offset(idx);
      int physical_start = clampHardware(logical_start + offset);
      int physical_target = clampHardware(logical_target + offset);
      double dist = static_cast<double>(physical_target - physical_start);
      double absd = std::abs(dist);
      worst = std::max(worst, absd);
      cs.push_back({logical_start, physical_start, physical_target, offset, absd, dist > 0 ? 1.0 : -1.0});
    }

    if (speed <= 0 || worst < 0.5) {
      // Instant apply
      auto res = std::make_shared<MoveServo::Result>();
      res->success = true;
      res->message = (worst < 0.5 ? "already at target" : "applied instantly");
      res->final_pulses_us.resize(indices.size());
      for (size_t i = 0; i < cs.size(); ++i) {
        logical_pulses_[indices[i]] = logical_target;
        backend_->setPulse(indices[i], cs[i].physical_target);
        res->final_pulses_us[i] = cs[i].physical_target;  // physical value
      }
      res->total_estimated_duration_s = 0.0f;
      gh->succeed(res);
      clear_active_goal();
      return;
    }

    struct Profile {
      bool trapezoid{false};
      bool triangular{false};
      double accel{0};
      double cruise{0};
      double t_accel{0};
      double t_cruise{0};
      double total{0};
    } p;

    p.trapezoid = use_trap;
    double est_duration = 0.0;

    if (!use_trap) {
      est_duration = worst / speed;
    } else {
      p.cruise = speed;
      p.accel = goal_accel > 0 ? static_cast<double>(goal_accel) : std::max(p.cruise / 0.2, p.cruise * 5.0);
      p.t_accel = p.cruise / p.accel;
      double dist_accel = 0.5 * p.accel * p.t_accel * p.t_accel;
      if (2 * dist_accel >= worst) {
        p.triangular = true;
        p.t_accel = std::sqrt(worst / p.accel);
        p.total = 2 * p.t_accel;
        est_duration = p.total;
        p.cruise = p.accel * p.t_accel;
      } else {
        double dist_cruise = worst - 2 * dist_accel;
        p.t_cruise = dist_cruise / p.cruise;
        p.total = 2 * p.t_accel + p.t_cruise;
        est_duration = p.total;
      }
    }

    RCLCPP_INFO(get_logger(), "Move request channels=%zu worst=%.1f speed=%d profile=%s est=%.3fs", indices.size(),
                worst, speed, use_trap ? (p.triangular ? "triangular" : "trapezoid") : "linear", est_duration);

    auto fb = std::make_shared<MoveServo::Feedback>();
    fb->current_pulses_us.resize(indices.size());
    const double rate_hz = 50.0;
    rclcpp::Rate rate(rate_hz);
    double elapsed = 0.0;
    std::string phase = use_trap ? "accel" : "linear";

    auto apply_fraction = [&](double f) {
      if (f > 1.0)
        f = 1.0;

      for (size_t i = 0; i < cs.size(); ++i) {
        double local_target_dist = cs[i].distance;  // full dist for channel i
        double traveled = local_target_dist * f;    // ensure synchronous completion
        double phys = cs[i].physical_start + (cs[i].dir * traveled);
        int phys_i = clampHardware(static_cast<int>(std::round(phys)));
        backend_->setPulse(indices[i], phys_i);
        logical_pulses_[indices[i]] = clampLogical(phys_i - cs[i].offset);  // keep stored logical within user limits
        fb->current_pulses_us[i] = phys_i;                                  // report physical value actually sent
      }
      fb->progress = static_cast<float>(f);
      fb->estimated_remaining_s = static_cast<float>(std::max(0.0, est_duration - elapsed));
      fb->phase = phase;
      gh->publish_feedback(fb);
    };

    if (!use_trap) {
      double step = static_cast<double>(speed) / rate_hz;
      double traveled = 0.0;
      while (rclcpp::ok() && traveled < worst - 0.5) {
        if (gh->is_canceling()) {
          auto res = std::make_shared<MoveServo::Result>();
          res->success = false;
          res->message = "canceled";
          res->total_estimated_duration_s = static_cast<float>(est_duration);
          res->final_pulses_us.resize(indices.size());
          for (size_t i = 0; i < indices.size(); ++i) {
            int phys_cur = clampHardware(logical_pulses_[indices[i]] + cs[i].offset);
            res->final_pulses_us[i] = phys_cur;
          }
          gh->canceled(res);
          return;
        }
        double adv = std::min(step, worst - traveled);
        traveled += adv;
        apply_fraction(traveled / worst);
        rate.sleep();
        elapsed += 1.0 / rate_hz;
      }
    } else {
      while (rclcpp::ok()) {

        if (gh->is_canceling()) {
          auto res = std::make_shared<MoveServo::Result>();
          res->success = false;
          res->message = "canceled";
          res->total_estimated_duration_s = static_cast<float>(est_duration);
          res->final_pulses_us.resize(indices.size());
          for (size_t i = 0; i < indices.size(); ++i) {
            int phys_cur = clampHardware(logical_pulses_[indices[i]] + cs[i].offset);
            res->final_pulses_us[i] = phys_cur;
          }
          gh->canceled(res);
          return;
        }

        double f = 0.0;

        if (!p.triangular) {
          // acceleration phase
          if (elapsed < p.t_accel) {
            phase = "accel";
            double d = 0.5 * p.accel * elapsed * elapsed;
            f = d / worst;
          }

          // cruise phase
          else if (elapsed < (p.t_accel + p.t_cruise)) {
            phase = "cruise";
            double d_acc = 0.5 * p.accel * p.t_accel * p.t_accel;
            double t_c = elapsed - p.t_accel;
            double d = d_acc + p.cruise * t_c;
            f = d / worst;
          }

          // deceleration phase
          else if (elapsed < p.total) {
            phase = "decel";
            double t_dec = elapsed - (p.t_accel + p.t_cruise);
            double d_acc = 0.5 * p.accel * p.t_accel * p.t_accel;
            double d_cr = p.cruise * p.t_cruise;
            double v_start = p.cruise;
            double d_dec = v_start * t_dec - 0.5 * p.accel * t_dec * t_dec;
            double d = d_acc + d_cr + d_dec;
            f = d / worst;
          }

          // done
          else {
            phase = "done";
            break;
          }
        }

        // triangle profile
        else {

          // acceleration phase
          if (elapsed < p.t_accel) {
            phase = "accel";
            double d = 0.5 * p.accel * elapsed * elapsed;
            f = d / worst;
          }

          // deceleration phase
          else if (elapsed < p.total) {
            phase = "decel";
            double t_dec = elapsed - p.t_accel;
            double d_acc = 0.5 * p.accel * p.t_accel * p.t_accel;
            double v_peak = p.accel * p.t_accel;
            double d_dec = v_peak * t_dec - 0.5 * p.accel * t_dec * t_dec;
            double d = d_acc + d_dec;
            f = d / worst;
          }

          // done
          else {
            phase = "done";
            break;
          }
        }

        if (f > 1.0)
          f = 1.0;

        apply_fraction(f);

        if (f >= 1.0)
          break;
        rate.sleep();
        elapsed += 1.0 / rate_hz;
      }
    }

    // Finalize
    for (size_t i = 0; i < cs.size(); ++i) {
      backend_->setPulse(indices[i], cs[i].physical_target);
      logical_pulses_[indices[i]] = logical_target;
    }
    auto res = std::make_shared<MoveServo::Result>();
    res->success = true;
    char msg[128];
    std::snprintf(msg, sizeof(msg), "completed est=%.3fs profile=%s", est_duration,
                  use_trap ? (p.triangular ? "triangular" : "trapezoid") : "linear");
    res->message = msg;
    res->final_pulses_us.resize(indices.size());
    for (size_t i = 0; i < cs.size(); ++i)
      res->final_pulses_us[i] = cs[i].physical_target;
    res->total_estimated_duration_s = static_cast<float>(est_duration);
    gh->succeed(res);
    clear_active_goal();
  }

  void clear_active_goal() {
    std::lock_guard<std::mutex> lk(active_mutex_);
    active_goal_.reset();
  }

  void cancel_active_goal_for_shutdown() {
    std::shared_ptr<GoalHandleMove> gh;
    {
      std::lock_guard<std::mutex> lk(active_mutex_);
      gh = active_goal_;
    }
    if (gh) {
      auto res = std::make_shared<MoveServo::Result>();
      res->success = false;
      res->message = "aborted due to shutdown";
      gh->abort(res);
    }
    clear_active_goal();
  }

  void begin_shutdown() {
    bool expected = false;
    if (!shutting_down_.compare_exchange_strong(expected, true))
      return;  // already running
    RCLCPP_INFO(get_logger(), "Servo node beginning shutdown: aborting active goal, neutralizing outputs");
    cancel_active_goal_for_shutdown();
    // Put all used channels to a neutral pulse (initial logical + offset) or clamp.
    if (backend_) {
      for (int ch = 0; ch < channels_in_use_; ++ch) {
        int logical = logical_pulses_.size() > static_cast<size_t>(ch) ? logical_pulses_[ch] : initial_us_;
        int phys = clampHardware(logical + get_position_offset(ch));
        backend_->setPulse(ch, phys);
      }
    }
    if (worker_thread_.joinable()) {
      if (worker_thread_.get_id() == std::this_thread::get_id()) {
        RCLCPP_WARN(get_logger(), "Worker thread is current thread during shutdown; not joining to avoid deadlock");
      } else {
        worker_thread_.join();
      }
    }
    RCLCPP_INFO(get_logger(), "Shutdown: servos complete");
  }

  // Clamp a logical (user-facing) pulse using configured user min/max.
  int clampLogical(int us) const {
    if (us < min_us_)
      return min_us_;
    if (us > max_us_)
      return max_us_;
    return us;
  }

  // Clamp a physical (offset-applied) pulse strictly to hardware safe limits only.
  int clampHardware(int us) const {
    if (us < HARDWARE_US_MIN)
      return HARDWARE_US_MIN;
    if (us > HARDWARE_US_MAX)
      return HARDWARE_US_MAX;
    return us;
  }

  int get_position_offset(int channel_index) const {
    if (channel_index >= 0 && channel_index < static_cast<int>(position_offsets_us_.size()))
      return static_cast<int>(position_offsets_us_[channel_index]);
    return 0;
  }

  // Removed run_startup_move* functions (no longer needed with fixed delay)

  void create_action_server() {
    if (action_server_)
      return;
    action_server_ = rclcpp_action::create_server<MoveServo>(
        this, "move_servo",
        std::bind(&ServoControllerNode::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&ServoControllerNode::handle_cancel, this, std::placeholders::_1),
        std::bind(&ServoControllerNode::handle_accepted, this, std::placeholders::_1));
    RCLCPP_INFO(get_logger(), "Servo action server advertised (ready) backend=%s", backend_type_.c_str());
  }

  int64_t now_ms() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch())
        .count();
  }

  std::string backend_type_;
  int period_us_{};
  int freq_hz_{};
  int min_us_{};
  int max_us_{};
  int initial_us_{};
  int channels_in_use_{1};
  std::vector<int> logical_pulses_{};  // last logical pulse per channel
  bool enable_trapezoid_{false};
  int accel_us_per_s2_{0};
  std::vector<int64_t> position_offsets_us_{};  // additive per-channel logical->physical offsets (param raw type)
  // Startup move configuration removed
  std::unique_ptr<transformer_hw_servos::IServoBackend> backend_;
  rclcpp_action::Server<MoveServo>::SharedPtr action_server_;
  bool gate_action_server_{true};
  int settle_delay_ms_{300};
  std::atomic<int> pending_startup_moves_{0};
  std::atomic<bool> startup_completed_{false};
  int64_t startup_done_time_ms_{0};
  rclcpp::TimerBase::SharedPtr monitor_timer_{};
  // Shutdown / goal tracking
  std::atomic<bool> shutting_down_{false};
  std::mutex active_mutex_;
  std::shared_ptr<GoalHandleMove> active_goal_{};
  std::thread worker_thread_{};
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  try {
    auto node = std::make_shared<ServoControllerNode>();
    rclcpp::spin(node);
  } catch (const std::exception& e) {
    RCLCPP_FATAL(rclcpp::get_logger("transformer_hw_servos"), "Fatal: %s", e.what());
  }
  rclcpp::shutdown();
  return 0;
}
