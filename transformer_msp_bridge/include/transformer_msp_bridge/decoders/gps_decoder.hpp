#pragma once

#include "transformer_msp_bridge/msp_protocol.hpp"
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <geometry_msgs/msg/vector3_stamped.hpp>
#include <std_msgs/msg/float32.hpp>
#include <cmath>

namespace transformer_msp_bridge {

class GpsDecoder {
public:
  explicit GpsDecoder(rclcpp::Node &node) {
    fix_pub_ = node.create_publisher<sensor_msgs::msg::NavSatFix>("/msp/gps/fix", 10);
    vel_pub_ = node.create_publisher<geometry_msgs::msg::TwistStamped>("/msp/gps/vel", 10);
    home_vec_pub_ = node.create_publisher<geometry_msgs::msg::Vector3Stamped>("/msp/home/vector", 10);
    home_dist_pub_ = node.create_publisher<std_msgs::msg::Float32>("/msp/home/distance", 10);
  }

  void decodeRawGps(const MSPPacket &pkt) {
    if (pkt.payload.size() < 16) return; // minimal legacy size
    auto rd32 = [&](size_t off){ return (int32_t)(pkt.payload[off] | (pkt.payload[off+1]<<8) | (pkt.payload[off+2]<<16) | (pkt.payload[off+3]<<24)); };
    uint8_t fix = pkt.payload[0];
    // uint8_t sats = pkt.payload[1]; // could be exposed later
    int32_t lat = rd32(2);
    int32_t lon = rd32(6);
    int16_t alt_m = (int16_t)(pkt.payload[10] | (pkt.payload[11]<<8));
    uint16_t speed_cms = (uint16_t)(pkt.payload[12] | (pkt.payload[13]<<8));
    uint16_t course_deg10 = (uint16_t)(pkt.payload[14] | (pkt.payload[15]<<8));
    sensor_msgs::msg::NavSatFix msg;
    msg.latitude = lat / 1e7;
    msg.longitude = lon / 1e7;
    msg.altitude = alt_m;
    msg.status.service = sensor_msgs::msg::NavSatStatus::SERVICE_GPS;
    msg.status.status = (fix > 0) ? sensor_msgs::msg::NavSatStatus::STATUS_FIX : sensor_msgs::msg::NavSatStatus::STATUS_NO_FIX;
    fix_pub_->publish(msg);
    geometry_msgs::msg::TwistStamped vel;
    vel.twist.linear.x = speed_cms / 100.0; // m/s
    vel.twist.angular.z = (course_deg10 / 10.0) * (M_PI/180.0);
    vel_pub_->publish(vel);
  }

  void decodeCompGps(const MSPPacket &pkt) {
    if (pkt.payload.size() < 4) return;
    uint16_t dist = pkt.payload[0] | (pkt.payload[1]<<8);
    uint16_t dir = pkt.payload[2] | (pkt.payload[3]<<8);
    geometry_msgs::msg::Vector3Stamped vec;
    vec.vector.x = dist; vec.vector.y = dir; vec.vector.z = 0;
    home_vec_pub_->publish(vec);
    std_msgs::msg::Float32 d; d.data = dist; home_dist_pub_->publish(d);
  }

private:
  rclcpp::Publisher<sensor_msgs::msg::NavSatFix>::SharedPtr fix_pub_;
  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr vel_pub_;
  rclcpp::Publisher<geometry_msgs::msg::Vector3Stamped>::SharedPtr home_vec_pub_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr home_dist_pub_;
};

} // namespace transformer_msp_bridge
