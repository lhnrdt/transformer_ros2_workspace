#include <rclcpp/rclcpp.hpp>
#include <gpiod.h>

#include <atomic>
#include <chrono>
#include <csignal>
#include <thread>
#include <string>
#include <algorithm>

using namespace std::chrono_literals;

static std::atomic<bool> g_running{true};

// Generated header after rosidl: transformer_hw_servos/srv/set_servo_pulse.hpp
#include "transformer_hw_servos/srv/set_servo_pulse.hpp"

class DualServoNode : public rclcpp::Node {
public:
  using SetServoPulse = transformer_hw_servos::srv::SetServoPulse;

  DualServoNode()
  : Node("transformer_hw_servos"),
    gpiochip_name_(this->declare_parameter<std::string>("gpiochip_name", "gpiochip4")),
    gpio_servo0_(this->declare_parameter<int>("gpio_servo0", 6)),   // GPIO6
    gpio_servo1_(this->declare_parameter<int>("gpio_servo1", 27)),  // GPIO27
    period_us_(this->declare_parameter<int>("period_us", 20000)),   // 50Hz
    min_us_(this->declare_parameter<int>("min_us", 500)),
    max_us_(this->declare_parameter<int>("max_us", 2500))
  {
    // start centered (declare once)
    {
      int initial_us = this->declare_parameter<int>("initial_us", 1500);
      pulse_us_[0].store(initial_us);
      pulse_us_[1].store(initial_us);
    }

    // Open chip and request lines
    chip_ = gpiod_chip_open_by_name(gpiochip_name_.c_str());
    if (!chip_) {
      RCLCPP_FATAL(get_logger(), "Failed to open %s (permissions?)", gpiochip_name_.c_str());
      throw std::runtime_error("gpiod open failed");
    }
    line_[0] = gpiod_chip_get_line(chip_, gpio_servo0_);
    line_[1] = gpiod_chip_get_line(chip_, gpio_servo1_);
    if (!line_[0] || !line_[1]) {
      if (line_[0]) gpiod_line_release(line_[0]);
      if (line_[1]) gpiod_line_release(line_[1]);
      gpiod_chip_close(chip_);
      throw std::runtime_error("Failed to get GPIO lines for servos");
    }
    if (gpiod_line_request_output(line_[0], "transformer_hw_servos_0", 0) < 0 ||
        gpiod_line_request_output(line_[1], "transformer_hw_servos_1", 0) < 0) {
      if (line_[0]) gpiod_line_release(line_[0]);
      if (line_[1]) gpiod_line_release(line_[1]);
      gpiod_chip_close(chip_);
      throw std::runtime_error("Failed to request GPIO lines as outputs");
    }

    // Service for setting pulse widths
    srv_ = this->create_service<SetServoPulse>(
      "set_servo_pulse",
      std::bind(&DualServoNode::handleSetPulse, this,
                std::placeholders::_1, std::placeholders::_2));

    // Spin PWM thread
    pwm_thread_ = std::thread(&DualServoNode::pwmLoop, this);

    RCLCPP_INFO(get_logger(), "Servos ready on GPIO%d and GPIO%d via %s @ 50Hz",
                gpio_servo0_, gpio_servo1_, gpiochip_name_.c_str());
  }

  ~DualServoNode() override {
    g_running = false;
    if (pwm_thread_.joinable()) pwm_thread_.join();
    for (auto &l : line_) {
      if (l) { gpiod_line_set_value(l, 0); gpiod_line_release(l); }
    }
    if (chip_) gpiod_chip_close(chip_);
  }

private:
  void handleSetPulse(const SetServoPulse::Request::SharedPtr req,
                      SetServoPulse::Response::SharedPtr res) {
    int idx = req->servo_index;
    if (idx < 0 || idx > 1) {
      res->success = false;
      res->message = "servo_index must be 0 or 1";
      return;
    }
    int us = std::clamp<int>(req->pulse_us, min_us_, max_us_);
    pulse_us_[idx].store(us);
    res->success = true;
    res->message = "updated";
  }

  void pwmLoop() {
    while (g_running.load()) {
      const int high0 = clampPulse(pulse_us_[0].load());
      const int high1 = clampPulse(pulse_us_[1].load());
      const int high = std::min(high0, high1);
      const int low = period_us_ - std::max(high0, high1);
      const int mid_gap = std::abs(high0 - high1);

      // Start both high
      gpiod_line_set_value(line_[0], 1);
      gpiod_line_set_value(line_[1], 1);
      busySleepMicros(high);

      // Drop the one that needs to go low earlier
      if (high0 < high1) {
        gpiod_line_set_value(line_[0], 0);
      } else if (high1 < high0) {
        gpiod_line_set_value(line_[1], 0);
      } else {
        // equal; drop both and finish cycle
        gpiod_line_set_value(line_[0], 0);
        gpiod_line_set_value(line_[1], 0);
        busySleepMicros(period_us_ - high);
        continue;
      }

      // Wait until the longer one finishes
      busySleepMicros(mid_gap);
      // Now drop the other
      if (high0 < high1) {
        gpiod_line_set_value(line_[1], 0);
      } else {
        gpiod_line_set_value(line_[0], 0);
      }

      // Finish the remainder of the period
      busySleepMicros(low);
    }
  }

  static void busySleepMicros(int us) {
    using clock = std::chrono::steady_clock;
    auto start = clock::now();
    auto target = start + std::chrono::microseconds(us);
    auto sleep_until = target - std::chrono::microseconds(200);
    if (sleep_until > clock::now()) {
      std::this_thread::sleep_until(sleep_until);
    }
    while (clock::now() < target) {}
  }

  int clampPulse(int us) const {
    if (us < min_us_) return min_us_;
    if (us > max_us_) return max_us_;
    return us;
  }

private:
  std::string gpiochip_name_;
  int gpio_servo0_;
  int gpio_servo1_;
  int period_us_;
  int min_us_;
  int max_us_;

  std::atomic<int> pulse_us_[2];

  gpiod_chip* chip_ {nullptr};
  gpiod_line* line_[2] {nullptr, nullptr};

  std::thread pwm_thread_;
  rclcpp::Service<SetServoPulse>::SharedPtr srv_;
};

static void sigintHandler(int) {
  g_running = false;
}

int main(int argc, char** argv) {
  std::signal(SIGINT, sigintHandler);
  rclcpp::init(argc, argv);
  try {
    auto node = std::make_shared<DualServoNode>();
    rclcpp::spin(node);
  } catch (const std::exception &e) {
    RCLCPP_FATAL(rclcpp::get_logger("transformer_hw_servos"), "Fatal: %s", e.what());
  }
  rclcpp::shutdown();
  return 0;
}
