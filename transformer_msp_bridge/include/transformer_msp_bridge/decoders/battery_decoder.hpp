#pragma once
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/battery_state.hpp>
#include <diagnostic_msgs/msg/diagnostic_array.hpp>
#include "transformer_msp_bridge/msp_protocol.hpp"
namespace transformer_msp_bridge {
class BatteryDecoder {
public:
  BatteryDecoder(rclcpp::Node &node) : node_(node) {
    analog_pub_ = node_.create_publisher<sensor_msgs::msg::BatteryState>("/msp/battery",10);
    extended_pub_ = node_.create_publisher<sensor_msgs::msg::BatteryState>("/msp/battery/dji",10);
  }
  void decodeAnalog(const MSPPacket &pkt);
  void decodeBatteryState(const MSPPacket &pkt);
private:
  rclcpp::Node &node_;
  rclcpp::Publisher<sensor_msgs::msg::BatteryState>::SharedPtr analog_pub_;
  rclcpp::Publisher<sensor_msgs::msg::BatteryState>::SharedPtr extended_pub_;
};
} // namespace transformer_msp_bridge
