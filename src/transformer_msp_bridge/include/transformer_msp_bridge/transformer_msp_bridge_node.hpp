// Declares the ROS 2 node that bridges MSP data into Transformer topics.
#pragma once

#include <atomic>
#include <chrono>
#include <cstdint>
#include <deque>
#include <memory>
#include <mutex>
#include <string>
#include <string_view>
#include <thread>
#include <utility>
#include <vector>
#include <sstream>

#include "diagnostic_msgs/msg/diagnostic_array.hpp"
#include "diagnostic_msgs/msg/diagnostic_status.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include "geometry_msgs/msg/vector3_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/battery_state.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "sensor_msgs/msg/magnetic_field.hpp"
#include "sensor_msgs/msg/nav_sat_fix.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/u_int16_multi_array.hpp"

#include "transformer_msp_bridge/decoder_base.hpp"
#include "transformer_msp_bridge/decoder_outputs.hpp"
#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include "transformer_msp_bridge/msg/msp_inav_status.hpp"
#include "transformer_msp_bridge/serial_port.hpp"

namespace transformer_msp_bridge
{
namespace detail
{
std::string sanitize_param_key(std::string_view message_name);
std::string to_hex(const std::vector<uint8_t> &data, bool spaced = true);
void append_key_value(diagnostic_msgs::msg::DiagnosticStatus &status, const std::string &key, bool value);

template <typename T>
void append_key_value(diagnostic_msgs::msg::DiagnosticStatus &status, const std::string &key, const T &value)
{
  diagnostic_msgs::msg::KeyValue kv;
  kv.key = key;
  std::ostringstream oss;
  oss << value;
  kv.value = oss.str();
  status.values.push_back(std::move(kv));
}

} // namespace detail

class TransformerMspBridgeNode : public rclcpp::Node
{
public:
  explicit TransformerMspBridgeNode(const rclcpp::NodeOptions &options = rclcpp::NodeOptions());
  ~TransformerMspBridgeNode() override;

private:
  struct CommandDefinition
  {
    std::string param_key;
    std::string message_name;
    uint16_t command_id;
    double default_rate_hz;
    bool default_enabled;
  };

  struct CommandSchedule
  {
    CommandDefinition definition;
    bool enabled{false};
    double rate_hz{0.0};
    std::chrono::steady_clock::duration period{std::chrono::steady_clock::duration::zero()};
    std::chrono::steady_clock::time_point next_fire{};
  };

  void configurePublishers();
  void configureDecoders();
  void configureCommandSchedules();
  void configureRcOverride();
  void verifyDecoderCoverage(const msp::RegistryView &registry_view);

  bool openSerial();
  void closeSerial();
  void readLoop();
  bool sendCommand(uint16_t command_id, const std::vector<uint8_t> &payload = {});
  void pollCommands();
  void handlePacket(const MSPPacket &pkt);
  void handleRcOverride(const std_msgs::msg::UInt16MultiArray::SharedPtr msg);
  void tickRcOverride();

  void publishImu(const ImuSample &sample);
  void publishAttitude(const AttitudeAngles &angles);
  void publishAltitude(const AltitudeSample &sample);
  void publishGpsRaw(const GpsRawData &data);
  void publishGpsHome(const GpsHomeVector &data);
  void publishRc(const RcChannelsData &data);
  void publishServo(const ServoPositionData &data);
  void publishMotor(const MotorOutputData &data);
  void publishBatteryAnalog(const BatteryAnalogData &data);
  void publishBatteryStatus(const BatteryStatusData &data);
  void publishRangefinder(const RangefinderSample &sample);
  void publishCompass(const CompassSample &sample);
  void publishBarometer(const BarometerSample &sample);
  void publishInavStatus(const InavStatusData &data);
  void publishInavGeneric(const InavGenericFrame &frame);
  void publishStatusEx(const SystemStatusExData &data);
  void publishSensorStatus(const SystemSensorStatusData &data);
  void publishSensorConfig(const SystemSensorConfigData &data);
  void publishGpsStatistics(const SystemGpsStatsData &data);
  void publishRcTuning(const RcTuningData &data);
  void publishRtc(const SystemRtcData &data);

  struct PendingRequest
  {
    uint16_t command_id{0};
    std::chrono::steady_clock::time_point sent_at{};
  };

