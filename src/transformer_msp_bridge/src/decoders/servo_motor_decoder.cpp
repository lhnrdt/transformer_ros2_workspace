#include "transformer_msp_bridge/decoders/servo_motor_decoder.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include <utility>

namespace transformer_msp_bridge
{

  namespace
  {
  const uint16_t kMspServo = msp::command_id("MSP_SERVO");
  const uint16_t kMspMotor = msp::command_id("MSP_MOTOR");
  }

  ServoMotorDecoder::ServoMotorDecoder(Callbacks callbacks) : callbacks_(std::move(callbacks)) {}

  void ServoMotorDecoder::set_callbacks(Callbacks callbacks) { callbacks_ = std::move(callbacks); }

  bool ServoMotorDecoder::matches(uint16_t id) const { return id == kMspServo || id == kMspMotor; }
  std::string ServoMotorDecoder::name() const { return "servo_motor"; }

  void ServoMotorDecoder::decode(const MSPPacket &pkt)
  {
    if (pkt.cmd == kMspServo)
      decodeServo(pkt);
    else if (pkt.cmd == kMspMotor)
      decodeMotor(pkt);
  }

  void ServoMotorDecoder::decodeServo(const MSPPacket &pkt)
  {
    size_t n = pkt.payload.size() / 2;
    if (!n)
      return;
    ServoPositionData data;
    data.positions.reserve(n);
    for (size_t i = 0; i < n; i++)
    {
      uint16_t v = pkt.payload[2 * i] | (pkt.payload[2 * i + 1] << 8);
      data.positions.push_back(static_cast<double>(v));
    }
    if (callbacks_.servo)
      callbacks_.servo(data);
  }

  void ServoMotorDecoder::decodeMotor(const MSPPacket &pkt)
  {
    size_t n = pkt.payload.size() / 2;
    if (!n)
      return;
    MotorOutputData data;
    data.values.reserve(n);
    for (size_t i = 0; i < n; i++)
    {
      uint16_t v = pkt.payload[2 * i] | (pkt.payload[2 * i + 1] << 8);
      data.values.push_back(static_cast<double>(v));
    }
    if (callbacks_.motor)
      callbacks_.motor(data);
  }

} // namespace transformer_msp_bridge
