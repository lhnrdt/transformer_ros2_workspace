#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include "transformer_msp_bridge/msp_protocol.hpp"
#include "transformer_msp_bridge/decoders/system_decoder.hpp"
#include <diagnostic_msgs/msg/diagnostic_array.hpp>
#include <diagnostic_msgs/msg/diagnostic_status.hpp>

using transformer_msp_bridge::MSPPacket;
using transformer_msp_bridge::SystemDecoder;
using diagnostic_msgs::msg::DiagnosticArray;
using diagnostic_msgs::msg::DiagnosticStatus;

class SystemDecoderExtendedFixture : public ::testing::Test {
protected:
  void SetUp() override {
    rclcpp::init(0, nullptr);
    node_ = std::make_shared<rclcpp::Node>("system_decoder_ext_test");
    // SystemDecoder only takes a node reference
    decoder_ = std::make_unique<SystemDecoder>(*node_);
  }
  void TearDown() override {
    decoder_.reset();
    rclcpp::shutdown();
  }
  std::shared_ptr<rclcpp::Node> node_;
  std::unique_ptr<SystemDecoder> decoder_;
};

static void spin_for(std::shared_ptr<rclcpp::Node> node,int ms=60){ rclcpp::executors::SingleThreadedExecutor ex; ex.add_node(node); auto start=std::chrono::steady_clock::now(); while(std::chrono::steady_clock::now()-start < std::chrono::milliseconds(ms)){ ex.spin_some(); std::this_thread::sleep_for(std::chrono::milliseconds(1)); }}

// Helper to find a status by name
static DiagnosticStatus findStatus(const DiagnosticArray &arr, const std::string &name){ for(const auto &s: arr.status) if(s.name==name) return s; return DiagnosticStatus(); }
static std::string getValue(const DiagnosticStatus &st, const std::string &key){ for(const auto &kv: st.values) if(kv.key==key) return kv.value; return ""; }

TEST_F(SystemDecoderExtendedFixture, RcTuningDecoding) {
  DiagnosticArray::SharedPtr last;
  // SystemDecoder publishes rc_tuning on /msp/status_ex
  auto sub = node_->create_subscription<DiagnosticArray>("/msp/status_ex",10,[&last](DiagnosticArray::ConstSharedPtr m){ last = std::make_shared<DiagnosticArray>(*m); });
  MSPPacket pkt; pkt.cmd = MSP_RC_TUNING; pkt.payload = { 100, 50, 55, 40, 10, 30, 90, 80, 70, 0x20, 0x03 }; // tpa_breakpoint=0x0320=800
  decoder_->decode(pkt);
  spin_for(node_);
  ASSERT_TRUE(last);
  auto st = findStatus(*last, "rc_tuning");
  ASSERT_EQ(st.name, "rc_tuning");
  EXPECT_EQ(getValue(st, "rc_rate"), "1.000000");
  EXPECT_EQ(getValue(st, "rc_expo"), "0.500000");
  EXPECT_EQ(getValue(st, "thr_mid"), "0.550000");
  EXPECT_EQ(getValue(st, "thr_expo"), "0.400000");
  EXPECT_EQ(getValue(st, "dyn_throttle_pid"), "10.000000");
  EXPECT_EQ(getValue(st, "rc_yaw_expo"), "0.300000");
  EXPECT_EQ(getValue(st, "rc_yaw_rate"), "0.900000");
  EXPECT_EQ(getValue(st, "rc_pitch_rate"), "0.800000");
  EXPECT_EQ(getValue(st, "rc_roll_rate"), "0.700000");
  EXPECT_EQ(getValue(st, "tpa_breakpoint"), "800.000000");
}

TEST_F(SystemDecoderExtendedFixture, GpsStatisticsDecoding) {
  DiagnosticArray::SharedPtr last;
  diagnostic_msgs::msg::DiagnosticStatus::SharedPtr single;
  // Gps stats array published on /msp/status_ex, single status on /msp/gps/statistics
  auto sub = node_->create_subscription<DiagnosticArray>("/msp/status_ex",10,[&last](DiagnosticArray::ConstSharedPtr m){ last = std::make_shared<DiagnosticArray>(*m); });
  auto subSingle = node_->create_subscription<DiagnosticStatus>("/msp/gps/statistics",10,[&single](DiagnosticStatus::ConstSharedPtr m){ single = std::make_shared<DiagnosticStatus>(*m); });
  // errors=1, timeouts=2, pktCount=300 (0x012C), rejected=4, ignored=5, crc=6, gpsReset=0x89ABCDEF
  MSPPacket pkt; pkt.cmd = MSP_GPSSTATISTICS; pkt.payload = {
    0x01,0x00, 0x02,0x00, 0x2C,0x01, 0x04,0x00, 0x05,0x00, 0x06,0x00,
    0xEF,0xCD,0xAB,0x89 };
  decoder_->decode(pkt);
  spin_for(node_);
  ASSERT_TRUE(last);
  auto st = findStatus(*last, "gps_statistics");
  ASSERT_EQ(st.name, "gps_statistics");
  EXPECT_EQ(getValue(st, "errors"), "1");
  EXPECT_EQ(getValue(st, "timeouts"), "2");
  EXPECT_EQ(getValue(st, "packet_count"), "300");
  EXPECT_EQ(getValue(st, "packet_rejected"), "4");
  EXPECT_EQ(getValue(st, "packet_ignored"), "5");
  EXPECT_EQ(getValue(st, "packet_crc_error"), "6");
  EXPECT_EQ(getValue(st, "gps_reset_flags"), "2309737967"); // 0x89ABCDEF
  ASSERT_TRUE(single);
  EXPECT_EQ(single->name, "gps_statistics");
}

TEST_F(SystemDecoderExtendedFixture, RtcDecoding) {
  DiagnosticArray::SharedPtr last;
  // RTC published on /msp/status_ex
  auto sub = node_->create_subscription<DiagnosticArray>("/msp/status_ex",10,[&last](DiagnosticArray::ConstSharedPtr m){ last = std::make_shared<DiagnosticArray>(*m); });
  // secs = 0x01020304 = 16909060, millis=0x07D0=2000
  MSPPacket pkt; pkt.cmd = MSP_RTC; pkt.payload = { 0x04,0x03,0x02,0x01, 0xD0,0x07 };
  decoder_->decode(pkt);
  spin_for(node_);
  ASSERT_TRUE(last);
  auto st = findStatus(*last, "rtc");
  ASSERT_EQ(st.name, "rtc");
  EXPECT_EQ(getValue(st, "secs"), "16909060");
  EXPECT_EQ(getValue(st, "millis"), "2000");
}
