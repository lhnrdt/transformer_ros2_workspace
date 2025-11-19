#include "transformer_msp_bridge/transformer_msp_bridge_node.hpp"

#include <algorithm>
#include <array>
#include <cctype>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <limits>
#include <unordered_set>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "transformer_msp_bridge/msp_builders.hpp"

namespace transformer_msp_bridge {
namespace detail {
// Derive a ROS parameter key from an MSP message name so params remain stable across boots.
//
// MSP message names are human readable (e.g. "RC Channels"), but ROS parameters should be
// stable identifiers that survive renaming or reordering of the internal registry. To achieve
// that we:
//   * lowercase every character,
//   * replace spaces with underscores,
//   * preserve existing underscores,
//   * and prefix the whole string with "command.".
//
// The resulting key is deterministic and safe to use in YAML/launch files so users can
// configure polling behavior per MSP command.
std::string sanitize_param_key(std::string_view message_name) {
  std::string result;
  result.reserve(message_name.size() + 8);
  result.append("command.");
  for (char ch : message_name) {
    if (ch == ' ') {
      result.push_back('_');
    } else if (ch == '_') {
      result.push_back('_');
    } else {
      result.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
    }
  }
  return result;
}

// Render payload bytes as uppercase hex for human-readable diagnostics.
//
// This is used when logging TX/RX MSP frames to help with debugging low-level protocol
// issues. The `spaced` flag allows switching between compact output (0102FF) and more
// human-friendly output (01 02 FF).
std::string to_hex(const std::vector<uint8_t>& data, bool spaced) {
  std::ostringstream oss;
  oss << std::hex << std::uppercase << std::setfill('0');
  for (std::size_t i = 0; i < data.size(); ++i) {
    oss << std::setw(2) << static_cast<int>(data[i]);
    if (spaced && i + 1 < data.size()) {
      oss << ' ';
    }
  }
  return oss.str();
}

// Append a boolean diagnostic value using explicit "true"/"false" strings.
//
// DiagnosticStatus values are string based, so this helper makes it easy to add boolean
// flags without proliferating slightly different representations across the codebase.
void append_key_value(diagnostic_msgs::msg::DiagnosticStatus& status, const std::string& key, bool value) {
  diagnostic_msgs::msg::KeyValue kv;
  kv.key = key;
  kv.value = value ? "true" : "false";
  status.values.push_back(std::move(kv));
}

}  // namespace detail

namespace {
constexpr uint16_t kMspSetRawRc = 0x00C8u;
}

TransformerMspBridgeNode::TransformerMspBridgeNode(const rclcpp::NodeOptions& options)
    : rclcpp::Node("transformer_msp_bridge", options),
      // Configure the MSP parser so that every decoded packet is delivered to handlePacket().
      // The parser object is long-lived and will call this bound functor from the serial
      // reader thread whenever it has a complete, checksum-verified packet.
      parser_(std::bind(&TransformerMspBridgeNode::handlePacket, this, std::placeholders::_1)) {
  // --- Parameter initialization -------------------------------------------------------------
  // Most behavior of the bridge is controlled by ROS parameters. We declare them once here
  // so they are visible to tooling and configuration via YAML/launch files.

  // Serial transport configuration: which device we talk to and how.
  port_ = declare_parameter<std::string>("port", "/dev/ttyAMA0");
  baudrate_ = declare_parameter<int>("baudrate", 115200);
  timeout_ms_ = declare_parameter<int>("timeout_ms", 50);

  // RC channel configuration: how many channels we expect and how often we publish them.
  rc_channel_count_ = static_cast<std::size_t>(declare_parameter<int>("rc_channel_count", 16));
  rc_publish_rate_hz_ = declare_parameter<double>("rc_publish_rate_hz", 10.0);

  // RC override input: topic name and update rate for outgoing MSP_SET_RAW_RC commands.
  rc_override_topic_ = declare_parameter<std::string>("rc_override_topic", "/msp/rc_override");
  rc_override_rate_hz_ = declare_parameter<double>("rc_override_rate_hz", 50.0);
  const double rc_override_hold_seconds = declare_parameter<double>("rc_override_hold_seconds", 0.2);
  rc_override_hold_duration_ = std::chrono::duration_cast<std::chrono::steady_clock::duration>(
      std::chrono::duration<double>(std::max(rc_override_hold_seconds, 0.0)));

  // Debug and logging controls. When enabled these can generate a lot of console output,
  // which is extremely useful while bringing up new hardware or investigating protocol
  // problems.
  debug_msp_ = declare_parameter<bool>("debug_msp", false);
  log_msp_tx_ = declare_parameter<bool>("log_msp_tx", false);
  log_msp_rx_ = declare_parameter<bool>("log_msp_rx", false);

  // MSP version/tunneling behavior. Many flight controllers today support both v1 and v2
  // frames; these knobs allow forcing a particular style or using v2 tunneled over v1 when
  // only a v1 link is exposed.
  v2_fallback_timeout_sec_ = declare_parameter<double>("v2_fallback_timeout_sec", 5.0);
  force_msp_v2_ = declare_parameter<bool>("force_msp_v2", false);
  use_v2_tunnel_ = declare_parameter<bool>("use_v2_tunnel", false);
  use_v2_for_legacy_ = declare_parameter<bool>("use_v2_for_legacy", false);

  // Frame IDs that will appear in message headers and TF for IMU, magnetometer, GPS and
  // altitude. These defaults work for many robots but can be customized to fit an existing
  // frame tree.
  frame_id_imu_ = declare_parameter<std::string>("frame_id.imu", "base_link");
  frame_id_mag_ = declare_parameter<std::string>("frame_id.mag", frame_id_imu_);
  frame_id_gps_ = declare_parameter<std::string>("frame_id.gps", "gps");
  frame_id_altitude_ = declare_parameter<std::string>("frame_id.altitude", frame_id_imu_);
  // Optional attitude TF output; when enabled we broadcast a transform that encodes roll,
  // pitch and yaw as reported by the flight controller.
  broadcast_attitude_tf_ = declare_parameter<bool>("attitude_tf.enabled", false);
  const std::string default_tf_parent = frame_id_imu_;
  attitude_tf_parent_frame_ = declare_parameter<std::string>("attitude_tf.parent_frame", default_tf_parent);
  const std::string default_tf_child = frame_id_imu_ + "_attitude";
  attitude_tf_child_frame_ = declare_parameter<std::string>("attitude_tf.child_frame", default_tf_child);

  if (broadcast_attitude_tf_) {
    // Only allocate a TF broadcaster if the user actually wants attitude TFs to be
    // published. This keeps resource usage and TF noise low in setups that don't need it.
    tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(this);
  }

  // --- Node wiring --------------------------------------------------------------------------
  // After parameters are set up we construct all publishers, subscribers and decoders.
  // This ensures that once we start polling the MSP link, every piece of data has a place
  // to go (topics, diagnostics, TF, etc.).
  configurePublishers();
  configureDecoders();
  configureCommandSchedules();
  configureRcOverride();

  stats_window_start_ = std::chrono::steady_clock::now();
  stats_window_tx_bytes_ = 0;
  stats_window_rx_bytes_ = 0;
  stats_window_tx_messages_ = 0;
  stats_window_rx_packets_ = 0;
  stats_window_response_sum_ns_ = 0;
  stats_window_response_count_ = 0;
  // Statistics timer: every few seconds we compute link throughput and response time and
  // print them to the log. This helps detect overloaded serial links or misconfigured
  // polling rates.
  stats_timer_ = create_wall_timer(std::chrono::seconds(5), [this]() {
    const auto now = std::chrono::steady_clock::now();
    const auto elapsed = now - stats_window_start_;
    if (elapsed <= std::chrono::steady_clock::duration::zero()) {
      return;
    }

    const double elapsed_sec = std::chrono::duration<double>(elapsed).count();
    if (elapsed_sec <= 0.0) {
      return;
    }

    const std::uint64_t tx_bytes = tx_bytes_.load(std::memory_order_relaxed);
    const std::uint64_t rx_bytes = rx_bytes_.load(std::memory_order_relaxed);
    const std::uint64_t tx_msgs = tx_messages_.load(std::memory_order_relaxed);
    const std::uint64_t rx_pkts = rx_packets_.load(std::memory_order_relaxed);
    const std::uint64_t resp_sum_ns = response_time_sum_ns_.load(std::memory_order_relaxed);
    const std::uint64_t resp_count = response_time_count_.load(std::memory_order_relaxed);

    // Compute deltas since the last reporting window; this makes statistics independent of
    // total node uptime and easier to reason about.
    const std::uint64_t delta_tx_bytes = tx_bytes - stats_window_tx_bytes_;
    const std::uint64_t delta_rx_bytes = rx_bytes - stats_window_rx_bytes_;
    const std::uint64_t delta_tx_msgs = tx_msgs - stats_window_tx_messages_;
    const std::uint64_t delta_rx_pkts = rx_pkts - stats_window_rx_packets_;
    const std::uint64_t delta_resp_count = resp_count - stats_window_response_count_;
    const std::uint64_t delta_resp_sum_ns = resp_sum_ns - stats_window_response_sum_ns_;

    // Convert byte deltas to human-friendly rates (kB/s and bits/s) for logging.
    const double tx_kbytes_per_sec = static_cast<double>(delta_tx_bytes) / 1024.0 / elapsed_sec;
    const double rx_kbytes_per_sec = static_cast<double>(delta_rx_bytes) / 1024.0 / elapsed_sec;
    const double tx_bits_per_sec = static_cast<double>(delta_tx_bytes) * 8.0 / elapsed_sec;
    const double rx_bits_per_sec = static_cast<double>(delta_rx_bytes) * 8.0 / elapsed_sec;
    const double avg_resp_ms =
        delta_resp_count > 0
            ? (static_cast<double>(delta_resp_sum_ns) / 1000000.0 / static_cast<double>(delta_resp_count))
            : 0.0;
    const double link_capacity_bps = baudrate_ > 0 ? static_cast<double>(baudrate_) : 0.0;
    const double tx_load_pct = link_capacity_bps > 0.0 ? (tx_bits_per_sec / link_capacity_bps) * 100.0 : 0.0;
    const double rx_load_pct = link_capacity_bps > 0.0 ? (rx_bits_per_sec / link_capacity_bps) * 100.0 : 0.0;

    if (tx_load_pct > 90.0) {
      RCLCPP_WARN(get_logger(), "\nMSP link warning: TX load %.1f%%", tx_load_pct);
    }

    if (rx_load_pct > 90.0) {
      RCLCPP_WARN(get_logger(), "\nMSP link warning: RX load %.1f%%", rx_load_pct);
    }

    RCLCPP_INFO(get_logger(),
                "\nMSP link stats: tx %.2f kB/s (%llu msgs, load %.1f%%) | rx %.2f kB/s (%llu packets, load %.1f%%) | "
                "resp avg %.2f ms (%llu samples)",
                tx_kbytes_per_sec, static_cast<unsigned long long>(delta_tx_msgs), tx_load_pct, rx_kbytes_per_sec,
                static_cast<unsigned long long>(delta_rx_pkts), rx_load_pct, avg_resp_ms,
                static_cast<unsigned long long>(delta_resp_count));

    stats_window_tx_bytes_ = tx_bytes;
    stats_window_rx_bytes_ = rx_bytes;
    stats_window_tx_messages_ = tx_msgs;
    stats_window_rx_packets_ = rx_pkts;
    stats_window_response_sum_ns_ = resp_sum_ns;
    stats_window_response_count_ = resp_count;
    stats_window_start_ = now;
  });

  if (!openSerial()) {
    throw std::runtime_error("Failed to open MSP serial port: " + port_);
  }

  poll_timer_ =
      create_wall_timer(std::chrono::milliseconds(20), std::bind(&TransformerMspBridgeNode::pollCommands, this));

  RCLCPP_INFO(get_logger(), "\033[32m[READY] Transformer MSP bridge ready on %s @ %d baud\033[0m", port_.c_str(),
              baudrate_);
}

TransformerMspBridgeNode::~TransformerMspBridgeNode() {
  // Signal the background read thread to stop and wait for it to finish before closing the
  // serial port. This ensures we never read or write after teardown.
  running_.store(false);
  if (reader_thread_.joinable()) {
    reader_thread_.join();
  }
  closeSerial();
}

void TransformerMspBridgeNode::configureCommandSchedules() {
  // Mirror the default registry so parameters and scheduling always share a single source of truth.
  //
  // The MSP registry exposes metadata for each known command: numeric ID, name, default
  // polling rate and whether it is enabled by default. Here we turn that into a vector of
  // CommandSchedule objects and declare parameters per command so users can override the
  // defaults without touching code.
  command_schedules_.clear();
  const auto registry_view = msp::get_default_registry();
  command_schedules_.reserve(registry_view.size);

  const auto now = std::chrono::steady_clock::now();
  for (std::size_t i = 0; i < registry_view.size; ++i) {
    const auto& entry = registry_view.data[i];
    if (entry.id == 0) {
      continue;
    }

    CommandDefinition definition{};
    definition.message_name = std::string(entry.name);
    definition.param_key = detail::sanitize_param_key(entry.name);
    definition.command_id = entry.id;
    definition.default_rate_hz = entry.poll_rate_hz;
    definition.default_enabled = entry.default_polled;

    CommandSchedule schedule{};
    schedule.definition = std::move(definition);
    const std::string enabled_param = schedule.definition.param_key + ".enabled";
    const std::string rate_param = schedule.definition.param_key + ".rate_hz";

    schedule.enabled = declare_parameter<bool>(enabled_param, schedule.definition.default_enabled);
    schedule.rate_hz = declare_parameter<double>(rate_param, schedule.definition.default_rate_hz);

    if (!schedule.enabled || schedule.rate_hz <= 0.0) {
      schedule.enabled = false;
      schedule.period = std::chrono::steady_clock::duration::zero();
    } else {
      const double period_seconds = 1.0 / schedule.rate_hz;
      schedule.period = std::chrono::duration_cast<std::chrono::steady_clock::duration>(
          std::chrono::duration<double>(period_seconds));
      if (schedule.period.count() <= 0) {
        schedule.period = std::chrono::milliseconds(1);
      }
      schedule.next_fire = now + schedule.period;
    }

    command_schedules_.push_back(std::move(schedule));
  }
  verifyDecoderCoverage(registry_view);
}

bool TransformerMspBridgeNode::openSerial() {
  // Lazily open the serial device and start the background reader thread.
  //
  // All access to the serial object is guarded by serial_mutex_ so that open/close and
  // read/write cannot race with each other.
  std::lock_guard<std::mutex> lock(serial_mutex_);
  if (serial_ready_) {
    return true;
  }

  if (!serial_.open(port_, baudrate_, timeout_ms_)) {
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

void TransformerMspBridgeNode::closeSerial() {
  // Close the serial port; the reader thread observes serial_ready_ and will exit.
  std::lock_guard<std::mutex> lock(serial_mutex_);
  serial_ready_ = false;
  serial_.close();
}

void TransformerMspBridgeNode::readLoop() {
  // Pump bytes from the serial port into the MSP parser while the node remains active.
  //
  // This function runs in a dedicated background thread. It performs blocking reads with the
  // configured timeout and forwards any received bytes to the MSP parser, which detects
  // packet boundaries and checksums.
  std::array<uint8_t, 512> buffer{};
  while (running_.load()) {
    int bytes_read = 0;
    {
      std::lock_guard<std::mutex> lock(serial_mutex_);
      if (!serial_ready_) {
        break;
      }
      // Perform a single non-owning read into the local buffer. The call may block up to
      // the configured timeout; we release the mutex immediately afterwards so the writer
      // side is not blocked longer than needed.
      bytes_read = serial_.readSome(buffer.data(), buffer.size());
    }

    if (bytes_read > 0) {
      // Track the number of raw bytes received for throughput statistics.
      rx_bytes_.fetch_add(static_cast<std::uint64_t>(bytes_read), std::memory_order_relaxed);
      if (log_msp_rx_) {
        // Log exactly the bytes we just read in hex form for debugging.
        std::vector<uint8_t> chunk(buffer.begin(), buffer.begin() + bytes_read);
        RCLCPP_INFO(get_logger(), "MSP RX [%d]: %s", bytes_read, detail::to_hex(chunk).c_str());
      }
      // Feed the new bytes into the MSP state machine. It may emit zero, one or multiple
      // complete packets depending on what was already buffered.
      parser_.feed(buffer.data(), static_cast<std::size_t>(bytes_read));
    } else if (bytes_read == 0) {
      // No data available at the moment; sleep briefly to avoid busy spinning.
      std::this_thread::sleep_for(std::chrono::milliseconds(2));
    } else {
      // Negative return value indicates a transient error from the serial backend. We log a
      // throttled warning and back off for a short period before trying again.
      RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 2000, "Serial read error, retrying");
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
  }
}

bool TransformerMspBridgeNode::sendCommand(uint16_t command_id, const std::vector<uint8_t>& payload) {
  // Build a request honoring v1/v2 configuration, then write it to the serial link.
  //
  // Depending on the command and configuration we may emit a v1 frame, a v2 frame or a v2
  // frame tunneled inside v1. The builder helpers hide the exact wire format from the rest
  // of the code.
  std::vector<uint8_t> frame;
  const bool is_v2 = msp::is_v2(command_id);

  if (is_v2 || force_msp_v2_ || use_v2_for_legacy_) {
    if (use_v2_tunnel_ && !force_msp_v2_) {
      frame = buildPacketV2OverV1(command_id, payload);
    } else {
      frame = buildPacketV2(command_id, payload);
    }
  } else {
    frame = buildPacketRaw(static_cast<uint8_t>(command_id & 0xFF), payload);
  }

  if (frame.empty()) {
    // If the builder could not construct a valid frame (e.g. invalid payload size), bail
    // out early instead of attempting to touch the serial port.
    return false;
  }

  if (log_msp_tx_) {
    const std::string_view name = msp::message_name(command_id);
    if (!name.empty()) {
      RCLCPP_INFO(get_logger(), "MSP TX (%u %.*s): %s", static_cast<unsigned>(command_id),
                  static_cast<int>(name.size()), name.data(), detail::to_hex(frame).c_str());
    } else {
      RCLCPP_INFO(get_logger(), "MSP TX (%u): %s", static_cast<unsigned>(command_id), detail::to_hex(frame).c_str());
    }
  }

  std::lock_guard<std::mutex> lock(serial_mutex_);
  if (!serial_ready_) {
    // Serial port has been closed or never opened; treat as a soft failure.
    return false;
  }
  // Attempt to write the full frame; writeAll() either succeeds completely or fails.
  const bool wrote = serial_.writeAll(frame.data(), frame.size());
  if (wrote) {
    tx_bytes_.fetch_add(static_cast<std::uint64_t>(frame.size()), std::memory_order_relaxed);
    tx_messages_.fetch_add(1ULL, std::memory_order_relaxed);
    if (command_id != kMspSetRawRc) {
      const auto now = std::chrono::steady_clock::now();
      std::lock_guard<std::mutex> pending_lock(pending_request_mutex_);
      // Record that we sent this command at `now` so handlePacket() can later compute an
      // approximate round-trip time for matching responses. The deque is kept bounded to
      // avoid unbounded growth if responses never arrive.
      pending_requests_.push_back(PendingRequest{command_id, now});
      while (pending_requests_.size() > 256) {
        pending_requests_.pop_front();
      }
    }
  }
  return wrote;
}

void TransformerMspBridgeNode::pollCommands() {
  // Fire any enabled schedule that has expired and immediately queue its next deadline.
  //
  // This is called periodically from a wall timer. For each enabled schedule we check
  // whether its next_fire time has passed and, if so, send the corresponding MSP command
  // and move next_fire into the future.
  if (!serial_ready_) {
    return;
  }

  const auto now = std::chrono::steady_clock::now();
  for (auto& schedule : command_schedules_) {
    if (!schedule.enabled || schedule.period == std::chrono::steady_clock::duration::zero()) {
      continue;
    }
    if (now < schedule.next_fire) {
      continue;
    }

    if (!sendCommand(schedule.definition.command_id)) {
      RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 5000, "Failed to send MSP command %u",
                           static_cast<unsigned>(schedule.definition.command_id));
    }
    schedule.next_fire = now + schedule.period;
  }
}

void TransformerMspBridgeNode::configureRcOverride() {
  if (rc_channel_count_ == 0) {
    RCLCPP_WARN(get_logger(), "rc_channel_count parameter is zero; RC override disabled");
    return;
  }

  if (rc_override_hold_duration_ <= std::chrono::steady_clock::duration::zero()) {
    rc_override_hold_duration_ = std::chrono::milliseconds(40);
  }

  rc_override_channels_.assign(rc_channel_count_, 1500u);
  rc_override_sub_ = create_subscription<std_msgs::msg::UInt16MultiArray>(
      rc_override_topic_, rclcpp::QoS(10),
      [this](const std_msgs::msg::UInt16MultiArray::SharedPtr msg) { handleRcOverride(msg); });

  if (rc_override_rate_hz_ <= 0.0) {
    RCLCPP_WARN(get_logger(), "rc_override_rate_hz parameter <= 0; RC override transmission disabled");
    return;
  }

  const double clamped_rate = std::max(rc_override_rate_hz_, 1.0);
  const auto period = std::chrono::duration_cast<std::chrono::steady_clock::duration>(
      std::chrono::duration<double>(1.0 / clamped_rate));
  const auto effective_period =
      period > std::chrono::steady_clock::duration::zero() ? period : std::chrono::milliseconds(1);
  // Timer that will periodically call tickRcOverride() to actually transmit override
  // values while they are active.
  rc_override_timer_ = create_wall_timer(effective_period, [this]() { tickRcOverride(); });
}

void TransformerMspBridgeNode::handleRcOverride(const std_msgs::msg::UInt16MultiArray::SharedPtr msg) {
  if (!msg) {
    return;
  }

  constexpr std::size_t kMaxChannels = 32;
  // Respect both the configured channel count and a hard safety limit to prevent overly
  // large MSP frames.
  const std::size_t desired_count = std::max<std::size_t>(rc_channel_count_, msg->data.size());
  const std::size_t final_count = std::min<std::size_t>(desired_count, kMaxChannels);
  std::vector<uint16_t> sanitized(final_count, 1500u);
  const std::size_t copy_count = std::min<std::size_t>(msg->data.size(), final_count);
  for (std::size_t i = 0; i < copy_count; ++i) {
    sanitized[i] = std::clamp<uint16_t>(msg->data[i], 750u, 2250u);
  }

  const auto now = std::chrono::steady_clock::now();
  {
    // Update shared override state while holding the mutex so that the timer callback sees
    // a consistent snapshot of channels and timestamps.
    std::lock_guard<std::mutex> lock(rc_override_mutex_);
    rc_override_channels_ = std::move(sanitized);
    rc_override_last_msg_ = now;
    rc_override_active_ = true;
  }

  tickRcOverride();
}

void TransformerMspBridgeNode::tickRcOverride() {
  if (!serial_ready_) {
    return;
  }

  std::vector<uint16_t> channels;
  const auto now = std::chrono::steady_clock::now();
  {
    // Copy the active override channels under lock, but release the mutex before we build
    // the payload or touch the serial port to keep lock hold times short.
    std::lock_guard<std::mutex> lock(rc_override_mutex_);
    if (!rc_override_active_) {
      return;
    }
    if (now - rc_override_last_msg_ > rc_override_hold_duration_) {
      rc_override_active_ = false;
      return;
    }
    channels = rc_override_channels_;
  }

  if (channels.empty()) {
    return;
  }

  // Encode channel values into little-endian 16-bit fields as expected by MSP_SET_RAW_RC.
  std::vector<uint8_t> payload;
  payload.reserve(channels.size() * 2);
  for (uint16_t value : channels) {
    payload.push_back(static_cast<uint8_t>(value & 0xFFu));
    payload.push_back(static_cast<uint8_t>((value >> 8) & 0xFFu));
  }

  if (!sendCommand(kMspSetRawRc, payload)) {
    RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 1000, "Failed to transmit MSP_SET_RAW_RC");
  }
}

void TransformerMspBridgeNode::handlePacket(const MSPPacket& pkt) {
  // Offer each decoder the packet; decoders filter by command ID internally.
  //
  // This method is called by the MSP parser whenever a complete packet has been received
  // and validated. We use it to update statistics and to fan out the packet to any
  // interested decoders.
  rx_packets_.fetch_add(1ULL, std::memory_order_relaxed);
  const auto now = std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point sent_time{};
  bool matched_request = false;
  if (pkt.cmd != 0) {
    // Try to associate this packet with a previously sent request of the same command ID.
    // This let us approximate round-trip times for commands that expect responses.
    std::lock_guard<std::mutex> lock(pending_request_mutex_);
    // Drop any very old entries to keep the deque size reasonable even if responses are
    // lost on the wire.
    while (!pending_requests_.empty() && now - pending_requests_.front().sent_at > std::chrono::seconds(2)) {
      pending_requests_.pop_front();
    }

    const auto rit = std::find_if(pending_requests_.rbegin(), pending_requests_.rend(),
                                  [cmd = pkt.cmd](const PendingRequest& entry) { return entry.command_id == cmd; });
    if (rit != pending_requests_.rend()) {
      // Found a matching request; remember when it was sent and remove it from the deque
      // so subsequent packets for the same command ID are treated independently.
      sent_time = rit->sent_at;
      auto erase_it = rit.base();
      --erase_it;
      pending_requests_.erase(erase_it);
      matched_request = true;
    }
  }

  if (matched_request) {
    // Accumulate the measured round-trip time into running statistics for later reporting.
    const auto rtt_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now - sent_time).count();
    response_time_sum_ns_.fetch_add(static_cast<std::uint64_t>(rtt_ns), std::memory_order_relaxed);
    response_time_count_.fetch_add(1ULL, std::memory_order_relaxed);
  }

