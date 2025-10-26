#pragma once
#include "transformer_msp_bridge/decoder_base.hpp"
#include "transformer_msp_bridge/decoder_outputs.hpp"
#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include <functional>
namespace transformer_msp_bridge
{
  class SystemDecoder : public IMspDecoder
  {
  public:
    using StatusCallback = std::function<void(const SystemStatusExData &)>;
    using SensorStatusCallback = std::function<void(const SystemSensorStatusData &)>;
    using SensorConfigCallback = std::function<void(const SystemSensorConfigData &)>;
    using GpsStatsCallback = std::function<void(const SystemGpsStatsData &)>;
    using RcTuningCallback = std::function<void(const RcTuningData &)>;
    using RtcCallback = std::function<void(const SystemRtcData &)>;

    struct Callbacks
    {
      StatusCallback status_ex;
      SensorStatusCallback sensor_status;
      SensorConfigCallback sensor_config;
      GpsStatsCallback gps_statistics;
      RcTuningCallback rc_tuning;
      RtcCallback rtc;
    };

    explicit SystemDecoder(Callbacks callbacks = {});
    void set_callbacks(Callbacks callbacks);
    void decodeStatusEx(const MSPPacket &pkt);
    void decodeStatus(const MSPPacket &pkt) { decodeStatusEx(pkt); }
    void decodeSensorStatus(const MSPPacket &pkt);
    void decodeSensorConfig(const MSPPacket &pkt);
    void decodeGpsStatistics(const MSPPacket &pkt);
    void decodeRcTuning(const MSPPacket &pkt);
    void decodeRtc(const MSPPacket &pkt);
    bool matches(uint16_t id) const override
    {
      return id == kMspStatusEx || id == kMspStatus || id == kMspSensorStatus ||
             id == kMspSensorConfig || id == kMspGpsStatistics || id == kMspRcTuning ||
             id == kMspRtc;
    }
    void decode(const MSPPacket &pkt) override
    {
      if (pkt.cmd == kMspStatusEx)
      {
        decodeStatusEx(pkt);
      }
      else if (pkt.cmd == kMspStatus)
      {
        decodeStatus(pkt);
      }
      else if (pkt.cmd == kMspSensorStatus)
      {
        decodeSensorStatus(pkt);
      }
      else if (pkt.cmd == kMspSensorConfig)
      {
        decodeSensorConfig(pkt);
      }
      else if (pkt.cmd == kMspGpsStatistics)
      {
        decodeGpsStatistics(pkt);
      }
      else if (pkt.cmd == kMspRcTuning)
      {
        decodeRcTuning(pkt);
      }
      else if (pkt.cmd == kMspRtc)
      {
        decodeRtc(pkt);
      }
    }
    std::string name() const override { return "system"; }

  private:
  static const uint16_t kMspStatusEx;
  static const uint16_t kMspStatus;
  static const uint16_t kMspSensorStatus;
  static const uint16_t kMspSensorConfig;
  static const uint16_t kMspGpsStatistics;
  static const uint16_t kMspRcTuning;
  static const uint16_t kMspRtc;
    Callbacks callbacks_{};
  };
} // namespace transformer_msp_bridge
