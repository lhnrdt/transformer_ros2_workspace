// MSP Bridge ROS 2 node implementation: connects MSP decoders to ROS topics.

#include <algorithm>
#include <atomic>
#include <array>
#include <chrono>
#include <functional>
#include <iomanip>
#include <limits>
#include <memory>
#include <mutex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "diagnostic_msgs/msg/diagnostic_array.hpp"
#include "diagnostic_msgs/msg/diagnostic_status.hpp"
#include "diagnostic_msgs/msg/key_value.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include "geometry_msgs/msg/vector3_stamped.hpp"
#include "rclcpp/qos.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/battery_state.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "sensor_msgs/msg/magnetic_field.hpp"
#include "sensor_msgs/msg/nav_sat_fix.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/u_int16_multi_array.hpp"

#include "transformer_msp_bridge/decoder_outputs.hpp"
#include "transformer_msp_bridge/decoders/altitude_decoder.hpp"
#include "transformer_msp_bridge/decoders/attitude_decoder.hpp"
#include "transformer_msp_bridge/decoders/battery_decoder.hpp"
#include "transformer_msp_bridge/decoders/gps_decoder.hpp"
#include "transformer_msp_bridge/decoders/imu_decoder.hpp"
#include "transformer_msp_bridge/decoders/inav_generic_decoder.hpp"
#include "transformer_msp_bridge/decoders/inav_status_decoder.hpp"
#include "transformer_msp_bridge/decoders/rc_decoder.hpp"
#include "transformer_msp_bridge/decoders/sensor_decoder.hpp"
#include "transformer_msp_bridge/decoders/servo_motor_decoder.hpp"
#include "transformer_msp_bridge/decoders/system_decoder.hpp"
#include "transformer_msp_bridge/msp_builders.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/msg/msp_inav_status.hpp"
#include "transformer_msp_bridge/serial_port.hpp"

namespace transformer_msp_bridge
{
	namespace
	{
		std::string to_hex(const std::vector<uint8_t> &data, bool spaced = true)
		{
			std::ostringstream oss;
			oss << std::hex << std::uppercase << std::setfill('0');
			for (size_t i = 0; i < data.size(); ++i)
			{
				oss << std::setw(2) << static_cast<int>(data[i]);
				if (spaced && i + 1 < data.size())
					oss << ' ';
			}
			return oss.str();
		}

			inline void append_key_value(diagnostic_msgs::msg::DiagnosticStatus &status, const std::string &key, bool value)
			{
				diagnostic_msgs::msg::KeyValue kv;
				kv.key = key;
				kv.value = value ? "true" : "false";
				status.values.push_back(std::move(kv));
			}

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
	} // namespace

	class TransformerMspBridgeNode : public rclcpp::Node
	{
	public:
		explicit TransformerMspBridgeNode(const rclcpp::NodeOptions &options = rclcpp::NodeOptions());
		~TransformerMspBridgeNode() override;

	private:
		struct CommandDefinition
		{
			const char *param_key;
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
		bool openSerial();
		void closeSerial();
		void readLoop();
		bool sendCommand(uint16_t command_id);
		void pollCommands();
		void handlePacket(const MSPPacket &pkt);

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

		MSPParser parser_;
		std::vector<std::unique_ptr<IMspDecoder>> decoders_;
		std::vector<CommandSchedule> command_schedules_;
		rclcpp::TimerBase::SharedPtr poll_timer_;

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

	TransformerMspBridgeNode::TransformerMspBridgeNode(const rclcpp::NodeOptions &options)
			: rclcpp::Node("transformer_msp_bridge", options),
				parser_(std::bind(&TransformerMspBridgeNode::handlePacket, this, std::placeholders::_1))
	{
		port_ = declare_parameter<std::string>("port", "/dev/ttyAMA0");
		baudrate_ = declare_parameter<int>("baudrate", 115200);
		timeout_ms_ = declare_parameter<int>("timeout_ms", 50);
		rc_channel_count_ = static_cast<std::size_t>(declare_parameter<int>("rc_channel_count", 8));
		rc_publish_rate_hz_ = declare_parameter<double>("rc_publish_rate_hz", 10.0);
		debug_msp_ = declare_parameter<bool>("debug_msp", false);
		log_msp_tx_ = declare_parameter<bool>("log_msp_tx", false);
		log_msp_rx_ = declare_parameter<bool>("log_msp_rx", false);
		v2_fallback_timeout_sec_ = declare_parameter<double>("v2_fallback_timeout_sec", 5.0);
		force_msp_v2_ = declare_parameter<bool>("force_msp_v2", false);
		use_v2_tunnel_ = declare_parameter<bool>("use_v2_tunnel", false);
		use_v2_for_legacy_ = declare_parameter<bool>("use_v2_for_legacy", false);

		frame_id_imu_ = declare_parameter<std::string>("frame_id.imu", "base_link");
		frame_id_mag_ = declare_parameter<std::string>("frame_id.mag", frame_id_imu_);
		frame_id_gps_ = declare_parameter<std::string>("frame_id.gps", "gps");
		frame_id_altitude_ = declare_parameter<std::string>("frame_id.altitude", frame_id_imu_);
		frame_id_rangefinder_ = declare_parameter<std::string>("frame_id.rangefinder", frame_id_imu_);

		configurePublishers();
		configureDecoders();
		configureCommandSchedules();

		if (!openSerial())
		{
			throw std::runtime_error("Failed to open MSP serial port: " + port_);
		}

		poll_timer_ = create_wall_timer(std::chrono::milliseconds(20), std::bind(&TransformerMspBridgeNode::pollCommands, this));
	}

