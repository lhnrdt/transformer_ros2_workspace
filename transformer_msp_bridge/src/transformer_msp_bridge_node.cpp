#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/u_int16_multi_array.hpp>
#include <geometry_msgs/msg/vector3.hpp>
#include <sensor_msgs/msg/battery_state.hpp>
#include <std_msgs/msg/float32.hpp>
#include "transformer_msp_bridge/msg/msp_inav_status.hpp"
#include "msp/msp_protocol_v2_sensor_msg.h" // packed v2 sensor structs

#include "transformer_msp_bridge/msp_protocol.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include "transformer_msp_bridge/serial_port.hpp"

#include <thread>
#include <mutex>
#include <atomic>
#include <unordered_map>
#include <algorithm>

using std::placeholders::_1;

namespace transformer_msp_bridge
{

  class MSPBridgeNode : public rclcpp::Node
  {
  public:
    MSPBridgeNode() : Node("transformer_msp_bridge")
    {
      port_ = declare_parameter<std::string>("port", "/dev/ttyAMA0");
      baud_ = declare_parameter<int>("baudrate", 115200);
      timeout_ms_ = declare_parameter<int>("timeout_ms", 50);
      rc_channel_count_ = declare_parameter<int>("rc_channel_count", 8);
      poll_rate_hz_ = declare_parameter<double>("telemetry_poll_rate_hz", 10.0);
      rc_echo_rate_hz_ = declare_parameter<double>("rc_publish_rate_hz", 10.0);
      debug_msp_ = declare_parameter<bool>("debug_msp", false);
      log_msp_tx_ = declare_parameter<bool>("log_msp_tx", false);
      log_msp_rx_ = declare_parameter<bool>("log_msp_rx", false);
      v2_fallback_timeout_sec_ = declare_parameter<double>("v2_fallback_timeout_sec", 5.0);
      force_msp_v2_ = declare_parameter<bool>("force_msp_v2", false);
      use_v2_tunnel_ = declare_parameter<bool>("use_v2_tunnel", false);
  use_v2_for_legacy_ = declare_parameter<bool>("use_v2_for_legacy", false); // probe legacy cmds as native v2

      if (!serial_.open(port_, baud_, timeout_ms_))
      {
        RCLCPP_FATAL(get_logger(), "Failed to open serial port %s", port_.c_str());
        throw std::runtime_error("serial open failed");
      }

      parser_ = std::make_unique<MSPParser>([this](const MSPPacket &pkt)
                                            { this->dispatchPacket(pkt); });

      // Build manual registry (can be extended later manually)
      registry_ = build_default_registry();
      // Bootstrap commands (always v1) before enabling v2 sensors
  // Negotiation order: IDENT (if supported) -> API_VERSION -> FC_VARIANT -> FC_VERSION
  bootstrap_cmds_ = {(uint16_t)MSP_IDENT, (uint16_t)MSP_API_VERSION, (uint16_t)MSP_FC_VARIANT, (uint16_t)MSP_FC_VERSION};
      // Attach decode callbacks where needed (assign lambda capturing this)
      for (auto &d : registry_)
      {
        if (d.id == MSP_ATTITUDE)
          d.decode_cb = [this](const MSPPacket &pkt)
          { this->decodeAttitude(pkt); };
        else if (d.id == MSP_RC)
          d.decode_cb = [this](const MSPPacket &pkt)
          { this->decodeRc(pkt); };
        else if (d.id == MSP_ANALOG)
          d.decode_cb = [this](const MSPPacket &pkt)
          { this->decodeAnalog(pkt); };
        else if (d.id == 0x1F01 /*MSP2_SENSOR_RANGEFINDER*/)
          d.decode_cb = [this](const MSPPacket &pkt)
          { this->decodeRangefinder(pkt); };
        else if (d.id == 0x1F04 /*MSP2_SENSOR_COMPASS*/)
          d.decode_cb = [this](const MSPPacket &pkt)
          { this->decodeCompass(pkt); };
        else if (d.id == 0x1F05 /*MSP2_SENSOR_BAROMETER*/)
          d.decode_cb = [this](const MSPPacket &pkt)
          { this->decodeBarometer(pkt); };
        else if (d.id == 0x2000 /*MSP2_INAV_STATUS*/)
          d.decode_cb = [this](const MSPPacket &pkt)
          { this->decodeInavStatus(pkt); };
      }

      rc_pub_ = create_publisher<std_msgs::msg::UInt16MultiArray>("/msp/rc_out", 10);
      attitude_pub_ = create_publisher<geometry_msgs::msg::Vector3>("/msp/attitude", 10);
      rc_in_pub_ = create_publisher<std_msgs::msg::UInt16MultiArray>("/msp/rc_in", 10);
      battery_pub_ = create_publisher<sensor_msgs::msg::BatteryState>("/msp/battery", 10);
      rangefinder_pub_ = create_publisher<std_msgs::msg::Float32>("/msp/rangefinder", 10);
      compass_pub_ = create_publisher<geometry_msgs::msg::Vector3>("/msp/compass", 10);
      barometer_pub_ = create_publisher<std_msgs::msg::Float32>("/msp/barometer", 10);
  inav_status_pub_ = create_publisher<transformer_msp_bridge::msg::MspInavStatus>("/msp/inav_status", 10);

      rc_sub_ = create_subscription<std_msgs::msg::UInt16MultiArray>(
          "/msp/rc_override", 10, std::bind(&MSPBridgeNode::rcCallback, this, _1));

      // Timers
      read_timer_ = create_wall_timer(std::chrono::milliseconds(5), std::bind(&MSPBridgeNode::readLoop, this));
      if (rc_echo_rate_hz_ > 0)
      {
        rc_timer_ = create_wall_timer(std::chrono::milliseconds((int)(1000.0 / rc_echo_rate_hz_)), std::bind(&MSPBridgeNode::publishRC, this));
      }
      // Poll timer: iterate registry and send requests whose period elapsed
      poll_timer_ = create_wall_timer(std::chrono::milliseconds(50), std::bind(&MSPBridgeNode::pollTelemetry, this));
      stats_timer_ = create_wall_timer(std::chrono::seconds(10), std::bind(&MSPBridgeNode::logStats, this));

      current_rc_.assign(rc_channel_count_, 1500);
    }

