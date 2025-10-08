#include "transformer_msp_bridge/decoders/rc_decoder.hpp"

namespace transformer_msp_bridge
{

  RcDecoder::RcDecoder(rclcpp::Node &node, const std::string &topic)
  {
    pub_ = node.create_publisher<std_msgs::msg::UInt16MultiArray>(topic, 10);
  }

  bool RcDecoder::matches(uint16_t command_id) const { return command_id == MSP_RC; }
  std::string RcDecoder::name() const { return "rc"; }

  void RcDecoder::decode(const MSPPacket &pkt)
  {
    if (pkt.cmd != MSP_RC || pkt.payload.size() < 16)
      return;
    std::vector<uint16_t> chans;
    chans.reserve(pkt.payload.size() / 2);
    for (size_t i = 0; i + 1 < pkt.payload.size(); i += 2)
    {
      chans.push_back(pkt.payload[i] | (pkt.payload[i + 1] << 8));
    }
    std_msgs::msg::UInt16MultiArray m;
    m.data = std::move(chans);
    pub_->publish(m);
  }

} // namespace transformer_msp_bridge
