#include <gtest/gtest.h>
#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/battery_state.hpp>
#include <thread>
#include "transformer_msp_bridge/decoders/battery_decoder.hpp"

using namespace transformer_msp_bridge;

// Helper to spin node briefly (renamed to avoid clash with rclcpp::spin_some)
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

TEST(BatteryDecoder, AnalogBasic)
{
  auto node = std::make_shared<rclcpp::Node>("battery_decoder_test");
  BatteryDecoder decoder(*node);

  sensor_msgs::msg::BatteryState::SharedPtr last;
  auto sub = node->create_subscription<sensor_msgs::msg::BatteryState>(
      "/msp/battery", 10, [&](sensor_msgs::msg::BatteryState::SharedPtr msg)
      { last = msg; });

  // Allow DDS to match publisher/subscription before publishing
  spin_for(node, 100);

  // MSP_ANALOG schema expects 7 bytes: vbat(U8), mah(U16), rssi(U16), amps(I16)
  MSPPacket pkt;
  pkt.cmd = MSP_ANALOG;
  pkt.payload = {(uint8_t)123, 0, 0, 0, 0, 0, 0}; // 12.3V, zeros for others
  // Try a few times to tolerate discovery delays
  for (int i = 0; i < 10 && !last; ++i)
  {
    decoder.decode(pkt);
    spin_for(node, 100);
  }
  ASSERT_TRUE(last);
  EXPECT_NEAR(last->voltage, 12.3, 1e-4);
  EXPECT_TRUE(last->present);
}

TEST(BatteryDecoder, ExtendedState)
{
  auto node = std::make_shared<rclcpp::Node>("battery_decoder_ext_test");
  BatteryDecoder decoder(*node);

  sensor_msgs::msg::BatteryState::SharedPtr last;
  auto sub = node->create_subscription<sensor_msgs::msg::BatteryState>(
      "/msp/battery/dji", 10, [&](sensor_msgs::msg::BatteryState::SharedPtr msg)
      { last = msg; });

  // Craft payload: cells=4, capacity(2)=5000 (-> 5 * 3600 = 18000C), mv(2)=1684 (16.84V), current(2)=1234 (12.34A), remaining%=85
  MSPPacket pkt;
  pkt.cmd = MSP_BATTERY_STATE;
  pkt.payload = {
      4,          // cells
      0x88, 0x13, // capacity 5000 (0x1388)
      0x94, 0x06, // mv 1684
      0xD2, 0x04, // current 1234
      85          // remaining %
  };
  decoder.decode(pkt);
  spin_for(node);
  ASSERT_TRUE(last);
  EXPECT_EQ(last->cell_voltage.size(), 4u);
  EXPECT_NEAR(last->voltage, 16.84, 1e-2);
  EXPECT_NEAR(last->current, 12.34, 1e-2);
  EXPECT_NEAR(last->percentage, 0.85, 1e-6);
  EXPECT_NEAR(last->charge, 18000.0f, 1.0f); // coarse tolerance
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  rclcpp::init(argc, argv);
  int ret = RUN_ALL_TESTS();
  rclcpp::shutdown();
  return ret;
}
