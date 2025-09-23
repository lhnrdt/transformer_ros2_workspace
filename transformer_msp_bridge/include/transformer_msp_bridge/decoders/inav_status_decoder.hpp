#pragma once

#include "transformer_msp_bridge/msp_protocol.hpp"
#include "transformer_msp_bridge/decoder_base.hpp"
#include "transformer_msp_bridge/msg/msp_inav_status.hpp"
#include <rclcpp/rclcpp.hpp>

namespace transformer_msp_bridge {

class InavStatusDecoder : public IMspDecoder {
public:
  explicit InavStatusDecoder(rclcpp::Node &node, bool debug);
  void decode(const MSPPacket &pkt) override;
  bool matches(uint16_t command_id) const override;
  std::string name() const override;
private:
  bool debug_{false};
  bool logged_{false};
  rclcpp::Publisher<transformer_msp_bridge::msg::MspInavStatus>::SharedPtr pub_;
};

} // namespace transformer_msp_bridge
