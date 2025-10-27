// Declares the streaming MSP frame parser and supporting packet types.
#pragma once
#include <cstdint>
#include <vector>
#include <functional>

namespace transformer_msp_bridge
{

  enum class MSPVersion : uint8_t
  {
    V1 = 1,
    V2 = 2
  };

  struct MSPPacket
  {
    MSPVersion version{MSPVersion::V1};
    uint16_t cmd{0};
    uint8_t flags{0};
    std::vector<uint8_t> payload;
    bool tunneled{false};
  };

  struct MSPParserStats
  {
    uint64_t native_v2_rx{0};
    uint64_t tunneled_v2_rx{0};
    uint64_t native_v2_crc_fail{0};
    uint64_t tunneled_v2_crc_fail{0};
    uint64_t oversized_frame_dropped{0};
    uint64_t aborted_frames{0};
    uint64_t malformed_header{0};
  };

  using PacketCallback = std::function<void(const MSPPacket &)>;

  class MSPParser
  {
  public:
    explicit MSPParser(PacketCallback cb);
    void reset();
    void input(uint8_t byte);
    void feed(const uint8_t *data, size_t length)
    {
      for (size_t i = 0; i < length; i++)
        input(data[i]);
    }
    const std::vector<uint8_t> &currentFrameBytes() const { return frame_trace_; }
    const MSPParserStats &stats() const { return stats_; }
    // Abort current frame parsing (used for streaming abort requirement). Returns true if a frame was in progress.
    bool abort();
    // Adjust maximum accepted payload size (applies to both V1 and V2 logical payloads).
    void setMaxPayloadSize(uint16_t max_size) { max_payload_size_ = max_size; }
    uint16_t maxPayloadSize() const { return max_payload_size_; }
    // Zero-copy accessor: returns pointer & length to current (accumulating) payload buffer (NOT valid after emit/reset).
    const uint8_t *payloadData() const { return payload_buffer_.empty() ? nullptr : payload_buffer_.data(); }
    size_t payloadSize() const { return payload_buffer_.size(); }

  private:
    // Frame layout constants (without payload):
    static constexpr size_t kV1BaseFrameLen = 6; // $ M < size cmd checksum (size=0 case)
    static constexpr size_t kV2BaseFrameLen = 9; // $ X < flags idL idH lenL lenH crc (len=0 case)
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
    bool in_frame_{false};            // True once a '$' start marker has been accepted.
    size_t frame_pos_{0};             // 1-based index of the current byte within the frame.
    size_t expected_frame_length_{0}; // Total frame length (including checksum/CRC) once derivable, else 0.
    uint16_t max_payload_size_{512};  // Hardening limit: payloads larger than this are dropped.

    // V1 specific accumulators.
    uint8_t v1_payload_length_{0}; // Declared payload length for v1 frame.
    uint8_t v1_command_{0};        // Command identifier (1 byte) for v1.
    uint8_t v1_checksum_{0};       // Running XOR checksum accumulator.

    // V2 specific accumulators.
    uint8_t v2_flags_{0};           // Flags field (feature bits / direction info for some implementations).
    uint16_t v2_command_{0};        // 16-bit little-endian command id.
    uint16_t v2_payload_length_{0}; // 16-bit little-endian payload length.
    uint8_t v2_crc_computed_{0};    // Incrementally computed CRC8 value.
    uint8_t v2_crc_received_{0};    // CRC byte extracted from frame tail for comparison.

    // Shared payload buffer reused for both versions.
    std::vector<uint8_t> payload_buffer_; // Reused buffer storing raw payload bytes (v1 or v2 logical payload).

    void emitV1();
    void emitV2();
    void handleTunneledV2();
    // Lightweight frame factory: centralize packet object construction.
    MSPPacket makePacketV1() const;
    MSPPacket makePacketV2(bool tunneled) const;
    // Internal byte processors to reduce long if/else chains in input()
    void processV1Byte(uint8_t byte_value);
    void processV2Byte(uint8_t byte_value);
    // Centralized termination handler: ok=true means integrity (checksum/CRC) passed.
    // is_v2 distinguishes version; handles stats, emission, and reset.
    void finishFrame(bool ok, bool is_v2);

    // Frame trace for diagnostics / tests.
    std::vector<uint8_t> frame_trace_; // Captures raw frame bytes for diagnostics / tests.
    MSPParserStats stats_{};           // Aggregated counters for monitoring / tests.
  };

} // namespace transformer_msp_bridge
