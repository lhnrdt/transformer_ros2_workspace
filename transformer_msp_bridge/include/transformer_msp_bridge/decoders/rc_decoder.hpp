#pragma once
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/u_int16_multi_array.hpp>
#include "transformer_msp_bridge/msp_protocol.hpp"
#include "transformer_msp_bridge/decoder_base.hpp"
namespace transformer_msp_bridge {
class RcDecoder : public IMspDecoder {
public:
  RcDecoder(rclcpp::Node &node, const std::string &topic);
  void decode(const MSPPacket &pkt) override;
  bool matches(uint16_t command_id) const override;
  std::string name() const override;
private:
  rclcpp::Publisher<std_msgs::msg::UInt16MultiArray>::SharedPtr pub_;
};
} // namespace transformer_msp_bridge
