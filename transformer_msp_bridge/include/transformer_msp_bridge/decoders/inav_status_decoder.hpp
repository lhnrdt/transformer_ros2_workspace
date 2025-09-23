#pragma once

#include "transformer_msp_bridge/msp_protocol.hpp"
#include "transformer_msp_bridge/decoder_base.hpp"
#include "transformer_msp_bridge/msg/msp_inav_status.hpp"
#include <rclcpp/rclcpp.hpp>

namespace transformer_msp_bridge {

class InavStatusDecoder : public IMspDecoder {
public:
  explicit InavStatusDecoder(rclcpp::Node &node, bool debug): debug_(debug) {
    pub_ = node.create_publisher<transformer_msp_bridge::msg::MspInavStatus>("/msp/inav_status", 10);
  }
  void decode(const MSPPacket &pkt) {
    if (pkt.payload.size() < 2+2+2+2+1+4+1) return;
    const uint8_t *p = pkt.payload.data();
    auto rd16 = [&](size_t off){ return (uint16_t)(p[off] | (p[off+1] << 8)); };
    uint16_t cycleTime = rd16(0);
    uint16_t i2cErrors = rd16(2);
    uint16_t sensorStatus = rd16(4);
    uint16_t cpuLoad = rd16(6);
    uint8_t profileAndBatt = p[8];
    uint32_t armingFlags = (uint32_t)p[9] | ((uint32_t)p[10] << 8) | ((uint32_t)p[11] << 16) | ((uint32_t)p[12] << 24);
    size_t activeModesStart = 13;
    if (pkt.payload.size() <= activeModesStart) return;
    size_t mixerProfilePos = pkt.payload.size() - 1;
    uint8_t mixerProfile = pkt.payload[mixerProfilePos];
    size_t activeModesLen = mixerProfilePos - activeModesStart;
    transformer_msp_bridge::msg::MspInavStatus msg;
    msg.cycle_time_us = cycleTime;
    msg.i2c_errors = i2cErrors;
    msg.sensor_status = sensorStatus;
    msg.cpu_load_percent = cpuLoad;
    msg.config_profile = (uint8_t)(profileAndBatt & 0x0F);
    msg.battery_profile = (uint8_t)((profileAndBatt >> 4) & 0x0F);
    msg.mixer_profile = mixerProfile;
    msg.arming_flags = armingFlags;
    if (activeModesLen > 0) {
      msg.active_modes.assign(pkt.payload.begin() + activeModesStart, pkt.payload.begin() + activeModesStart + activeModesLen);
    }
    pub_->publish(msg);
    if (debug_ && !logged_) {
      RCLCPP_INFO(rclcpp::get_logger("InavStatusDecoder"), "INAV_STATUS: cycle=%u cpu=%u%% i2c=%u sensorMask=0x%04X modes=%zu profile=%u batt=%u mixer=%u", cycleTime, cpuLoad, i2cErrors, sensorStatus, activeModesLen, (unsigned)(profileAndBatt & 0x0F), (unsigned)((profileAndBatt >> 4) & 0x0F), mixerProfile);
      logged_ = true;
    }
  }
  bool matches(uint16_t command_id) const override { return command_id == MSP2_INAV_STATUS; }
  std::string name() const override { return "inav_status"; }
private:
  bool debug_{false};
  bool logged_{false};
  rclcpp::Publisher<transformer_msp_bridge::msg::MspInavStatus>::SharedPtr pub_;
};

} // namespace transformer_msp_bridge
