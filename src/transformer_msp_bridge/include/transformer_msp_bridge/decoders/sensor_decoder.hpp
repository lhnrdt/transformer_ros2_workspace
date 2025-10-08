#pragma once

#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/decoder_base.hpp"
#include "msp/msp_protocol_v2_sensor_msg.h"
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>
#include <geometry_msgs/msg/vector3.hpp>
#include <limits>

namespace transformer_msp_bridge
{

  class SensorDecoder : public IMspDecoder
  {
  public:
    explicit SensorDecoder(rclcpp::Node &node, bool debug);
    void decode(const MSPPacket &pkt) override;
    bool matches(uint16_t command_id) const override;
    std::string name() const override;

  private:
    template <typename T>
    bool decodeStruct(const MSPPacket &pkt, T &out);
    void decodeRangefinder(const MSPPacket &pkt);
    void decodeCompass(const MSPPacket &pkt);
    void decodeBarometer(const MSPPacket &pkt);
    bool debug_{false};
    bool logged_rangefinder_{false};
    bool logged_compass_{false};
    bool logged_baro_{false};
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr rangefinder_pub_;
    rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr compass_pub_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr barometer_pub_;
  };

} // namespace transformer_msp_bridge
