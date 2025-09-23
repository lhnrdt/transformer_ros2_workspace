#include "transformer_msp_bridge/decoders/imu_decoder.hpp"

namespace transformer_msp_bridge {

ImuDecoder::ImuDecoder(rclcpp::Node &node) {
	imu_pub_ = node.create_publisher<sensor_msgs::msg::Imu>("/msp/imu", 10);
	mag_pub_ = node.create_publisher<sensor_msgs::msg::MagneticField>("/msp/mag", 10);
}

bool ImuDecoder::matches(uint16_t command_id) const { return command_id == MSP_RAW_IMU; }
std::string ImuDecoder::name() const { return "imu"; }

void ImuDecoder::decode(const MSPPacket &pkt) {
	if (pkt.cmd == MSP_RAW_IMU) decodeRawImu(pkt);
}

void ImuDecoder::decodeRawImu(const MSPPacket &pkt) {
	if (pkt.payload.size() < 18) return; // 9 * int16
	auto rd16 = [&](size_t off){ return (int16_t)(pkt.payload[off] | (pkt.payload[off+1] << 8)); };
	int16_t ax=rd16(0), ay=rd16(2), az=rd16(4);
	int16_t gx=rd16(6), gy=rd16(8), gz=rd16(10);
	int16_t mx=rd16(12), my=rd16(14), mz=rd16(16);
	sensor_msgs::msg::Imu imu; // orientation left unset
	constexpr double g = 9.80665;
	imu.linear_acceleration.x = (ax / 512.0) * g;
	imu.linear_acceleration.y = (ay / 512.0) * g;
	imu.linear_acceleration.z = (az / 512.0) * g;
	imu.angular_velocity.x = (gx / 16.0) * (M_PI/180.0);
	imu.angular_velocity.y = (gy / 16.0) * (M_PI/180.0);
	imu.angular_velocity.z = (gz / 16.0) * (M_PI/180.0);
	imu_pub_->publish(imu);
	sensor_msgs::msg::MagneticField mag;
	mag.magnetic_field.x = mx * 1e-6; // rough scaling; adjust with calibration if needed
	mag.magnetic_field.y = my * 1e-6;
	mag.magnetic_field.z = mz * 1e-6;
	mag_pub_->publish(mag);
}

} // namespace transformer_msp_bridge
