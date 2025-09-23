// Clean reconstruction of node implementation
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/u_int16_multi_array.hpp>
#include <std_msgs/msg/float32.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <diagnostic_msgs/msg/diagnostic_array.hpp>
#include <diagnostic_msgs/msg/diagnostic_status.hpp>

#include "transformer_msp_bridge/serial_port.hpp"
#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/msp_builders.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"

#include "transformer_msp_bridge/decoders/imu_decoder.hpp"
#include "transformer_msp_bridge/decoders/gps_decoder.hpp"
#include "transformer_msp_bridge/decoders/altitude_decoder.hpp"
#include "transformer_msp_bridge/decoders/servo_motor_decoder.hpp"
#include "transformer_msp_bridge/decoders/sensor_decoder.hpp"
#include "transformer_msp_bridge/decoders/inav_status_decoder.hpp"
#include "transformer_msp_bridge/decoders/attitude_decoder.hpp"
#include "transformer_msp_bridge/decoders/rc_decoder.hpp"
#include "transformer_msp_bridge/decoders/system_decoder.hpp"
#include "transformer_msp_bridge/decoders/battery_decoder.hpp"
#include "transformer_msp_bridge/decoder_registry.hpp"

#include <deque>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <iomanip>

using std::placeholders::_1;

namespace transformer_msp_bridge {

class MSPBridgeNode : public rclcpp::Node {
public:
  MSPBridgeNode() : rclcpp::Node("transformer_msp_bridge") {
    // Core params
    port_ = declare_parameter<std::string>("port", "/dev/ttyAMA0");
    baud_ = declare_parameter<int>("baudrate", 115200);
    timeout_ms_ = declare_parameter<int>("timeout_ms", 50);
    rc_channel_count_ = declare_parameter<int>("rc_channel_count", 8);
    rc_echo_rate_hz_ = declare_parameter<double>("rc_publish_rate_hz", 10.0);
    debug_msp_ = declare_parameter<bool>("debug_msp", false);
    log_msp_tx_ = declare_parameter<bool>("log_msp_tx", false);
    log_msp_rx_ = declare_parameter<bool>("log_msp_rx", false);
    v2_fallback_timeout_sec_ = declare_parameter<double>("v2_fallback_timeout_sec", 5.0);
    force_msp_v2_ = declare_parameter<bool>("force_msp_v2", false);
    use_v2_tunnel_ = declare_parameter<bool>("use_v2_tunnel", false);
    use_v2_for_legacy_ = declare_parameter<bool>("use_v2_for_legacy", false);

    if (!serial_.open(port_, baud_, timeout_ms_)) {
      RCLCPP_FATAL(get_logger(), "Failed to open %s", port_.c_str());
      throw std::runtime_error("serial open failed");
    }

    parser_ = std::make_unique<MSPParser>([this](const MSPPacket &pkt){ dispatchPacket(pkt); });
    registry_ = build_default_registry();
    bootstrap_cmds_ = {(uint16_t)MSP_IDENT, (uint16_t)MSP_API_VERSION, (uint16_t)MSP_FC_VARIANT, (uint16_t)MSP_FC_VERSION};

    // Register all decoders (interface-based) directly in registry
    decoder_registry_.add(std::unique_ptr<IMspDecoder>(new ImuDecoder(*this)));
    decoder_registry_.add(std::unique_ptr<IMspDecoder>(new GpsDecoder(*this)));
    decoder_registry_.add(std::unique_ptr<IMspDecoder>(new AltitudeDecoder(*this)));
    decoder_registry_.add(std::unique_ptr<IMspDecoder>(new ServoMotorDecoder(*this)));
    decoder_registry_.add(std::unique_ptr<IMspDecoder>(new SensorDecoder(*this, debug_msp_)));
    decoder_registry_.add(std::unique_ptr<IMspDecoder>(new InavStatusDecoder(*this, debug_msp_)));
    decoder_registry_.add(std::unique_ptr<IMspDecoder>(new AttitudeDecoder(*this)));
    decoder_registry_.add(std::unique_ptr<IMspDecoder>(new RcDecoder(*this, std::string("/msp/rc_in"))));
    decoder_registry_.add(std::unique_ptr<IMspDecoder>(new SystemDecoder(*this)));
    decoder_registry_.add(std::unique_ptr<IMspDecoder>(new BatteryDecoder(*this)));

    setupPublishersAndSubs();
    declareCommandParameters();
    installParamCallback();
    setupTimers();
  }

private:
  struct ScheduleEntry {
    std::chrono::steady_clock::time_point due{};
    uint16_t id{};
    ScheduleEntry() = default;
    ScheduleEntry(std::chrono::steady_clock::time_point d, uint16_t i) : due(d), id(i) {}
    bool operator<(const ScheduleEntry &o) const { return due > o.due; }
  };