	TransformerMspBridgeNode::~TransformerMspBridgeNode()
	{
		running_.store(false);
		if (reader_thread_.joinable())
			reader_thread_.join();
		closeSerial();
	}

	void TransformerMspBridgeNode::configurePublishers()
	{
		imu_pub_ = create_publisher<sensor_msgs::msg::Imu>("/msp/imu", rclcpp::SensorDataQoS());
		mag_pub_ = create_publisher<sensor_msgs::msg::MagneticField>("/msp/mag", rclcpp::SensorDataQoS());
		attitude_pub_ = create_publisher<geometry_msgs::msg::Vector3>("/msp/attitude", rclcpp::QoS(10));
		altitude_pub_ = create_publisher<std_msgs::msg::Float32>("/msp/altitude", rclcpp::QoS(10));
		vertical_speed_pub_ = create_publisher<geometry_msgs::msg::TwistStamped>("/msp/vertical_speed", rclcpp::QoS(10));
		gps_fix_pub_ = create_publisher<sensor_msgs::msg::NavSatFix>("/msp/gps/fix", rclcpp::QoS(10));
		gps_vel_pub_ = create_publisher<geometry_msgs::msg::TwistStamped>("/msp/gps/vel", rclcpp::QoS(10));
		gps_home_vec_pub_ = create_publisher<geometry_msgs::msg::Vector3Stamped>("/msp/home/vector", rclcpp::QoS(10));
		gps_home_dist_pub_ = create_publisher<std_msgs::msg::Float32>("/msp/home/distance", rclcpp::QoS(10));
		rc_pub_ = create_publisher<std_msgs::msg::UInt16MultiArray>("/msp/rc", rclcpp::QoS(10));
		servo_pub_ = create_publisher<sensor_msgs::msg::JointState>("/msp/servo", rclcpp::QoS(10));
		motor_pub_ = create_publisher<sensor_msgs::msg::JointState>("/msp/motor", rclcpp::QoS(10));
		battery_pub_ = create_publisher<sensor_msgs::msg::BatteryState>("/msp/battery", rclcpp::QoS(10));
		battery_extended_pub_ = create_publisher<sensor_msgs::msg::BatteryState>("/msp/battery/dji", rclcpp::QoS(10));
		rangefinder_pub_ = create_publisher<std_msgs::msg::Float32>("/msp/rangefinder", rclcpp::QoS(10));
		compass_pub_ = create_publisher<geometry_msgs::msg::Vector3>("/msp/compass", rclcpp::QoS(10));
		barometer_pub_ = create_publisher<std_msgs::msg::Float32>("/msp/barometer", rclcpp::QoS(10));
		inav_status_pub_ = create_publisher<transformer_msp_bridge::msg::MspInavStatus>("/msp/inav_status", rclcpp::QoS(10));
		inav_generic_pub_ = create_publisher<diagnostic_msgs::msg::DiagnosticArray>("/msp/inav_generic", rclcpp::QoS(10));
		status_pub_ = create_publisher<diagnostic_msgs::msg::DiagnosticArray>("/msp/status_ex", rclcpp::QoS(10));
		sensor_status_pub_ = create_publisher<diagnostic_msgs::msg::DiagnosticArray>("/msp/sensors/status", rclcpp::QoS(10));
		gps_stats_status_pub_ = create_publisher<diagnostic_msgs::msg::DiagnosticStatus>("/msp/gps/statistics", rclcpp::QoS(10));
		gps_stats_array_pub_ = create_publisher<diagnostic_msgs::msg::DiagnosticArray>("/msp/gps/statistics_array", rclcpp::QoS(10));
		rc_tuning_pub_ = create_publisher<diagnostic_msgs::msg::DiagnosticArray>("/msp/rc/tuning", rclcpp::QoS(10));
		rtc_pub_ = create_publisher<diagnostic_msgs::msg::DiagnosticArray>("/msp/rtc", rclcpp::QoS(10));
	}

