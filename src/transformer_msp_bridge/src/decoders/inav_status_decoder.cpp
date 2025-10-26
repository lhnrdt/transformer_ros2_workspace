#include "transformer_msp_bridge/decoders/inav_status_decoder.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include <iomanip>
#include <sstream>
#include <utility>

namespace transformer_msp_bridge
{

  namespace
  {
  const uint16_t kMsp2InavStatus = msp::command_id("MSP2_INAV_STATUS");
  }

  InavStatusDecoder::InavStatusDecoder() = default;

  InavStatusDecoder::InavStatusDecoder(Callbacks callbacks) : callbacks_(std::move(callbacks)) {}

  void InavStatusDecoder::set_callbacks(Callbacks callbacks) { callbacks_ = std::move(callbacks); }

  bool InavStatusDecoder::matches(uint16_t id) const
  {
    return id == kMsp2InavStatus;
  }
  std::string InavStatusDecoder::name() const
  {
    return "inav_status";
  }

  void InavStatusDecoder::decode(const MSPPacket &pkt)
  {
    if (pkt.cmd != kMsp2InavStatus)
      return;
    if (pkt.payload.size() < 2 + 2 + 2 + 2 + 1 + 4 + 1)
      return;
    const uint8_t *p = pkt.payload.data();
    auto rd16 = [&](size_t off)
    {
      return (uint16_t)(p[off] | (p[off + 1] << 8));
    };
    uint16_t cycleTime = rd16(0);
    uint16_t i2cErrors = rd16(2);
    uint16_t sensorStatus = rd16(4);
    uint16_t cpuLoad = rd16(6);
    uint8_t profileAndBatt = p[8];
    uint32_t armingFlags = (uint32_t)p[9] | ((uint32_t)p[10] << 8) | ((uint32_t)p[11] << 16) | ((uint32_t)p[12] << 24);
    size_t activeModesStart = 13;
    if (pkt.payload.size() <= activeModesStart)
      return;
    size_t mixerProfilePos = pkt.payload.size() - 1;
    uint8_t mixerProfile = pkt.payload[mixerProfilePos];
    size_t activeModesLen = mixerProfilePos - activeModesStart;
    InavStatusData data;
    data.cycle_time_us = cycleTime;
    data.i2c_errors = i2cErrors;
    data.sensor_status_mask = sensorStatus;
    data.cpu_load_percent = cpuLoad;
    data.config_profile = static_cast<uint8_t>(profileAndBatt & 0x0F);
    data.battery_profile = static_cast<uint8_t>((profileAndBatt >> 4) & 0x0F);
    data.mixer_profile = mixerProfile;
    data.arming_flags = armingFlags;
    if (activeModesLen > 0)
    {
      data.active_modes.assign(pkt.payload.begin() + activeModesStart,
                               pkt.payload.begin() + activeModesStart + activeModesLen);
    }
    if (callbacks_.status)
      callbacks_.status(data);
    if (callbacks_.log_first_frame && callbacks_.log_info && !logged_)
    {
      std::ostringstream oss;
      oss << "INAV_STATUS: cycle=" << cycleTime << " cpu=" << cpuLoad << "% i2c=" << i2cErrors
          << " sensorMask=0x" << std::hex << std::uppercase << sensorStatus << std::dec << " modes=" << activeModesLen
          << " profile=" << static_cast<unsigned>(profileAndBatt & 0x0F)
          << " batt=" << static_cast<unsigned>((profileAndBatt >> 4) & 0x0F) << " mixer="
          << static_cast<unsigned>(mixerProfile);
      callbacks_.log_info(oss.str());
      logged_ = true;
    }
  }

} // namespace transformer_msp_bridge
