#include <rclcpp/rclcpp.hpp>
#include <gpiod.h>

#include <atomic>
#include <chrono>
#include <csignal>
#include <thread>
#include <string>
#include <algorithm>
#include <pthread.h>
#include <sys/mman.h>

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
    period_us_(this->declare_parameter<int>("period_us", 20000))   // 50Hz
  {
    // Timing control options (optional)
    use_realtime_ = this->declare_parameter<bool>("use_realtime", false);
    rt_priority_ = this->declare_parameter<int>("rt_priority", 80);
    cpu_affinity_ = this->declare_parameter<int>("cpu_affinity", -1); // -1 = no pinning
    tail_spin_us_ = this->declare_parameter<int>("tail_spin_us", 100); // busy spin tail duration
    // start centered (declare once)
      min_us_global_ = this->declare_parameter<int>("min_us", 1350);
      max_us_global_ = this->declare_parameter<int>("max_us", 2500);
      min_us_servo_[0] = this->declare_parameter<int>("min_us_servo0", min_us_global_);
      min_us_servo_[1] = this->declare_parameter<int>("min_us_servo1", min_us_global_);
      max_us_servo_[0] = this->declare_parameter<int>("max_us_servo0", max_us_global_);
      max_us_servo_[1] = this->declare_parameter<int>("max_us_servo1", max_us_global_);
    {
      int initial_us = this->declare_parameter<int>("initial_us", 1500);
        pulse_us_[0].store(clampPulse(0, initial_us));
        pulse_us_[1].store(clampPulse(1, initial_us));
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
    int us = clampPulse(idx, req->pulse_us);
    pulse_us_[idx].store(us);
    res->success = true;
    res->message = "updated";
  }

  void pwmLoop() {
    // Optional: upgrade this thread to RT and pin to a CPU to reduce jitter
    if (use_realtime_) {
      // Best-effort: ignore errors, as these depend on privileges
      mlockall(MCL_CURRENT | MCL_FUTURE);
      struct sched_param sp;
      sp.sched_priority = std::max(1, std::min(rt_priority_, 99));
      pthread_setschedparam(pthread_self(), SCHED_FIFO, &sp);
      if (cpu_affinity_ >= 0) {
        cpu_set_t set;
        CPU_ZERO(&set);
        CPU_SET(cpu_affinity_, &set);
        pthread_setaffinity_np(pthread_self(), sizeof(set), &set);
      }
    }

    while (g_running.load()) {
      const int high0 = clampPulse(0, pulse_us_[0].load());
      const int high1 = clampPulse(1, pulse_us_[1].load());
      const int high = std::min(high0, high1);
      const int low = period_us_ - std::max(high0, high1);
      const int mid_gap = std::abs(high0 - high1);

      // Start both high
      gpiod_line_set_value(line_[0], 1);
      gpiod_line_set_value(line_[1], 1);
  busySleepMicros(high, tail_spin_us_);

      // Drop the one that needs to go low earlier
      if (high0 < high1) {
        gpiod_line_set_value(line_[0], 0);
      } else if (high1 < high0) {
        gpiod_line_set_value(line_[1], 0);
      } else {
        // equal; drop both and finish cycle
        gpiod_line_set_value(line_[0], 0);
        gpiod_line_set_value(line_[1], 0);
        busySleepMicros(period_us_ - high, tail_spin_us_);
        continue;
      }

      // Wait until the longer one finishes
  busySleepMicros(mid_gap, tail_spin_us_);
      // Now drop the other
      if (high0 < high1) {
        gpiod_line_set_value(line_[1], 0);
      } else {
        gpiod_line_set_value(line_[0], 0);
      }

      // Finish the remainder of the period
      busySleepMicros(low, tail_spin_us_);
    }
  }

  static void busySleepMicros(int us, int tail_us) {
    using clock = std::chrono::steady_clock;
    auto start = clock::now();
    auto target = start + std::chrono::microseconds(us);
    auto sleep_until = target - std::chrono::microseconds(std::max(0, tail_us));
    if (sleep_until > clock::now()) {
      std::this_thread::sleep_until(sleep_until);
    }
    while (clock::now() < target) {}
  }

  int clampPulse(int idx, int us) const {
    int mn = min_us_servo_[idx];
    int mx = max_us_servo_[idx];
    if (mn > mx) std::swap(mn, mx);
    if (us < mn) return mn;
    if (us > mx) return mx;
    return us;
  }

private:
  std::string gpiochip_name_;
  int gpio_servo0_;
  int gpio_servo1_;
  int period_us_;
  bool use_realtime_;
  int rt_priority_;
  int cpu_affinity_;
  int tail_spin_us_;
  int min_us_global_;
  int max_us_global_;
  int min_us_servo_[2];
  int max_us_servo_[2];

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
