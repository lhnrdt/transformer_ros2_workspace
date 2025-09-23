#pragma once
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/vector3.hpp>
#include "transformer_msp_bridge/msp_protocol.hpp"
namespace transformer_msp_bridge {
class AttitudeDecoder {
public:
  explicit AttitudeDecoder(rclcpp::Node &node) : node_(node) {
    pub_ = node_.create_publisher<geometry_msgs::msg::Vector3>("/msp/attitude", 10);
  }
  void decode(const MSPPacket &pkt) {
    if (pkt.payload.size() < 6) return;
    int16_t roll = (int16_t)(pkt.payload[0] | (pkt.payload[1] << 8));
    int16_t pitch = (int16_t)(pkt.payload[2] | (pkt.payload[3] << 8));
    int16_t yaw = (int16_t)(pkt.payload[4] | (pkt.payload[5] << 8));
    geometry_msgs::msg::Vector3 v; v.x = roll / 10.0; v.y = pitch / 10.0; v.z = yaw / 10.0; pub_->publish(v);
  }
private:
  rclcpp::Node &node_;
  rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr pub_;
};
} // namespace transformer_msp_bridge
