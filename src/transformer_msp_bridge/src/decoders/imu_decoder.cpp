#include "transformer_msp_bridge/decoders/imu_decoder.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include "transformer_msp_bridge/msp_utils.hpp"
#include <utility>

namespace transformer_msp_bridge
{

  namespace
  {
  const uint16_t kMspRawImu = msp::command_id("MSP_RAW_IMU");
  }

  ImuDecoder::ImuDecoder(Callback callback) : callback_(std::move(callback)) {}

  void ImuDecoder::set_callback(Callback callback) { callback_ = std::move(callback); }

  bool ImuDecoder::matches(uint16_t id) const
  {
    return id == kMspRawImu;
  }
  std::string ImuDecoder::name() const
  {
    return "imu";
  }

  void ImuDecoder::decode(const MSPPacket &pkt)
  {
    if (pkt.cmd == kMspRawImu)
      decodeRawImu(pkt);
  }

  void ImuDecoder::decodeRawImu(const MSPPacket &pkt)
  {
    if (pkt.cmd != kMspRawImu || pkt.payload.size() < 18)
      return;
    int16_t ax, ay, az, gx, gy, gz, mx, my, mz;
    if (!readI16LE(pkt.payload, 0, ax) || !readI16LE(pkt.payload, 2, ay) || !readI16LE(pkt.payload, 4, az) ||
        !readI16LE(pkt.payload, 6, gx) || !readI16LE(pkt.payload, 8, gy) || !readI16LE(pkt.payload, 10, gz) ||
        !readI16LE(pkt.payload, 12, mx) || !readI16LE(pkt.payload, 14, my) || !readI16LE(pkt.payload, 16, mz))
      return;
    constexpr double gravity = 9.80665;
    constexpr double deg_to_rad = 3.14159265358979323846 / 180.0;
    ImuSample sample;
    sample.linear_acceleration_mps2 = {static_cast<double>(ax) * gravity / 512.0,
                                       static_cast<double>(ay) * gravity / 512.0,
                                       static_cast<double>(az) * gravity / 512.0};
    sample.angular_velocity_radps = {static_cast<double>(gx) * deg_to_rad / 16.0,
                                     static_cast<double>(gy) * deg_to_rad / 16.0,
                                     static_cast<double>(gz) * deg_to_rad / 16.0};
    sample.magnetic_field_tesla = {static_cast<double>(mx) * 1e-6, static_cast<double>(my) * 1e-6,
                                   static_cast<double>(mz) * 1e-6};
    if (callback_)
      callback_(sample);
  }

} // namespace transformer_msp_bridge