	void TransformerMspBridgeNode::configureDecoders()
	{
		decoders_.clear();

		decoders_.emplace_back(std::make_unique<ImuDecoder>(ImuDecoder::Callback([this](const ImuSample &sample) {
			publishImu(sample);
		})));

		decoders_.emplace_back(std::make_unique<AttitudeDecoder>(AttitudeDecoder::Callback([this](const AttitudeAngles &angles) {
			publishAttitude(angles);
		})));

		decoders_.emplace_back(std::make_unique<AltitudeDecoder>(AltitudeDecoder::Callback([this](const AltitudeSample &sample) {
			publishAltitude(sample);
		})));

		GpsDecoder::Callbacks gps_callbacks;
		gps_callbacks.raw = [this](const GpsRawData &data) { publishGpsRaw(data); };
		gps_callbacks.home = [this](const GpsHomeVector &data) { publishGpsHome(data); };
		decoders_.emplace_back(std::make_unique<GpsDecoder>(gps_callbacks));

		decoders_.emplace_back(std::make_unique<RcDecoder>(RcDecoder::Callback([this](const RcChannelsData &data) {
			publishRc(data);
		})));

		ServoMotorDecoder::Callbacks servo_callbacks;
		servo_callbacks.servo = [this](const ServoPositionData &data) { publishServo(data); };
		servo_callbacks.motor = [this](const MotorOutputData &data) { publishMotor(data); };
		decoders_.emplace_back(std::make_unique<ServoMotorDecoder>(servo_callbacks));

		BatteryDecoder::Callbacks battery_callbacks;
		battery_callbacks.analog = [this](const BatteryAnalogData &data) { publishBatteryAnalog(data); };
		battery_callbacks.status = [this](const BatteryStatusData &data) { publishBatteryStatus(data); };
		decoders_.emplace_back(std::make_unique<BatteryDecoder>(battery_callbacks));

		SensorDecoder::Callbacks sensor_callbacks;
		sensor_callbacks.rangefinder = [this](const RangefinderSample &sample) { publishRangefinder(sample); };
		sensor_callbacks.compass = [this](const CompassSample &sample) { publishCompass(sample); };
		sensor_callbacks.barometer = [this](const BarometerSample &sample) { publishBarometer(sample); };
		if (debug_msp_)
		{
			sensor_callbacks.log_info = [this](const std::string &message) { RCLCPP_INFO(get_logger(), "%s", message.c_str()); };
			sensor_callbacks.log_first_frame = true;
		}
		decoders_.emplace_back(std::make_unique<SensorDecoder>(sensor_callbacks));

		InavStatusDecoder::Callbacks inav_callbacks;
		inav_callbacks.status = [this](const InavStatusData &data) { publishInavStatus(data); };
		if (debug_msp_)
		{
			inav_callbacks.log_info = [this](const std::string &message) { RCLCPP_INFO(get_logger(), "%s", message.c_str()); };
			inav_callbacks.log_first_frame = true;
		}
		decoders_.emplace_back(std::make_unique<InavStatusDecoder>(inav_callbacks));

		decoders_.emplace_back(std::make_unique<InavGenericDecoder>(InavGenericDecoder::FrameCallback([this](const InavGenericFrame &frame) {
			publishInavGeneric(frame);
		})));

		SystemDecoder::Callbacks system_callbacks;
		system_callbacks.status_ex = [this](const SystemStatusExData &data) { publishStatusEx(data); };
		system_callbacks.sensor_status = [this](const SystemSensorStatusData &data) { publishSensorStatus(data); };
		system_callbacks.sensor_config = [this](const SystemSensorConfigData &data) { publishSensorConfig(data); };
		system_callbacks.gps_statistics = [this](const SystemGpsStatsData &data) { publishGpsStatistics(data); };
		system_callbacks.rc_tuning = [this](const RcTuningData &data) { publishRcTuning(data); };
		system_callbacks.rtc = [this](const SystemRtcData &data) { publishRtc(data); };
		decoders_.emplace_back(std::make_unique<SystemDecoder>(system_callbacks));
	}

