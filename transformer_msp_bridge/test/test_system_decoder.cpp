#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <diagnostic_msgs/msg/diagnostic_array.hpp>
#include <diagnostic_msgs/msg/diagnostic_status.hpp>
#include <chrono>
#include <thread>
#include "transformer_msp_bridge/decoders/system_decoder.hpp"

using namespace transformer_msp_bridge;

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

TEST(SystemDecoder, StatusExBasic)
{
  auto node = std::make_shared<rclcpp::Node>("system_decoder_status_ex_test");
  SystemDecoder decoder(*node);
  diagnostic_msgs::msg::DiagnosticArray::SharedPtr last;
  auto sub = node->create_subscription<diagnostic_msgs::msg::DiagnosticArray>("/msp/status_ex", 10,
                                                                              [&](diagnostic_msgs::msg::DiagnosticArray::SharedPtr msg)
                                                                              { last = msg; });

  // Build minimal plausible payload for MSP_STATUS_EX
  // cycle(2)=2000, i2cErr(2)=3, sensors(2)=0x01FF, modeFlags(4)=0x0A0B0C0D, profile=2, sysLoad=45,
  // gyroCycle(2)=125, lastArmReason=7, armingFlags(4)=0x11223344, accCal=1
  MSPPacket pkt;
  pkt.cmd = MSP_STATUS_EX;
  pkt.payload = {
      0xD0, 0x07,             // 2000
      0x03, 0x00,             // i2cErr
      0xFF, 0x01,             // sensors
      0x0D, 0x0C, 0x0B, 0x0A, // mode flags
      0x02,                   // profile
      0x2D,                   // sysLoad (45)
      0x7D, 0x00,             // gyroCycle 125
      0x07,                   // lastArmReason
      0x44, 0x33, 0x22, 0x11, // armingFlags
      0x01                    // accCal
  };
  decoder.decode(pkt);
  spin_for(node);
  ASSERT_TRUE(last);
  ASSERT_FALSE(last->status.empty());
  const auto &st = last->status.front();
  EXPECT_EQ(st.name, "status_ex");
  // Simple key presence checks
  bool found_cycle = false, found_arming = false;
  for (const auto &kv : st.values)
  {
    if (kv.key == "cycle_time_us" && kv.value == "2000")
      found_cycle = true;
    if (kv.key == "arming_flags" && kv.value == std::to_string(0x11223344))
      found_arming = true;
  }
  EXPECT_TRUE(found_cycle);
  EXPECT_TRUE(found_arming);
}

TEST(SystemDecoder, SensorStatusMasks)
{
  auto node = std::make_shared<rclcpp::Node>("system_decoder_sensor_status_test");
  SystemDecoder decoder(*node);
  diagnostic_msgs::msg::DiagnosticArray::SharedPtr last;
  auto sub = node->create_subscription<diagnostic_msgs::msg::DiagnosticArray>("/msp/sensors/status", 10,
                                                                              [&](diagnostic_msgs::msg::DiagnosticArray::SharedPtr msg)
                                                                              { last = msg; });

  MSPPacket pkt;
  pkt.cmd = MSP_SENSOR_STATUS;
  pkt.payload = {0x0F, 0x00, 0xF0, 0x00}; // present=0x000F failing=0x00F0
  decoder.decode(pkt);
  spin_for(node);
  ASSERT_TRUE(last);
  ASSERT_FALSE(last->status.empty());
  const auto &st = last->status.front();
  bool present = false, failing = false;
  for (const auto &kv : st.values)
  {
    if (kv.key == "present_mask" && kv.value == std::to_string(0x000F))
      present = true;
    if (kv.key == "failing_mask" && kv.value == std::to_string(0x00F0))
      failing = true;
  }
  EXPECT_TRUE(present);
  EXPECT_TRUE(failing);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  rclcpp::init(argc, argv);
  int ret = RUN_ALL_TESTS();
  rclcpp::shutdown();
  return ret;
}