  static std::string sanitizeName(const char *raw) {
    if (!raw) return {};
    std::string s(raw), out; out.reserve(s.size());
    for (char c : s) out.push_back(std::isalnum((unsigned char)c)? std::tolower(c): '_');
    std::string collapsed; collapsed.reserve(out.size()); bool prev=false; for(char c: out){ if(c=='_'){ if(!prev) collapsed.push_back(c); prev=true; } else { collapsed.push_back(c); prev=false; } }
    while(!collapsed.empty() && collapsed.front()=='_') collapsed.erase(collapsed.begin());
    while(!collapsed.empty() && collapsed.back()=='_') collapsed.pop_back();
    return collapsed;
  }

  void declareCommandParameters() {
    for (auto &d : registry_) {
      std::string base = d.name? sanitizeName(d.name): std::string();
      if (base.empty()) {
        std::ostringstream oss; oss << "cmd_" << std::hex << std::setw(4) << std::setfill('0') << d.id; base = oss.str();
      }
      std::string enabled_param = std::string("command.") + base + ".enabled";
      std::string rate_param = std::string("command.") + base + ".rate_hz";
      bool def_enabled = d.poll_rate_hz > 0.0;
      double def_rate = d.poll_rate_hz;
      bool enabled = declare_parameter<bool>(enabled_param, def_enabled);
      double rate = declare_parameter<double>(rate_param, def_rate);
      if (!enabled) rate = 0.0;
      d.poll_rate_hz = rate;
      command_param_name_map_[d.id] = {enabled_param, rate_param};
    }
  }

  void installParamCallback() {
    param_callback_handle_ = add_on_set_parameters_callback([
      this](const std::vector<rclcpp::Parameter> &params){
        rcl_interfaces::msg::SetParametersResult res; res.successful=true; res.reason="ok";
        struct Change { CommandDescriptor *desc; double new_rate; };
        std::vector<Change> changes;
        for (auto &p : params) {
          const std::string &name = p.get_name();
            for (auto &pair : command_param_name_map_) {
              auto *desc = findDescriptor(pair.first); if (!desc) continue;
              if (name == pair.second.enabled) {
                if (p.get_type()!=rclcpp::ParameterType::PARAMETER_BOOL){ res.successful=false; res.reason="type mismatch for enabled"; return res; }
                bool en = p.as_bool(); double current = desc->poll_rate_hz;
                if (!en) changes.push_back({desc, 0.0});
                else if (current<=0.0) {
                  double rate_val = get_parameter(pair.second.rate).as_double();
                  if (rate_val <=0.0) { res.successful=false; res.reason="enabled true requires rate_hz>0"; return res; }
                  changes.push_back({desc, rate_val});
                }
              } else if (name == pair.second.rate) {
                if (p.get_type()!=rclcpp::ParameterType::PARAMETER_DOUBLE){ res.successful=false; res.reason="type mismatch for rate"; return res; }
                double rate_val = p.as_double(); if (rate_val < 0.0){ res.successful=false; res.reason="rate_hz must be >=0"; return res; }
                changes.push_back({desc, rate_val});
              }
            }
        }
        for (auto &c : changes) {
          c.desc->poll_rate_hz = c.new_rate;
          RCLCPP_INFO(get_logger(), "Command 0x%04X new poll_rate_hz=%.3f", c.desc->id, c.new_rate);
        }
        if (!changes.empty()) schedule_dirty_ = true;
        return res;
      });
  }

  void setupPublishersAndSubs() {
    rc_pub_ = create_publisher<std_msgs::msg::UInt16MultiArray>("/msp/rc_out", 10);
    airspeed_pub_ = create_publisher<std_msgs::msg::Float32>("/msp/airspeed", 10);
    temps_pub_ = create_publisher<diagnostic_msgs::msg::DiagnosticArray>("/msp/temps", 10);
    esc_rpm_pub_ = create_publisher<sensor_msgs::msg::JointState>("/msp/esc/rpm", 10);
    rc_sub_ = create_subscription<std_msgs::msg::UInt16MultiArray>("/msp/rc_override", 10, std::bind(&MSPBridgeNode::rcCallback, this, _1));
    current_rc_.assign(rc_channel_count_, 1500);
  }

