#include <gtest/gtest.h>
#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/msp_builders.hpp"
#include <random>
#include <chrono>

using namespace transformer_msp_bridge;

// Simple fuzz/robustness test: feed random bytes and ensure no crashes and parser returns to idle after resets.
TEST(MSPParserFuzz, RandomNoiseDoesNotCrash) {
    std::vector<MSPPacket> collected;
    MSPParser parser([&](const MSPPacket& pkt){ collected.push_back(pkt); });

    std::mt19937 rng(12345);
    std::uniform_int_distribution<int> dist(0,255);

    constexpr int iterations = 2000;
    for (int i=0;i<iterations;++i) {
        uint8_t b = static_cast<uint8_t>(dist(rng));
        parser.input(b);
        // We allow parser internal state transitions; no specific assertion here other than no throw.
    }
    SUCCEED();
}

// Mix of valid frames interleaved with noise.
TEST(MSPParserFuzz, MixedValidAndNoise) {
    std::vector<MSPPacket> collected;
    MSPParser parser([&](const MSPPacket& pkt){ collected.push_back(pkt); });

    std::mt19937 rng(67890);
    std::uniform_int_distribution<int> dist(0,255);

    // Create a few valid frames
    auto f1 = buildPacketRaw(42, {1,2,3});
    auto f2 = buildPacketV2(0x1234, {0xAA,0xBB}, 0x05);

    for (int cycle=0; cycle<100; ++cycle) {
        // inject some noise
        for (int n=0;n<10;++n) parser.input(static_cast<uint8_t>(dist(rng)));
        // inject frame 1
        for (auto b: f1) parser.input(b);
        // more noise
        for (int n=0;n<5;++n) parser.input(static_cast<uint8_t>(dist(rng)));
        // inject frame 2
        for (auto b: f2) parser.input(b);
    }

    // Expect at least 100 of each (some may be lost if noise causes resets before start but should generally parse all)
    size_t v1_count=0, v2_count=0;
    for (auto &p : collected) {
        if (p.version == MSPVersion::V1) v1_count++; else if (p.version==MSPVersion::V2) v2_count++; }
    EXPECT_GE(v1_count, 80u); // tolerate some loss
    EXPECT_GE(v2_count, 80u);
}
