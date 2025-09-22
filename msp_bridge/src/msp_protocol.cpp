#include "msp_bridge/msp_protocol.hpp"
#include <cstring>
#include "msp/msp_protocol.h" // may or may not expose MSP_V2_FRAME_ID
#ifndef MSP_V2_FRAME_ID
#define MSP_V2_FRAME_ID 255
#endif

namespace msp_bridge {

MSPParser::MSPParser(PacketCallback cb) : cb_(std::move(cb)) {}

void MSPParser::reset() {
  state_ = State::Idle;
  current_version_ = MSPVersion::V1;
  size_ = 0; cmd_v1_ = 0; checksum_ = 0; buf_.clear();
  v2_flags_ = 0; v2_id_ = 0; v2_len_ = 0; v2_crc_calc_ = 0; v2_crc_recv_ = 0;
  frame_bytes_.clear();
}

namespace { // internal helper
inline uint8_t crc8_dvb_s2_update_fn(uint8_t crc, uint8_t data) {
  crc ^= data;
  for (int i = 0; i < 8; ++i) {
    if (crc & 0x80) crc = (crc << 1) ^ 0xD5; else crc <<= 1; // poly 0xD5
  }
  return crc;
}
}

uint8_t MSPParser::crc8_dvb_s2_update(uint8_t crc, uint8_t data) { return crc8_dvb_s2_update_fn(crc, data); }

void MSPParser::emitV1() {
  MSPPacket pkt;
  pkt.version = MSPVersion::V1;
  pkt.cmd = cmd_v1_;
  pkt.flags = 0;
  pkt.payload = buf_;
  if (cb_) cb_(pkt);
}

void MSPParser::emitV2() {
  MSPPacket pkt;
  pkt.version = MSPVersion::V2;
  pkt.cmd = v2_id_;
  pkt.flags = v2_flags_;
  pkt.payload = buf_;
  pkt.tunneled = false; // native unless overwritten in tunneled path
  if (cb_) cb_(pkt);
  stats_.native_v2_rx++;
}

void MSPParser::input(uint8_t b) {
  switch(state_) {
    case State::Idle:
      if (b == '$') { state_ = State::HeaderStart; frame_bytes_.clear(); frame_bytes_.push_back(b);} else reset();
      break;
    case State::HeaderStart:
      frame_bytes_.push_back(b);
      if (b == 'M') { current_version_ = MSPVersion::V1; state_ = State::HeaderDir; }
      else if (b == 'X') { current_version_ = MSPVersion::V2; state_ = State::V2_HeaderDir2; }
      else reset();
      break;
    // V1 path
    case State::HeaderDir:
      frame_bytes_.push_back(b);
      if (b == '<' || b == '>') { state_ = State::Size; }
      else reset();
      break;
    case State::Size:
      frame_bytes_.push_back(b);
      size_ = b;
      buf_.clear(); buf_.reserve(size_);
      checksum_ = b;
      state_ = State::Cmd;
      break;
    case State::Cmd:
      frame_bytes_.push_back(b);
      cmd_v1_ = b;
      checksum_ ^= b;
      state_ = (size_ == 0) ? State::Checksum : State::Payload;
      break;
    case State::Payload:
      frame_bytes_.push_back(b);
      buf_.push_back(b);
      checksum_ ^= b;
      if (buf_.size() >= size_) state_ = State::Checksum;
      break;
    case State::Checksum:
      frame_bytes_.push_back(b);
      if (checksum_ == b) {
        // Check if this is a tunneled v2-over-v1 frame (cmd 255) with enough bytes for v2 header + crc
  if (cmd_v1_ == 255 && buf_.size() >= 5 + 1) {
          // Parse embedded v2 header
          uint8_t flags = buf_[0];
          uint16_t cmd = static_cast<uint16_t>(buf_[1]) | (static_cast<uint16_t>(buf_[2]) << 8);
          uint16_t len = static_cast<uint16_t>(buf_[3]) | (static_cast<uint16_t>(buf_[4]) << 8);
          size_t needed = 5 + len + 1; // header + payload + crc8
          if (buf_.size() == needed) {
            uint8_t crc_calc = 0;
            for (size_t i=0;i<5;i++) crc_calc = crc8_dvb_s2_update_fn(crc_calc, buf_[i]);
            if (len > 0) {
              for (size_t i=0;i<len;i++) crc_calc = crc8_dvb_s2_update_fn(crc_calc, buf_[5+i]);
            }
            uint8_t crc_recv = buf_[5+len];
            if (crc_calc == crc_recv) {
              MSPPacket pkt; pkt.version = MSPVersion::V2; pkt.cmd = cmd; pkt.flags = flags; pkt.tunneled = true;
              pkt.payload.assign(buf_.begin()+5, buf_.begin()+5+len);
              if (cb_) cb_(pkt);
              stats_.tunneled_v2_rx++;
            } else {
              stats_.tunneled_v2_crc_fail++;
            }
          } else {
            // length mismatch; ignore
          }
        } else {
          emitV1();
        }
      }
      reset();
      break;
    // V2 path
    case State::V2_HeaderDir2:
      frame_bytes_.push_back(b);
      if (b == '<' || b == '>') {
        state_ = State::V2_Flags;
        v2_crc_calc_ = 0; // CRC8 start value
      } else { reset(); }
      break;
    case State::V2_Flags:
      frame_bytes_.push_back(b);
      v2_flags_ = b;
      v2_crc_calc_ = crc8_dvb_s2_update_fn(v2_crc_calc_, b);
      state_ = State::V2_IdLow; break;
    case State::V2_IdLow:
      frame_bytes_.push_back(b);
      v2_id_ = b;
      v2_crc_calc_ = crc8_dvb_s2_update_fn(v2_crc_calc_, b);
      state_ = State::V2_IdHigh; break;
    case State::V2_IdHigh:
      frame_bytes_.push_back(b);
      v2_id_ |= (uint16_t)b << 8;
      v2_crc_calc_ = crc8_dvb_s2_update_fn(v2_crc_calc_, b);
      state_ = State::V2_LenLow; break;
    case State::V2_LenLow:
      frame_bytes_.push_back(b);
      v2_len_ = b;
      v2_crc_calc_ = crc8_dvb_s2_update_fn(v2_crc_calc_, b);
      state_ = State::V2_LenHigh; break;
    case State::V2_LenHigh:
      frame_bytes_.push_back(b);
      v2_len_ |= (uint16_t)b << 8;
      v2_crc_calc_ = crc8_dvb_s2_update_fn(v2_crc_calc_, b);
      buf_.clear(); buf_.reserve(v2_len_);
      state_ = (v2_len_ == 0) ? State::V2_CRC : State::V2_Payload; break;
    case State::V2_Payload:
      frame_bytes_.push_back(b);
      buf_.push_back(b);
      v2_crc_calc_ = crc8_dvb_s2_update_fn(v2_crc_calc_, b);
      if (buf_.size() >= v2_len_) {
        state_ = State::V2_CRC;
      }
      break;
    case State::V2_CRC:
      frame_bytes_.push_back(b);
      v2_crc_recv_ = b;
      if (v2_crc_calc_ == v2_crc_recv_) emitV2();
      else stats_.native_v2_crc_fail++;
      reset(); break;
  }
}

std::vector<uint8_t> buildPacket(uint8_t cmd, const std::vector<uint16_t>& rc_values) {
  std::vector<uint8_t> payload; payload.reserve(rc_values.size()*2);
  for (uint16_t v : rc_values) {
    payload.push_back(static_cast<uint8_t>(v & 0xFF));
    payload.push_back(static_cast<uint8_t>((v >> 8) & 0xFF));
  }
  return buildPacketRaw(cmd, payload);
}

std::vector<uint8_t> buildPacketRaw(uint8_t cmd, const std::vector<uint8_t>& payload) {
  uint8_t size = static_cast<uint8_t>(payload.size());
  uint8_t cs = size ^ cmd;
  for (uint8_t b : payload) cs ^= b;
  std::vector<uint8_t> out; out.reserve(6 + payload.size());
  out.push_back('$'); out.push_back('M'); out.push_back('<');
  out.push_back(size); out.push_back(cmd);
  for (uint8_t b : payload) out.push_back(b);
  out.push_back(cs);
  return out;
}

std::vector<uint8_t> buildPacketV2(uint16_t cmd, const std::vector<uint8_t>& payload, uint8_t flags) {
  // Native v2 frame with CRC8 DVB-S2 over header+payload
  uint16_t len = static_cast<uint16_t>(payload.size());
  uint8_t crc = 0;
  auto crc_upd = [&](uint8_t b){ crc = crc8_dvb_s2_update_fn(crc, b); };
  std::vector<uint8_t> out; out.reserve(8 + payload.size());
  out.push_back('$'); out.push_back('X'); out.push_back('<');
  out.push_back(flags); crc_upd(flags);
  uint8_t cmdL = cmd & 0xFF; uint8_t cmdH = (cmd >> 8) & 0xFF;
  out.push_back(cmdL); crc_upd(cmdL);
  out.push_back(cmdH); crc_upd(cmdH);
  uint8_t lenL = len & 0xFF; uint8_t lenH = (len >> 8) & 0xFF;
  out.push_back(lenL); crc_upd(lenL);
  out.push_back(lenH); crc_upd(lenH);
  for (uint8_t b : payload) { out.push_back(b); crc_upd(b); }
  out.push_back(crc); // single-byte CRC8
  return out;
}

std::vector<uint8_t> buildPacketV2OverV1(uint16_t cmd, const std::vector<uint8_t>& payload, uint8_t flags) {
  // Compose v2 header (flags, cmdL, cmdH, lenL, lenH) + payload + v2 crc8 inside a v1 frame with cmd=MSP_V2_FRAME_ID
  uint16_t len = static_cast<uint16_t>(payload.size());
  uint8_t v2_hdr[5];
  v2_hdr[0] = flags;
  v2_hdr[1] = static_cast<uint8_t>(cmd & 0xFF);
  v2_hdr[2] = static_cast<uint8_t>((cmd >> 8) & 0xFF);
  v2_hdr[3] = static_cast<uint8_t>(len & 0xFF);
  v2_hdr[4] = static_cast<uint8_t>((len >> 8) & 0xFF);
  uint8_t crc = 0;
  for (uint8_t b : v2_hdr) crc = crc8_dvb_s2_update_fn(crc, b);
  for (uint8_t b : payload) crc = crc8_dvb_s2_update_fn(crc, b);
  // Build inner buffer: v2 header + payload + crc8
  std::vector<uint8_t> inner; inner.reserve(5 + payload.size() + 1);
  inner.insert(inner.end(), v2_hdr, v2_hdr + 5);
  inner.insert(inner.end(), payload.begin(), payload.end());
  inner.push_back(crc);
  // Wrap in v1 frame with cmd=255 and size = inner.size()
  return buildPacketRaw(static_cast<uint8_t>(MSP_V2_FRAME_ID), inner);
}

} // namespace msp_bridge
