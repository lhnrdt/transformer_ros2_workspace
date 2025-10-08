// CRC8 DVB-S2 implementation (polynomial 0xD5) definitions.
// Moved from header to keep headers free of executable code per project guidelines.

#include "transformer_msp_bridge/crc.hpp"

namespace transformer_msp_bridge
{
	namespace crc8_dvb_s2
	{

		uint8_t update(uint8_t crc, uint8_t data)
		{
			crc ^= data;
			for (int bit = 0; bit < 8; ++bit)
			{
				crc = (crc & 0x80) ? static_cast<uint8_t>((crc << 1) ^ POLY) : static_cast<uint8_t>(crc << 1);
			}
			return crc;
		}

		uint8_t compute(const uint8_t *data, size_t length, uint8_t seed)
		{
			uint8_t crc = seed;
			for (size_t i = 0; i < length; ++i)
			{
				crc = update(crc, data[i]);
			}
			return crc;
		}

		uint8_t compute(const std::vector<uint8_t> &buffer, uint8_t seed)
		{
			return compute(buffer.data(), buffer.size(), seed);
		}

	} // namespace crc8_dvb_s2
} // namespace transformer_msp_bridge
