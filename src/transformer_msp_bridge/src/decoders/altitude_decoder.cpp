#include "transformer_msp_bridge/decoders/altitude_decoder.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include "transformer_msp_bridge/msp_utils.hpp"
#include <utility>

namespace transformer_msp_bridge
{

  namespace
  {
  const uint16_t kMspAltitude = msp::command_id("MSP_ALTITUDE");
  }

  AltitudeDecoder::AltitudeDecoder(Callback callback) : callback_(std::move(callback)) {}

  void AltitudeDecoder::set_callback(Callback callback) { callback_ = std::move(callback); }

  bool AltitudeDecoder::matches(uint16_t id) const
  {
    return id == kMspAltitude;
  }
  std::string AltitudeDecoder::name() const
  {
    return "altitude";
  }

  void AltitudeDecoder::decode(const MSPPacket &pkt)
  {
    decodeAltitude(pkt);
  }

  void AltitudeDecoder::decodeAltitude(const MSPPacket &pkt)
  {
    if (pkt.cmd != kMspAltitude)
      return;
    if (pkt.payload.size() < 10)
      return;
    int32_t alt_cm;
    int16_t vs_cms;
    int32_t baro_cm;
    if (!readI32LE(pkt.payload, 0, alt_cm) || !readI16LE(pkt.payload, 4, vs_cms) ||
        !readI32LE(pkt.payload, 6, baro_cm))
      return;
    AltitudeSample sample;
    sample.altitude_m = static_cast<float>(alt_cm) / 100.0F;
    sample.vertical_speed_mps = static_cast<float>(vs_cms) / 100.0F;
    sample.baro_altitude_m = static_cast<float>(baro_cm) / 100.0F;
    if (callback_)
      callback_(sample);
  }

} // namespace transformer_msp_bridge