  private:
    template <typename T>
    bool decodeStruct(const MSPPacket &pkt, T &out)
    {
      if (pkt.payload.size() < sizeof(T))
        return false;
      // MSP is little-endian; target assumed little-endian platform (ARM/x86). If not, manual field swap needed.
      std::memcpy(&out, pkt.payload.data(), sizeof(T));
      return true;
    }
    void rcCallback(const std_msgs::msg::UInt16MultiArray::SharedPtr msg)
    {
      size_t n = std::min<size_t>(msg->data.size(), (size_t)rc_channel_count_);
      if (n == 0)
        return;
      for (size_t i = 0; i < n; i++)
        current_rc_[i] = msg->data[i];
      // Send immediately
      auto pkt = buildPacket(MSP_SET_RAW_RC, current_rc_);
      serial_.writeAll(pkt.data(), pkt.size());
    }

    void publishRC()
    {
      std_msgs::msg::UInt16MultiArray m;
      m.data = current_rc_;
      rc_pub_->publish(std::move(m));
    }

    void pollTelemetry()
    {
      const auto now = std::chrono::steady_clock::now();

      // Handle bootstrap first
      if (!bootstrap_done_)
      {
        if (!bootstrap_cmds_.empty())
        {
          uint16_t cmd = bootstrap_cmds_.front();
          auto frame = buildPacketRaw(static_cast<uint8_t>(cmd), {}); // v1 only
          writeFrame(frame);
          bootstrap_cmds_.pop_front();
          return; // send one bootstrap per cycle
        }
        else
        {
          bootstrap_done_ = true;
          bootstrap_completed_time_ = now;
        }
      }

      // Check v2 fallback
      if (!force_msp_v2_ && v2_enabled_attempted_ && !v2_confirmed_)
      {
        auto elapsed = std::chrono::duration<double>(now - bootstrap_completed_time_).count();
        if (elapsed > v2_fallback_timeout_sec_ && !v2_fallback_applied_)
        {
          // Disable v2-required commands
          for (auto &d : registry_)
          {
            if (d.requires_v2)
              d.poll_rate_hz = 0.0;
          }
          v2_fallback_applied_ = true;
          RCLCPP_WARN(get_logger(), "No v2 frames within %.1fs -> disabling v2 sensor polling (set force_msp_v2 to override)", v2_fallback_timeout_sec_);
        }
      }

      for (auto &meta : registry_)
      {
        if (meta.poll_rate_hz <= 0.0)
          continue;
        if (meta.requires_v2 && !v2_confirmed_)
        {
          // Mark that we attempted v2 usage
          v2_enabled_attempted_ = true;
          if (v2_fallback_applied_)
            continue; // already disabled
        }
        auto period = std::chrono::duration<double>(1.0 / meta.poll_rate_hz);
        auto &last = last_sent_[meta.id];
        if (last.time_since_epoch().count() == 0 || now - last >= period)
        {
          if (meta.build_request_cb)
          {
            auto frame = meta.build_request_cb();
            // Optionally probe legacy commands via native v2 (IDs < 256) if negotiated proto>=2
            bool legacy_id = meta.id < 256;
            if (!meta.requires_v2 && use_v2_for_legacy_ && proto_supports_v2_ && legacy_id && !use_v2_tunnel_)
            {
              frame = buildPacketV2(static_cast<uint16_t>(meta.id), {}, 0);
            }
            else if (use_v2_tunnel_ && meta.requires_v2)
            {
              frame = buildPacketV2OverV1(meta.id, {}, 0);
            }
            // Track TX counters heuristically by inspecting frame header
            if (!frame.empty()) {
              if (frame.size() >= 3 && frame[0] == '$' && frame[1] == 'X') {
                native_v2_tx_++;
              } else if (frame.size() >= 6 && frame[0] == '$' && frame[1] == 'M' && frame[4] == 255) {
                // tunneled v2 frame (cmd 255)
                tunneled_v2_tx_++;
              }
            }
            writeFrame(frame);
            last = now;
          }
        }
      }
    }

