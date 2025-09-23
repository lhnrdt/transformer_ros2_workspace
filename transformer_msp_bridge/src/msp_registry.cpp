#include "transformer_msp_bridge/msp_registry.hpp"
#include "msp/msp_protocol.h" // external constants (v1 IDs)
#include "msp/msp_protocol_v2_sensor.h" // v2 sensor IDs

namespace transformer_msp_bridge {

std::vector<CommandDescriptor> build_default_registry() {
  std::vector<CommandDescriptor> regs;
  // ATTITUDE (example) - request has no payload
  CommandDescriptor att;
  att.id = MSP_ATTITUDE;
  att.name = "MSP_ATTITUDE";
  att.poll_rate_hz = 10.0; // default; node can override via params later
  att.build_request_cb = [=]() {
    return buildPacketRaw(static_cast<uint8_t>(MSP_ATTITUDE), {});
  };
  // decode_cb left empty; node will supply decode handler by wrapping this descriptor
  regs.push_back(att);

  // RC (inbound telemetry of current RC channels)
  CommandDescriptor rc;
  rc.id = MSP_RC;
  rc.name = "MSP_RC";
  rc.poll_rate_hz = 5.0; // 5 Hz snapshot
  rc.build_request_cb = [=]() {
    return buildPacketRaw(static_cast<uint8_t>(MSP_RC), {});
  };
  regs.push_back(rc);

  // ANALOG (battery voltage, mAh, RSSI)
  CommandDescriptor analog;
  analog.id = MSP_ANALOG;
  analog.name = "MSP_ANALOG";
  analog.poll_rate_hz = 2.0; // 2 Hz
  analog.build_request_cb = [=]() {
    return buildPacketRaw(static_cast<uint8_t>(MSP_ANALOG), {});
  };
  regs.push_back(analog);
  
  // V2 Rangefinder sensor (example of MSP v2 16-bit command)
  CommandDescriptor rangefinder;
  rangefinder.id = MSP2_SENSOR_RANGEFINDER; // 0x1F01 (>255 requires v2)
  rangefinder.name = "MSP2_SENSOR_RANGEFINDER";
  rangefinder.poll_rate_hz = 5.0; // 5 Hz typical for rangefinder
  rangefinder.build_request_cb = [=]() {
    // Empty payload request; flags = 0
    return buildPacketV2(rangefinder.id, {}, 0);
  };
  rangefinder.requires_v2 = true;
  regs.push_back(rangefinder);

  // V2 Compass sensor
  CommandDescriptor compass;
  compass.id = MSP2_SENSOR_COMPASS; // 0x1F04
  compass.name = "MSP2_SENSOR_COMPASS";
  compass.poll_rate_hz = 5.0; // 5 Hz
  compass.build_request_cb = [=]() {
    return buildPacketV2(compass.id, {}, 0);
  };
  compass.requires_v2 = true;
  regs.push_back(compass);

  // V2 Barometer sensor
  CommandDescriptor baro;
  baro.id = MSP2_SENSOR_BAROMETER; // 0x1F05
  baro.name = "MSP2_SENSOR_BAROMETER";
  baro.poll_rate_hz = 5.0; // 5 Hz
  baro.build_request_cb = [=]() {
    return buildPacketV2(baro.id, {}, 0);
  };
  baro.requires_v2 = true;
  regs.push_back(baro);

  // INAV extended status (0x2000) - MSP2_INAV_STATUS
  CommandDescriptor inav_status;
  inav_status.id = 0x2000; // MSP2_INAV_STATUS (not in sensor header, manual constant)
  inav_status.name = "MSP2_INAV_STATUS";
  inav_status.poll_rate_hz = 2.0; // modest rate
  inav_status.build_request_cb = [=]() {
    return buildPacketV2(inav_status.id, {}, 0);
  };
  inav_status.requires_v2 = true;
  regs.push_back(inav_status);
  return regs;
}

} // namespace transformer_msp_bridge
