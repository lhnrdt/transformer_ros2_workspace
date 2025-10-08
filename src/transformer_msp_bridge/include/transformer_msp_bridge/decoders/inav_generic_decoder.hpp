#pragma once

#include <diagnostic_msgs/msg/diagnostic_array.hpp>
#include <diagnostic_msgs/msg/diagnostic_status.hpp>
#include <diagnostic_msgs/msg/key_value.hpp>
#include <rclcpp/rclcpp.hpp>
#include "transformer_msp_bridge/decoder_base.hpp"

namespace transformer_msp_bridge
{

  // Minimal decoder for assorted MSPv2 INAV telemetry frames we poll by default.
  // Publishes a DiagnosticArray with a single DiagnosticStatus per frame type,
  // containing a hex-encoded raw payload to avoid "no decoder" warnings while
  // keeping implementation simple.
  class InavGenericDecoder : public IMspDecoder
  {
  public:
    explicit InavGenericDecoder(rclcpp::Node &node) : node_(node)
    {
      diag_pub_ = node_.create_publisher<diagnostic_msgs::msg::DiagnosticArray>("/msp/inav_generic", 10);
    }

    bool matches(uint16_t command_id) const override;
    void decode(const MSPPacket &pkt) override;
    std::string name() const override { return "inav_generic"; }

  private:
    void publishRaw(const MSPPacket &pkt, const std::string &title);

    rclcpp::Node &node_;
    rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticArray>::SharedPtr diag_pub_{};
  };

} // namespace transformer_msp_bridge
