#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/magnetic_field.hpp>
#include <chrono>
#include <thread>
#include "transformer_msp_bridge/decoders/imu_decoder.hpp"

using namespace transformer_msp_bridge;

static void spin_for(rclcpp::Node::SharedPtr node, int ms=60) {
  auto start = std::chrono::steady_clock::now();
  rclcpp::executors::SingleThreadedExecutor exec; exec.add_node(node);
  while ((std::chrono::steady_clock::now() - start) < std::chrono::milliseconds(ms)) {
    exec.spin_some();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
}

TEST(ImuDecoder, RawImuScaling) {
  auto node = std::make_shared<rclcpp::Node>("imu_decoder_test");
  ImuDecoder decoder(*node);

  sensor_msgs::msg::Imu::SharedPtr last_imu;
  sensor_msgs::msg::MagneticField::SharedPtr last_mag;
  auto sub_imu = node->create_subscription<sensor_msgs::msg::Imu>("/msp/imu",10,
    [&](sensor_msgs::msg::Imu::SharedPtr msg){ last_imu = msg; });
  auto sub_mag = node->create_subscription<sensor_msgs::msg::MagneticField>("/msp/mag",10,
    [&](sensor_msgs::msg::MagneticField::SharedPtr msg){ last_mag = msg; });

  // Craft payload of 9 int16 values: ax ay az gx gy gz mx my mz
  // Choose ax=512 => 1g, ay=-512 => -1g, az=1024 => 2g
  // gx=160 => 10 deg/s, gy=-160 => -10 deg/s, gz=320 => 20 deg/s
  // mx=100, my=-200, mz=50
  auto put16 = [](std::vector<uint8_t>& v, int16_t val){ v.push_back(val & 0xFF); v.push_back((val >> 8) & 0xFF); };
  MSPPacket pkt; pkt.cmd = MSP_RAW_IMU;
  put16(pkt.payload, 512);   // ax
  put16(pkt.payload, -512);  // ay
  put16(pkt.payload, 1024);  // az
  put16(pkt.payload, 160);   // gx
  put16(pkt.payload, -160);  // gy
  put16(pkt.payload, 320);   // gz
  put16(pkt.payload, 100);   // mx
  put16(pkt.payload, -200);  // my
  put16(pkt.payload, 50);    // mz

  decoder.decode(pkt);
  spin_for(node);

  ASSERT_TRUE(last_imu);
  // accel: (raw/512)*g
  constexpr double g = 9.80665;
  EXPECT_NEAR(last_imu->linear_acceleration.x, 1.0 * g, 1e-4);
  EXPECT_NEAR(last_imu->linear_acceleration.y, -1.0 * g, 1e-4);
  EXPECT_NEAR(last_imu->linear_acceleration.z, 2.0 * g, 1e-4);
  // gyro: (raw/16) deg/s -> rad/s
  double deg2rad = M_PI/180.0;
  EXPECT_NEAR(last_imu->angular_velocity.x, 10.0 * deg2rad, 1e-5);
  EXPECT_NEAR(last_imu->angular_velocity.y, -10.0 * deg2rad, 1e-5);
  EXPECT_NEAR(last_imu->angular_velocity.z, 20.0 * deg2rad, 1e-5);

  ASSERT_TRUE(last_mag);
  EXPECT_NEAR(last_mag->magnetic_field.x, 100e-6, 1e-9);
  EXPECT_NEAR(last_mag->magnetic_field.y, -200e-6, 1e-9);
  EXPECT_NEAR(last_mag->magnetic_field.z, 50e-6, 1e-9);
}

TEST(ImuDecoder, ShortPayloadIgnored) {
  auto node = std::make_shared<rclcpp::Node>("imu_decoder_short_test");
  ImuDecoder decoder(*node);
  sensor_msgs::msg::Imu::SharedPtr last_imu;
  auto sub_imu = node->create_subscription<sensor_msgs::msg::Imu>("/msp/imu",10,
    [&](sensor_msgs::msg::Imu::SharedPtr msg){ last_imu = msg; });
  MSPPacket pkt; pkt.cmd = MSP_RAW_IMU; pkt.payload = {0x00}; // too short
  decoder.decode(pkt);
  spin_for(node);
  EXPECT_FALSE(last_imu) << "Decoder should ignore short payload";
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  rclcpp::init(argc, argv);
  int ret = RUN_ALL_TESTS();
  rclcpp::shutdown();
  return ret;
}
