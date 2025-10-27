#include "transformer_msp_bridge/decoders/battery_decoder.hpp"
#include "transformer_msp_bridge/msp_utils.hpp"
#include <limits>
#include <utility>

namespace transformer_msp_bridge
{

  const uint16_t BatteryDecoder::kAnalogCommand = msp::command_id("MSP2_INAV_ANALOG");
  const uint16_t BatteryDecoder::kBatteryConfigCommand = msp::command_id("MSP2_INAV_BATTERY_CONFIG");

  BatteryDecoder::BatteryDecoder(Callbacks callbacks) : callbacks_(std::move(callbacks)) {}

  void BatteryDecoder::set_callbacks(Callbacks callbacks) { callbacks_ = std::move(callbacks); }

  void BatteryDecoder::decodeAnalog(const MSPPacket &pkt)
  {
    if (pkt.cmd != kAnalogCommand)
      return;
    if (!callbacks_.analog)
      return;
    if (pkt.payload.size() < 24)
      return;

    size_t offset = 0;
    uint8_t battery_flags = 0;
    uint16_t vbat_raw = 0;
    uint16_t amperage_raw = 0;
    uint32_t power_draw_raw = 0;
    uint32_t mah_drawn_raw = 0;
    uint32_t mwh_drawn_raw = 0;
    uint32_t remaining_capacity_raw = 0;
    uint8_t percentage_raw = 0;
    uint16_t rssi_raw = 0;

    if (!readU8(pkt.payload, offset, battery_flags))
      return;
    offset += 1;
    if (!readU16LE(pkt.payload, offset, vbat_raw))
      return;
    offset += 2;
    if (!readU16LE(pkt.payload, offset, amperage_raw))
      return;
    offset += 2;
    if (!readU32LE(pkt.payload, offset, power_draw_raw))
      return;
    offset += 4;
    if (!readU32LE(pkt.payload, offset, mah_drawn_raw))
      return;
    offset += 4;
    if (!readU32LE(pkt.payload, offset, mwh_drawn_raw))
      return;
    offset += 4;
    if (!readU32LE(pkt.payload, offset, remaining_capacity_raw))
      return;
    offset += 4;
    if (!readU8(pkt.payload, offset, percentage_raw))
      return;
    offset += 1;
    if (!readU16LE(pkt.payload, offset, rssi_raw))
      return;

    BatteryAnalogData data;
    data.present = true;
    data.full_on_plugin = (battery_flags & 0x01u) != 0u;
    data.use_capacity_thresholds = (battery_flags & 0x02u) != 0u;
    data.battery_state = static_cast<uint8_t>((battery_flags >> 2) & 0x03u);
    data.cell_count = static_cast<uint8_t>((battery_flags >> 4) & 0x0Fu);
    if (data.cell_count == 0 && last_config_)
    {
      data.cell_count = last_config_->cell_count;
    }
    data.voltage_v = static_cast<float>(vbat_raw) / 100.0F;
    data.current_a = static_cast<float>(amperage_raw) / 100.0F;
    data.power_w = static_cast<float>(power_draw_raw) / 1000.0F;
    data.consumed_mah = static_cast<float>(mah_drawn_raw);
    data.consumed_mwh = static_cast<float>(mwh_drawn_raw);
    if (percentage_raw <= 100u)
    {
      data.percentage = static_cast<float>(percentage_raw);
    }
    else
    {
      data.percentage = std::numeric_limits<float>::quiet_NaN();
    }
    data.capacity_unit = last_config_ ? last_config_->capacity_unit : static_cast<uint8_t>(0xFFu);
    data.remaining_capacity_mah = std::numeric_limits<float>::quiet_NaN();
    data.remaining_capacity_mwh = std::numeric_limits<float>::quiet_NaN();
    if (data.capacity_unit == 0)
    {
      data.remaining_capacity_mah = static_cast<float>(remaining_capacity_raw);
    }
    else if (data.capacity_unit == 1)
    {
      data.remaining_capacity_mwh = static_cast<float>(remaining_capacity_raw);
    }
  data.rssi_raw = rssi_raw;
  data.rssi_valid = (rssi_raw != 0u);

    callbacks_.analog(data);
  }

