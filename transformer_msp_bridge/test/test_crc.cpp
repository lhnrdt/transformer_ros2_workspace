#include <gtest/gtest.h>
#include "transformer_msp_bridge/crc.hpp"
#include <vector>

using namespace transformer_msp_bridge;

TEST(CRCTest, KnownVector) {
    std::vector<uint8_t> data{0x01,0x02,0x03,0x04,0x05};
    // Reference CRC computed independently (polynomial 0xD5, initial 0)
    uint8_t expected = 0x6B; 
    uint8_t computed_bulk = crc8_dvb_s2::compute(data);
    EXPECT_EQ(expected, computed_bulk);

    // Incremental update path must match bulk compute
    uint8_t crc_inc = 0;
    for(uint8_t b: data) crc_inc = crc8_dvb_s2::update(crc_inc, b);
    EXPECT_EQ(expected, crc_inc);
}

TEST(CRCTest, EmptyBuffer) {
    std::vector<uint8_t> empty;
    EXPECT_EQ(0u, crc8_dvb_s2::compute(empty));
}

TEST(CRCTest, SeededConsistency) {
    std::vector<uint8_t> data{0xFF,0x00,0xA5,0x5A,0xD5};
    const uint8_t seed = 0x5A;
    uint8_t bulk = crc8_dvb_s2::compute(data.data(), data.size(), seed);
    uint8_t inc = seed;
    for(uint8_t b: data) inc = crc8_dvb_s2::update(inc, b);
    EXPECT_EQ(bulk, inc);
}

TEST(CRCTest, SingleByteAllValues) {
    // Spot check that processing a single byte matches direct expectations of manual loop
    for(int val=0; val<256; ++val) {
        uint8_t crc = 0;
        crc = crc8_dvb_s2::update(crc, static_cast<uint8_t>(val));
        // Recompute manually to validate update logic symmetry
        uint8_t manual = 0 ^ static_cast<uint8_t>(val);
        for(int i=0;i<8;++i) {
            manual = (manual & 0x80) ? static_cast<uint8_t>((manual << 1) ^ crc8_dvb_s2::POLY)
                                     : static_cast<uint8_t>(manual << 1);
        }
        EXPECT_EQ(crc, manual) << "Mismatch for byte 0x" << std::hex << val;
    }
}
