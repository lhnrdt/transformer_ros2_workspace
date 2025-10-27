// Declares the MSP RC channels decoder for servo input telemetry.
#pragma once
#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/decoder_base.hpp"
#include "transformer_msp_bridge/decoder_outputs.hpp"
#include <functional>
namespace transformer_msp_bridge
{
  class RcDecoder : public IMspDecoder
  {
  public:
    using Callback = std::function<void(const RcChannelsData &)>;

    explicit RcDecoder(Callback callback = {});
    void set_callback(Callback callback);
    void decode(const MSPPacket &pkt) override;
    bool matches(uint16_t command_id) const override;
    std::string name() const override;

  private:
    Callback callback_;
  };
} // namespace transformer_msp_bridge
