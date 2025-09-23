#include "transformer_msp_bridge/msp_builders.hpp"
#include "msp/msp_protocol.h"
#ifndef MSP_V2_FRAME_ID
#define MSP_V2_FRAME_ID 255
#endif

namespace transformer_msp_bridge
{
    namespace
    {
        inline uint8_t crc8_update(uint8_t crc, uint8_t data)
        {
            crc ^= data;
            for (int i = 0; i < 8; ++i)
                crc = (crc & 0x80) ? ((crc << 1) ^ 0xD5) : (crc << 1);
            return crc;
        }
    }

    std::vector<uint8_t> buildPacket(uint8_t cmd, const std::vector<uint16_t> &rc_values)
    {
        std::vector<uint8_t> payload;
        payload.reserve(rc_values.size() * 2);
        for (uint16_t v : rc_values)
        {
            payload.push_back(static_cast<uint8_t>(v & 0xFF));
            payload.push_back(static_cast<uint8_t>((v >> 8) & 0xFF));
        }
        return buildPacketRaw(cmd, payload);
    }

    std::vector<uint8_t> buildPacketRaw(uint8_t cmd, const std::vector<uint8_t> &payload)
    {
        uint8_t size = static_cast<uint8_t>(payload.size());
        uint8_t cs = size ^ cmd;
        for (uint8_t b : payload)
            cs ^= b;
        std::vector<uint8_t> out;
        out.reserve(6 + payload.size());
        out.push_back('$');
        out.push_back('M');
        out.push_back('<');
        out.push_back(size);
        out.push_back(cmd);
        out.insert(out.end(), payload.begin(), payload.end());
        out.push_back(cs);
        return out;
    }

    std::vector<uint8_t> buildPacketV2(uint16_t cmd, const std::vector<uint8_t> &payload, uint8_t flags)
    {
        uint16_t len = static_cast<uint16_t>(payload.size());
        uint8_t crc = 0;
        auto upd = [&](uint8_t b)
        { crc = crc8_update(crc, b); };
        std::vector<uint8_t> out;
        out.reserve(8 + payload.size());
        out.push_back('$');
        out.push_back('X');
        out.push_back('<');
        out.push_back(flags);
        upd(flags);
        uint8_t cmdL = cmd & 0xFF, cmdH = (cmd >> 8) & 0xFF;
        out.push_back(cmdL);
        upd(cmdL);
        out.push_back(cmdH);
        upd(cmdH);
        uint8_t lenL = len & 0xFF, lenH = (len >> 8) & 0xFF;
        out.push_back(lenL);
        upd(lenL);
        out.push_back(lenH);
        upd(lenH);
        for (uint8_t b : payload)
        {
            out.push_back(b);
            upd(b);
        }
        out.push_back(crc);
        return out;
    }

    std::vector<uint8_t> buildPacketV2OverV1(uint16_t cmd, const std::vector<uint8_t> &payload, uint8_t flags)
    {
        uint16_t len = static_cast<uint16_t>(payload.size());
        uint8_t hdr[5];
        hdr[0] = flags;
        hdr[1] = static_cast<uint8_t>(cmd & 0xFF);
        hdr[2] = static_cast<uint8_t>((cmd >> 8) & 0xFF);
        hdr[3] = static_cast<uint8_t>(len & 0xFF);
        hdr[4] = static_cast<uint8_t>((len >> 8) & 0xFF);
        uint8_t crc = 0;
        for (uint8_t b : hdr)
            crc = crc8_update(crc, b);
        for (uint8_t b : payload)
            crc = crc8_update(crc, b);
        std::vector<uint8_t> inner;
        inner.reserve(5 + payload.size() + 1);
        inner.insert(inner.end(), hdr, hdr + 5);
        inner.insert(inner.end(), payload.begin(), payload.end());
        inner.push_back(crc);
        return buildPacketRaw(static_cast<uint8_t>(MSP_V2_FRAME_ID), inner);
    }

} // namespace transformer_msp_bridge
