#include "transformer_msp_bridge/msp_parser.hpp"
#include <cstring>

// Keep MSP_V2_FRAME_ID compatibility if external header doesn't define it
#include "msp/msp_protocol.h"
#ifndef MSP_V2_FRAME_ID
#define MSP_V2_FRAME_ID 255
#endif

namespace transformer_msp_bridge {
namespace {
inline uint8_t crc8_update(uint8_t crc, uint8_t data) {
  crc ^= data;
  for (int i=0;i<8;++i) crc = (crc & 0x80) ? ((crc << 1) ^ 0xD5) : (crc << 1);
  return crc;
}
}

MSPParser::MSPParser(PacketCallback cb) : cb_(std::move(cb)) {}

void MSPParser::reset() {
  state_ = State::Idle;
  current_version_ = MSPVersion::V1;
  size_ = 0; cmd_v1_ = 0; checksum_ = 0; buf_.clear();
  v2_flags_ = 0; v2_id_ = 0; v2_len_ = 0; v2_crc_calc_ = 0; v2_crc_recv_ = 0; frame_bytes_.clear();
}

uint8_t MSPParser::crc8_dvb_s2_update(uint8_t crc, uint8_t data) { return crc8_update(crc, data); }

void MSPParser::emitV1() {
  MSPPacket pkt; pkt.version = MSPVersion::V1; pkt.cmd = cmd_v1_; pkt.flags = 0; pkt.payload = buf_; pkt.tunneled = false; if (cb_) cb_(pkt); }

void MSPParser::emitV2() {
  MSPPacket pkt; pkt.version = MSPVersion::V2; pkt.cmd = v2_id_; pkt.flags = v2_flags_; pkt.payload = buf_; pkt.tunneled = false; if (cb_) cb_(pkt); stats_.native_v2_rx++; }

// Helpers to read LE multi-byte while guarding overruns
static uint16_t rd16(const std::vector<uint8_t>& v, size_t off) { if (v.size() < off + 2) return 0; return static_cast<uint16_t>(v[off] | (v[off+1] << 8)); }

void MSPParser::handleTunneledV2() {
  // Expect at least header(5) + crc(1)
  if (cmd_v1_ != 255 || buf_.size() < 6) { emitV1(); return; }
  uint16_t inner_len = rd16(buf_, 3);
  size_t needed = 5 + inner_len + 1;
  if (buf_.size() != needed) { emitV1(); return; }
  uint8_t crc = 0; for(size_t i=0;i<5;++i) crc = crc8_update(crc, buf_[i]);
  for(size_t i=0;i<inner_len;++i) crc = crc8_update(crc, buf_[5+i]);
  uint8_t recv = buf_[5+inner_len];
  if (crc != recv) { stats_.tunneled_v2_crc_fail++; return; }
  MSPPacket pkt; pkt.version = MSPVersion::V2; pkt.tunneled = true; pkt.flags = buf_[0]; pkt.cmd = rd16(buf_,1); pkt.payload.assign(buf_.begin()+5, buf_.begin()+5+inner_len); if (cb_) cb_(pkt); stats_.tunneled_v2_rx++; }

void MSPParser::input(uint8_t b) {
  switch(state_) {
    case State::Idle:
      if (b == '$') { state_ = State::HeaderStart; frame_bytes_.clear(); frame_bytes_.push_back(b);} else reset(); break;
    case State::HeaderStart:
      frame_bytes_.push_back(b);
      if (b=='M') { current_version_ = MSPVersion::V1; state_ = State::HeaderDir; }
      else if (b=='X') { current_version_ = MSPVersion::V2; state_ = State::V2_HeaderDir2; }
      else reset();
      break;
    case State::HeaderDir:
      frame_bytes_.push_back(b);
      if (b=='<' || b=='>') state_ = State::Size; else reset();
      break;
    case State::Size:
      frame_bytes_.push_back(b); size_ = b; buf_.clear(); buf_.reserve(size_); checksum_ = b; state_ = State::Cmd; break;
    case State::Cmd:
      frame_bytes_.push_back(b); cmd_v1_ = b; checksum_ ^= b; state_ = (size_==0)?State::Checksum:State::Payload; break;
    case State::Payload:
      frame_bytes_.push_back(b); buf_.push_back(b); checksum_ ^= b; if (buf_.size()>=size_) state_ = State::Checksum; break;
    case State::Checksum:
      frame_bytes_.push_back(b);
      if (checksum_ == b) handleTunneledV2();
      reset();
      break;
    case State::V2_HeaderDir2:
      frame_bytes_.push_back(b); if (b=='<' || b=='>') { state_ = State::V2_Flags; v2_crc_calc_ = 0; } else reset(); break;
    case State::V2_Flags:
      frame_bytes_.push_back(b); v2_flags_ = b; v2_crc_calc_ = crc8_update(v2_crc_calc_, b); state_ = State::V2_IdLow; break;
    case State::V2_IdLow:
      frame_bytes_.push_back(b); v2_id_ = b; v2_crc_calc_ = crc8_update(v2_crc_calc_, b); state_ = State::V2_IdHigh; break;
    case State::V2_IdHigh:
      frame_bytes_.push_back(b); v2_id_ |= (uint16_t)b << 8; v2_crc_calc_ = crc8_update(v2_crc_calc_, b); state_ = State::V2_LenLow; break;
    case State::V2_LenLow:
      frame_bytes_.push_back(b); v2_len_ = b; v2_crc_calc_ = crc8_update(v2_crc_calc_, b); state_ = State::V2_LenHigh; break;
    case State::V2_LenHigh:
      frame_bytes_.push_back(b); v2_len_ |= (uint16_t)b << 8; v2_crc_calc_ = crc8_update(v2_crc_calc_, b); buf_.clear(); buf_.reserve(v2_len_); state_ = (v2_len_==0)?State::V2_CRC:State::V2_Payload; break;
    case State::V2_Payload:
      frame_bytes_.push_back(b); buf_.push_back(b); v2_crc_calc_ = crc8_update(v2_crc_calc_, b); if (buf_.size()>=v2_len_) state_ = State::V2_CRC; break;
    case State::V2_CRC:
      frame_bytes_.push_back(b); v2_crc_recv_ = b; if (v2_crc_calc_ == v2_crc_recv_) emitV2(); else stats_.native_v2_crc_fail++; reset(); break;
  }
}

} // namespace transformer_msp_bridge
