#pragma once

#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/decoder_base.hpp"
#include "transformer_msp_bridge/decoder_outputs.hpp"
#include <functional>

namespace transformer_msp_bridge
{

  class ServoMotorDecoder : public IMspDecoder
  {
  public:
    using ServoCallback = std::function<void(const ServoPositionData &)>;
    using MotorCallback = std::function<void(const MotorOutputData &)>;

    struct Callbacks
    {
      ServoCallback servo;
      MotorCallback motor;
    };

    explicit ServoMotorDecoder(Callbacks callbacks = {});
    void set_callbacks(Callbacks callbacks);
    void decode(const MSPPacket &pkt) override;
    bool matches(uint16_t command_id) const override;
    std::string name() const override;

  private:
    void decodeServo(const MSPPacket &pkt);
    void decodeMotor(const MSPPacket &pkt);
    Callbacks callbacks_{};
  };

} // namespace transformer_msp_bridge
