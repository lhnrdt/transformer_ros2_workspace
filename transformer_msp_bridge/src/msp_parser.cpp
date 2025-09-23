#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/crc.hpp"
#include "transformer_msp_bridge/msp_utils.hpp"
#include <cstring>

// Keep MSP_V2_FRAME_ID compatibility if external header doesn't define it
#include "msp/msp_protocol.h"
#ifndef MSP_V2_FRAME_ID
#define MSP_V2_FRAME_ID 255
#endif

namespace transformer_msp_bridge
{

    MSPParser::MSPParser(PacketCallback cb) : cb_(std::move(cb)) {}

    void MSPParser::reset()
    {
        state_ = State::Idle;
        current_version_ = MSPVersion::V1;
        v1_payload_length_ = 0;
        v1_command_ = 0;
        v1_checksum_ = 0;
        payload_buffer_.clear();
        v2_flags_ = 0;
        v2_command_ = 0;
        v2_payload_length_ = 0;
        v2_crc_computed_ = 0;
        v2_crc_received_ = 0;
    frame_trace_.clear();
    }

    void MSPParser::emitV1()
    {
        MSPPacket pkt;
        pkt.version = MSPVersion::V1;
        pkt.cmd = v1_command_;
        pkt.flags = 0;
        pkt.payload = payload_buffer_;
        pkt.tunneled = false;
        if (cb_)
            cb_(pkt);
    }

    void MSPParser::emitV2()
    {
        MSPPacket pkt;
        pkt.version = MSPVersion::V2;
        pkt.cmd = v2_command_;
        pkt.flags = v2_flags_;
        pkt.payload = payload_buffer_;
        pkt.tunneled = false;
        if (cb_)
            cb_(pkt);
        stats_.native_v2_rx++;
    }

