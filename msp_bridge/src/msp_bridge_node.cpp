#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/u_int16_multi_array.hpp>
#include <geometry_msgs/msg/vector3.hpp>

#include "msp_bridge/msp_protocol.hpp"
#include "msp_bridge/serial_port.hpp"

#include <thread>
#include <mutex>
#include <atomic>

using std::placeholders::_1;

namespace msp_bridge {

class MSPBridgeNode : public rclcpp::Node {
public:
  MSPBridgeNode() : Node("msp_bridge") {
    port_ = declare_parameter<std::string>("port", "/dev/ttyAMA0");
    baud_ = declare_parameter<int>("baudrate", 115200);
    timeout_ms_ = declare_parameter<int>("timeout_ms", 50);
    rc_channel_count_ = declare_parameter<int>("rc_channel_count", 8);
    poll_rate_hz_ = declare_parameter<double>("telemetry_poll_rate_hz", 10.0);
    rc_echo_rate_hz_ = declare_parameter<double>("rc_publish_rate_hz", 10.0);

    if (!serial_.open(port_, baud_, timeout_ms_)) {
      RCLCPP_FATAL(get_logger(), "Failed to open serial port %s", port_.c_str());
      throw std::runtime_error("serial open failed");
    }

    parser_ = std::make_unique<MSPParser>([this](const MSPPacket &pkt){ this->handlePacket(pkt); });

    rc_pub_ = create_publisher<std_msgs::msg::UInt16MultiArray>("/msp/rc_out", 10);
    attitude_pub_ = create_publisher<geometry_msgs::msg::Vector3>("/msp/attitude", 10);

    rc_sub_ = create_subscription<std_msgs::msg::UInt16MultiArray>(
      "/msp/rc_override", 10, std::bind(&MSPBridgeNode::rcCallback, this, _1));

    // Timers
    read_timer_ = create_wall_timer(std::chrono::milliseconds(5), std::bind(&MSPBridgeNode::readLoop, this));
    if (rc_echo_rate_hz_ > 0) {
      rc_timer_ = create_wall_timer(std::chrono::milliseconds((int)(1000.0/rc_echo_rate_hz_)), std::bind(&MSPBridgeNode::publishRC, this));
    }
    if (poll_rate_hz_ > 0) {
      poll_timer_ = create_wall_timer(std::chrono::milliseconds((int)(1000.0/poll_rate_hz_)), std::bind(&MSPBridgeNode::pollTelemetry, this));
    }

    current_rc_.assign(rc_channel_count_, 1500);
  }

private:
  void rcCallback(const std_msgs::msg::UInt16MultiArray::SharedPtr msg) {
    size_t n = std::min<size_t>(msg->data.size(), (size_t)rc_channel_count_);
    if (n == 0) return;
    for (size_t i=0;i<n;i++) current_rc_[i] = msg->data[i];
    // Send immediately
  auto pkt = buildPacket(MSP_SET_RAW_RC, current_rc_);
    serial_.writeAll(pkt.data(), pkt.size());
  }

  void publishRC() {
    std_msgs::msg::UInt16MultiArray m;
    m.data = current_rc_;
    rc_pub_->publish(std::move(m));
  }

  void pollTelemetry() {
    // Request attitude
  auto pkt = buildPacketRaw(MSP_ATTITUDE, {});
    serial_.writeAll(pkt.data(), pkt.size());
  }

  void readLoop() {
    uint8_t buf[256];
    int n = serial_.readSome(buf, sizeof(buf));
    if (n > 0) {
      for (int i=0;i<n;i++) parser_->input(buf[i]);
    }
  }

  void handlePacket(const MSPPacket &pkt) {
    if (pkt.cmd == MSP_ATTITUDE) {
      if (pkt.payload.size() >= 6) {
        int16_t roll  = (int16_t)(pkt.payload[0] | (pkt.payload[1]<<8));
        int16_t pitch = (int16_t)(pkt.payload[2] | (pkt.payload[3]<<8));
        int16_t yaw   = (int16_t)(pkt.payload[4] | (pkt.payload[5]<<8));
        geometry_msgs::msg::Vector3 v;
        v.x = roll / 10.0; // typical scaling: 0.1 deg
        v.y = pitch / 10.0;
        v.z = yaw / 10.0;
        attitude_pub_->publish(std::move(v));
      }
    }
  }

  // Params
  std::string port_;
  int baud_{115200};
  int timeout_ms_{50};
  int rc_channel_count_{8};
  double poll_rate_hz_{10.0};
  double rc_echo_rate_hz_{10.0};

  SerialPort serial_;
  std::unique_ptr<MSPParser> parser_;

  std::vector<uint16_t> current_rc_;

  rclcpp::Publisher<std_msgs::msg::UInt16MultiArray>::SharedPtr rc_pub_;
  rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr attitude_pub_;
  rclcpp::Subscription<std_msgs::msg::UInt16MultiArray>::SharedPtr rc_sub_;

  rclcpp::TimerBase::SharedPtr read_timer_;
  rclcpp::TimerBase::SharedPtr rc_timer_;
  rclcpp::TimerBase::SharedPtr poll_timer_;
};

} // namespace msp_bridge

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<msp_bridge::MSPBridgeNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
