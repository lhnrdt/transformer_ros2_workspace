#include <rclcpp/rclcpp.hpp>
#include <gpiod.h>
#include <atomic>
#include <chrono>
#include <csignal>
#include <cstdio>
#include <fcntl.h>
#include <termios.h>
#include <thread>
#include <unistd.h>

using namespace std::chrono_literals;

static std::atomic<bool> g_running{true};

class ServoPwmNode : public rclcpp::Node
{
public:
  ServoPwmNode()
      : Node("servo_pwm_dual"),
        chip_name_("/dev/gpiochip4"),
        gpio_line1_(6),    // BCM6 (header pin 31)
        gpio_line2_(27),   // BCM27 (header pin 13)
        period_us_(20000), // 50 Hz -> 20 ms period
        pulse_us_(1500),   // start centered
        min_us_(1350),
        max_us_(2500)
  {
    // Open GPIO chip and request both lines as outputs
    chip_ = gpiod_chip_open(chip_name_.c_str());
    if (!chip_)
    {
      throw std::runtime_error("Failed to open " + chip_name_);
    }
    
    line1_ = gpiod_chip_get_line(chip_, gpio_line1_);
    if (!line1_)
    {
      gpiod_chip_close(chip_);
      throw std::runtime_error("Failed to get line " + std::to_string(gpio_line1_));
    }
    
    line2_ = gpiod_chip_get_line(chip_, gpio_line2_);
    if (!line2_)
    {
      gpiod_chip_close(chip_);
      throw std::runtime_error("Failed to get line " + std::to_string(gpio_line2_));
    }
    
    if (gpiod_line_request_output(line1_, "servo_pwm_node_gpio6", 0) < 0)
    {
      gpiod_chip_close(chip_);
      throw std::runtime_error("Failed to request GPIO6 as output");
    }
    
    if (gpiod_line_request_output(line2_, "servo_pwm_node_gpio27", 0) < 0)
    {
      gpiod_line_release(line1_);
      gpiod_chip_close(chip_);
      throw std::runtime_error("Failed to request GPIO27 as output");
    }

    RCLCPP_INFO(get_logger(),
                "Servo PWM on GPIO%d and GPIO%d via %s @ 50 Hz. Start pulse: %d us",
                gpio_line1_, gpio_line2_, chip_name_.c_str(), pulse_us_.load());

    // Start worker threads
    pwm_thread_ = std::thread(&ServoPwmNode::pwmLoop, this);
    input_thread_ = std::thread(&ServoPwmNode::keyboardLoop, this);

    // Timer just to periodically log the current pulse width
    status_timer_ = this->create_wall_timer(
        1s, [this]()
        { RCLCPP_INFO_THROTTLE(
              get_logger(),
              *this->get_clock(),
              2000, // milliseconds
              "Pulse width: %d us",
              pulse_us_.load()); });
  }

  ~ServoPwmNode() override
  {
    g_running = false;
    if (input_thread_.joinable())
      input_thread_.join();
    if (pwm_thread_.joinable())
      pwm_thread_.join();
    if (line1_)
    {
      gpiod_line_set_value(line1_, 0);
      gpiod_line_release(line1_);
    }
    if (line2_)
    {
      gpiod_line_set_value(line2_, 0);
      gpiod_line_release(line2_);
    }
    if (chip_)
      gpiod_chip_close(chip_);
    RCLCPP_INFO(get_logger(), "Shut down cleanly.");
  }

private:
  void pwmLoop()
  {
    // Simple software PWM: set high for pulse_us_, low for (period_us_ - pulse_us_)
    while (g_running.load())
    {
      int high = pulse_us_.load();
      if (high < min_us_)
        high = min_us_;
      if (high > max_us_)
        high = max_us_;
      int low = period_us_ - high;

      // Set both GPIOs high simultaneously
      gpiod_line_set_value(line1_, 1);
      gpiod_line_set_value(line2_, 1);
      busySleepMicros(high);
      
      // Set both GPIOs low simultaneously
      gpiod_line_set_value(line1_, 0);
      gpiod_line_set_value(line2_, 0);
      busySleepMicros(low);
    }
  }

