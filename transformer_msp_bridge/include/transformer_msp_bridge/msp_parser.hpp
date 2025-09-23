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
};

using PacketCallback = std::function<void(const MSPPacket&)>;


class MSPParser {
public:
  explicit MSPParser(PacketCallback cb);
  void reset();
  void input(uint8_t byte);
  const std::vector<uint8_t>& currentFrameBytes() const { return frame_trace_; }
  const MSPParserStats & stats() const { return stats_; }
private:
  PacketCallback cb_;
  enum class State {
    Idle,
    HeaderStart,
    HeaderDir,
    Size,
    Cmd,
    Payload,
    Checksum,
    V2_HeaderDir2,
    V2_Flags,
    V2_IdLow,
    V2_IdHigh,
    V2_LenLow,
    V2_LenHigh,
    V2_Payload,
    V2_CRC
  } state_{State::Idle};

  MSPVersion current_version_{MSPVersion::V1};
  uint8_t v1_payload_length_{0};
  uint8_t v1_command_{0};
  uint8_t v1_checksum_{0};
  std::vector<uint8_t> payload_buffer_;

  uint8_t v2_flags_{0};
  uint16_t v2_command_{0};
  uint16_t v2_payload_length_{0};
  uint8_t v2_crc_computed_{0};
  uint8_t v2_crc_received_{0};
  void emitV1();
  void emitV2();
  void handleTunneledV2();
  // Per-state handlers (refactored from monolithic input()).
  void handleIdle(uint8_t byte_value);
  void handleHeaderStart(uint8_t byte_value);
  void handleHeaderDir(uint8_t byte_value);
  void handleV1Size(uint8_t byte_value);
  void handleV1Command(uint8_t byte_value);
  void handleV1Payload(uint8_t byte_value);
  void handleV1Checksum(uint8_t byte_value);
  void handleV2HeaderDir2(uint8_t byte_value);
  void handleV2Flags(uint8_t byte_value);
  void handleV2IdLow(uint8_t byte_value);
  void handleV2IdHigh(uint8_t byte_value);
  void handleV2LenLow(uint8_t byte_value);
  void handleV2LenHigh(uint8_t byte_value);
  void handleV2Payload(uint8_t byte_value);
  void handleV2Crc(uint8_t byte_value);
  std::vector<uint8_t> frame_trace_;
  MSPParserStats stats_{};
};

} // namespace transformer_msp_bridge
