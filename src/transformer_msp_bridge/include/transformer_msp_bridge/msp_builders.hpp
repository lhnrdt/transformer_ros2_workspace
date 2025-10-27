// Declares helper functions for constructing MSP v1, v2, and tunneled frames.
#pragma once
#include <cstdint>
#include <vector>

namespace transformer_msp_bridge
{

    // Builder helpers for composing MSP frames.
    // V1: size byte, cmd (8-bit), XOR checksum.
    // V2: extended header with flags, 16-bit command & length, CRC8 DVB-S2.
    // Tunneled V2-over-V1: a V2 frame (header+payload+CRC8) transported inside a V1 frame using the MSP v2 tunnel command id.

    std::vector<uint8_t> buildPacket(uint8_t cmd, const std::vector<uint16_t> &rc_values);
    std::vector<uint8_t> buildPacketRaw(uint8_t cmd, const std::vector<uint8_t> &payload);
    std::vector<uint8_t> buildPacketV2(uint16_t command, const std::vector<uint8_t> &payload, uint8_t flags = 0);
    std::vector<uint8_t> buildPacketV2OverV1(uint16_t command, const std::vector<uint8_t> &payload, uint8_t flags = 0);

} // namespace transformer_msp_bridge
