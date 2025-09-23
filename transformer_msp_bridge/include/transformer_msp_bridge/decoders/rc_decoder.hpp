#pragma once
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/u_int16_multi_array.hpp>
#include "transformer_msp_bridge/msp_protocol.hpp"
#include "transformer_msp_bridge/decoder_base.hpp"
namespace transformer_msp_bridge {
class RcDecoder : public IMspDecoder {
public:
  RcDecoder(rclcpp::Node &node, const std::string &topic) : node_(node) {
    pub_ = node_.create_publisher<std_msgs::msg::UInt16MultiArray>(topic, 10);
  }
  void decode(const MSPPacket &pkt) {
    if (pkt.payload.size() < 16) return;
    std::vector<uint16_t> chans; chans.reserve(pkt.payload.size()/2);
    for (size_t i=0;i+1<pkt.payload.size(); i+=2) {
      chans.push_back(pkt.payload[i] | (pkt.payload[i+1] << 8));
    }
    std_msgs::msg::UInt16MultiArray m; m.data = std::move(chans); pub_->publish(m);
  }
  bool matches(uint16_t command_id) const override { return command_id == MSP_RC; }
  std::string name() const override { return "rc"; }
private:
  rclcpp::Node &node_;
  rclcpp::Publisher<std_msgs::msg::UInt16MultiArray>::SharedPtr pub_;
};
} // namespace transformer_msp_bridge
