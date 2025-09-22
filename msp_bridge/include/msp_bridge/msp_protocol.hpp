#pragma once
#include <cstdint>
#include <vector>
#include <functional>
#include <optional>
#include <string>

namespace msp_bridge {

// Use external iNav MSP constant definitions instead of redefining IDs.
#include "msp/msp_protocol.h"

struct MSPPacket {
  uint8_t cmd{0};
  std::vector<uint8_t> payload; // raw payload bytes
};

// Callback signature for decoded packets
using PacketCallback = std::function<void(const MSPPacket&)>;

class MSPParser {
public:
  explicit MSPParser(PacketCallback cb);
  void reset();
  void input(uint8_t byte); // feed one byte
private:
  PacketCallback cb_;
  enum class State { Idle, HeaderStart, HeaderDir, Size, Cmd, Payload, Checksum } state_{State::Idle};
  uint8_t size_{0};
  uint8_t cmd_{0};
  uint8_t checksum_{0};
  std::vector<uint8_t> buf_;
};

// Build an MSP v1 packet (direction host->FC) with given command and payload.
std::vector<uint8_t> buildPacket(uint8_t cmd, const std::vector<uint16_t>& rc_values);
std::vector<uint8_t> buildPacketRaw(uint8_t cmd, const std::vector<uint8_t>& payload);

} // namespace msp_bridge