  void setupTimers() {
    read_timer_ = create_wall_timer(std::chrono::milliseconds(5), std::bind(&MSPBridgeNode::readLoop, this));
    if (rc_echo_rate_hz_ > 0) {
      rc_timer_ = create_wall_timer(std::chrono::milliseconds((int)(1000.0/rc_echo_rate_hz_)), std::bind(&MSPBridgeNode::publishRC, this));
    }
    poll_timer_ = create_wall_timer(std::chrono::milliseconds(50), std::bind(&MSPBridgeNode::pollTelemetry, this));
    stats_timer_ = create_wall_timer(std::chrono::seconds(10), std::bind(&MSPBridgeNode::logStats, this));
  }

  void readLoop() {
    uint8_t buf[256];
    int n = serial_.readSome(buf, sizeof(buf));
    for (int i=0;i<n;i++) parser_->input(buf[i]);
  }

  void pollTelemetry() {
    auto now = std::chrono::steady_clock::now();
    if (!bootstrap_done_) {
      if (!bootstrap_cmds_.empty()) {
        uint16_t cmd = bootstrap_cmds_.front();
        auto frame = buildPacketRaw(static_cast<uint8_t>(cmd), {});
        writeFrame(frame);
        bootstrap_cmds_.pop_front();
        return;
      } else {
        bootstrap_done_ = true; bootstrap_completed_time_ = now; schedule_dirty_ = true;
      }
    }
    if (!force_msp_v2_ && v2_enabled_attempted_ && !v2_confirmed_) {
      double elapsed = std::chrono::duration<double>(now - bootstrap_completed_time_).count();
      if (elapsed > v2_fallback_timeout_sec_ && !v2_fallback_applied_) {
        for (auto &d : registry_) if (d.requires_v2) d.poll_rate_hz = 0.0;
        v2_fallback_applied_ = true;
        RCLCPP_WARN(get_logger(), "No v2 frames within %.1fs -> disabling v2 sensor polling", v2_fallback_timeout_sec_);
      }
    }
    if (schedule_dirty_) { rebuildSchedule(now); schedule_dirty_ = false; }
    const size_t max_per_tick = 8; size_t sent = 0;
    while (!schedule_.empty()) {
      auto entry = schedule_.top();
      if (entry.due > now) break;
      schedule_.pop();
      CommandDescriptor *desc = findDescriptor(entry.id); if (!desc) continue;
      if (desc->poll_rate_hz <= 0.0) continue;
      if (desc->requires_v2 && !v2_confirmed_) { v2_enabled_attempted_ = true; if (v2_fallback_applied_) continue; }
      if (desc->build_request_cb) {
        auto frame = desc->build_request_cb();
        bool legacy_id = desc->id < 256;
        if (!desc->requires_v2 && use_v2_for_legacy_ && proto_supports_v2_ && legacy_id && !use_v2_tunnel_)
          frame = buildPacketV2(static_cast<uint16_t>(desc->id), {}, 0);
        else if (use_v2_tunnel_ && desc->requires_v2)
          frame = buildPacketV2OverV1(desc->id, {}, 0);
        if (!frame.empty()) {
          if (frame.size()>=3 && frame[0]=='$' && frame[1]=='X') native_v2_tx_++; else if (frame.size()>=6 && frame[0]=='$' && frame[1]=='M' && frame[4]==255) tunneled_v2_tx_++;
        }
        writeFrame(frame);
        last_sent_[desc->id] = now;
      }
      if (desc->poll_rate_hz > 0.0) {
        using Clock = std::chrono::steady_clock;
        auto period_d = std::chrono::duration<double>(1.0/desc->poll_rate_hz);
        auto period = std::chrono::duration_cast<Clock::duration>(period_d);
        Clock::time_point next_due = entry.due + period;
        size_t safety = 0;
        while (next_due < now && safety < 5) { next_due += period; ++safety; }
        if (next_due < now) next_due = Clock::now() + period;
        schedule_.emplace(next_due, desc->id);
      }
      if (++sent >= max_per_tick) break;
    }
  }

  void dispatchPacket(const MSPPacket &pkt) {
    if (log_msp_rx_) {
      const auto &raw = parser_->currentFrameBytes();
      std::ostringstream oss; oss << (pkt.version==MSPVersion::V2? "RX V2 [":"RX V1 [") << raw.size() << "]:";
      for (auto b: raw) oss << ' ' << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (int)b;
      RCLCPP_INFO(get_logger(), "%s cmd=0x%04X len=%zu", oss.str().c_str(), pkt.cmd, pkt.payload.size());
    }
    if (pkt.version == MSPVersion::V1) stats_.frames_v1++; else if (pkt.version == MSPVersion::V2) { stats_.frames_v2++; last_v2_rx_ = std::chrono::steady_clock::now(); v2_confirmed_ = true; }
    if (pkt.version == MSPVersion::V2 && pkt.payload.empty()) {
      // ack
    }
    if (pkt.cmd == MSP_IDENT && !ident_received_) { ident_received_ = true; }
    else if (pkt.cmd == MSP_API_VERSION && !api_version_received_) {
      if (pkt.payload.size() >= 3) {
        uint8_t proto_ver = pkt.payload[2]; api_version_received_ = true;
        if (proto_ver >= 2) proto_supports_v2_ = true; else proto_supports_v2_ = false;
      }
    }
    // Decode polymorphically via registry only (no per-descriptor callbacks)
    decoder_registry_.dispatch(pkt);
  }

