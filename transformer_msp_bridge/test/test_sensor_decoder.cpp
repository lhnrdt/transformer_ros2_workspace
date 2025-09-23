#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include "transformer_msp_bridge/msp_protocol.hpp"
#include "transformer_msp_bridge/decoders/sensor_decoder.hpp"

using transformer_msp_bridge::MSPPacket;
using transformer_msp_bridge::SensorDecoder;

class SensorDecoderFixture : public ::testing::Test {
protected:
  void SetUp() override {
    rclcpp::init(0, nullptr);
    node_ = std::make_shared<rclcpp::Node>("sensor_decoder_test");
  }
  void TearDown() override {
    rclcpp::shutdown();
  }
  std::shared_ptr<rclcpp::Node> node_;
};

static void spin_for(std::shared_ptr<rclcpp::Node> node, int ms=50){
  rclcpp::executors::SingleThreadedExecutor exec; exec.add_node(node);
  auto start=std::chrono::steady_clock::now();
  while(std::chrono::steady_clock::now()-start < std::chrono::milliseconds(ms)) {
    exec.spin_some();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

TEST_F(SensorDecoderFixture, RangefinderValidAndInvalid) {
  SensorDecoder decoder(*node_, false);
  std_msgs::msg::Float32::SharedPtr last;
  auto sub = node_->create_subscription<std_msgs::msg::Float32>("/msp/rangefinder", 10,
    [&last](std_msgs::msg::Float32::ConstSharedPtr m){ last = std::make_shared<std_msgs::msg::Float32>(*m); });

  // Structure: { uint8_t quality; int32_t distanceMm; }
  // distanceMm = 1234 (0x000004D2 little endian) quality=0x55
  MSPPacket pkt; pkt.cmd = 0x1F01; pkt.payload = { 0x55, 0xD2, 0x04, 0x00, 0x00 }; // quality + distance
  decoder.decode(pkt);
  spin_for(node_);
  ASSERT_TRUE(last);
  EXPECT_NEAR(last->data, 1.234f, 1e-3f);

  // Invalid (negative) distance => NaN. Use -1 = 0xFFFFFFFF
  MSPPacket pkt2; pkt2.cmd = 0x1F01; pkt2.payload = { 0x10, 0xFF,0xFF,0xFF,0xFF }; // quality=0x10, distance=-1
  decoder.decode(pkt2);
  spin_for(node_);
  ASSERT_TRUE(last);
  EXPECT_TRUE(std::isnan(last->data));
}

TEST_F(SensorDecoderFixture, CompassVector) {
  SensorDecoder decoder(*node_, false);
  geometry_msgs::msg::Vector3::SharedPtr v;
  auto sub = node_->create_subscription<geometry_msgs::msg::Vector3>("/msp/compass", 10,
    [&v](geometry_msgs::msg::Vector3::ConstSharedPtr m){ v = std::make_shared<geometry_msgs::msg::Vector3>(*m); });
  // typedef struct { uint8_t instance; uint32_t timeMs; int16_t magX; int16_t magY; int16_t magZ; } mspSensorCompassDataMessage_t;
  MSPPacket pkt; pkt.cmd = 0x1F04; // compass
  // instance=1, timeMs=0x00000064 (100), magX=-300 (0xFED4), magY=512 (0x0200), magZ=25 (0x0019)
  pkt.payload = { 0x01, 0x64,0x00,0x00,0x00, 0xD4,0xFE, 0x00,0x02, 0x19,0x00 };
  decoder.decode(pkt);
  spin_for(node_);
  ASSERT_TRUE(v);
  EXPECT_NEAR(v->x, -300.0, 0.1);
  EXPECT_NEAR(v->y, 512.0, 0.1);
  EXPECT_NEAR(v->z, 25.0, 0.1);
}

TEST_F(SensorDecoderFixture, BarometerPressure) {
  SensorDecoder decoder(*node_, false);
  std_msgs::msg::Float32::SharedPtr pressure;
  auto sub = node_->create_subscription<std_msgs::msg::Float32>("/msp/barometer", 10,
    [&pressure](std_msgs::msg::Float32::ConstSharedPtr m){ pressure = std::make_shared<std_msgs::msg::Float32>(*m); });
  // typedef struct { uint8_t  instance; uint32_t timeMs; float pressurePa; int16_t temp; } mspSensorBaroDataMessage_t;
  // We'll encode pressure 101325.0f (standard atm), temp=10000 -> 100.00C, instance=2, timeMs=200.
  float p = 101325.0f; uint8_t *pb = reinterpret_cast<uint8_t*>(&p);
  MSPPacket pkt; pkt.cmd = 0x1F05; pkt.payload = { 0x02, 0xC8,0x00,0x00,0x00, pb[0],pb[1],pb[2],pb[3], 0x10,0x27 };
  decoder.decode(pkt);
  spin_for(node_);
  ASSERT_TRUE(pressure);
  EXPECT_NEAR(pressure->data, 101325.0f, 0.5f);
}

TEST_F(SensorDecoderFixture, ShortPayloadIgnored) {
  SensorDecoder decoder(*node_, false);
  std_msgs::msg::Float32::SharedPtr last;
  auto sub = node_->create_subscription<std_msgs::msg::Float32>("/msp/rangefinder", 10,
    [&last](std_msgs::msg::Float32::ConstSharedPtr m){ last = std::make_shared<std_msgs::msg::Float32>(*m); });
  MSPPacket pkt; pkt.cmd = 0x1F01; pkt.payload = {0x00}; // too short
  decoder.decode(pkt);
  spin_for(node_);
  EXPECT_FALSE(last);
}