    void readLoop()
    {
      uint8_t buf[256];
      int n = serial_.readSome(buf, sizeof(buf));
      if (n > 0)
      {
        for (int i = 0; i < n; i++)
          parser_->input(buf[i]);
      }
    }

    void dispatchPacket(const MSPPacket &pkt)
    {
      if (log_msp_rx_)
      {
        const auto &raw = parser_->currentFrameBytes();
        std::ostringstream oss;
        oss << (pkt.version == MSPVersion::V2 ? "RX V2 [" : "RX V1 [") << raw.size() << "]:";
        for (auto b : raw)
        {
          oss << ' ' << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (int)b;
        }
        RCLCPP_INFO(get_logger(), "%s cmd=0x%04X len=%zu", oss.str().c_str(), pkt.cmd, pkt.payload.size());
      }
      // Stats
      if (pkt.version == MSPVersion::V1)
        stats_.frames_v1++;
      else if (pkt.version == MSPVersion::V2)
      {
        stats_.frames_v2++;
        last_v2_rx_ = std::chrono::steady_clock::now();
        v2_confirmed_ = true;
      }
      if (pkt.version == MSPVersion::V2 && pkt.payload.empty())
      {
        // Possibly an ack with no payload; ignore
      }

      // Handle bootstrap responses
      if (pkt.cmd == MSP_IDENT && !ident_received_)
      {
        ident_received_ = true;
        // Classic MSP_IDENT payload (legacy MultiWii): (version, multiType, msp_version, capability[4])
        if (pkt.payload.size() >= 7)
        {
          uint8_t mw_version = pkt.payload[0];
          uint8_t mw_multitype = pkt.payload[1];
          uint8_t mw_msp_version = pkt.payload[2];
          RCLCPP_INFO(get_logger(), "MSP_IDENT: mw_version=%u multitype=%u msp_version=%u (legacy signature)", mw_version, mw_multitype, mw_msp_version);
          // Legacy MultiWii does not speak MSP v2; keep v1 only polling.
        }
        else
        {
          // Some firmwares might respond with different length; log generically.
          RCLCPP_INFO(get_logger(), "MSP_IDENT received (%zu bytes)", pkt.payload.size());
        }
      }
      else if (pkt.cmd == MSP_API_VERSION && !api_version_received_)
      {
        if (pkt.payload.size() >= 3)
        {
          uint8_t api_major = pkt.payload[0];
          uint8_t api_minor = pkt.payload[1];
          uint8_t proto_ver = pkt.payload[2];
          api_version_received_ = true;
          RCLCPP_INFO(get_logger(), "MSP_API_VERSION: api=%u.%u proto=%u", api_major, api_minor, proto_ver);
          if (proto_ver >= 2)
          {
            RCLCPP_INFO(get_logger(), "Protocol v2 supported; continuing v2 sensor polling.");
            proto_supports_v2_ = true; // allow probing before first native v2 rx
          }
          else
          {
            RCLCPP_WARN(get_logger(), "Protocol v2 NOT supported (proto=%u); disabling v2 sensors.", proto_ver);
            for (auto &d : registry_)
              if (d.requires_v2)
                d.poll_rate_hz = 0.0;
            v2_fallback_applied_ = true;
          }
        }
      }
      else if (pkt.cmd == MSP_FC_VARIANT)
      {
        std::string variant(pkt.payload.begin(), pkt.payload.end());
        RCLCPP_INFO(get_logger(), "MSP_FC_VARIANT: %s", variant.c_str());
      }
      else if (pkt.cmd == MSP_FC_VERSION)
      {
        if (pkt.payload.size() >= 3)
        {
          RCLCPP_INFO(get_logger(), "MSP_FC_VERSION: %u.%u.%u", pkt.payload[0], pkt.payload[1], pkt.payload[2]);
        }
      }

      auto it = std::find_if(registry_.begin(), registry_.end(), [&](const CommandDescriptor &d)
                             { return d.id == pkt.cmd; });
      if (it != registry_.end() && it->decode_cb)
      {
        it->decode_cb(pkt);
      }
    }

