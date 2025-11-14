#pragma once

#include <atomic>
#include <chrono>
#include <cstdint>
#include <deque>
#include <memory>
#include <mutex>
#include <optional>
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

namespace tf2_ros
{
class TransformBroadcaster;
}

namespace transformer_msp_bridge
{
namespace detail
{
  /**
   * @brief Build a stable ROS parameter key from a human-readable MSP message name.
   *
   * MSP messages are typically identified by human-friendly names such as
   * "STATUS_EX" or "BATTERY_STATE". For configuration we expose one
   * parameter namespace per MSP command. This helper converts a message name
   * into a normalized parameter key of the form:
   *
   *   command.<lowercased_name_with_spaces_replaced_by_underscores>
   *
   * This keeps parameter names stable across boots and independent of the
   * numeric MSP command id.
   *
   * @param message_name Human-readable MSP message name from the registry.
   * @return Normalized parameter namespace for this command.
   */
  std::string sanitize_param_key(std::string_view message_name);

  /**
   * @brief Render a payload as hexadecimal for logging and diagnostics.
   *
   * @param data   Input bytes to render.
   * @param spaced If true, insert a single space between bytes.
   * @return Uppercase hexadecimal string representation.
   */
  std::string to_hex(const std::vector<uint8_t> &data, bool spaced = true);

  /**
   * @brief Append a boolean key/value pair to a diagnostic status.
   *
   * The value is written in a human-friendly form ("true" / "false").
   *
   * @param status Diagnostic status to extend.
   * @param key    Key label to use.
   * @param value  Boolean value to record.
   */
  void append_key_value(diagnostic_msgs::msg::DiagnosticStatus &status, const std::string &key, bool value);

  /**
   * @brief Append an arbitrary value as a key/value pair to a diagnostic status.
   *
   * This helper relies on the type @p T being streamable to an std::ostream.
   * Values are converted to strings using the stream insertion operator and
   * then attached as diagnostic_msgs::msg::KeyValue entries.
   *
   * @tparam T      Value type, must support operator<<(std::ostream&, const T&).
   * @param status  Diagnostic status to extend.
   * @param key     Key label to use.
   * @param value   Value to convert and attach.
   */
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

/**
 * @brief ROS 2 node that bridges MSP telemetry and commands to Transformer topics.
 *
 * This node maintains a serial link to a flight controller speaking the
 * MultiWii Serial Protocol (MSP). It periodically polls MSP commands,
 * decodes telemetry using a pluggable decoder set and publishes the
 * resulting data as standard ROS 2 messages (IMU, GPS, battery, diagnostics,
 * RC channels, servo and motor outputs, ...).
 *
 * Additionally, the node can:
 *  - publish an attitude transform into TF (optional),
 *  - expose RC override via a ROS topic and translate it into MSP_SET_RAW_RC,
 *  - collect link statistics for monitoring throughput and latency.
 */
class TransformerMspBridgeNode : public rclcpp::Node
{
public:
  /**
   * @brief Construct the bridge node with optional node options.
   *
   * The constructor declares all configurable parameters (serial port,
   * polling schedule, frame ids, RC override behaviour, logging toggles)
   * and sets up publishers, decoders, timers and the MSP parser.
   *
   * @param options Optional rclcpp node options (useful in composable setups).
   */
  explicit TransformerMspBridgeNode(const rclcpp::NodeOptions &options = rclcpp::NodeOptions());

  /**
   * @brief Ensure threads and the serial link are shut down cleanly.
   *
   * The destructor stops the reader thread, closes the serial port and
   * releases any resources that depend on the node lifetime.
   */
  ~TransformerMspBridgeNode() override;

private:
  struct CommandDefinition
  {
    /** Normalized parameter namespace (e.g. "command.status_ex"). */
    std::string param_key;
    /** Human-readable MSP message name as reported by the registry. */
    std::string message_name;
    /** Numeric MSP command identifier. */
    uint16_t command_id;
    /** Default polling rate in Hertz as suggested by the registry. */
    double default_rate_hz;
    /** Whether the command is polled by default in the registry. */
    bool default_enabled;
  };

  struct CommandSchedule
  {
    /** Backing definition shared across nodes / boots. */
    CommandDefinition definition;
    /** Whether polling is enabled after applying user overrides. */
    bool enabled{false};
    /** Effective polling rate in Hertz. */
    double rate_hz{0.0};
    /** Derived period between polls (0 when disabled). */
    std::chrono::steady_clock::duration period{std::chrono::steady_clock::duration::zero()};
    /** Next time this command should be fired. */
    std::chrono::steady_clock::time_point next_fire{};
  };

  /** @brief Create all ROS publishers used by the bridge. */
  void configurePublishers();

  /** @brief Instantiate and register all MSP decoders. */
  void configureDecoders();

  /** @brief Derive per-command polling schedules from the MSP registry and parameters. */
  void configureCommandSchedules();

  /** @brief Configure RC override subscription and transmission timer. */
  void configureRcOverride();

  /** @brief Check that every decoder-required MSP command is scheduled or warn otherwise. */
  void verifyDecoderCoverage(const msp::RegistryView &registry_view);

