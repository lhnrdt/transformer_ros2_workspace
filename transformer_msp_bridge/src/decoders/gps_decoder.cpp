#include "transformer_msp_bridge/decoders/gps_decoder.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include "transformer_msp_bridge/msp_utils.hpp"

namespace transformer_msp_bridge
{

  GpsDecoder::GpsDecoder(rclcpp::Node &node)
  {
    fix_pub_ = node.create_publisher<sensor_msgs::msg::NavSatFix>("/msp/gps/fix", 10);
    vel_pub_ = node.create_publisher<geometry_msgs::msg::TwistStamped>("/msp/gps/vel", 10);
    home_vec_pub_ = node.create_publisher<geometry_msgs::msg::Vector3Stamped>("/msp/home/vector", 10);
    home_dist_pub_ = node.create_publisher<std_msgs::msg::Float32>("/msp/home/distance", 10);
  }

  bool GpsDecoder::matches(uint16_t command_id) const
  {
    return command_id == MSP_RAW_GPS || command_id == MSP_COMP_GPS;
  }
  std::string GpsDecoder::name() const
  {
    return "gps";
  }

  void GpsDecoder::decode(const MSPPacket &pkt)
  {
    if (pkt.cmd == MSP_RAW_GPS)
      decodeRawGps(pkt);
    else if (pkt.cmd == MSP_COMP_GPS)
      decodeCompGps(pkt);
  }

  void GpsDecoder::decodeRawGps(const MSPPacket &pkt)
  {
    if (pkt.payload.size() < 14)
      return;
    uint8_t fix, sats;
    int32_t lat, lon;
    int16_t alt;
    uint16_t speed_cms, course_deg10;
    if (!readU8(pkt.payload, 0, fix) || !readU8(pkt.payload, 1, sats) || !readI32LE(pkt.payload, 2, lat) ||
        !readI32LE(pkt.payload, 6, lon) || !readI16LE(pkt.payload, 10, alt) || !readU16LE(pkt.payload, 12, speed_cms) ||
        !readU16LE(pkt.payload, 14, course_deg10))
    {
      return;
    }
    double lat_deg = lat * 1e-7;
    double lon_deg = lon * 1e-7;
    double alt_m = alt * 1.0;
    double speed_ms = speed_cms / 100.0;
    double course_rad = (course_deg10 / 10.0) * (M_PI / 180.0);
    sensor_msgs::msg::NavSatFix msg;
    msg.latitude = lat_deg;
    msg.longitude = lon_deg;
    msg.altitude = alt_m;
    msg.status.service = sensor_msgs::msg::NavSatStatus::SERVICE_GPS;
    msg.status.status =
        (fix > 0) ? sensor_msgs::msg::NavSatStatus::STATUS_FIX : sensor_msgs::msg::NavSatStatus::STATUS_NO_FIX;
    fix_pub_->publish(msg);
    geometry_msgs::msg::TwistStamped vel;
    vel.twist.linear.x = speed_ms; // already scaled to m/s
    vel.twist.angular.z = course_rad;
    vel_pub_->publish(vel);
  }

  void GpsDecoder::decodeCompGps(const MSPPacket &pkt)
  {
    if (pkt.payload.size() < 4)
      return;
    uint16_t dist_u16, dir_deg_u16;
    if (!readU16LE(pkt.payload, 0, dist_u16) || !readU16LE(pkt.payload, 2, dir_deg_u16))
      return;
    double dist = dist_u16 * 1.0;
    double dir_deg = dir_deg_u16 * 1.0;
    geometry_msgs::msg::Vector3Stamped vec;
    vec.vector.x = dist;
    vec.vector.y = dir_deg;
    vec.vector.z = 0;
    home_vec_pub_->publish(vec);
    std_msgs::msg::Float32 dist_msg;
    dist_msg.data = static_cast<float>(dist);
    home_dist_pub_->publish(dist_msg);
  }

} // namespace transformer_msp_bridge