    void writeFrame(const std::vector<uint8_t> &frame)
    {
      serial_.writeAll(frame.data(), frame.size());
      if (log_msp_tx_)
      {
        std::ostringstream oss;
        oss << "TX [" << frame.size() << "]:";
        for (auto b : frame)
        {
          oss << ' ' << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (int)b;
        }
        RCLCPP_INFO(get_logger(), "%s", oss.str().c_str());
      }
    }

    void logStats()
    {
      if (!debug_msp_)
        return;
      const auto &ps = parser_->stats();
      RCLCPP_INFO(get_logger(), "MSP stats: v1=%llu v2_native_rx=%llu v2_tunnel_rx=%llu v2_native_crc_fail=%llu v2_tunnel_crc_fail=%llu v2_native_tx=%llu v2_tunnel_tx=%llu v2_confirmed=%s fallback_applied=%s", (unsigned long long)stats_.frames_v1, (unsigned long long)ps.native_v2_rx, (unsigned long long)ps.tunneled_v2_rx, (unsigned long long)ps.native_v2_crc_fail, (unsigned long long)ps.tunneled_v2_crc_fail, (unsigned long long)native_v2_tx_, (unsigned long long)tunneled_v2_tx_, v2_confirmed_ ? "yes" : "no", v2_fallback_applied_ ? "yes" : "no");
    }

    void decodeAttitude(const MSPPacket &pkt)
    {
      if (pkt.payload.size() < 6)
        return;
      int16_t roll = (int16_t)(pkt.payload[0] | (pkt.payload[1] << 8));
      int16_t pitch = (int16_t)(pkt.payload[2] | (pkt.payload[3] << 8));
      int16_t yaw = (int16_t)(pkt.payload[4] | (pkt.payload[5] << 8));
      geometry_msgs::msg::Vector3 v;
      v.x = roll / 10.0;
      v.y = pitch / 10.0;
      v.z = yaw / 10.0;
      attitude_pub_->publish(std::move(v));
    }

    void decodeRc(const MSPPacket &pkt)
    {
      if (pkt.payload.size() < 16)
        return; // at least 8 channels *2
      std::vector<uint16_t> chans;
      size_t n = pkt.payload.size() / 2;
      chans.reserve(n);
      for (size_t i = 0; i < n; i++)
      {
        uint16_t v = pkt.payload[2 * i] | (pkt.payload[2 * i + 1] << 8);
        chans.push_back(v);
      }
      std_msgs::msg::UInt16MultiArray m;
      m.data = std::move(chans);
      rc_in_pub_->publish(std::move(m));
    }

