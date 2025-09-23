#include "transformer_msp_bridge/decoders/attitude_decoder.hpp"

namespace transformer_msp_bridge {

AttitudeDecoder::AttitudeDecoder(rclcpp::Node &node) {
	pub_ = node.create_publisher<geometry_msgs::msg::Vector3>("/msp/attitude", 10);
}

bool AttitudeDecoder::matches(uint16_t command_id) const { return command_id == MSP_ATTITUDE; }
std::string AttitudeDecoder::name() const { return "attitude"; }

void AttitudeDecoder::decode(const MSPPacket &pkt) {
	if (pkt.cmd != MSP_ATTITUDE || pkt.payload.size() < 6) return;
	int16_t roll = (int16_t)(pkt.payload[0] | (pkt.payload[1] << 8));
	int16_t pitch = (int16_t)(pkt.payload[2] | (pkt.payload[3] << 8));
	int16_t yaw = (int16_t)(pkt.payload[4] | (pkt.payload[5] << 8));
	geometry_msgs::msg::Vector3 v; v.x = roll / 10.0; v.y = pitch / 10.0; v.z = yaw / 10.0; pub_->publish(v);
}

} // namespace transformer_msp_bridge
