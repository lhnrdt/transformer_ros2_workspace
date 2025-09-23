#pragma once

#include "transformer_msp_bridge/msp_protocol.hpp"
#include "msp/msp_protocol_v2_sensor_msg.h"
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>
#include <geometry_msgs/msg/vector3.hpp>
#include <limits>

namespace transformer_msp_bridge {

class SensorDecoder {
public:
  explicit SensorDecoder(rclcpp::Node &node, bool debug): debug_(debug) {
    rangefinder_pub_ = node.create_publisher<std_msgs::msg::Float32>("/msp/rangefinder", 10);
    compass_pub_ = node.create_publisher<geometry_msgs::msg::Vector3>("/msp/compass", 10);
    barometer_pub_ = node.create_publisher<std_msgs::msg::Float32>("/msp/barometer", 10);
  }
  template<typename T>
  bool decodeStruct(const MSPPacket &pkt, T &out) {
    if(pkt.payload.size() < sizeof(T)) return false;
    std::memcpy(&out, pkt.payload.data(), sizeof(T));
    return true;
  }
  void decodeRangefinder(const MSPPacket &pkt) {
    mspSensorRangefinderDataMessage_t rf{}; if(!decodeStruct(pkt, rf)) return; std_msgs::msg::Float32 msg; if(rf.distanceMm < 0) msg.data = std::numeric_limits<float>::quiet_NaN(); else msg.data = rf.distanceMm/1000.0f; rangefinder_pub_->publish(msg); if(debug_ && !logged_rangefinder_){ RCLCPP_INFO(rclcpp::get_logger("SensorDecoder"), "Rangefinder first frame: quality=%u dist=%.3fm", rf.quality, msg.data); logged_rangefinder_=true; }
  }
  void decodeCompass(const MSPPacket &pkt) {
    mspSensorCompassDataMessage_t c{}; if(!decodeStruct(pkt,c)) return; geometry_msgs::msg::Vector3 v; v.x=c.magX; v.y=c.magY; v.z=c.magZ; compass_pub_->publish(v); if(debug_ && !logged_compass_) { RCLCPP_INFO(rclcpp::get_logger("SensorDecoder"), "Compass first frame: inst=%u mGauss=(%d,%d,%d)", c.instance,c.magX,c.magY,c.magZ); logged_compass_=true; }
  }
  void decodeBarometer(const MSPPacket &pkt) {
    mspSensorBaroDataMessage_t b{}; if(!decodeStruct(pkt,b)) return; std_msgs::msg::Float32 m; m.data=b.pressurePa; barometer_pub_->publish(m); if(debug_ && !logged_baro_) { RCLCPP_INFO(rclcpp::get_logger("SensorDecoder"), "Barometer first frame: inst=%u pressure=%.2fPa temp=%.2fC", b.instance,b.pressurePa,b.temp/100.0f); logged_baro_=true; }
  }
private:
  bool debug_{false};
  bool logged_rangefinder_{false};
  bool logged_compass_{false};
  bool logged_baro_{false};
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr rangefinder_pub_;
  rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr compass_pub_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr barometer_pub_;
};

} // namespace transformer_msp_bridge
