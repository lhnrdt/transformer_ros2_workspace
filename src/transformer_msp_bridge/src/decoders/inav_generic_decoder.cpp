#include "transformer_msp_bridge/decoders/inav_generic_decoder.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include <utility>

namespace transformer_msp_bridge
{

  namespace
  {
  const uint16_t kMsp2InavAnalog = msp::command_id("MSP2_INAV_ANALOG");
  const uint16_t kMsp2InavBatteryConfig = msp::command_id("MSP2_INAV_BATTERY_CONFIG");
  const uint16_t kMsp2InavAirSpeed = msp::command_id("MSP2_INAV_AIR_SPEED");
  const uint16_t kMsp2InavTemperatures = msp::command_id("MSP2_INAV_TEMPERATURES");
  const uint16_t kMsp2InavEscRpm = msp::command_id("MSP2_INAV_ESC_RPM");
  }

  InavGenericDecoder::InavGenericDecoder(FrameCallback callback) : callback_(std::move(callback)) {}

  void InavGenericDecoder::set_callback(FrameCallback callback) { callback_ = std::move(callback); }

  bool InavGenericDecoder::matches(uint16_t command_id) const
  {
    return command_id == kMsp2InavAnalog || command_id == kMsp2InavBatteryConfig ||
           command_id == kMsp2InavAirSpeed || command_id == kMsp2InavTemperatures ||
           command_id == kMsp2InavEscRpm;
  }

  void InavGenericDecoder::publishRaw(const MSPPacket &pkt, const std::string &title)
  {
    if (!callback_)
      return;
    InavGenericFrame frame;
    frame.command_id = pkt.cmd;
    frame.description = title;
    frame.payload = pkt.payload;
    callback_(frame);
  }

  void InavGenericDecoder::decode(const MSPPacket &pkt)
  {
    if (pkt.cmd == kMsp2InavAnalog)
    {
      publishRaw(pkt, "inav_analog");
    }
    else if (pkt.cmd == kMsp2InavBatteryConfig)
    {
      publishRaw(pkt, "inav_battery_config");
    }
    else if (pkt.cmd == kMsp2InavAirSpeed)
    {
      publishRaw(pkt, "inav_air_speed");
    }
    else if (pkt.cmd == kMsp2InavTemperatures)
    {
      publishRaw(pkt, "inav_temperatures");
    }
    else if (pkt.cmd == kMsp2InavEscRpm)
    {
      publishRaw(pkt, "inav_esc_rpm");
    }
  }

} // namespace transformer_msp_bridge
