#pragma once

#include "transformer_msp_bridge/msp_protocol.hpp"
#include "transformer_msp_bridge/decoder_base.hpp"
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/magnetic_field.hpp>
#include <cmath>

namespace transformer_msp_bridge {

class ImuDecoder : public IMspDecoder {
public:
  explicit ImuDecoder(rclcpp::Node &node) {
    imu_pub_ = node.create_publisher<sensor_msgs::msg::Imu>("/msp/imu", 10);
    mag_pub_ = node.create_publisher<sensor_msgs::msg::MagneticField>("/msp/mag", 10);
  }

  void decodeRawImu(const MSPPacket &pkt) {
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

  bool matches(uint16_t command_id) const override { return command_id == MSP_RAW_IMU; }
  void decode(const MSPPacket &pkt) override { if (pkt.cmd == MSP_RAW_IMU) decodeRawImu(pkt); }
  std::string name() const override { return "imu"; }

private:
  rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imu_pub_;
  rclcpp::Publisher<sensor_msgs::msg::MagneticField>::SharedPtr mag_pub_;
};

} // namespace transformer_msp_bridge
