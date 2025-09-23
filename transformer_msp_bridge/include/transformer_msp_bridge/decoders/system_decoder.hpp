#pragma once
#include <rclcpp/rclcpp.hpp>
#include <diagnostic_msgs/msg/diagnostic_array.hpp>
#include <diagnostic_msgs/msg/diagnostic_status.hpp>
#include "transformer_msp_bridge/msp_protocol.hpp"
namespace transformer_msp_bridge {
class SystemDecoder {
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
private:
  rclcpp::Node &node_;
  rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticArray>::SharedPtr status_pub_;
  rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticArray>::SharedPtr sensor_status_pub_;
  rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticStatus>::SharedPtr gps_stats_single_pub_;
};
} // namespace transformer_msp_bridge
