#include "transformer_msp_bridge/msp_parser.hpp"
#include <cstring>
#include "transformer_msp_bridge/crc.hpp"
#include "transformer_msp_bridge/msp_utils.hpp"

// Keep MSP_V2_FRAME_ID compatibility if external header doesn't define it
#include "msp/msp_protocol.h"
#ifndef MSP_V2_FRAME_ID
#define MSP_V2_FRAME_ID 255
#endif

namespace transformer_msp_bridge {

MSPParser::MSPParser(PacketCallback cb) : cb_(std::move(cb)) {}

void MSPParser::reset() {
  in_frame_ = false;
  current_version_ = MSPVersion::V1;
  frame_pos_ = 0;
  expected_frame_length_ = 0;
  v1_payload_length_ = 0;
  v1_command_ = 0;
  v1_checksum_ = 0;
  v2_flags_ = 0;
  v2_command_ = 0;
  v2_payload_length_ = 0;
  v2_crc_computed_ = 0;
  v2_crc_received_ = 0;
  payload_buffer_.clear();
  frame_trace_.clear();
}

void MSPParser::emitV1() {
  if (cb_)
    cb_(makePacketV1());
}

void MSPParser::emitV2() {
  if (cb_)
    cb_(makePacketV2(false));
  stats_.native_v2_rx++;
}

void MSPParser::handleTunneledV2() {
  // A tunneled V2 frame is indicated by a V1 command of 255 with an inner payload layout:
  // [flags(1)][command_le(2)][length_le(2)][payload...][crc8]
  if (v1_command_ != 255 || payload_buffer_.size() < 6) {
    emitV1();
    return;
  }
  uint16_t inner_payload_length = readUint16LE(payload_buffer_, 3);
  size_t expected_total = 5 + inner_payload_length + 1;  // header + payload + crc
  if (payload_buffer_.size() != expected_total) {
    emitV1();
    return;
  }
  uint8_t crc = 0;
  for (size_t i = 0; i < 5; ++i)
    crc = crc8_dvb_s2::update(crc, payload_buffer_[i]);
  for (size_t i = 0; i < inner_payload_length; ++i)
    crc = crc8_dvb_s2::update(crc, payload_buffer_[5 + i]);
  uint8_t received_crc = payload_buffer_[5 + inner_payload_length];
  if (crc != received_crc) {
    stats_.tunneled_v2_crc_fail++;
    return;
  }
  MSPPacket pkt;
  pkt.version = MSPVersion::V2;
  pkt.tunneled = true;
  pkt.flags = payload_buffer_[0];
  pkt.cmd = readUint16LE(payload_buffer_, 1);
  pkt.payload.assign(payload_buffer_.begin() + 5, payload_buffer_.begin() + 5 + inner_payload_length);
  if (cb_)
    cb_(pkt);
  stats_.tunneled_v2_rx++;
}
MSPPacket MSPParser::makePacketV1() const {
  MSPPacket p;
  p.version = MSPVersion::V1;
  p.cmd = v1_command_;
  p.flags = 0;
  p.payload = payload_buffer_;
  p.tunneled = false;
  return p;
}
MSPPacket MSPParser::makePacketV2(bool tunneled) const {
  MSPPacket p;
  p.version = MSPVersion::V2;
  p.cmd = v2_command_;
  p.flags = v2_flags_;
  p.payload = payload_buffer_;
  p.tunneled = tunneled;
  return p;
}
bool MSPParser::abort() {
  if (!in_frame_)
    return false;
  abort_requested_ = true;
  stats_.aborted_frames++;
  reset();
  return true;
}
void MSPParser::input(uint8_t byte_value) {
  // Fast path: seek frame start.
  if (!in_frame_) {
    if (byte_value == '$') {
      reset();
      in_frame_ = true;
      frame_pos_ = 1;  // '$'
      frame_trace_.push_back(byte_value);
    }
    return;
  }

  frame_trace_.push_back(byte_value);
  ++frame_pos_;

  // Version decision at position 2 ('$' already consumed).
  if (frame_pos_ == 2) {
    if (byte_value == 'M') {
      current_version_ = MSPVersion::V1;
    } else if (byte_value == 'X') {
      current_version_ = MSPVersion::V2;
    } else {
      stats_.malformed_header++;
      reset();
    }
    return;
  }

  // Direction / secondary header char at position 3.
  if (frame_pos_ == 3) {
    if (byte_value != '<' && byte_value != '>') {
      stats_.malformed_header++;
      reset();
    }
    return;
  }

  if (current_version_ == MSPVersion::V1) {
    // Layout after first 3 bytes for V1:
    // 4: payload size (1)
    // 5: command (1)
    // 6..(5+len): payload
    // (6+len): checksum
    if (frame_pos_ == 4) {  // size
      v1_payload_length_ = byte_value;
      v1_checksum_ = byte_value;  // initial XOR with size
      payload_buffer_.clear();
      if (v1_payload_length_ > max_payload_size_) {
        stats_.oversized_frame_dropped++;
        reset();
        return;
      }
      payload_buffer_.reserve(v1_payload_length_);
      if (v1_payload_length_ == 0) {
        expected_frame_length_ = 6;  // $ M < size cmd checksum (no payload)
      }
      return;
    }
    if (frame_pos_ == 5) {  // command
      v1_command_ = byte_value;
      v1_checksum_ ^= byte_value;
      if (v1_payload_length_ > 0) {
        expected_frame_length_ = 6 + v1_payload_length_;  // compute once we know size
      }
      return;
    }
    // Payload bytes (if any)
    size_t payload_index = frame_pos_ - 6;  // first payload byte => index 0
    if (frame_pos_ >= 6 && payload_index < v1_payload_length_) {
      payload_buffer_.push_back(byte_value);
      v1_checksum_ ^= byte_value;
      return;
    }
    // Checksum byte
    if (expected_frame_length_ && frame_pos_ == expected_frame_length_) {
      if (v1_checksum_ == byte_value) {
        handleTunneledV2();
      }
      reset();
      return;
    }
    // If we reach here something inconsistent happened; reset.
    reset();
    return;
  } else {  // MSP V2
    // Layout after first 3 bytes for V2:
    // 4: flags (1)
    // 5: cmd id low
    // 6: cmd id high
    // 7: len low
    // 8: len high
    // 9..(8+len): payload
    // (9+len): crc
    if (frame_pos_ == 4) {  // flags
      v2_flags_ = byte_value;
      v2_crc_computed_ = crc8_dvb_s2::update(0, byte_value);
      return;
    }
    if (frame_pos_ == 5) {  // id low
      v2_command_ = byte_value;
      v2_crc_computed_ = crc8_dvb_s2::update(v2_crc_computed_, byte_value);
      return;
    }
    if (frame_pos_ == 6) {  // id high
      v2_command_ |= static_cast<uint16_t>(byte_value) << 8;
      v2_crc_computed_ = crc8_dvb_s2::update(v2_crc_computed_, byte_value);
      return;
    }
    if (frame_pos_ == 7) {  // len low
      v2_payload_length_ = byte_value;
      v2_crc_computed_ = crc8_dvb_s2::update(v2_crc_computed_, byte_value);
      return;
    }
    if (frame_pos_ == 8) {  // len high
      v2_payload_length_ |= static_cast<uint16_t>(byte_value) << 8;
      v2_crc_computed_ = crc8_dvb_s2::update(v2_crc_computed_, byte_value);
      payload_buffer_.clear();
      if (v2_payload_length_ > max_payload_size_) {
        stats_.oversized_frame_dropped++;
        reset();
        return;
      }
      payload_buffer_.reserve(v2_payload_length_);
      if (v2_payload_length_ == 0) {
        expected_frame_length_ = 9;  // '$' 'X' '<' flags idL idH lenL lenH crc
      } else {
        expected_frame_length_ = 9 + v2_payload_length_;
      }
      return;
    }
    // Payload region
    if (frame_pos_ >= 9 && frame_pos_ < expected_frame_length_) {
      // If expected length not yet set something went wrong.
      if (!expected_frame_length_) {
        reset();
        return;
      }
      size_t payload_index = frame_pos_ - 9;  // first payload byte index 0
      if (payload_index < v2_payload_length_) {
        payload_buffer_.push_back(byte_value);
        v2_crc_computed_ = crc8_dvb_s2::update(v2_crc_computed_, byte_value);
        return;
      }
    }
    // CRC byte
    if (expected_frame_length_ && frame_pos_ == expected_frame_length_) {
      v2_crc_received_ = byte_value;
      if (v2_crc_computed_ == v2_crc_received_) {
        emitV2();
      } else {
        stats_.native_v2_crc_fail++;
      }
      reset();
      return;
    }
    reset();
    return;
  }
}

}  // namespace transformer_msp_bridge
