#pragma once
#include <cstdint>
#include <vector>
#include <functional>
#include <optional>
#include <string>

namespace transformer_msp_bridge {

// Use external iNav MSP constant definitions instead of redefining IDs.
#include "msp/msp_protocol.h"

// Some older negotiation flows begin with MSP_IDENT (classic MultiWii ID=100) prior to API_VERSION.
// If the external header doesn't supply it (modern INAV often omits), define a fallback.
#ifndef MSP_IDENT
#define MSP_IDENT 100
#endif

enum class MSPVersion : uint8_t { V1 = 1, V2 = 2 };

struct MSPPacket {
  MSPVersion version{MSPVersion::V1};
  uint16_t cmd{0};              // widen to 16 bits for v2 (v1 uses low 8 bits)
  uint8_t flags{0};             // v2 flags field (0 for v1)
  std::vector<uint8_t> payload; // raw payload bytes
  bool tunneled{false};         // true if this v2 packet arrived via v2-over-v1 tunnel
};

struct MSPParserStats {
  uint64_t native_v2_rx{0};
  uint64_t tunneled_v2_rx{0};
  uint64_t native_v2_crc_fail{0};
  uint64_t tunneled_v2_crc_fail{0};
};

// Callback signature for decoded packets
using PacketCallback = std::function<void(const MSPPacket&)>;

class MSPParser {
public:
  explicit MSPParser(PacketCallback cb);
  void reset();
  void input(uint8_t byte); // feed one byte
  const std::vector<uint8_t>& currentFrameBytes() const { return frame_bytes_; }
  const MSPParserStats & stats() const { return stats_; }
private:
  PacketCallback cb_;
  enum class State {
    Idle,
    HeaderStart,
    HeaderDir,
    Size,      // v1 size
    Cmd,       // v1 cmd
    Payload,   // v1 payload
    Checksum,  // v1 checksum
    V2_HeaderDir2, // after '$' 'X'
    V2_Flags,
    V2_IdLow,
    V2_IdHigh,
    V2_LenLow,
    V2_LenHigh,
    V2_Payload,
    V2_CRC
  } state_{State::Idle};

  // Shared accumulators
  MSPVersion current_version_{MSPVersion::V1};
  uint8_t size_{0};
  uint8_t cmd_v1_{0};
  uint8_t checksum_{0};
  std::vector<uint8_t> buf_;

  // v2 fields
  uint8_t v2_flags_{0};
  uint16_t v2_id_{0};
  uint16_t v2_len_{0};
  uint8_t v2_crc_calc_{0};
  uint8_t v2_crc_recv_{0};
  void emitV1();
  void emitV2();
  static uint8_t crc8_dvb_s2_update(uint8_t crc, uint8_t data);
  // Raw frame accumulation (from '$' start up to and including checksum byte)
  std::vector<uint8_t> frame_bytes_;
  MSPParserStats stats_{};
};

// Build an MSP v1 packet (direction host->FC) with given command and payload.
std::vector<uint8_t> buildPacket(uint8_t cmd, const std::vector<uint16_t>& rc_values);
std::vector<uint8_t> buildPacketRaw(uint8_t cmd, const std::vector<uint8_t>& payload);

// Build an MSP v2 packet.
std::vector<uint8_t> buildPacketV2(uint16_t cmd, const std::vector<uint8_t>& payload, uint8_t flags = 0);

// Build an MSP v2-over-v1 tunneled packet (MSP_V2_FRAME_ID inside v1 frame).
std::vector<uint8_t> buildPacketV2OverV1(uint16_t cmd, const std::vector<uint8_t>& payload, uint8_t flags = 0);

} // namespace transformer_msp_bridge
