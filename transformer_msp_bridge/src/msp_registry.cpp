#include "transformer_msp_bridge/msp_registry.hpp"
#include "transformer_msp_bridge/msp_builders.hpp" // buildPacketRaw / buildPacketV2
#include "msp/msp_protocol.h" // external constants (v1 IDs)
#include "msp/msp_protocol_v2_sensor.h" // v2 sensor IDs

namespace transformer_msp_bridge {

std::vector<CommandDescriptor> build_default_registry() {
  std::vector<CommandDescriptor> regs;
  // ---------------- V1 Core Telemetry ----------------
  // RAW_IMU (acc, gyro, mag)
  {
    CommandDescriptor d;
    d.id = MSP_RAW_IMU;
    d.name = "MSP_RAW_IMU";
    d.poll_rate_hz = 50.0; // high rate for raw IMU
    d.build_request_cb = [=]() { return buildPacketRaw(static_cast<uint8_t>(d.id), {}); };
    regs.push_back(d);
  }
  // SERVO
  {
    CommandDescriptor d; d.id = MSP_SERVO; d.name = "MSP_SERVO"; d.poll_rate_hz = 10.0; d.build_request_cb = [=](){ return buildPacketRaw(static_cast<uint8_t>(MSP_SERVO), {}); }; regs.push_back(d);
  }
  // MOTOR
  {
    CommandDescriptor d; d.id = MSP_MOTOR; d.name = "MSP_MOTOR"; d.poll_rate_hz = 10.0; d.build_request_cb = [=](){ return buildPacketRaw(static_cast<uint8_t>(MSP_MOTOR), {}); }; regs.push_back(d);
  }
  // RC (inbound telemetry of current RC channels)
  {
    CommandDescriptor d; d.id = MSP_RC; d.name = "MSP_RC"; d.poll_rate_hz = 5.0; d.build_request_cb = [=](){ return buildPacketRaw(static_cast<uint8_t>(MSP_RC), {}); }; regs.push_back(d);
  }
  // RAW_GPS
  {
    CommandDescriptor d; d.id = MSP_RAW_GPS; d.name = "MSP_RAW_GPS"; d.poll_rate_hz = 5.0; d.build_request_cb = [=](){ return buildPacketRaw(static_cast<uint8_t>(MSP_RAW_GPS), {}); }; regs.push_back(d);
  }
  // COMP_GPS (home vector)
  {
    CommandDescriptor d; d.id = MSP_COMP_GPS; d.name = "MSP_COMP_GPS"; d.poll_rate_hz = 2.0; d.build_request_cb = [=](){ return buildPacketRaw(static_cast<uint8_t>(MSP_COMP_GPS), {}); }; regs.push_back(d);
  }
  // ATTITUDE (example) - request has no payload
  CommandDescriptor att;
  att.id = MSP_ATTITUDE;
  att.name = "MSP_ATTITUDE";
  att.poll_rate_hz = 10.0; // default; node can override via params later
  att.build_request_cb = [=]() {
    return buildPacketRaw(static_cast<uint8_t>(MSP_ATTITUDE), {});
  };
  regs.push_back(att);
  // ALTITUDE
  {
    CommandDescriptor d; d.id = MSP_ALTITUDE; d.name = "MSP_ALTITUDE"; d.poll_rate_hz = 5.0; d.build_request_cb = [=](){ return buildPacketRaw(static_cast<uint8_t>(MSP_ALTITUDE), {}); }; regs.push_back(d);
  }

  // ANALOG (battery voltage, mAh, RSSI)
  CommandDescriptor analog;
  analog.id = MSP_ANALOG;
  analog.name = "MSP_ANALOG";
  analog.poll_rate_hz = 2.0; // 2 Hz
  analog.build_request_cb = [=]() {
    return buildPacketRaw(static_cast<uint8_t>(MSP_ANALOG), {});
  };
  regs.push_back(analog);
  // RC_TUNING
  {
    CommandDescriptor d; d.id = MSP_RC_TUNING; d.name = "MSP_RC_TUNING"; d.poll_rate_hz = 0.2; d.build_request_cb = [=](){ return buildPacketRaw(static_cast<uint8_t>(MSP_RC_TUNING), {}); }; regs.push_back(d);
  }
  // BATTERY_STATE (extended)
  {
    CommandDescriptor d; d.id = MSP_BATTERY_STATE; d.name = "MSP_BATTERY_STATE"; d.poll_rate_hz = 1.0; d.build_request_cb = [=](){ return buildPacketRaw(static_cast<uint8_t>(MSP_BATTERY_STATE), {}); }; regs.push_back(d);
  }
  // RTC (time)
  {
    CommandDescriptor d; d.id = MSP_RTC; d.name = "MSP_RTC"; d.poll_rate_hz = 0.5; d.build_request_cb = [=](){ return buildPacketRaw(static_cast<uint8_t>(MSP_RTC), {}); }; regs.push_back(d);
  }
  // STATUS_EX (note: some firmwares expose MSP_STATUS, MSP_STATUS_EX may map differently; ensure header availability)
  {
    CommandDescriptor d; d.id = MSP_STATUS; d.name = "MSP_STATUS"; d.poll_rate_hz = 2.0; d.build_request_cb = [=](){ return buildPacketRaw(static_cast<uint8_t>(MSP_STATUS), {}); }; regs.push_back(d);
  }
  // SENSOR_STATUS (not explicitly defined; using MSP_SENSOR_CONFIG as proxy if needed)
  {
    CommandDescriptor d; d.id = MSP_SENSOR_CONFIG; d.name = "MSP_SENSOR_CONFIG"; d.poll_rate_hz = 2.0; d.build_request_cb = [=](){ return buildPacketRaw(static_cast<uint8_t>(MSP_SENSOR_CONFIG), {}); }; regs.push_back(d);
  }
  // GPSSTATISTICS (no direct macro in header at provided lines; keep numeric or define if available)
  {
    CommandDescriptor d; d.id = 166; d.name = "MSP_GPSSTATISTICS"; d.poll_rate_hz = 1.0; d.build_request_cb = [=](){ return buildPacketRaw(166, {}); }; regs.push_back(d);
  }
  
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

  // INAV Analog (battery flags, VBAT, cells)
  {
    CommandDescriptor d; d.id = MSP2_INAV_ANALOG; d.name = "MSP2_INAV_ANALOG"; d.poll_rate_hz = 2.0; d.requires_v2 = true; d.build_request_cb = [=](){ return buildPacketV2(MSP2_INAV_ANALOG, {}, 0); }; regs.push_back(d);
  }
  // INAV Battery Config
  {
    CommandDescriptor d; d.id = MSP2_INAV_BATTERY_CONFIG; d.name = "MSP2_INAV_BATTERY_CONFIG"; d.poll_rate_hz = 0.05; d.requires_v2 = true; d.build_request_cb = [=](){ return buildPacketV2(MSP2_INAV_BATTERY_CONFIG, {}, 0); }; regs.push_back(d);
  }
  // INAV Air Speed
  {
    CommandDescriptor d; d.id = MSP2_INAV_AIR_SPEED; d.name = "MSP2_INAV_AIR_SPEED"; d.poll_rate_hz = 5.0; d.requires_v2 = true; d.build_request_cb = [=](){ return buildPacketV2(MSP2_INAV_AIR_SPEED, {}, 0); }; regs.push_back(d);
  }
  // INAV Temperatures
  {
    CommandDescriptor d; d.id = MSP2_INAV_TEMPERATURES; d.name = "MSP2_INAV_TEMPERATURES"; d.poll_rate_hz = 1.0; d.requires_v2 = true; d.build_request_cb = [=](){ return buildPacketV2(MSP2_INAV_TEMPERATURES, {}, 0); }; regs.push_back(d);
  }
  // INAV ESC RPM
  {
    CommandDescriptor d; d.id = MSP2_INAV_ESC_RPM; d.name = "MSP2_INAV_ESC_RPM"; d.poll_rate_hz = 5.0; d.requires_v2 = true; d.build_request_cb = [=](){ return buildPacketV2(MSP2_INAV_ESC_RPM, {}, 0); }; regs.push_back(d);
  }

  // Common Setting (on-demand, not polled by default)
  {
    CommandDescriptor d; d.id = MSP2_COMMON_SETTING; d.name = "MSP2_COMMON_SETTING"; d.poll_rate_hz = 0.0; d.requires_v2 = true; d.build_request_cb = [=](){ return buildPacketV2(MSP2_COMMON_SETTING, {}, 0); }; regs.push_back(d);
  }
  // Common Set Setting (write)
  {
    CommandDescriptor d; d.id = MSP2_COMMON_SET_SETTING; d.name = "MSP2_COMMON_SET_SETTING"; d.poll_rate_hz = 0.0; d.requires_v2 = true; d.build_request_cb = [=](){ return buildPacketV2(MSP2_COMMON_SET_SETTING, {}, 0); }; regs.push_back(d);
  }
  return regs;
}

} // namespace transformer_msp_bridge
