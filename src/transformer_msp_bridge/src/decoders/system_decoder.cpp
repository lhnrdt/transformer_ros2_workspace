// System diagnostics related decoders implementation
#include "transformer_msp_bridge/decoders/system_decoder.hpp"
#include <algorithm>
#include <utility>

namespace transformer_msp_bridge
{

  const uint16_t SystemDecoder::kMspStatusEx = msp::command_id("MSP_STATUS_EX");
  const uint16_t SystemDecoder::kMspStatus = msp::command_id("MSP_STATUS");
  const uint16_t SystemDecoder::kMspSensorStatus = msp::command_id("MSP_SENSOR_STATUS");
  const uint16_t SystemDecoder::kMspSensorConfig = msp::command_id("MSP_SENSOR_CONFIG");
  const uint16_t SystemDecoder::kMspGpsStatistics = msp::command_id("MSP_GPSSTATISTICS");
  const uint16_t SystemDecoder::kMspRcTuning = msp::command_id("MSP_RC_TUNING");
  const uint16_t SystemDecoder::kMspRtc = msp::command_id("MSP_RTC");

  SystemDecoder::SystemDecoder(Callbacks callbacks) : callbacks_(std::move(callbacks)) {}

  void SystemDecoder::set_callbacks(Callbacks callbacks) { callbacks_ = std::move(callbacks); }

