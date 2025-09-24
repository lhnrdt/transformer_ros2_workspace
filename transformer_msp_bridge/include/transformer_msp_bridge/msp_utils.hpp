#pragma once
#include <cstdint>
#include <vector>

namespace transformer_msp_bridge {

// Safe little-endian readers with bounds checking. Return false if out-of-range.
bool readU8(const std::vector<uint8_t>& buffer, size_t offset, uint8_t& out);
bool readI8(const std::vector<uint8_t>& buffer, size_t offset, int8_t& out);
bool readU16LE(const std::vector<uint8_t>& buffer, size_t offset, uint16_t& out);
bool readI16LE(const std::vector<uint8_t>& buffer, size_t offset, int16_t& out);
bool readU32LE(const std::vector<uint8_t>& buffer, size_t offset, uint32_t& out);
bool readI32LE(const std::vector<uint8_t>& buffer, size_t offset, int32_t& out);

}  // namespace transformer_msp_bridge