  /**
   * @brief Open the serial port and start the background reader thread.
   *
   * @return true if the port is open and ready for use.
   */
  bool openSerial();

  /** @brief Close the serial port; the reader loop will observe this and exit. */
  void closeSerial();

  /** @brief Blocking loop that reads bytes from the serial port and feeds the parser. */
  void readLoop();

  /**
   * @brief Encode and send a single MSP command frame.
   *
   * This helper chooses MSP v1/v2 or v2-over-v1 according to the node
   * configuration and updates link statistics. For non-RC commands it also
   * tracks outstanding requests for latency measurements.
   *
   * @param command_id Numeric MSP command id.
   * @param payload    Optional payload bytes; may be empty for simple queries.
   * @return true if the frame was written to the serial port.
   */
  bool sendCommand(uint16_t command_id, const std::vector<uint8_t> &payload = {});

  /** @brief Iterate all schedules and fire commands whose deadline has passed. */
  void pollCommands();

  /**
   * @brief Process a fully parsed MSP packet from the parser.
   *
   * Updates round-trip time statistics and forwards the packet to any
   * registered decoders that express interest in the packet's command id.
   *
   * @param pkt Parsed MSP packet.
   */
  void handlePacket(const MSPPacket &pkt);

  /**
   * @brief Handle an incoming RC override message.
   *
   * The message is sanitized (range checked and length-clamped) before
   * being stored for transmission as MSP_SET_RAW_RC.
   *
   * @param msg Incoming RC channel override message.
   */
  void handleRcOverride(const std_msgs::msg::UInt16MultiArray::SharedPtr msg);

  /** @brief Periodic hook that transmits RC override frames while active. */
  void tickRcOverride();

  /** @brief Publish IMU readings converted from MSP samples. */
  void publishImu(const ImuSample &sample);

  /** @brief Publish attitude angles (roll/pitch/yaw) as a simple Vector3. */
  void publishAttitude(const AttitudeAngles &angles);

  /** @brief Publish altitude-related information. */
  void publishAltitude(const AltitudeSample &sample);

  /** @brief Publish raw GPS fix data. */
  void publishGpsRaw(const GpsRawData &data);

  /** @brief Publish a vector from home position to the current GPS position. */
  void publishGpsHome(const GpsHomeVector &data);

  /** @brief Publish RC channel values over a ROS topic. */
  void publishRc(const RcChannelsData &data);

  /** @brief Publish servo positions as a JointState. */
  void publishServo(const ServoPositionData &data);

  /** @brief Publish motor outputs as a JointState. */
  void publishMotor(const MotorOutputData &data);

  /** @brief Publish analog battery state derived from MSP data. */
  void publishBatteryAnalog(const BatteryAnalogData &data);

  /** @brief Handle battery configuration messages and cache them for later use. */
  void handleBatteryConfig(const BatteryConfigData &data);

  /** @brief Publish the high-level INAV status message. */
  void publishInavStatus(const InavStatusData &data);

  /** @brief Publish generic INAV diagnostic frames as diagnostic arrays. */
  void publishInavGeneric(const InavGenericFrame &frame);

  /** @brief Publish extended system status information. */
  void publishStatusEx(const SystemStatusExData &data);

  /** @brief Publish per-sensor status information. */
  void publishSensorStatus(const SystemSensorStatusData &data);

  /** @brief Publish sensor configuration diagnostics. */
  void publishSensorConfig(const SystemSensorConfigData &data);

  /** @brief Publish GPS statistics as diagnostic messages. */
  void publishGpsStatistics(const SystemGpsStatsData &data);

  /** @brief Publish RC tuning configuration. */
  void publishRcTuning(const RcTuningData &data);

  /** @brief Publish system RTC information. */
  void publishRtc(const SystemRtcData &data);

  /** @brief Broadcast a TF transform representing the vehicle attitude. */
  void broadcastAttitudeTransform(const AttitudeAngles &angles);

  struct PendingRequest
  {
    /** MSP command id we are waiting for. */
    uint16_t command_id{0};
    /** Timestamp when the request was sent. */
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
  bool broadcast_attitude_tf_{false};
  std::string attitude_tf_parent_frame_{"map"};
  std::string attitude_tf_child_frame_{"base_link"};
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;

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

  std::mutex battery_config_mutex_;
  std::optional<BatteryConfigData> last_battery_config_;

  rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imu_pub_;
  rclcpp::Publisher<sensor_msgs::msg::MagneticField>::SharedPtr mag_pub_;
  rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr attitude_pub_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr altitude_pub_;
  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr vertical_speed_pub_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr baro_altitude_pub_;
  rclcpp::Publisher<sensor_msgs::msg::NavSatFix>::SharedPtr gps_fix_pub_;
  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr gps_vel_pub_;
  rclcpp::Publisher<geometry_msgs::msg::Vector3Stamped>::SharedPtr gps_home_vec_pub_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr gps_home_dist_pub_;
  rclcpp::Publisher<std_msgs::msg::UInt16MultiArray>::SharedPtr rc_pub_;
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr servo_pub_;
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr motor_pub_;
  rclcpp::Publisher<sensor_msgs::msg::BatteryState>::SharedPtr battery_pub_;
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
