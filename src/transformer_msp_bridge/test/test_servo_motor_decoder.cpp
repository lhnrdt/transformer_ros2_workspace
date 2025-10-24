#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <vector>
#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/decoders/servo_motor_decoder.hpp"
#include "schema_expectations.hpp"

using transformer_msp_bridge::MSPPacket;
using transformer_msp_bridge::ServoMotorDecoder;
using transformer_msp_bridge::test_utils::expect_payload_matches_schema;

class ServoMotorDecoderFixture : public ::testing::Test
{
protected:
  void SetUp() override
  {
    rclcpp::init(0, nullptr);
    node_ = std::make_shared<rclcpp::Node>("servo_motor_decoder_test");
  }
  void TearDown() override { rclcpp::shutdown(); }
  std::shared_ptr<rclcpp::Node> node_;
};

static void spin_for(std::shared_ptr<rclcpp::Node> node, int ms = 50)
{
  rclcpp::executors::SingleThreadedExecutor ex;
  ex.add_node(node);
  auto start = std::chrono::steady_clock::now();
  while (std::chrono::steady_clock::now() - start < std::chrono::milliseconds(ms))
  {
    ex.spin_some();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

TEST_F(ServoMotorDecoderFixture, ServoPositionsDecoded)
{
  ServoMotorDecoder decoder(*node_);
  sensor_msgs::msg::JointState::SharedPtr last;
  auto sub = node_->create_subscription<sensor_msgs::msg::JointState>("/msp/servo", 10,
                                                                      [&last](sensor_msgs::msg::JointState::ConstSharedPtr m)
                                                                      { last = std::make_shared<sensor_msgs::msg::JointState>(*m); });
  // Three servo values: 1000, 1500, 2000
  MSPPacket pkt;
  pkt.cmd = MSP_SERVO;
  pkt.payload = {0xE8, 0x03, 0xDC, 0x05, 0xD0, 0x07}; // little-endian
  decoder.decode(pkt);
  spin_for(node_);
  ASSERT_TRUE(last);
  ASSERT_EQ(last->position.size(), 3u);
  EXPECT_NEAR(last->position[0], 1000.0, 1e-6);
  EXPECT_NEAR(last->position[1], 1500.0, 1e-6);
  EXPECT_NEAR(last->position[2], 2000.0, 1e-6);
}

TEST_F(ServoMotorDecoderFixture, MotorVelocitiesDecoded)
{
  ServoMotorDecoder decoder(*node_);
  sensor_msgs::msg::JointState::SharedPtr last;
  auto sub = node_->create_subscription<sensor_msgs::msg::JointState>("/msp/motor", 10,
                                                                      [&last](sensor_msgs::msg::JointState::ConstSharedPtr m)
                                                                      { last = std::make_shared<sensor_msgs::msg::JointState>(*m); });
  // Four motor values: 1100, 1200, 1300, 1400
  MSPPacket pkt;
  pkt.cmd = MSP_MOTOR;
  pkt.payload = {0x4C, 0x04, 0xB0, 0x04, 0x14, 0x05, 0x78, 0x05};
  expect_payload_matches_schema(MSP_MOTOR, pkt.payload);
  decoder.decode(pkt);
  spin_for(node_);
  ASSERT_TRUE(last);
  ASSERT_EQ(last->velocity.size(), 4u);
  EXPECT_NEAR(last->velocity[0], 1100.0, 1e-6);
  EXPECT_NEAR(last->velocity[1], 1200.0, 1e-6);
  EXPECT_NEAR(last->velocity[2], 1300.0, 1e-6);
  EXPECT_NEAR(last->velocity[3], 1400.0, 1e-6);
}

TEST_F(ServoMotorDecoderFixture, ShortPayloadIgnored)
{
  ServoMotorDecoder decoder(*node_);
  sensor_msgs::msg::JointState::SharedPtr servoMsg;
  auto sub = node_->create_subscription<sensor_msgs::msg::JointState>("/msp/servo", 10,
                                                                      [&servoMsg](sensor_msgs::msg::JointState::ConstSharedPtr m)
                                                                      { servoMsg = std::make_shared<sensor_msgs::msg::JointState>(*m); });
  MSPPacket pkt;
  pkt.cmd = MSP_SERVO;
  pkt.payload = {0xE8}; // odd length -> n=0 when integer division by 2? Actually size/2 ==0
  decoder.decode(pkt);
  spin_for(node_);
  EXPECT_FALSE(servoMsg);
}
