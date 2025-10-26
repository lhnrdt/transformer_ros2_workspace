#include "transformer_msp_bridge/decoders/gps_decoder.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include "transformer_msp_bridge/msp_utils.hpp"
#include <utility>

namespace transformer_msp_bridge
{

  namespace
  {
  const uint16_t kMspRawGps = msp::command_id("MSP_RAW_GPS");
  const uint16_t kMspCompGps = msp::command_id("MSP_COMP_GPS");
  }

  GpsDecoder::GpsDecoder(Callbacks callbacks) : callbacks_(std::move(callbacks)) {}

  void GpsDecoder::set_callbacks(Callbacks callbacks) { callbacks_ = std::move(callbacks); }

  bool GpsDecoder::matches(uint16_t id) const
  {
    return id == kMspRawGps || id == kMspCompGps;
  }
  std::string GpsDecoder::name() const
  {
    return "gps";
  }

  void GpsDecoder::decode(const MSPPacket &pkt)
  {
    if (pkt.cmd == kMspRawGps)
      decodeRawGps(pkt);
    else if (pkt.cmd == kMspCompGps)
      decodeCompGps(pkt);
  }

  void GpsDecoder::decodeRawGps(const MSPPacket &pkt)
  {
    if (pkt.cmd != kMspRawGps || pkt.payload.size() < 14)
      return;
    uint8_t fix, sats;
    int32_t lat, lon;
    int16_t alt;
    uint16_t speed_cms, course_deg10;
    if (!readU8(pkt.payload, 0, fix) || !readU8(pkt.payload, 1, sats) || !readI32LE(pkt.payload, 2, lat) ||
        !readI32LE(pkt.payload, 6, lon) || !readI16LE(pkt.payload, 10, alt) || !readU16LE(pkt.payload, 12, speed_cms) ||
        !readU16LE(pkt.payload, 14, course_deg10))
    {
      return;
    }
    constexpr double deg_to_rad = 3.14159265358979323846 / 180.0;
    GpsRawData data;
    data.fix_type = fix;
    data.satellites = sats;
    data.latitude_deg = static_cast<double>(lat) * 1e-7;
    data.longitude_deg = static_cast<double>(lon) * 1e-7;
    data.altitude_m = static_cast<double>(alt);
    data.speed_mps = static_cast<double>(speed_cms) / 100.0;
    data.course_rad = static_cast<double>(course_deg10) / 10.0 * deg_to_rad;
    if (callbacks_.raw)
      callbacks_.raw(data);
  }

  void GpsDecoder::decodeCompGps(const MSPPacket &pkt)
  {
    if (pkt.cmd != kMspCompGps || pkt.payload.size() < 4)
      return;
    uint16_t dist_u16, dir_deg_u16;
    if (!readU16LE(pkt.payload, 0, dist_u16) || !readU16LE(pkt.payload, 2, dir_deg_u16))
      return;
    GpsHomeVector data;
    data.distance_m = static_cast<double>(dist_u16);
    data.direction_deg = static_cast<double>(dir_deg_u16);
    if (callbacks_.home)
      callbacks_.home(data);
  }

} // namespace transformer_msp_bridge
