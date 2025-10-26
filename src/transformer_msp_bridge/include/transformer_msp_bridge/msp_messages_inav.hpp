#pragma once
// Auto-generated compact MSP header (INAV MSPv1+v2).
// One macro call per message; hex-only IDs; no registry list.

#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <vector>

namespace msp {

enum class MspDir : uint8_t { In, Out, InOut, Unknown };

struct MspField {
  std::string_view name;
  std::string_view ctype;
  std::string_view size;
  std::string_view units;
  std::string_view description;
};

struct MspMsg {
  std::string_view name;
  uint32_t         id_hex;
  MspDir           dir;
  const MspField  *fields;
  std::size_t      field_count;
};

inline std::vector<const MspMsg *> &registry_storage() {
  static std::vector<const MspMsg *> storage;
  return storage;
}

struct RegistrySentinel {
  explicit RegistrySentinel(const MspMsg &msg) {
    registry_storage().push_back(&msg);
  }
};

inline const std::vector<const MspMsg *> &all_messages() {
  return registry_storage();
}

template <typename... Ts>
constexpr auto make_fields(Ts... elems) {
  return std::array<MspField, sizeof...(Ts)>{ { elems... } };
}

#define MSP_FIELD(n,t,s,u,d) ::msp::MspField{ (n), (t), (s), (u), (d) }

#define MSP_MESSAGE(NAME, HEXID, DIR, ...)                     \
  inline constexpr auto NAME##_FIELDS =                        \
    ::msp::make_fields(__VA_ARGS__);                         \
  inline constexpr ::msp::MspMsg NAME{                         \
    #NAME, (HEXID), (DIR), NAME##_FIELDS.data(),             \
    NAME##_FIELDS.size()};                                   \
  inline const ::msp::RegistrySentinel NAME##_REGISTRAR{NAME}

} // namespace msp

// ------------------- Definitions -------------------
MSP_MESSAGE(
  MSP_API_VERSION, 0x01, ::msp::MspDir::Out,
  MSP_FIELD("mspProtocolVersion","uint8_t","1","","MSP Protocol version (MSP_PROTOCOL_VERSION, typically 0)."),
  MSP_FIELD("apiVersionMajor","uint8_t","1","","INAV API Major version (API_VERSION_MAJOR)."),
  MSP_FIELD("apiVersionMinor","uint8_t","1","","INAV API Minor version (API_VERSION_MINOR).")
);



MSP_MESSAGE(
  MSP_FC_VARIANT, 0x02, ::msp::MspDir::Out,
  MSP_FIELD("fcVariantIdentifier","char[4]","4","","4-character identifier string (e.g., \"INAV\"). Defined by flightControllerIdentifier.")
);
MSP_MESSAGE(
  MSP_FC_VERSION, 0x03, ::msp::MspDir::Out,
  MSP_FIELD("fcVersionMajor","uint8_t","1","","Firmware Major version (FC_VERSION_MAJOR)."),
  MSP_FIELD("fcVersionMinor","uint8_t","1","","Firmware Minor version (FC_VERSION_MINOR)."),
  MSP_FIELD("fcVersionPatch","uint8_t","1","","Firmware Patch level (FC_VERSION_PATCH_LEVEL).")
);
MSP_MESSAGE(
  MSP_BOARD_INFO, 0x04, ::msp::MspDir::Out,
  MSP_FIELD("boardIdentifier","char[4]","4","","4-character UPPER CASE board identifier (TARGET_BOARD_IDENTIFIER)."),
  MSP_FIELD("hardwareRevision","uint16_t","2","","Hardware revision number. 0 if not detected (USE_HARDWARE_REVISION_DETECTION)."),
  MSP_FIELD("osdSupport","uint8_t","1","","OSD chip type: 0=None, 2=Onboard (USE_OSD). INAV does not support slave OSD (1)."),
  MSP_FIELD("commCapabilities","uint8_t","1","","Communication capabilities bitmask: Bit 0=VCP support (USE_VCP), Bit 1=SoftSerial support (USE_SOFTSERIAL1/2)."),
  MSP_FIELD("targetNameLength","uint8_t","1","","Length of the target name string that follows."),
  MSP_FIELD("targetName","char[]","Variable","","Target name string (e.g., \"MATEKF405\"). Length given by previous field.")
);
MSP_MESSAGE(
  MSP_BUILD_INFO, 0x05, ::msp::MspDir::Out,
  MSP_FIELD("buildDate","char[11]","11","","Build date string (e.g., \"Dec 31 2023\"). BUILD_DATE_LENGTH."),
  MSP_FIELD("buildTime","char[8]","8","","Build time string (e.g., \"23:59:59\"). BUILD_TIME_LENGTH."),
  MSP_FIELD("gitRevision","char[7]","7","","Short Git revision string. GIT_SHORT_REVISION_LENGTH.")
);
MSP_MESSAGE(
  MSP_INAV_PID, 0x06, ::msp::MspDir::Out,
  MSP_FIELD("legacyAsyncProcessing","uint8_t","1","-","Legacy, unused. Always 0."),
  MSP_FIELD("legacyAsyncValue1","uint16_t","2","-","Legacy, unused. Always 0."),
  MSP_FIELD("legacyAsyncValue2","uint16_t","2","-","Legacy, unused. Always 0."),
  MSP_FIELD("headingHoldRateLimit","uint8_t","1","deg/s","Max rate for heading hold P term (pidProfile()->heading_hold_rate_limit)."),
  MSP_FIELD("headingHoldLpfFreq","uint8_t","1","Hz","Fixed LPF frequency for heading hold error (HEADING_HOLD_ERROR_LPF_FREQ)."),
  MSP_FIELD("legacyYawJumpLimit","uint16_t","2","-","Legacy, unused. Always 0."),
  MSP_FIELD("legacyGyroLpf","uint8_t","1","Enum","Fixed value GYRO_LPF_256HZ."),
  MSP_FIELD("accLpfHz","uint8_t","1","Hz","Accelerometer LPF frequency (accelerometerConfig()->acc_lpf_hz)."),
  MSP_FIELD("reserved1","uint8_t","1","-","Reserved. Always 0."),
  MSP_FIELD("reserved2","uint8_t","1","-","Reserved. Always 0."),
  MSP_FIELD("reserved3","uint8_t","1","-","Reserved. Always 0."),
  MSP_FIELD("reserved4","uint8_t","1","-","Reserved. Always 0.")
);
MSP_MESSAGE(
  MSP_SET_INAV_PID, 0x07, ::msp::MspDir::In,
  MSP_FIELD("legacyAsyncProcessing","uint8_t","1","-","Legacy, ignored."),
  MSP_FIELD("legacyAsyncValue1","uint16_t","2","-","Legacy, ignored."),
  MSP_FIELD("legacyAsyncValue2","uint16_t","2","-","Legacy, ignored."),
  MSP_FIELD("headingHoldRateLimit","uint8_t","1","deg/s","Sets pidProfileMutable()->heading_hold_rate_limit."),
  MSP_FIELD("headingHoldLpfFreq","uint8_t","1","Hz","Ignored (fixed value HEADING_HOLD_ERROR_LPF_FREQ used)."),
  MSP_FIELD("legacyYawJumpLimit","uint16_t","2","-","Legacy, ignored."),
  MSP_FIELD("legacyGyroLpf","uint8_t","1","Enum","Ignored (was gyro LPF)."),
  MSP_FIELD("accLpfHz","uint8_t","1","Hz","Sets accelerometerConfigMutable()->acc_lpf_hz."),
  MSP_FIELD("reserved1","uint8_t","1","-","Ignored."),
  MSP_FIELD("reserved2","uint8_t","1","-","Ignored."),
  MSP_FIELD("reserved3","uint8_t","1","-","Ignored."),
  MSP_FIELD("reserved4","uint8_t","1","-","Ignored.")
);
MSP_MESSAGE(
  MSP_NAME, 0x0a, ::msp::MspDir::Out,
  MSP_FIELD("craftName","char[]","Variable","","The craft name string (systemConfig()->craftName). Null termination is not explicitly sent, the length is determined by the payload size.")
);
MSP_MESSAGE(
  MSP_SET_NAME, 0x0b, ::msp::MspDir::In,
  MSP_FIELD("craftName","char[]","1 to MAX_NAME_LENGTH","","The new craft name string. Automatically null-terminated by the FC.")
);
MSP_MESSAGE(
  MSP_NAV_POSHOLD, 0x0c, ::msp::MspDir::Out,
  MSP_FIELD("userControlMode","uint8_t","1","Enum","Navigation user control mode (navConfig()->general.flags.user_control_mode)."),
  MSP_FIELD("maxAutoSpeed","uint16_t","2","cm/s","Max speed in autonomous modes (navConfig()->general.max_auto_speed)."),
  MSP_FIELD("maxAutoClimbRate","uint16_t","2","cm/s","Max climb rate in autonomous modes (uses fw.max_auto_climb_rate or mc.max_auto_climb_rate based on platform)."),
  MSP_FIELD("maxManualSpeed","uint16_t","2","cm/s","Max speed in manual modes with GPS aiding (navConfig()->general.max_manual_speed)."),
  MSP_FIELD("maxManualClimbRate","uint16_t","2","cm/s","Max climb rate in manual modes with GPS aiding (uses fw.max_manual_climb_rate or mc.max_manual_climb_rate)."),
  MSP_FIELD("mcMaxBankAngle","uint8_t","1","degrees","Max bank angle for multirotor position hold (navConfig()->mc.max_bank_angle)."),
  MSP_FIELD("mcAltHoldThrottleType","uint8_t","1","Enum","Altitude Hold throttle control type (navConfig()->mc.althold_throttle_type)."),
  MSP_FIELD("mcHoverThrottle","uint16_t","2","PWM","Multirotor hover throttle (currentBatteryProfile->nav.mc.hover_throttle).")
);
MSP_MESSAGE(
  MSP_SET_NAV_POSHOLD, 0x0d, ::msp::MspDir::In,
  MSP_FIELD("userControlMode","uint8_t","1","Enum","Sets navConfigMutable()->general.flags.user_control_mode."),
  MSP_FIELD("maxAutoSpeed","uint16_t","2","cm/s","Sets navConfigMutable()->general.max_auto_speed."),
  MSP_FIELD("maxAutoClimbRate","uint16_t","2","cm/s","Sets fw.max_auto_climb_rate or mc.max_auto_climb_rate based on current platform type."),
  MSP_FIELD("maxManualSpeed","uint16_t","2","cm/s","Sets navConfigMutable()->general.max_manual_speed."),
  MSP_FIELD("maxManualClimbRate","uint16_t","2","cm/s","Sets fw.max_manual_climb_rate or mc.max_manual_climb_rate."),
  MSP_FIELD("mcMaxBankAngle","uint8_t","1","degrees","Sets navConfigMutable()->mc.max_bank_angle."),
  MSP_FIELD("mcAltHoldThrottleType","uint8_t","1","Enum","Sets navConfigMutable()->mc.althold_throttle_type."),
  MSP_FIELD("mcHoverThrottle","uint16_t","2","PWM","Sets currentBatteryProfileMutable->nav.mc.hover_throttle.")
);
MSP_MESSAGE(
  MSP_CALIBRATION_DATA, 0x0e, ::msp::MspDir::Out,
  MSP_FIELD("accCalibAxisFlags","uint8_t","1","Bitmask","Flags indicating which axes of the accelerometer have been calibrated (accGetCalibrationAxisFlags())."),
  MSP_FIELD("accZeroX","uint16_t","2","Raw ADC","Accelerometer zero offset for X-axis (accelerometerConfig()->accZero.raw[X])."),
  MSP_FIELD("accZeroY","uint16_t","2","Raw ADC","Accelerometer zero offset for Y-axis (accelerometerConfig()->accZero.raw[Y])."),
  MSP_FIELD("accZeroZ","uint16_t","2","Raw ADC","Accelerometer zero offset for Z-axis (accelerometerConfig()->accZero.raw[Z])."),
  MSP_FIELD("accGainX","uint16_t","2","Raw ADC","Accelerometer gain/scale for X-axis (accelerometerConfig()->accGain.raw[X])."),
  MSP_FIELD("accGainY","uint16_t","2","Raw ADC","Accelerometer gain/scale for Y-axis (accelerometerConfig()->accGain.raw[Y])."),
  MSP_FIELD("accGainZ","uint16_t","2","Raw ADC","Accelerometer gain/scale for Z-axis (accelerometerConfig()->accGain.raw[Z])."),
  MSP_FIELD("magZeroX","uint16_t","2","Raw ADC","Magnetometer zero offset for X-axis (compassConfig()->magZero.raw[X]). 0 if USE_MAG disabled."),
  MSP_FIELD("magZeroY","uint16_t","2","Raw ADC","Magnetometer zero offset for Y-axis (compassConfig()->magZero.raw[Y]). 0 if USE_MAG disabled."),
  MSP_FIELD("magZeroZ","uint16_t","2","Raw ADC","Magnetometer zero offset for Z-axis (compassConfig()->magZero.raw[Z]). 0 if USE_MAG disabled."),
  MSP_FIELD("opflowScale","uint16_t","2","Scale 256","Optical flow scale factor (opticalFlowConfig()->opflow_scale 256). 0 if USE_OPFLOW disabled."),
  MSP_FIELD("magGainX","uint16_t","2","Raw ADC","Magnetometer gain/scale for X-axis (compassConfig()->magGain[X]). 0 if USE_MAG disabled."),
  MSP_FIELD("magGainY","uint16_t","2","Raw ADC","Magnetometer gain/scale for Y-axis (compassConfig()->magGain[Y]). 0 if USE_MAG disabled."),
  MSP_FIELD("magGainZ","uint16_t","2","Raw ADC","Magnetometer gain/scale for Z-axis (compassConfig()->magGain[Z]). 0 if USE_MAG disabled.")
);
MSP_MESSAGE(
  MSP_SET_CALIBRATION_DATA, 0x0f, ::msp::MspDir::In,
  MSP_FIELD("accZeroX","uint16_t","2","Raw ADC","Sets accelerometerConfigMutable()->accZero.raw[X]."),
  MSP_FIELD("accZeroY","uint16_t","2","Raw ADC","Sets accelerometerConfigMutable()->accZero.raw[Y]."),
  MSP_FIELD("accZeroZ","uint16_t","2","Raw ADC","Sets accelerometerConfigMutable()->accZero.raw[Z]."),
  MSP_FIELD("accGainX","uint16_t","2","Raw ADC","Sets accelerometerConfigMutable()->accGain.raw[X]."),
  MSP_FIELD("accGainY","uint16_t","2","Raw ADC","Sets accelerometerConfigMutable()->accGain.raw[Y]."),
  MSP_FIELD("accGainZ","uint16_t","2","Raw ADC","Sets accelerometerConfigMutable()->accGain.raw[Z]."),
  MSP_FIELD("magZeroX","uint16_t","2","Raw ADC","Sets compassConfigMutable()->magZero.raw[X] (if USE_MAG)."),
  MSP_FIELD("magZeroY","uint16_t","2","Raw ADC","Sets compassConfigMutable()->magZero.raw[Y] (if USE_MAG)."),
  MSP_FIELD("magZeroZ","uint16_t","2","Raw ADC","Sets compassConfigMutable()->magZero.raw[Z] (if USE_MAG)."),
  MSP_FIELD("opflowScale","uint16_t","2","Scale 256","Sets opticalFlowConfigMutable()->opflow_scale = value / 256.0f (if USE_OPFLOW)."),
  MSP_FIELD("magGainX","uint16_t","2","Raw ADC","Sets compassConfigMutable()->magGain[X] (if USE_MAG)."),
  MSP_FIELD("magGainY","uint16_t","2","Raw ADC","Sets compassConfigMutable()->magGain[Y] (if USE_MAG)."),
  MSP_FIELD("magGainZ","uint16_t","2","Raw ADC","Sets compassConfigMutable()->magGain[Z] (if USE_MAG).")
);
MSP_MESSAGE(
  MSP_POSITION_ESTIMATION_CONFIG, 0x10, ::msp::MspDir::Out,
  MSP_FIELD("weightZBaroP","uint16_t","2","Weight 100","Barometer Z position fusion weight (positionEstimationConfig()->w_z_baro_p 100)."),
  MSP_FIELD("weightZGPSP","uint16_t","2","Weight 100","GPS Z position fusion weight (positionEstimationConfig()->w_z_gps_p 100)."),
  MSP_FIELD("weightZGPSV","uint16_t","2","Weight 100","GPS Z velocity fusion weight (positionEstimationConfig()->w_z_gps_v 100)."),
  MSP_FIELD("weightXYGPSP","uint16_t","2","Weight 100","GPS XY position fusion weight (positionEstimationConfig()->w_xy_gps_p 100)."),
  MSP_FIELD("weightXYGPSV","uint16_t","2","Weight 100","GPS XY velocity fusion weight (positionEstimationConfig()->w_xy_gps_v 100)."),
  MSP_FIELD("minSats","uint8_t","1","Count","Minimum satellites required for GPS use (gpsConfigMutable()->gpsMinSats)."),
  MSP_FIELD("useGPSVelNED","uint8_t","1","Boolean","Legacy flag, always 1 (GPS velocity is always used if available).")
);
MSP_MESSAGE(
  MSP_SET_POSITION_ESTIMATION_CONFIG, 0x11, ::msp::MspDir::In,
  MSP_FIELD("weightZBaroP","uint16_t","2","Weight 100","Sets positionEstimationConfigMutable()->w_z_baro_p = value / 100.0f (constrained 0.0-10.0)."),
  MSP_FIELD("weightZGPSP","uint16_t","2","Weight 100","Sets positionEstimationConfigMutable()->w_z_gps_p = value / 100.0f (constrained 0.0-10.0)."),
  MSP_FIELD("weightZGPSV","uint16_t","2","Weight 100","Sets positionEstimationConfigMutable()->w_z_gps_v = value / 100.0f (constrained 0.0-10.0)."),
  MSP_FIELD("weightXYGPSP","uint16_t","2","Weight 100","Sets positionEstimationConfigMutable()->w_xy_gps_p = value / 100.0f (constrained 0.0-10.0)."),
  MSP_FIELD("weightXYGPSV","uint16_t","2","Weight 100","Sets positionEstimationConfigMutable()->w_xy_gps_v = value / 100.0f (constrained 0.0-10.0)."),
  MSP_FIELD("minSats","uint8_t","1","Count","Sets gpsConfigMutable()->gpsMinSats (constrained 5-10)."),
  MSP_FIELD("useGPSVelNED","uint8_t","1","Boolean","Legacy flag, ignored.")
);
MSP_MESSAGE(
  MSP_WP_MISSION_LOAD, 0x12, ::msp::MspDir::In,
  MSP_FIELD("missionID","uint8_t","1","","Reserved for future use, currently ignored.")
);
MSP_MESSAGE(
  MSP_WP_MISSION_SAVE, 0x13, ::msp::MspDir::In,
  MSP_FIELD("missionID","uint8_t","1","","Reserved for future use, currently ignored.")
);
MSP_MESSAGE(
  MSP_WP_GETINFO, 0x14, ::msp::MspDir::Out,
  MSP_FIELD("wpCapabilities","uint8_t","1","","Reserved for future waypoint capabilities flags. Currently always 0."),
  MSP_FIELD("maxWaypoints","uint8_t","1","","Maximum number of waypoints supported (NAV_MAX_WAYPOINTS)."),
  MSP_FIELD("missionValid","uint8_t","1","","Boolean flag indicating if the current mission in RAM is valid (isWaypointListValid())."),
  MSP_FIELD("waypointCount","uint8_t","1","","Number of waypoints currently defined in the mission (getWaypointCount()).")
);
MSP_MESSAGE(
  MSP_RTH_AND_LAND_CONFIG, 0x15, ::msp::MspDir::Out,
  MSP_FIELD("minRthDistance","uint16_t","2","meters","Minimum distance from home required for RTH to engage (navConfig()->general.min_rth_distance)."),
  MSP_FIELD("rthClimbFirst","uint8_t","1","Boolean","Flag: Climb to RTH altitude before returning (navConfig()->general.flags.rth_climb_first)."),
  MSP_FIELD("rthClimbIgnoreEmerg","uint8_t","1","Boolean","Flag: Climb even in emergency RTH (navConfig()->general.flags.rth_climb_ignore_emerg)."),
  MSP_FIELD("rthTailFirst","uint8_t","1","Boolean","Flag: Multirotor returns tail-first (navConfig()->general.flags.rth_tail_first)."),
  MSP_FIELD("rthAllowLanding","uint8_t","1","Boolean","Flag: Allow automatic landing after RTH (navConfig()->general.flags.rth_allow_landing)."),
  MSP_FIELD("rthAltControlMode","uint8_t","1","Enum","RTH altitude control mode (navConfig()->general.flags.rth_alt_control_mode)."),
  MSP_FIELD("rthAbortThreshold","uint16_t","2","cm/s","Stick input threshold to abort RTH (navConfig()->general.rth_abort_threshold)."),
  MSP_FIELD("rthAltitude","uint16_t","2","meters","Target RTH altitude (navConfig()->general.rth_altitude)."),
  MSP_FIELD("landMinAltVspd","uint16_t","2","cm/s","Landing vertical speed at minimum slowdown altitude (navConfig()->general.land_minalt_vspd)."),
  MSP_FIELD("landMaxAltVspd","uint16_t","2","cm/s","Landing vertical speed at maximum slowdown altitude (navConfig()->general.land_maxalt_vspd)."),
  MSP_FIELD("landSlowdownMinAlt","uint16_t","2","meters","Altitude below which landMinAltVspd applies (navConfig()->general.land_slowdown_minalt)."),
  MSP_FIELD("landSlowdownMaxAlt","uint16_t","2","meters","Altitude above which landMaxAltVspd applies (navConfig()->general.land_slowdown_maxalt)."),
  MSP_FIELD("emergDescentRate","uint16_t","2","cm/s","Vertical speed during emergency landing descent (navConfig()->general.emerg_descent_rate).")
);
MSP_MESSAGE(
  MSP_SET_RTH_AND_LAND_CONFIG, 0x16, ::msp::MspDir::In,
  MSP_FIELD("minRthDistance","uint16_t","2","meters","Sets navConfigMutable()->general.min_rth_distance."),
  MSP_FIELD("rthClimbFirst","uint8_t","1","Boolean","Sets navConfigMutable()->general.flags.rth_climb_first."),
  MSP_FIELD("rthClimbIgnoreEmerg","uint8_t","1","Boolean","Sets navConfigMutable()->general.flags.rth_climb_ignore_emerg."),
  MSP_FIELD("rthTailFirst","uint8_t","1","Boolean","Sets navConfigMutable()->general.flags.rth_tail_first."),
  MSP_FIELD("rthAllowLanding","uint8_t","1","Boolean","Sets navConfigMutable()->general.flags.rth_allow_landing."),
  MSP_FIELD("rthAltControlMode","uint8_t","1","Enum","Sets navConfigMutable()->general.flags.rth_alt_control_mode."),
  MSP_FIELD("rthAbortThreshold","uint16_t","2","cm/s","Sets navConfigMutable()->general.rth_abort_threshold."),
  MSP_FIELD("rthAltitude","uint16_t","2","meters","Sets navConfigMutable()->general.rth_altitude."),
  MSP_FIELD("landMinAltVspd","uint16_t","2","cm/s","Sets navConfigMutable()->general.land_minalt_vspd."),
  MSP_FIELD("landMaxAltVspd","uint16_t","2","cm/s","Sets navConfigMutable()->general.land_maxalt_vspd."),
  MSP_FIELD("landSlowdownMinAlt","uint16_t","2","meters","Sets navConfigMutable()->general.land_slowdown_minalt."),
  MSP_FIELD("landSlowdownMaxAlt","uint16_t","2","meters","Sets navConfigMutable()->general.land_slowdown_maxalt."),
  MSP_FIELD("emergDescentRate","uint16_t","2","cm/s","Sets navConfigMutable()->general.emerg_descent_rate.")
);
MSP_MESSAGE(
  MSP_FW_CONFIG, 0x17, ::msp::MspDir::Out,
  MSP_FIELD("cruiseThrottle","uint16_t","2","PWM","Cruise throttle level (currentBatteryProfile->nav.fw.cruise_throttle)."),
  MSP_FIELD("minThrottle","uint16_t","2","PWM","Minimum throttle during autonomous flight (currentBatteryProfile->nav.fw.min_throttle)."),
  MSP_FIELD("maxThrottle","uint16_t","2","PWM","Maximum throttle during autonomous flight (currentBatteryProfile->nav.fw.max_throttle)."),
  MSP_FIELD("maxBankAngle","uint8_t","1","degrees","Maximum bank angle allowed (navConfig()->fw.max_bank_angle)."),
  MSP_FIELD("maxClimbAngle","uint8_t","1","degrees","Maximum pitch angle during climb (navConfig()->fw.max_climb_angle)."),
  MSP_FIELD("maxDiveAngle","uint8_t","1","degrees","Maximum negative pitch angle during descent (navConfig()->fw.max_dive_angle)."),
  MSP_FIELD("pitchToThrottle","uint8_t","1","Ratio (%)","Pitch-to-throttle feed-forward ratio (currentBatteryProfile->nav.fw.pitch_to_throttle)."),
  MSP_FIELD("loiterRadius","uint16_t","2","meters","Default loiter radius (navConfig()->fw.loiter_radius).")
);
MSP_MESSAGE(
  MSP_SET_FW_CONFIG, 0x18, ::msp::MspDir::In,
  MSP_FIELD("cruiseThrottle","uint16_t","2","PWM","Sets currentBatteryProfileMutable->nav.fw.cruise_throttle."),
  MSP_FIELD("minThrottle","uint16_t","2","PWM","Sets currentBatteryProfileMutable->nav.fw.min_throttle."),
  MSP_FIELD("maxThrottle","uint16_t","2","PWM","Sets currentBatteryProfileMutable->nav.fw.max_throttle."),
  MSP_FIELD("maxBankAngle","uint8_t","1","degrees","Sets navConfigMutable()->fw.max_bank_angle."),
  MSP_FIELD("maxClimbAngle","uint8_t","1","degrees","Sets navConfigMutable()->fw.max_climb_angle."),
  MSP_FIELD("maxDiveAngle","uint8_t","1","degrees","Sets navConfigMutable()->fw.max_dive_angle."),
  MSP_FIELD("pitchToThrottle","uint8_t","1","Ratio (%)","Sets currentBatteryProfileMutable->nav.fw.pitch_to_throttle."),
  MSP_FIELD("loiterRadius","uint16_t","2","meters","Sets navConfigMutable()->fw.loiter_radius.")
);
MSP_MESSAGE(
  MSP_MODE_RANGES, 0x22, ::msp::MspDir::Out,
  MSP_FIELD("modePermanentId","uint8_t","1","ID","Permanent ID of the flight mode (maps to boxId via findBoxByActiveBoxId). 0 if entry unused."),
  MSP_FIELD("auxChannelIndex","uint8_t","1","Index","0-based index of the AUX channel used for activation."),
  MSP_FIELD("rangeStartStep","uint8_t","1","0-20","Start step (corresponding to channel value range 900-2100 in steps of 50/25, depends on steps calculation)."),
  MSP_FIELD("rangeEndStep","uint8_t","1","0-20","End step for the activation range.")
);
MSP_MESSAGE(
  MSP_SET_MODE_RANGE, 0x23, ::msp::MspDir::In,
  MSP_FIELD("rangeIndex","uint8_t","1","Index","Index of the mode range to set (0 to MAX_MODE_ACTIVATION_CONDITION_COUNT - 1)."),
  MSP_FIELD("modePermanentId","uint8_t","1","ID","Permanent ID of the flight mode to assign."),
  MSP_FIELD("auxChannelIndex","uint8_t","1","Index","0-based index of the AUX channel."),
  MSP_FIELD("rangeStartStep","uint8_t","1","0-20","Start step for activation."),
  MSP_FIELD("rangeEndStep","uint8_t","1","0-20","End step for activation.")
);
MSP_MESSAGE(
  MSP_FEATURE, 0x24, ::msp::MspDir::Out,
  MSP_FIELD("featureMask","uint32_t","4","","Bitmask of active features (see featureMask()).")
);
MSP_MESSAGE(
  MSP_SET_FEATURE, 0x25, ::msp::MspDir::In,
  MSP_FIELD("featureMask","uint32_t","4","","Bitmask of features to enable.")
);
MSP_MESSAGE(
  MSP_BOARD_ALIGNMENT, 0x26, ::msp::MspDir::Out,
  MSP_FIELD("rollAlign","uint16_t","2","deci-degrees","Board alignment roll angle (boardAlignment()->rollDeciDegrees)."),
  MSP_FIELD("pitchAlign","uint16_t","2","deci-degrees","Board alignment pitch angle (boardAlignment()->pitchDeciDegrees)."),
  MSP_FIELD("yawAlign","uint16_t","2","deci-degrees","Board alignment yaw angle (boardAlignment()->yawDeciDegrees).")
);
MSP_MESSAGE(
  MSP_SET_BOARD_ALIGNMENT, 0x27, ::msp::MspDir::In,
  MSP_FIELD("rollAlign","uint16_t","2","deci-degrees","Sets boardAlignmentMutable()->rollDeciDegrees."),
  MSP_FIELD("pitchAlign","uint16_t","2","deci-degrees","Sets boardAlignmentMutable()->pitchDeciDegrees."),
  MSP_FIELD("yawAlign","uint16_t","2","deci-degrees","Sets boardAlignmentMutable()->yawDeciDegrees.")
);
MSP_MESSAGE(
  MSP_CURRENT_METER_CONFIG, 0x28, ::msp::MspDir::Out,
  MSP_FIELD("scale","uint16_t","2","mV/10A or similar","Current sensor scale factor (batteryMetersConfig()->current.scale). Units depend on sensor type."),
  MSP_FIELD("offset","uint16_t","2","mV","Current sensor offset (batteryMetersConfig()->current.offset)."),
  MSP_FIELD("type","uint8_t","1","Enum","Type of current sensor hardware (batteryMetersConfig()->current.type)."),
  MSP_FIELD("capacity","uint16_t","2","mAh (legacy)","Battery capacity (constrained 0-65535) (currentBatteryProfile->capacity.value). Note: This is legacy, use MSP2_INAV_BATTERY_CONFIG for full 32-bit capacity.")
);
MSP_MESSAGE(
  MSP_SET_CURRENT_METER_CONFIG, 0x29, ::msp::MspDir::In,
  MSP_FIELD("scale","uint16_t","2","mV/10A or similar","Sets batteryMetersConfigMutable()->current.scale."),
  MSP_FIELD("offset","uint16_t","2","mV","Sets batteryMetersConfigMutable()->current.offset."),
  MSP_FIELD("type","uint8_t","1","Enum","Sets batteryMetersConfigMutable()->current.type."),
  MSP_FIELD("capacity","uint16_t","2","mAh (legacy)","Sets currentBatteryProfileMutable->capacity.value (truncated to 16 bits).")
);
MSP_MESSAGE(
  MSP_MIXER, 0x2a, ::msp::MspDir::Out,
  MSP_FIELD("mixerMode","uint8_t","1","","Always 3 (QuadX) in INAV for compatibility.")
);
MSP_MESSAGE(
  MSP_SET_MIXER, 0x2b, ::msp::MspDir::In,
  MSP_FIELD("mixerMode","uint8_t","1","","Mixer mode to set (ignored by INAV).")
);
MSP_MESSAGE(
  MSP_RX_CONFIG, 0x2c, ::msp::MspDir::Out,
  MSP_FIELD("serialRxProvider","uint8_t","1","Enum","Serial RX provider type (rxConfig()->serialrx_provider)."),
  MSP_FIELD("maxCheck","uint16_t","2","PWM","Upper channel value threshold for stick commands (rxConfig()->maxcheck)."),
  MSP_FIELD("midRc","uint16_t","2","PWM","Center channel value (PWM_RANGE_MIDDLE, typically 1500)."),
  MSP_FIELD("minCheck","uint16_t","2","PWM","Lower channel value threshold for stick commands (rxConfig()->mincheck)."),
  MSP_FIELD("spektrumSatBind","uint8_t","1","Count/Flag","Spektrum bind pulses (rxConfig()->spektrum_sat_bind). 0 if USE_SPEKTRUM_BIND disabled."),
  MSP_FIELD("rxMinUsec","uint16_t","2","µs","Minimum expected pulse width (rxConfig()->rx_min_usec)."),
  MSP_FIELD("rxMaxUsec","uint16_t","2","µs","Maximum expected pulse width (rxConfig()->rx_max_usec)."),
  MSP_FIELD("bfCompatRcInterpolation","uint8_t","1","-","BF compatibility. Always 0."),
  MSP_FIELD("bfCompatRcInterpolationInt","uint8_t","1","-","BF compatibility. Always 0."),
  MSP_FIELD("bfCompatAirModeThreshold","uint16_t","2","-","BF compatibility. Always 0."),
  MSP_FIELD("reserved1","uint8_t","1","-","Reserved/Padding. Always 0."),
  MSP_FIELD("reserved2","uint32_t","4","-","Reserved/Padding. Always 0."),
  MSP_FIELD("reserved3","uint8_t","1","-","Reserved/Padding. Always 0."),
  MSP_FIELD("bfCompatFpvCamAngle","uint8_t","1","-","BF compatibility. Always 0."),
  MSP_FIELD("receiverType","uint8_t","1","Enum","Receiver type (Parallel PWM, PPM, Serial) (rxConfig()->receiverType).")
);
MSP_MESSAGE(
  MSP_SET_RX_CONFIG, 0x2d, ::msp::MspDir::In,
  MSP_FIELD("serialRxProvider","uint8_t","1","Enum","Sets rxConfigMutable()->serialrx_provider."),
  MSP_FIELD("maxCheck","uint16_t","2","PWM","Sets rxConfigMutable()->maxcheck."),
  MSP_FIELD("midRc","uint16_t","2","PWM","Ignored (PWM_RANGE_MIDDLE is used)."),
  MSP_FIELD("minCheck","uint16_t","2","PWM","Sets rxConfigMutable()->mincheck."),
  MSP_FIELD("spektrumSatBind","uint8_t","1","Count/Flag","Sets rxConfigMutable()->spektrum_sat_bind (if USE_SPEKTRUM_BIND)."),
  MSP_FIELD("rxMinUsec","uint16_t","2","µs","Sets rxConfigMutable()->rx_min_usec."),
  MSP_FIELD("rxMaxUsec","uint16_t","2","µs","Sets rxConfigMutable()->rx_max_usec."),
  MSP_FIELD("bfCompatRcInterpolation","uint8_t","1","-","Ignored."),
  MSP_FIELD("bfCompatRcInterpolationInt","uint8_t","1","-","Ignored."),
  MSP_FIELD("bfCompatAirModeThreshold","uint16_t","2","-","Ignored."),
  MSP_FIELD("reserved1","uint8_t","1","-","Ignored."),
  MSP_FIELD("reserved2","uint32_t","4","-","Ignored."),
  MSP_FIELD("reserved3","uint8_t","1","-","Ignored."),
  MSP_FIELD("bfCompatFpvCamAngle","uint8_t","1","-","Ignored."),
  MSP_FIELD("receiverType","uint8_t","1","Enum","Sets rxConfigMutable()->receiverType.")
);
MSP_MESSAGE(
  MSP_LED_COLORS, 0x2e, ::msp::MspDir::Out,
  MSP_FIELD("hue","uint16_t","2","","Hue value (0-359)."),
  MSP_FIELD("saturation","uint8_t","1","","Saturation value (0-255)."),
  MSP_FIELD("value","uint8_t","1","","Value/Brightness (0-255).")
);
MSP_MESSAGE(
  MSP_SET_LED_COLORS, 0x2f, ::msp::MspDir::In,
  MSP_FIELD("hue","uint16_t","2","","Hue value (0-359)."),
  MSP_FIELD("saturation","uint8_t","1","","Saturation value (0-255)."),
  MSP_FIELD("value","uint8_t","1","","Value/Brightness (0-255).")
);
MSP_MESSAGE(
  MSP_LED_STRIP_CONFIG, 0x30, ::msp::MspDir::Out,
  MSP_FIELD("legacyLedConfig","uint32_t","4","","Packed LED configuration (position, function, overlay, color, direction, params). See C code for bit packing details.")
);
MSP_MESSAGE(
  MSP_SET_LED_STRIP_CONFIG, 0x31, ::msp::MspDir::In,
  MSP_FIELD("ledIndex","uint8_t","1","","Index of the LED to configure (0 to LED_MAX_STRIP_LENGTH - 1)."),
  MSP_FIELD("legacyLedConfig","uint32_t","4","","Packed LED configuration to set.")
);
MSP_MESSAGE(
  MSP_RSSI_CONFIG, 0x32, ::msp::MspDir::Out,
  MSP_FIELD("rssiChannel","uint8_t","1","","AUX channel index (1-based) used for RSSI, or 0 if disabled (rxConfig()->rssi_channel).")
);
MSP_MESSAGE(
  MSP_SET_RSSI_CONFIG, 0x33, ::msp::MspDir::In,
  MSP_FIELD("rssiChannel","uint8_t","1","","AUX channel index (1-based) to use for RSSI, or 0 to disable.")
);
MSP_MESSAGE(
  MSP_ADJUSTMENT_RANGES, 0x34, ::msp::MspDir::Out,
  MSP_FIELD("adjustmentIndex","uint8_t","1","","Index of the adjustment slot (0 to MAX_SIMULTANEOUS_ADJUSTMENT_COUNT - 1)."),
  MSP_FIELD("auxChannelIndex","uint8_t","1","","0-based index of the AUX channel controlling the adjustment value."),
  MSP_FIELD("rangeStartStep","uint8_t","1","","Start step (0-20) of the control channel range."),
  MSP_FIELD("rangeEndStep","uint8_t","1","","End step (0-20) of the control channel range."),
  MSP_FIELD("adjustmentFunction","uint8_t","1","","Function/parameter being adjusted (e.g., PID gain, rate). See rcAdjustments.h enum."),
  MSP_FIELD("auxSwitchChannelIndex","uint8_t","1","","0-based index of the AUX channel acting as an enable switch (or 0 if always enabled).")
);
MSP_MESSAGE(
  MSP_SET_ADJUSTMENT_RANGE, 0x35, ::msp::MspDir::In,
  MSP_FIELD("rangeIndex","uint8_t","1","","Index of the adjustment range to set (0 to MAX_ADJUSTMENT_RANGE_COUNT - 1)."),
  MSP_FIELD("adjustmentIndex","uint8_t","1","","Adjustment slot index (0 to MAX_SIMULTANEOUS_ADJUSTMENT_COUNT - 1)."),
  MSP_FIELD("auxChannelIndex","uint8_t","1","","0-based index of the control AUX channel."),
  MSP_FIELD("rangeStartStep","uint8_t","1","","Start step (0-20)."),
  MSP_FIELD("rangeEndStep","uint8_t","1","","End step (0-20)."),
  MSP_FIELD("adjustmentFunction","uint8_t","1","","Function/parameter being adjusted."),
  MSP_FIELD("auxSwitchChannelIndex","uint8_t","1","","0-based index of the enable switch AUX channel (or 0).")
);
MSP_MESSAGE(
  MSP_VOLTAGE_METER_CONFIG, 0x38, ::msp::MspDir::Out,
  MSP_FIELD("vbatScale","uint8_t","1","Scale / 10","Voltage sensor scale factor / 10 (batteryMetersConfig()->voltage.scale / 10). 0 if USE_ADC disabled."),
  MSP_FIELD("vbatMinCell","uint8_t","1","0.1V","Minimum cell voltage / 10 (currentBatteryProfile->voltage.cellMin / 10). 0 if USE_ADC disabled."),
  MSP_FIELD("vbatMaxCell","uint8_t","1","0.1V","Maximum cell voltage / 10 (currentBatteryProfile->voltage.cellMax / 10). 0 if USE_ADC disabled."),
  MSP_FIELD("vbatWarningCell","uint8_t","1","0.1V","Warning cell voltage / 10 (currentBatteryProfile->voltage.cellWarning / 10). 0 if USE_ADC disabled.")
);
MSP_MESSAGE(
  MSP_SET_VOLTAGE_METER_CONFIG, 0x39, ::msp::MspDir::In,
  MSP_FIELD("vbatScale","uint8_t","1","Scale / 10","Sets batteryMetersConfigMutable()->voltage.scale = value 10 (if USE_ADC)."),
  MSP_FIELD("vbatMinCell","uint8_t","1","0.1V","Sets currentBatteryProfileMutable->voltage.cellMin = value 10 (if USE_ADC)."),
  MSP_FIELD("vbatMaxCell","uint8_t","1","0.1V","Sets currentBatteryProfileMutable->voltage.cellMax = value 10 (if USE_ADC)."),
  MSP_FIELD("vbatWarningCell","uint8_t","1","0.1V","Sets currentBatteryProfileMutable->voltage.cellWarning = value 10 (if USE_ADC).")
);
MSP_MESSAGE(
  MSP_SONAR_ALTITUDE, 0x3a, ::msp::MspDir::Out,
  MSP_FIELD("rangefinderAltitude","uint32_t","4","cm","Latest altitude reading from the rangefinder (rangefinderGetLatestAltitude()). 0 if USE_RANGEFINDER disabled or no reading.")
);
MSP_MESSAGE(
  MSP_RX_MAP, 0x40, ::msp::MspDir::Out,
  MSP_FIELD("rcMap","uint8_t[MAX_MAPPABLE_RX_INPUTS]","MAX_MAPPABLE_RX_INPUTS","","Array defining the mapping from input channel index to logical function (Roll, Pitch, Yaw, Throttle, Aux1...).")
);
MSP_MESSAGE(
  MSP_SET_RX_MAP, 0x41, ::msp::MspDir::In,
  MSP_FIELD("rcMap","uint8_t[MAX_MAPPABLE_RX_INPUTS]","MAX_MAPPABLE_RX_INPUTS","","Array defining the new channel mapping.")
);
MSP_MESSAGE(
  MSP_REBOOT, 0x44, ::msp::MspDir::Out
);
MSP_MESSAGE(
  MSP_DATAFLASH_SUMMARY, 0x46, ::msp::MspDir::Out,
  MSP_FIELD("flashReady","uint8_t","1","","Boolean: 1 if flash chip is ready, 0 otherwise. (flashIsReady()). 0 if USE_FLASHFS disabled."),
  MSP_FIELD("sectorCount","uint32_t","4","","Total number of sectors on the flash chip (geometry->sectors). 0 if USE_FLASHFS disabled."),
  MSP_FIELD("totalSize","uint32_t","4","","Total size of the flash chip in bytes (geometry->totalSize). 0 if USE_FLASHFS disabled."),
  MSP_FIELD("usedSize","uint32_t","4","","Currently used size in bytes (FlashFS offset) (flashfsGetOffset()). 0 if USE_FLASHFS disabled.")
);
MSP_MESSAGE(
  MSP_DATAFLASH_READ, 0x47, ::msp::MspDir::InOut,
  MSP_FIELD("address","uint32_t","4","","Starting address to read from within the FlashFS volume."),
  MSP_FIELD("size","uint16_t","2","","(Optional) Number of bytes to read. Defaults to 128 if not provided."),
  MSP_FIELD("address","uint32_t","4","","The starting address from which data was actually read."),
  MSP_FIELD("data","uint8_t[]","Variable","","The data read from flash. Length is MIN(requested size, remaining buffer space, remaining flashfs data).")
);
MSP_MESSAGE(
  MSP_DATAFLASH_ERASE, 0x48, ::msp::MspDir::In
);
MSP_MESSAGE(
  MSP_LOOP_TIME, 0x49, ::msp::MspDir::Out,
  MSP_FIELD("looptime","uint16_t","2","µs","Configured loop time (gyroConfig()->looptime).")
);
MSP_MESSAGE(
  MSP_SET_LOOP_TIME, 0x4a, ::msp::MspDir::In,
  MSP_FIELD("looptime","uint16_t","2","µs","New loop time to set (gyroConfigMutable()->looptime).")
);
MSP_MESSAGE(
  MSP_FAILSAFE_CONFIG, 0x4b, ::msp::MspDir::Out,
  MSP_FIELD("failsafeDelay","uint8_t","1","0.1s","Delay before failsafe stage 1 activates (failsafeConfig()->failsafe_delay)."),
  MSP_FIELD("failsafeOffDelay","uint8_t","1","0.1s","Delay after signal recovery before returning control (failsafeConfig()->failsafe_off_delay)."),
  MSP_FIELD("failsafeThrottle","uint16_t","2","PWM","Throttle level during failsafe stage 2 (currentBatteryProfile->failsafe_throttle)."),
  MSP_FIELD("legacyKillSwitch","uint8_t","1","-","Legacy flag, always 0."),
  MSP_FIELD("failsafeThrottleLowDelay","uint16_t","2","ms","Delay for throttle-based failsafe detection (failsafeConfig()->failsafe_throttle_low_delay)."),
  MSP_FIELD("failsafeProcedure","uint8_t","1","Enum","Failsafe procedure (Drop, RTH, Land, etc.) (failsafeConfig()->failsafe_procedure)."),
  MSP_FIELD("failsafeRecoveryDelay","uint8_t","1","0.1s","Delay after RTH finishes before attempting recovery (failsafeConfig()->failsafe_recovery_delay)."),
  MSP_FIELD("failsafeFWRollAngle","uint16_t","2","deci-degrees","Fixed wing failsafe roll angle (failsafeConfig()->failsafe_fw_roll_angle)."),
  MSP_FIELD("failsafeFWPitchAngle","uint16_t","2","deci-degrees","Fixed wing failsafe pitch angle (failsafeConfig()->failsafe_fw_pitch_angle)."),
  MSP_FIELD("failsafeFWYawRate","uint16_t","2","deg/s","Fixed wing failsafe yaw rate (failsafeConfig()->failsafe_fw_yaw_rate)."),
  MSP_FIELD("failsafeStickThreshold","uint16_t","2","PWM units","Stick movement threshold to exit failsafe (failsafeConfig()->failsafe_stick_motion_threshold)."),
  MSP_FIELD("failsafeMinDistance","uint16_t","2","meters","Minimum distance from home for RTH failsafe (failsafeConfig()->failsafe_min_distance)."),
  MSP_FIELD("failsafeMinDistanceProc","uint8_t","1","Enum","Failsafe procedure if below min distance (failsafeConfig()->failsafe_min_distance_procedure).")
);
MSP_MESSAGE(
  MSP_SET_FAILSAFE_CONFIG, 0x4c, ::msp::MspDir::In,
  MSP_FIELD("failsafeDelay","uint8_t","1","0.1s","Sets failsafeConfigMutable()->failsafe_delay."),
  MSP_FIELD("failsafeOffDelay","uint8_t","1","0.1s","Sets failsafeConfigMutable()->failsafe_off_delay."),
  MSP_FIELD("failsafeThrottle","uint16_t","2","PWM","Sets currentBatteryProfileMutable->failsafe_throttle."),
  MSP_FIELD("legacyKillSwitch","uint8_t","1","-","Ignored."),
  MSP_FIELD("failsafeThrottleLowDelay","uint16_t","2","ms","Sets failsafeConfigMutable()->failsafe_throttle_low_delay."),
  MSP_FIELD("failsafeProcedure","uint8_t","1","Enum","Sets failsafeConfigMutable()->failsafe_procedure."),
  MSP_FIELD("failsafeRecoveryDelay","uint8_t","1","0.1s","Sets failsafeConfigMutable()->failsafe_recovery_delay."),
  MSP_FIELD("failsafeFWRollAngle","uint16_t","2","deci-degrees","Sets failsafeConfigMutable()->failsafe_fw_roll_angle (casted to int16_t)."),
  MSP_FIELD("failsafeFWPitchAngle","uint16_t","2","deci-degrees","Sets failsafeConfigMutable()->failsafe_fw_pitch_angle (casted to int16_t)."),
  MSP_FIELD("failsafeFWYawRate","uint16_t","2","deg/s","Sets failsafeConfigMutable()->failsafe_fw_yaw_rate (casted to int16_t)."),
  MSP_FIELD("failsafeStickThreshold","uint16_t","2","PWM units","Sets failsafeConfigMutable()->failsafe_stick_motion_threshold."),
  MSP_FIELD("failsafeMinDistance","uint16_t","2","meters","Sets failsafeConfigMutable()->failsafe_min_distance."),
  MSP_FIELD("failsafeMinDistanceProc","uint8_t","1","Enum","Sets failsafeConfigMutable()->failsafe_min_distance_procedure.")
);
MSP_MESSAGE(
  MSP_SDCARD_SUMMARY, 0x4f, ::msp::MspDir::Out,
  MSP_FIELD("sdCardSupported","uint8_t","1","","Bitmask: Bit 0 = 1 if SD card support compiled in (USE_SDCARD)."),
  MSP_FIELD("sdCardState","uint8_t","1","","Enum (mspSDCardState_e): Current state (Not Present, Fatal, Card Init, FS Init, Ready). 0 if USE_SDCARD disabled."),
  MSP_FIELD("fsError","uint8_t","1","","Last filesystem error code (afatfs_getLastError()). 0 if USE_SDCARD disabled."),
  MSP_FIELD("freeSpaceKB","uint32_t","4","","Free space in KiB (afatfs_getContiguousFreeSpace() / 1024). 0 if USE_SDCARD disabled."),
  MSP_FIELD("totalSpaceKB","uint32_t","4","","Total space in KiB (sdcard_getMetadata()->numBlocks / 2). 0 if USE_SDCARD disabled.")
);
MSP_MESSAGE(
  MSP_BLACKBOX_CONFIG, 0x50, ::msp::MspDir::Out,
  MSP_FIELD("blackboxDevice","uint8_t","1","","Always 0 (API no longer supported)."),
  MSP_FIELD("blackboxRateNum","uint8_t","1","","Always 0."),
  MSP_FIELD("blackboxRateDenom","uint8_t","1","","Always 0."),
  MSP_FIELD("blackboxPDenom","uint8_t","1","","Always 0.")
);
MSP_MESSAGE(
  MSP_OSD_CONFIG, 0x54, ::msp::MspDir::Out,
  MSP_FIELD("osdDriverType","uint8_t","1","Enum","OSD_DRIVER_MAX7456 if USE_OSD, else OSD_DRIVER_NONE."),
  MSP_FIELD("videoSystem","uint8_t","1","Enum","Video system (Auto/PAL/NTSC) (osdConfig()->video_system). Sent even if OSD disabled."),
  MSP_FIELD("units","uint8_t","1","Enum","Measurement units (Metric/Imperial) (osdConfig()->units). Sent even if OSD disabled."),
  MSP_FIELD("rssiAlarm","uint8_t","1","%","RSSI alarm threshold (osdConfig()->rssi_alarm). Sent even if OSD disabled."),
  MSP_FIELD("capAlarm","uint16_t","2","mAh/mWh","Capacity alarm threshold (currentBatteryProfile->capacity.warning). Sent even if OSD disabled."),
  MSP_FIELD("timerAlarm","uint16_t","2","seconds","Timer alarm threshold (osdConfig()->time_alarm). Sent even if OSD disabled."),
  MSP_FIELD("altAlarm","uint16_t","2","meters","Altitude alarm threshold (osdConfig()->alt_alarm). Sent even if OSD disabled."),
  MSP_FIELD("distAlarm","uint16_t","2","meters","Distance alarm threshold (osdConfig()->dist_alarm). Sent even if OSD disabled."),
  MSP_FIELD("negAltAlarm","uint16_t","2","meters","Negative altitude alarm threshold (osdConfig()->neg_alt_alarm). Sent even if OSD disabled."),
  MSP_FIELD("itemPositions","uint16_t[OSD_ITEM_COUNT]","OSD_ITEM_COUNT 2","Coordinates","Packed X/Y position for each OSD item on screen 0 (osdLayoutsConfig()->item_pos[0][i]). Sent even if OSD disabled.")
);
MSP_MESSAGE(
  MSP_SET_OSD_CONFIG, 0x55, ::msp::MspDir::In,
  MSP_FIELD("addr","uint8_t","1","-","Must be 0xFF (-1)."),
  MSP_FIELD("videoSystem","uint8_t","1","Enum","Sets osdConfigMutable()->video_system."),
  MSP_FIELD("units","uint8_t","1","Enum","Sets osdConfigMutable()->units."),
  MSP_FIELD("rssiAlarm","uint8_t","1","%","Sets osdConfigMutable()->rssi_alarm."),
  MSP_FIELD("capAlarm","uint16_t","2","mAh/mWh","Sets currentBatteryProfileMutable->capacity.warning."),
  MSP_FIELD("timerAlarm","uint16_t","2","seconds","Sets osdConfigMutable()->time_alarm."),
  MSP_FIELD("altAlarm","uint16_t","2","meters","Sets osdConfigMutable()->alt_alarm."),
  MSP_FIELD("distAlarm","uint16_t","2","meters","(Optional) Sets osdConfigMutable()->dist_alarm."),
  MSP_FIELD("negAltAlarm","uint16_t","2","meters","(Optional) Sets osdConfigMutable()->neg_alt_alarm."),
  MSP_FIELD("itemIndex","uint8_t","1","Index","Index of the OSD item to position (0 to OSD_ITEM_COUNT - 1).")
);
MSP_MESSAGE(
  MSP_OSD_CHAR_WRITE, 0x57, ::msp::MspDir::In,
  MSP_FIELD("address","uint8_t or uint16_t","1 or 2","","Starting address in font memory. Size depends on total payload size."),
  MSP_FIELD("charData","uint8_t[]","Variable","","Character bitmap data (54 or 64 bytes per char, depending on format).")
);
MSP_MESSAGE(
  MSP_VTX_CONFIG, 0x58, ::msp::MspDir::Out,
  MSP_FIELD("vtxDeviceType","uint8_t","1","","Enum (VTXDEV_): Type of VTX device detected/configured. VTXDEV_UNKNOWN if none."),
  MSP_FIELD("band","uint8_t","1","","VTX band number (from vtxSettingsConfig)."),
  MSP_FIELD("channel","uint8_t","1","","VTX channel number (from vtxSettingsConfig)."),
  MSP_FIELD("power","uint8_t","1","","VTX power level index (from vtxSettingsConfig)."),
  MSP_FIELD("pitMode","uint8_t","1","","Boolean: 1 if VTX is currently in pit mode, 0 otherwise."),
  MSP_FIELD("vtxReady","uint8_t","1","","Boolean: 1 if VTX device reported ready, 0 otherwise."),
  MSP_FIELD("lowPowerDisarm","uint8_t","1","","Boolean: 1 if low power on disarm is enabled (from vtxSettingsConfig)."),
  MSP_FIELD("vtxTableAvailable","uint8_t","1","","Boolean: 1 if VTX tables (band/power) are available for query."),
  MSP_FIELD("bandCount","uint8_t","1","","Number of bands supported by the VTX device."),
  MSP_FIELD("channelCount","uint8_t","1","","Number of channels per band supported by the VTX device."),
  MSP_FIELD("powerCount","uint8_t","1","","Number of power levels supported by the VTX device.")
);
MSP_MESSAGE(
  MSP_SET_VTX_CONFIG, 0x59, ::msp::MspDir::In,
  MSP_FIELD("bandChannelEncoded","uint16_t","2","","Encoded band/channel value: (band-1)8 + (channel-1). If <= VTXCOMMON_MSP_BANDCHAN_CHKVAL."),
  MSP_FIELD("power","uint8_t","1","","Power level index to set (vtxSettingsConfigMutable()->power)."),
  MSP_FIELD("pitMode","uint8_t","1","","Pit mode state to set (0=off, 1=on). Directly calls vtxCommonSetPitMode."),
  MSP_FIELD("lowPowerDisarm","uint8_t","1","","Low power on disarm setting (vtxSettingsConfigMutable()->lowPowerDisarm)."),
  MSP_FIELD("pitModeFreq","uint16_t","2","","Ignored. Betaflight extension."),
  MSP_FIELD("band","uint8_t","1","","Explicit band number to set (vtxSettingsConfigMutable()->band). Overrides encoded value if present."),
  MSP_FIELD("channel","uint8_t","1","","Explicit channel number to set (vtxSettingsConfigMutable()->channel). Overrides encoded value if present."),
  MSP_FIELD("frequency","uint16_t","2","","Ignored. Betaflight extension."),
  MSP_FIELD("bandCount","uint8_t","1","","Ignored. Betaflight extension."),
  MSP_FIELD("channelCount","uint8_t","1","","Ignored. Betaflight extension."),
  MSP_FIELD("powerCount","uint8_t","1","","Ignored. Betaflight extension (can potentially reduce reported power count if valid).")
);
MSP_MESSAGE(
  MSP_ADVANCED_CONFIG, 0x5a, ::msp::MspDir::Out,
  MSP_FIELD("gyroSyncDenom","uint8_t","1","","Always 1 (BF compatibility)."),
  MSP_FIELD("pidProcessDenom","uint8_t","1","","Always 1 (BF compatibility)."),
  MSP_FIELD("useUnsyncedPwm","uint8_t","1","","Always 1 (BF compatibility, INAV uses async PWM based on protocol)."),
  MSP_FIELD("motorPwmProtocol","uint8_t","1","","Enum: Motor PWM protocol type (motorConfig()->motorPwmProtocol)."),
  MSP_FIELD("motorPwmRate","uint16_t","2","","Hz: Motor PWM rate (if applicable) (motorConfig()->motorPwmRate)."),
  MSP_FIELD("servoPwmRate","uint16_t","2","","Hz: Servo PWM rate (servoConfig()->servoPwmRate)."),
  MSP_FIELD("legacyGyroSync","uint8_t","1","","Always 0 (BF compatibility).")
);
MSP_MESSAGE(
  MSP_SET_ADVANCED_CONFIG, 0x5b, ::msp::MspDir::In,
  MSP_FIELD("gyroSyncDenom","uint8_t","1","","Ignored."),
  MSP_FIELD("pidProcessDenom","uint8_t","1","","Ignored."),
  MSP_FIELD("useUnsyncedPwm","uint8_t","1","","Ignored."),
  MSP_FIELD("motorPwmProtocol","uint8_t","1","","Sets motorConfigMutable()->motorPwmProtocol."),
  MSP_FIELD("motorPwmRate","uint16_t","2","","Sets motorConfigMutable()->motorPwmRate."),
  MSP_FIELD("servoPwmRate","uint16_t","2","","Sets servoConfigMutable()->servoPwmRate."),
  MSP_FIELD("legacyGyroSync","uint8_t","1","","Ignored.")
);
MSP_MESSAGE(
  MSP_FILTER_CONFIG, 0x5c, ::msp::MspDir::Out,
  MSP_FIELD("gyroMainLpfHz","uint8_t","1","Hz","Gyro main low-pass filter cutoff frequency (gyroConfig()->gyro_main_lpf_hz)."),
  MSP_FIELD("dtermLpfHz","uint16_t","2","Hz","D-term low-pass filter cutoff frequency (pidProfile()->dterm_lpf_hz)."),
  MSP_FIELD("yawLpfHz","uint16_t","2","Hz","Yaw low-pass filter cutoff frequency (pidProfile()->yaw_lpf_hz)."),
  MSP_FIELD("legacyGyroNotchHz","uint16_t","2","-","Always 0 (Legacy)."),
  MSP_FIELD("legacyGyroNotchCutoff","uint16_t","2","-","Always 1 (Legacy)."),
  MSP_FIELD("bfCompatDtermNotchHz","uint16_t","2","-","Always 0 (BF compatibility)."),
  MSP_FIELD("bfCompatDtermNotchCutoff","uint16_t","2","-","Always 1 (BF compatibility)."),
  MSP_FIELD("bfCompatGyroNotch2Hz","uint16_t","2","-","Always 0 (BF compatibility)."),
  MSP_FIELD("bfCompatGyroNotch2Cutoff","uint16_t","2","-","Always 1 (BF compatibility)."),
  MSP_FIELD("accNotchHz","uint16_t","2","Hz","Accelerometer notch filter center frequency (accelerometerConfig()->acc_notch_hz)."),
  MSP_FIELD("accNotchCutoff","uint16_t","2","Hz","Accelerometer notch filter cutoff frequency (accelerometerConfig()->acc_notch_cutoff)."),
  MSP_FIELD("legacyGyroStage2LpfHz","uint16_t","2","-","Always 0 (Legacy).")
);
MSP_MESSAGE(
  MSP_SET_FILTER_CONFIG, 0x5d, ::msp::MspDir::In,
  MSP_FIELD("gyroMainLpfHz","uint8_t","1","Hz","Sets gyroConfigMutable()->gyro_main_lpf_hz. (Size >= 5)"),
  MSP_FIELD("dtermLpfHz","uint16_t","2","Hz","Sets pidProfileMutable()->dterm_lpf_hz (constrained 0-500). (Size >= 5)"),
  MSP_FIELD("yawLpfHz","uint16_t","2","Hz","Sets pidProfileMutable()->yaw_lpf_hz (constrained 0-255). (Size >= 5)"),
  MSP_FIELD("legacyGyroNotchHz","uint16_t","2","-","Ignored. (Size >= 9)"),
  MSP_FIELD("legacyGyroNotchCutoff","uint16_t","2","-","Ignored. (Size >= 9)"),
  MSP_FIELD("bfCompatDtermNotchHz","uint16_t","2","-","Ignored. (Size >= 13)"),
  MSP_FIELD("bfCompatDtermNotchCutoff","uint16_t","2","-","Ignored. (Size >= 13)"),
  MSP_FIELD("bfCompatGyroNotch2Hz","uint16_t","2","-","Ignored. (Size >= 17)"),
  MSP_FIELD("bfCompatGyroNotch2Cutoff","uint16_t","2","-","Ignored. (Size >= 17)"),
  MSP_FIELD("accNotchHz","uint16_t","2","Hz","Sets accelerometerConfigMutable()->acc_notch_hz (constrained 0-255). (Size >= 21)"),
  MSP_FIELD("accNotchCutoff","uint16_t","2","Hz","Sets accelerometerConfigMutable()->acc_notch_cutoff (constrained 1-255). (Size >= 21)"),
  MSP_FIELD("legacyGyroStage2LpfHz","uint16_t","2","-","Ignored. (Size >= 22)")
);
MSP_MESSAGE(
  MSP_PID_ADVANCED, 0x5e, ::msp::MspDir::Out,
  MSP_FIELD("legacyRollPitchItermIgnore","uint16_t","2","-","Always 0 (Legacy)."),
  MSP_FIELD("legacyYawItermIgnore","uint16_t","2","-","Always 0 (Legacy)."),
  MSP_FIELD("legacyYawPLimit","uint16_t","2","-","Always 0 (Legacy)."),
  MSP_FIELD("bfCompatDeltaMethod","uint8_t","1","-","Always 0 (BF compatibility)."),
  MSP_FIELD("bfCompatVbatPidComp","uint8_t","1","-","Always 0 (BF compatibility)."),
  MSP_FIELD("bfCompatSetpointRelaxRatio","uint8_t","1","-","Always 0 (BF compatibility)."),
  MSP_FIELD("reserved1","uint8_t","1","-","Always 0."),
  MSP_FIELD("legacyPidSumLimit","uint16_t","2","-","Always 0 (Legacy)."),
  MSP_FIELD("bfCompatItermThrottleGain","uint8_t","1","-","Always 0 (BF compatibility)."),
  MSP_FIELD("accelLimitRollPitch","uint16_t","2","dps / 10","Axis acceleration limit for Roll/Pitch / 10 (pidProfile()->axisAccelerationLimitRollPitch / 10)."),
  MSP_FIELD("accelLimitYaw","uint16_t","2","dps / 10","Axis acceleration limit for Yaw / 10 (pidProfile()->axisAccelerationLimitYaw / 10).")
);
MSP_MESSAGE(
  MSP_SET_PID_ADVANCED, 0x5f, ::msp::MspDir::In,
  MSP_FIELD("legacyRollPitchItermIgnore","uint16_t","2","-","Ignored."),
  MSP_FIELD("legacyYawItermIgnore","uint16_t","2","-","Ignored."),
  MSP_FIELD("legacyYawPLimit","uint16_t","2","-","Ignored."),
  MSP_FIELD("bfCompatDeltaMethod","uint8_t","1","-","Ignored."),
  MSP_FIELD("bfCompatVbatPidComp","uint8_t","1","-","Ignored."),
  MSP_FIELD("bfCompatSetpointRelaxRatio","uint8_t","1","-","Ignored."),
  MSP_FIELD("reserved1","uint8_t","1","-","Ignored."),
  MSP_FIELD("legacyPidSumLimit","uint16_t","2","-","Ignored."),
  MSP_FIELD("bfCompatItermThrottleGain","uint8_t","1","-","Ignored."),
  MSP_FIELD("accelLimitRollPitch","uint16_t","2","dps / 10","Sets pidProfileMutable()->axisAccelerationLimitRollPitch = value 10."),
  MSP_FIELD("accelLimitYaw","uint16_t","2","dps / 10","Sets pidProfileMutable()->axisAccelerationLimitYaw = value 10.")
);
MSP_MESSAGE(
  MSP_SENSOR_CONFIG, 0x60, ::msp::MspDir::Out,
  MSP_FIELD("accHardware","uint8_t","1","","Enum (accHardware_e): Accelerometer hardware type (accelerometerConfig()->acc_hardware)."),
  MSP_FIELD("baroHardware","uint8_t","1","","Enum (baroHardware_e): Barometer hardware type (barometerConfig()->baro_hardware). 0 if USE_BARO disabled."),
  MSP_FIELD("magHardware","uint8_t","1","","Enum (magHardware_e): Magnetometer hardware type (compassConfig()->mag_hardware). 0 if USE_MAG disabled."),
  MSP_FIELD("pitotHardware","uint8_t","1","","Enum (pitotHardware_e): Pitot tube hardware type (pitotmeterConfig()->pitot_hardware). 0 if USE_PITOT disabled."),
  MSP_FIELD("rangefinderHardware","uint8_t","1","","Enum (rangefinderHardware_e): Rangefinder hardware type (rangefinderConfig()->rangefinder_hardware). 0 if USE_RANGEFINDER disabled."),
  MSP_FIELD("opflowHardware","uint8_t","1","","Enum (opticalFlowHardware_e): Optical flow hardware type (opticalFlowConfig()->opflow_hardware). 0 if USE_OPFLOW disabled.")
);
MSP_MESSAGE(
  MSP_SET_SENSOR_CONFIG, 0x61, ::msp::MspDir::In,
  MSP_FIELD("accHardware","uint8_t","1","","Sets accelerometerConfigMutable()->acc_hardware."),
  MSP_FIELD("baroHardware","uint8_t","1","","Sets barometerConfigMutable()->baro_hardware (if USE_BARO)."),
  MSP_FIELD("magHardware","uint8_t","1","","Sets compassConfigMutable()->mag_hardware (if USE_MAG)."),
  MSP_FIELD("pitotHardware","uint8_t","1","","Sets pitotmeterConfigMutable()->pitot_hardware (if USE_PITOT)."),
  MSP_FIELD("rangefinderHardware","uint8_t","1","","Sets rangefinderConfigMutable()->rangefinder_hardware (if USE_RANGEFINDER)."),
  MSP_FIELD("opflowHardware","uint8_t","1","","Sets opticalFlowConfigMutable()->opflow_hardware (if USE_OPFLOW).")
);
MSP_MESSAGE(
  MSP_STATUS, 0x65, ::msp::MspDir::Out,
  MSP_FIELD("cycleTime","uint16_t","2","µs","Main loop cycle time (cycleTime)."),
  MSP_FIELD("i2cErrors","uint16_t","2","Count","Number of I2C errors encountered (i2cGetErrorCounter()). 0 if USE_I2C not defined."),
  MSP_FIELD("sensorStatus","uint16_t","2","Bitmask","Bitmask indicating available/active sensors (packSensorStatus()). See notes."),
  MSP_FIELD("activeModesLow","uint32_t","4","Bitmask","First 32 bits of the active flight modes bitmask (packBoxModeFlags())."),
  MSP_FIELD("profile","uint8_t","1","Index","Current configuration profile index (0-based) (getConfigProfile()).")
);
MSP_MESSAGE(
  MSP_RAW_IMU, 0x66, ::msp::MspDir::Out,
  MSP_FIELD("accX","int16_t","2","~1/512 G","Raw accelerometer X reading, scaled (acc.accADCf[X] 512)."),
  MSP_FIELD("accY","int16_t","2","~1/512 G","Raw accelerometer Y reading, scaled (acc.accADCf[Y] 512)."),
  MSP_FIELD("accZ","int16_t","2","~1/512 G","Raw accelerometer Z reading, scaled (acc.accADCf[Z] 512)."),
  MSP_FIELD("gyroX","int16_t","2","deg/s","Gyroscope X-axis rate (gyroRateDps(X))."),
  MSP_FIELD("gyroY","int16_t","2","deg/s","Gyroscope Y-axis rate (gyroRateDps(Y))."),
  MSP_FIELD("gyroZ","int16_t","2","deg/s","Gyroscope Z-axis rate (gyroRateDps(Z))."),
  MSP_FIELD("magX","int16_t","2","Raw units","Raw magnetometer X reading (mag.magADC[X]). 0 if USE_MAG disabled."),
  MSP_FIELD("magY","int16_t","2","Raw units","Raw magnetometer Y reading (mag.magADC[Y]). 0 if USE_MAG disabled."),
  MSP_FIELD("magZ","int16_t","2","Raw units","Raw magnetometer Z reading (mag.magADC[Z]). 0 if USE_MAG disabled.")
);
MSP_MESSAGE(
  MSP_SERVO, 0x67, ::msp::MspDir::Out,
  MSP_FIELD("servoOutputs","int16_t[MAX_SUPPORTED_SERVOS]","MAX_SUPPORTED_SERVOS 2","PWM","Array of current servo output values (typically 1000-2000).")
);
MSP_MESSAGE(
  MSP_MOTOR, 0x68, ::msp::MspDir::Out,
  MSP_FIELD("motorOutputs","uint16_t[8]","16","PWM","Array of current motor output values (typically 1000-2000). Values beyond MAX_SUPPORTED_MOTORS are 0.")
);
MSP_MESSAGE(
  MSP_RC, 0x69, ::msp::MspDir::Out,
  MSP_FIELD("rcChannels","uint16_t[]","rxRuntimeConfig.channelCount 2","PWM","Array of current RC channel values (typically 1000-2000). Length depends on detected channels.")
);
MSP_MESSAGE(
  MSP_RAW_GPS, 0x6a, ::msp::MspDir::Out,
  MSP_FIELD("fixType","uint8_t","1","Enum","GPS fix type (gpsSol.fixType)."),
  MSP_FIELD("numSat","uint8_t","1","Count","Number of satellites used in solution (gpsSol.numSat)."),
  MSP_FIELD("latitude","int32_t","4","deg 1e7","Latitude (gpsSol.llh.lat)."),
  MSP_FIELD("longitude","int32_t","4","deg 1e7","Longitude (gpsSol.llh.lon)."),
  MSP_FIELD("altitude","int16_t","2","meters","Altitude above MSL (gpsSol.llh.alt / 100)."),
  MSP_FIELD("speed","uint16_t","2","cm/s","Ground speed (gpsSol.groundSpeed)."),
  MSP_FIELD("groundCourse","uint16_t","2","deci-degrees","Ground course (gpsSol.groundCourse)."),
  MSP_FIELD("hdop","uint16_t","2","HDOP 100","Horizontal Dilution of Precision (gpsSol.hdop).")
);
MSP_MESSAGE(
  MSP_COMP_GPS, 0x6b, ::msp::MspDir::Out,
  MSP_FIELD("distanceToHome","uint16_t","2","meters","Distance to the home point (GPS_distanceToHome)."),
  MSP_FIELD("directionToHome","uint16_t","2","degrees","Direction to the home point (0-360) (GPS_directionToHome)."),
  MSP_FIELD("gpsHeartbeat","uint8_t","1","Boolean","Indicates if GPS data is being received (gpsSol.flags.gpsHeartbeat).")
);
MSP_MESSAGE(
  MSP_ATTITUDE, 0x6c, ::msp::MspDir::Out,
  MSP_FIELD("roll","int16_t","2","deci-degrees","Roll angle (attitude.values.roll)."),
  MSP_FIELD("pitch","int16_t","2","deci-degrees","Pitch angle (attitude.values.pitch)."),
  MSP_FIELD("yaw","int16_t","2","degrees","Yaw/Heading angle (DECIDEGREES_TO_DEGREES(attitude.values.yaw)).")
);
MSP_MESSAGE(
  MSP_ALTITUDE, 0x6d, ::msp::MspDir::Out,
  MSP_FIELD("estimatedAltitude","int32_t","4","cm","Estimated altitude above home/sea level (getEstimatedActualPosition(Z))."),
  MSP_FIELD("variometer","int16_t","2","cm/s","Estimated vertical speed (getEstimatedActualVelocity(Z))."),
  MSP_FIELD("baroAltitude","int32_t","4","cm","Latest raw altitude from barometer (baroGetLatestAltitude()). 0 if USE_BARO disabled.")
);
MSP_MESSAGE(
  MSP_ANALOG, 0x6e, ::msp::MspDir::Out,
  MSP_FIELD("vbat","uint8_t","1","0.1V","Battery voltage, scaled (getBatteryVoltage() / 10), constrained 0-255."),
  MSP_FIELD("mAhDrawn","uint16_t","2","mAh","Consumed battery capacity (getMAhDrawn()), constrained 0-65535."),
  MSP_FIELD("rssi","uint16_t","2","0-1023 or %","Received Signal Strength Indicator (getRSSI()). Units depend on source."),
  MSP_FIELD("amperage","int16_t","2","0.01A","Current draw (getAmperage()), constrained -32768 to 32767.")
);
MSP_MESSAGE(
  MSP_RC_TUNING, 0x6f, ::msp::MspDir::Out,
  MSP_FIELD("legacyRcRate","uint8_t","1","","Always 100 (Legacy, unused)."),
  MSP_FIELD("rcExpo","uint8_t","1","","Roll/Pitch RC Expo (currentControlRateProfile->stabilized.rcExpo8)."),
  MSP_FIELD("rollRate","uint8_t","1","","Roll Rate (currentControlRateProfile->stabilized.rates[FD_ROLL])."),
  MSP_FIELD("pitchRate","uint8_t","1","","Pitch Rate (currentControlRateProfile->stabilized.rates[FD_PITCH])."),
  MSP_FIELD("yawRate","uint8_t","1","","Yaw Rate (currentControlRateProfile->stabilized.rates[FD_YAW])."),
  MSP_FIELD("dynamicThrottlePID","uint8_t","1","","Dynamic Throttle PID (TPA) value (currentControlRateProfile->throttle.dynPID)."),
  MSP_FIELD("throttleMid","uint8_t","1","","Throttle Midpoint (currentControlRateProfile->throttle.rcMid8)."),
  MSP_FIELD("throttleExpo","uint8_t","1","","Throttle Expo (currentControlRateProfile->throttle.rcExpo8)."),
  MSP_FIELD("tpaBreakpoint","uint16_t","2","","Throttle PID Attenuation (TPA) breakpoint (currentControlRateProfile->throttle.pa_breakpoint)."),
  MSP_FIELD("rcYawExpo","uint8_t","1","","Yaw RC Expo (currentControlRateProfile->stabilized.rcYawExpo8).")
);
MSP_MESSAGE(
  MSP_ACTIVEBOXES, 0x71, ::msp::MspDir::Out,
  MSP_FIELD("activeModes","boxBitmask_t","sizeof(boxBitmask_t)","","Bitmask of all active modes (packBoxModeFlags()). Size depends on boxBitmask_t definition.")
);
MSP_MESSAGE(
  MSP_MISC, 0x72, ::msp::MspDir::Out,
  MSP_FIELD("midRc","uint16_t","2","PWM","Mid RC value (PWM_RANGE_MIDDLE, typically 1500)."),
  MSP_FIELD("legacyMinThrottle","uint16_t","2","-","Always 0 (Legacy)."),
  MSP_FIELD("maxThrottle","uint16_t","2","PWM","Maximum throttle command (getMaxThrottle())."),
  MSP_FIELD("minCommand","uint16_t","2","PWM","Minimum motor command when disarmed (motorConfig()->mincommand)."),
  MSP_FIELD("failsafeThrottle","uint16_t","2","PWM","Failsafe throttle level (currentBatteryProfile->failsafe_throttle)."),
  MSP_FIELD("gpsType","uint8_t","1","Enum","GPS provider type (gpsConfig()->provider). 0 if USE_GPS disabled."),
  MSP_FIELD("legacyGpsBaud","uint8_t","1","-","Always 0 (Legacy)."),
  MSP_FIELD("gpsSbasMode","uint8_t","1","Enum","GPS SBAS mode (gpsConfig()->sbasMode). 0 if USE_GPS disabled."),
  MSP_FIELD("legacyMwCurrentOut","uint8_t","1","-","Always 0 (Legacy)."),
  MSP_FIELD("rssiChannel","uint8_t","1","Index","RSSI channel index (1-based) (rxConfig()->rssi_channel)."),
  MSP_FIELD("reserved1","uint8_t","1","-","Always 0."),
  MSP_FIELD("magDeclination","uint16_t","2","0.1 degrees","Magnetic declination / 10 (compassConfig()->mag_declination / 10). 0 if USE_MAG disabled."),
  MSP_FIELD("vbatScale","uint8_t","1","Scale / 10","Voltage scale / 10 (batteryMetersConfig()->voltage.scale / 10). 0 if USE_ADC disabled."),
  MSP_FIELD("vbatMinCell","uint8_t","1","0.1V","Min cell voltage / 10 (currentBatteryProfile->voltage.cellMin / 10). 0 if USE_ADC disabled."),
  MSP_FIELD("vbatMaxCell","uint8_t","1","0.1V","Max cell voltage / 10 (currentBatteryProfile->voltage.cellMax / 10). 0 if USE_ADC disabled."),
  MSP_FIELD("vbatWarningCell","uint8_t","1","0.1V","Warning cell voltage / 10 (currentBatteryProfile->voltage.cellWarning / 10). 0 if USE_ADC disabled.")
);
MSP_MESSAGE(
  MSP_BOXNAMES, 0x74, ::msp::MspDir::Out,
  MSP_FIELD("boxNamesString","char[]","Variable","","String containing mode names separated by ';'. Null termination not guaranteed by MSP, relies on payload size. (serializeBoxNamesReply()).")
);
MSP_MESSAGE(
  MSP_PIDNAMES, 0x75, ::msp::MspDir::Out,
  MSP_FIELD("pidNamesString","char[]","Variable","","String \"ROLL;PITCH;YAW;ALT;Pos;PosR;NavR;LEVEL;MAG;VEL;\". Null termination not guaranteed by MSP.")
);
MSP_MESSAGE(
  MSP_WP, 0x76, ::msp::MspDir::InOut,
  MSP_FIELD("waypointIndex","uint8_t","1","","Index of the waypoint to retrieve (0 to NAV_MAX_WAYPOINTS - 1)."),
  MSP_FIELD("waypointIndex","uint8_t","1","Index","Index of the returned waypoint."),
  MSP_FIELD("action","uint8_t","1","Enum","Waypoint action type (navWaypointActions_e)."),
  MSP_FIELD("latitude","int32_t","4","deg 1e7","Latitude coordinate."),
  MSP_FIELD("longitude","int32_t","4","deg 1e7","Longitude coordinate."),
  MSP_FIELD("altitude","int32_t","4","cm","Altitude coordinate (relative to home or sea level, see flag)."),
  MSP_FIELD("param1","uint16_t","2","Varies","Parameter 1 (meaning depends on action)."),
  MSP_FIELD("param2","uint16_t","2","Varies","Parameter 2 (meaning depends on action)."),
  MSP_FIELD("param3","uint16_t","2","Varies","Parameter 3 (meaning depends on action)."),
  MSP_FIELD("flag","uint8_t","1","Bitmask","Waypoint flags (NAV_WP_FLAG_).")
);
MSP_MESSAGE(
  MSP_BOXIDS, 0x77, ::msp::MspDir::Out,
  MSP_FIELD("boxIds","uint8_t[]","Variable","","Array of permanent IDs for each configured box (serializeBoxReply()). Length depends on number of boxes.")
);
MSP_MESSAGE(
  MSP_SERVO_CONFIGURATIONS, 0x78, ::msp::MspDir::Out,
  MSP_FIELD("min","uint16_t","2","PWM","Minimum servo endpoint (servoParams(i)->min)."),
  MSP_FIELD("max","uint16_t","2","PWM","Maximum servo endpoint (servoParams(i)->max)."),
  MSP_FIELD("middle","uint16_t","2","PWM","Middle/Neutral servo position (servoParams(i)->middle)."),
  MSP_FIELD("rate","uint8_t","1","% (-100 to 100)","Servo rate/scaling (servoParams(i)->rate)."),
  MSP_FIELD("reserved1","uint8_t","1","-","Always 0."),
  MSP_FIELD("reserved2","uint8_t","1","-","Always 0."),
  MSP_FIELD("legacyForwardChan","uint8_t","1","-","Always 255 (Legacy)."),
  MSP_FIELD("legacyReversedSources","uint32_t","4","-","Always 0 (Legacy).")
);
MSP_MESSAGE(
  MSP_NAV_STATUS, 0x79, ::msp::MspDir::Out,
  MSP_FIELD("navMode","uint8_t","1","","Enum (NAV_MODE_): Current navigation mode (None, RTH, WP, Hold, etc.) (NAV_Status.mode)."),
  MSP_FIELD("navState","uint8_t","1","","Enum (NAV_STATE_): Current navigation state (NAV_Status.state)."),
  MSP_FIELD("activeWpAction","uint8_t","1","","Enum (navWaypointActions_e): Action of the currently executing waypoint (NAV_Status.activeWpAction)."),
  MSP_FIELD("activeWpNumber","uint8_t","1","","Index: Index of the currently executing waypoint (NAV_Status.activeWpNumber)."),
  MSP_FIELD("navError","uint8_t","1","","Enum (NAV_ERROR_): Current navigation error code (NAV_Status.error)."),
  MSP_FIELD("targetHeading","int16_t","2","","degrees: Target heading for heading controller (getHeadingHoldTarget()).")
);
MSP_MESSAGE(
  MSP_3D, 0x7c, ::msp::MspDir::Out,
  MSP_FIELD("deadbandLow","uint16_t","2","PWM","Lower deadband limit for 3D mode (reversibleMotorsConfig()->deadband_low)."),
  MSP_FIELD("deadbandHigh","uint16_t","2","PWM","Upper deadband limit for 3D mode (reversibleMotorsConfig()->deadband_high)."),
  MSP_FIELD("neutral","uint16_t","2","PWM","Neutral throttle point for 3D mode (reversibleMotorsConfig()->neutral).")
);
MSP_MESSAGE(
  MSP_RC_DEADBAND, 0x7d, ::msp::MspDir::Out,
  MSP_FIELD("deadband","uint8_t","1","PWM","General RC deadband for Roll/Pitch (rcControlsConfig()->deadband)."),
  MSP_FIELD("yawDeadband","uint8_t","1","PWM","Specific deadband for Yaw (rcControlsConfig()->yaw_deadband)."),
  MSP_FIELD("altHoldDeadband","uint8_t","1","PWM","Deadband for altitude hold adjustments (rcControlsConfig()->alt_hold_deadband)."),
  MSP_FIELD("throttleDeadband","uint16_t","2","PWM","Deadband around throttle mid-stick (rcControlsConfig()->mid_throttle_deadband).")
);
MSP_MESSAGE(
  MSP_SENSOR_ALIGNMENT, 0x7e, ::msp::MspDir::Out,
  MSP_FIELD("gyroAlign","uint8_t","1","","Always 0 (Legacy alignment enum)."),
  MSP_FIELD("accAlign","uint8_t","1","","Always 0 (Legacy alignment enum)."),
  MSP_FIELD("magAlign","uint8_t","1","","Magnetometer alignment (compassConfig()->mag_align). 0 if USE_MAG disabled."),
  MSP_FIELD("opflowAlign","uint8_t","1","","Optical flow alignment (opticalFlowConfig()->opflow_align). 0 if USE_OPFLOW disabled.")
);
MSP_MESSAGE(
  MSP_LED_STRIP_MODECOLOR, 0x7f, ::msp::MspDir::Out,
  MSP_FIELD("modeIndex","uint8_t","1","","Index of the LED mode (ledModeIndex_e). LED_MODE_COUNT for special colors."),
  MSP_FIELD("directionOrSpecialIndex","uint8_t","1","","Index of the direction (ledDirection_e) or special color (ledSpecialColor_e)."),
  MSP_FIELD("colorIndex","uint8_t","1","","Index of the color assigned from ledStripConfig()->colors.")
);
MSP_MESSAGE(
  MSP_BATTERY_STATE, 0x82, ::msp::MspDir::Out,
  MSP_FIELD("cellCount","uint8_t","1","Count","Number of battery cells (getBatteryCellCount())."),
  MSP_FIELD("capacity","uint16_t","2","mAh","Battery capacity (currentBatteryProfile->capacity.value)."),
  MSP_FIELD("vbatScaled","uint8_t","1","0.1V","Battery voltage / 10 (getBatteryVoltage() / 10)."),
  MSP_FIELD("mAhDrawn","uint16_t","2","mAh","Consumed capacity (getMAhDrawn())."),
  MSP_FIELD("amperage","int16_t","2","0.01A","Current draw (getAmperage())."),
  MSP_FIELD("batteryState","uint8_t","1","Enum","Current battery state (getBatteryState(), see BATTERY_STATE_)."),
  MSP_FIELD("vbatActual","uint16_t","2","0.01V","Actual battery voltage (getBatteryVoltage()).")
);
MSP_MESSAGE(
  MSP_VTXTABLE_BAND, 0x89, ::msp::MspDir::InOut
);
MSP_MESSAGE(
  MSP_VTXTABLE_POWERLEVEL, 0x8a, ::msp::MspDir::InOut,
  MSP_FIELD("powerLevelIndex","uint8_t","1","","1-based index of the power level to query."),
  MSP_FIELD("powerLevelIndex","uint8_t","1","","1-based index of the returned power level."),
  MSP_FIELD("powerValue","uint16_t","2","","Always 0 (Actual power value in mW is not stored/returned via MSP)."),
  MSP_FIELD("labelLength","uint8_t","1","","Length of the power level label string that follows."),
  MSP_FIELD("label","char[]","Variable","","Power level label string (e.g., \"25\", \"200\"). Length given by previous field.")
);
MSP_MESSAGE(
  MSP_STATUS_EX, 0x96, ::msp::MspDir::Out,
  MSP_FIELD("cycleTime","uint16_t","2","µs","Main loop cycle time."),
  MSP_FIELD("i2cErrors","uint16_t","2","Count","I2C errors."),
  MSP_FIELD("sensorStatus","uint16_t","2","Bitmask","Sensor status bitmask."),
  MSP_FIELD("activeModesLow","uint32_t","4","Bitmask","First 32 active modes."),
  MSP_FIELD("profile","uint8_t","1","Index","Current config profile index."),
  MSP_FIELD("cpuLoad","uint16_t","2","%","Average system load percentage (averageSystemLoadPercent)."),
  MSP_FIELD("armingFlags","uint16_t","2","Bitmask","Flight controller arming flags (armingFlags). Note: Truncated to 16 bits."),
  MSP_FIELD("accCalibAxisFlags","uint8_t","1","Bitmask","Accelerometer calibrated axes flags (accGetCalibrationAxisFlags()).")
);
MSP_MESSAGE(
  MSP_SENSOR_STATUS, 0x97, ::msp::MspDir::Out,
  MSP_FIELD("overallHealth","uint8_t","1","Boolean","1 if all essential hardware is healthy, 0 otherwise (isHardwareHealthy())."),
  MSP_FIELD("gyroStatus","uint8_t","1","Enum","Gyro hardware status (getHwGyroStatus())."),
  MSP_FIELD("accStatus","uint8_t","1","Enum","Accelerometer hardware status (getHwAccelerometerStatus())."),
  MSP_FIELD("magStatus","uint8_t","1","Enum","Compass hardware status (getHwCompassStatus())."),
  MSP_FIELD("baroStatus","uint8_t","1","Enum","Barometer hardware status (getHwBarometerStatus())."),
  MSP_FIELD("gpsStatus","uint8_t","1","Enum","GPS hardware status (getHwGPSStatus())."),
  MSP_FIELD("rangefinderStatus","uint8_t","1","Enum","Rangefinder hardware status (getHwRangefinderStatus())."),
  MSP_FIELD("pitotStatus","uint8_t","1","Enum","Pitot hardware status (getHwPitotmeterStatus())."),
  MSP_FIELD("opflowStatus","uint8_t","1","Enum","Optical Flow hardware status (getHwOpticalFlowStatus()).")
);
MSP_MESSAGE(
  MSP_UID, 0xa0, ::msp::MspDir::Out,
  MSP_FIELD("uid0","uint32_t","4","","First 32 bits of the unique ID (U_ID_0)."),
  MSP_FIELD("uid1","uint32_t","4","","Middle 32 bits of the unique ID (U_ID_1)."),
  MSP_FIELD("uid2","uint32_t","4","","Last 32 bits of the unique ID (U_ID_2).")
);
MSP_MESSAGE(
  MSP_GPSSVINFO, 0xa4, ::msp::MspDir::Out,
  MSP_FIELD("protocolVersion","uint8_t","1","","Always 1 (Stub version)."),
  MSP_FIELD("numChannels","uint8_t","1","","Always 0 (Number of SV info channels reported)."),
  MSP_FIELD("hdopHundreds","uint8_t","1","","HDOP / 100 (gpsSol.hdop / 100)."),
  MSP_FIELD("hdopUnits","uint8_t","1","","HDOP / 100 (gpsSol.hdop / 100).")
);
MSP_MESSAGE(
  MSP_GPSSTATISTICS, 0xa6, ::msp::MspDir::Out,
  MSP_FIELD("lastMessageDt","uint16_t","2","ms","Time since last valid GPS message (gpsStats.lastMessageDt)."),
  MSP_FIELD("errors","uint32_t","4","Count","Number of GPS communication errors (gpsStats.errors)."),
  MSP_FIELD("timeouts","uint32_t","4","Count","Number of GPS communication timeouts (gpsStats.timeouts)."),
  MSP_FIELD("packetCount","uint32_t","4","Count","Number of valid GPS packets received (gpsStats.packetCount)."),
  MSP_FIELD("hdop","uint16_t","2","HDOP 100","Horizontal Dilution of Precision (gpsSol.hdop)."),
  MSP_FIELD("eph","uint16_t","2","cm","Estimated Horizontal Position Accuracy (gpsSol.eph)."),
  MSP_FIELD("epv","uint16_t","2","cm","Estimated Vertical Position Accuracy (gpsSol.epv).")
);
MSP_MESSAGE(
  MSP_SET_TX_INFO, 0xba, ::msp::MspDir::In,
  MSP_FIELD("rssi","uint8_t","1","%","RSSI value (0-100) provided by the external source.")
);
MSP_MESSAGE(
  MSP_TX_INFO, 0xbb, ::msp::MspDir::Out,
  MSP_FIELD("rssiSource","uint8_t","1","","Enum: Source of the RSSI value (getRSSISource())."),
  MSP_FIELD("rtcDateTimeIsSet","uint8_t","1","","Boolean: 1 if the RTC has been set, 0 otherwise.")
);
MSP_MESSAGE(
  MSP_SET_RAW_RC, 0xc8, ::msp::MspDir::In,
  MSP_FIELD("rcChannels","uint16_t[]","Variable (2 channelCount)","PWM","Array of RC channel values (typically 1000-2000). Number of channels determined by payload size.")
);
MSP_MESSAGE(
  MSP_SET_RAW_GPS, 0xc9, ::msp::MspDir::In,
  MSP_FIELD("fixType","uint8_t","1","Enum","GPS fix type."),
  MSP_FIELD("numSat","uint8_t","1","Count","Number of satellites."),
  MSP_FIELD("latitude","int32_t","4","deg 1e7","Latitude."),
  MSP_FIELD("longitude","int32_t","4","deg 1e7","Longitude."),
  MSP_FIELD("altitude","int16_t","2","meters","Altitude (converted to cm internally)."),
  MSP_FIELD("speed","uint16_t","2","cm/s","Ground speed."),
  MSP_FIELD("groundCourse","uint16_t","2","???","Ground course (units unclear from code, likely degrees or deci-degrees, ignored in current code).")
);
MSP_MESSAGE(
  MSP_SET_RC_TUNING, 0xcc, ::msp::MspDir::In,
  MSP_FIELD("legacyRcRate","uint8_t","1","","Ignored."),
  MSP_FIELD("rcExpo","uint8_t","1","","Sets currentControlRateProfile->stabilized.rcExpo8."),
  MSP_FIELD("rollRate","uint8_t","1","","Sets currentControlRateProfile->stabilized.rates[FD_ROLL] (constrained)."),
  MSP_FIELD("pitchRate","uint8_t","1","","Sets currentControlRateProfile->stabilized.rates[FD_PITCH] (constrained)."),
  MSP_FIELD("yawRate","uint8_t","1","","Sets currentControlRateProfile->stabilized.rates[FD_YAW] (constrained)."),
  MSP_FIELD("dynamicThrottlePID","uint8_t","1","","Sets currentControlRateProfile->throttle.dynPID (constrained)."),
  MSP_FIELD("throttleMid","uint8_t","1","","Sets currentControlRateProfile->throttle.rcMid8."),
  MSP_FIELD("throttleExpo","uint8_t","1","","Sets currentControlRateProfile->throttle.rcExpo8."),
  MSP_FIELD("tpaBreakpoint","uint16_t","2","","Sets currentControlRateProfile->throttle.pa_breakpoint."),
  MSP_FIELD("rcYawExpo","uint8_t","1","","(Optional) Sets currentControlRateProfile->stabilized.rcYawExpo8.")
);
MSP_MESSAGE(
  MSP_ACC_CALIBRATION, 0xcd, ::msp::MspDir::In
);
MSP_MESSAGE(
  MSP_MAG_CALIBRATION, 0xce, ::msp::MspDir::In
);
MSP_MESSAGE(
  MSP_SET_MISC, 0xcf, ::msp::MspDir::In,
  MSP_FIELD("midRc","uint16_t","2","PWM","Ignored."),
  MSP_FIELD("legacyMinThrottle","uint16_t","2","-","Ignored."),
  MSP_FIELD("legacyMaxThrottle","uint16_t","2","-","Ignored."),
  MSP_FIELD("minCommand","uint16_t","2","PWM","Sets motorConfigMutable()->mincommand (constrained 0-PWM_RANGE_MAX)."),
  MSP_FIELD("failsafeThrottle","uint16_t","2","PWM","Sets currentBatteryProfileMutable->failsafe_throttle (constrained PWM_RANGE_MIN/MAX)."),
  MSP_FIELD("gpsType","uint8_t","1","Enum","Sets gpsConfigMutable()->provider (if USE_GPS)."),
  MSP_FIELD("legacyGpsBaud","uint8_t","1","-","Ignored."),
  MSP_FIELD("gpsSbasMode","uint8_t","1","Enum","Sets gpsConfigMutable()->sbasMode (if USE_GPS)."),
  MSP_FIELD("legacyMwCurrentOut","uint8_t","1","-","Ignored."),
  MSP_FIELD("rssiChannel","uint8_t","1","Index","Sets rxConfigMutable()->rssi_channel (constrained 0-MAX_SUPPORTED_RC_CHANNEL_COUNT). Updates source."),
  MSP_FIELD("reserved1","uint8_t","1","-","Ignored."),
  MSP_FIELD("magDeclination","uint16_t","2","0.1 degrees","Sets compassConfigMutable()->mag_declination = value 10 (if USE_MAG)."),
  MSP_FIELD("vbatScale","uint8_t","1","Scale / 10","Sets batteryMetersConfigMutable()->voltage.scale = value 10 (if USE_ADC)."),
  MSP_FIELD("vbatMinCell","uint8_t","1","0.1V","Sets currentBatteryProfileMutable->voltage.cellMin = value 10 (if USE_ADC)."),
  MSP_FIELD("vbatMaxCell","uint8_t","1","0.1V","Sets currentBatteryProfileMutable->voltage.cellMax = value 10 (if USE_ADC)."),
  MSP_FIELD("vbatWarningCell","uint8_t","1","0.1V","Sets currentBatteryProfileMutable->voltage.cellWarning = value 10 (if USE_ADC).")
);
MSP_MESSAGE(
  MSP_RESET_CONF, 0xd0, ::msp::MspDir::In
);
MSP_MESSAGE(
  MSP_SET_WP, 0xd1, ::msp::MspDir::In,
  MSP_FIELD("waypointIndex","uint8_t","1","Index","Index of the waypoint to set (0 to NAV_MAX_WAYPOINTS - 1)."),
  MSP_FIELD("action","uint8_t","1","Enum","Waypoint action type."),
  MSP_FIELD("latitude","int32_t","4","deg 1e7","Latitude coordinate."),
  MSP_FIELD("longitude","int32_t","4","deg 1e7","Longitude coordinate."),
  MSP_FIELD("altitude","int32_t","4","cm","Altitude coordinate."),
  MSP_FIELD("param1","uint16_t","2","Varies","Parameter 1."),
  MSP_FIELD("param2","uint16_t","2","Varies","Parameter 2."),
  MSP_FIELD("param3","uint16_t","2","Varies","Parameter 3."),
  MSP_FIELD("flag","uint8_t","1","Bitmask","Waypoint flags.")
);
MSP_MESSAGE(
  MSP_SELECT_SETTING, 0xd2, ::msp::MspDir::In,
  MSP_FIELD("profileIndex","uint8_t","1","","Index of the profile to activate (0-based).")
);
MSP_MESSAGE(
  MSP_SET_HEAD, 0xd3, ::msp::MspDir::In,
  MSP_FIELD("heading","int16_t","2","degrees","Target heading (0-359).")
);
MSP_MESSAGE(
  MSP_SET_SERVO_CONFIGURATION, 0xd4, ::msp::MspDir::In,
  MSP_FIELD("servoIndex","uint8_t","1","Index","Index of the servo to configure (0 to MAX_SUPPORTED_SERVOS - 1)."),
  MSP_FIELD("min","uint16_t","2","PWM","Minimum servo endpoint."),
  MSP_FIELD("max","uint16_t","2","PWM","Maximum servo endpoint."),
  MSP_FIELD("middle","uint16_t","2","PWM","Middle/Neutral servo position."),
  MSP_FIELD("rate","uint8_t","1","%","Servo rate/scaling."),
  MSP_FIELD("reserved1","uint8_t","1","-","Ignored."),
  MSP_FIELD("reserved2","uint8_t","1","-","Ignored."),
  MSP_FIELD("legacyForwardChan","uint8_t","1","-","Ignored."),
  MSP_FIELD("legacyReversedSources","uint32_t","4","-","Ignored.")
);
MSP_MESSAGE(
  MSP_SET_MOTOR, 0xd6, ::msp::MspDir::In,
  MSP_FIELD("motorValues","uint16_t[8]","16","PWM","Array of motor values to set when disarmed. Only affects first MAX_SUPPORTED_MOTORS.")
);
MSP_MESSAGE(
  MSP_SET_3D, 0xd9, ::msp::MspDir::In,
  MSP_FIELD("deadbandLow","uint16_t","2","PWM","Sets reversibleMotorsConfigMutable()->deadband_low."),
  MSP_FIELD("deadbandHigh","uint16_t","2","PWM","Sets reversibleMotorsConfigMutable()->deadband_high."),
  MSP_FIELD("neutral","uint16_t","2","PWM","Sets reversibleMotorsConfigMutable()->neutral.")
);
MSP_MESSAGE(
  MSP_SET_RC_DEADBAND, 0xda, ::msp::MspDir::In,
  MSP_FIELD("deadband","uint8_t","1","PWM","Sets rcControlsConfigMutable()->deadband."),
  MSP_FIELD("yawDeadband","uint8_t","1","PWM","Sets rcControlsConfigMutable()->yaw_deadband."),
  MSP_FIELD("altHoldDeadband","uint8_t","1","PWM","Sets rcControlsConfigMutable()->alt_hold_deadband."),
  MSP_FIELD("throttleDeadband","uint16_t","2","PWM","Sets rcControlsConfigMutable()->mid_throttle_deadband.")
);
MSP_MESSAGE(
  MSP_SET_RESET_CURR_PID, 0xdb, ::msp::MspDir::In
);
MSP_MESSAGE(
  MSP_SET_SENSOR_ALIGNMENT, 0xdc, ::msp::MspDir::In,
  MSP_FIELD("gyroAlign","uint8_t","1","","Ignored."),
  MSP_FIELD("accAlign","uint8_t","1","","Ignored."),
  MSP_FIELD("magAlign","uint8_t","1","","Sets compassConfigMutable()->mag_align (if USE_MAG)."),
  MSP_FIELD("opflowAlign","uint8_t","1","","Sets opticalFlowConfigMutable()->opflow_align (if USE_OPFLOW).")
);
MSP_MESSAGE(
  MSP_SET_LED_STRIP_MODECOLOR, 0xdd, ::msp::MspDir::In,
  MSP_FIELD("modeIndex","uint8_t","1","","Index of the LED mode (ledModeIndex_e or LED_MODE_COUNT for special)."),
  MSP_FIELD("directionOrSpecialIndex","uint8_t","1","","Index of the direction or special color."),
  MSP_FIELD("colorIndex","uint8_t","1","","Index of the color to assign from ledStripConfig()->colors.")
);
MSP_MESSAGE(
  MSP_SERVO_MIX_RULES, 0xf1, ::msp::MspDir::Out,
  MSP_FIELD("targetChannel","uint8_t","1","Index","Servo output channel index (0-based)."),
  MSP_FIELD("inputSource","uint8_t","1","Enum","Input source for the mix (RC chan, Roll, Pitch...). See mixerSource_t."),
  MSP_FIELD("rate","uint16_t","2","% 100?","Mixing rate/weight. Needs scaling check."),
  MSP_FIELD("speed","uint8_t","1","0-100","Speed/Slew rate limit."),
  MSP_FIELD("reserved1","uint8_t","1","-","Always 0."),
  MSP_FIELD("legacyMax","uint8_t","1","-","Always 100 (Legacy)."),
  MSP_FIELD("legacyBox","uint8_t","1","-","Always 0 (Legacy).")
);
MSP_MESSAGE(
  MSP_SET_SERVO_MIX_RULE, 0xf2, ::msp::MspDir::In,
  MSP_FIELD("ruleIndex","uint8_t","1","Index","Index of the rule to set (0 to MAX_SERVO_RULES - 1)."),
  MSP_FIELD("targetChannel","uint8_t","1","Index","Servo output channel index."),
  MSP_FIELD("inputSource","uint8_t","1","Enum","Input source for the mix."),
  MSP_FIELD("rate","uint16_t","2","% 100?","Mixing rate/weight."),
  MSP_FIELD("speed","uint8_t","1","0-100","Speed/Slew rate limit."),
  MSP_FIELD("legacyMinMax","uint16_t","2","-","Ignored."),
  MSP_FIELD("legacyBox","uint8_t","1","-","Ignored.")
);
MSP_MESSAGE(
  MSP_SET_PASSTHROUGH, 0xf5, ::msp::MspDir::InOut,
  MSP_FIELD("passthroughMode","uint8_t","1","","Type of passthrough (mspPassthroughType_e: Serial ID, Serial Function, ESC 4way)."),
  MSP_FIELD("passthroughArgument","uint8_t","1","","Argument for the mode (e.g., Serial Port Identifier, Serial Function ID). Defaults to 0 if not sent."),
  MSP_FIELD("status","uint8_t","1","","1 if passthrough started successfully, 0 on error (e.g., port not found). For 4way, returns number of ESCs found.")
);
MSP_MESSAGE(
  MSP_RTC, 0xf6, ::msp::MspDir::Out,
  MSP_FIELD("seconds","int32_t","4","Seconds","Seconds since epoch (or relative time if not set). 0 if RTC time unknown."),
  MSP_FIELD("millis","uint16_t","2","Milliseconds","Millisecond part of the time. 0 if RTC time unknown.")
);
MSP_MESSAGE(
  MSP_SET_RTC, 0xf7, ::msp::MspDir::In,
  MSP_FIELD("seconds","int32_t","4","Seconds","Seconds component of time to set."),
  MSP_FIELD("millis","uint16_t","2","Milliseconds","Millisecond component of time to set.")
);
MSP_MESSAGE(
  MSP_EEPROM_WRITE, 0xfa, ::msp::MspDir::In
);
MSP_MESSAGE(
  MSP_DEBUGMSG, 0xfd, ::msp::MspDir::Out,
  MSP_FIELD("Message Text","char[]","Variable","","NUL terminated [debug message](https://github.com/iNavFlight/inav/blob/master/docs/development/serial_printf_debugging.md) text.")
);
MSP_MESSAGE(
  MSP_DEBUG, 0xfe, ::msp::MspDir::Out,
  MSP_FIELD("debugValues","uint16_t[4]","8","","First 4 values from the debug array.")
);
MSP_MESSAGE(
  MSP_V2_FRAME, 0xff, ::msp::MspDir::In
);
MSP_MESSAGE(
  MSP2_COMMON_TZ, 0x1001, ::msp::MspDir::Out,
  MSP_FIELD("tzOffsetMinutes","int16_t","2","Minutes","Time zone offset from UTC (timeConfig()->tz_offset)."),
  MSP_FIELD("tzAutoDst","uint8_t","1","Boolean","Automatic daylight saving time enabled (timeConfig()->tz_automatic_dst).")
);
MSP_MESSAGE(
  MSP2_COMMON_SET_TZ, 0x1002, ::msp::MspDir::In,
  MSP_FIELD("tzOffsetMinutes","int16_t","2","Minutes","Sets timeConfigMutable()->tz_offset."),
  MSP_FIELD("tzOffsetMinutes","int16_t","2","Minutes","Sets timeConfigMutable()->tz_offset."),
  MSP_FIELD("tzAutoDst","uint8_t","1","Boolean","Sets timeConfigMutable()->tz_automatic_dst.")
);
MSP_MESSAGE(
  MSP2_COMMON_SETTING, 0x1003, ::msp::MspDir::InOut,
  MSP_FIELD("settingName","char[]","Variable","","Null-terminated string containing the setting name (e.g., \"gyro_main_lpf_hz\")."),
  MSP_FIELD("zeroByte","uint8_t","1","","Must be 0."),
  MSP_FIELD("settingIndex","uint16_t","2","","Absolute index of the setting."),
  MSP_FIELD("settingValue","uint8_t[]","Variable","","Raw byte value of the setting. Size depends on the setting's type (settingGetValueSize()).")
);
MSP_MESSAGE(
  MSP2_COMMON_SET_SETTING, 0x1004, ::msp::MspDir::In,
  MSP_FIELD("settingIdentifier","Varies","Variable","","Setting name (null-terminated string) OR Index (0x00 followed by uint16_t index)."),
  MSP_FIELD("settingValue","uint8_t[]","Variable","","Raw byte value to set for the setting. Size must match the setting's type.")
);
MSP_MESSAGE(
  MSP2_COMMON_MOTOR_MIXER, 0x1005, ::msp::MspDir::Out,
  MSP_FIELD("throttleWeight","uint16_t","2","Scaled (0-4000)","Throttle weight 1000, offset by 2000. (Range -2.0 to +2.0 -> 0 to 4000)."),
  MSP_FIELD("rollWeight","uint16_t","2","Scaled (0-4000)","Roll weight 1000, offset by 2000."),
  MSP_FIELD("pitchWeight","uint16_t","2","Scaled (0-4000)","Pitch weight 1000, offset by 2000."),
  MSP_FIELD("yawWeight","uint16_t","2","Scaled (0-4000)","Yaw weight 1000, offset by 2000."),
  MSP_FIELD("throttleWeight","uint16_t","2","Scaled (0-4000)","Profile 2 Throttle weight."),
  MSP_FIELD("rollWeight","uint16_t","2","Scaled (0-4000)","Profile 2 Roll weight."),
  MSP_FIELD("pitchWeight","uint16_t","2","Scaled (0-4000)","Profile 2 Pitch weight."),
  MSP_FIELD("yawWeight","uint16_t","2","Scaled (0-4000)","Profile 2 Yaw weight.")
);
MSP_MESSAGE(
  MSP2_COMMON_SET_MOTOR_MIXER, 0x1006, ::msp::MspDir::In,
  MSP_FIELD("motorIndex","uint8_t","1","Index","Index of the motor to configure (0 to MAX_SUPPORTED_MOTORS - 1)."),
  MSP_FIELD("throttleWeight","uint16_t","2","Scaled (0-4000)","Sets throttle weight from (value / 1000.0) - 2.0."),
  MSP_FIELD("rollWeight","uint16_t","2","Scaled (0-4000)","Sets roll weight from (value / 1000.0) - 2.0."),
  MSP_FIELD("pitchWeight","uint16_t","2","Scaled (0-4000)","Sets pitch weight from (value / 1000.0) - 2.0."),
  MSP_FIELD("yawWeight","uint16_t","2","Scaled (0-4000)","Sets yaw weight from (value / 1000.0) - 2.0.")
);
MSP_MESSAGE(
  MSP2_COMMON_SETTING_INFO, 0x1007, ::msp::MspDir::InOut,
  MSP_FIELD("settingName","char[]","Variable","","Null-terminated setting name."),
  MSP_FIELD("pgn","uint16_t","2","","Parameter Group Number (PGN) ID."),
  MSP_FIELD("type","uint8_t","1","","Variable type (VAR_UINT8, VAR_FLOAT, etc.)."),
  MSP_FIELD("section","uint8_t","1","","Setting section (MASTER_VALUE, PROFILE_VALUE, etc.)."),
  MSP_FIELD("mode","uint8_t","1","","Setting mode (MODE_NORMAL, MODE_LOOKUP, etc.)."),
  MSP_FIELD("minValue","int32_t","4","","Minimum allowed value (as signed 32-bit)."),
  MSP_FIELD("maxValue","uint32_t","4","","Maximum allowed value (as unsigned 32-bit)."),
  MSP_FIELD("settingIndex","uint16_t","2","","Absolute index of the setting."),
  MSP_FIELD("profileIndex","uint8_t","1","","Current profile index (if applicable, else 0)."),
  MSP_FIELD("profileCount","uint8_t","1","","Total number of profiles (if applicable, else 0)."),
  MSP_FIELD("lookupNames","char[]","Variable","","(If mode == MODE_LOOKUP) Series of null-terminated strings for each possible value from min to max."),
  MSP_FIELD("settingValue","uint8_t[]","Variable","","Current raw byte value of the setting.")
);
MSP_MESSAGE(
  MSP2_COMMON_PG_LIST, 0x1008, ::msp::MspDir::InOut,
  MSP_FIELD("pgn","uint16_t","2","","PGN ID to query. If omitted, returns all used PGNs."),
  MSP_FIELD("pgn","uint16_t","2","","Parameter Group Number (PGN) ID."),
  MSP_FIELD("startIndex","uint16_t","2","","Absolute index of the first setting in this group."),
  MSP_FIELD("endIndex","uint16_t","2","","Absolute index of the last setting in this group.")
);
MSP_MESSAGE(
  MSP2_COMMON_SERIAL_CONFIG, 0x1009, ::msp::MspDir::Out,
  MSP_FIELD("identifier","uint8_t","1","","Port identifier (serialPortIdentifier_e)."),
  MSP_FIELD("functionMask","uint32_t","4","","Bitmask of enabled functions (FUNCTION_)."),
  MSP_FIELD("mspBaudIndex","uint8_t","1","","Baud rate index for MSP function."),
  MSP_FIELD("gpsBaudIndex","uint8_t","1","","Baud rate index for GPS function."),
  MSP_FIELD("telemetryBaudIndex","uint8_t","1","","Baud rate index for Telemetry function."),
  MSP_FIELD("peripheralBaudIndex","uint8_t","1","","Baud rate index for other peripheral functions.")
);
MSP_MESSAGE(
  MSP2_COMMON_SET_SERIAL_CONFIG, 0x100a, ::msp::MspDir::In,
  MSP_FIELD("identifier","uint8_t","1","","Port identifier (serialPortIdentifier_e)."),
  MSP_FIELD("functionMask","uint32_t","4","","Bitmask of functions to enable."),
  MSP_FIELD("mspBaudIndex","uint8_t","1","","Baud rate index for MSP."),
  MSP_FIELD("gpsBaudIndex","uint8_t","1","","Baud rate index for GPS."),
  MSP_FIELD("telemetryBaudIndex","uint8_t","1","","Baud rate index for Telemetry."),
  MSP_FIELD("peripheralBaudIndex","uint8_t","1","","Baud rate index for peripherals.")
);
MSP_MESSAGE(
  MSP2_COMMON_SET_RADAR_POS, 0x100b, ::msp::MspDir::In,
  MSP_FIELD("poiIndex","uint8_t","1","Index","Index of the POI slot (0 to RADAR_MAX_POIS - 1)."),
  MSP_FIELD("state","uint8_t","1","Enum","Status of the POI (0=undefined, 1=armed, 2=lost)."),
  MSP_FIELD("latitude","int32_t","4","deg 1e7","Latitude of the POI."),
  MSP_FIELD("longitude","int32_t","4","deg 1e7","Longitude of the POI."),
  MSP_FIELD("altitude","int32_t","4","cm","Altitude of the POI."),
  MSP_FIELD("heading","int16_t","2","degrees","Heading of the POI."),
  MSP_FIELD("speed","uint16_t","2","cm/s","Speed of the POI."),
  MSP_FIELD("linkQuality","uint8_t","1","0-4","Link quality indicator.")
);
MSP_MESSAGE(
  MSP2_COMMON_SET_MSP_RC_LINK_STATS, 0x100d, ::msp::MspDir::In,
  MSP_FIELD("sublinkID","uint8_t","1","-","Sublink identifier (usually 0)."),
  MSP_FIELD("validLink","uint8_t","1","Boolean","Indicates if the link is currently valid (not in failsafe)."),
  MSP_FIELD("rssiPercent","uint8_t","1","%","Uplink RSSI percentage (0-100)."),
  MSP_FIELD("uplinkRSSI_dBm","uint8_t","1","-dBm","Uplink RSSI in dBm (sent as positive, e.g., 70 means -70dBm)."),
  MSP_FIELD("downlinkLQ","uint8_t","1","%","Downlink Link Quality (0-100)."),
  MSP_FIELD("uplinkLQ","uint8_t","1","%","Uplink Link Quality (0-100)."),
  MSP_FIELD("uplinkSNR","int8_t","1","dB","Uplink Signal-to-Noise Ratio.")
);
MSP_MESSAGE(
  MSP2_COMMON_SET_MSP_RC_INFO, 0x100e, ::msp::MspDir::In,
  MSP_FIELD("sublinkID","uint8_t","1","-","Sublink identifier (usually 0)."),
  MSP_FIELD("uplinkTxPower","uint16_t","2","mW?","Uplink transmitter power level."),
  MSP_FIELD("downlinkTxPower","uint16_t","2","mW?","Downlink transmitter power level."),
  MSP_FIELD("band","char[4]","4","-","Operating band string (e.g., \"2G4\", \"900\")."),
  MSP_FIELD("mode","char[6]","6","-","Operating mode/rate string (e.g., \"100HZ\", \"F1000\").")
);
MSP_MESSAGE(
  MSP2_SENSOR_RANGEFINDER, 0x1f01, ::msp::MspDir::In,
  MSP_FIELD("quality","uint8_t","1","0-255","Quality of the measurement."),
  MSP_FIELD("distanceMm","int32_t","4","mm","Measured distance. Negative value indicates out of range.")
);
MSP_MESSAGE(
  MSP2_SENSOR_OPTIC_FLOW, 0x1f02, ::msp::MspDir::In,
  MSP_FIELD("quality","uint8_t","1","","Quality of the measurement (0-255)."),
  MSP_FIELD("motionX","int32_t","4","","Raw integrated flow value X."),
  MSP_FIELD("motionY","int32_t","4","","Raw integrated flow value Y.")
);
MSP_MESSAGE(
  MSP2_SENSOR_GPS, 0x1f03, ::msp::MspDir::In,
  MSP_FIELD("instance","uint8_t","1","-","Sensor instance number (for multi-GPS)."),
  MSP_FIELD("gpsWeek","uint16_t","2","-","GPS week number (0xFFFF if unavailable)."),
  MSP_FIELD("msTOW","uint32_t","4","ms","Milliseconds Time of Week."),
  MSP_FIELD("fixType","uint8_t","1","Enum","Type of GPS fix."),
  MSP_FIELD("satellitesInView","uint8_t","1","Count","Number of satellites used in solution."),
  MSP_FIELD("hPosAccuracy","uint16_t","2","cm","Horizontal position accuracy estimate."),
  MSP_FIELD("vPosAccuracy","uint16_t","2","cm","Vertical position accuracy estimate."),
  MSP_FIELD("hVelAccuracy","uint16_t","2","cm/s","Horizontal velocity accuracy estimate."),
  MSP_FIELD("hdop","uint16_t","2","HDOP 100","Horizontal Dilution of Precision."),
  MSP_FIELD("longitude","int32_t","4","deg 1e7","Longitude."),
  MSP_FIELD("latitude","int32_t","4","deg 1e7","Latitude."),
  MSP_FIELD("mslAltitude","int32_t","4","cm","Altitude above Mean Sea Level."),
  MSP_FIELD("nedVelNorth","int32_t","4","cm/s","North velocity (NED frame)."),
  MSP_FIELD("nedVelEast","int32_t","4","cm/s","East velocity (NED frame)."),
  MSP_FIELD("nedVelDown","int32_t","4","cm/s","Down velocity (NED frame)."),
  MSP_FIELD("groundCourse","uint16_t","2","deg 100","Ground course (0-36000)."),
  MSP_FIELD("trueYaw","uint16_t","2","deg 100","True heading/yaw (0-36000, 65535 if unavailable)."),
  MSP_FIELD("year","uint16_t","2","-","Year (e.g., 2023)."),
  MSP_FIELD("month","uint8_t","1","-","Month (1-12)."),
  MSP_FIELD("day","uint8_t","1","-","Day of month (1-31)."),
  MSP_FIELD("hour","uint8_t","1","-","Hour (0-23)."),
  MSP_FIELD("min","uint8_t","1","-","Minute (0-59)."),
  MSP_FIELD("sec","uint8_t","1","-","Second (0-59).")
);
MSP_MESSAGE(
  MSP2_SENSOR_COMPASS, 0x1f04, ::msp::MspDir::In,
  MSP_FIELD("instance","uint8_t","1","-","Sensor instance number."),
  MSP_FIELD("timeMs","uint32_t","4","ms","Timestamp from the sensor."),
  MSP_FIELD("magX","int16_t","2","mGauss","Front component reading."),
  MSP_FIELD("magY","int16_t","2","mGauss","Right component reading."),
  MSP_FIELD("magZ","int16_t","2","mGauss","Down component reading.")
);
MSP_MESSAGE(
  MSP2_SENSOR_BAROMETER, 0x1f05, ::msp::MspDir::In,
  MSP_FIELD("instance","uint8_t","1","-","Sensor instance number."),
  MSP_FIELD("timeMs","uint32_t","4","ms","Timestamp from the sensor."),
  MSP_FIELD("pressurePa","float","4","Pa","Absolute pressure."),
  MSP_FIELD("temp","int16_t","2","0.01 deg C","Temperature.")
);
MSP_MESSAGE(
  MSP2_SENSOR_AIRSPEED, 0x1f06, ::msp::MspDir::In,
  MSP_FIELD("instance","uint8_t","1","-","Sensor instance number."),
  MSP_FIELD("timeMs","uint32_t","4","ms","Timestamp from the sensor."),
  MSP_FIELD("diffPressurePa","float","4","Pa","Differential pressure."),
  MSP_FIELD("temp","int16_t","2","0.01 deg C","Temperature.")
);
MSP_MESSAGE(
  MSP2_SENSOR_HEADTRACKER, 0x1f07, ::msp::MspDir::In
);
MSP_MESSAGE(
  MSP2_INAV_STATUS, 0x2000, ::msp::MspDir::Out,
  MSP_FIELD("cycleTime","uint16_t","2","µs","Main loop cycle time."),
  MSP_FIELD("i2cErrors","uint16_t","2","Count","I2C errors."),
  MSP_FIELD("sensorStatus","uint16_t","2","Bitmask","Sensor status bitmask."),
  MSP_FIELD("cpuLoad","uint16_t","2","%","Average system load percentage."),
  MSP_FIELD("profileAndBattProfile","uint8_t","1","Packed","Bits 0-3: Config profile index (getConfigProfile()), Bits 4-7: Battery profile index (getConfigBatteryProfile())."),
  MSP_FIELD("armingFlags","uint32_t","4","Bitmask","Full 32-bit flight controller arming flags (armingFlags)."),
  MSP_FIELD("activeModes","boxBitmask_t","sizeof(boxBitmask_t)","Bitmask","Full bitmask of active flight modes (packBoxModeFlags())."),
  MSP_FIELD("mixerProfile","uint8_t","1","Index","Current mixer profile index (getConfigMixerProfile()).")
);
MSP_MESSAGE(
  MSP2_INAV_OPTICAL_FLOW, 0x2001, ::msp::MspDir::Out,
  MSP_FIELD("quality","uint8_t","1","0-255","Raw quality indicator from the sensor (opflow.rawQuality). 0 if USE_OPFLOW disabled."),
  MSP_FIELD("flowRateX","int16_t","2","degrees/s","Optical flow rate X (roll axis) (RADIANS_TO_DEGREES(opflow.flowRate[X])). 0 if USE_OPFLOW disabled."),
  MSP_FIELD("flowRateY","int16_t","2","degrees/s","Optical flow rate Y (pitch axis) (RADIANS_TO_DEGREES(opflow.flowRate[Y])). 0 if USE_OPFLOW disabled."),
  MSP_FIELD("bodyRateX","int16_t","2","degrees/s","Compensated body rate X (roll axis) (RADIANS_TO_DEGREES(opflow.bodyRate[X])). 0 if USE_OPFLOW disabled."),
  MSP_FIELD("bodyRateY","int16_t","2","degrees/s","Compensated body rate Y (pitch axis) (RADIANS_TO_DEGREES(opflow.bodyRate[Y])). 0 if USE_OPFLOW disabled.")
);
MSP_MESSAGE(
  MSP2_INAV_ANALOG, 0x2002, ::msp::MspDir::Out,
  MSP_FIELD("batteryFlags","uint8_t","1","Bitmask","Battery status flags: Bit 0=Full on plug-in, Bit 1=Use capacity threshold, Bit 2-3=Battery State enum (getBatteryState()), Bit 4-7=Cell Count (getBatteryCellCount())."),
  MSP_FIELD("vbat","uint16_t","2","0.01V","Battery voltage (getBatteryVoltage())."),
  MSP_FIELD("amperage","uint16_t","2","0.01A","Current draw (getAmperage())."),
  MSP_FIELD("powerDraw","uint32_t","4","mW","Power draw (getPower())."),
  MSP_FIELD("mAhDrawn","uint32_t","4","mAh","Consumed capacity (getMAhDrawn())."),
  MSP_FIELD("mWhDrawn","uint32_t","4","mWh","Consumed energy (getMWhDrawn())."),
  MSP_FIELD("remainingCapacity","uint32_t","4","mAh/mWh","Estimated remaining capacity (getBatteryRemainingCapacity())."),
  MSP_FIELD("percentageRemaining","uint8_t","1","%","Estimated remaining capacity percentage (calculateBatteryPercentage())."),
  MSP_FIELD("rssi","uint16_t","2","0-1023 or %","RSSI value (getRSSI()).")
);
MSP_MESSAGE(
  MSP2_INAV_MISC, 0x2003, ::msp::MspDir::Out,
  MSP_FIELD("midRc","uint16_t","2","PWM","Mid RC value (PWM_RANGE_MIDDLE)."),
  MSP_FIELD("legacyMinThrottle","uint16_t","2","-","Always 0 (Legacy)."),
  MSP_FIELD("maxThrottle","uint16_t","2","PWM","Maximum throttle command (getMaxThrottle())."),
  MSP_FIELD("minCommand","uint16_t","2","PWM","Minimum motor command (motorConfig()->mincommand)."),
  MSP_FIELD("failsafeThrottle","uint16_t","2","PWM","Failsafe throttle level (currentBatteryProfile->failsafe_throttle)."),
  MSP_FIELD("gpsType","uint8_t","1","Enum","GPS provider type (gpsConfig()->provider). 0 if USE_GPS disabled."),
  MSP_FIELD("legacyGpsBaud","uint8_t","1","-","Always 0 (Legacy)."),
  MSP_FIELD("gpsSbasMode","uint8_t","1","Enum","GPS SBAS mode (gpsConfig()->sbasMode). 0 if USE_GPS disabled."),
  MSP_FIELD("rssiChannel","uint8_t","1","Index","RSSI channel index (1-based) (rxConfig()->rssi_channel)."),
  MSP_FIELD("magDeclination","uint16_t","2","0.1 degrees","Magnetic declination / 10 (compassConfig()->mag_declination / 10). 0 if USE_MAG disabled."),
  MSP_FIELD("vbatScale","uint16_t","2","Scale","Voltage scale (batteryMetersConfig()->voltage.scale). 0 if USE_ADC disabled."),
  MSP_FIELD("vbatSource","uint8_t","1","Enum","Voltage source (batteryMetersConfig()->voltageSource). 0 if USE_ADC disabled."),
  MSP_FIELD("cellCount","uint8_t","1","Count","Configured cell count (currentBatteryProfile->cells). 0 if USE_ADC disabled."),
  MSP_FIELD("vbatCellDetect","uint16_t","2","0.01V","Cell detection voltage (currentBatteryProfile->voltage.cellDetect). 0 if USE_ADC disabled."),
  MSP_FIELD("vbatMinCell","uint16_t","2","0.01V","Min cell voltage (currentBatteryProfile->voltage.cellMin). 0 if USE_ADC disabled."),
  MSP_FIELD("vbatMaxCell","uint16_t","2","0.01V","Max cell voltage (currentBatteryProfile->voltage.cellMax). 0 if USE_ADC disabled."),
  MSP_FIELD("vbatWarningCell","uint16_t","2","0.01V","Warning cell voltage (currentBatteryProfile->voltage.cellWarning). 0 if USE_ADC disabled."),
  MSP_FIELD("capacityValue","uint32_t","4","mAh/mWh","Battery capacity (currentBatteryProfile->capacity.value)."),
  MSP_FIELD("capacityWarning","uint32_t","4","mAh/mWh","Capacity warning threshold (currentBatteryProfile->capacity.warning)."),
  MSP_FIELD("capacityCritical","uint32_t","4","mAh/mWh","Capacity critical threshold (currentBatteryProfile->capacity.critical)."),
  MSP_FIELD("capacityUnit","uint8_t","1","Enum","Capacity unit (batteryMetersConfig()->capacity_unit).")
);
MSP_MESSAGE(
  MSP2_INAV_SET_MISC, 0x2004, ::msp::MspDir::In,
  MSP_FIELD("midRc","uint16_t","2","PWM","Ignored."),
  MSP_FIELD("legacyMinThrottle","uint16_t","2","-","Ignored."),
  MSP_FIELD("legacyMaxThrottle","uint16_t","2","-","Ignored."),
  MSP_FIELD("minCommand","uint16_t","2","PWM","Sets motorConfigMutable()->mincommand (constrained)."),
  MSP_FIELD("failsafeThrottle","uint16_t","2","PWM","Sets currentBatteryProfileMutable->failsafe_throttle (constrained)."),
  MSP_FIELD("gpsType","uint8_t","1","Enum","Sets gpsConfigMutable()->provider (if USE_GPS)."),
  MSP_FIELD("legacyGpsBaud","uint8_t","1","-","Ignored."),
  MSP_FIELD("gpsSbasMode","uint8_t","1","Enum","Sets gpsConfigMutable()->sbasMode (if USE_GPS)."),
  MSP_FIELD("rssiChannel","uint8_t","1","Index","Sets rxConfigMutable()->rssi_channel (constrained). Updates source."),
  MSP_FIELD("magDeclination","uint16_t","2","0.1 degrees","Sets compassConfigMutable()->mag_declination = value 10 (if USE_MAG)."),
  MSP_FIELD("vbatScale","uint16_t","2","Scale","Sets batteryMetersConfigMutable()->voltage.scale (if USE_ADC)."),
  MSP_FIELD("vbatSource","uint8_t","1","Enum","Sets batteryMetersConfigMutable()->voltageSource (if USE_ADC, validated)."),
  MSP_FIELD("cellCount","uint8_t","1","Count","Sets currentBatteryProfileMutable->cells (if USE_ADC)."),
  MSP_FIELD("vbatCellDetect","uint16_t","2","0.01V","Sets currentBatteryProfileMutable->voltage.cellDetect (if USE_ADC)."),
  MSP_FIELD("vbatMinCell","uint16_t","2","0.01V","Sets currentBatteryProfileMutable->voltage.cellMin (if USE_ADC)."),
  MSP_FIELD("vbatMaxCell","uint16_t","2","0.01V","Sets currentBatteryProfileMutable->voltage.cellMax (if USE_ADC)."),
  MSP_FIELD("vbatWarningCell","uint16_t","2","0.01V","Sets currentBatteryProfileMutable->voltage.cellWarning (if USE_ADC)."),
  MSP_FIELD("capacityValue","uint32_t","4","mAh/mWh","Sets currentBatteryProfileMutable->capacity.value."),
  MSP_FIELD("capacityWarning","uint32_t","4","mAh/mWh","Sets currentBatteryProfileMutable->capacity.warning."),
  MSP_FIELD("capacityCritical","uint32_t","4","mAh/mWh","Sets currentBatteryProfileMutable->capacity.critical."),
  MSP_FIELD("capacityUnit","uint8_t","1","Enum","Sets batteryMetersConfigMutable()->capacity_unit (validated). Updates OSD energy unit if changed.")
);
MSP_MESSAGE(
  MSP2_INAV_BATTERY_CONFIG, 0x2005, ::msp::MspDir::Out,
  MSP_FIELD("vbatScale","uint16_t","2","Scale","Voltage scale (batteryMetersConfig()->voltage.scale)."),
  MSP_FIELD("vbatSource","uint8_t","1","Enum","Voltage source (batteryMetersConfig()->voltageSource)."),
  MSP_FIELD("cellCount","uint8_t","1","Count","Configured cell count (currentBatteryProfile->cells)."),
  MSP_FIELD("vbatCellDetect","uint16_t","2","0.01V","Cell detection voltage (currentBatteryProfile->voltage.cellDetect)."),
  MSP_FIELD("vbatMinCell","uint16_t","2","0.01V","Min cell voltage (currentBatteryProfile->voltage.cellMin)."),
  MSP_FIELD("vbatMaxCell","uint16_t","2","0.01V","Max cell voltage (currentBatteryProfile->voltage.cellMax)."),
  MSP_FIELD("vbatWarningCell","uint16_t","2","0.01V","Warning cell voltage (currentBatteryProfile->voltage.cellWarning)."),
  MSP_FIELD("currentOffset","uint16_t","2","mV","Current sensor offset (batteryMetersConfig()->current.offset)."),
  MSP_FIELD("currentScale","uint16_t","2","Scale","Current sensor scale (batteryMetersConfig()->current.scale)."),
  MSP_FIELD("capacityValue","uint32_t","4","mAh/mWh","Battery capacity (currentBatteryProfile->capacity.value)."),
  MSP_FIELD("capacityWarning","uint32_t","4","mAh/mWh","Capacity warning threshold (currentBatteryProfile->capacity.warning)."),
  MSP_FIELD("capacityCritical","uint32_t","4","mAh/mWh","Capacity critical threshold (currentBatteryProfile->capacity.critical)."),
  MSP_FIELD("capacityUnit","uint8_t","1","Enum","Capacity unit (batteryMetersConfig()->capacity_unit).")
);
MSP_MESSAGE(
  MSP2_INAV_SET_BATTERY_CONFIG, 0x2006, ::msp::MspDir::In,
  MSP_FIELD("vbatScale","uint16_t","2","Scale","Sets batteryMetersConfigMutable()->voltage.scale (if USE_ADC)."),
  MSP_FIELD("vbatSource","uint8_t","1","Enum","Sets batteryMetersConfigMutable()->voltageSource (if USE_ADC, validated)."),
  MSP_FIELD("cellCount","uint8_t","1","Count","Sets currentBatteryProfileMutable->cells (if USE_ADC)."),
  MSP_FIELD("vbatCellDetect","uint16_t","2","0.01V","Sets currentBatteryProfileMutable->voltage.cellDetect (if USE_ADC)."),
  MSP_FIELD("vbatMinCell","uint16_t","2","0.01V","Sets currentBatteryProfileMutable->voltage.cellMin (if USE_ADC)."),
  MSP_FIELD("vbatMaxCell","uint16_t","2","0.01V","Sets currentBatteryProfileMutable->voltage.cellMax (if USE_ADC)."),
  MSP_FIELD("vbatWarningCell","uint16_t","2","0.01V","Sets currentBatteryProfileMutable->voltage.cellWarning (if USE_ADC)."),
  MSP_FIELD("currentOffset","uint16_t","2","mV","Sets batteryMetersConfigMutable()->current.offset."),
  MSP_FIELD("currentScale","uint16_t","2","Scale","Sets batteryMetersConfigMutable()->current.scale."),
  MSP_FIELD("capacityValue","uint32_t","4","mAh/mWh","Sets currentBatteryProfileMutable->capacity.value."),
  MSP_FIELD("capacityWarning","uint32_t","4","mAh/mWh","Sets currentBatteryProfileMutable->capacity.warning."),
  MSP_FIELD("capacityCritical","uint32_t","4","mAh/mWh","Sets currentBatteryProfileMutable->capacity.critical."),
  MSP_FIELD("capacityUnit","uint8_t","1","Enum","Sets batteryMetersConfigMutable()->capacity_unit (validated). Updates OSD energy unit if changed.")
);
MSP_MESSAGE(
  MSP2_INAV_RATE_PROFILE, 0x2007, ::msp::MspDir::Out,
  MSP_FIELD("throttleMid","uint8_t","1","","Throttle Midpoint (currentControlRateProfile->throttle.rcMid8)."),
  MSP_FIELD("throttleExpo","uint8_t","1","","Throttle Expo (currentControlRateProfile->throttle.rcExpo8)."),
  MSP_FIELD("dynamicThrottlePID","uint8_t","1","","TPA value (currentControlRateProfile->throttle.dynPID)."),
  MSP_FIELD("tpaBreakpoint","uint16_t","2","","TPA breakpoint (currentControlRateProfile->throttle.pa_breakpoint)."),
  MSP_FIELD("stabRcExpo","uint8_t","1","","Stabilized Roll/Pitch Expo (currentControlRateProfile->stabilized.rcExpo8)."),
  MSP_FIELD("stabRcYawExpo","uint8_t","1","","Stabilized Yaw Expo (currentControlRateProfile->stabilized.rcYawExpo8)."),
  MSP_FIELD("stabRollRate","uint8_t","1","","Stabilized Roll Rate (currentControlRateProfile->stabilized.rates[FD_ROLL])."),
  MSP_FIELD("stabPitchRate","uint8_t","1","","Stabilized Pitch Rate (currentControlRateProfile->stabilized.rates[FD_PITCH])."),
  MSP_FIELD("stabYawRate","uint8_t","1","","Stabilized Yaw Rate (currentControlRateProfile->stabilized.rates[FD_YAW])."),
  MSP_FIELD("manualRcExpo","uint8_t","1","","Manual Roll/Pitch Expo (currentControlRateProfile->manual.rcExpo8)."),
  MSP_FIELD("manualRcYawExpo","uint8_t","1","","Manual Yaw Expo (currentControlRateProfile->manual.rcYawExpo8)."),
  MSP_FIELD("manualRollRate","uint8_t","1","","Manual Roll Rate (currentControlRateProfile->manual.rates[FD_ROLL])."),
  MSP_FIELD("manualPitchRate","uint8_t","1","","Manual Pitch Rate (currentControlRateProfile->manual.rates[FD_PITCH])."),
  MSP_FIELD("manualYawRate","uint8_t","1","","Manual Yaw Rate (currentControlRateProfile->manual.rates[FD_YAW]).")
);
MSP_MESSAGE(
  MSP2_INAV_SET_RATE_PROFILE, 0x2008, ::msp::MspDir::In,
  MSP_FIELD("throttleMid","uint8_t","1","","Sets currentControlRateProfile_p->throttle.rcMid8."),
  MSP_FIELD("throttleExpo","uint8_t","1","","Sets currentControlRateProfile_p->throttle.rcExpo8."),
  MSP_FIELD("dynamicThrottlePID","uint8_t","1","","Sets currentControlRateProfile_p->throttle.dynPID."),
  MSP_FIELD("tpaBreakpoint","uint16_t","2","","Sets currentControlRateProfile_p->throttle.pa_breakpoint."),
  MSP_FIELD("stabRcExpo","uint8_t","1","","Sets currentControlRateProfile_p->stabilized.rcExpo8."),
  MSP_FIELD("stabRcYawExpo","uint8_t","1","","Sets currentControlRateProfile_p->stabilized.rcYawExpo8."),
  MSP_FIELD("stabRollRate","uint8_t","1","","Sets currentControlRateProfile_p->stabilized.rates[FD_ROLL] (constrained)."),
  MSP_FIELD("stabPitchRate","uint8_t","1","","Sets currentControlRateProfile_p->stabilized.rates[FD_PITCH] (constrained)."),
  MSP_FIELD("stabYawRate","uint8_t","1","","Sets currentControlRateProfile_p->stabilized.rates[FD_YAW] (constrained)."),
  MSP_FIELD("manualRcExpo","uint8_t","1","","Sets currentControlRateProfile_p->manual.rcExpo8."),
  MSP_FIELD("manualRcYawExpo","uint8_t","1","","Sets currentControlRateProfile_p->manual.rcYawExpo8."),
  MSP_FIELD("manualRollRate","uint8_t","1","","Sets currentControlRateProfile_p->manual.rates[FD_ROLL] (constrained)."),
  MSP_FIELD("manualPitchRate","uint8_t","1","","Sets currentControlRateProfile_p->manual.rates[FD_PITCH] (constrained)."),
  MSP_FIELD("manualYawRate","uint8_t","1","","Sets currentControlRateProfile_p->manual.rates[FD_YAW] (constrained).")
);
MSP_MESSAGE(
  MSP2_INAV_AIR_SPEED, 0x2009, ::msp::MspDir::Out,
  MSP_FIELD("airspeed","uint32_t","4","cm/s","Estimated/measured airspeed (getAirspeedEstimate()). 0 if USE_PITOT disabled or no valid data.")
);
MSP_MESSAGE(
  MSP2_INAV_OUTPUT_MAPPING, 0x200a, ::msp::MspDir::Out,
  MSP_FIELD("usageFlags","uint8_t","1","","Timer usage flags (truncated). TIM_USE_MOTOR or TIM_USE_SERVO.")
);
MSP_MESSAGE(
  MSP2_INAV_MC_BRAKING, 0x200b, ::msp::MspDir::Out,
  MSP_FIELD("brakingSpeedThreshold","uint16_t","2","cm/s","Speed above which braking engages (navConfig()->mc.braking_speed_threshold)."),
  MSP_FIELD("brakingDisengageSpeed","uint16_t","2","cm/s","Speed below which braking disengages (navConfig()->mc.braking_disengage_speed)."),
  MSP_FIELD("brakingTimeout","uint16_t","2","ms","Timeout before braking force reduces (navConfig()->mc.braking_timeout)."),
  MSP_FIELD("brakingBoostFactor","uint8_t","1","%","Boost factor applied during braking (navConfig()->mc.braking_boost_factor)."),
  MSP_FIELD("brakingBoostTimeout","uint16_t","2","ms","Timeout for the boost factor (navConfig()->mc.braking_boost_timeout)."),
  MSP_FIELD("brakingBoostSpeedThreshold","uint16_t","2","cm/s","Speed threshold for boost engagement (navConfig()->mc.braking_boost_speed_threshold)."),
  MSP_FIELD("brakingBoostDisengageSpeed","uint16_t","2","cm/s","Speed threshold for boost disengagement (navConfig()->mc.braking_boost_disengage_speed)."),
  MSP_FIELD("brakingBankAngle","uint8_t","1","degrees","Maximum bank angle allowed during braking (navConfig()->mc.braking_bank_angle).")
);
MSP_MESSAGE(
  MSP2_INAV_SET_MC_BRAKING, 0x200c, ::msp::MspDir::In,
  MSP_FIELD("brakingSpeedThreshold","uint16_t","2","cm/s","Sets navConfigMutable()->mc.braking_speed_threshold."),
  MSP_FIELD("brakingDisengageSpeed","uint16_t","2","cm/s","Sets navConfigMutable()->mc.braking_disengage_speed."),
  MSP_FIELD("brakingTimeout","uint16_t","2","ms","Sets navConfigMutable()->mc.braking_timeout."),
  MSP_FIELD("brakingBoostFactor","uint8_t","1","%","Sets navConfigMutable()->mc.braking_boost_factor."),
  MSP_FIELD("brakingBoostTimeout","uint16_t","2","ms","Sets navConfigMutable()->mc.braking_boost_timeout."),
  MSP_FIELD("brakingBoostSpeedThreshold","uint16_t","2","cm/s","Sets navConfigMutable()->mc.braking_boost_speed_threshold."),
  MSP_FIELD("brakingBoostDisengageSpeed","uint16_t","2","cm/s","Sets navConfigMutable()->mc.braking_boost_disengage_speed."),
  MSP_FIELD("brakingBankAngle","uint8_t","1","degrees","Sets navConfigMutable()->mc.braking_bank_angle.")
);
MSP_MESSAGE(
  MSP2_INAV_OUTPUT_MAPPING_EXT, 0x200d, ::msp::MspDir::Out,
  MSP_FIELD("timerId","uint8_t","1","","Hardware timer identifier (e.g., TIM1, TIM2). Value depends on target."),
  MSP_FIELD("usageFlags","uint8_t","1","","Timer usage flags (truncated). TIM_USE_MOTOR or TIM_USE_SERVO.")
);
MSP_MESSAGE(
  MSP2_INAV_TIMER_OUTPUT_MODE, 0x200e, ::msp::MspDir::InOut,
  MSP_FIELD("timerIndex","uint8_t","1","","Index of the hardware timer definition (0 to HARDWARE_TIMER_DEFINITION_COUNT - 1)."),
  MSP_FIELD("timerIndex","uint8_t","1","","Timer index."),
  MSP_FIELD("outputMode","uint8_t","1","","Output mode override (TIMER_OUTPUT_MODE_ enum)."),
  MSP_FIELD("timerIndex","uint8_t","1","","Timer index requested."),
  MSP_FIELD("outputMode","uint8_t","1","","Output mode override for the requested timer.")
);
MSP_MESSAGE(
  MSP2_INAV_SET_TIMER_OUTPUT_MODE, 0x200f, ::msp::MspDir::In,
  MSP_FIELD("timerIndex","uint8_t","1","","Index of the hardware timer definition."),
  MSP_FIELD("outputMode","uint8_t","1","","Output mode override (TIMER_OUTPUT_MODE_ enum) to set.")
);
MSP_MESSAGE(
  MSP2_INAV_MIXER, 0x2010, ::msp::MspDir::Out,
  MSP_FIELD("motorDirectionInverted","uint8_t","1","","Boolean: 1 if motor direction is reversed globally (mixerConfig()->motorDirectionInverted)."),
  MSP_FIELD("reserved1","uint8_t","1","","Always 0 (Was yaw jump prevention limit)."),
  MSP_FIELD("motorStopOnLow","uint8_t","1","","Boolean: 1 if motors stop at minimum throttle (mixerConfig()->motorstopOnLow)."),
  MSP_FIELD("platformType","uint8_t","1","","Enum (platformType_e): Vehicle platform type (Multirotor, Airplane, etc.) (mixerConfig()->platformType)."),
  MSP_FIELD("hasFlaps","uint8_t","1","","Boolean: 1 if the current mixer configuration includes flaps (mixerConfig()->hasFlaps)."),
  MSP_FIELD("appliedMixerPreset","uint16_t","2","","Enum (mixerPreset_e): Mixer preset currently applied (mixerConfig()->appliedMixerPreset)."),
  MSP_FIELD("maxMotors","uint8_t","1","","Constant: Maximum motors supported (MAX_SUPPORTED_MOTORS)."),
  MSP_FIELD("maxServos","uint8_t","1","","Constant: Maximum servos supported (MAX_SUPPORTED_SERVOS).")
);
MSP_MESSAGE(
  MSP2_INAV_SET_MIXER, 0x2011, ::msp::MspDir::In,
  MSP_FIELD("motorDirectionInverted","uint8_t","1","","Sets mixerConfigMutable()->motorDirectionInverted."),
  MSP_FIELD("reserved1","uint8_t","1","","Ignored."),
  MSP_FIELD("motorStopOnLow","uint8_t","1","","Sets mixerConfigMutable()->motorstopOnLow."),
  MSP_FIELD("platformType","uint8_t","1","","Sets mixerConfigMutable()->platformType."),
  MSP_FIELD("hasFlaps","uint8_t","1","","Sets mixerConfigMutable()->hasFlaps."),
  MSP_FIELD("appliedMixerPreset","uint16_t","2","","Sets mixerConfigMutable()->appliedMixerPreset."),
  MSP_FIELD("maxMotors","uint8_t","1","","Ignored."),
  MSP_FIELD("maxServos","uint8_t","1","","Ignored.")
);
MSP_MESSAGE(
  MSP2_INAV_OSD_LAYOUTS, 0x2012, ::msp::MspDir::InOut,
  MSP_FIELD("layoutIndex","uint8_t","1","","Index of the OSD layout (0 to OSD_LAYOUT_COUNT - 1)."),
  MSP_FIELD("layoutIndex","uint8_t","1","","Index of the OSD layout."),
  MSP_FIELD("itemIndex","uint16_t","2","","Index of the OSD item (OSD_ITEM_ enum, 0 to OSD_ITEM_COUNT - 1)."),
  MSP_FIELD("layoutCount","uint8_t","1","","Number of OSD layouts (OSD_LAYOUT_COUNT)."),
  MSP_FIELD("itemCount","uint8_t","1","","Number of OSD items per layout (OSD_ITEM_COUNT)."),
  MSP_FIELD("itemPositions","uint16_t[OSD_ITEM_COUNT]","OSD_ITEM_COUNT 2","","Packed X/Y positions for all items in the requested layout."),
  MSP_FIELD("itemPosition","uint16_t","2","","Packed X/Y position for the requested item in the requested layout.")
);
MSP_MESSAGE(
  MSP2_INAV_OSD_SET_LAYOUT_ITEM, 0x2013, ::msp::MspDir::In,
  MSP_FIELD("layoutIndex","uint8_t","1","Index","Index of the OSD layout (0 to OSD_LAYOUT_COUNT - 1)."),
  MSP_FIELD("itemIndex","uint8_t","1","Index","Index of the OSD item (OSD_ITEM_ enum).")
);
MSP_MESSAGE(
  MSP2_INAV_OSD_ALARMS, 0x2014, ::msp::MspDir::Out,
  MSP_FIELD("rssiAlarm","uint8_t","1","%","RSSI alarm threshold (osdConfig()->rssi_alarm)."),
  MSP_FIELD("timerAlarm","uint16_t","2","seconds","Timer alarm threshold (osdConfig()->time_alarm)."),
  MSP_FIELD("altAlarm","uint16_t","2","meters","Altitude alarm threshold (osdConfig()->alt_alarm)."),
  MSP_FIELD("distAlarm","uint16_t","2","meters","Distance alarm threshold (osdConfig()->dist_alarm)."),
  MSP_FIELD("negAltAlarm","uint16_t","2","meters","Negative altitude alarm threshold (osdConfig()->neg_alt_alarm)."),
  MSP_FIELD("gForceAlarm","uint16_t","2","G 1000","G-force alarm threshold (osdConfig()->gforce_alarm 1000)."),
  MSP_FIELD("gForceAxisMinAlarm","int16_t","2","G 1000","Min G-force per-axis alarm (osdConfig()->gforce_axis_alarm_min 1000)."),
  MSP_FIELD("gForceAxisMaxAlarm","int16_t","2","G 1000","Max G-force per-axis alarm (osdConfig()->gforce_axis_alarm_max 1000)."),
  MSP_FIELD("currentAlarm","uint8_t","1","0.1 A ?","Current draw alarm threshold (osdConfig()->current_alarm). Units may need verification."),
  MSP_FIELD("imuTempMinAlarm","uint16_t","2","degrees C","Min IMU temperature alarm (osdConfig()->imu_temp_alarm_min)."),
  MSP_FIELD("imuTempMaxAlarm","uint16_t","2","degrees C","Max IMU temperature alarm (osdConfig()->imu_temp_alarm_max)."),
  MSP_FIELD("baroTempMinAlarm","uint16_t","2","degrees C","Min Baro temperature alarm (osdConfig()->baro_temp_alarm_min). 0 if USE_BARO disabled."),
  MSP_FIELD("baroTempMaxAlarm","uint16_t","2","degrees C","Max Baro temperature alarm (osdConfig()->baro_temp_alarm_max). 0 if USE_BARO disabled."),
  MSP_FIELD("adsbWarnDistance","uint16_t","2","meters","ADSB warning distance (osdConfig()->adsb_distance_warning). 0 if USE_ADSB disabled."),
  MSP_FIELD("adsbAlertDistance","uint16_t","2","meters","ADSB alert distance (osdConfig()->adsb_distance_alert). 0 if USE_ADSB disabled.")
);
MSP_MESSAGE(
  MSP2_INAV_OSD_SET_ALARMS, 0x2015, ::msp::MspDir::In,
  MSP_FIELD("rssiAlarm","uint8_t","1","%","Sets osdConfigMutable()->rssi_alarm."),
  MSP_FIELD("timerAlarm","uint16_t","2","seconds","Sets osdConfigMutable()->time_alarm."),
  MSP_FIELD("altAlarm","uint16_t","2","meters","Sets osdConfigMutable()->alt_alarm."),
  MSP_FIELD("distAlarm","uint16_t","2","meters","Sets osdConfigMutable()->dist_alarm."),
  MSP_FIELD("negAltAlarm","uint16_t","2","meters","Sets osdConfigMutable()->neg_alt_alarm."),
  MSP_FIELD("gForceAlarm","uint16_t","2","G 1000","Sets osdConfigMutable()->gforce_alarm = value / 1000.0f."),
  MSP_FIELD("gForceAxisMinAlarm","int16_t","2","G 1000","Sets osdConfigMutable()->gforce_axis_alarm_min = value / 1000.0f."),
  MSP_FIELD("gForceAxisMaxAlarm","int16_t","2","G 1000","Sets osdConfigMutable()->gforce_axis_alarm_max = value / 1000.0f."),
  MSP_FIELD("currentAlarm","uint8_t","1","0.1 A ?","Sets osdConfigMutable()->current_alarm."),
  MSP_FIELD("imuTempMinAlarm","uint16_t","2","degrees C","Sets osdConfigMutable()->imu_temp_alarm_min."),
  MSP_FIELD("imuTempMaxAlarm","uint16_t","2","degrees C","Sets osdConfigMutable()->imu_temp_alarm_max."),
  MSP_FIELD("baroTempMinAlarm","uint16_t","2","degrees C","Sets osdConfigMutable()->baro_temp_alarm_min (if USE_BARO)."),
  MSP_FIELD("baroTempMaxAlarm","uint16_t","2","degrees C","Sets osdConfigMutable()->baro_temp_alarm_max (if USE_BARO).")
);
MSP_MESSAGE(
  MSP2_INAV_OSD_PREFERENCES, 0x2016, ::msp::MspDir::Out,
  MSP_FIELD("videoSystem","uint8_t","1","","Enum: Video system (Auto/PAL/NTSC) (osdConfig()->video_system)."),
  MSP_FIELD("mainVoltageDecimals","uint8_t","1","","Count: Decimal places for main voltage display (osdConfig()->main_voltage_decimals)."),
  MSP_FIELD("ahiReverseRoll","uint8_t","1","","Boolean: Reverse roll direction on Artificial Horizon (osdConfig()->ahi_reverse_roll)."),
  MSP_FIELD("crosshairsStyle","uint8_t","1","","Enum: Style of the center crosshairs (osdConfig()->crosshairs_style)."),
  MSP_FIELD("leftSidebarScroll","uint8_t","1","","Boolean: Enable scrolling for left sidebar (osdConfig()->left_sidebar_scroll)."),
  MSP_FIELD("rightSidebarScroll","uint8_t","1","","Boolean: Enable scrolling for right sidebar (osdConfig()->right_sidebar_scroll)."),
  MSP_FIELD("sidebarScrollArrows","uint8_t","1","","Boolean: Show arrows for scrollable sidebars (osdConfig()->sidebar_scroll_arrows)."),
  MSP_FIELD("units","uint8_t","1","","Enum: Measurement units (Metric/Imperial) (osdConfig()->units)."),
  MSP_FIELD("statsEnergyUnit","uint8_t","1","","Enum: Unit for energy display in post-flight stats (osdConfig()->stats_energy_unit).")
);
MSP_MESSAGE(
  MSP2_INAV_OSD_SET_PREFERENCES, 0x2017, ::msp::MspDir::In,
  MSP_FIELD("videoSystem","uint8_t","1","","Sets osdConfigMutable()->video_system."),
  MSP_FIELD("mainVoltageDecimals","uint8_t","1","","Sets osdConfigMutable()->main_voltage_decimals."),
  MSP_FIELD("ahiReverseRoll","uint8_t","1","","Sets osdConfigMutable()->ahi_reverse_roll."),
  MSP_FIELD("crosshairsStyle","uint8_t","1","","Sets osdConfigMutable()->crosshairs_style."),
  MSP_FIELD("leftSidebarScroll","uint8_t","1","","Sets osdConfigMutable()->left_sidebar_scroll."),
  MSP_FIELD("rightSidebarScroll","uint8_t","1","","Sets osdConfigMutable()->right_sidebar_scroll."),
  MSP_FIELD("sidebarScrollArrows","uint8_t","1","","Sets osdConfigMutable()->sidebar_scroll_arrows."),
  MSP_FIELD("units","uint8_t","1","","Sets osdConfigMutable()->units."),
  MSP_FIELD("statsEnergyUnit","uint8_t","1","","Sets osdConfigMutable()->stats_energy_unit.")
);
MSP_MESSAGE(
  MSP2_INAV_SELECT_BATTERY_PROFILE, 0x2018, ::msp::MspDir::In,
  MSP_FIELD("batteryProfileIndex","uint8_t","1","","Index of the battery profile to activate (0-based).")
);
MSP_MESSAGE(
  MSP2_INAV_DEBUG, 0x2019, ::msp::MspDir::Out,
  MSP_FIELD("debugValues","uint32_t[DEBUG32_VALUE_COUNT]","DEBUG32_VALUE_COUNT 4","","Values from the debug array (typically 8 values).")
);
MSP_MESSAGE(
  MSP2_BLACKBOX_CONFIG, 0x201a, ::msp::MspDir::Out,
  MSP_FIELD("blackboxSupported","uint8_t","1","","Boolean: 1 if Blackbox is supported (USE_BLACKBOX), 0 otherwise."),
  MSP_FIELD("blackboxDevice","uint8_t","1","","Enum (blackboxDevice_e): Target device for logging (blackboxConfig()->device). 0 if not supported."),
  MSP_FIELD("blackboxRateNum","uint16_t","2","","Numerator for logging rate divider (blackboxConfig()->rate_num). 0 if not supported."),
  MSP_FIELD("blackboxRateDenom","uint16_t","2","","Denominator for logging rate divider (blackboxConfig()->rate_denom). 0 if not supported."),
  MSP_FIELD("blackboxIncludeFlags","uint32_t","4","","Bitmask: Flags for fields included/excluded from logging (blackboxConfig()->includeFlags).")
);
MSP_MESSAGE(
  MSP2_SET_BLACKBOX_CONFIG, 0x201b, ::msp::MspDir::In,
  MSP_FIELD("blackboxDevice","uint8_t","1","","Sets blackboxConfigMutable()->device."),
  MSP_FIELD("blackboxRateNum","uint16_t","2","","Sets blackboxConfigMutable()->rate_num."),
  MSP_FIELD("blackboxRateDenom","uint16_t","2","","Sets blackboxConfigMutable()->rate_denom."),
  MSP_FIELD("blackboxIncludeFlags","uint32_t","4","","Sets blackboxConfigMutable()->includeFlags.")
);
MSP_MESSAGE(
  MSP2_INAV_TEMP_SENSOR_CONFIG, 0x201c, ::msp::MspDir::Out,
  MSP_FIELD("type","uint8_t","1","","Enum (tempSensorType_e): Type of the temperature sensor."),
  MSP_FIELD("address","uint64_t","8","","Sensor address/ID (e.g., for 1-Wire sensors)."),
  MSP_FIELD("alarmMin","uint16_t","2","","Min temperature alarm threshold (degrees C)."),
  MSP_FIELD("alarmMax","uint16_t","2","","Max temperature alarm threshold (degrees C)."),
  MSP_FIELD("osdSymbol","uint8_t","1","","Index: OSD symbol to use for this sensor (0 to TEMP_SENSOR_SYM_COUNT)."),
  MSP_FIELD("label","char[TEMPERATURE_LABEL_LEN]","TEMPERATURE_LABEL_LEN","","User-defined label for the sensor.")
);
MSP_MESSAGE(
  MSP2_INAV_SET_TEMP_SENSOR_CONFIG, 0x201d, ::msp::MspDir::In,
  MSP_FIELD("type","uint8_t","1","","Sets sensor type."),
  MSP_FIELD("address","uint64_t","8","","Sets sensor address/ID."),
  MSP_FIELD("alarmMin","uint16_t","2","","Sets min alarm threshold."),
  MSP_FIELD("alarmMax","uint16_t","2","","Sets max alarm threshold."),
  MSP_FIELD("osdSymbol","uint8_t","1","","Sets OSD symbol index (validated)."),
  MSP_FIELD("label","char[TEMPERATURE_LABEL_LEN]","TEMPERATURE_LABEL_LEN","","Sets sensor label (converted to uppercase).")
);
MSP_MESSAGE(
  MSP2_INAV_TEMPERATURES, 0x201e, ::msp::MspDir::Out,
  MSP_FIELD("temperature","int16_t[]","Variable","degrees C","Per-sensor temperatures. Each entry is degrees Celsius multiplied by 10 (or -1000 if unavailable).")
);
MSP_MESSAGE(
  MSP_SIMULATOR, 0x201f, ::msp::MspDir::InOut,
  MSP_FIELD("simulatorVersion","uint8_t","1","","Version of the simulator protocol (SIMULATOR_MSP_VERSION)."),
  MSP_FIELD("hitlFlags","uint8_t","1","","Bitmask: Options for HITL (HITL_ flags)."),
  MSP_FIELD("gpsFixType","uint8_t","1","","(If HITL_HAS_NEW_GPS_DATA) Simulated GPS fix type."),
  MSP_FIELD("gpsNumSat","uint8_t","1","","(If HITL_HAS_NEW_GPS_DATA) Simulated satellite count."),
  MSP_FIELD("gpsLat","uint32_t","4","","(If HITL_HAS_NEW_GPS_DATA) Simulated latitude (1e7 deg)."),
  MSP_FIELD("gpsLon","uint32_t","4","","(If HITL_HAS_NEW_GPS_DATA) Simulated longitude (1e7 deg)."),
  MSP_FIELD("gpsAlt","uint32_t","4","","(If HITL_HAS_NEW_GPS_DATA) Simulated altitude (cm)."),
  MSP_FIELD("gpsSpeed","uint16_t","2","","(If HITL_HAS_NEW_GPS_DATA) Simulated ground speed (cm/s)."),
  MSP_FIELD("gpsCourse","uint16_t","2","","(If HITL_HAS_NEW_GPS_DATA) Simulated ground course (deci-deg)."),
  MSP_FIELD("gpsVelN","int16_t","2","","(If HITL_HAS_NEW_GPS_DATA) Simulated North velocity (cm/s)."),
  MSP_FIELD("gpsVelE","int16_t","2","","(If HITL_HAS_NEW_GPS_DATA) Simulated East velocity (cm/s)."),
  MSP_FIELD("gpsVelD","int16_t","2","","(If HITL_HAS_NEW_GPS_DATA) Simulated Down velocity (cm/s)."),
  MSP_FIELD("imuRoll","int16_t","2","","(If NOT HITL_USE_IMU) Simulated Roll (deci-deg)."),
  MSP_FIELD("imuPitch","int16_t","2","","(If NOT HITL_USE_IMU) Simulated Pitch (deci-deg)."),
  MSP_FIELD("imuYaw","int16_t","2","","(If NOT HITL_USE_IMU) Simulated Yaw (deci-deg)."),
  MSP_FIELD("vbat","uint8_t","1","","(If HITL_EXT_BATTERY_VOLTAGE) Simulated battery voltage (0.1V units)."),
  MSP_FIELD("airspeed","uint16_t","2","","(If HITL_AIRSPEED) Simulated airspeed (cm/s)."),
  MSP_FIELD("extFlags","uint8_t","1","","(If HITL_EXTENDED_FLAGS) Additional flags (upper 8 bits)."),
  MSP_FIELD("stabilizedRoll","uint16_t","2","","Stabilized Roll command output (-500 to 500)."),
  MSP_FIELD("stabilizedPitch","uint16_t","2","","Stabilized Pitch command output (-500 to 500)."),
  MSP_FIELD("stabilizedYaw","uint16_t","2","","Stabilized Yaw command output (-500 to 500)."),
  MSP_FIELD("stabilizedThrottle","uint16_t","2","","Stabilized Throttle command output (-500 to 500 if armed, else -500)."),
  MSP_FIELD("debugFlags","uint8_t","1","","Packed flags: Debug index (0-7), Platform type, Armed state, OSD feature status."),
  MSP_FIELD("debugValue","uint32_t","4","","Current debug value (debug[simulatorData.debugIndex])."),
  MSP_FIELD("attitudeRoll","int16_t","2","","Current estimated Roll (deci-deg)."),
  MSP_FIELD("attitudePitch","int16_t","2","","Current estimated Pitch (deci-deg)."),
  MSP_FIELD("attitudeYaw","int16_t","2","","Current estimated Yaw (deci-deg)."),
  MSP_FIELD("osdHeader","uint8_t","1","","OSD RLE Header (255)."),
  MSP_FIELD("osdRows","uint8_t","1","","(If OSD supported) Number of OSD rows."),
  MSP_FIELD("osdCols","uint8_t","1","","(If OSD supported) Number of OSD columns."),
  MSP_FIELD("osdStartY","uint8_t","1","","(If OSD supported) Starting row for RLE data."),
  MSP_FIELD("osdStartX","uint8_t","1","","(If OSD supported) Starting column for RLE data."),
  MSP_FIELD("osdRleData","uint8_t[]","Variable","","(If OSD supported) Run-length encoded OSD character data. Terminated by [0, 0].")
);
MSP_MESSAGE(
  MSP2_INAV_SERVO_MIXER, 0x2020, ::msp::MspDir::Out,
  MSP_FIELD("targetChannel","uint8_t","1","","Servo output channel index (0-based)."),
  MSP_FIELD("inputSource","uint8_t","1","","Enum: Input source (mixerSource_t)."),
  MSP_FIELD("rate","uint16_t","2","","Mixing rate/weight."),
  MSP_FIELD("speed","uint8_t","1","","Speed/Slew rate limit (0-100)."),
  MSP_FIELD("conditionId","uint8_t","1","","Logic Condition ID (0 to MAX_LOGIC_CONDITIONS - 1, or 255/-1 if none/disabled)."),
  MSP_FIELD("targetChannel","uint8_t","1","","Profile 2 Target channel."),
  MSP_FIELD("inputSource","uint8_t","1","","Profile 2 Input source."),
  MSP_FIELD("rate","uint16_t","2","","Profile 2 Rate."),
  MSP_FIELD("speed","uint8_t","1","","Profile 2 Speed."),
  MSP_FIELD("conditionId","uint8_t","1","","Profile 2 Logic Condition ID.")
);
MSP_MESSAGE(
  MSP2_INAV_SET_SERVO_MIXER, 0x2021, ::msp::MspDir::In,
  MSP_FIELD("ruleIndex","uint8_t","1","","Index of the rule to set (0 to MAX_SERVO_RULES - 1)."),
  MSP_FIELD("targetChannel","uint8_t","1","","Servo output channel index."),
  MSP_FIELD("inputSource","uint8_t","1","","Enum: Input source (mixerSource_t)."),
  MSP_FIELD("rate","uint16_t","2","","Mixing rate/weight."),
  MSP_FIELD("speed","uint8_t","1","","Speed/Slew rate limit (0-100)."),
  MSP_FIELD("conditionId","uint8_t","1","","Logic Condition ID (255/-1 if none). Ignored if USE_PROGRAMMING_FRAMEWORK is disabled.")
);
MSP_MESSAGE(
  MSP2_INAV_LOGIC_CONDITIONS, 0x2022, ::msp::MspDir::Out,
  MSP_FIELD("enabled","uint8_t","1","","Boolean: 1 if the condition is enabled."),
  MSP_FIELD("activatorId","uint8_t","1","","ID of the activator condition (if any, 255 if none)."),
  MSP_FIELD("operation","uint8_t","1","","Enum (logicConditionOp_e): Logical operation (AND, OR, XOR, etc.)."),
  MSP_FIELD("operandAType","uint8_t","1","","Enum (logicOperandType_e): Type of the first operand (Flight Mode, GVAR, etc.)."),
  MSP_FIELD("operandAValue","uint32_t","4","","Value/ID of the first operand."),
  MSP_FIELD("operandBType","uint8_t","1","","Enum (logicOperandType_e): Type of the second operand."),
  MSP_FIELD("operandBValue","uint32_t","4","","Value/ID of the second operand."),
  MSP_FIELD("flags","uint8_t","1","","Bitmask: Condition flags (e.g., LC_FLAG_FIRST_TIME_TRUE).")
);
MSP_MESSAGE(
  MSP2_INAV_SET_LOGIC_CONDITIONS, 0x2023, ::msp::MspDir::In,
  MSP_FIELD("conditionIndex","uint8_t","1","","Index of the condition to set (0 to MAX_LOGIC_CONDITIONS - 1)."),
  MSP_FIELD("enabled","uint8_t","1","","Boolean: 1 to enable the condition."),
  MSP_FIELD("activatorId","uint8_t","1","","Activator condition ID."),
  MSP_FIELD("operation","uint8_t","1","","Enum: Logical operation."),
  MSP_FIELD("operandAType","uint8_t","1","","Enum: Type of operand A."),
  MSP_FIELD("operandAValue","uint32_t","4","","Value/ID of operand A."),
  MSP_FIELD("operandBType","uint8_t","1","","Enum: Type of operand B."),
  MSP_FIELD("operandBValue","uint32_t","4","","Value/ID of operand B."),
  MSP_FIELD("flags","uint8_t","1","","Bitmask: Condition flags.")
);
MSP_MESSAGE(
  MSP2_INAV_LOGIC_CONDITIONS_STATUS, 0x2026, ::msp::MspDir::Out,
  MSP_FIELD("conditionValues","uint32_t[MAX_LOGIC_CONDITIONS]","MAX_LOGIC_CONDITIONS 4","","Array of current values for each logic condition (logicConditionGetValue(i)). 1 for true, 0 for false, or numerical value depending on operation.")
);
MSP_MESSAGE(
  MSP2_INAV_GVAR_STATUS, 0x2027, ::msp::MspDir::Out,
  MSP_FIELD("gvarValues","uint32_t[MAX_GLOBAL_VARIABLES]","MAX_GLOBAL_VARIABLES 4","","Array of current values for each global variable (gvGet(i)).")
);
MSP_MESSAGE(
  MSP2_INAV_PROGRAMMING_PID, 0x2028, ::msp::MspDir::Out,
  MSP_FIELD("enabled","uint8_t","1","","Boolean: 1 if the PID is enabled."),
  MSP_FIELD("setpointType","uint8_t","1","","Enum (logicOperandType_e): Type of the setpoint source."),
  MSP_FIELD("setpointValue","uint32_t","4","","Value/ID of the setpoint source."),
  MSP_FIELD("measurementType","uint8_t","1","","Enum (logicOperandType_e): Type of the measurement source."),
  MSP_FIELD("measurementValue","uint32_t","4","","Value/ID of the measurement source."),
  MSP_FIELD("gainP","uint16_t","2","","Proportional gain."),
  MSP_FIELD("gainI","uint16_t","2","","Integral gain."),
  MSP_FIELD("gainD","uint16_t","2","","Derivative gain."),
  MSP_FIELD("gainFF","uint16_t","2","","Feed-forward gain.")
);
MSP_MESSAGE(
  MSP2_INAV_SET_PROGRAMMING_PID, 0x2029, ::msp::MspDir::In,
  MSP_FIELD("pidIndex","uint8_t","1","","Index of the Programming PID to set (0 to MAX_PROGRAMMING_PID_COUNT - 1)."),
  MSP_FIELD("enabled","uint8_t","1","","Boolean: 1 to enable the PID."),
  MSP_FIELD("setpointType","uint8_t","1","","Enum: Type of the setpoint source."),
  MSP_FIELD("setpointValue","uint32_t","4","","Value/ID of the setpoint source."),
  MSP_FIELD("measurementType","uint8_t","1","","Enum: Type of the measurement source."),
  MSP_FIELD("measurementValue","uint32_t","4","","Value/ID of the measurement source."),
  MSP_FIELD("gainP","uint16_t","2","","Proportional gain."),
  MSP_FIELD("gainI","uint16_t","2","","Integral gain."),
  MSP_FIELD("gainD","uint16_t","2","","Derivative gain."),
  MSP_FIELD("gainFF","uint16_t","2","","Feed-forward gain.")
);
MSP_MESSAGE(
  MSP2_INAV_PROGRAMMING_PID_STATUS, 0x202a, ::msp::MspDir::Out,
  MSP_FIELD("pidOutputs","uint32_t[MAX_PROGRAMMING_PID_COUNT]","MAX_PROGRAMMING_PID_COUNT 4","","Array of current output values for each Programming PID (programmingPidGetOutput(i)).")
);
MSP_MESSAGE(
  MSP2_PID, 0x2030, ::msp::MspDir::Out,
  MSP_FIELD("P","uint8_t","1","","Proportional gain (pidBank()->pid[i].P), constrained 0-255."),
  MSP_FIELD("I","uint8_t","1","","Integral gain (pidBank()->pid[i].I), constrained 0-255."),
  MSP_FIELD("D","uint8_t","1","","Derivative gain (pidBank()->pid[i].D), constrained 0-255."),
  MSP_FIELD("FF","uint8_t","1","","Feed-forward gain (pidBank()->pid[i].FF), constrained 0-255.")
);
MSP_MESSAGE(
  MSP2_SET_PID, 0x2031, ::msp::MspDir::In,
  MSP_FIELD("P","uint8_t","1","","Sets Proportional gain (pidBankMutable()->pid[i].P)."),
  MSP_FIELD("I","uint8_t","1","","Sets Integral gain (pidBankMutable()->pid[i].I)."),
  MSP_FIELD("D","uint8_t","1","","Sets Derivative gain (pidBankMutable()->pid[i].D)."),
  MSP_FIELD("FF","uint8_t","1","","Sets Feed-forward gain (pidBankMutable()->pid[i].FF).")
);
MSP_MESSAGE(
  MSP2_INAV_OPFLOW_CALIBRATION, 0x2032, ::msp::MspDir::In
);
MSP_MESSAGE(
  MSP2_INAV_FWUPDT_PREPARE, 0x2033, ::msp::MspDir::In,
  MSP_FIELD("firmwareSize","uint32_t","4","","Total size of the incoming firmware file in bytes.")
);
MSP_MESSAGE(
  MSP2_INAV_FWUPDT_STORE, 0x2034, ::msp::MspDir::In,
  MSP_FIELD("firmwareChunk","uint8_t[]","Variable","","Chunk of firmware data.")
);
MSP_MESSAGE(
  MSP2_INAV_FWUPDT_EXEC, 0x2035, ::msp::MspDir::In,
  MSP_FIELD("updateType","uint8_t","1","","Type of update (e.g., full flash, specific section - currently ignored/unused).")
);
MSP_MESSAGE(
  MSP2_INAV_FWUPDT_ROLLBACK_PREPARE, 0x2036, ::msp::MspDir::In
);
MSP_MESSAGE(
  MSP2_INAV_FWUPDT_ROLLBACK_EXEC, 0x2037, ::msp::MspDir::In
);
MSP_MESSAGE(
  MSP2_INAV_SAFEHOME, 0x2038, ::msp::MspDir::InOut,
  MSP_FIELD("safehomeIndex","uint8_t","1","","Index of the safe home location (0 to MAX_SAFE_HOMES - 1)."),
  MSP_FIELD("safehomeIndex","uint8_t","1","","Index requested."),
  MSP_FIELD("enabled","uint8_t","1","","Boolean: 1 if this safe home is enabled."),
  MSP_FIELD("latitude","int32_t","4","","Latitude (1e7 deg)."),
  MSP_FIELD("longitude","int32_t","4","","Longitude (1e7 deg).")
);
MSP_MESSAGE(
  MSP2_INAV_SET_SAFEHOME, 0x2039, ::msp::MspDir::In,
  MSP_FIELD("safehomeIndex","uint8_t","1","","Index of the safe home location (0 to MAX_SAFE_HOMES - 1)."),
  MSP_FIELD("enabled","uint8_t","1","","Boolean: 1 to enable this safe home."),
  MSP_FIELD("latitude","int32_t","4","","Latitude (1e7 deg)."),
  MSP_FIELD("longitude","int32_t","4","","Longitude (1e7 deg).")
);
MSP_MESSAGE(
  MSP2_INAV_MISC2, 0x203a, ::msp::MspDir::Out,
  MSP_FIELD("uptimeSeconds","uint32_t","4","Seconds","Time since boot (micros() / 1000000)."),
  MSP_FIELD("flightTimeSeconds","uint32_t","4","Seconds","Accumulated flight time (getFlightTime())."),
  MSP_FIELD("throttlePercent","uint8_t","1","%","Current throttle output percentage (getThrottlePercent(true))."),
  MSP_FIELD("autoThrottleFlag","uint8_t","1","Boolean","1 if navigation is controlling throttle, 0 otherwise (navigationIsControllingThrottle()).")
);
MSP_MESSAGE(
  MSP2_INAV_LOGIC_CONDITIONS_SINGLE, 0x203b, ::msp::MspDir::InOut,
  MSP_FIELD("conditionIndex","uint8_t","1","","Index of the condition to retrieve (0 to MAX_LOGIC_CONDITIONS - 1)."),
  MSP_FIELD("enabled","uint8_t","1","","Boolean: 1 if enabled."),
  MSP_FIELD("activatorId","uint8_t","1","","Activator ID."),
  MSP_FIELD("operation","uint8_t","1","","Enum: Logical operation."),
  MSP_FIELD("operandAType","uint8_t","1","","Enum: Type of operand A."),
  MSP_FIELD("operandAValue","uint32_t","4","","Value/ID of operand A."),
  MSP_FIELD("operandBType","uint8_t","1","","Enum: Type of operand B."),
  MSP_FIELD("operandBValue","uint32_t","4","","Value/ID of operand B."),
  MSP_FIELD("flags","uint8_t","1","","Bitmask: Condition flags.")
);
MSP_MESSAGE(
  MSP2_INAV_ESC_RPM, 0x2040, ::msp::MspDir::Out,
  MSP_FIELD("escRpm","uint32_t[]","Variable","RPM","Per-motor ESC RPM values. One entry per motor reporting telemetry.")
);
MSP_MESSAGE(
  MSP2_INAV_ESC_TELEM, 0x2041, ::msp::MspDir::Out,
  MSP_FIELD("motorCount","uint8_t","1","","Number of motors reporting telemetry (getMotorCount())."),
  MSP_FIELD("escData","escSensorData_t[]","motorCount sizeof(escSensorData_t)","","Array of escSensorData_t structures containing voltage, current, temp, RPM, errors etc. for each ESC.")
);
MSP_MESSAGE(
  MSP2_INAV_LED_STRIP_CONFIG_EX, 0x2048, ::msp::MspDir::Out,
  MSP_FIELD("ledConfig","ledConfig_t","sizeof(ledConfig_t)","","Full configuration structure for the LED.")
);
MSP_MESSAGE(
  MSP2_INAV_SET_LED_STRIP_CONFIG_EX, 0x2049, ::msp::MspDir::In,
  MSP_FIELD("ledIndex","uint8_t","1","","Index of the LED to configure (0 to LED_MAX_STRIP_LENGTH - 1)."),
  MSP_FIELD("ledConfig","ledConfig_t","sizeof(ledConfig_t)","","Full configuration structure for the LED.")
);
MSP_MESSAGE(
  MSP2_INAV_FW_APPROACH, 0x204a, ::msp::MspDir::InOut,
  MSP_FIELD("approachIndex","uint8_t","1","","Index of the approach setting (0 to MAX_FW_LAND_APPOACH_SETTINGS - 1)."),
  MSP_FIELD("approachIndex","uint8_t","1","Index","Index requested."),
  MSP_FIELD("approachAlt","uint32_t","4","cm","Altitude for the approach phase."),
  MSP_FIELD("landAlt","uint32_t","4","cm","Altitude for the final landing phase."),
  MSP_FIELD("approachDirection","uint8_t","1","Enum","Direction of approach (From WP, Specific Heading)."),
  MSP_FIELD("landHeading1","int16_t","2","degrees","Primary landing heading (if approachDirection requires it)."),
  MSP_FIELD("landHeading2","int16_t","2","degrees","Secondary landing heading (if approachDirection requires it)."),
  MSP_FIELD("isSeaLevelRef","uint8_t","1","Boolean","1 if altitudes are relative to sea level, 0 if relative to home.")
);
MSP_MESSAGE(
  MSP2_INAV_SET_FW_APPROACH, 0x204b, ::msp::MspDir::In,
  MSP_FIELD("approachIndex","uint8_t","1","Index","Index of the approach setting (0 to MAX_FW_LAND_APPOACH_SETTINGS - 1)."),
  MSP_FIELD("approachAlt","uint32_t","4","cm","Sets approach altitude."),
  MSP_FIELD("landAlt","uint32_t","4","cm","Sets landing altitude."),
  MSP_FIELD("approachDirection","uint8_t","1","Enum","Sets approach direction."),
  MSP_FIELD("landHeading1","int16_t","2","degrees","Sets primary landing heading."),
  MSP_FIELD("landHeading2","int16_t","2","degrees","Sets secondary landing heading."),
  MSP_FIELD("isSeaLevelRef","uint8_t","1","Boolean","Sets altitude reference.")
);
MSP_MESSAGE(
  MSP2_INAV_GPS_UBLOX_COMMAND, 0x2050, ::msp::MspDir::In,
  MSP_FIELD("ubxCommand","uint8_t[]","Variable (>= 8)","","Raw U-Blox UBX protocol command frame (including header, class, ID, length, payload, checksum).")
);
MSP_MESSAGE(
  MSP2_INAV_RATE_DYNAMICS, 0x2060, ::msp::MspDir::Out,
  MSP_FIELD("sensitivityCenter","uint8_t","1","%","Sensitivity at stick center (currentControlRateProfile->rateDynamics.sensitivityCenter)."),
  MSP_FIELD("sensitivityEnd","uint8_t","1","%","Sensitivity at stick ends (currentControlRateProfile->rateDynamics.sensitivityEnd)."),
  MSP_FIELD("correctionCenter","uint8_t","1","%","Correction strength at stick center (currentControlRateProfile->rateDynamics.correctionCenter)."),
  MSP_FIELD("correctionEnd","uint8_t","1","%","Correction strength at stick ends (currentControlRateProfile->rateDynamics.correctionEnd)."),
  MSP_FIELD("weightCenter","uint8_t","1","%","Transition weight at stick center (currentControlRateProfile->rateDynamics.weightCenter)."),
  MSP_FIELD("weightEnd","uint8_t","1","%","Transition weight at stick ends (currentControlRateProfile->rateDynamics.weightEnd).")
);
MSP_MESSAGE(
  MSP2_INAV_SET_RATE_DYNAMICS, 0x2061, ::msp::MspDir::In,
  MSP_FIELD("sensitivityCenter","uint8_t","1","%","Sets sensitivity at center."),
  MSP_FIELD("sensitivityEnd","uint8_t","1","%","Sets sensitivity at ends."),
  MSP_FIELD("correctionCenter","uint8_t","1","%","Sets correction at center."),
  MSP_FIELD("correctionEnd","uint8_t","1","%","Sets correction at ends."),
  MSP_FIELD("weightCenter","uint8_t","1","%","Sets weight at center."),
  MSP_FIELD("weightEnd","uint8_t","1","%","Sets weight at ends.")
);
MSP_MESSAGE(
  MSP2_INAV_EZ_TUNE, 0x2070, ::msp::MspDir::Out,
  MSP_FIELD("enabled","uint8_t","1","","Boolean: 1 if EZ-Tune is enabled (ezTune()->enabled)."),
  MSP_FIELD("filterHz","uint16_t","2","","Filter frequency used during tuning (ezTune()->filterHz)."),
  MSP_FIELD("axisRatio","uint8_t","1","","Roll vs Pitch axis tuning ratio (ezTune()->axisRatio)."),
  MSP_FIELD("response","uint8_t","1","","Desired response characteristic (ezTune()->response)."),
  MSP_FIELD("damping","uint8_t","1","","Desired damping characteristic (ezTune()->damping)."),
  MSP_FIELD("stability","uint8_t","1","","Stability preference (ezTune()->stability)."),
  MSP_FIELD("aggressiveness","uint8_t","1","","Aggressiveness preference (ezTune()->aggressiveness)."),
  MSP_FIELD("rate","uint8_t","1","","Resulting rate setting (ezTune()->rate)."),
  MSP_FIELD("expo","uint8_t","1","","Resulting expo setting (ezTune()->expo)."),
  MSP_FIELD("snappiness","uint8_t","1","","Snappiness preference (ezTune()->snappiness).")
);
MSP_MESSAGE(
  MSP2_INAV_EZ_TUNE_SET, 0x2071, ::msp::MspDir::In,
  MSP_FIELD("enabled","uint8_t","1","","Sets enabled state."),
  MSP_FIELD("filterHz","uint16_t","2","","Sets filter frequency."),
  MSP_FIELD("axisRatio","uint8_t","1","","Sets axis ratio."),
  MSP_FIELD("response","uint8_t","1","","Sets response characteristic."),
  MSP_FIELD("damping","uint8_t","1","","Sets damping characteristic."),
  MSP_FIELD("stability","uint8_t","1","","Sets stability preference."),
  MSP_FIELD("aggressiveness","uint8_t","1","","Sets aggressiveness preference."),
  MSP_FIELD("rate","uint8_t","1","","Sets rate setting."),
  MSP_FIELD("expo","uint8_t","1","","Sets expo setting."),
  MSP_FIELD("snappiness","uint8_t","1","","(Optional) Sets snappiness preference.")
);
MSP_MESSAGE(
  MSP2_INAV_SELECT_MIXER_PROFILE, 0x2080, ::msp::MspDir::In,
  MSP_FIELD("mixerProfileIndex","uint8_t","1","","Index of the mixer profile to activate (0-based).")
);
MSP_MESSAGE(
  MSP2_ADSB_VEHICLE_LIST, 0x2090, ::msp::MspDir::Out,
  MSP_FIELD("maxVehicles","uint8_t","1","","Maximum number of vehicles tracked (MAX_ADSB_VEHICLES). 0 if USE_ADSB disabled."),
  MSP_FIELD("callsignLength","uint8_t","1","","Maximum length of callsign string (ADSB_CALL_SIGN_MAX_LENGTH). 0 if USE_ADSB disabled."),
  MSP_FIELD("totalVehicleMsgs","uint32_t","4","","Total vehicle messages received (getAdsbStatus()->vehiclesMessagesTotal). 0 if USE_ADSB disabled."),
  MSP_FIELD("totalHeartbeatMsgs","uint32_t","4","","Total heartbeat messages received (getAdsbStatus()->heartbeatMessagesTotal). 0 if USE_ADSB disabled."),
  MSP_FIELD("Vehicle Data (Repeated maxVehicles times):","","","",""),
  MSP_FIELD("callsign","char[ADSB_CALL_SIGN_MAX_LENGTH]","ADSB_CALL_SIGN_MAX_LENGTH","","Vehicle callsign (padded with nulls)."),
  MSP_FIELD("icao","uint32_t","4","","ICAO 24-bit address."),
  MSP_FIELD("latitude","int32_t","4","","Latitude (1e7 deg)."),
  MSP_FIELD("longitude","int32_t","4","","Longitude (1e7 deg)."),
  MSP_FIELD("altitude","int32_t","4","","Altitude (cm)."),
  MSP_FIELD("heading","int16_t","2","","Heading (degrees)."),
  MSP_FIELD("tslc","uint8_t","1","","Time Since Last Communication (seconds)."),
  MSP_FIELD("emitterType","uint8_t","1","","Enum: Type of ADSB emitter."),
  MSP_FIELD("ttl","uint8_t","1","","Time-to-live counter for this entry.")
);
MSP_MESSAGE(
  MSP2_INAV_CUSTOM_OSD_ELEMENTS, 0x2100, ::msp::MspDir::Out,
  MSP_FIELD("maxElements","uint8_t","1","","Maximum number of custom elements (MAX_CUSTOM_ELEMENTS)."),
  MSP_FIELD("maxTextLength","uint8_t","1","","Maximum length of the text part (OSD_CUSTOM_ELEMENT_TEXT_SIZE - 1)."),
  MSP_FIELD("maxParts","uint8_t","1","","Maximum number of parts per element (CUSTOM_ELEMENTS_PARTS).")
);
MSP_MESSAGE(
  MSP2_INAV_CUSTOM_OSD_ELEMENT, 0x2101, ::msp::MspDir::InOut,
  MSP_FIELD("elementIndex","uint8_t","1","","Index of the custom element (0 to MAX_CUSTOM_ELEMENTS - 1)."),
  MSP_FIELD("Parts Data (Repeated CUSTOM_ELEMENTS_PARTS times):","","","",""),
  MSP_FIELD("partType","uint8_t","1","","Enum (customElementType_e): Type of this part (Text, Variable, Symbol)."),
  MSP_FIELD("partValue","uint16_t","2","","Value/ID associated with this part (GVAR index, Symbol ID, etc.)."),
  MSP_FIELD("Visibility Data:","","","",""),
  MSP_FIELD("visibilityType","uint8_t","1","","Enum (logicOperandType_e): Type of visibility condition source."),
  MSP_FIELD("visibilityValue","uint16_t","2","","Value/ID of the visibility condition source (e.g., Logic Condition ID)."),
  MSP_FIELD("Text Data:","","","",""),
  MSP_FIELD("elementText","char[OSD_CUSTOM_ELEMENT_TEXT_SIZE - 1]","OSD_CUSTOM_ELEMENT_TEXT_SIZE - 1","","Static text part of the element (null padding likely).")
);
MSP_MESSAGE(
  MSP2_INAV_SET_CUSTOM_OSD_ELEMENTS, 0x2102, ::msp::MspDir::In,
  MSP_FIELD("elementIndex","uint8_t","1","","Index of the custom element (0 to MAX_CUSTOM_ELEMENTS - 1)."),
  MSP_FIELD("Parts Data (Repeated CUSTOM_ELEMENTS_PARTS times):","","","",""),
  MSP_FIELD("partType","uint8_t","1","","Enum (customElementType_e): Type of this part."),
  MSP_FIELD("partValue","uint16_t","2","","Value/ID associated with this part."),
  MSP_FIELD("Visibility Data:","","","",""),
  MSP_FIELD("visibilityType","uint8_t","1","","Enum (logicOperandType_e): Type of visibility condition source."),
  MSP_FIELD("visibilityValue","uint16_t","2","","Value/ID of the visibility condition source."),
  MSP_FIELD("Text Data:","","","",""),
  MSP_FIELD("elementText","char[OSD_CUSTOM_ELEMENT_TEXT_SIZE - 1]","OSD_CUSTOM_ELEMENT_TEXT_SIZE - 1","","Static text part of the element.")
);
MSP_MESSAGE(
  MSP2_INAV_OUTPUT_MAPPING_EXT2, 0x210d, ::msp::MspDir::Out,
  MSP_FIELD("timerId","uint8_t","1","","Hardware timer identifier (e.g., TIM1, TIM2). SITL uses index."),
  MSP_FIELD("usageFlags","uint32_t","4","","Full 32-bit timer usage flags (TIM_USE_)."),
  MSP_FIELD("pinLabel","uint8_t","1","","Label for special pin usage (PIN_LABEL_ enum, e.g., PIN_LABEL_LED). 0 (PIN_LABEL_NONE) otherwise.")
);
MSP_MESSAGE(
  MSP2_INAV_SERVO_CONFIG, 0x2200, ::msp::MspDir::Out,
  MSP_FIELD("min","uint16_t","2","PWM","Minimum servo endpoint (servoParams(i)->min)."),
  MSP_FIELD("max","uint16_t","2","PWM","Maximum servo endpoint (servoParams(i)->max)."),
  MSP_FIELD("middle","uint16_t","2","PWM","Middle/Neutral servo position (servoParams(i)->middle)."),
  MSP_FIELD("rate","uint8_t","1","% (-100 to 100)","Servo rate/scaling (servoParams(i)->rate).")
);
MSP_MESSAGE(
  MSP2_INAV_SET_SERVO_CONFIG, 0x2201, ::msp::MspDir::In,
  MSP_FIELD("servoIndex","uint8_t","1","Index","Index of the servo to configure (0 to MAX_SUPPORTED_SERVOS - 1)."),
  MSP_FIELD("min","uint16_t","2","PWM","Sets minimum servo endpoint."),
  MSP_FIELD("max","uint16_t","2","PWM","Sets maximum servo endpoint."),
  MSP_FIELD("middle","uint16_t","2","PWM","Sets middle/neutral servo position."),
  MSP_FIELD("rate","uint8_t","1","%","Sets servo rate/scaling.")
);
MSP_MESSAGE(
  MSP2_INAV_GEOZONE, 0x2210, ::msp::MspDir::InOut,
  MSP_FIELD("geozoneIndex","uint8_t","1","","Index of the geozone (0 to MAX_GEOZONES_IN_CONFIG - 1)."),
  MSP_FIELD("geozoneIndex","uint8_t","1","","Index requested."),
  MSP_FIELD("type","uint8_t","1","","Enum (GEOZONE_TYPE_): Zone type (Inclusion/Exclusion)."),
  MSP_FIELD("shape","uint8_t","1","","Enum (GEOZONE_SHAPE_): Zone shape (Polygon/Circular)."),
  MSP_FIELD("minAltitude","uint32_t","4","","Minimum allowed altitude within the zone (cm)."),
  MSP_FIELD("maxAltitude","uint32_t","4","","Maximum allowed altitude within the zone (cm)."),
  MSP_FIELD("isSeaLevelRef","uint8_t","1","","Boolean: 1 if altitudes are relative to sea level, 0 if relative to home."),
  MSP_FIELD("fenceAction","uint8_t","1","","Enum (GEOZONE_ACTION_): Action to take upon boundary violation."),
  MSP_FIELD("vertexCount","uint8_t","1","","Number of vertices defined for this zone.")
);
MSP_MESSAGE(
  MSP2_INAV_SET_GEOZONE, 0x2211, ::msp::MspDir::In,
  MSP_FIELD("geozoneIndex","uint8_t","1","","Index of the geozone (0 to MAX_GEOZONES_IN_CONFIG - 1)."),
  MSP_FIELD("type","uint8_t","1","","Enum (GEOZONE_TYPE_): Zone type."),
  MSP_FIELD("shape","uint8_t","1","","Enum (GEOZONE_SHAPE_): Zone shape."),
  MSP_FIELD("minAltitude","uint32_t","4","","Minimum allowed altitude (cm)."),
  MSP_FIELD("maxAltitude","uint32_t","4","","Maximum allowed altitude (cm)."),
  MSP_FIELD("isSeaLevelRef","uint8_t","1","","Boolean: Altitude reference."),
  MSP_FIELD("fenceAction","uint8_t","1","","Enum (GEOZONE_ACTION_): Fence action."),
  MSP_FIELD("vertexCount","uint8_t","1","","Number of vertices to be defined (used for validation later).")
);
MSP_MESSAGE(
  MSP2_INAV_GEOZONE_VERTEX, 0x2212, ::msp::MspDir::InOut,
  MSP_FIELD("geozoneIndex","uint8_t","1","","Index of the geozone."),
  MSP_FIELD("vertexId","uint8_t","1","","Index of the vertex within the zone (0-based). For circles, 0 = center."),
  MSP_FIELD("geozoneIndex","uint8_t","1","Index","Geozone index requested."),
  MSP_FIELD("vertexId","uint8_t","1","Index","Vertex index requested."),
  MSP_FIELD("latitude","int32_t","4","deg 1e7","Vertex latitude."),
  MSP_FIELD("longitude","int32_t","4","deg 1e7","Vertex longitude."),
  MSP_FIELD("geozoneIndex","uint8_t","1","Index","Geozone index requested."),
  MSP_FIELD("vertexId","uint8_t","1","Index","Vertex index requested (always 0 for center)."),
  MSP_FIELD("centerLatitude","int32_t","4","deg 1e7","Center latitude."),
  MSP_FIELD("centerLongitude","int32_t","4","deg 1e7","Center longitude."),
  MSP_FIELD("radius","uint32_t","4","cm","Radius of the circular zone.")
);
MSP_MESSAGE(
  MSP2_INAV_SET_GEOZONE_VERTEX, 0x2213, ::msp::MspDir::In,
  MSP_FIELD("geozoneIndex","uint8_t","1","Index","Geozone index."),
  MSP_FIELD("vertexId","uint8_t","1","Index","Vertex index (0-based)."),
  MSP_FIELD("latitude","int32_t","4","deg 1e7","Vertex latitude."),
  MSP_FIELD("longitude","int32_t","4","deg 1e7","Vertex longitude."),
  MSP_FIELD("geozoneIndex","uint8_t","1","Index","Geozone index."),
  MSP_FIELD("vertexId","uint8_t","1","Index","Vertex index (must be 0 for center)."),
  MSP_FIELD("centerLatitude","int32_t","4","deg 1e7","Center latitude."),
  MSP_FIELD("centerLongitude","int32_t","4","deg 1e7","Center longitude."),
  MSP_FIELD("radius","uint32_t","4","cm","Radius of the circular zone.")
);
MSP_MESSAGE(
  MSP2_BETAFLIGHT_BIND, 0x3000, ::msp::MspDir::In
);
