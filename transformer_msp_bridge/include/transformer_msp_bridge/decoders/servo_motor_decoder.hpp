#pragma once

#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/decoder_base.hpp"
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joint_state.hpp>

namespace transformer_msp_bridge {

class ServoMotorDecoder : public IMspDecoder {
public:
  explicit ServoMotorDecoder(rclcpp::Node &node);
  void decode(const MSPPacket &pkt) override;
  bool matches(uint16_t command_id) const override;
  std::string name() const override;
private:
  void decodeServo(const MSPPacket &pkt);
  void decodeMotor(const MSPPacket &pkt);
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr servo_pub_;
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr motor_pub_;
};

} // namespace transformer_msp_bridge
