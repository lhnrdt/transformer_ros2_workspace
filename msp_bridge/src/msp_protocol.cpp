#include "msp_bridge/msp_protocol.hpp"
#include <cstring>

namespace msp_bridge {

MSPParser::MSPParser(PacketCallback cb) : cb_(std::move(cb)) {}

void MSPParser::reset() {
  state_ = State::Idle;
  size_ = 0; cmd_ = 0; checksum_ = 0; buf_.clear();
}

void MSPParser::input(uint8_t b) {
  switch(state_) {
    case State::Idle:
      if (b == '$') state_ = State::HeaderStart; else reset();
      break;
    case State::HeaderStart:
      if (b == 'M') state_ = State::HeaderDir; else reset();
      break;
    case State::HeaderDir:
      if (b == '<' || b == '>') { state_ = State::Size; } else { reset(); }
      break;
    case State::Size:
      size_ = b;
      buf_.clear(); buf_.reserve(size_);
      checksum_ = b;
      state_ = State::Cmd;
      break;
    case State::Cmd:
      cmd_ = b;
      checksum_ ^= b;
      if (size_ == 0) { state_ = State::Checksum; } else { state_ = State::Payload; }
      break;
    case State::Payload:
      buf_.push_back(b);
      checksum_ ^= b;
      if (buf_.size() >= size_) {
        state_ = State::Checksum;
      }
      break;
    case State::Checksum:
      if (checksum_ == b) {
        MSPPacket pkt{cmd_, buf_};
        if (cb_) cb_(pkt);
      }
      reset();
      break;
  }
}

std::vector<uint8_t> buildPacket(uint8_t cmd, const std::vector<uint16_t>& rc_values) {
  // RC channels little-endian 16-bit each
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

} // namespace msp_bridge
