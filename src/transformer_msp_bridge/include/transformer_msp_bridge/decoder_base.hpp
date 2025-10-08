#pragma once

#include <string>
#include <cstdint>
#include "transformer_msp_bridge/msp_parser.hpp" // MSPPacket

namespace transformer_msp_bridge
{

  // Base interface for MSP decoders. Provides a uniform way to test if a decoder
  // wants to handle a command id and to invoke decoding.
  class IMspDecoder
  {
  public:
    virtual ~IMspDecoder() = default;
    // Return true if this decoder handles the given command id.
    virtual bool matches(uint16_t command_id) const = 0;
    // Decode the given packet (only called if matches() was true).
    virtual void decode(const MSPPacket &pkt) = 0;
    // Human readable name (for logging / diagnostics).
    virtual std::string name() const = 0;
  };

} // namespace transformer_msp_bridge