  if (debug_msp_) {
    RCLCPP_DEBUG(get_logger(), "MSP RX cmd=%u len=%zu", static_cast<unsigned>(pkt.cmd), pkt.payload.size());
  }

  // Finally, hand the packet to any decoder that is interested in this command ID. Multiple
  // decoders can subscribe to the same command if they publish different ROS views of the
  // data.
  for (auto& decoder : decoders_) {
    if (decoder && decoder->matches(pkt.cmd)) {
      decoder->decode(pkt);
    }
  }
}

void TransformerMspBridgeNode::verifyDecoderCoverage(const msp::RegistryView& registry_view) {
  std::unordered_set<uint16_t> scheduled_ids;
  scheduled_ids.reserve(command_schedules_.size());
  for (const auto& schedule : command_schedules_) {
    scheduled_ids.insert(schedule.definition.command_id);
  }

  for (std::size_t i = 0; i < registry_view.size; ++i) {
    const auto& entry = registry_view.data[i];
    if (entry.id == 0) {
      continue;
    }

    bool used_by_decoder = false;
    for (const auto& decoder : decoders_) {
      if (decoder && decoder->matches(entry.id)) {
        used_by_decoder = true;
        break;
      }
    }

    if (!used_by_decoder) {
      continue;
    }

    const bool schedule_present = scheduled_ids.find(entry.id) != scheduled_ids.end();
    if (!schedule_present) {
      if (entry.default_polled) {
        RCLCPP_WARN(
            get_logger(),
            "MSP command %.*s required by active decoders is not scheduled; related publishers will stay silent",
            static_cast<int>(entry.name.size()), entry.name.data());
      }
      continue;
    }

    const auto schedule_it = std::find_if(command_schedules_.begin(), command_schedules_.end(),
                                          [command_id = entry.id](const CommandSchedule& schedule) {
                                            return schedule.definition.command_id == command_id;
                                          });

    if (schedule_it != command_schedules_.end() && !schedule_it->enabled && entry.default_polled) {
      RCLCPP_WARN(get_logger(), "MSP command %.*s schedule disabled; related publishers will stay silent",
                  static_cast<int>(entry.name.size()), entry.name.data());
    }
  }
}

}  // namespace transformer_msp_bridge

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  try {
    auto node = std::make_shared<transformer_msp_bridge::TransformerMspBridgeNode>();
    rclcpp::spin(node);
  } catch (const std::exception& ex) {
    RCLCPP_FATAL(rclcpp::get_logger("transformer_msp_bridge"), "%s", ex.what());
  }
  rclcpp::shutdown();
  return 0;
}
