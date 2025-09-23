#pragma once

#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/decoder_base.hpp"
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>

namespace transformer_msp_bridge {

class AltitudeDecoder : public IMspDecoder {
public:
  explicit AltitudeDecoder(rclcpp::Node &node);
  void decode(const MSPPacket &pkt) override;
  bool matches(uint16_t command_id) const override;
  std::string name() const override;
private:
  void decodeAltitude(const MSPPacket &pkt);
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr alt_pub_;
  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr vs_pub_;
};

} // namespace transformer_msp_bridge
