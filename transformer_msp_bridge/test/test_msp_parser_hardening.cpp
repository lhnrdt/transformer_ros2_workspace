// Tests for hardening and new MSPParser features.
#include <gtest/gtest.h>
#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/msp_builders.hpp"

using namespace transformer_msp_bridge;

TEST(MSPParserHardening, MaxPayloadV1Rejected)
{
  std::vector<MSPPacket> packets;
  MSPParser parser([&](const MSPPacket &p)
                   { packets.push_back(p); });
  parser.setMaxPayloadSize(3); // small limit
  // Build a V1 frame with payload length 5
  std::vector<uint8_t> long_payload = {1, 2, 3, 4, 5};
  auto frame = buildPacketRaw(10, long_payload);
  for (auto b : frame)
    parser.input(b);
  EXPECT_TRUE(packets.empty());
  EXPECT_EQ(parser.stats().oversized_frame_dropped, 1u);
}

TEST(MSPParserHardening, MaxPayloadV2Rejected)
{
  std::vector<MSPPacket> packets;
  MSPParser parser([&](const MSPPacket &p)
                   { packets.push_back(p); });
  parser.setMaxPayloadSize(1);
  auto frame = buildPacketV2(0x1234, {0xAA, 0xBB}); // payload size 2
  for (auto b : frame)
    parser.input(b);
  EXPECT_TRUE(packets.empty());
  EXPECT_EQ(parser.stats().oversized_frame_dropped, 1u);
}

TEST(MSPParserHardening, AbortMidFrame)
{
  std::vector<MSPPacket> packets;
  MSPParser parser([&](const MSPPacket &p)
                   { packets.push_back(p); });
  auto frame = buildPacketRaw(42, {0x11, 0x22, 0x33, 0x44});
  // Feed only header + size + cmd (first 5 bytes)
  for (size_t i = 0; i < 5 && i < frame.size(); ++i)
    parser.input(frame[i]);
  bool aborted = parser.abort();
  EXPECT_TRUE(aborted);
  // Feed remainder – should be treated as new data; complete frame won't emit because partial.
  for (size_t i = 5; i < frame.size(); ++i)
    parser.input(frame[i]);
  EXPECT_TRUE(packets.empty());
  EXPECT_EQ(parser.stats().aborted_frames, 1u);
}

TEST(MSPParserHardening, ZeroCopyPayloadDuringAccumulation)
{
  std::vector<MSPPacket> packets;
  MSPParser parser([&](const MSPPacket &p)
                   { packets.push_back(p); });
  auto frame = buildPacketRaw(7, {0x01, 0x02, 0x03});
  // Feed bytes one by one, inspect zero-copy accessor for payload accumulation.
  for (size_t i = 0; i < frame.size(); ++i)
  {
    parser.input(frame[i]);
    if (i >= 6 && i < frame.size() - 1)
    { // payload region before checksum
      const uint8_t *data = parser.payloadData();
      size_t sz = parser.payloadSize();
      ASSERT_NE(data, nullptr);
      // For frame layout: indices: 0:$ 1:M 2:< 3:size 4:cmd 5:payload[0] 6:payload[1] 7:payload[2] 8:checksum
      // When i==6 -> two payload bytes processed, etc.
      size_t expected = (i - 4); // payload bytes consumed so far
      ASSERT_EQ(sz, expected);
      for (size_t k = 0; k < sz; k++)
      {
        EXPECT_EQ(data[k], (uint8_t)(k + 1));
      }
    }
  }
  ASSERT_EQ(packets.size(), 1u);
  EXPECT_EQ(packets[0].cmd, 7u);
}
