#include "transformer_msp_bridge/decoders/rc_decoder.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include <utility>

namespace transformer_msp_bridge
{

  namespace
  {
  const uint16_t kMspRc = msp::command_id("MSP_RC");
  }

  RcDecoder::RcDecoder(Callback callback) : callback_(std::move(callback)) {}

  void RcDecoder::set_callback(Callback callback) { callback_ = std::move(callback); }

  bool RcDecoder::matches(uint16_t id) const { return id == kMspRc; }
  std::string RcDecoder::name() const { return "rc"; }

  void RcDecoder::decode(const MSPPacket &pkt)
  {
    if (pkt.cmd != kMspRc || pkt.payload.size() < 16)
      return;
    std::vector<uint16_t> chans;
    chans.reserve(pkt.payload.size() / 2);
    for (size_t i = 0; i + 1 < pkt.payload.size(); i += 2)
    {
      chans.push_back(pkt.payload[i] | (pkt.payload[i + 1] << 8));
    }
    RcChannelsData data;
    data.channels = std::move(chans);
    if (callback_)
      callback_(data);
  }

} // namespace transformer_msp_bridge
