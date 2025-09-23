#include "transformer_msp_bridge/decoders/altitude_decoder.hpp"

namespace transformer_msp_bridge {

AltitudeDecoder::AltitudeDecoder(rclcpp::Node &node) {
  alt_pub_ = node.create_publisher<std_msgs::msg::Float32>("/msp/altitude", 10);
  vs_pub_ = node.create_publisher<geometry_msgs::msg::TwistStamped>("/msp/vertical_speed", 10);
}

bool AltitudeDecoder::matches(uint16_t command_id) const { return command_id == MSP_ALTITUDE; }
std::string AltitudeDecoder::name() const { return "altitude"; }

void AltitudeDecoder::decode(const MSPPacket &pkt) { decodeAltitude(pkt); }

void AltitudeDecoder::decodeAltitude(const MSPPacket &pkt) {
  if (pkt.cmd != MSP_ALTITUDE || pkt.payload.size() < 6) return;
  int32_t alt_cm = (int32_t)(pkt.payload[0] | (pkt.payload[1]<<8) | (pkt.payload[2]<<16) | (pkt.payload[3]<<24));
  int16_t vs_cms = (int16_t)(pkt.payload[4] | (pkt.payload[5]<<8));
  std_msgs::msg::Float32 alt; alt.data = alt_cm / 100.0f; alt_pub_->publish(alt);
  geometry_msgs::msg::TwistStamped vs; vs.twist.linear.z = vs_cms / 100.0; vs_pub_->publish(vs);
}

} // namespace transformer_msp_bridge
