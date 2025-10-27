#include "transformer_msp_bridge/decoders/attitude_decoder.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include "transformer_msp_bridge/msp_utils.hpp"
#include <utility>

namespace transformer_msp_bridge
{

  namespace
  {
  const uint16_t kMspAttitude = msp::command_id("MSP_ATTITUDE");
  }

  AttitudeDecoder::AttitudeDecoder(Callback callback) : callback_(std::move(callback)) {}

  void AttitudeDecoder::set_callback(Callback callback) { callback_ = std::move(callback); }

  bool AttitudeDecoder::matches(uint16_t id) const
  {
    return id == kMspAttitude;
  }
  std::string AttitudeDecoder::name() const
  {
    return "attitude";
  }

  void AttitudeDecoder::decode(const MSPPacket &pkt)
  {
    if (pkt.cmd != kMspAttitude)
      return;
    if (pkt.payload.size() < 6)
      return;
    int16_t roll, pitch, yaw;
    if (!readI16LE(pkt.payload, 0, roll) || !readI16LE(pkt.payload, 2, pitch) || !readI16LE(pkt.payload, 4, yaw))
      return;
  // MSP encodes roll and pitch in decidegrees, yaw in whole degrees.
  constexpr double kDeciDegreesToDegrees = 0.1;
  AttitudeAngles data;
  data.roll_deg = static_cast<double>(roll) * kDeciDegreesToDegrees;
  data.pitch_deg = static_cast<double>(pitch) * kDeciDegreesToDegrees;
  data.yaw_deg = static_cast<double>(yaw);
    if (callback_)
      callback_(data);
  }

} // namespace transformer_msp_bridge