    void decodeAnalog(const MSPPacket &pkt)
    {
      if (pkt.payload.size() < 1)
        return;
      uint8_t vbat_raw = pkt.payload[0]; // 0.1V units typical
      float voltage = vbat_raw / 10.0f;
      sensor_msgs::msg::BatteryState b;
      b.voltage = voltage;
      b.present = true;
      b.percentage = std::numeric_limits<float>::quiet_NaN();
      b.current = std::numeric_limits<float>::quiet_NaN();
      b.charge = std::numeric_limits<float>::quiet_NaN();
      battery_pub_->publish(std::move(b));
    }

    void decodeRangefinder(const MSPPacket &pkt)
    {
      mspSensorRangefinderDataMessage_t rf{};
      if (!decodeStruct(pkt, rf))
        return;
      std_msgs::msg::Float32 msg;
      if (rf.distanceMm < 0)
        msg.data = std::numeric_limits<float>::quiet_NaN();
      else
        msg.data = rf.distanceMm / 1000.0f;
      rangefinder_pub_->publish(msg);
      if (debug_msp_ && !logged_rangefinder_)
      {
        RCLCPP_INFO(get_logger(), "Rangefinder first frame: quality=%u dist_m=%.3f", rf.quality, msg.data);
        logged_rangefinder_ = true;
      }
    }

    void decodeCompass(const MSPPacket &pkt)
    {
      mspSensorCompassDataMessage_t comp{};
      if (!decodeStruct(pkt, comp))
        return;
      geometry_msgs::msg::Vector3 v;
      v.x = comp.magX;
      v.y = comp.magY;
      v.z = comp.magZ;
      compass_pub_->publish(v);
      if (debug_msp_ && !logged_compass_)
      {
        RCLCPP_INFO(get_logger(), "Compass first frame: inst=%u timeMs=%u mGauss=(%d,%d,%d)", comp.instance, comp.timeMs, comp.magX, comp.magY, comp.magZ);
        logged_compass_ = true;
      }
    }

    void decodeBarometer(const MSPPacket &pkt)
    {
      mspSensorBaroDataMessage_t baro{};
      if (!decodeStruct(pkt, baro))
        return;
      std_msgs::msg::Float32 m;
      m.data = baro.pressurePa;
      barometer_pub_->publish(m);
      if (debug_msp_ && !logged_baro_)
      {
        RCLCPP_INFO(get_logger(), "Barometer first frame: inst=%u timeMs=%u pressure=%.2fPa temp=%.2fC", baro.instance, baro.timeMs, baro.pressurePa, baro.temp / 100.0f);
        logged_baro_ = true;
      }
    }

    void decodeInavStatus(const MSPPacket &pkt)
    {
      // Expected minimal payload structure based on provided spec (dynamic tail for activeModes bitmask)
      // cycleTime(2) i2cErrors(2) sensorStatus(2) cpuLoad(2) profileAndBatt(1) armingFlags(4) activeModes(var) mixerProfile(1)
      if (pkt.payload.size() < 2+2+2+2+1+4+1) return; // minimal sanity (activeModes at least 0 bytes)
      const uint8_t *p = pkt.payload.data();
      auto rd16 = [&](size_t off){ return (uint16_t)(p[off] | (p[off+1] << 8)); };
      uint16_t cycleTime = rd16(0);
      uint16_t i2cErrors = rd16(2);
      uint16_t sensorStatus = rd16(4);
      uint16_t cpuLoad = rd16(6);
      uint8_t profileAndBatt = p[8];
      uint32_t armingFlags = (uint32_t)p[9] | ((uint32_t)p[10] << 8) | ((uint32_t)p[11] << 16) | ((uint32_t)p[12] << 24);
      size_t activeModesStart = 13;
      if (pkt.payload.size() <= activeModesStart) return;
      size_t mixerProfilePos = pkt.payload.size() - 1;
      uint8_t mixerProfile = pkt.payload[mixerProfilePos];
      size_t activeModesLen = mixerProfilePos - activeModesStart; // could be 0
      transformer_msp_bridge::msg::MspInavStatus msg;
      msg.cycle_time_us = cycleTime;
      msg.i2c_errors = i2cErrors;
      msg.sensor_status = sensorStatus;
      msg.cpu_load_percent = cpuLoad;
      msg.config_profile = (uint8_t)(profileAndBatt & 0x0F);
      msg.battery_profile = (uint8_t)((profileAndBatt >> 4) & 0x0F);
      msg.mixer_profile = mixerProfile;
      msg.arming_flags = armingFlags;
      if (activeModesLen > 0) {
        msg.active_modes.assign(pkt.payload.begin() + activeModesStart, pkt.payload.begin() + activeModesStart + activeModesLen);
      }
      inav_status_pub_->publish(msg);
      // For now log first frame summary
      if (debug_msp_ && !logged_inav_status_) {
        RCLCPP_INFO(get_logger(), "INAV_STATUS: cycle=%u us cpu=%u%% i2cErr=%u sensorMask=0x%04X arming=0x%08X activeModesLen=%zu profile=%u battProfile=%u mixer=%u", cycleTime, cpuLoad, i2cErrors, sensorStatus, armingFlags, activeModesLen, (unsigned)(profileAndBatt & 0x0F), (unsigned)((profileAndBatt >> 4) & 0x0F), mixerProfile);
        logged_inav_status_ = true;
      }
    }

