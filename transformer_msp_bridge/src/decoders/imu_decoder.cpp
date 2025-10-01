#include "transformer_msp_bridge/decoders/imu_decoder.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include "transformer_msp_bridge/msp_utils.hpp"

namespace transformer_msp_bridge
{

  ImuDecoder::ImuDecoder(rclcpp::Node &node)
  {
    imu_pub_ = node.create_publisher<sensor_msgs::msg::Imu>("/msp/imu", 10);
    mag_pub_ = node.create_publisher<sensor_msgs::msg::MagneticField>("/msp/mag", 10);
  }

  bool ImuDecoder::matches(uint16_t command_id) const
  {
    return command_id == MSP_RAW_IMU;
  }
  std::string ImuDecoder::name() const
  {
    return "imu";
  }

  void ImuDecoder::decode(const MSPPacket &pkt)
  {
    if (pkt.cmd == MSP_RAW_IMU)
      decodeRawImu(pkt);
  }

  void ImuDecoder::decodeRawImu(const MSPPacket &pkt)
  {
    if (pkt.payload.size() < 18)
      return;
    int16_t ax, ay, az, gx, gy, gz, mx, my, mz;
    if (!readI16LE(pkt.payload, 0, ax) || !readI16LE(pkt.payload, 2, ay) || !readI16LE(pkt.payload, 4, az) ||
        !readI16LE(pkt.payload, 6, gx) || !readI16LE(pkt.payload, 8, gy) || !readI16LE(pkt.payload, 10, gz) ||
        !readI16LE(pkt.payload, 12, mx) || !readI16LE(pkt.payload, 14, my) || !readI16LE(pkt.payload, 16, mz))
      return;

    sensor_msgs::msg::Imu imu; // orientation left unset
    constexpr double g = 9.80665;
    imu.linear_acceleration.x = (ax / 512.0) * g;
    imu.linear_acceleration.y = (ay / 512.0) * g;
    imu.linear_acceleration.z = (az / 512.0) * g;
    imu.angular_velocity.x = (gx / 16.0) * (M_PI / 180.0);
    imu.angular_velocity.y = (gy / 16.0) * (M_PI / 180.0);
    imu.angular_velocity.z = (gz / 16.0) * (M_PI / 180.0);
    imu_pub_->publish(imu);

    sensor_msgs::msg::MagneticField mag;
    mag.magnetic_field.x = mx * 1e-6; // rough scaling; adjust with calibration if needed
    mag.magnetic_field.y = my * 1e-6;
    mag.magnetic_field.z = mz * 1e-6;
    mag_pub_->publish(mag);
  }

} // namespace transformer_msp_bridge
