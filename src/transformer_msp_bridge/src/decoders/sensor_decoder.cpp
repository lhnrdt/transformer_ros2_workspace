#include "transformer_msp_bridge/decoders/sensor_decoder.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include "transformer_msp_bridge/msp_utils.hpp"
#include <cstring>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace transformer_msp_bridge
{

  namespace
  {
  const uint16_t kRangefinderCommand = msp::command_id("MSP2_SENSOR_RANGEFINDER");
  const uint16_t kCompassCommand = msp::command_id("MSP2_SENSOR_COMPASS");
  const uint16_t kBarometerCommand = msp::command_id("MSP2_SENSOR_BAROMETER");

    [[maybe_unused]] const bool kRegistryValidated = []() {
      if (kRangefinderCommand == 0)
      {
        throw std::runtime_error("MSP2_SENSOR_RANGEFINDER missing from registry");
      }
      if (kCompassCommand == 0)
      {
        throw std::runtime_error("MSP2_SENSOR_COMPASS missing from registry");
      }
      if (kBarometerCommand == 0)
      {
        throw std::runtime_error("MSP2_SENSOR_BAROMETER missing from registry");
      }
      return true;
    }();
  } // namespace

  SensorDecoder::SensorDecoder() = default;

  SensorDecoder::SensorDecoder(Callbacks callbacks) : callbacks_(std::move(callbacks)) {}

  void SensorDecoder::set_callbacks(Callbacks callbacks) { callbacks_ = std::move(callbacks); }

  bool SensorDecoder::matches(uint16_t command_id) const
  {
    return command_id == kRangefinderCommand || command_id == kCompassCommand || command_id == kBarometerCommand;
  }

  std::string SensorDecoder::name() const { return "sensor"; }

  void SensorDecoder::decode(const MSPPacket &pkt)
  {
    if (pkt.cmd == kRangefinderCommand)
      decodeRangefinder(pkt);
    else if (pkt.cmd == kCompassCommand)
      decodeCompass(pkt);
    else if (pkt.cmd == kBarometerCommand)
      decodeBarometer(pkt);
  }

  void SensorDecoder::decodeRangefinder(const MSPPacket &pkt)
  {
    RangefinderSample sample;
    uint8_t quality = 0;
    int32_t distance_mm = 0;
    if (!readU8(pkt.payload, 0, quality) || !readI32LE(pkt.payload, 1, distance_mm))
      return;

    if (distance_mm < 0)
      sample.distance_m = std::numeric_limits<float>::quiet_NaN();
    else
      sample.distance_m = static_cast<float>(distance_mm) / 1000.0F;
    sample.quality = quality;
    if (callbacks_.rangefinder)
      callbacks_.rangefinder(sample);
    if (callbacks_.log_first_frame && callbacks_.log_info && !logged_rangefinder_)
    {
      std::ostringstream oss;
      oss << "Rangefinder first frame: quality=" << static_cast<unsigned>(quality) << " dist=" << sample.distance_m
          << "m";
      callbacks_.log_info(oss.str());
      logged_rangefinder_ = true;
    }
  }

  void SensorDecoder::decodeCompass(const MSPPacket &pkt)
  {
    CompassSample sample;
    int16_t mag_x = 0;
    int16_t mag_y = 0;
    int16_t mag_z = 0;
    uint32_t timestamp_ms = 0;

  if (!readU8(pkt.payload, 0, sample.instance) || !readU32LE(pkt.payload, 1, timestamp_ms) ||
    !readI16LE(pkt.payload, 5, mag_x) || !readI16LE(pkt.payload, 7, mag_y) ||
    !readI16LE(pkt.payload, 9, mag_z))
      return;

    (void)timestamp_ms; // Timestamp is not currently exposed.
    sample.magnetic_field_mgauss = {mag_x, mag_y, mag_z};
    if (callbacks_.compass)
      callbacks_.compass(sample);
    if (callbacks_.log_first_frame && callbacks_.log_info && !logged_compass_)
    {
      std::ostringstream oss;
      oss << "Compass first frame: inst=" << static_cast<unsigned>(sample.instance) << " mGauss=(" << mag_x << ','
          << mag_y << ',' << mag_z << ')';
      callbacks_.log_info(oss.str());
      logged_compass_ = true;
    }
  }

  void SensorDecoder::decodeBarometer(const MSPPacket &pkt)
  {
    BarometerSample sample;
    int16_t temp_raw = 0;
    uint32_t pressure_raw = 0;

    uint32_t timestamp_ms = 0;

    if (!readU8(pkt.payload, 0, sample.instance) || !readU32LE(pkt.payload, 1, timestamp_ms) ||
        !readU32LE(pkt.payload, 5, pressure_raw) || !readI16LE(pkt.payload, 9, temp_raw))
      return;

  float pressure = 0.0F;
  std::memcpy(&pressure, &pressure_raw, sizeof(pressure));
    sample.pressure_pa = pressure;
    sample.temperature_c = static_cast<float>(temp_raw) / 100.0F;
    (void)timestamp_ms;
    if (callbacks_.barometer)
      callbacks_.barometer(sample);
    if (callbacks_.log_first_frame && callbacks_.log_info && !logged_baro_)
    {
      std::ostringstream oss;
      oss << "Barometer first frame: inst=" << static_cast<unsigned>(sample.instance) << " pressure="
          << sample.pressure_pa << "Pa temp=" << sample.temperature_c << 'C';
      callbacks_.log_info(oss.str());
      logged_baro_ = true;
    }
  }

  // Explicit instantiations if needed (none currently)

} // namespace transformer_msp_bridge
