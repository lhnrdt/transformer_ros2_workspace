#include "transformer_msp_bridge/decoders/battery_decoder.hpp"
#include <limits>
#include "transformer_msp_bridge/msp_registry.hpp"

namespace transformer_msp_bridge
{

  void BatteryDecoder::decodeAnalog(const MSPPacket &pkt)
  {
    if (pkt.cmd != MSP_ANALOG)
      return;
    sensor_msgs::msg::BatteryState b;
    bool published = false;
    if (!pkt.payload.empty())
    {
      uint8_t vbat_deciv = pkt.payload[0];
      b.voltage = vbat_deciv / 10.0f;
      published = true;
    }
    if (published)
    {
      b.present = true;
      b.percentage = std::numeric_limits<float>::quiet_NaN();
      b.current = std::numeric_limits<float>::quiet_NaN();
      b.charge = std::numeric_limits<float>::quiet_NaN();
      analog_pub_->publish(b);
    }
  }

  void BatteryDecoder::decodeBatteryState(const MSPPacket &pkt)
  {
    if (pkt.payload.size() < 1)
    {
      return;
    }

    size_t off = 0;
    auto rd8 = [&](size_t o) -> uint8_t
    {
      return o < pkt.payload.size() ? pkt.payload[o] : 0;
    };
    auto rd16 = [&](size_t o) -> uint16_t
    {
      if (pkt.payload.size() < o + 2)
        return 0;
      return static_cast<uint16_t>(pkt.payload[o] | (pkt.payload[o + 1] << 8));
    };

    uint8_t cells = rd8(off);
    off += 1;

    sensor_msgs::msg::BatteryState b;
    b.header.stamp = node_.now();
    b.present = true;
    b.cell_voltage.resize(cells, std::numeric_limits<float>::quiet_NaN());

    if (pkt.payload.size() >= off + 2)
    {
      uint16_t cap = rd16(off);
      off += 2;
      // capacity reported in mAh * 10? original used /1000 *3600 (convert mAh to Coulombs)
      b.charge = cap / 1000.0f * 3600.0f;
    }
    if (pkt.payload.size() >= off + 2)
    {
      uint16_t mv = rd16(off);
      off += 2;
      b.voltage = mv / 100.0f;
    }
    if (pkt.payload.size() >= off + 2)
    {
      uint16_t mc = rd16(off);
      off += 2;
      b.current = mc / 100.0f;
    }
    if (pkt.payload.size() > off)
    {
      uint8_t rem = rd8(off);
      b.percentage = rem / 100.0f;
    }

    extended_pub_->publish(b);
  }

} // namespace transformer_msp_bridge
