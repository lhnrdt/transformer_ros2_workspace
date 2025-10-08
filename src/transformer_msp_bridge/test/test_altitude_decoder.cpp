#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float32.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include "transformer_msp_bridge/decoders/altitude_decoder.hpp"

using namespace transformer_msp_bridge;

static void spin_for(rclcpp::Node::SharedPtr node, int ms = 60)
{
  auto start = std::chrono::steady_clock::now();
  rclcpp::executors::SingleThreadedExecutor exec;
  exec.add_node(node);
  while ((std::chrono::steady_clock::now() - start) < std::chrono::milliseconds(ms))
  {
    exec.spin_some();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
}

TEST(AltitudeDecoder, BasicScaling)
{
  auto node = std::make_shared<rclcpp::Node>("altitude_decoder_test");
  AltitudeDecoder decoder(*node);
  std_msgs::msg::Float32::SharedPtr alt_msg;
  geometry_msgs::msg::TwistStamped::SharedPtr vs_msg;
  auto sub_alt = node->create_subscription<std_msgs::msg::Float32>("/msp/altitude", 10, [&](std_msgs::msg::Float32::SharedPtr m)
                                                                   { alt_msg = m; });
  auto sub_vs = node->create_subscription<geometry_msgs::msg::TwistStamped>("/msp/vertical_speed", 10, [&](geometry_msgs::msg::TwistStamped::SharedPtr m)
                                                                            { vs_msg = m; });
  MSPPacket pkt;
  pkt.cmd = MSP_ALTITUDE;
  int32_t alt_cm = 12345; // 123.45 m
  int16_t vs_cms = -250;  // -2.50 m/s
  pkt.payload = {
      (uint8_t)(alt_cm & 0xFF), (uint8_t)((alt_cm >> 8) & 0xFF), (uint8_t)((alt_cm >> 16) & 0xFF), (uint8_t)((alt_cm >> 24) & 0xFF),
      (uint8_t)(vs_cms & 0xFF), (uint8_t)((vs_cms >> 8) & 0xFF)};
  decoder.decode(pkt);
  spin_for(node);
  ASSERT_TRUE(alt_msg);
  EXPECT_NEAR(alt_msg->data, 123.45f, 1e-4);
  ASSERT_TRUE(vs_msg);
  EXPECT_NEAR(vs_msg->twist.linear.z, -2.50, 1e-4);
}

TEST(AltitudeDecoder, ShortPayloadIgnored)
{
  auto node = std::make_shared<rclcpp::Node>("altitude_decoder_short_test");
  AltitudeDecoder decoder(*node);
  std_msgs::msg::Float32::SharedPtr alt_msg;
  auto sub_alt = node->create_subscription<std_msgs::msg::Float32>("/msp/altitude", 10, [&](std_msgs::msg::Float32::SharedPtr m)
                                                                   { alt_msg = m; });
  MSPPacket pkt;
  pkt.cmd = MSP_ALTITUDE;
  pkt.payload = {0x01, 0x02, 0x03};
  decoder.decode(pkt);
  spin_for(node);
  EXPECT_FALSE(alt_msg);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  rclcpp::init(argc, argv);
  int r = RUN_ALL_TESTS();
  rclcpp::shutdown();
  return r;
}
