// Declares the MSP GPS decoder handling raw and home-vector telemetry.
#pragma once

#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/decoder_base.hpp"
#include "transformer_msp_bridge/decoder_outputs.hpp"
#include <functional>

namespace transformer_msp_bridge
{

  class GpsDecoder : public IMspDecoder
  {
  public:
    using RawCallback = std::function<void(const GpsRawData &)>;
    using HomeCallback = std::function<void(const GpsHomeVector &)>;

    struct Callbacks
    {
      RawCallback raw;
      HomeCallback home;
    };

    explicit GpsDecoder(Callbacks callbacks = {});
    void set_callbacks(Callbacks callbacks);
    void decode(const MSPPacket &pkt) override;
    bool matches(uint16_t command_id) const override;
    std::string name() const override;

  private:
    void decodeRawGps(const MSPPacket &pkt);
    void decodeCompGps(const MSPPacket &pkt);
    Callbacks callbacks_{};
  };

} // namespace transformer_msp_bridge