  std::string port_{};
  int baudrate_{115200};
  int timeout_ms_{50};
  bool log_msp_tx_{false};
  bool log_msp_rx_{false};
  bool debug_msp_{false};
  bool use_v2_tunnel_{false};
  bool force_msp_v2_{false};
  bool use_v2_for_legacy_{false};
  double v2_fallback_timeout_sec_{5.0};
  std::size_t rc_channel_count_{8};
  double rc_publish_rate_hz_{10.0};

  std::string frame_id_imu_{"base_link"};
  std::string frame_id_mag_{"base_link"};
  std::string frame_id_gps_{"gps"};
  std::string frame_id_altitude_{"base_link"};
  std::string frame_id_rangefinder_{"base_link"};

  SerialPort serial_;
  std::mutex serial_mutex_;
  std::thread reader_thread_;
  std::atomic<bool> running_{false};
  bool serial_ready_{false};

  // Link-level statistics
  std::atomic<std::uint64_t> tx_bytes_{0};
  std::atomic<std::uint64_t> rx_bytes_{0};
  std::atomic<std::uint64_t> tx_messages_{0};
  std::atomic<std::uint64_t> rx_packets_{0};
  std::atomic<std::uint64_t> response_time_sum_ns_{0};
  std::atomic<std::uint64_t> response_time_count_{0};
  std::chrono::steady_clock::time_point stats_window_start_{};
  std::uint64_t stats_window_tx_bytes_{0};
  std::uint64_t stats_window_rx_bytes_{0};
  std::uint64_t stats_window_tx_messages_{0};
  std::uint64_t stats_window_rx_packets_{0};
  std::uint64_t stats_window_response_sum_ns_{0};
  std::uint64_t stats_window_response_count_{0};
  rclcpp::TimerBase::SharedPtr stats_timer_;
  std::mutex pending_request_mutex_;
  std::deque<PendingRequest> pending_requests_;

  MSPParser parser_;
  std::vector<std::unique_ptr<IMspDecoder>> decoders_;
  std::vector<CommandSchedule> command_schedules_;
  rclcpp::TimerBase::SharedPtr poll_timer_;

  std::string rc_override_topic_{"/msp/rc_override"};
  double rc_override_rate_hz_{50.0};
  std::chrono::steady_clock::duration rc_override_hold_duration_{std::chrono::milliseconds(200)};
  rclcpp::Subscription<std_msgs::msg::UInt16MultiArray>::SharedPtr rc_override_sub_;
  rclcpp::TimerBase::SharedPtr rc_override_timer_;
  std::mutex rc_override_mutex_;
  std::vector<uint16_t> rc_override_channels_;
  std::chrono::steady_clock::time_point rc_override_last_msg_{};
  bool rc_override_active_{false};

  rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imu_pub_;
  rclcpp::Publisher<sensor_msgs::msg::MagneticField>::SharedPtr mag_pub_;
  rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr attitude_pub_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr altitude_pub_;
  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr vertical_speed_pub_;
  rclcpp::Publisher<sensor_msgs::msg::NavSatFix>::SharedPtr gps_fix_pub_;
  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr gps_vel_pub_;
  rclcpp::Publisher<geometry_msgs::msg::Vector3Stamped>::SharedPtr gps_home_vec_pub_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr gps_home_dist_pub_;
  rclcpp::Publisher<std_msgs::msg::UInt16MultiArray>::SharedPtr rc_pub_;
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr servo_pub_;
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr motor_pub_;
  rclcpp::Publisher<sensor_msgs::msg::BatteryState>::SharedPtr battery_pub_;
  rclcpp::Publisher<sensor_msgs::msg::BatteryState>::SharedPtr battery_extended_pub_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr rangefinder_pub_;
  rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr compass_pub_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr barometer_pub_;
  rclcpp::Publisher<transformer_msp_bridge::msg::MspInavStatus>::SharedPtr inav_status_pub_;
  rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticArray>::SharedPtr inav_generic_pub_;
  rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticArray>::SharedPtr status_pub_;
  rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticArray>::SharedPtr sensor_status_pub_;
  rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticStatus>::SharedPtr gps_stats_status_pub_;
  rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticArray>::SharedPtr gps_stats_array_pub_;
  rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticArray>::SharedPtr rc_tuning_pub_;
  rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticArray>::SharedPtr rtc_pub_;
};

} // namespace transformer_msp_bridge
