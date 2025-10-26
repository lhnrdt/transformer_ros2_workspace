#pragma once

#include "transformer_msp_bridge/decoder_base.hpp"
#include "transformer_msp_bridge/decoder_outputs.hpp"
#include "transformer_msp_bridge/msp_parser.hpp"
#include <functional>
#include <string>

namespace transformer_msp_bridge
{

  class SensorDecoder : public IMspDecoder
  {
  public:
    using RangefinderCallback = std::function<void(const RangefinderSample &)>;
    using CompassCallback = std::function<void(const CompassSample &)>;
    using BarometerCallback = std::function<void(const BarometerSample &)>;

    struct Callbacks
    {
      RangefinderCallback rangefinder{};
      CompassCallback compass{};
      BarometerCallback barometer{};
      std::function<void(const std::string &)> log_info{};
      bool log_first_frame{false};
    };

  SensorDecoder();
  explicit SensorDecoder(Callbacks callbacks);
    void set_callbacks(Callbacks callbacks);
    void decode(const MSPPacket &pkt) override;
    bool matches(uint16_t id) const override;
    std::string name() const override;

  private:
    void decodeRangefinder(const MSPPacket &pkt);
    void decodeCompass(const MSPPacket &pkt);
    void decodeBarometer(const MSPPacket &pkt);
    Callbacks callbacks_{};
    bool logged_rangefinder_{false};
    bool logged_compass_{false};
    bool logged_baro_{false};
  };

} // namespace transformer_msp_bridge
