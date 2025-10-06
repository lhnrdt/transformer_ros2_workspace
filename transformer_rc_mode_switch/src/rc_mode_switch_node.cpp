#include <algorithm>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <std_msgs/msg/u_int16_multi_array.hpp>
#include <string>
#include <transformer_controller/action/transform_mode.hpp>

class RcModeSwitchNode : public rclcpp::Node {
 public:
  using TransformMode = transformer_controller::action::TransformMode;
  using TransformHandle = rclcpp_action::ClientGoalHandle<TransformMode>;

  RcModeSwitchNode() : Node("rc_mode_switch") {
    channel_index_ = declare_parameter<int>("channel_index", 5);  // CH6 -> index 5 (0-based)
    drive_high_ = declare_parameter<int>("drive_high_center", 2000);
    flight_low_ = declare_parameter<int>("flight_low_center", 1000);
    tolerance_ = declare_parameter<int>("tolerance", 300);
    debounce_ms_ = declare_parameter<int>("debounce_ms", 500);
    min_publish_channels_ = declare_parameter<int>("min_channels", 6);
    rc_topic_ = declare_parameter<std::string>("rc_topic", "/msp/rc_in");

    transform_client_ = rclcpp_action::create_client<TransformMode>(this, "transform_mode");

    rc_sub_ = create_subscription<std_msgs::msg::UInt16MultiArray>(
        rc_topic_, 10, std::bind(&RcModeSwitchNode::rcCallback, this, std::placeholders::_1));

    RCLCPP_INFO(get_logger(), "RC Mode Switch node started. CH index=%d drive_center=%d flight_center=%d tol=%d",
                channel_index_, drive_high_, flight_low_, tolerance_);
  }

 private:
  void rcCallback(const std_msgs::msg::UInt16MultiArray::SharedPtr msg) {
    if ((int)msg->data.size() < std::max(min_publish_channels_, channel_index_ + 1)) {
      return;  // not enough channels yet
    }
    int value = msg->data[channel_index_];
    auto now = std::chrono::steady_clock::now();

    // Determine desired mode
    std::string desired;
    if (std::abs(value - drive_high_) <= tolerance_) {
      desired = "drive";
    } else if (std::abs(value - flight_low_) <= tolerance_) {
      desired = "flight";
    } else {
      // in-between or invalid; do nothing
      return;
    }

    if (desired == last_sent_mode_) {
      // Already commanded
      return;
    }

    // Debounce: ensure time since last send
    auto ms_since = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_goal_time_).count();
    if (ms_since < debounce_ms_) {
      return;
    }

    if (!transform_client_->action_server_is_ready()) {
      RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 5000, "Transform action server not ready yet");
      return;
    }

    TransformMode::Goal goal;
    goal.target_mode = desired;
    RCLCPP_INFO(get_logger(), "Sending transform goal to mode=%s (rc ch%d value=%d)", desired.c_str(),
                channel_index_ + 1, value);
    auto send_future = transform_client_->async_send_goal(goal);
    last_goal_time_ = now;
    last_sent_mode_ = desired;
  }

  // Parameters
  int channel_index_;
  int drive_high_;
  int flight_low_;
  int tolerance_;
  int debounce_ms_;
  int min_publish_channels_;
  std::string rc_topic_;

  // State
  std::string last_sent_mode_;
  std::chrono::steady_clock::time_point last_goal_time_ = std::chrono::steady_clock::now() - std::chrono::seconds(10);

  // ROS interfacing
  rclcpp_action::Client<TransformMode>::SharedPtr transform_client_;
  rclcpp::Subscription<std_msgs::msg::UInt16MultiArray>::SharedPtr rc_sub_;
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<RcModeSwitchNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
