// Implements defensive little-endian readers for MSP payload parsing.
#include "transformer_msp_bridge/msp_utils.hpp"

namespace transformer_msp_bridge
{

  bool readU8(const std::vector<uint8_t> &buffer, size_t offset, uint8_t &out)
  {
    if (buffer.size() < offset + 1)
      return false;
    out = buffer[offset];
    return true;
  }
  bool readI8(const std::vector<uint8_t> &buffer, size_t offset, int8_t &out)
  {
    if (buffer.size() < offset + 1)
      return false;
    out = static_cast<int8_t>(buffer[offset]);
    return true;
  }
  bool readU16LE(const std::vector<uint8_t> &buffer, size_t offset, uint16_t &out)
  {
    if (buffer.size() < offset + 2)
      return false;
    out = static_cast<uint16_t>(buffer[offset] | (static_cast<uint16_t>(buffer[offset + 1]) << 8));
    return true;
  }
  bool readI16LE(const std::vector<uint8_t> &buffer, size_t offset, int16_t &out)
  {
    if (buffer.size() < offset + 2)
      return false;
    out = static_cast<int16_t>(buffer[offset] | (static_cast<uint16_t>(buffer[offset + 1]) << 8));
    return true;
  }
  bool readU32LE(const std::vector<uint8_t> &buffer, size_t offset, uint32_t &out)
  {
    if (buffer.size() < offset + 4)
      return false;
    out = static_cast<uint32_t>(buffer[offset]) | (static_cast<uint32_t>(buffer[offset + 1]) << 8) |
          (static_cast<uint32_t>(buffer[offset + 2]) << 16) | (static_cast<uint32_t>(buffer[offset + 3]) << 24);
    return true;
  }
  bool readI32LE(const std::vector<uint8_t> &buffer, size_t offset, int32_t &out)
  {
    uint32_t tmp;
    if (!readU32LE(buffer, offset, tmp))
      return false;
    out = static_cast<int32_t>(tmp);
    return true;
  }

} // namespace transformer_msp_bridge
