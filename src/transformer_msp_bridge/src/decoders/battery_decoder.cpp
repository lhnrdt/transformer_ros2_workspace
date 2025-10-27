#include "transformer_msp_bridge/decoders/battery_decoder.hpp"
#include "transformer_msp_bridge/msp_utils.hpp"
#include <algorithm>
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
    if (pkt.cmd != kBatteryStateCommand || pkt.payload.size() < 11)
      return;
    if (!callbacks_.status)
      return;

    uint8_t cell_count = 0;
    uint16_t capacity_mah = 0;
    uint8_t voltage_deci = 0;
    uint16_t consumed_mah = 0;
    int16_t current_centiamp = 0;
    uint8_t battery_state = 0;
    uint16_t voltage_centi = 0;

    size_t offset = 0;
    if (!readU8(pkt.payload, offset, cell_count))
      return;
    offset += 1;
    if (!readU16LE(pkt.payload, offset, capacity_mah))
      return;
    offset += 2;
    if (!readU8(pkt.payload, offset, voltage_deci))
      return;
    offset += 1;
    if (!readU16LE(pkt.payload, offset, consumed_mah))
      return;
    offset += 2;
    if (!readI16LE(pkt.payload, offset, current_centiamp))
      return;
    offset += 2;
    if (!readU8(pkt.payload, offset, battery_state))
      return;
    offset += 1;
    if (!readU16LE(pkt.payload, offset, voltage_centi))
      return;

    BatteryStatusData data;
    data.present = true;
    data.cell_count = cell_count;
    data.cell_voltage_v.assign(cell_count, std::numeric_limits<float>::quiet_NaN());
    data.voltage_v = static_cast<float>(voltage_centi) / 100.0F;
    data.current_a = static_cast<float>(current_centiamp) / 100.0F;

    const float total_coulombs = capacity_mah > 0 ? static_cast<float>(capacity_mah) / 1000.0F * 3600.0F
                                                  : std::numeric_limits<float>::quiet_NaN();
    const float consumed_coulombs = static_cast<float>(consumed_mah) / 1000.0F * 3600.0F;
    if (capacity_mah > 0)
    {
      data.charge_c = std::max(0.0F, total_coulombs - consumed_coulombs);
      data.remaining_fraction = std::clamp(1.0F - static_cast<float>(consumed_mah) / static_cast<float>(capacity_mah),
                                           0.0F, 1.0F);
    }
    else
    {
      data.charge_c = std::numeric_limits<float>::quiet_NaN();
      data.remaining_fraction = std::numeric_limits<float>::quiet_NaN();
    }

    (void)voltage_deci;
    (void)battery_state;
    callbacks_.status(data);
  }

} // namespace transformer_msp_bridge
