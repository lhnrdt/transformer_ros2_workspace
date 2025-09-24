#include "transformer_msp_bridge/decoders/attitude_decoder.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include "transformer_msp_bridge/msp_utils.hpp"

namespace transformer_msp_bridge {

AttitudeDecoder::AttitudeDecoder(rclcpp::Node& node) {
  pub_ = node.create_publisher<geometry_msgs::msg::Vector3>("/msp/attitude", 10);
}

bool AttitudeDecoder::matches(uint16_t command_id) const {
  return command_id == MSP_ATTITUDE;
}
std::string AttitudeDecoder::name() const {
  return "attitude";
}

void AttitudeDecoder::decode(const MSPPacket& pkt) {
  if (pkt.cmd != MSP_ATTITUDE)
    return;
  if (pkt.payload.size() < 6)
    return;
  int16_t roll, pitch, yaw;
  if (!readI16LE(pkt.payload, 0, roll) || !readI16LE(pkt.payload, 2, pitch) || !readI16LE(pkt.payload, 4, yaw))
    return;
  geometry_msgs::msg::Vector3 v;
  v.x = roll / 10.0;
  v.y = pitch / 10.0;
  v.z = yaw / 10.0;
  pub_->publish(v);
}

}  // namespace transformer_msp_bridge