  void rcCallback(const std_msgs::msg::UInt16MultiArray::SharedPtr msg) {
    size_t n = std::min<size_t>(msg->data.size(), (size_t)rc_channel_count_);
    if (n==0) return;
    for (size_t i=0;i<n;i++) current_rc_[i] = msg->data[i];
    auto bytes = buildPacket(MSP_SET_RAW_RC, current_rc_);
    serial_.writeAll(bytes.data(), bytes.size());
  }

  void publishRC() {
    std_msgs::msg::UInt16MultiArray m; m.data = current_rc_; rc_pub_->publish(m);
  }

  void rebuildSchedule(std::chrono::steady_clock::time_point now) {
    while (!schedule_.empty()) schedule_.pop();
    for (auto &d : registry_) {
      if (d.poll_rate_hz > 0.0) {
        schedule_.emplace(now, d.id);
      }
    }
  }

  void logStats() {
    RCLCPP_INFO(get_logger(), "Frames v1=%zu v2=%zu native_v2_tx=%zu tunneled_v2_tx=%zu", stats_.frames_v1, stats_.frames_v2, native_v2_tx_, tunneled_v2_tx_);
  }

  CommandDescriptor *findDescriptor(uint16_t id) {
    for (auto &d : registry_) {
      if (d.id == id) return &d;
    }
    return nullptr;
  }

  void writeFrame(const std::vector<uint8_t> &frame) {
    if (frame.empty()) return;
    if (log_msp_tx_) {
      std::ostringstream oss; oss << "TX [" << frame.size() << "]:";
      for (auto b: frame) oss << ' ' << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (int)b;
      RCLCPP_INFO(get_logger(), "%s", oss.str().c_str());
    }
    serial_.writeAll(frame.data(), frame.size());
  }

  // Members
  std::string port_; int baud_; int timeout_ms_{};
  int rc_channel_count_{}; double rc_echo_rate_hz_{};
  bool debug_msp_{}; bool log_msp_tx_{}; bool log_msp_rx_{};
  double v2_fallback_timeout_sec_{}; bool force_msp_v2_{}; bool use_v2_tunnel_{}; bool use_v2_for_legacy_{};

  SerialPort serial_;
  std::unique_ptr<MSPParser> parser_;
  std::vector<CommandDescriptor> registry_;
  std::unordered_map<uint16_t, std::chrono::steady_clock::time_point> last_sent_;

  struct ParamNames { std::string enabled; std::string rate; };
  std::unordered_map<uint16_t, ParamNames> command_param_name_map_;

  // Scheduling
  std::priority_queue<ScheduleEntry> schedule_;
  bool schedule_dirty_ = true;

  // Bootstrap
  std::deque<uint16_t> bootstrap_cmds_;
  bool bootstrap_done_ = false; bool ident_received_ = false; bool api_version_received_ = false;
  bool proto_supports_v2_ = false; bool v2_confirmed_ = false; bool v2_enabled_attempted_ = false; bool v2_fallback_applied_ = false;
  std::chrono::steady_clock::time_point bootstrap_completed_time_;

  // Stats
  struct Stats { size_t frames_v1=0; size_t frames_v2=0; } stats_;
  size_t native_v2_tx_=0, tunneled_v2_tx_=0; std::chrono::steady_clock::time_point last_v2_rx_;

  // RC state
  std::vector<uint16_t> current_rc_;

  // Timers
  rclcpp::TimerBase::SharedPtr read_timer_, rc_timer_, poll_timer_, stats_timer_;

  // Param callback
  OnSetParametersCallbackHandle::SharedPtr param_callback_handle_;

  // Publishers / subs
  rclcpp::Publisher<std_msgs::msg::UInt16MultiArray>::SharedPtr rc_pub_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr airspeed_pub_;
  rclcpp::Publisher<diagnostic_msgs::msg::DiagnosticArray>::SharedPtr temps_pub_;
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr esc_rpm_pub_;
  rclcpp::Subscription<std_msgs::msg::UInt16MultiArray>::SharedPtr rc_sub_;

  DecoderRegistry decoder_registry_;
};

} // namespace transformer_msp_bridge

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<transformer_msp_bridge::MSPBridgeNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
