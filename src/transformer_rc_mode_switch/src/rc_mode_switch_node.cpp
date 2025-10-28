#include "transformer_rc_mode_switch/rc_mode_switch_node.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <memory>
#include <string>

namespace transformer_rc_mode_switch {

namespace {

/** @brief Name used to register the node with the ROS graph. */
constexpr char kNodeName[] = "rc_mode_switch";

/** @brief Action server name for commanding transformer modes. */
constexpr char kTransformActionName[] = "transform_mode";

/** @brief Default RC channel index assigned to transformer mode switching. */
constexpr int kDefaultChannelIndex = 5;

/** @brief Default PWM center value for the drive mode position. */
constexpr int kDefaultDriveHighCenter = 2000;

/** @brief Default PWM center value for the flight mode position. */
constexpr int kDefaultFlightLowCenter = 1000;

/** @brief Default tolerance around the expected PWM center values. */
constexpr int kDefaultTolerance = 300;

/** @brief Default debounce interval preventing rapid mode toggling. */
constexpr std::chrono::milliseconds kDefaultDebounce{500};

/** @brief Default minimal number of RC channels expected in the message. */
constexpr int kDefaultMinChannelCount = 6;

/** @brief Default topic name publishing raw RC channel data. */
constexpr char kDefaultRcTopic[] = "/msp/rc";

/** @brief Queue depth for the RC subscription to balance latency and reliability. */
constexpr std::size_t kSubscriptionQueueDepth = 10U;

}  // namespace

RcModeSwitchNode::RcModeSwitchNode() : Node(kNodeName) {
  InitializeParameters();
  InitializeActionClient();
  InitializeSubscription();

  RCLCPP_INFO(get_logger(),
              "\033[32m[READY] RC mode switch online | channel_index=%d drive_center=%d flight_center=%d tolerance=%d debounce_ms=%ld\033[0m",
              channel_index_, drive_high_center_, flight_low_center_, tolerance_,
              static_cast<long>(debounce_period_.count()));
}

void RcModeSwitchNode::InitializeParameters() {
  // Load and sanitize the configured channel that carries the mode command.
  const int declared_channel_index = declare_parameter<int>("channel_index", kDefaultChannelIndex);
  channel_index_ = std::max(0, declared_channel_index);

  // Load the expected PWM centers for the physical switch positions.
  drive_high_center_ = declare_parameter<int>("drive_high_center", kDefaultDriveHighCenter);
  flight_low_center_ = declare_parameter<int>("flight_low_center", kDefaultFlightLowCenter);

  // Use an absolute tolerance to accommodate receiver jitter while preventing negative values.
  tolerance_ = declare_parameter<int>("tolerance", kDefaultTolerance);
  if (tolerance_ < 0) {
    RCLCPP_WARN(get_logger(), "Received negative tolerance; using absolute value instead");
    tolerance_ = std::abs(tolerance_);
  }

  // Translate the debounce parameter into a chrono duration, guarding against invalid input.
  const int declared_debounce_ms = declare_parameter<int>("debounce_ms", static_cast<int>(kDefaultDebounce.count()));
  const int sanitized_debounce_ms = std::max(0, declared_debounce_ms);
  debounce_period_ = std::chrono::milliseconds(sanitized_debounce_ms);

  // Determine how many channels must be present before considering a mode command valid.
  const int declared_min_channels = declare_parameter<int>("min_channels", kDefaultMinChannelCount);
  min_publish_channels_ = std::max(channel_index_ + 1, std::max(0, declared_min_channels));

  // Identify which topic supplies the RC signal.
  rc_topic_ = declare_parameter<std::string>("rc_topic", kDefaultRcTopic);
}

void RcModeSwitchNode::InitializeActionClient() {
  // The action client bridges outgoing commands to the transformer controller.
  transform_client_ = rclcpp_action::create_client<TransformMode>(this, kTransformActionName);
}

void RcModeSwitchNode::InitializeSubscription() {
  // Subscribe to RC channel updates with a modest queue size for low-latency behavior.
  auto qos = rclcpp::QoS(rclcpp::KeepLast(kSubscriptionQueueDepth));
  rc_subscription_ = create_subscription<std_msgs::msg::UInt16MultiArray>(
      rc_topic_, qos, [this](const std_msgs::msg::UInt16MultiArray::SharedPtr msg) { OnRcMessage(msg); });
}

void RcModeSwitchNode::OnRcMessage(const std_msgs::msg::UInt16MultiArray::SharedPtr& msg) {
  // Reject null shared pointers defensively; this should not happen but protects against misuse.
  if (!msg) {
    RCLCPP_WARN(get_logger(), "Received null RC message pointer; ignoring");
    return;
  }

  const auto now = std::chrono::steady_clock::now();

  // Ensure the incoming message contains the configured channel before accessing it.
  const auto required_channels = std::max(min_publish_channels_, channel_index_ + 1);
  if (static_cast<int>(msg->data.size()) < required_channels) {
    RCLCPP_DEBUG(get_logger(), "RC message missing expected channels (have=%zu need>=%d)", msg->data.size(),
                 required_channels);
    return;
  }

  const int channel_value = msg->data[static_cast<std::size_t>(channel_index_)];
  const Mode requested_mode = DetermineRequestedMode(channel_value);

  // Abort when the switch remains in the neutral zone to avoid spamming commands.
  if (requested_mode == Mode::kUnknown) {
    return;
  }

  // Avoid repeated goals for the same mode while the switch is stationary.
  if (requested_mode == last_sent_mode_) {
    return;
  }

  // Honor the configured debounce window to filter rapid toggling caused by switch chatter.
  if (!IsDebounced(now)) {
    RCLCPP_DEBUG(get_logger(), "RC command suppressed by debounce window");
    return;
  }

  if (!transform_client_) {
    RCLCPP_ERROR(get_logger(), "Transform action client not initialized; cannot send mode command");
    return;
  }

  if (!transform_client_->action_server_is_ready()) {
    RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 5000, "Transform action server not ready yet");
    return;
  }

