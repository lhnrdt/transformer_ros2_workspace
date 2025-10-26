#include "transformer_msp_bridge/decoders/battery_decoder.hpp"
#include <limits>
#include <utility>

namespace transformer_msp_bridge
{

  const uint16_t BatteryDecoder::kAnalogCommand = msp::command_id("MSP_ANALOG");
  const uint16_t BatteryDecoder::kBatteryStateCommand = msp::command_id("MSP_BATTERY_STATE");

  BatteryDecoder::BatteryDecoder(Callbacks callbacks) : callbacks_(std::move(callbacks)) {}

  void BatteryDecoder::set_callbacks(Callbacks callbacks) { callbacks_ = std::move(callbacks); }

  void BatteryDecoder::decodeAnalog(const MSPPacket &pkt)
  {
    if (pkt.cmd != kAnalogCommand)
      return;
    if (pkt.payload.empty() || !callbacks_.analog)
      return;
    BatteryAnalogData data;
    data.voltage_v = static_cast<float>(pkt.payload[0]) / 10.0F;
    data.present = true;
    callbacks_.analog(data);
  }

  void BatteryDecoder::decodeBatteryState(const MSPPacket &pkt)
  {
    if (pkt.cmd != kBatteryStateCommand)
      return;
    if (pkt.payload.size() < 1)
    {
      return;
    }

    if (!callbacks_.status)
      return;

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

    BatteryStatusData data;
    data.present = true;
    data.cell_count = cells;
    data.cell_voltage_v.assign(cells, std::numeric_limits<float>::quiet_NaN());

    if (pkt.payload.size() >= off + 2)
    {
      uint16_t cap = rd16(off);
      off += 2;
      // capacity reported in mAh * 10? original used /1000 *3600 (convert mAh to Coulombs)
      data.charge_c = cap / 1000.0f * 3600.0f;
    }
    if (pkt.payload.size() >= off + 2)
    {
      uint16_t mv = rd16(off);
      off += 2;
      data.voltage_v = mv / 100.0f;
    }
    if (pkt.payload.size() >= off + 2)
    {
      uint16_t mc = rd16(off);
      off += 2;
      data.current_a = mc / 100.0f;
    }
    if (pkt.payload.size() > off)
    {
      uint8_t rem = rd8(off);
      data.remaining_fraction = rem / 100.0f;
    }

    callbacks_.status(data);
  }

} // namespace transformer_msp_bridge
