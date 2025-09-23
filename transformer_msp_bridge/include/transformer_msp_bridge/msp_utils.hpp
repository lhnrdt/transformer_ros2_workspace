#pragma once
#include <cstdint>
#include <vector>

namespace transformer_msp_bridge {

// Read a 16-bit little-endian unsigned value from buffer at offset; returns 0 if out of range.
uint16_t readUint16LE(const std::vector<uint8_t>& buffer, size_t offset);

} // namespace transformer_msp_bridge