  void BatteryDecoder::decodeBatteryConfig(const MSPPacket &pkt)
  {
    if (pkt.cmd != kBatteryConfigCommand)
      return;
    if (pkt.payload.size() < 29)
      return;

    size_t offset = 0;
    uint16_t voltage_scale_raw = 0;
    uint8_t voltage_source = 0;
    uint8_t cell_count = 0;
    uint16_t cell_detect_raw = 0;
    uint16_t cell_min_raw = 0;
    uint16_t cell_max_raw = 0;
    uint16_t cell_warning_raw = 0;
    uint16_t current_offset_raw = 0;
    uint16_t current_scale_raw = 0;
    uint32_t capacity_value_raw = 0;
    uint32_t capacity_warning_raw = 0;
    uint32_t capacity_critical_raw = 0;
    uint8_t capacity_unit = 0;

    if (!readU16LE(pkt.payload, offset, voltage_scale_raw))
      return;
    offset += 2;
    if (!readU8(pkt.payload, offset, voltage_source))
      return;
    offset += 1;
    if (!readU8(pkt.payload, offset, cell_count))
      return;
    offset += 1;
    if (!readU16LE(pkt.payload, offset, cell_detect_raw))
      return;
    offset += 2;
    if (!readU16LE(pkt.payload, offset, cell_min_raw))
      return;
    offset += 2;
    if (!readU16LE(pkt.payload, offset, cell_max_raw))
      return;
    offset += 2;
    if (!readU16LE(pkt.payload, offset, cell_warning_raw))
      return;
    offset += 2;
    if (!readU16LE(pkt.payload, offset, current_offset_raw))
      return;
    offset += 2;
    if (!readU16LE(pkt.payload, offset, current_scale_raw))
      return;
    offset += 2;
    if (!readU32LE(pkt.payload, offset, capacity_value_raw))
      return;
    offset += 4;
    if (!readU32LE(pkt.payload, offset, capacity_warning_raw))
      return;
    offset += 4;
    if (!readU32LE(pkt.payload, offset, capacity_critical_raw))
      return;
    offset += 4;
    if (!readU8(pkt.payload, offset, capacity_unit))
      return;

    BatteryConfigData config;
    config.voltage_scale = static_cast<float>(voltage_scale_raw);
    config.voltage_source = voltage_source;
    config.cell_count = cell_count;
    config.cell_detect_voltage_v = static_cast<float>(cell_detect_raw) / 100.0F;
    config.cell_min_voltage_v = static_cast<float>(cell_min_raw) / 100.0F;
    config.cell_max_voltage_v = static_cast<float>(cell_max_raw) / 100.0F;
    config.cell_warning_voltage_v = static_cast<float>(cell_warning_raw) / 100.0F;
    config.current_offset_mv = static_cast<float>(current_offset_raw);
    config.current_scale = static_cast<float>(current_scale_raw);
    config.capacity_unit = capacity_unit;
    config.capacity_mah = std::numeric_limits<float>::quiet_NaN();
    config.capacity_warning_mah = std::numeric_limits<float>::quiet_NaN();
    config.capacity_critical_mah = std::numeric_limits<float>::quiet_NaN();
    config.capacity_mwh = std::numeric_limits<float>::quiet_NaN();
    config.capacity_warning_mwh = std::numeric_limits<float>::quiet_NaN();
    config.capacity_critical_mwh = std::numeric_limits<float>::quiet_NaN();

    if (capacity_unit == 0)
    {
      config.capacity_mah = static_cast<float>(capacity_value_raw);
      config.capacity_warning_mah = static_cast<float>(capacity_warning_raw);
      config.capacity_critical_mah = static_cast<float>(capacity_critical_raw);
    }
    else if (capacity_unit == 1)
    {
      config.capacity_mwh = static_cast<float>(capacity_value_raw);
      config.capacity_warning_mwh = static_cast<float>(capacity_warning_raw);
      config.capacity_critical_mwh = static_cast<float>(capacity_critical_raw);
    }

    last_config_ = config;

    if (callbacks_.config)
    {
      callbacks_.config(config);
    }
  }

} // namespace transformer_msp_bridge