    // Params
    std::string port_;
    int baud_{115200};
    int timeout_ms_{50};
    int rc_channel_count_{8};
    double poll_rate_hz_{10.0}; // retained but superseded by per-command poll rates
    double rc_echo_rate_hz_{10.0};
    bool debug_msp_{false};
    bool log_msp_tx_{false};
    bool log_msp_rx_{false};
    double v2_fallback_timeout_sec_{5.0};
    bool force_msp_v2_{false};
    bool use_v2_tunnel_{false};
  bool use_v2_for_legacy_{false};

    SerialPort serial_;
    std::unique_ptr<MSPParser> parser_;

    std::vector<uint16_t> current_rc_;

    rclcpp::Publisher<std_msgs::msg::UInt16MultiArray>::SharedPtr rc_pub_;
    rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr attitude_pub_;
    rclcpp::Publisher<std_msgs::msg::UInt16MultiArray>::SharedPtr rc_in_pub_;
    rclcpp::Publisher<sensor_msgs::msg::BatteryState>::SharedPtr battery_pub_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr rangefinder_pub_;
    rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr compass_pub_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr barometer_pub_;
  rclcpp::Publisher<transformer_msp_bridge::msg::MspInavStatus>::SharedPtr inav_status_pub_;

    // First-frame logging flags
    bool logged_rangefinder_{false};
    bool logged_compass_{false};
    bool logged_baro_{false};
  bool logged_inav_status_{false};
    rclcpp::Subscription<std_msgs::msg::UInt16MultiArray>::SharedPtr rc_sub_;

    rclcpp::TimerBase::SharedPtr read_timer_;
    rclcpp::TimerBase::SharedPtr rc_timer_;
    rclcpp::TimerBase::SharedPtr poll_timer_;

    // Registry-driven polling
    std::vector<CommandDescriptor> registry_;
    std::unordered_map<uint16_t, std::chrono::steady_clock::time_point> last_sent_;

    // Bootstrap & version negotiation
    std::deque<uint16_t> bootstrap_cmds_;
    bool bootstrap_done_{false};
    bool api_version_received_{false};
  bool ident_received_{false};
    std::chrono::steady_clock::time_point bootstrap_completed_time_{};

    // V2 state
    bool v2_confirmed_{false};
    bool v2_fallback_applied_{false};
    bool v2_enabled_attempted_{false};
    std::chrono::steady_clock::time_point last_v2_rx_{};
  bool proto_supports_v2_{false}; // from API_VERSION proto>=2

    struct MSPStats
    {
      uint64_t frames_v1{0};
      uint64_t frames_v2{0};
    } stats_;

    // TX counters
    uint64_t native_v2_tx_{0};
    uint64_t tunneled_v2_tx_{0};

    rclcpp::TimerBase::SharedPtr stats_timer_;
  };

} // namespace transformer_msp_bridge

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<transformer_msp_bridge::MSPBridgeNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
