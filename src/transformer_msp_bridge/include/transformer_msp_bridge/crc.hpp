// Declares CRC8 (DVB-S2 polynomial) utilities used to validate MSP frames.
#pragma once
#include <cstdint>
#include <vector>

namespace transformer_msp_bridge
{
    namespace crc8_dvb_s2
    {

        static constexpr uint8_t POLY = 0xD5;

        // Incrementally update a CRC with one byte.
        uint8_t update(uint8_t crc, uint8_t data);

        // Compute CRC over a contiguous raw buffer.
        uint8_t compute(const uint8_t *data, size_t length, uint8_t seed = 0);

        // Compute CRC over a std::vector buffer wrapper.
        uint8_t compute(const std::vector<uint8_t> &buffer, uint8_t seed = 0);

    } // namespace crc8_dvb_s2
} // namespace transformer_msp_bridge
