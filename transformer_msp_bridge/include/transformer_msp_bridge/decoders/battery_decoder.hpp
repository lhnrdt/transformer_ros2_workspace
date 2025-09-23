#pragma once
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/battery_state.hpp>
#include <diagnostic_msgs/msg/diagnostic_array.hpp>
#include "transformer_msp_bridge/msp_protocol.hpp"
#include "transformer_msp_bridge/decoder_base.hpp"
namespace transformer_msp_bridge {
class BatteryDecoder : public IMspDecoder {
public:
  BatteryDecoder(rclcpp::Node &node) : node_(node) {
    analog_pub_ = node_.create_publisher<sensor_msgs::msg::BatteryState>("/msp/battery",10);
    extended_pub_ = node_.create_publisher<sensor_msgs::msg::BatteryState>("/msp/battery/dji",10);
  }
  void decodeAnalog(const MSPPacket &pkt);
  void decodeBatteryState(const MSPPacket &pkt);
  // IMspDecoder implementation
  bool matches(uint16_t command_id) const override {
    return command_id == MSP_ANALOG || command_id == MSP_BATTERY_STATE;
  }
  void decode(const MSPPacket &pkt) override {
    if (pkt.cmd == MSP_ANALOG) decodeAnalog(pkt);
    else if (pkt.cmd == MSP_BATTERY_STATE) decodeBatteryState(pkt);
  }
  std::string name() const override { return "battery"; }
private:
  rclcpp::Node &node_;
  rclcpp::Publisher<sensor_msgs::msg::BatteryState>::SharedPtr analog_pub_;
  rclcpp::Publisher<sensor_msgs::msg::BatteryState>::SharedPtr extended_pub_;
};
} // namespace transformer_msp_bridge