  DispatchGoal(requested_mode, channel_value, now);
}

RcModeSwitchNode::Mode RcModeSwitchNode::DetermineRequestedMode(const int channel_value) const {
  // Detect whether the RC input rests near the drive configuration.
  if (std::abs(channel_value - drive_high_center_) <= tolerance_) {
    return Mode::kDrive;
  }

  // Detect whether the RC input rests near the flight configuration.
  if (std::abs(channel_value - flight_low_center_) <= tolerance_) {
    return Mode::kFlight;
  }

  // Any intermediate value is treated as neutral and results in no command.
  return Mode::kUnknown;
}

bool RcModeSwitchNode::IsDebounced(const std::chrono::steady_clock::time_point now) const {
  if (debounce_period_.count() == 0) {
    return true;
  }

  // Permit the first command immediately by treating the epoch timestamp as untouched state.
  if (last_goal_time_.time_since_epoch().count() == 0) {
    return true;
  }

  return (now - last_goal_time_) >= debounce_period_;
}

void RcModeSwitchNode::DispatchGoal(const Mode mode, const int channel_value,
                                    const std::chrono::steady_clock::time_point now) {
  // Populate the goal with the textual mode understood by the controller.
  TransformMode::Goal goal;
  goal.target_mode = ModeToString(mode);

  const int human_channel_number = channel_index_ + 1;
  RCLCPP_INFO(get_logger(), "\033[34m[TRANSITION] Issuing transform goal | mode=%s channel=%d value=%d\033[0m",
              goal.target_mode.c_str(), human_channel_number, channel_value);

  auto goal_future = transform_client_->async_send_goal(goal);
  (void)goal_future;  // The future is intentionally unused; fire-and-forget behavior is sufficient here.

  // Update internal state for the next debounce evaluation.
  last_goal_time_ = now;
  last_sent_mode_ = mode;
}

std::string RcModeSwitchNode::ModeToString(const Mode mode) {
  switch (mode) {
    case Mode::kDrive:
      return "drive";
    case Mode::kFlight:
      return "flight";
    case Mode::kUnknown:
    default:
      break;
  }
  return "unknown";
}

}  // namespace transformer_rc_mode_switch

/**
 * @brief Program entry point that spins the RC mode switch node.
 *
 * @param argc Argument count passed from the console.
 * @param argv Argument vector passed from the console.
 * @return int Zero on normal shutdown, non-zero otherwise.
 */
int main(int argc, char** argv) {
  rclcpp::init(argc, argv);

  auto node = std::make_shared<transformer_rc_mode_switch::RcModeSwitchNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
