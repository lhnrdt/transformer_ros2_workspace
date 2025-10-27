// Declares decoders for MSP analog and battery status telemetry.
#pragma once
#include "transformer_msp_bridge/decoder_base.hpp"
#include "transformer_msp_bridge/decoder_outputs.hpp"
#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include <functional>
#include <optional>
namespace transformer_msp_bridge
{
  class BatteryDecoder : public IMspDecoder
  {
  public:
    using AnalogCallback = std::function<void(const BatteryAnalogData &)>;
    using ConfigCallback = std::function<void(const BatteryConfigData &)>;

    struct Callbacks
    {
      AnalogCallback analog;
      ConfigCallback config;
    };

    explicit BatteryDecoder(Callbacks callbacks = {});
    void set_callbacks(Callbacks callbacks);
    void decodeAnalog(const MSPPacket &pkt);
    void decodeBatteryConfig(const MSPPacket &pkt);
    // IMspDecoder implementation
    bool matches(uint16_t id) const override
    {
      return id == kAnalogCommand || id == kBatteryConfigCommand;
    }
    void decode(const MSPPacket &pkt) override
    {
      if (pkt.cmd == kAnalogCommand)
        decodeAnalog(pkt);
      else if (pkt.cmd == kBatteryConfigCommand)
        decodeBatteryConfig(pkt);
    }
    std::string name() const override { return "battery"; }

  private:
  static const uint16_t kAnalogCommand;
  static const uint16_t kBatteryConfigCommand;
    Callbacks callbacks_{};
    std::optional<BatteryConfigData> last_config_{};
  };
} // namespace transformer_msp_bridge
