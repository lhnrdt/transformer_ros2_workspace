#pragma once

#include "transformer_msp_bridge/decoder_base.hpp"
#include "transformer_msp_bridge/decoder_outputs.hpp"
#include <functional>

namespace transformer_msp_bridge
{

  // Minimal decoder for assorted MSPv2 INAV telemetry frames we poll by default.
  // Publishes a DiagnosticArray with a single DiagnosticStatus per frame type,
  // containing a hex-encoded raw payload to avoid "no decoder" warnings while
  // keeping implementation simple.
  class InavGenericDecoder : public IMspDecoder
  {
  public:
    using FrameCallback = std::function<void(const InavGenericFrame &)>;

    explicit InavGenericDecoder(FrameCallback callback = {});
    void set_callback(FrameCallback callback);

    bool matches(uint16_t command_id) const override;
    void decode(const MSPPacket &pkt) override;
    std::string name() const override { return "inav_generic"; }

  private:
    void publishRaw(const MSPPacket &pkt, const std::string &title);

    FrameCallback callback_{};
  };

} // namespace transformer_msp_bridge
