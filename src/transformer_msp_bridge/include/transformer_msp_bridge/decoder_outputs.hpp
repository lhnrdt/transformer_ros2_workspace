// Defines plain-old-data structs that decoders populate before ROS publication.
#pragma once

#include <array>
#include <cstdint>
#include <limits>
#include <string>
#include <vector>

namespace transformer_msp_bridge
{

  struct ImuSample
  {
    std::array<double, 3> linear_acceleration_mps2{};
    std::array<double, 3> angular_velocity_radps{};
    std::array<double, 3> magnetic_field_tesla{};
  };

  struct AttitudeAngles
  {
    double roll_deg{0.0};
    double pitch_deg{0.0};
    double yaw_deg{0.0};
  };

  struct AltitudeSample
  {
    float altitude_m{std::numeric_limits<float>::quiet_NaN()};
    float vertical_speed_mps{std::numeric_limits<float>::quiet_NaN()};
  };

  struct GpsRawData
  {
    double latitude_deg{0.0};
    double longitude_deg{0.0};
    double altitude_m{0.0};
    double speed_mps{0.0};
    double course_rad{0.0};
    uint8_t fix_type{0};
    uint8_t satellites{0};
  };

  struct GpsHomeVector
  {
    double distance_m{0.0};
    double direction_deg{0.0};
  };

  struct RcChannelsData
  {
    std::vector<uint16_t> channels;
  };

  struct ServoPositionData
  {
    std::vector<double> positions;
  };

  struct MotorOutputData
  {
    std::vector<double> values;
  };

  struct BatteryAnalogData
  {
    float voltage_v{std::numeric_limits<float>::quiet_NaN()};
    bool present{false};
  };

  struct BatteryStatusData
  {
    uint8_t cell_count{0};
    std::vector<float> cell_voltage_v;
    float voltage_v{std::numeric_limits<float>::quiet_NaN()};
    float current_a{std::numeric_limits<float>::quiet_NaN()};
    float charge_c{std::numeric_limits<float>::quiet_NaN()};
    float remaining_fraction{std::numeric_limits<float>::quiet_NaN()};
    bool present{false};
  };

  struct RangefinderSample
  {
    float distance_m{std::numeric_limits<float>::quiet_NaN()};
    uint8_t quality{0};
  };

  struct CompassSample
  {
    uint8_t instance{0};
    std::array<int16_t, 3> magnetic_field_mgauss{};
  };

  struct BarometerSample
  {
    uint8_t instance{0};
    float pressure_pa{std::numeric_limits<float>::quiet_NaN()};
    float temperature_c{std::numeric_limits<float>::quiet_NaN()};
  };

  struct InavStatusData
  {
    uint16_t cycle_time_us{0};
    uint16_t i2c_errors{0};
    uint16_t sensor_status_mask{0};
    uint16_t cpu_load_percent{0};
    uint8_t config_profile{0};
    uint8_t battery_profile{0};
    uint8_t mixer_profile{0};
    uint32_t arming_flags{0};
    std::vector<uint8_t> active_modes;
  };

  struct InavGenericFrame
  {
    uint16_t command_id{0};
    std::string description;
    std::vector<uint8_t> payload;
  };

  struct SystemStatusExData
  {
    uint16_t cycle_time_us{0};
    uint16_t i2c_errors{0};
    uint16_t sensors_mask{0};
    uint32_t mode_flags{0};
    uint8_t profile{0};
    uint8_t system_load_pct{0};
    uint16_t gyro_cycle_time_us{0};
    uint8_t last_arm_disable{0};
    uint32_t arming_flags{0};
    uint8_t acc_cal_running{0};
  };

  struct SystemSensorStatusData
  {
    bool has_masks{false};
    uint16_t present_mask{0};
    uint16_t failing_mask{0};
    std::vector<uint8_t> raw_payload;
  };

  struct SystemSensorConfigData
  {
    std::vector<uint8_t> hardware_ids;
    std::vector<uint8_t> raw_tail;
  };

  struct SystemGpsStatsData
  {
    uint16_t errors{0};
    uint16_t timeouts{0};
    uint16_t packet_count{0};
    uint16_t packet_rejected{0};
    uint16_t packet_ignored{0};
    uint16_t packet_crc_error{0};
    uint32_t gps_reset_flags{0};
  };

  struct RcTuningData
  {
    double rc_rate{0.0};
    double rc_expo{0.0};
    double throttle_mid{0.0};
    double throttle_expo{0.0};
    double dyn_throttle_pid{0.0};
    double rc_yaw_expo{0.0};
    double rc_yaw_rate{0.0};
    double rc_pitch_rate{0.0};
    double rc_roll_rate{0.0};
    double tpa_breakpoint{0.0};
  };

  struct SystemRtcData
  {
    int32_t seconds{0};
    uint16_t millis{0};
  };

} // namespace transformer_msp_bridge
