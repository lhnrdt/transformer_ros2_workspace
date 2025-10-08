#include <gtest/gtest.h>
#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/msp_builders.hpp"
#include <vector>
#include <cstdint>

using namespace transformer_msp_bridge;

struct CapturedPacket
{
  MSPPacket pkt;
};

class MSPParserFixture : public ::testing::Test
{
protected:
  void SetUp() override
  {
    packets_.clear();
    parser_ = std::make_unique<MSPParser>([this](const MSPPacket &p)
                                          { packets_.push_back({p}); });
  }
  std::unique_ptr<MSPParser> parser_;
  std::vector<CapturedPacket> packets_;
  void feed(const std::vector<uint8_t> &bytes)
  {
    for (auto b : bytes)
      parser_->input(b);
  }
};

TEST_F(MSPParserFixture, V1SimplePacket)
{
  auto frame = buildPacketRaw(42, {0x11, 0x22, 0x33});
  feed(frame);
  ASSERT_EQ(packets_.size(), 1u);
  const auto &p = packets_[0].pkt;
  EXPECT_EQ(p.version, MSPVersion::V1);
  EXPECT_EQ(p.cmd, 42u);
  ASSERT_EQ(p.payload.size(), 3u);
  EXPECT_EQ(p.payload[0], 0x11);
  EXPECT_EQ(p.payload[1], 0x22);
  EXPECT_EQ(p.payload[2], 0x33);
  EXPECT_FALSE(p.tunneled);
}

TEST_F(MSPParserFixture, V2NativePacket)
{
  auto frame = buildPacketV2(0x1234, {0xAA, 0x55}, 0x07);
  feed(frame);
  ASSERT_EQ(packets_.size(), 1u);
  const auto &p = packets_[0].pkt;
  EXPECT_EQ(p.version, MSPVersion::V2);
  EXPECT_EQ(p.cmd, 0x1234u);
  EXPECT_EQ(p.flags, 0x07);
  ASSERT_EQ(p.payload.size(), 2u);
  EXPECT_EQ(p.payload[0], 0xAA);
  EXPECT_EQ(p.payload[1], 0x55);
  EXPECT_FALSE(p.tunneled);
  EXPECT_EQ(parser_->stats().native_v2_rx, 1u);
}

TEST_F(MSPParserFixture, V2TunneledPacket)
{
  auto frame = buildPacketV2OverV1(0x2222, {0x10, 0x20, 0x30}, 0x01);
  feed(frame);
  ASSERT_EQ(packets_.size(), 1u);
  const auto &p = packets_[0].pkt;
  EXPECT_EQ(p.version, MSPVersion::V2);
  EXPECT_TRUE(p.tunneled);
  EXPECT_EQ(p.cmd, 0x2222u);
  EXPECT_EQ(p.flags, 0x01);
  ASSERT_EQ(p.payload.size(), 3u);
  EXPECT_EQ(p.payload[0], 0x10);
  EXPECT_EQ(p.payload[1], 0x20);
  EXPECT_EQ(p.payload[2], 0x30);
  EXPECT_EQ(parser_->stats().tunneled_v2_rx, 1u);
}

TEST_F(MSPParserFixture, NativeV2CrcFailure)
{
  auto frame = buildPacketV2(0x0102, {0x01, 0x02, 0x03}, 0x00);
  // Corrupt last CRC byte
  frame.back() ^= 0xFF;
  feed(frame);
  EXPECT_EQ(packets_.size(), 0u);
  EXPECT_EQ(parser_->stats().native_v2_crc_fail, 1u);
}

TEST_F(MSPParserFixture, TunneledV2CrcFailure)
{
  auto frame = buildPacketV2OverV1(0x0A0B, {0x09, 0x08}, 0x02);
  // Layout: ['$','M','<', size, 255, inner..., v1_checksum]
  // inner := flags(1) + cmdL + cmdH + lenL + lenH + payload + inner_crc (crc8 over header+payload)
  // We corrupt ONLY the inner CRC but recompute the outer v1 checksum so that the v1 frame is accepted
  // and the parser reaches the tunneled v2 CRC validation path (incrementing tunneled_v2_crc_fail).
  if (frame.size() > 7)
  { // ensure enough bytes
    uint8_t size_field = frame[3];
    size_t inner_start = 5;
    size_t inner_len = size_field;                        // number of inner bytes
    size_t inner_crc_index = inner_start + inner_len - 1; // last byte of inner = crc8
    // Flip inner CRC bit pattern
    frame[inner_crc_index] ^= 0xFF;
    // Recompute outer v1 checksum: XOR of size, cmd(255), and all inner bytes
    uint8_t cs = size_field ^ frame[4];
    for (size_t i = inner_start; i < inner_start + inner_len; ++i)
      cs ^= frame[i];
    frame.back() = cs; // overwrite stored checksum
  }
  feed(frame);
  EXPECT_EQ(packets_.size(), 0u);
  EXPECT_EQ(parser_->stats().tunneled_v2_crc_fail, 1u);
}

TEST_F(MSPParserFixture, PartialFrameNoEmit)
{
  auto frame = buildPacketRaw(10, {0x01, 0x02, 0x03, 0x04});
  // feed all but checksum
  ASSERT_GE(frame.size(), 1u);
  for (size_t i = 0; i + 1 < frame.size(); ++i)
    parser_->input(frame[i]);
  EXPECT_EQ(packets_.size(), 0u);
}

TEST_F(MSPParserFixture, MultipleFramesSequence)
{
  auto f1 = buildPacketRaw(1, {0x01});
  auto f2 = buildPacketV2(0x0203, {}); // empty payload
  auto f3 = buildPacketV2OverV1(0x0405, {0xAA});
  std::vector<uint8_t> all;
  all.insert(all.end(), f1.begin(), f1.end());
  all.insert(all.end(), f2.begin(), f2.end());
  all.insert(all.end(), f3.begin(), f3.end());
  feed(all);
  ASSERT_EQ(packets_.size(), 3u);
  EXPECT_EQ(packets_[0].pkt.version, MSPVersion::V1);
  EXPECT_EQ(packets_[1].pkt.version, MSPVersion::V2);
  EXPECT_FALSE(packets_[1].pkt.tunneled);
  EXPECT_TRUE(packets_[2].pkt.tunneled);
  EXPECT_EQ(parser_->stats().native_v2_rx, 1u);
  EXPECT_EQ(parser_->stats().tunneled_v2_rx, 1u);
}
