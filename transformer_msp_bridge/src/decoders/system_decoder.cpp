// System diagnostics related decoders implementation
#include "transformer_msp_bridge/decoders/system_decoder.hpp"
#include <sstream>
#include <iomanip>

namespace transformer_msp_bridge {

using diagnostic_msgs::msg::DiagnosticArray;
using diagnostic_msgs::msg::DiagnosticStatus;
using diagnostic_msgs::msg::KeyValue;

void SystemDecoder::decodeRcTuning(const MSPPacket &pkt) {
  if (pkt.payload.size() < 9) {
    return;
  }
  auto rd8 = [&](size_t o) -> uint8_t { return o < pkt.payload.size() ? pkt.payload[o] : 0; };
  auto rd16 = [&](size_t o) -> uint16_t {
    if (pkt.payload.size() < o + 2) return 0;
    return static_cast<uint16_t>(pkt.payload[o] | (pkt.payload[o + 1] << 8));
  };

  uint8_t rcRate8 = rd8(0);
  uint8_t rcExpo8 = rd8(1);
  uint8_t thrMid8 = rd8(2);
  uint8_t thrExpo8 = rd8(3);
  uint8_t dynThrPID = rd8(4);
  uint8_t rcYawExpo8 = rd8(5);
  uint8_t rcYawRate = rd8(6);
  uint8_t rcPitchRate = rd8(7);
  uint8_t rcRollRate = rd8(8);
  uint16_t tpa_breakpoint = pkt.payload.size() >= 11 ? rd16(9) : 0;

  DiagnosticStatus st;
  st.name = "rc_tuning";
  st.hardware_id = "fc";
  st.level = DiagnosticStatus::OK;
  st.message = "rc tuning";

  auto add = [&](const std::string &k, double v) {
    KeyValue kv; kv.key = k; kv.value = std::to_string(v); st.values.push_back(kv);
  };
  add("rc_rate", rcRate8 / 100.0);
  add("rc_expo", rcExpo8 / 100.0);
  add("thr_mid", thrMid8 / 100.0);
  add("thr_expo", thrExpo8 / 100.0);
  add("dyn_throttle_pid", dynThrPID);
  add("rc_yaw_expo", rcYawExpo8 / 100.0);
  add("rc_yaw_rate", rcYawRate / 100.0);
  add("rc_pitch_rate", rcPitchRate / 100.0);
  add("rc_roll_rate", rcRollRate / 100.0);
  add("tpa_breakpoint", tpa_breakpoint);

  DiagnosticArray arr; arr.header.stamp = node_.now(); arr.status.push_back(st);
  status_pub_->publish(arr);
}

void SystemDecoder::decodeStatusEx(const MSPPacket &pkt) {
  if (pkt.payload.size() < 6) {
    return;
  }
  auto rd8 = [&](size_t o) -> uint8_t { return o < pkt.payload.size() ? pkt.payload[o] : 0; };
  auto rd16 = [&](size_t o) -> uint16_t {
    if (pkt.payload.size() < o + 2) return 0;
    return static_cast<uint16_t>(pkt.payload[o] | (pkt.payload[o + 1] << 8));
  };
  auto rd32 = [&](size_t o) -> uint32_t {
    if (pkt.payload.size() < o + 4) return 0;
    return static_cast<uint32_t>(pkt.payload[o] | (pkt.payload[o + 1] << 8) | (pkt.payload[o + 2] << 16) | (pkt.payload[o + 3] << 24));
  };

  size_t off = 0;
  uint16_t cycle = rd16(off); off += 2;
  uint16_t i2cErr = rd16(off); off += 2;
  uint16_t sensors = rd16(off); off += 2;
  uint32_t modeFlags = pkt.payload.size() >= off + 4 ? rd32(off) : 0; off += (pkt.payload.size() >= off + 4 ? 4 : 0);
  uint8_t profile = rd8(off); if (off < pkt.payload.size()) off++;
  uint8_t sysLoad = rd8(off); if (off < pkt.payload.size()) off++;
  uint16_t gyroCycle = pkt.payload.size() >= off + 2 ? rd16(off) : 0; off += (pkt.payload.size() >= off + 2 ? 2 : 0);
  uint8_t lastArmReason = pkt.payload.size() > off ? rd8(off) : 0; if (pkt.payload.size() > off) off++;
  uint32_t armingFlags = pkt.payload.size() >= off + 4 ? rd32(off) : 0; off += (pkt.payload.size() >= off + 4 ? 4 : 0);
  uint8_t accCal = pkt.payload.size() > off ? rd8(off) : 0;

  DiagnosticStatus st;
  st.name = "status_ex";
  st.hardware_id = "fc";
  st.level = DiagnosticStatus::OK;
  st.message = "status";

  auto add = [&](const std::string &k, uint64_t v) {
    KeyValue kv; kv.key = k; kv.value = std::to_string(v); st.values.push_back(kv);
  };
  add("cycle_time_us", cycle);
  add("i2c_errors", i2cErr);
  add("sensors_mask", sensors);
  add("mode_flags", modeFlags);
  add("profile", profile);
  add("system_load_pct", sysLoad);
  add("gyro_cycle_time", gyroCycle);
  add("last_arm_disable", lastArmReason);
  add("arming_flags", armingFlags);
  add("acc_cal_running", accCal);

  DiagnosticArray arr; arr.header.stamp = node_.now(); arr.status.push_back(st);
  status_pub_->publish(arr);
}

void SystemDecoder::decodeSensorStatus(const MSPPacket &pkt) {
  DiagnosticStatus st;
  st.name = "sensor_status";
  st.hardware_id = "fc";
  st.level = DiagnosticStatus::OK;
  st.message = "sensors";

  auto rd16 = [&](size_t o) -> uint16_t {
    if (pkt.payload.size() < o + 2) return 0;
    return static_cast<uint16_t>(pkt.payload[o] | (pkt.payload[o + 1] << 8));
  };
  if (pkt.payload.size() >= 4) {
    uint16_t present = rd16(0);
    uint16_t failing = rd16(2);
    KeyValue kv1; kv1.key = "present_mask"; kv1.value = std::to_string(present); st.values.push_back(kv1);
    KeyValue kv2; kv2.key = "failing_mask"; kv2.value = std::to_string(failing); st.values.push_back(kv2);
  } else {
    std::ostringstream hex;
    for (auto b : pkt.payload) {
      hex << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(b);
    }
    KeyValue kv; kv.key = "raw"; kv.value = hex.str(); st.values.push_back(kv);
  }

  DiagnosticArray arr; arr.header.stamp = node_.now(); arr.status.push_back(st);
  sensor_status_pub_->publish(arr);
}

void SystemDecoder::decodeGpsStatistics(const MSPPacket &pkt) {
  auto rd16 = [&](size_t o) -> uint16_t {
    if (pkt.payload.size() < o + 2) return 0;
    return static_cast<uint16_t>(pkt.payload[o] | (pkt.payload[o + 1] << 8));
  };
  auto rd32 = [&](size_t o) -> uint32_t {
    if (pkt.payload.size() < o + 4) return 0;
    return static_cast<uint32_t>(pkt.payload[o] | (pkt.payload[o + 1] << 8) | (pkt.payload[o + 2] << 16) | (pkt.payload[o + 3] << 24));
  };

  uint16_t errors       = rd16(0);
  uint16_t timeouts     = rd16(2);
  uint16_t pktCount     = rd16(4);
  uint16_t pktRejected  = rd16(6);
  uint16_t pktIgnored   = rd16(8);
  uint16_t pktCrcErr    = rd16(10);
  uint32_t gpsReset     = rd32(12);

  DiagnosticStatus st;
  st.name = "gps_statistics";
  st.hardware_id = "fc";
  st.level = DiagnosticStatus::OK;
  st.message = "gps stats";

  auto add = [&](const std::string &k, uint64_t v) {
    KeyValue kv; kv.key = k; kv.value = std::to_string(v); st.values.push_back(kv);
  };
  add("errors", errors);
  add("timeouts", timeouts);
  add("packet_count", pktCount);
  add("packet_rejected", pktRejected);
  add("packet_ignored", pktIgnored);
  add("packet_crc_error", pktCrcErr);
  add("gps_reset_flags", gpsReset);

  DiagnosticArray arr; arr.header.stamp = node_.now(); arr.status.push_back(st);
  gps_stats_single_pub_->publish(st);
  status_pub_->publish(arr);
}

void SystemDecoder::decodeRtc(const MSPPacket &pkt) {
  if (pkt.payload.size() < 6) {
    return;
  }
  int32_t secs = static_cast<int32_t>(pkt.payload[0] | (pkt.payload[1] << 8) | (pkt.payload[2] << 16) | (pkt.payload[3] << 24));
  uint16_t millis = static_cast<uint16_t>(pkt.payload[4] | (pkt.payload[5] << 8));

  DiagnosticStatus st;
  st.name = "rtc";
  st.hardware_id = "fc";
  st.level = DiagnosticStatus::OK;
  st.message = "rtc time";
  KeyValue kv1; kv1.key = "secs";   kv1.value = std::to_string(secs);   st.values.push_back(kv1);
  KeyValue kv2; kv2.key = "millis"; kv2.value = std::to_string(millis); st.values.push_back(kv2);

  DiagnosticArray arr; arr.header.stamp = node_.now(); arr.status.push_back(st);
  status_pub_->publish(arr);
}

} // namespace transformer_msp_bridge