  // Busy-sleep hybrid: sleep_for for most of it, then short spin for last ~50us
  static void busySleepMicros(int us)
  {
    using clock = std::chrono::steady_clock;
    auto start = clock::now();
    auto target = start + std::chrono::microseconds(us);
    // Sleep for the bulk
    auto sleep_until = target - std::chrono::microseconds(200);
    if (sleep_until > clock::now())
    {
      std::this_thread::sleep_until(sleep_until);
    }
    // Short spin to tighten tail
    while (clock::now() < target)
    {
      // spin
    }
  }

  // Non-blocking keyboard input on stdin
  void keyboardLoop()
  {
    setTerminalRaw(true);
    printHelp();

    while (g_running.load())
    {
      int c = readCharNonBlocking();
      if (c < 0)
      {
        std::this_thread::sleep_for(10ms);
        continue;
      }
      if (c == 'q' || c == 'Q')
      {
        RCLCPP_INFO(get_logger(), "Quit requested.");
        g_running = false;
        break;
      }
      else if (c == '+' || c == '=')
      {
        adjustPulse(+50); // +50 us
      }
      else if (c == '-')
      {
        adjustPulse(-50); // -50 us
      }
      else if (c == ']')
      {
        adjustPulse(+10); // fine +10 us
      }
      else if (c == '[')
      {
        adjustPulse(-10); // fine -10 us
      }
      else if (c == 'r' || c == 'R')
      {
        pulse_us_.store(1500);
        RCLCPP_INFO(get_logger(), "Reset to 1500 us");
      }
      else if (c == 'h' || c == 'H')
      {
        printHelp();
      }
    }

    setTerminalRaw(false);
  }

  void adjustPulse(int delta_us)
  {
    int value = pulse_us_.load() + delta_us;
    if (value < min_us_)
      value = min_us_;
    if (value > max_us_)
      value = max_us_;
    pulse_us_.store(value);
    RCLCPP_INFO(get_logger(), "Pulse width: %d us", value);
  }

  void printHelp()
  {
    RCLCPP_INFO(get_logger(), R"HELP(

Controls:
  '+'  : +50 us
  '-'  : -50 us
  ']'  : +10 us (fine)
  '['  : -10 us (fine)
  'r'  : reset to 1500 us
  'h'  : help
  'q'  : quit

)HELP");
  }

  static int readCharNonBlocking()
  {
    unsigned char c;
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    int n = read(STDIN_FILENO, &c, 1);
    return (n == 1) ? c : -1;
  }

  static void setTerminalRaw(bool enable)
  {
    static struct termios oldt;
    static bool saved = false;

    if (enable)
    {
      struct termios newt;
      if (!saved)
      {
        tcgetattr(STDIN_FILENO, &oldt);
        saved = true;
      }
      newt = oldt;

      // Turn off line buffering + echo, BUT keep signals/output processing
      newt.c_lflag &= ~(ICANON | ECHO); // non-canonical, no echo
      newt.c_lflag |= ISIG;             // keep Ctrl-C/Z (SIGINT/SIGTSTP)
      // Nonblocking read behavior parameters
      newt.c_cc[VMIN] = 0;
      newt.c_cc[VTIME] = 0;

      tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
    else if (saved)
    {
      tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
  }

private:
  std::string chip_name_;
  int gpio_line1_;
  int gpio_line2_;
  int period_us_;
  std::atomic<int> pulse_us_;
  const int min_us_;
  const int max_us_;

  gpiod_chip *chip_{nullptr};
  gpiod_line *line1_{nullptr};
  gpiod_line *line2_{nullptr};

  std::thread pwm_thread_;
  std::thread input_thread_;
  rclcpp::TimerBase::SharedPtr status_timer_;
};

// Handle Ctrl-C cleanly
void sigintHandler(int)
{
  g_running = false;
}

int main(int argc, char *argv[])
{
  signal(SIGINT, sigintHandler);
  rclcpp::init(argc, argv);
  try
  {
    auto node = std::make_shared<ServoPwmNode>();
    rclcpp::spin(node);
  }
  catch (const std::exception &e)
  {
    RCLCPP_ERROR(rclcpp::get_logger("software_pwm"),
                 "Fatal error: %s", e.what());
  }
  rclcpp::shutdown();
  return 0;
}