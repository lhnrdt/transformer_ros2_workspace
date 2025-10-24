#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/vector3.hpp>
#include <chrono>
#include <thread>
#include <vector>
#include "transformer_msp_bridge/decoders/attitude_decoder.hpp"
#include "schema_expectations.hpp"

using namespace transformer_msp_bridge;
using transformer_msp_bridge::test_utils::expect_payload_matches_schema;

static void spin_for(rclcpp::Node::SharedPtr node, int ms = 50)
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

TEST(AttitudeDecoder, BasicScaling)
{
  auto node = std::make_shared<rclcpp::Node>("attitude_decoder_test");
  AttitudeDecoder decoder(*node);

  geometry_msgs::msg::Vector3::SharedPtr last;
  auto sub = node->create_subscription<geometry_msgs::msg::Vector3>("/msp/attitude", 10,
                                                                    [&](geometry_msgs::msg::Vector3::SharedPtr msg)
                                                                    { last = msg; });

  // roll=123.4deg, pitch=-56.7deg, yaw=45.0deg -> scaled by *10 in payload as int16
  int16_t roll = (int16_t)(1234);
  int16_t pitch = (int16_t)(-567);
  int16_t yaw = (int16_t)(450);
  MSPPacket pkt;
  pkt.cmd = MSP_ATTITUDE;
  const std::vector<uint8_t> payload = {
    static_cast<uint8_t>(roll & 0xFF), static_cast<uint8_t>((roll >> 8) & 0xFF),
    static_cast<uint8_t>(pitch & 0xFF), static_cast<uint8_t>((pitch >> 8) & 0xFF),
    static_cast<uint8_t>(yaw & 0xFF), static_cast<uint8_t>((yaw >> 8) & 0xFF)};
  expect_payload_matches_schema(MSP_ATTITUDE, payload);
  pkt.payload = payload;
  decoder.decode(pkt);
  spin_for(node);
  ASSERT_TRUE(last);
  EXPECT_NEAR(last->x, 123.4, 1e-3);
  EXPECT_NEAR(last->y, -56.7, 1e-3);
  EXPECT_NEAR(last->z, 45.0, 1e-3);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  rclcpp::init(argc, argv);
  int ret = RUN_ALL_TESTS();
  rclcpp::shutdown();
  return ret;
}
