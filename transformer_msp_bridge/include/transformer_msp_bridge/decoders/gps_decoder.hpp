#pragma once

#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/decoder_base.hpp"
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <geometry_msgs/msg/vector3_stamped.hpp>
#include <std_msgs/msg/float32.hpp>
#include <cmath>

namespace transformer_msp_bridge {

class GpsDecoder : public IMspDecoder {
public:
  explicit GpsDecoder(rclcpp::Node &node);
  void decode(const MSPPacket &pkt) override;
  bool matches(uint16_t command_id) const override;
  std::string name() const override;
private:
  void decodeRawGps(const MSPPacket &pkt);
  void decodeCompGps(const MSPPacket &pkt);
  rclcpp::Publisher<sensor_msgs::msg::NavSatFix>::SharedPtr fix_pub_;
  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr vel_pub_;
  rclcpp::Publisher<geometry_msgs::msg::Vector3Stamped>::SharedPtr home_vec_pub_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr home_dist_pub_;
};

} // namespace transformer_msp_bridge
