#include "transformer_msp_bridge/decoders/servo_motor_decoder.hpp"

namespace transformer_msp_bridge
{

  ServoMotorDecoder::ServoMotorDecoder(rclcpp::Node &node)
  {
    servo_pub_ = node.create_publisher<sensor_msgs::msg::JointState>("/msp/servo", 10);
    motor_pub_ = node.create_publisher<sensor_msgs::msg::JointState>("/msp/motor", 10);
  }

  bool ServoMotorDecoder::matches(uint16_t command_id) const { return command_id == MSP_SERVO || command_id == MSP_MOTOR; }
  std::string ServoMotorDecoder::name() const { return "servo_motor"; }

  void ServoMotorDecoder::decode(const MSPPacket &pkt)
  {
    if (pkt.cmd == MSP_SERVO)
      decodeServo(pkt);
    else if (pkt.cmd == MSP_MOTOR)
      decodeMotor(pkt);
  }

  void ServoMotorDecoder::decodeServo(const MSPPacket &pkt)
  {
    size_t n = pkt.payload.size() / 2;
    if (!n)
      return;
    sensor_msgs::msg::JointState js;
    js.position.reserve(n);
    for (size_t i = 0; i < n; i++)
    {
      uint16_t v = pkt.payload[2 * i] | (pkt.payload[2 * i + 1] << 8);
      js.position.push_back(static_cast<double>(v));
    }
    servo_pub_->publish(js);
  }

  void ServoMotorDecoder::decodeMotor(const MSPPacket &pkt)
  {
    size_t n = pkt.payload.size() / 2;
    if (!n)
      return;
    sensor_msgs::msg::JointState js;
    js.velocity.reserve(n);
    for (size_t i = 0; i < n; i++)
    {
      uint16_t v = pkt.payload[2 * i] | (pkt.payload[2 * i + 1] << 8);
      js.velocity.push_back(static_cast<double>(v));
    }
    motor_pub_->publish(js);
  }

} // namespace transformer_msp_bridge