    void MSPParser::handleTunneledV2()
    {
        // A tunneled V2 frame is indicated by a V1 command of 255 with an inner payload layout:
        // [flags(1)][command_le(2)][length_le(2)][payload...][crc8]
        if (v1_command_ != 255 || payload_buffer_.size() < 6)
        {
            emitV1();
            return;
        }
        uint16_t inner_payload_length = readUint16LE(payload_buffer_, 3);
        size_t expected_total = 5 + inner_payload_length + 1; // header + payload + crc
        if (payload_buffer_.size() != expected_total)
        {
            emitV1();
            return;
        }
        uint8_t crc = 0;
        for (size_t i = 0; i < 5; ++i)
            crc = crc8_dvb_s2::update(crc, payload_buffer_[i]);
        for (size_t i = 0; i < inner_payload_length; ++i)
            crc = crc8_dvb_s2::update(crc, payload_buffer_[5 + i]);
        uint8_t received_crc = payload_buffer_[5 + inner_payload_length];
        if (crc != received_crc)
        {
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
    // ---- Per-state handler implementations ----
    void MSPParser::handleIdle(uint8_t byte_value) {
        if (byte_value == '$') {
            state_ = State::HeaderStart; frame_trace_.clear(); frame_trace_.push_back(byte_value); }
        else reset();
    }
    void MSPParser::handleHeaderStart(uint8_t byte_value) {
        frame_trace_.push_back(byte_value);
        if (byte_value == 'M') { current_version_ = MSPVersion::V1; state_ = State::HeaderDir; }
        else if (byte_value == 'X') { current_version_ = MSPVersion::V2; state_ = State::V2_HeaderDir2; }
        else reset();
    }
    void MSPParser::handleHeaderDir(uint8_t byte_value) {
        frame_trace_.push_back(byte_value);
        if (byte_value == '<' || byte_value == '>') state_ = State::Size; else reset();
    }
    void MSPParser::handleV1Size(uint8_t byte_value) {
        frame_trace_.push_back(byte_value); v1_payload_length_ = byte_value; payload_buffer_.clear(); payload_buffer_.reserve(v1_payload_length_); v1_checksum_ = byte_value; state_ = State::Cmd; }
    void MSPParser::handleV1Command(uint8_t byte_value) {
        frame_trace_.push_back(byte_value); v1_command_ = byte_value; v1_checksum_ ^= byte_value; state_ = (v1_payload_length_==0)?State::Checksum:State::Payload; }
    void MSPParser::handleV1Payload(uint8_t byte_value) {
        frame_trace_.push_back(byte_value); payload_buffer_.push_back(byte_value); v1_checksum_ ^= byte_value; if (payload_buffer_.size()>=v1_payload_length_) state_ = State::Checksum; }
    void MSPParser::handleV1Checksum(uint8_t byte_value) {
        frame_trace_.push_back(byte_value); if (v1_checksum_ == byte_value) { handleTunneledV2(); } reset(); }
    void MSPParser::handleV2HeaderDir2(uint8_t byte_value) {
        frame_trace_.push_back(byte_value); if (byte_value == '<' || byte_value == '>') { state_ = State::V2_Flags; v2_crc_computed_ = 0; } else reset(); }
    void MSPParser::handleV2Flags(uint8_t byte_value) {
        frame_trace_.push_back(byte_value); v2_flags_ = byte_value; v2_crc_computed_ = crc8_dvb_s2::update(v2_crc_computed_, byte_value); state_ = State::V2_IdLow; }
    void MSPParser::handleV2IdLow(uint8_t byte_value) {
        frame_trace_.push_back(byte_value); v2_command_ = byte_value; v2_crc_computed_ = crc8_dvb_s2::update(v2_crc_computed_, byte_value); state_ = State::V2_IdHigh; }
    void MSPParser::handleV2IdHigh(uint8_t byte_value) {
        frame_trace_.push_back(byte_value); v2_command_ |= (uint16_t)byte_value << 8; v2_crc_computed_ = crc8_dvb_s2::update(v2_crc_computed_, byte_value); state_ = State::V2_LenLow; }
    void MSPParser::handleV2LenLow(uint8_t byte_value) {
        frame_trace_.push_back(byte_value); v2_payload_length_ = byte_value; v2_crc_computed_ = crc8_dvb_s2::update(v2_crc_computed_, byte_value); state_ = State::V2_LenHigh; }
    void MSPParser::handleV2LenHigh(uint8_t byte_value) {
        frame_trace_.push_back(byte_value); v2_payload_length_ |= (uint16_t)byte_value << 8; v2_crc_computed_ = crc8_dvb_s2::update(v2_crc_computed_, byte_value); payload_buffer_.clear(); payload_buffer_.reserve(v2_payload_length_); state_ = (v2_payload_length_==0)?State::V2_CRC:State::V2_Payload; }
    void MSPParser::handleV2Payload(uint8_t byte_value) {
        frame_trace_.push_back(byte_value); payload_buffer_.push_back(byte_value); v2_crc_computed_ = crc8_dvb_s2::update(v2_crc_computed_, byte_value); if (payload_buffer_.size()>=v2_payload_length_) state_ = State::V2_CRC; }
    void MSPParser::handleV2Crc(uint8_t byte_value) {   
        frame_trace_.push_back(byte_value); v2_crc_received_ = byte_value; if (v2_crc_computed_ == v2_crc_received_) { emitV2(); } else { stats_.native_v2_crc_fail++; } reset(); }

    void MSPParser::input(uint8_t byte_value)
    {
        switch (state_)
        {
        case State::Idle:          handleIdle(byte_value); break;
        case State::HeaderStart:   handleHeaderStart(byte_value); break;
        case State::HeaderDir:     handleHeaderDir(byte_value); break;
        case State::Size:          handleV1Size(byte_value); break;
        case State::Cmd:           handleV1Command(byte_value); break;
        case State::Payload:       handleV1Payload(byte_value); break;
        case State::Checksum:      handleV1Checksum(byte_value); break;
        case State::V2_HeaderDir2: handleV2HeaderDir2(byte_value); break;
        case State::V2_Flags:      handleV2Flags(byte_value); break;
        case State::V2_IdLow:      handleV2IdLow(byte_value); break;
        case State::V2_IdHigh:     handleV2IdHigh(byte_value); break;
        case State::V2_LenLow:     handleV2LenLow(byte_value); break;
        case State::V2_LenHigh:    handleV2LenHigh(byte_value); break;
        case State::V2_Payload:    handleV2Payload(byte_value); break;
        case State::V2_CRC:        handleV2Crc(byte_value); break;
        }
    }

} // namespace transformer_msp_bridge
