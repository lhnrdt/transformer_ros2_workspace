// Single-channel servo controller node (currently one logical channel exposed).
// Adds support for per-channel mechanical position offsets (additive pulse microseconds) and
// an optional startup move (profiled) to apply the offset after powering up at the un-offset position.

#include <cmath>
#include <memory>
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
    // Optional profiled startup move from logical initial pulse (physical without offset) to
    // physical initial pulse WITH offset. If disabled we apply offset instantly.
    startup_enable_ = this->declare_parameter<bool>("startup_move.enable", false);
    startup_speed_ = this->declare_parameter<int>("startup_move.speed_us_per_s", 4000);  // reasonable default
    startup_accel_ = this->declare_parameter<int>("startup_move.accel_us_per_s2", 0);    // heuristic if 0
    startup_use_trapezoid_ = this->declare_parameter<bool>("startup_move.use_trapezoid", true);
    // Trapezoidal profile parameters (optional). If disabled we use constant velocity (current behavior).
    enable_trapezoid_ =
        this->declare_parameter<bool>("enable_trapezoid", false);  // default profile flag (can be overridden per-goal)
    accel_us_per_s2_ = this->declare_parameter<int>("accel_us_per_s2", 0);  // default accel if goal doesn't specify

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

    action_server_ = rclcpp_action::create_server<MoveServo>(
        this, "move_servo",
        std::bind(&ServoControllerNode::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&ServoControllerNode::handle_cancel, this, std::placeholders::_1),
        std::bind(&ServoControllerNode::handle_accepted, this, std::placeholders::_1));

    RCLCPP_INFO(get_logger(), "Servo controller ready backend=%s freq=%dHz channels=%d startup_move=%s",
                backend_type_.c_str(), freq_hz_, channels_in_use_, startup_enable_ ? "on" : "off");

    // Optional startup profiled move to apply mechanical offset smoothly.
    if (startup_enable_) {
      RCLCPP_INFO(get_logger(), "Startup move enabled: speed=%dus/s accel=%dus/s^2 profile=%s", startup_speed_,
                  startup_accel_, startup_use_trapezoid_ ? "trapezoid" : "linear");
      for (int ch = 0; ch < channels_in_use_; ++ch) {
        int logical_start = logical_pulses_[ch];
        int offset = get_position_offset(ch);
        int physical_start = clampHardware(logical_start);  // logical_start already user-clamped
        int physical_target = clampHardware(logical_start + offset);
        int distance = physical_target - physical_start;
        if (physical_target != physical_start) {
          RCLCPP_INFO(get_logger(),
                      "Startup ch=%d logical_start=%d offset=%d physical_start=%d physical_target=%d distance=%d",
                      ch + 1, logical_start, offset, physical_start, physical_target, distance);
          std::thread(&ServoControllerNode::run_startup_move, this, ch, physical_start, physical_target).detach();
        } else if (offset != 0) {
          RCLCPP_INFO(get_logger(), "Startup ch=%d offset=%d instantaneous apply to %d (no distance)", ch + 1, offset,
                      physical_target);
          backend_->setPulse(ch, physical_target);
        } else {
          RCLCPP_DEBUG(get_logger(), "Startup ch=%d no offset", ch + 1);
        }
      }
    } else {
      for (int ch = 0; ch < channels_in_use_; ++ch) {
        int offset = get_position_offset(ch);
        if (offset != 0)
          backend_->setPulse(ch, clampHardware(logical_pulses_[ch] + offset));
      }
    }
  }

  ~ServoControllerNode() override {
    if (backend_)
      backend_->shutdown();
  }

 private:
  rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID&, std::shared_ptr<const MoveServo::Goal> goal) {
    if (goal->channels.empty())
      return rclcpp_action::GoalResponse::REJECT;
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
    std::thread(&ServoControllerNode::execute_goal, this, gh).detach();
  }

  void execute_goal(const std::shared_ptr<GoalHandleMove> gh) {
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
          if (elapsed < p.t_accel) {
            phase = "accel";
            double d = 0.5 * p.accel * elapsed * elapsed;
            f = d / worst;
          } else if (elapsed < (p.t_accel + p.t_cruise)) {
            phase = "cruise";
            double d_acc = 0.5 * p.accel * p.t_accel * p.t_accel;
            double t_c = elapsed - p.t_accel;
            double d = d_acc + p.cruise * t_c;
            f = d / worst;
          } else if (elapsed < p.total) {
            phase = "decel";
            double t_dec = elapsed - (p.t_accel + p.t_cruise);
            double d_acc = 0.5 * p.accel * p.t_accel * p.t_accel;
            double d_cr = p.cruise * p.t_cruise;
            double v_start = p.cruise;
            double d_dec = v_start * t_dec - 0.5 * p.accel * t_dec * t_dec;
            double d = d_acc + d_cr + d_dec;
            f = d / worst;
          } else {
            phase = "done";
            break;
          }
        } else {
          if (elapsed < p.t_accel) {
            phase = "accel";
            double d = 0.5 * p.accel * elapsed * elapsed;
            f = d / worst;
          } else if (elapsed < p.total) {
            phase = "decel";
            double t_dec = elapsed - p.t_accel;
            double d_acc = 0.5 * p.accel * p.t_accel * p.t_accel;
            double v_peak = p.accel * p.t_accel;
            double d_dec = v_peak * t_dec - 0.5 * p.accel * t_dec * t_dec;
            double d = d_acc + d_dec;
            f = d / worst;
          } else {
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

  void run_startup_move(int channel_index, int physical_start, int physical_target) {
    // Simple reuse of motion planning (subset). Distances are physical pulses.
    int speed = startup_speed_;
    bool use_trap = startup_use_trapezoid_;
    int accel = startup_accel_ > 0 ? startup_accel_ : (speed > 0 ? std::max(speed / 0.2, speed * 5.0) : 0);
    if (speed <= 0 || physical_start == physical_target) {
      backend_->setPulse(channel_index, physical_target);
      return;
    }
    double distance = static_cast<double>(physical_target - physical_start);
    double dir = distance > 0 ? 1.0 : -1.0;
    double remaining = std::abs(distance);
    const double rate_hz = 50.0;
    rclcpp::Rate rate(rate_hz);
    double elapsed = 0.0;
    struct P {
      bool trapezoid{false};
      bool triangular{false};
      double accel{0};
      double cruise_speed{0};
      double t_accel{0};
      double t_cruise{0};
      double total_time{0};
    } p;
    p.trapezoid = use_trap;
    double current = physical_start;
    if (!use_trap) {
      double step = static_cast<double>(speed) / rate_hz;
      while (rclcpp::ok() && remaining > 0.5) {
        double adv = std::min(step, remaining);
        current += dir * adv;
        remaining -= adv;
        backend_->setPulse(channel_index, clampHardware(static_cast<int>(std::round(current))));
        rate.sleep();
      }
    } else {
      p.accel = accel;
      p.cruise_speed = speed;
      p.t_accel = p.cruise_speed / p.accel;
      double dist_accel = 0.5 * p.accel * p.t_accel * p.t_accel;
      if (2 * dist_accel >= remaining) {
        p.triangular = true;
        p.t_accel = std::sqrt(remaining / p.accel);
        p.total_time = 2 * p.t_accel;
        p.cruise_speed = p.accel * p.t_accel;
      } else {
        double dist_cruise = remaining - 2 * dist_accel;
        p.t_cruise = dist_cruise / p.cruise_speed;
        p.total_time = 2 * p.t_accel + p.t_cruise;
      }
      while (rclcpp::ok()) {
        double vel = 0.0;
        if (elapsed < p.t_accel) {
          vel = p.accel * elapsed;
        } else if (!p.triangular && elapsed < (p.t_accel + p.t_cruise)) {
          vel = p.cruise_speed;
        } else if (elapsed < p.total_time) {
          double t_dec = elapsed - (p.triangular ? p.t_accel : (p.t_accel + p.t_cruise));
          vel = p.cruise_speed - p.accel * t_dec;
          if (vel < 0)
            vel = 0;
        } else {
          break;
        }
        double adv = vel / rate_hz;
        if (adv > remaining)
          adv = remaining;
        current += dir * adv;
        remaining -= adv;
        backend_->setPulse(channel_index, clampHardware(static_cast<int>(std::round(current))));
        if (remaining <= 0.5)
          break;
        rate.sleep();
        elapsed += 1.0 / rate_hz;
      }
    }
    backend_->setPulse(channel_index, clampHardware(physical_target));
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
  // Startup move configuration
  bool startup_enable_{false};
  int startup_speed_{0};
  int startup_accel_{0};
  bool startup_use_trapezoid_{true};
  std::unique_ptr<transformer_hw_servos::IServoBackend> backend_;
  rclcpp_action::Server<MoveServo>::SharedPtr action_server_;
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
