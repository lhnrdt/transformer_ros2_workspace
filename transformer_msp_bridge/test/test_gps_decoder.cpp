#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <geometry_msgs/msg/vector3_stamped.hpp>
#include <std_msgs/msg/float32.hpp>
#include "transformer_msp_bridge/decoders/gps_decoder.hpp"

using namespace transformer_msp_bridge;

static void spin_for(rclcpp::Node::SharedPtr node, int ms=80) {
  auto start = std::chrono::steady_clock::now();
  rclcpp::executors::SingleThreadedExecutor exec; exec.add_node(node);
  while ((std::chrono::steady_clock::now() - start) < std::chrono::milliseconds(ms)) { exec.spin_some(); std::this_thread::sleep_for(std::chrono::milliseconds(5)); }
}

TEST(GpsDecoder, RawGpsBasic) {
  auto node = std::make_shared<rclcpp::Node>("gps_decoder_test");
  GpsDecoder decoder(*node);
  sensor_msgs::msg::NavSatFix::SharedPtr fix;
  geometry_msgs::msg::TwistStamped::SharedPtr vel;
  auto sub_fix = node->create_subscription<sensor_msgs::msg::NavSatFix>(
    "/msp/gps/fix",10,[&](sensor_msgs::msg::NavSatFix::SharedPtr m){fix=m;});
  auto sub_vel = node->create_subscription<geometry_msgs::msg::TwistStamped>(
    "/msp/gps/vel",10,[&](geometry_msgs::msg::TwistStamped::SharedPtr m){vel=m;});
  MSPPacket pkt; pkt.cmd = MSP_RAW_GPS;
  auto push8=[&](uint8_t b){ pkt.payload.push_back(b); };
  auto push16=[&](uint16_t v){ pkt.payload.push_back(v & 0xFF); pkt.payload.push_back((v>>8)&0xFF); };
  auto push32=[&](int32_t v){ pkt.payload.push_back(v & 0xFF); pkt.payload.push_back((v>>8)&0xFF); pkt.payload.push_back((v>>16)&0xFF); pkt.payload.push_back((v>>24)&0xFF); };
  // fix flag, sats
  push8(1); push8(10);
  int32_t lat = 374221234; // 37.4221234
  int32_t lon = -1220845678; // -122.0845678
  push32(lat); push32(lon);
  push16(123); // alt m
  push16(1500); // speed cm/s
  push16(900); // course 90.0 deg
  decoder.decode(pkt);
  spin_for(node);
  ASSERT_TRUE(fix);
  EXPECT_NEAR(fix->latitude, 37.4221234, 1e-7);
  EXPECT_NEAR(fix->longitude, -122.0845678, 1e-7);
  EXPECT_DOUBLE_EQ(fix->altitude, 123);
  EXPECT_EQ(fix->status.status, sensor_msgs::msg::NavSatStatus::STATUS_FIX);
  ASSERT_TRUE(vel);
  EXPECT_NEAR(vel->twist.linear.x, 15.0, 1e-6);
  EXPECT_NEAR(vel->twist.angular.z, (90.0 * M_PI/180.0), 1e-6);
}

TEST(GpsDecoder, CompGpsVector) {
  auto node = std::make_shared<rclcpp::Node>("gps_comp_decoder_test");
  GpsDecoder decoder(*node);
  geometry_msgs::msg::Vector3Stamped::SharedPtr home_vec;
  std_msgs::msg::Float32::SharedPtr home_dist;
  auto sub_vec = node->create_subscription<geometry_msgs::msg::Vector3Stamped>(
    "/msp/home/vector",10,[&](geometry_msgs::msg::Vector3Stamped::SharedPtr m){home_vec=m;});
  auto sub_dist = node->create_subscription<std_msgs::msg::Float32>(
    "/msp/home/distance",10,[&](std_msgs::msg::Float32::SharedPtr m){home_dist=m;});
  MSPPacket pkt; pkt.cmd = MSP_COMP_GPS; pkt.payload = { 0x34, 0x12, 0x78, 0x56 }; // dist=0x1234=4660, dir=0x5678=22136
  decoder.decode(pkt);
  spin_for(node);
  ASSERT_TRUE(home_vec);
  EXPECT_DOUBLE_EQ(home_vec->vector.x, 4660);
  EXPECT_DOUBLE_EQ(home_vec->vector.y, 22136);
  ASSERT_TRUE(home_dist);
  EXPECT_FLOAT_EQ(home_dist->data, 4660.0f);
}

int main(int argc, char** argv){
  testing::InitGoogleTest(&argc, argv); rclcpp::init(argc, argv); int r = RUN_ALL_TESTS(); rclcpp::shutdown(); return r;
}
