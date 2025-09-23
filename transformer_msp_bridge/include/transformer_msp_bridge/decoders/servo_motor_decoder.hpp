#pragma once

#include "transformer_msp_bridge/msp_protocol.hpp"
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joint_state.hpp>

namespace transformer_msp_bridge {

class ServoMotorDecoder {
public:
  explicit ServoMotorDecoder(rclcpp::Node &node) {
    servo_pub_ = node.create_publisher<sensor_msgs::msg::JointState>("/msp/servo", 10);
    motor_pub_ = node.create_publisher<sensor_msgs::msg::JointState>("/msp/motor", 10);
  }
  void decodeServo(const MSPPacket &pkt) {
    size_t n = pkt.payload.size()/2; if(!n) return; sensor_msgs::msg::JointState js; js.position.reserve(n);
    for(size_t i=0;i<n;i++){ uint16_t v = pkt.payload[2*i] | (pkt.payload[2*i+1]<<8); js.position.push_back(static_cast<double>(v)); }
    servo_pub_->publish(js);
  }
  void decodeMotor(const MSPPacket &pkt) {
    size_t n = pkt.payload.size()/2; if(!n) return; sensor_msgs::msg::JointState js; js.velocity.reserve(n);
    for(size_t i=0;i<n;i++){ uint16_t v = pkt.payload[2*i] | (pkt.payload[2*i+1]<<8); js.velocity.push_back(static_cast<double>(v)); }
    motor_pub_->publish(js);
  }
private:
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr servo_pub_;
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr motor_pub_;
};

} // namespace transformer_msp_bridge
