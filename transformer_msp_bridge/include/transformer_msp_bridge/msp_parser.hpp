#pragma once
#include <cstdint>
#include <vector>
#include <functional>

namespace transformer_msp_bridge {

// External iNav MSP protocol constants
#include "msp/msp_protocol.h"

#ifndef MSP_IDENT
#define MSP_IDENT 100
#endif

enum class MSPVersion : uint8_t { V1 = 1, V2 = 2 };

struct MSPPacket {
  MSPVersion version{MSPVersion::V1};
  uint16_t cmd{0};
  uint8_t flags{0};
  std::vector<uint8_t> payload;
  bool tunneled{false};
};

struct MSPParserStats {
  uint64_t native_v2_rx{0};
  uint64_t tunneled_v2_rx{0};
  uint64_t native_v2_crc_fail{0};
  uint64_t tunneled_v2_crc_fail{0};
  uint64_t oversized_frame_dropped{0};
  uint64_t aborted_frames{0};
  uint64_t malformed_header{0};
};

using PacketCallback = std::function<void(const MSPPacket&)>;


class MSPParser {
public:
  explicit MSPParser(PacketCallback cb);
  void reset();
  void input(uint8_t byte);
  const std::vector<uint8_t>& currentFrameBytes() const { return frame_trace_; }
  const MSPParserStats & stats() const { return stats_; }
  // Abort current frame parsing (used for streaming abort requirement). Returns true if a frame was in progress.
  bool abort();
  // Adjust maximum accepted payload size (applies to both V1 and V2 logical payloads).
  void setMaxPayloadSize(uint16_t max_size) { max_payload_size_ = max_size; }
  uint16_t maxPayloadSize() const { return max_payload_size_; }
  // Zero-copy accessor: returns pointer & length to current (accumulating) payload buffer (NOT valid after emit/reset).
  const uint8_t* payloadData() const { return payload_buffer_.empty() ? nullptr : payload_buffer_.data(); }
  size_t payloadSize() const { return payload_buffer_.size(); }
private:
  // Callback invoked when a full packet has been parsed.
  PacketCallback cb_;

  // Parsing approach (refactored):
  // Instead of a large switch with many tiny per-state functions, we treat a frame
  // as a linear sequence of bytes and keep only positional counters. Once enough
  // header bytes are collected we know the final frame length and can branch to
  // the appropriate version specific logic (v1 or v2) while streaming CRC/XOR.
  // This significantly reduces boilerplate while retaining clarity.

  MSPVersion current_version_{MSPVersion::V1};

  // Generic frame tracking.
  bool in_frame_{false};          // True after '$' has been seen.
  size_t frame_pos_{0};           // 1-based count of bytes collected in current frame.
  size_t expected_frame_length_{0}; // Total number of bytes expected for this frame (once known).
  uint16_t max_payload_size_{512};  // Harden: configurable guard.
  bool abort_requested_{false};

  // V1 specific accumulators.
  uint8_t v1_payload_length_{0};
  uint8_t v1_command_{0};
  uint8_t v1_checksum_{0};

  // V2 specific accumulators.
  uint8_t  v2_flags_{0};
  uint16_t v2_command_{0};
  uint16_t v2_payload_length_{0};
  uint8_t  v2_crc_computed_{0};
  uint8_t  v2_crc_received_{0};

  // Shared payload buffer reused for both versions.
  std::vector<uint8_t> payload_buffer_;

  void emitV1();
  void emitV2();
  void handleTunneledV2();
  // Lightweight frame factory: centralize packet object construction.
  MSPPacket makePacketV1() const;
  MSPPacket makePacketV2(bool tunneled) const;

  // Frame trace for diagnostics / tests.
  std::vector<uint8_t> frame_trace_;
  MSPParserStats stats_{};
};

} // namespace transformer_msp_bridge