	void TransformerMspBridgeNode::configureCommandSchedules()
	{
		static const std::array<CommandDefinition, 22> kCommandDefinitions = {{
			{"command.msp_raw_imu", msp::command_id("MSP_RAW_IMU"), 50.0, false},
			{"command.msp_servo", msp::command_id("MSP_SERVO"), 10.0, true},
			{"command.msp_motor", msp::command_id("MSP_MOTOR"), 10.0, true},
			{"command.msp_rc", msp::command_id("MSP_RC"), 5.0, true},
			{"command.msp_raw_gps", msp::command_id("MSP_RAW_GPS"), 5.0, true},
			{"command.msp_comp_gps", msp::command_id("MSP_COMP_GPS"), 2.0, true},
			{"command.msp_attitude", msp::command_id("MSP_ATTITUDE"), 10.0, true},
			{"command.msp_altitude", msp::command_id("MSP_ALTITUDE"), 5.0, true},
			{"command.msp_analog", msp::command_id("MSP_ANALOG"), 2.0, true},
			{"command.msp_rc_tuning", msp::command_id("MSP_RC_TUNING"), 0.2, false},
			{"command.msp_battery_state", msp::command_id("MSP_BATTERY_STATE"), 1.0, true},
			{"command.msp_rtc", msp::command_id("MSP_RTC"), 0.5, false},
			{"command.msp_status", msp::command_id("MSP_STATUS_EX"), 2.0, true},
			{"command.msp_sensor_config", msp::command_id("MSP_SENSOR_CONFIG"), 2.0, true},
			{"command.msp_sensor_status", msp::command_id("MSP_SENSOR_STATUS"), 2.0, true},
			{"command.msp_gpsstatistics", msp::command_id("MSP_GPSSTATISTICS"), 1.0, true},
			{"command.msp2_inav_status", msp::command_id("MSP2_INAV_STATUS"), 2.0, true},
			{"command.msp2_inav_analog", msp::command_id("MSP2_INAV_ANALOG"), 2.0, true},
			{"command.msp2_inav_battery_config", msp::command_id("MSP2_INAV_BATTERY_CONFIG"), 0.05, false},
			{"command.msp2_inav_air_speed", msp::command_id("MSP2_INAV_AIR_SPEED"), 5.0, true},
			{"command.msp2_inav_temperatures", msp::command_id("MSP2_INAV_TEMPERATURES"), 1.0, true},
			{"command.msp2_inav_esc_rpm", msp::command_id("MSP2_INAV_ESC_RPM"), 5.0, true},
		}};

		command_schedules_.clear();
		command_schedules_.reserve(kCommandDefinitions.size());

		const auto now = std::chrono::steady_clock::now();
		for (const auto &definition : kCommandDefinitions)
		{
			CommandSchedule schedule{};
			schedule.definition = definition;
			const std::string enabled_param = std::string(definition.param_key) + ".enabled";
			const std::string rate_param = std::string(definition.param_key) + ".rate_hz";

			schedule.enabled = declare_parameter<bool>(enabled_param, definition.default_enabled);
			schedule.rate_hz = declare_parameter<double>(rate_param, definition.default_rate_hz);

			if (!schedule.enabled || schedule.rate_hz <= 0.0)
			{
				schedule.enabled = false;
				schedule.period = std::chrono::steady_clock::duration::zero();
			}
			else
			{
				const double period_seconds = 1.0 / schedule.rate_hz;
				schedule.period = std::chrono::duration_cast<std::chrono::steady_clock::duration>(
						std::chrono::duration<double>(period_seconds));
				if (schedule.period.count() <= 0)
				{
					schedule.period = std::chrono::milliseconds(1);
				}
				schedule.next_fire = now + schedule.period;
			}

			command_schedules_.push_back(schedule);
		}
	}

	bool TransformerMspBridgeNode::openSerial()
	{
		std::lock_guard<std::mutex> lock(serial_mutex_);
		if (serial_ready_)
			return true;

		if (!serial_.open(port_, baudrate_, timeout_ms_))
		{
			RCLCPP_ERROR(get_logger(), "Failed to open serial port %s", port_.c_str());
			serial_ready_ = false;
			return false;
		}

		serial_ready_ = true;
		running_.store(true);
		reader_thread_ = std::thread(&TransformerMspBridgeNode::readLoop, this);
		RCLCPP_INFO(get_logger(), "Opened MSP serial port %s @ %d baud", port_.c_str(), baudrate_);
		return true;
	}

	void TransformerMspBridgeNode::closeSerial()
	{
		std::lock_guard<std::mutex> lock(serial_mutex_);
		serial_ready_ = false;
		serial_.close();
	}

