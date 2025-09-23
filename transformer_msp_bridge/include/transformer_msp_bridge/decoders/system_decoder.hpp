#pragma once
#include <rclcpp/rclcpp.hpp>
#include <diagnostic_msgs/msg/diagnostic_array.hpp>
#include <diagnostic_msgs/msg/diagnostic_status.hpp>
#include "transformer_msp_bridge/msp_protocol.hpp"
#include "transformer_msp_bridge/decoder_base.hpp"
namespace transformer_msp_bridge {
class SystemDecoder : public IMspDecoder {
public:
  SystemDecoder(rclcpp::Node &node) : node_(node) {
    status_pub_ = node_.create_publisher<diagnostic_msgs::msg::DiagnosticArray>("/msp/status_ex",10);
    sensor_status_pub_ = node_.create_publisher<diagnostic_msgs::msg::DiagnosticArray>("/msp/sensors/status",10);
    gps_stats_single_pub_ = node_.create_publisher<diagnostic_msgs::msg::DiagnosticStatus>("/msp/gps/statistics",10);
  }
  void decodeStatusEx(const MSPPacket &pkt);
  void decodeSensorStatus(const MSPPacket &pkt);
  void decodeGpsStatistics(const MSPPacket &pkt);
  void decodeRcTuning(const MSPPacket &pkt);
  void decodeRtc(const MSPPacket &pkt);
  bool matches(uint16_t command_id) const override {
    return command_id == MSP_STATUS_EX || command_id == MSP_SENSOR_STATUS || command_id == MSP_GPSSTATISTICS ||
           command_id == MSP_RC_TUNING || command_id == MSP_RTC;
  }
  void decode(const MSPPacket &pkt) override {
    switch (pkt.cmd) {
      case MSP_STATUS_EX: decodeStatusEx(pkt); break;
      case MSP_SENSOR_STATUS: decodeSensorStatus(pkt); break;
      case MSP_GPSSTATISTICS: decodeGpsStatistics(pkt); break;
      case MSP_RC_TUNING: decodeRcTuning(pkt); break;
      case MSP_RTC: decodeRtc(pkt); break;
      default: break;
    }
  }
  std::string name() const override { return "system"; }
private:
  rclcpp::Node &node_;
  rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticArray>::SharedPtr status_pub_;
  rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticArray>::SharedPtr sensor_status_pub_;
  rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticStatus>::SharedPtr gps_stats_single_pub_;
};
} // namespace transformer_msp_bridge
