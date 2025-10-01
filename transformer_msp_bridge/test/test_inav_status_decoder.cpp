#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/decoders/inav_status_decoder.hpp"
#include "transformer_msp_bridge/msg/msp_inav_status.hpp"

using transformer_msp_bridge::InavStatusDecoder;
using transformer_msp_bridge::MSPPacket;

class InavStatusDecoderFixture : public ::testing::Test
{
protected:
  void SetUp() override
  {
    rclcpp::init(0, nullptr);
    node_ = std::make_shared<rclcpp::Node>("inav_status_decoder_test");
  }
  void TearDown() override
  {
    rclcpp::shutdown();
  }
  std::shared_ptr<rclcpp::Node> node_;
};

static void spin_for_messages(std::shared_ptr<rclcpp::Node> node, int ms = 50)
{
  auto start = std::chrono::steady_clock::now();
  rclcpp::executors::SingleThreadedExecutor exec;
  exec.add_node(node);
  while (std::chrono::steady_clock::now() - start < std::chrono::milliseconds(ms))
  {
    exec.spin_some();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

TEST_F(InavStatusDecoderFixture, BasicDecoding)
{
  InavStatusDecoder decoder(*node_, false);
  auto sub = node_->create_subscription<transformer_msp_bridge::msg::MspInavStatus>(
      "/msp/inav_status", 10,
      [](transformer_msp_bridge::msg::MspInavStatus::ConstSharedPtr) {});

  transformer_msp_bridge::msg::MspInavStatus::SharedPtr received;
  auto sub2 = node_->create_subscription<transformer_msp_bridge::msg::MspInavStatus>(
      "/msp/inav_status", 10,
      [&received](transformer_msp_bridge::msg::MspInavStatus::ConstSharedPtr msg)
      { received = std::make_shared<transformer_msp_bridge::msg::MspInavStatus>(*msg); });

  // Build payload:
  // cycle(2) i2c(2) sensor(2) cpu(2) profileBatt(1) armingFlags(4) activeModes(N) mixerProfile(1)
  uint16_t cycle = 1500, i2c = 3, sensor = 0x1234, cpu = 42;
  uint8_t profile = 2, batt = 5; // packed: low nibble config_profile, high nibble battery_profile
  uint8_t profileBatt = (uint8_t)((batt << 4) | (profile & 0x0F));
  uint32_t armingFlags = 0xA5A5C3F0;
  std::vector<uint8_t> activeModes = {0x10, 0x02, 0x7F};
  uint8_t mixerProfile = 7;

  std::vector<uint8_t> payload;
  auto push16 = [&](uint16_t v)
  { payload.push_back(v & 0xFF); payload.push_back((v>>8)&0xFF); };
  push16(cycle);
  push16(i2c);
  push16(sensor);
  push16(cpu);
  payload.push_back(profileBatt);
  payload.push_back(armingFlags & 0xFF);
  payload.push_back((armingFlags >> 8) & 0xFF);
  payload.push_back((armingFlags >> 16) & 0xFF);
  payload.push_back((armingFlags >> 24) & 0xFF);
  payload.insert(payload.end(), activeModes.begin(), activeModes.end());
  payload.push_back(mixerProfile);

  MSPPacket pkt;
  pkt.cmd = MSP2_INAV_STATUS;
  pkt.payload = payload;
  decoder.decode(pkt);

  spin_for_messages(node_);
  ASSERT_TRUE(received);
  EXPECT_EQ(received->cycle_time_us, cycle);
  EXPECT_EQ(received->i2c_errors, i2c);
  EXPECT_EQ(received->sensor_status, sensor);
  EXPECT_EQ(received->cpu_load_percent, cpu);
  EXPECT_EQ(received->config_profile, profile);
  EXPECT_EQ(received->battery_profile, batt);
  EXPECT_EQ(received->arming_flags, armingFlags);
  ASSERT_EQ(received->active_modes.size(), activeModes.size());
  for (size_t i = 0; i < activeModes.size(); ++i)
    EXPECT_EQ(received->active_modes[i], activeModes[i]);
  EXPECT_EQ(received->mixer_profile, mixerProfile);
}

TEST_F(InavStatusDecoderFixture, ShortPayloadIgnored)
{
  InavStatusDecoder decoder(*node_, false);
  transformer_msp_bridge::msg::MspInavStatus::SharedPtr received;
  auto sub = node_->create_subscription<transformer_msp_bridge::msg::MspInavStatus>(
      "/msp/inav_status", 10,
      [&received](transformer_msp_bridge::msg::MspInavStatus::ConstSharedPtr msg)
      { received = std::make_shared<transformer_msp_bridge::msg::MspInavStatus>(*msg); });
  MSPPacket pkt;
  pkt.cmd = MSP2_INAV_STATUS;
  pkt.payload = {0x00, 0x01}; // too short
  decoder.decode(pkt);
  spin_for_messages(node_);
  EXPECT_FALSE(received);
}
