#include "transformer_msp_bridge/msp_utils.hpp"

namespace transformer_msp_bridge {

uint16_t readUint16LE(const std::vector<uint8_t>& buffer, size_t offset) {
    if (buffer.size() < offset + 2) return 0;
    return static_cast<uint16_t>(buffer[offset] | (static_cast<uint16_t>(buffer[offset + 1]) << 8));
}

} // namespace transformer_msp_bridge
