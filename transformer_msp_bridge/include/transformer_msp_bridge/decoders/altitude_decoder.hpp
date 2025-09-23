#pragma once

#include "transformer_msp_bridge/msp_protocol.hpp"
#include "transformer_msp_bridge/decoder_base.hpp"
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>

namespace transformer_msp_bridge {

class AltitudeDecoder : public IMspDecoder {
public:
  explicit AltitudeDecoder(rclcpp::Node &node) {
    alt_pub_ = node.create_publisher<std_msgs::msg::Float32>("/msp/altitude", 10);
    vs_pub_ = node.create_publisher<geometry_msgs::msg::TwistStamped>("/msp/vertical_speed", 10);
  }

  void decodeAltitude(const MSPPacket &pkt) {
    if (pkt.payload.size() < 6) return;
    int32_t alt_cm = (int32_t)(pkt.payload[0] | (pkt.payload[1]<<8) | (pkt.payload[2]<<16) | (pkt.payload[3]<<24));
    int16_t vs_cms = (int16_t)(pkt.payload[4] | (pkt.payload[5]<<8));
    std_msgs::msg::Float32 alt; alt.data = alt_cm / 100.0f; alt_pub_->publish(alt);
    geometry_msgs::msg::TwistStamped vs; vs.twist.linear.z = vs_cms / 100.0; vs_pub_->publish(vs);
  }

  // IMspDecoder implementation
  bool matches(uint16_t command_id) const override { return command_id == MSP_ALTITUDE; }
  void decode(const MSPPacket &pkt) override { decodeAltitude(pkt); }
  std::string name() const override { return "altitude"; }

private:
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr alt_pub_;
  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr vs_pub_;
};

} // namespace transformer_msp_bridge