	void TransformerMspBridgeNode::readLoop()
	{
		std::array<uint8_t, 512> buffer{};
		while (running_.load())
		{
			int bytes_read = 0;
			{
				std::lock_guard<std::mutex> lock(serial_mutex_);
				if (!serial_ready_)
					break;
				bytes_read = serial_.readSome(buffer.data(), buffer.size());
			}

			if (bytes_read > 0)
			{
				if (log_msp_rx_)
				{
					std::vector<uint8_t> chunk(buffer.begin(), buffer.begin() + bytes_read);
					RCLCPP_INFO(get_logger(), "MSP RX [%d]: %s", bytes_read, to_hex(chunk).c_str());
				}
				parser_.feed(buffer.data(), static_cast<std::size_t>(bytes_read));
			}
			else if (bytes_read == 0)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(2));
			}
			else
			{
				RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 2000, "Serial read error, retrying");
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}
		}
	}

	bool TransformerMspBridgeNode::sendCommand(uint16_t command_id)
	{
		std::vector<uint8_t> frame;
		const bool is_v2 = msp::is_v2(command_id);

		if (is_v2 || force_msp_v2_ || use_v2_for_legacy_)
		{
			if (use_v2_tunnel_ && !force_msp_v2_)
			{
				frame = buildPacketV2OverV1(command_id, {});
			}
			else
			{
				frame = buildPacketV2(command_id, {});
			}
		}
		else
		{
			frame = buildPacketRaw(static_cast<uint8_t>(command_id & 0xFF), {});
		}

		if (frame.empty())
			return false;

		if (log_msp_tx_)
		{
			const std::string_view name = msp::message_name(command_id);
			if (!name.empty())
			{
				RCLCPP_INFO(get_logger(), "MSP TX (%u %.*s): %s", static_cast<unsigned>(command_id),
							 static_cast<int>(name.size()), name.data(), to_hex(frame).c_str());
			}
			else
			{
				RCLCPP_INFO(get_logger(), "MSP TX (%u): %s", static_cast<unsigned>(command_id), to_hex(frame).c_str());
			}
		}

		std::lock_guard<std::mutex> lock(serial_mutex_);
		if (!serial_ready_)
			return false;
		return serial_.writeAll(frame.data(), frame.size());
	}

	void TransformerMspBridgeNode::pollCommands()
	{
		if (!serial_ready_)
			return;

		const auto now = std::chrono::steady_clock::now();
		for (auto &schedule : command_schedules_)
		{
			if (!schedule.enabled || schedule.period == std::chrono::steady_clock::duration::zero())
				continue;
			if (now < schedule.next_fire)
				continue;

			if (!sendCommand(schedule.definition.command_id))
			{
				RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 5000, "Failed to send MSP command %u",
														 static_cast<unsigned>(schedule.definition.command_id));
			}
			schedule.next_fire = now + schedule.period;
		}
	}

	void TransformerMspBridgeNode::handlePacket(const MSPPacket &pkt)
	{
		if (debug_msp_)
		{
			RCLCPP_DEBUG(get_logger(), "MSP RX cmd=%u len=%zu", static_cast<unsigned>(pkt.cmd), pkt.payload.size());
		}

		for (auto &decoder : decoders_)
		{
			if (decoder && decoder->matches(pkt.cmd))
			{
				decoder->decode(pkt);
			}
		}
	}

	void TransformerMspBridgeNode::publishImu(const ImuSample &sample)
	{
		if (imu_pub_)
		{
			sensor_msgs::msg::Imu msg;
			msg.header.stamp = now();
			msg.header.frame_id = frame_id_imu_;
			msg.orientation_covariance[0] = -1.0;
			msg.angular_velocity_covariance[0] = -1.0;
			msg.linear_acceleration_covariance[0] = -1.0;
			msg.linear_acceleration.x = sample.linear_acceleration_mps2[0];
			msg.linear_acceleration.y = sample.linear_acceleration_mps2[1];
			msg.linear_acceleration.z = sample.linear_acceleration_mps2[2];
			msg.angular_velocity.x = sample.angular_velocity_radps[0];
			msg.angular_velocity.y = sample.angular_velocity_radps[1];
			msg.angular_velocity.z = sample.angular_velocity_radps[2];
			imu_pub_->publish(msg);
		}

		if (mag_pub_)
		{
			sensor_msgs::msg::MagneticField mag;
			mag.header.stamp = now();
			mag.header.frame_id = frame_id_mag_;
			mag.magnetic_field.x = sample.magnetic_field_tesla[0];
			mag.magnetic_field.y = sample.magnetic_field_tesla[1];
			mag.magnetic_field.z = sample.magnetic_field_tesla[2];
			mag_pub_->publish(mag);
		}
	}

	void TransformerMspBridgeNode::publishAttitude(const AttitudeAngles &angles)
	{
		if (!attitude_pub_)
			return;
		geometry_msgs::msg::Vector3 msg;
		msg.x = angles.roll_deg;
		msg.y = angles.pitch_deg;
		msg.z = angles.yaw_deg;
		attitude_pub_->publish(msg);
	}

	void TransformerMspBridgeNode::publishAltitude(const AltitudeSample &sample)
	{
		if (altitude_pub_)
		{
			std_msgs::msg::Float32 msg;
			msg.data = sample.altitude_m;
			altitude_pub_->publish(msg);
		}

		if (vertical_speed_pub_)
		{
			geometry_msgs::msg::TwistStamped msg;
			msg.header.stamp = now();
			msg.header.frame_id = frame_id_altitude_;
			msg.twist.linear.z = sample.vertical_speed_mps;
			vertical_speed_pub_->publish(msg);
		}
	}

	void TransformerMspBridgeNode::publishGpsRaw(const GpsRawData &data)
	{
		if (!gps_fix_pub_ && !gps_vel_pub_)
			return;

		if (gps_fix_pub_)
		{
			sensor_msgs::msg::NavSatFix fix;
			fix.header.stamp = now();
			fix.header.frame_id = frame_id_gps_;
			fix.latitude = data.latitude_deg;
			fix.longitude = data.longitude_deg;
			fix.altitude = data.altitude_m;
			fix.status.service = sensor_msgs::msg::NavSatStatus::SERVICE_GPS;
			fix.status.status = data.fix_type > 0 ? sensor_msgs::msg::NavSatStatus::STATUS_FIX
																						: sensor_msgs::msg::NavSatStatus::STATUS_NO_FIX;
			fix.position_covariance_type = sensor_msgs::msg::NavSatFix::COVARIANCE_TYPE_UNKNOWN;
			gps_fix_pub_->publish(fix);
		}

		if (gps_vel_pub_)
		{
			geometry_msgs::msg::TwistStamped vel;
			vel.header.stamp = now();
			vel.header.frame_id = frame_id_gps_;
			vel.twist.linear.x = data.speed_mps;
			vel.twist.angular.z = data.course_rad;
			gps_vel_pub_->publish(vel);
		}
	}

	void TransformerMspBridgeNode::publishGpsHome(const GpsHomeVector &data)
	{
		if (gps_home_vec_pub_)
		{
			geometry_msgs::msg::Vector3Stamped vec;
			vec.header.stamp = now();
			vec.header.frame_id = frame_id_gps_;
			vec.vector.x = data.distance_m;
			vec.vector.y = data.direction_deg;
			vec.vector.z = 0.0;
			gps_home_vec_pub_->publish(vec);
		}

		if (gps_home_dist_pub_)
		{
			std_msgs::msg::Float32 dist;
			dist.data = static_cast<float>(data.distance_m);
			gps_home_dist_pub_->publish(dist);
		}
	}

	void TransformerMspBridgeNode::publishRc(const RcChannelsData &data)
	{
		if (!rc_pub_)
			return;
		std_msgs::msg::UInt16MultiArray msg;
		msg.data = data.channels;
		rc_pub_->publish(msg);
	}

	void TransformerMspBridgeNode::publishServo(const ServoPositionData &data)
	{
		if (!servo_pub_)
			return;
		sensor_msgs::msg::JointState msg;
		msg.header.stamp = now();
		msg.position = data.positions;
		servo_pub_->publish(msg);
	}

	void TransformerMspBridgeNode::publishMotor(const MotorOutputData &data)
	{
		if (!motor_pub_)
			return;
		sensor_msgs::msg::JointState msg;
		msg.header.stamp = now();
		msg.velocity = data.values;
		motor_pub_->publish(msg);
	}

	void TransformerMspBridgeNode::publishBatteryAnalog(const BatteryAnalogData &data)
	{
		if (!battery_pub_)
			return;
		sensor_msgs::msg::BatteryState msg;
		msg.header.stamp = now();
		msg.header.frame_id = frame_id_imu_;
		msg.voltage = data.voltage_v;
		msg.present = data.present;
		msg.percentage = std::numeric_limits<float>::quiet_NaN();
		msg.current = std::numeric_limits<float>::quiet_NaN();
		msg.charge = std::numeric_limits<float>::quiet_NaN();
		battery_pub_->publish(msg);
	}

	void TransformerMspBridgeNode::publishBatteryStatus(const BatteryStatusData &data)
	{
		if (!battery_extended_pub_)
			return;
		sensor_msgs::msg::BatteryState msg;
		msg.header.stamp = now();
		msg.header.frame_id = frame_id_imu_;
		msg.present = data.present;
		msg.voltage = data.voltage_v;
		msg.current = data.current_a;
		msg.charge = data.charge_c;
		msg.percentage = data.remaining_fraction;
		msg.cell_voltage = data.cell_voltage_v;
		battery_extended_pub_->publish(msg);
	}

	void TransformerMspBridgeNode::publishRangefinder(const RangefinderSample &sample)
	{
		if (!rangefinder_pub_)
			return;
		std_msgs::msg::Float32 msg;
		msg.data = sample.distance_m;
		rangefinder_pub_->publish(msg);
	}

	void TransformerMspBridgeNode::publishCompass(const CompassSample &sample)
	{
		if (!compass_pub_)
			return;
		geometry_msgs::msg::Vector3 msg;
		msg.x = static_cast<double>(sample.magnetic_field_mgauss[0]);
		msg.y = static_cast<double>(sample.magnetic_field_mgauss[1]);
		msg.z = static_cast<double>(sample.magnetic_field_mgauss[2]);
		compass_pub_->publish(msg);
	}

	void TransformerMspBridgeNode::publishBarometer(const BarometerSample &sample)
	{
		if (!barometer_pub_)
			return;
		std_msgs::msg::Float32 msg;
		msg.data = sample.pressure_pa;
		barometer_pub_->publish(msg);
	}

	void TransformerMspBridgeNode::publishInavStatus(const InavStatusData &data)
	{
		if (!inav_status_pub_)
			return;
		transformer_msp_bridge::msg::MspInavStatus msg;
		msg.cycle_time_us = data.cycle_time_us;
		msg.i2c_errors = data.i2c_errors;
		msg.sensor_status = data.sensor_status_mask;
		msg.cpu_load_percent = data.cpu_load_percent;
		msg.config_profile = data.config_profile;
		msg.battery_profile = data.battery_profile;
		msg.mixer_profile = data.mixer_profile;
		msg.arming_flags = data.arming_flags;
		msg.active_modes = data.active_modes;
		inav_status_pub_->publish(msg);
	}

	void TransformerMspBridgeNode::publishInavGeneric(const InavGenericFrame &frame)
	{
		if (!inav_generic_pub_)
			return;
		diagnostic_msgs::msg::DiagnosticStatus status;
		status.level = diagnostic_msgs::msg::DiagnosticStatus::OK;
		status.name = frame.description;
		status.hardware_id = "fc";
		diagnostic_msgs::msg::KeyValue kv;
		kv.key = "payload";
		kv.value = to_hex(frame.payload, false);
		status.values.push_back(std::move(kv));
		diagnostic_msgs::msg::DiagnosticArray array;
		array.header.stamp = now();
		array.status.push_back(std::move(status));
		inav_generic_pub_->publish(array);
	}

	void TransformerMspBridgeNode::publishStatusEx(const SystemStatusExData &data)
	{
		if (!status_pub_)
			return;
		diagnostic_msgs::msg::DiagnosticStatus status;
		status.level = diagnostic_msgs::msg::DiagnosticStatus::OK;
		status.name = "status_ex";
		status.hardware_id = "fc";
		append_key_value(status, "cycle_time_us", data.cycle_time_us);
		append_key_value(status, "i2c_errors", data.i2c_errors);
		append_key_value(status, "sensors_mask", data.sensors_mask);
		append_key_value(status, "mode_flags", data.mode_flags);
		append_key_value(status, "profile", data.profile);
		append_key_value(status, "system_load_pct", data.system_load_pct);
		append_key_value(status, "gyro_cycle_time_us", data.gyro_cycle_time_us);
		append_key_value(status, "last_arm_disable", data.last_arm_disable);
		append_key_value(status, "arming_flags", data.arming_flags);
		append_key_value(status, "acc_cal_running", data.acc_cal_running);
		diagnostic_msgs::msg::DiagnosticArray array;
		array.header.stamp = now();
		array.status.push_back(std::move(status));
		status_pub_->publish(array);
	}

	void TransformerMspBridgeNode::publishSensorStatus(const SystemSensorStatusData &data)
	{
		if (!sensor_status_pub_)
			return;
		diagnostic_msgs::msg::DiagnosticStatus status;
		status.level = diagnostic_msgs::msg::DiagnosticStatus::OK;
		status.name = "sensor_status";
		status.hardware_id = "fc";
		if (data.has_masks)
		{
			append_key_value(status, "present_mask", data.present_mask);
			append_key_value(status, "failing_mask", data.failing_mask);
		}
		else if (!data.raw_payload.empty())
		{
			diagnostic_msgs::msg::KeyValue kv;
			kv.key = "raw";
			kv.value = to_hex(data.raw_payload);
			status.values.push_back(std::move(kv));
		}
		diagnostic_msgs::msg::DiagnosticArray array;
		array.header.stamp = now();
		array.status.push_back(std::move(status));
		sensor_status_pub_->publish(array);
	}

	void TransformerMspBridgeNode::publishSensorConfig(const SystemSensorConfigData &data)
	{
		if (!sensor_status_pub_)
			return;
		diagnostic_msgs::msg::DiagnosticStatus status;
		status.level = diagnostic_msgs::msg::DiagnosticStatus::OK;
		status.name = "sensor_config";
		status.hardware_id = "fc";
		for (std::size_t i = 0; i < data.hardware_ids.size(); ++i)
		{
			diagnostic_msgs::msg::KeyValue kv;
			kv.key = "hardware[" + std::to_string(i) + "]";
			kv.value = std::to_string(data.hardware_ids[i]);
			status.values.push_back(std::move(kv));
		}
		if (!data.raw_tail.empty())
		{
			diagnostic_msgs::msg::KeyValue kv;
			kv.key = "raw_tail";
			kv.value = to_hex(data.raw_tail);
			status.values.push_back(std::move(kv));
		}
		diagnostic_msgs::msg::DiagnosticArray array;
		array.header.stamp = now();
		array.status.push_back(std::move(status));
		sensor_status_pub_->publish(array);
	}

	void TransformerMspBridgeNode::publishGpsStatistics(const SystemGpsStatsData &data)
	{
		diagnostic_msgs::msg::DiagnosticStatus status;
		status.level = diagnostic_msgs::msg::DiagnosticStatus::OK;
		status.name = "gps_statistics";
		status.hardware_id = "fc";
		append_key_value(status, "errors", data.errors);
		append_key_value(status, "timeouts", data.timeouts);
		append_key_value(status, "packet_count", data.packet_count);
		append_key_value(status, "packet_rejected", data.packet_rejected);
		append_key_value(status, "packet_ignored", data.packet_ignored);
		append_key_value(status, "packet_crc_error", data.packet_crc_error);
		append_key_value(status, "gps_reset_flags", data.gps_reset_flags);

		if (gps_stats_status_pub_)
		{
			gps_stats_status_pub_->publish(status);
		}

		if (gps_stats_array_pub_)
		{
			diagnostic_msgs::msg::DiagnosticArray array;
			array.header.stamp = now();
			array.status.push_back(std::move(status));
			gps_stats_array_pub_->publish(array);
		}
	}

	void TransformerMspBridgeNode::publishRcTuning(const RcTuningData &data)
	{
		if (!rc_tuning_pub_)
			return;
		diagnostic_msgs::msg::DiagnosticStatus status;
		status.level = diagnostic_msgs::msg::DiagnosticStatus::OK;
		status.name = "rc_tuning";
		status.hardware_id = "fc";
		append_key_value(status, "rc_rate", data.rc_rate);
		append_key_value(status, "rc_expo", data.rc_expo);
		append_key_value(status, "thr_mid", data.throttle_mid);
		append_key_value(status, "thr_expo", data.throttle_expo);
		append_key_value(status, "dyn_throttle_pid", data.dyn_throttle_pid);
		append_key_value(status, "rc_yaw_expo", data.rc_yaw_expo);
		append_key_value(status, "rc_yaw_rate", data.rc_yaw_rate);
		append_key_value(status, "rc_pitch_rate", data.rc_pitch_rate);
		append_key_value(status, "rc_roll_rate", data.rc_roll_rate);
		append_key_value(status, "tpa_breakpoint", data.tpa_breakpoint);
		diagnostic_msgs::msg::DiagnosticArray array;
		array.header.stamp = now();
		array.status.push_back(std::move(status));
		rc_tuning_pub_->publish(array);
	}

	void TransformerMspBridgeNode::publishRtc(const SystemRtcData &data)
	{
		if (!rtc_pub_)
			return;
		diagnostic_msgs::msg::DiagnosticStatus status;
		status.level = diagnostic_msgs::msg::DiagnosticStatus::OK;
		status.name = "rtc";
		status.hardware_id = "fc";
		append_key_value(status, "seconds", data.seconds);
		append_key_value(status, "millis", data.millis);
		diagnostic_msgs::msg::DiagnosticArray array;
		array.header.stamp = now();
		array.status.push_back(std::move(status));
		rtc_pub_->publish(array);
	}

} // namespace transformer_msp_bridge

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	try
	{
		auto node = std::make_shared<transformer_msp_bridge::TransformerMspBridgeNode>();
		rclcpp::spin(node);
	}
	catch (const std::exception &ex)
	{
		RCLCPP_FATAL(rclcpp::get_logger("transformer_msp_bridge"), "%s", ex.what());
	}
	rclcpp::shutdown();
	return 0;
}