  void SystemDecoder::decodeRcTuning(const MSPPacket &pkt)
  {
    if (pkt.cmd != kMspRcTuning)
      return;
    if (pkt.payload.size() < 9)
    {
      return;
    }
    auto rd8 = [&](size_t o) -> uint8_t
    { return o < pkt.payload.size() ? pkt.payload[o] : 0; };
    auto rd16 = [&](size_t o) -> uint16_t
    {
      if (pkt.payload.size() < o + 2)
        return 0;
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

    if (!callbacks_.rc_tuning)
      return;

    RcTuningData data;
    data.rc_rate = rcRate8 / 100.0;
    data.rc_expo = rcExpo8 / 100.0;
    data.throttle_mid = thrMid8 / 100.0;
    data.throttle_expo = thrExpo8 / 100.0;
    data.dyn_throttle_pid = dynThrPID;
    data.rc_yaw_expo = rcYawExpo8 / 100.0;
    data.rc_yaw_rate = rcYawRate / 100.0;
    data.rc_pitch_rate = rcPitchRate / 100.0;
    data.rc_roll_rate = rcRollRate / 100.0;
    data.tpa_breakpoint = tpa_breakpoint;
    callbacks_.rc_tuning(data);
  }

  void SystemDecoder::decodeStatusEx(const MSPPacket &pkt)
  {
    if (pkt.cmd != kMspStatusEx && pkt.cmd != kMspStatus)
    {
      return;
    }
    if (pkt.payload.size() < 6)
    {
      return;
    }
    auto rd8 = [&](size_t o) -> uint8_t
    { return o < pkt.payload.size() ? pkt.payload[o] : 0; };
    auto rd16 = [&](size_t o) -> uint16_t
    {
      if (pkt.payload.size() < o + 2)
        return 0;
      return static_cast<uint16_t>(pkt.payload[o] | (pkt.payload[o + 1] << 8));
    };
    auto rd32 = [&](size_t o) -> uint32_t
    {
      if (pkt.payload.size() < o + 4)
        return 0;
      return static_cast<uint32_t>(pkt.payload[o] | (pkt.payload[o + 1] << 8) | (pkt.payload[o + 2] << 16) | (pkt.payload[o + 3] << 24));
    };

    size_t off = 0;
    uint16_t cycle = rd16(off);
    off += 2;
    uint16_t i2cErr = rd16(off);
    off += 2;
    uint16_t sensors = rd16(off);
    off += 2;
    uint32_t modeFlags = pkt.payload.size() >= off + 4 ? rd32(off) : 0;
    off += (pkt.payload.size() >= off + 4 ? 4 : 0);
    uint8_t profile = rd8(off);
    if (off < pkt.payload.size())
      off++;
    uint8_t sysLoad = rd8(off);
    if (off < pkt.payload.size())
      off++;
    uint16_t gyroCycle = pkt.payload.size() >= off + 2 ? rd16(off) : 0;
    off += (pkt.payload.size() >= off + 2 ? 2 : 0);
    uint8_t lastArmReason = pkt.payload.size() > off ? rd8(off) : 0;
    if (pkt.payload.size() > off)
      off++;
    uint32_t armingFlags = pkt.payload.size() >= off + 4 ? rd32(off) : 0;
    off += (pkt.payload.size() >= off + 4 ? 4 : 0);
    uint8_t accCal = pkt.payload.size() > off ? rd8(off) : 0;

    if (!callbacks_.status_ex)
      return;

    SystemStatusExData data;
    data.cycle_time_us = cycle;
    data.i2c_errors = i2cErr;
    data.sensors_mask = sensors;
    data.mode_flags = modeFlags;
    data.profile = profile;
    data.system_load_pct = sysLoad;
    data.gyro_cycle_time_us = gyroCycle;
    data.last_arm_disable = lastArmReason;
    data.arming_flags = armingFlags;
    data.acc_cal_running = accCal;
    callbacks_.status_ex(data);
  }

  void SystemDecoder::decodeSensorStatus(const MSPPacket &pkt)
  {
    if (pkt.cmd != kMspSensorStatus)
      return;
    if (!callbacks_.sensor_status)
      return;

    auto rd16 = [&](size_t o) -> uint16_t
    {
      if (pkt.payload.size() < o + 2)
        return 0;
      return static_cast<uint16_t>(pkt.payload[o] | (pkt.payload[o + 1] << 8));
    };
    SystemSensorStatusData data;
    data.raw_payload = pkt.payload;

    if (pkt.payload.size() >= 4)
    {
      data.has_masks = true;
      data.present_mask = rd16(0);
      data.failing_mask = rd16(2);
    }
    else
    {
      data.has_masks = false;
      data.raw_payload = pkt.payload;
    }
    callbacks_.sensor_status(data);
  }

  void SystemDecoder::decodeSensorConfig(const MSPPacket &pkt)
  {
    if (pkt.cmd != kMspSensorConfig)
      return;
    if (!callbacks_.sensor_config)
      return;

    constexpr std::size_t kHardwareIdCount = 9;
    const std::size_t count = std::min<std::size_t>(pkt.payload.size(), kHardwareIdCount);

    SystemSensorConfigData data;
    data.hardware_ids.assign(pkt.payload.begin(), pkt.payload.begin() + count);
    if (pkt.payload.size() > count)
    {
      data.raw_tail.assign(pkt.payload.begin() + count, pkt.payload.end());
    }
    callbacks_.sensor_config(data);
  }

  void SystemDecoder::decodeGpsStatistics(const MSPPacket &pkt)
  {
    if (pkt.cmd != kMspGpsStatistics)
      return;
    if (!callbacks_.gps_statistics)
      return;

    auto rd16 = [&](size_t o) -> uint16_t
    {
      if (pkt.payload.size() < o + 2)
        return 0;
      return static_cast<uint16_t>(pkt.payload[o] | (pkt.payload[o + 1] << 8));
    };
    auto rd32 = [&](size_t o) -> uint32_t
    {
      if (pkt.payload.size() < o + 4)
        return 0;
      return static_cast<uint32_t>(pkt.payload[o] | (pkt.payload[o + 1] << 8) | (pkt.payload[o + 2] << 16) | (pkt.payload[o + 3] << 24));
    };

    uint16_t errors = rd16(0);
    uint16_t timeouts = rd16(2);
    uint16_t pktCount = rd16(4);
    uint16_t pktRejected = rd16(6);
    uint16_t pktIgnored = rd16(8);
    uint16_t pktCrcErr = rd16(10);
    uint32_t gpsReset = rd32(12);

    SystemGpsStatsData data;
    data.errors = errors;
    data.timeouts = timeouts;
    data.packet_count = pktCount;
    data.packet_rejected = pktRejected;
    data.packet_ignored = pktIgnored;
    data.packet_crc_error = pktCrcErr;
    data.gps_reset_flags = gpsReset;
    callbacks_.gps_statistics(data);
  }

  void SystemDecoder::decodeRtc(const MSPPacket &pkt)
  {
    if (pkt.cmd != kMspRtc)
      return;
    if (pkt.payload.size() < 6)
    {
      return;
    }
    int32_t secs = static_cast<int32_t>(pkt.payload[0] | (pkt.payload[1] << 8) | (pkt.payload[2] << 16) | (pkt.payload[3] << 24));
    uint16_t millis = static_cast<uint16_t>(pkt.payload[4] | (pkt.payload[5] << 8));

    if (!callbacks_.rtc)
      return;

    SystemRtcData data;
    data.seconds = secs;
    data.millis = millis;
    callbacks_.rtc(data);
  }

} // namespace transformer_msp_bridge
