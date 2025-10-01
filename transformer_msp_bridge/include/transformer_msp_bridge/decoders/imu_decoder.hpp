#pragma once

#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/decoder_base.hpp"
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/magnetic_field.hpp>
#include <cmath>

namespace transformer_msp_bridge
{

  class ImuDecoder : public IMspDecoder
  {
  public:
    explicit ImuDecoder(rclcpp::Node &node);
    void decode(const MSPPacket &pkt) override;
    bool matches(uint16_t command_id) const override;
    std::string name() const override;

  private:
    void decodeRawImu(const MSPPacket &pkt);
    rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imu_pub_;
    rclcpp::Publisher<sensor_msgs::msg::MagneticField>::SharedPtr mag_pub_;
  };

} // namespace transformer_msp_bridge
