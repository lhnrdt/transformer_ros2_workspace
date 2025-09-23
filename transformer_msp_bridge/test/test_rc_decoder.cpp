#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/u_int16_multi_array.hpp>
#include "transformer_msp_bridge/decoders/rc_decoder.hpp"

using namespace transformer_msp_bridge;

static void spin_for(rclcpp::Node::SharedPtr node, int ms=60) {
  auto start = std::chrono::steady_clock::now();
  rclcpp::executors::SingleThreadedExecutor exec; exec.add_node(node);
  while ((std::chrono::steady_clock::now() - start) < std::chrono::milliseconds(ms)) { exec.spin_some(); std::this_thread::sleep_for(std::chrono::milliseconds(5)); }
}

TEST(RcDecoder, RcChannelsBasic) {
  auto node = std::make_shared<rclcpp::Node>("rc_decoder_test");
  RcDecoder decoder(*node, "/msp/rc");
  std_msgs::msg::UInt16MultiArray::SharedPtr last;
  auto sub = node->create_subscription<std_msgs::msg::UInt16MultiArray>("/msp/rc",10,
    [&](std_msgs::msg::UInt16MultiArray::SharedPtr m){ last = m; });
  MSPPacket pkt; pkt.cmd = MSP_RC;
  // 8 channels: 1000..1700 step 100
  for (uint16_t v=1000; v<1800; v+=100) { pkt.payload.push_back(v & 0xFF); pkt.payload.push_back((v>>8)&0xFF); }
  decoder.decode(pkt);
  spin_for(node);
  ASSERT_TRUE(last);
  ASSERT_EQ(last->data.size(), 8u);
  for (size_t i=0;i<8;i++) {
    EXPECT_EQ(last->data[i], 1000 + i*100);
  }
}

TEST(RcDecoder, ShortPayloadIgnored) {
  auto node = std::make_shared<rclcpp::Node>("rc_decoder_short_test");
  RcDecoder decoder(*node, "/msp/rc2");
  std_msgs::msg::UInt16MultiArray::SharedPtr last;
  auto sub = node->create_subscription<std_msgs::msg::UInt16MultiArray>("/msp/rc2",10,
    [&](std_msgs::msg::UInt16MultiArray::SharedPtr m){ last = m; });
  MSPPacket pkt; pkt.cmd = MSP_RC; pkt.payload = { 0xE8, 0x03, 0xF4 }; // 3 bytes (<16) should ignore
  decoder.decode(pkt);
  spin_for(node);
  EXPECT_FALSE(last);
}

int main(int argc, char **argv) { testing::InitGoogleTest(&argc, argv); rclcpp::init(argc, argv); int r = RUN_ALL_TESTS(); rclcpp::shutdown(); return r; }
