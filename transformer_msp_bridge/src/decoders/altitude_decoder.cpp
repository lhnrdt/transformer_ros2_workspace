#include "transformer_msp_bridge/decoders/altitude_decoder.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include "transformer_msp_bridge/msp_utils.hpp"

namespace transformer_msp_bridge {

AltitudeDecoder::AltitudeDecoder(rclcpp::Node& node) {
  alt_pub_ = node.create_publisher<std_msgs::msg::Float32>("/msp/altitude", 10);
  vs_pub_ = node.create_publisher<geometry_msgs::msg::TwistStamped>("/msp/vertical_speed", 10);
}

bool AltitudeDecoder::matches(uint16_t command_id) const {
  return command_id == MSP_ALTITUDE;
}
std::string AltitudeDecoder::name() const {
  return "altitude";
}

void AltitudeDecoder::decode(const MSPPacket& pkt) {
  decodeAltitude(pkt);
}

void AltitudeDecoder::decodeAltitude(const MSPPacket& pkt) {
  if (pkt.cmd != MSP_ALTITUDE)
    return;
  if (pkt.payload.size() < 6)
    return;
  int32_t alt_cm;
  int16_t vs_cms;
  if (!readI32LE(pkt.payload, 0, alt_cm) || !readI16LE(pkt.payload, 4, vs_cms))
    return;
  std_msgs::msg::Float32 alt;
  alt.data = static_cast<float>(alt_cm / 100.0);
  alt_pub_->publish(alt);
  geometry_msgs::msg::TwistStamped vs;
  vs.twist.linear.z = vs_cms / 100.0;
  vs_pub_->publish(vs);
}

}  // namespace transformer_msp_bridge
