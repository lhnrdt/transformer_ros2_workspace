#include "transformer_hw_actuators/actuator_node.h"

#include <algorithm>
#include <cerrno>
#include <chrono>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <thread>

#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;
namespace fs = std::filesystem;

namespace transformer_hw_actuators
{

  ActuatorNode::ActuatorNode(const rclcpp::NodeOptions &options) : Node("actuator_node", options)
  {

    // Register shutdown callback early (safe because node lifetime >= shutdown callback invocation)
    rclcpp::on_shutdown([this]()
                        { this->begin_shutdown(); });

    // Parameters with DC motor defaults
    pwmchip_index_ = this->declare_parameter<int>("pwmchip_index", 0);
    gpiochip_name_ = this->declare_parameter<std::string>("gpiochip_name", "gpiochip4");
    stby_gpio_ = this->declare_parameter<int>("stby_gpio", 26);
    mode_gpio_ = this->declare_parameter<int>("mode_gpio", 0);

    // NOTE: integer arrays are int64 in ROS 2 parameters. Declare as int64 and cast.
    auto pwm_channels_i64 = this->declare_parameter<std::vector<int64_t>>("pwm_channels", {1, 0});
    auto dir_gpios_i64 = this->declare_parameter<std::vector<int64_t>>("dir_gpios", {19, 5});

    pwm_channels_.assign(pwm_channels_i64.begin(), pwm_channels_i64.end());
    dir_gpios_.assign(dir_gpios_i64.begin(), dir_gpios_i64.end());

    dir_active_high_ = this->declare_parameter<std::vector<bool>>("dir_active_high", {true, true});
    period_ns_ = this->declare_parameter<int64_t>("period_ns", 50'000); // 20 kHz
    initial_percent_ = this->declare_parameter<int>("initial_percent", 0);
    brake_on_zero_ = this->declare_parameter<bool>("brake_on_zero", false);
    feedback_period_ms_ = this->declare_parameter<int>("feedback_period_ms", 50); // 20 Hz feedback

    if (pwm_channels_.size() != dir_gpios_.size())
    {
      RCLCPP_FATAL(get_logger(), "pwm_channels and dir_gpios must have same size");
      throw std::runtime_error("parameter size mismatch");
    }

    chip_path_ = "/sys/class/pwm/pwmchip" + std::to_string(pwmchip_index_);

    // open chosen chip
    gpio_chip_ = gpiod_chip_open_by_name(gpiochip_name_.c_str());
    if (!gpio_chip_)
    {
      RCLCPP_FATAL(get_logger(), "Failed to open %s (permission or wrong chip?)", gpiochip_name_.c_str());
      throw std::runtime_error("gpiod open failed");
    }

    dir_lines_.resize(dir_gpios_.size(), nullptr);

    for (size_t i = 0; i < dir_gpios_.size(); ++i)
    {
      int gpio = dir_gpios_[i];
      dir_lines_[i] = gpiod_chip_get_line(gpio_chip_, gpio);
      if (!dir_lines_[i])
      {
        RCLCPP_FATAL(get_logger(), "Failed to get GPIO line %d: %s", gpio, std::strerror(errno));
        throw std::runtime_error("gpiod get line failed");
      }
      int rv = gpiod_line_request_output(dir_lines_[i], "transformer_hw_actuators", 0);
      if (rv < 0)
      {
        int first_errno = errno;
        if (first_errno == EBUSY)
        {
          RCLCPP_WARN(get_logger(), "GPIO %d busy on first request (EBUSY); retrying after 150ms", gpio);
          rclcpp::sleep_for(150ms);
          rv = gpiod_line_request_output(dir_lines_[i], "transformer_hw_actuators", 0);
        }
        if (rv < 0)
        {
          RCLCPP_FATAL(get_logger(), "Failed to request output for GPIO %d errno=%d (%s)", gpio, errno,
                       std::strerror(errno));
          throw std::runtime_error("gpiod request failed");
        }
        else if (first_errno == EBUSY)
        {
          RCLCPP_INFO(get_logger(), "GPIO %d request succeeded on retry", gpio);
        }
      }
    }

    // Configure STBY and MODE lines and set high
    if (stby_gpio_ >= 0)
    {
      stby_line_ = gpiod_chip_get_line(gpio_chip_, stby_gpio_);
      if (!stby_line_)
        throw std::runtime_error("gpiod get line failed for STBY");
      if (gpiod_line_request_output(stby_line_, "transformer_hw_actuators", 1) < 0)
        throw std::runtime_error("gpiod request failed for STBY");
    }
    if (mode_gpio_ >= 0)
    {
      mode_line_ = gpiod_chip_get_line(gpio_chip_, mode_gpio_);
      if (!mode_line_)
        throw std::runtime_error("gpiod get line failed for MODE");
      if (gpiod_line_request_output(mode_line_, "transformer_hw_actuators", 1) < 0)
        throw std::runtime_error("gpiod request failed for MODE");
    }

    // Initialize each PWM channel
    for (int ch : pwm_channels_)
    {
      std::string err;
      if (!exportChannel(ch, err))
      {
        RCLCPP_ERROR(get_logger(), "Failed exporting PWM channel %d: %s", ch, err.c_str());
      }
      if (!ensurePeriod(ch, err))
      {
        RCLCPP_ERROR(get_logger(), "Failed setting period for channel %d: %s", ch, err.c_str());
      }
      if (!setDutyPercent(ch, std::abs(initial_percent_), err))
      {
        RCLCPP_ERROR(get_logger(), "Failed setting initial duty for channel %d: %s", ch, err.c_str());
      }
      if (!enableChannel(ch, true, err))
      {
        RCLCPP_ERROR(get_logger(), "Failed enabling channel %d: %s", ch, err.c_str());
      }
    }

    // Set initial directions
    for (size_t i = 0; i < dir_lines_.size(); ++i)
    {
      std::string err;
      bool fwd = initial_percent_ >= 0;
      if (!setDirection(i, fwd, err))
      {
        RCLCPP_ERROR(get_logger(), "Failed to set initial direction for actuator %zu: %s", i, err.c_str());
      }
    }

    // Create action server
    action_server_ = rclcpp_action::create_server<MoveActuator>(
        this,
        "move_actuator",
        std::bind(&ActuatorNode::handleGoal, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&ActuatorNode::handleCancel, this, std::placeholders::_1),
        std::bind(&ActuatorNode::handleAccepted, this, std::placeholders::_1));

    RCLCPP_INFO(get_logger(), "ActuatorNode ready for DC motors: pwmchip=%d period=%ldns", pwmchip_index_, (long)period_ns_);
  }

  ActuatorNode::~ActuatorNode()
  {
    // release gpios gracefully
    for (auto *line : dir_lines_)
    {
      if (line)
        gpiod_line_release(line);
    }
    if (stby_line_)
      gpiod_line_release(stby_line_);
    if (mode_line_)
      gpiod_line_release(mode_line_);
    if (gpio_chip_)
      gpiod_chip_close(gpio_chip_);
  }

  // ===== Filesystem helpers =====

  bool ActuatorNode::pathExists(const std::string &path)
  {
    std::error_code ec;
    return fs::exists(path, ec);
  }

  bool ActuatorNode::writeFile(const std::string &path, const std::string &value, std::string &err)
  {
    std::ofstream f(path);
    if (!f.is_open())
    {
      err = "open failed";
      return false;
    }
    f << value;
    if (!f)
    {
      err = "write failed";
      return false;
    }
    return true;
  }

  std::string ActuatorNode::chPath(int channel, const std::string &leaf) const
  {
    std::ostringstream ss;
    ss << "/pwm" << channel << "/" << leaf;
    return ss.str();
  }

  bool ActuatorNode::exportChannel(int channel, std::string &err)
  {
    auto pwm_path = chip_path_ + "/pwm" + std::to_string(channel);
    if (!pathExists(pwm_path))
    {
      auto export_path = chip_path_ + "/export";
      if (!writeFile(export_path, std::to_string(channel), err))
        return false;
      rclcpp::sleep_for(50ms);
    }
    return true;
  }

  bool ActuatorNode::ensurePeriod(int channel, std::string &err)
  {
    auto period_path = chip_path_ + chPath(channel, "period");
    return writeFile(period_path, std::to_string(period_ns_), err);
  }

  bool ActuatorNode::enableChannel(int channel, bool enable, std::string &err)
  {
    auto enable_path = chip_path_ + chPath(channel, "enable");
    return writeFile(enable_path, enable ? "1" : "0", err);
  }

  bool ActuatorNode::setDutyPercent(int channel, int percent, std::string &err)
  {
    if (percent < 0)
      percent = 0;
    if (percent > 100)
      percent = 100;
    int64_t duty_ns = (period_ns_ * static_cast<int64_t>(percent)) / 100;
    auto duty_path = chip_path_ + chPath(channel, "duty_cycle");
    return writeFile(duty_path, std::to_string(duty_ns), err);
  }

  bool ActuatorNode::setDirection(size_t actuator_idx, bool forward, std::string &err)
  {
    if (actuator_idx >= dir_lines_.size())
    {
      err = "bad actuator index";
      return false;
    }
    bool active_high = dir_active_high_.at(actuator_idx);
    int level = forward ? 1 : 0;
    if (!active_high)
      level = level ? 0 : 1;
    int rv = gpiod_line_set_value(dir_lines_[actuator_idx], level);
    if (rv < 0)
    {
      err = std::string("gpiod_line_set_value failed: ") + std::strerror(errno);
      return false;
    }
    return true;
  }

  // ===== Action callbacks =====

  rclcpp_action::GoalResponse ActuatorNode::handleGoal(const rclcpp_action::GoalUUID & /*uuid*/,
                                                       std::shared_ptr<const MoveActuator::Goal> goal)
  {
    auto now = std::chrono::steady_clock::now();
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    // Log full goal detail (first few elements if large)
    std::ostringstream detail;
    detail << "actuators=" << goal->actuators.size() << " [";
    for (size_t i = 0; i < goal->actuators.size(); ++i)
    {
      if (i)
        detail << ',';
      detail << goal->actuators[i];
    }
    detail << "] speeds=[";
    for (size_t i = 0; i < goal->speed_percents.size(); ++i)
    {
      if (i)
        detail << ',';
      detail << goal->speed_percents[i];
    }
    detail << "] durations=[";
    for (size_t i = 0; i < goal->duration_ms.size(); ++i)
    {
      if (i)
        detail << ',';
      detail << goal->duration_ms[i];
    }
    detail << "]";
    RCLCPP_INFO(get_logger(), "[T%lld] handleGoal: %s", static_cast<long long>(now_ms), detail.str().c_str());

    size_t n = goal->actuators.size();
    if (n == 0)
      return rclcpp_action::GoalResponse::REJECT;
    if (goal->speed_percents.size() != n)
    {
      RCLCPP_WARN(get_logger(), "Rejecting goal: speed_percents size mismatch");
      return rclcpp_action::GoalResponse::REJECT;
    }
    if (!(goal->duration_ms.size() == 0 || goal->duration_ms.size() == 1 || goal->duration_ms.size() == n))
    {
      RCLCPP_WARN(get_logger(), "Rejecting goal: duration_ms must be length 0,1 or match actuators size");
      return rclcpp_action::GoalResponse::REJECT;
    }
    // Check uniqueness and bounds
    std::vector<int32_t> seen;
    seen.reserve(n);
    for (size_t i = 0; i < n; ++i)
    {
      int a = goal->actuators[i];
      if (a < 0 || a >= static_cast<int>(pwm_channels_.size()))
      {
        RCLCPP_WARN(get_logger(), "Rejecting goal: invalid actuator index %d", a);
        return rclcpp_action::GoalResponse::REJECT;
      }
      if (std::find(seen.begin(), seen.end(), a) != seen.end())
      {
        RCLCPP_WARN(get_logger(), "Rejecting goal: duplicate actuator index %d", a);
        return rclcpp_action::GoalResponse::REJECT;
      }
      seen.push_back(a);
    }
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }

  rclcpp_action::CancelResponse ActuatorNode::handleCancel(const std::shared_ptr<GoalHandleMove> /*goal_handle*/)
  {
    return rclcpp_action::CancelResponse::ACCEPT;
  }

  void ActuatorNode::handleAccepted(const std::shared_ptr<GoalHandleMove> goal_handle)
  {
    auto now = std::chrono::steady_clock::now();
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    RCLCPP_INFO(get_logger(), "[T%lld] handleAccepted: spinning up execute thread", static_cast<long long>(now_ms));
    {
      std::lock_guard<std::mutex> lk(active_goal_mutex_);
      active_goal_ = goal_handle;
    }
    std::thread t{std::bind(&ActuatorNode::execute, this, goal_handle)};
    {
      std::lock_guard<std::mutex> lk(threads_mutex_);
      worker_threads_.push_back(std::move(t));
    }
  }

  void ActuatorNode::execute(const std::shared_ptr<GoalHandleMove> goal_handle)
  {
    if (shutting_down_)
    {
      auto res = std::make_shared<MoveActuator::Result>();
      res->success = false;
      res->message = "Shutting down";
      goal_handle->abort(res);
      // Clear active goal if this was it
      {
        std::lock_guard<std::mutex> lk(active_goal_mutex_);
        if (active_goal_.get() == goal_handle.get())
        {
          active_goal_.reset();
        }
      }
      return;
    }
    auto t_exec_start = std::chrono::steady_clock::now();
    auto t_exec_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t_exec_start.time_since_epoch()).count();
    RCLCPP_INFO(get_logger(), "[T%lld] execute: begin", static_cast<long long>(t_exec_ms));

    const auto goal = goal_handle->get_goal();
    auto result = std::make_shared<MoveActuator::Result>();
    auto feedback = std::make_shared<MoveActuator::Feedback>();
    size_t n = goal->actuators.size();
    feedback->current_speed_percents.resize(n);
    feedback->elapsed_ms.resize(n);
    feedback->remaining_ms.resize(n);

    // Normalize durations array
    std::vector<int> durations(n, 0);
    if (goal->duration_ms.size() == n)
    {
      for (size_t i = 0; i < n; ++i)
        durations[i] = static_cast<int>(goal->duration_ms[i]);
    }
    else if (goal->duration_ms.size() == 1)
    {
      std::fill(durations.begin(), durations.end(), static_cast<int>(goal->duration_ms[0]));
    } // else leave zeros (immediate)

    // Apply speeds with detailed logging
    std::string err;
    std::vector<int> applied_speeds(n, 0);
    std::vector<char> applied_dir(n, 'F');
    for (size_t i = 0; i < n; ++i)
    {
      int a = goal->actuators[i];
      int raw = goal->speed_percents[i];
      int spd = std::clamp(raw, -100, 100);
      bool fwd = spd >= 0;
      if (!setDirection(a, fwd, err))
      {
        result->success = false;
        result->message = std::string("setDirection failed actuator ") + std::to_string(a) + ": " + err;
        goal_handle->abort(result);
        return;
      }
      if (!setDutyPercent(pwm_channels_[a], std::abs(spd), err))
      {
        result->success = false;
        result->message = std::string("setDutyPercent failed actuator ") + std::to_string(a) + ": " + err;
        goal_handle->abort(result);
        return;
      }
      applied_speeds[i] = spd;
      applied_dir[i] = fwd ? 'F' : 'R';
      feedback->current_speed_percents[i] = spd;
      feedback->elapsed_ms[i] = 0;
      feedback->remaining_ms[i] = std::max(0, durations[i]);
    }
    // Build one structured log line
    {
      std::ostringstream ss;
      ss << "execute setup: actuators=[";
      for (size_t i = 0; i < n; ++i)
      {
        if (i)
          ss << ',';
        ss << goal->actuators[i];
      }
      ss << "] speeds=[";
      for (size_t i = 0; i < n; ++i)
      {
        if (i)
          ss << ',';
        ss << applied_speeds[i];
      }
      ss << "] dir=[";
      for (size_t i = 0; i < n; ++i)
      {
        if (i)
          ss << ',';
        ss << applied_dir[i];
      }
      ss << "] durations=[";
      for (size_t i = 0; i < n; ++i)
      {
        if (i)
          ss << ',';
        ss << durations[i];
      }
      ss << "]";
      RCLCPP_INFO(get_logger(), "%s", ss.str().c_str());
    }

    bool any_timed = std::any_of(durations.begin(), durations.end(), [](int d)
                                 { return d > 0; });
    if (!any_timed)
    {
      goal_handle->publish_feedback(feedback);
      result->success = true;
      result->message = "Speeds set (no timing)";
      goal_handle->succeed(result);
      // Clear active goal for untimed immediate success
      {
        std::lock_guard<std::mutex> lk(active_goal_mutex_);
        if (active_goal_.get() == goal_handle.get())
        {
          active_goal_.reset();
        }
      }
      return;
    }

    auto start = std::chrono::steady_clock::now();
    const int period_ms = std::max(1, feedback_period_ms_);
    rclcpp::Rate rate(1000ms / period_ms);

    while (rclcpp::ok())
    {
      if (goal_handle->is_canceling())
      {
        std::ostringstream ss;
        ss << "cancel requested: stopping actuators [";
        for (size_t i = 0; i < n; ++i)
        {
          if (i)
            ss << ',';
          ss << goal->actuators[i];
        }
        ss << "]";
        RCLCPP_INFO(get_logger(), "%s", ss.str().c_str());
        for (size_t i = 0; i < n; ++i)
        {
          (void)setDutyPercent(pwm_channels_[goal->actuators[i]], 0, err);
          feedback->current_speed_percents[i] = 0;
        }
        auto cancel_res = std::make_shared<MoveActuator::Result>();
        cancel_res->success = false;
        cancel_res->message = "Canceled";
        goal_handle->canceled(cancel_res);
        return;
      }

      auto now = std::chrono::steady_clock::now();
      int overall_elapsed = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count());
      bool all_done = true;

      for (size_t i = 0; i < n; ++i)
      {
        int dur = durations[i];
        if (dur > 0)
        {
          int el = std::min(overall_elapsed, dur);
          feedback->elapsed_ms[i] = el;
          feedback->remaining_ms[i] = std::max(0, dur - el);
          if (el < dur)
            all_done = false;
          else
          {
            // stop this actuator once complete (only once)
            if (feedback->current_speed_percents[i] != 0)
            {
              (void)setDutyPercent(pwm_channels_[goal->actuators[i]], 0, err);
              feedback->current_speed_percents[i] = 0;
              RCLCPP_DEBUG(get_logger(), "actuator %d duration complete; duty->0", goal->actuators[i]);
            }
          }
        }
        else
        {
          feedback->elapsed_ms[i] = 0;
          feedback->remaining_ms[i] = 0; // immediate
        }
      }

      goal_handle->publish_feedback(feedback);

      if (all_done)
        break;
      rate.sleep();
    }
    result->success = true;
    result->message = "Completed durations";
    goal_handle->succeed(result);
    // Clear active goal if this is the one
    {
      std::lock_guard<std::mutex> lk(active_goal_mutex_);
      if (active_goal_.get() == goal_handle.get())
      {
        active_goal_.reset();
      }
    }
  }

  void ActuatorNode::begin_shutdown()
  {
    if (shutting_down_.exchange(true))
      return; // already in progress
    RCLCPP_INFO(get_logger(), "Shutdown: initiating actuator safe stop");
    cancel_active_goal_for_shutdown();
    // Set duty to 0 for all PWM channels
    std::string err;
    for (size_t i = 0; i < pwm_channels_.size(); ++i)
    {
      (void)setDutyPercent(pwm_channels_[i], 0, err);
    }
    // Join worker threads
    {
      std::lock_guard<std::mutex> lk(threads_mutex_);
      for (auto &t : worker_threads_)
      {
        if (t.joinable())
          t.join();
      }
      worker_threads_.clear();
    }
    RCLCPP_INFO(get_logger(), "Shutdown: actuator threads joined, duty=0");
    RCLCPP_INFO(get_logger(), "Shutdown: actuator complete");
  }

  void ActuatorNode::cancel_active_goal_for_shutdown()
  {
    std::lock_guard<std::mutex> lk(active_goal_mutex_);
    if (active_goal_ && active_goal_->is_active())
    {
      auto res = std::make_shared<MoveActuator::Result>();
      res->success = false;
      res->message = "Aborted: node shutting down";
      active_goal_->abort(res);
    }
    active_goal_.reset();
  }

} // namespace transformer_hw_actuators

// ---- main ----
int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<transformer_hw_actuators::ActuatorNode>();
  rclcpp::executors::MultiThreadedExecutor exec;
  exec.add_node(node);
  exec.spin();
  rclcpp::shutdown();
  return 0;
}