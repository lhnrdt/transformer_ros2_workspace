#pragma once
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/vector3.hpp>
#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/decoder_base.hpp"
namespace transformer_msp_bridge {
class AttitudeDecoder : public IMspDecoder {
public:
  explicit AttitudeDecoder(rclcpp::Node &node);
  void decode(const MSPPacket &pkt) override;
  bool matches(uint16_t command_id) const override;
  std::string name() const override;
private:
  rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr pub_;
};
} // namespace transformer_msp_bridge
