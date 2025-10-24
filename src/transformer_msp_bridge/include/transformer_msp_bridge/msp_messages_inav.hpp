#pragma once
#include <cstdint>
#include <cstddef>
namespace msp {
enum class Direction : uint8_t { In, Out, InOut, Unknown };
struct Field { const char* name; const char* ctype; const char* size; const char* units; const char* description; };
struct Message {
  const char* name; uint32_t id; const char* id_hex; Direction direction; const char* description;
  const Field* fields; size_t field_count; uint8_t version; bool has_variable_length;
};

inline constexpr Field FIELDS_0[] = {
  { "mspProtocolVersion", "uint8_t", "1", "", "MSP Protocol version (MSP_PROTOCOL_VERSION, typically 0)." },
  { "apiVersionMajor", "uint8_t", "1", "", "INAV API Major version (API_VERSION_MAJOR)." },
  { "apiVersionMinor", "uint8_t", "1", "", "INAV API Minor version (API_VERSION_MINOR)." },
};

inline constexpr Field FIELDS_1[] = {
  { "fcVariantIdentifier", "char[4]", "4", "", "4-character identifier string (e.g., \"INAV\"). Defined by flightControllerIdentifier." },
};

inline constexpr Field FIELDS_2[] = {
  { "fcVersionMajor", "uint8_t", "1", "", "Firmware Major version (FC_VERSION_MAJOR)." },
  { "fcVersionMinor", "uint8_t", "1", "", "Firmware Minor version (FC_VERSION_MINOR)." },
  { "fcVersionPatch", "uint8_t", "1", "", "Firmware Patch level (FC_VERSION_PATCH_LEVEL)." },
};

inline constexpr Field FIELDS_3[] = {
  { "boardIdentifier", "char[4]", "4", "", "4-character UPPER CASE board identifier (TARGET_BOARD_IDENTIFIER)." },
  { "hardwareRevision", "uint16_t", "2", "", "Hardware revision number. 0 if not detected (USE_HARDWARE_REVISION_DETECTION)." },
  { "osdSupport", "uint8_t", "1", "", "OSD chip type: 0=None, 2=Onboard (USE_OSD). INAV does not support slave OSD (1)." },
  { "commCapabilities", "uint8_t", "1", "", "Communication capabilities bitmask: Bit 0=VCP support (USE_VCP), Bit 1=SoftSerial support (USE_SOFTSERIAL1/2)." },
  { "targetNameLength", "uint8_t", "1", "", "Length of the target name string that follows." },
  { "targetName", "char[]", "Variable", "", "Target name string (e.g., \"MATEKF405\"). Length given by previous field." },
};

inline constexpr Field FIELDS_4[] = {
  { "buildDate", "char[11]", "11", "", "Build date string (e.g., \"Dec 31 2023\"). BUILD_DATE_LENGTH." },
  { "buildTime", "char[8]", "8", "", "Build time string (e.g., \"23:59:59\"). BUILD_TIME_LENGTH." },
  { "gitRevision", "char[7]", "7", "", "Short Git revision string. GIT_SHORT_REVISION_LENGTH." },
};

inline constexpr Field FIELDS_5[] = {
  { "legacyAsyncProcessing", "uint8_t", "1", "-", "Legacy, unused. Always 0." },
  { "legacyAsyncValue1", "uint16_t", "2", "-", "Legacy, unused. Always 0." },
  { "legacyAsyncValue2", "uint16_t", "2", "-", "Legacy, unused. Always 0." },
  { "headingHoldRateLimit", "uint8_t", "1", "deg/s", "Max rate for heading hold P term (pidProfile()->heading_hold_rate_limit)." },
  { "headingHoldLpfFreq", "uint8_t", "1", "Hz", "Fixed LPF frequency for heading hold error (HEADING_HOLD_ERROR_LPF_FREQ)." },
  { "legacyYawJumpLimit", "uint16_t", "2", "-", "Legacy, unused. Always 0." },
  { "legacyGyroLpf", "uint8_t", "1", "Enum", "Fixed value GYRO_LPF_256HZ." },
  { "accLpfHz", "uint8_t", "1", "Hz", "Accelerometer LPF frequency (accelerometerConfig()->acc_lpf_hz)." },
  { "reserved1", "uint8_t", "1", "-", "Reserved. Always 0." },
  { "reserved2", "uint8_t", "1", "-", "Reserved. Always 0." },
  { "reserved3", "uint8_t", "1", "-", "Reserved. Always 0." },
  { "reserved4", "uint8_t", "1", "-", "Reserved. Always 0." },
};

inline constexpr Field FIELDS_6[] = {
  { "legacyAsyncProcessing", "uint8_t", "1", "-", "Legacy, ignored." },
  { "legacyAsyncValue1", "uint16_t", "2", "-", "Legacy, ignored." },
  { "legacyAsyncValue2", "uint16_t", "2", "-", "Legacy, ignored." },
  { "headingHoldRateLimit", "uint8_t", "1", "deg/s", "Sets pidProfileMutable()->heading_hold_rate_limit." },
  { "headingHoldLpfFreq", "uint8_t", "1", "Hz", "Ignored (fixed value HEADING_HOLD_ERROR_LPF_FREQ used)." },
  { "legacyYawJumpLimit", "uint16_t", "2", "-", "Legacy, ignored." },
  { "legacyGyroLpf", "uint8_t", "1", "Enum", "Ignored (was gyro LPF)." },
  { "accLpfHz", "uint8_t", "1", "Hz", "Sets accelerometerConfigMutable()->acc_lpf_hz." },
  { "reserved1", "uint8_t", "1", "-", "Ignored." },
  { "reserved2", "uint8_t", "1", "-", "Ignored." },
  { "reserved3", "uint8_t", "1", "-", "Ignored." },
  { "reserved4", "uint8_t", "1", "-", "Ignored." },
};

inline constexpr Field FIELDS_7[] = {
  { "craftName", "char[]", "Variable", "", "The craft name string (systemConfig()->craftName). Null termination is not explicitly sent, the length is determined by the payload size." },
};

inline constexpr Field FIELDS_8[] = {
  { "craftName", "char[]", "1 to MAX_NAME_LENGTH", "", "The new craft name string. Automatically null-terminated by the FC." },
};

inline constexpr Field FIELDS_9[] = {
  { "userControlMode", "uint8_t", "1", "Enum", "Navigation user control mode (navConfig()->general.flags.user_control_mode)." },
  { "maxAutoSpeed", "uint16_t", "2", "cm/s", "Max speed in autonomous modes (navConfig()->general.max_auto_speed)." },
  { "maxAutoClimbRate", "uint16_t", "2", "cm/s", "Max climb rate in autonomous modes (uses fw.max_auto_climb_rate or mc.max_auto_climb_rate based on platform)." },
  { "maxManualSpeed", "uint16_t", "2", "cm/s", "Max speed in manual modes with GPS aiding (navConfig()->general.max_manual_speed)." },
  { "maxManualClimbRate", "uint16_t", "2", "cm/s", "Max climb rate in manual modes with GPS aiding (uses fw.max_manual_climb_rate or mc.max_manual_climb_rate)." },
  { "mcMaxBankAngle", "uint8_t", "1", "degrees", "Max bank angle for multirotor position hold (navConfig()->mc.max_bank_angle)." },
  { "mcAltHoldThrottleType", "uint8_t", "1", "Enum", "Altitude Hold throttle control type (navConfig()->mc.althold_throttle_type)." },
  { "mcHoverThrottle", "uint16_t", "2", "PWM", "Multirotor hover throttle (currentBatteryProfile->nav.mc.hover_throttle)." },
};

inline constexpr Field FIELDS_10[] = {
  { "userControlMode", "uint8_t", "1", "Enum", "Sets navConfigMutable()->general.flags.user_control_mode." },
  { "maxAutoSpeed", "uint16_t", "2", "cm/s", "Sets navConfigMutable()->general.max_auto_speed." },
  { "maxAutoClimbRate", "uint16_t", "2", "cm/s", "Sets fw.max_auto_climb_rate or mc.max_auto_climb_rate based on current platform type." },
  { "maxManualSpeed", "uint16_t", "2", "cm/s", "Sets navConfigMutable()->general.max_manual_speed." },
  { "maxManualClimbRate", "uint16_t", "2", "cm/s", "Sets fw.max_manual_climb_rate or mc.max_manual_climb_rate." },
  { "mcMaxBankAngle", "uint8_t", "1", "degrees", "Sets navConfigMutable()->mc.max_bank_angle." },
  { "mcAltHoldThrottleType", "uint8_t", "1", "Enum", "Sets navConfigMutable()->mc.althold_throttle_type." },
  { "mcHoverThrottle", "uint16_t", "2", "PWM", "Sets currentBatteryProfileMutable->nav.mc.hover_throttle." },
};

inline constexpr Field FIELDS_11[] = {
  { "accCalibAxisFlags", "uint8_t", "1", "Bitmask", "Flags indicating which axes of the accelerometer have been calibrated (accGetCalibrationAxisFlags())." },
  { "accZeroX", "uint16_t", "2", "Raw ADC", "Accelerometer zero offset for X-axis (accelerometerConfig()->accZero.raw[X])." },
  { "accZeroY", "uint16_t", "2", "Raw ADC", "Accelerometer zero offset for Y-axis (accelerometerConfig()->accZero.raw[Y])." },
  { "accZeroZ", "uint16_t", "2", "Raw ADC", "Accelerometer zero offset for Z-axis (accelerometerConfig()->accZero.raw[Z])." },
  { "accGainX", "uint16_t", "2", "Raw ADC", "Accelerometer gain/scale for X-axis (accelerometerConfig()->accGain.raw[X])." },
  { "accGainY", "uint16_t", "2", "Raw ADC", "Accelerometer gain/scale for Y-axis (accelerometerConfig()->accGain.raw[Y])." },
  { "accGainZ", "uint16_t", "2", "Raw ADC", "Accelerometer gain/scale for Z-axis (accelerometerConfig()->accGain.raw[Z])." },
  { "magZeroX", "uint16_t", "2", "Raw ADC", "Magnetometer zero offset for X-axis (compassConfig()->magZero.raw[X]). 0 if USE_MAG disabled." },
  { "magZeroY", "uint16_t", "2", "Raw ADC", "Magnetometer zero offset for Y-axis (compassConfig()->magZero.raw[Y]). 0 if USE_MAG disabled." },
  { "magZeroZ", "uint16_t", "2", "Raw ADC", "Magnetometer zero offset for Z-axis (compassConfig()->magZero.raw[Z]). 0 if USE_MAG disabled." },
  { "opflowScale", "uint16_t", "2", "Scale 256", "Optical flow scale factor (opticalFlowConfig()->opflow_scale 256). 0 if USE_OPFLOW disabled." },
  { "magGainX", "uint16_t", "2", "Raw ADC", "Magnetometer gain/scale for X-axis (compassConfig()->magGain[X]). 0 if USE_MAG disabled." },
  { "magGainY", "uint16_t", "2", "Raw ADC", "Magnetometer gain/scale for Y-axis (compassConfig()->magGain[Y]). 0 if USE_MAG disabled." },
  { "magGainZ", "uint16_t", "2", "Raw ADC", "Magnetometer gain/scale for Z-axis (compassConfig()->magGain[Z]). 0 if USE_MAG disabled." },
};

inline constexpr Field FIELDS_12[] = {
  { "accZeroX", "uint16_t", "2", "Raw ADC", "Sets accelerometerConfigMutable()->accZero.raw[X]." },
  { "accZeroY", "uint16_t", "2", "Raw ADC", "Sets accelerometerConfigMutable()->accZero.raw[Y]." },
  { "accZeroZ", "uint16_t", "2", "Raw ADC", "Sets accelerometerConfigMutable()->accZero.raw[Z]." },
  { "accGainX", "uint16_t", "2", "Raw ADC", "Sets accelerometerConfigMutable()->accGain.raw[X]." },
  { "accGainY", "uint16_t", "2", "Raw ADC", "Sets accelerometerConfigMutable()->accGain.raw[Y]." },
  { "accGainZ", "uint16_t", "2", "Raw ADC", "Sets accelerometerConfigMutable()->accGain.raw[Z]." },
  { "magZeroX", "uint16_t", "2", "Raw ADC", "Sets compassConfigMutable()->magZero.raw[X] (if USE_MAG)." },
  { "magZeroY", "uint16_t", "2", "Raw ADC", "Sets compassConfigMutable()->magZero.raw[Y] (if USE_MAG)." },
  { "magZeroZ", "uint16_t", "2", "Raw ADC", "Sets compassConfigMutable()->magZero.raw[Z] (if USE_MAG)." },
  { "opflowScale", "uint16_t", "2", "Scale 256", "Sets opticalFlowConfigMutable()->opflow_scale = value / 256.0f (if USE_OPFLOW)." },
  { "magGainX", "uint16_t", "2", "Raw ADC", "Sets compassConfigMutable()->magGain[X] (if USE_MAG)." },
  { "magGainY", "uint16_t", "2", "Raw ADC", "Sets compassConfigMutable()->magGain[Y] (if USE_MAG)." },
  { "magGainZ", "uint16_t", "2", "Raw ADC", "Sets compassConfigMutable()->magGain[Z] (if USE_MAG)." },
};

inline constexpr Field FIELDS_13[] = {
  { "weightZBaroP", "uint16_t", "2", "Weight 100", "Barometer Z position fusion weight (positionEstimationConfig()->w_z_baro_p 100)." },
  { "weightZGPSP", "uint16_t", "2", "Weight 100", "GPS Z position fusion weight (positionEstimationConfig()->w_z_gps_p 100)." },
  { "weightZGPSV", "uint16_t", "2", "Weight 100", "GPS Z velocity fusion weight (positionEstimationConfig()->w_z_gps_v 100)." },
  { "weightXYGPSP", "uint16_t", "2", "Weight 100", "GPS XY position fusion weight (positionEstimationConfig()->w_xy_gps_p 100)." },
  { "weightXYGPSV", "uint16_t", "2", "Weight 100", "GPS XY velocity fusion weight (positionEstimationConfig()->w_xy_gps_v 100)." },
  { "minSats", "uint8_t", "1", "Count", "Minimum satellites required for GPS use (gpsConfigMutable()->gpsMinSats)." },
  { "useGPSVelNED", "uint8_t", "1", "Boolean", "Legacy flag, always 1 (GPS velocity is always used if available)." },
};

inline constexpr Field FIELDS_14[] = {
  { "weightZBaroP", "uint16_t", "2", "Weight 100", "Sets positionEstimationConfigMutable()->w_z_baro_p = value / 100.0f (constrained 0.0-10.0)." },
  { "weightZGPSP", "uint16_t", "2", "Weight 100", "Sets positionEstimationConfigMutable()->w_z_gps_p = value / 100.0f (constrained 0.0-10.0)." },
  { "weightZGPSV", "uint16_t", "2", "Weight 100", "Sets positionEstimationConfigMutable()->w_z_gps_v = value / 100.0f (constrained 0.0-10.0)." },
  { "weightXYGPSP", "uint16_t", "2", "Weight 100", "Sets positionEstimationConfigMutable()->w_xy_gps_p = value / 100.0f (constrained 0.0-10.0)." },
  { "weightXYGPSV", "uint16_t", "2", "Weight 100", "Sets positionEstimationConfigMutable()->w_xy_gps_v = value / 100.0f (constrained 0.0-10.0)." },
  { "minSats", "uint8_t", "1", "Count", "Sets gpsConfigMutable()->gpsMinSats (constrained 5-10)." },
  { "useGPSVelNED", "uint8_t", "1", "Boolean", "Legacy flag, ignored." },
};

inline constexpr Field FIELDS_15[] = {
  { "missionID", "uint8_t", "1", "", "Reserved for future use, currently ignored." },
};

inline constexpr Field FIELDS_16[] = {
  { "missionID", "uint8_t", "1", "", "Reserved for future use, currently ignored." },
};

inline constexpr Field FIELDS_17[] = {
  { "wpCapabilities", "uint8_t", "1", "", "Reserved for future waypoint capabilities flags. Currently always 0." },
  { "maxWaypoints", "uint8_t", "1", "", "Maximum number of waypoints supported (NAV_MAX_WAYPOINTS)." },
  { "missionValid", "uint8_t", "1", "", "Boolean flag indicating if the current mission in RAM is valid (isWaypointListValid())." },
  { "waypointCount", "uint8_t", "1", "", "Number of waypoints currently defined in the mission (getWaypointCount())." },
};

inline constexpr Field FIELDS_18[] = {
  { "minRthDistance", "uint16_t", "2", "meters", "Minimum distance from home required for RTH to engage (navConfig()->general.min_rth_distance)." },
  { "rthClimbFirst", "uint8_t", "1", "Boolean", "Flag: Climb to RTH altitude before returning (navConfig()->general.flags.rth_climb_first)." },
  { "rthClimbIgnoreEmerg", "uint8_t", "1", "Boolean", "Flag: Climb even in emergency RTH (navConfig()->general.flags.rth_climb_ignore_emerg)." },
  { "rthTailFirst", "uint8_t", "1", "Boolean", "Flag: Multirotor returns tail-first (navConfig()->general.flags.rth_tail_first)." },
  { "rthAllowLanding", "uint8_t", "1", "Boolean", "Flag: Allow automatic landing after RTH (navConfig()->general.flags.rth_allow_landing)." },
  { "rthAltControlMode", "uint8_t", "1", "Enum", "RTH altitude control mode (navConfig()->general.flags.rth_alt_control_mode)." },
  { "rthAbortThreshold", "uint16_t", "2", "cm/s", "Stick input threshold to abort RTH (navConfig()->general.rth_abort_threshold)." },
  { "rthAltitude", "uint16_t", "2", "meters", "Target RTH altitude (navConfig()->general.rth_altitude)." },
  { "landMinAltVspd", "uint16_t", "2", "cm/s", "Landing vertical speed at minimum slowdown altitude (navConfig()->general.land_minalt_vspd)." },
  { "landMaxAltVspd", "uint16_t", "2", "cm/s", "Landing vertical speed at maximum slowdown altitude (navConfig()->general.land_maxalt_vspd)." },
  { "landSlowdownMinAlt", "uint16_t", "2", "meters", "Altitude below which landMinAltVspd applies (navConfig()->general.land_slowdown_minalt)." },
  { "landSlowdownMaxAlt", "uint16_t", "2", "meters", "Altitude above which landMaxAltVspd applies (navConfig()->general.land_slowdown_maxalt)." },
  { "emergDescentRate", "uint16_t", "2", "cm/s", "Vertical speed during emergency landing descent (navConfig()->general.emerg_descent_rate)." },
};

inline constexpr Field FIELDS_19[] = {
  { "minRthDistance", "uint16_t", "2", "meters", "Sets navConfigMutable()->general.min_rth_distance." },
  { "rthClimbFirst", "uint8_t", "1", "Boolean", "Sets navConfigMutable()->general.flags.rth_climb_first." },
  { "rthClimbIgnoreEmerg", "uint8_t", "1", "Boolean", "Sets navConfigMutable()->general.flags.rth_climb_ignore_emerg." },
  { "rthTailFirst", "uint8_t", "1", "Boolean", "Sets navConfigMutable()->general.flags.rth_tail_first." },
  { "rthAllowLanding", "uint8_t", "1", "Boolean", "Sets navConfigMutable()->general.flags.rth_allow_landing." },
  { "rthAltControlMode", "uint8_t", "1", "Enum", "Sets navConfigMutable()->general.flags.rth_alt_control_mode." },
  { "rthAbortThreshold", "uint16_t", "2", "cm/s", "Sets navConfigMutable()->general.rth_abort_threshold." },
  { "rthAltitude", "uint16_t", "2", "meters", "Sets navConfigMutable()->general.rth_altitude." },
  { "landMinAltVspd", "uint16_t", "2", "cm/s", "Sets navConfigMutable()->general.land_minalt_vspd." },
  { "landMaxAltVspd", "uint16_t", "2", "cm/s", "Sets navConfigMutable()->general.land_maxalt_vspd." },
  { "landSlowdownMinAlt", "uint16_t", "2", "meters", "Sets navConfigMutable()->general.land_slowdown_minalt." },
  { "landSlowdownMaxAlt", "uint16_t", "2", "meters", "Sets navConfigMutable()->general.land_slowdown_maxalt." },
  { "emergDescentRate", "uint16_t", "2", "cm/s", "Sets navConfigMutable()->general.emerg_descent_rate." },
};

inline constexpr Field FIELDS_20[] = {
  { "cruiseThrottle", "uint16_t", "2", "PWM", "Cruise throttle level (currentBatteryProfile->nav.fw.cruise_throttle)." },
  { "minThrottle", "uint16_t", "2", "PWM", "Minimum throttle during autonomous flight (currentBatteryProfile->nav.fw.min_throttle)." },
  { "maxThrottle", "uint16_t", "2", "PWM", "Maximum throttle during autonomous flight (currentBatteryProfile->nav.fw.max_throttle)." },
  { "maxBankAngle", "uint8_t", "1", "degrees", "Maximum bank angle allowed (navConfig()->fw.max_bank_angle)." },
  { "maxClimbAngle", "uint8_t", "1", "degrees", "Maximum pitch angle during climb (navConfig()->fw.max_climb_angle)." },
  { "maxDiveAngle", "uint8_t", "1", "degrees", "Maximum negative pitch angle during descent (navConfig()->fw.max_dive_angle)." },
  { "pitchToThrottle", "uint8_t", "1", "Ratio (%)", "Pitch-to-throttle feed-forward ratio (currentBatteryProfile->nav.fw.pitch_to_throttle)." },
  { "loiterRadius", "uint16_t", "2", "meters", "Default loiter radius (navConfig()->fw.loiter_radius)." },
};

inline constexpr Field FIELDS_21[] = {
  { "cruiseThrottle", "uint16_t", "2", "PWM", "Sets currentBatteryProfileMutable->nav.fw.cruise_throttle." },
  { "minThrottle", "uint16_t", "2", "PWM", "Sets currentBatteryProfileMutable->nav.fw.min_throttle." },
  { "maxThrottle", "uint16_t", "2", "PWM", "Sets currentBatteryProfileMutable->nav.fw.max_throttle." },
  { "maxBankAngle", "uint8_t", "1", "degrees", "Sets navConfigMutable()->fw.max_bank_angle." },
  { "maxClimbAngle", "uint8_t", "1", "degrees", "Sets navConfigMutable()->fw.max_climb_angle." },
  { "maxDiveAngle", "uint8_t", "1", "degrees", "Sets navConfigMutable()->fw.max_dive_angle." },
  { "pitchToThrottle", "uint8_t", "1", "Ratio (%)", "Sets currentBatteryProfileMutable->nav.fw.pitch_to_throttle." },
  { "loiterRadius", "uint16_t", "2", "meters", "Sets navConfigMutable()->fw.loiter_radius." },
};

inline constexpr Field FIELDS_22[] = {
  { "modePermanentId", "uint8_t", "1", "ID", "Permanent ID of the flight mode (maps to boxId via findBoxByActiveBoxId). 0 if entry unused." },
  { "auxChannelIndex", "uint8_t", "1", "Index", "0-based index of the AUX channel used for activation." },
  { "rangeStartStep", "uint8_t", "1", "0-20", "Start step (corresponding to channel value range 900-2100 in steps of 50/25, depends on steps calculation)." },
  { "rangeEndStep", "uint8_t", "1", "0-20", "End step for the activation range." },
};

inline constexpr Field FIELDS_23[] = {
  { "rangeIndex", "uint8_t", "1", "Index", "Index of the mode range to set (0 to MAX_MODE_ACTIVATION_CONDITION_COUNT - 1)." },
  { "modePermanentId", "uint8_t", "1", "ID", "Permanent ID of the flight mode to assign." },
  { "auxChannelIndex", "uint8_t", "1", "Index", "0-based index of the AUX channel." },
  { "rangeStartStep", "uint8_t", "1", "0-20", "Start step for activation." },
  { "rangeEndStep", "uint8_t", "1", "0-20", "End step for activation." },
};

inline constexpr Field FIELDS_24[] = {
  { "featureMask", "uint32_t", "4", "", "Bitmask of active features (see featureMask())." },
};

inline constexpr Field FIELDS_25[] = {
  { "featureMask", "uint32_t", "4", "", "Bitmask of features to enable." },
};

inline constexpr Field FIELDS_26[] = {
  { "rollAlign", "uint16_t", "2", "deci-degrees", "Board alignment roll angle (boardAlignment()->rollDeciDegrees)." },
  { "pitchAlign", "uint16_t", "2", "deci-degrees", "Board alignment pitch angle (boardAlignment()->pitchDeciDegrees)." },
  { "yawAlign", "uint16_t", "2", "deci-degrees", "Board alignment yaw angle (boardAlignment()->yawDeciDegrees)." },
};

inline constexpr Field FIELDS_27[] = {
  { "rollAlign", "uint16_t", "2", "deci-degrees", "Sets boardAlignmentMutable()->rollDeciDegrees." },
  { "pitchAlign", "uint16_t", "2", "deci-degrees", "Sets boardAlignmentMutable()->pitchDeciDegrees." },
  { "yawAlign", "uint16_t", "2", "deci-degrees", "Sets boardAlignmentMutable()->yawDeciDegrees." },
};

inline constexpr Field FIELDS_28[] = {
  { "scale", "uint16_t", "2", "mV/10A or similar", "Current sensor scale factor (batteryMetersConfig()->current.scale). Units depend on sensor type." },
  { "offset", "uint16_t", "2", "mV", "Current sensor offset (batteryMetersConfig()->current.offset)." },
  { "type", "uint8_t", "1", "Enum", "Type of current sensor hardware (batteryMetersConfig()->current.type)." },
  { "capacity", "uint16_t", "2", "mAh (legacy)", "Battery capacity (constrained 0-65535) (currentBatteryProfile->capacity.value). Note: This is legacy, use MSP2_INAV_BATTERY_CONFIG for full 32-bit capacity." },
};

inline constexpr Field FIELDS_29[] = {
  { "scale", "uint16_t", "2", "mV/10A or similar", "Sets batteryMetersConfigMutable()->current.scale." },
  { "offset", "uint16_t", "2", "mV", "Sets batteryMetersConfigMutable()->current.offset." },
  { "type", "uint8_t", "1", "Enum", "Sets batteryMetersConfigMutable()->current.type." },
  { "capacity", "uint16_t", "2", "mAh (legacy)", "Sets currentBatteryProfileMutable->capacity.value (truncated to 16 bits)." },
};

inline constexpr Field FIELDS_30[] = {
  { "mixerMode", "uint8_t", "1", "", "Always 3 (QuadX) in INAV for compatibility." },
};

inline constexpr Field FIELDS_31[] = {
  { "mixerMode", "uint8_t", "1", "", "Mixer mode to set (ignored by INAV)." },
};

inline constexpr Field FIELDS_32[] = {
  { "serialRxProvider", "uint8_t", "1", "Enum", "Serial RX provider type (rxConfig()->serialrx_provider)." },
  { "maxCheck", "uint16_t", "2", "PWM", "Upper channel value threshold for stick commands (rxConfig()->maxcheck)." },
  { "midRc", "uint16_t", "2", "PWM", "Center channel value (PWM_RANGE_MIDDLE, typically 1500)." },
  { "minCheck", "uint16_t", "2", "PWM", "Lower channel value threshold for stick commands (rxConfig()->mincheck)." },
  { "spektrumSatBind", "uint8_t", "1", "Count/Flag", "Spektrum bind pulses (rxConfig()->spektrum_sat_bind). 0 if USE_SPEKTRUM_BIND disabled." },
  { "rxMinUsec", "uint16_t", "2", "µs", "Minimum expected pulse width (rxConfig()->rx_min_usec)." },
  { "rxMaxUsec", "uint16_t", "2", "µs", "Maximum expected pulse width (rxConfig()->rx_max_usec)." },
  { "bfCompatRcInterpolation", "uint8_t", "1", "-", "BF compatibility. Always 0." },
  { "bfCompatRcInterpolationInt", "uint8_t", "1", "-", "BF compatibility. Always 0." },
  { "bfCompatAirModeThreshold", "uint16_t", "2", "-", "BF compatibility. Always 0." },
  { "reserved1", "uint8_t", "1", "-", "Reserved/Padding. Always 0." },
  { "reserved2", "uint32_t", "4", "-", "Reserved/Padding. Always 0." },
  { "reserved3", "uint8_t", "1", "-", "Reserved/Padding. Always 0." },
  { "bfCompatFpvCamAngle", "uint8_t", "1", "-", "BF compatibility. Always 0." },
  { "receiverType", "uint8_t", "1", "Enum", "Receiver type (Parallel PWM, PPM, Serial) (rxConfig()->receiverType)." },
};

inline constexpr Field FIELDS_33[] = {
  { "serialRxProvider", "uint8_t", "1", "Enum", "Sets rxConfigMutable()->serialrx_provider." },
  { "maxCheck", "uint16_t", "2", "PWM", "Sets rxConfigMutable()->maxcheck." },
  { "midRc", "uint16_t", "2", "PWM", "Ignored (PWM_RANGE_MIDDLE is used)." },
  { "minCheck", "uint16_t", "2", "PWM", "Sets rxConfigMutable()->mincheck." },
  { "spektrumSatBind", "uint8_t", "1", "Count/Flag", "Sets rxConfigMutable()->spektrum_sat_bind (if USE_SPEKTRUM_BIND)." },
  { "rxMinUsec", "uint16_t", "2", "µs", "Sets rxConfigMutable()->rx_min_usec." },
  { "rxMaxUsec", "uint16_t", "2", "µs", "Sets rxConfigMutable()->rx_max_usec." },
  { "bfCompatRcInterpolation", "uint8_t", "1", "-", "Ignored." },
  { "bfCompatRcInterpolationInt", "uint8_t", "1", "-", "Ignored." },
  { "bfCompatAirModeThreshold", "uint16_t", "2", "-", "Ignored." },
  { "reserved1", "uint8_t", "1", "-", "Ignored." },
  { "reserved2", "uint32_t", "4", "-", "Ignored." },
  { "reserved3", "uint8_t", "1", "-", "Ignored." },
  { "bfCompatFpvCamAngle", "uint8_t", "1", "-", "Ignored." },
  { "receiverType", "uint8_t", "1", "Enum", "Sets rxConfigMutable()->receiverType." },
};

inline constexpr Field FIELDS_34[] = {
  { "hue", "uint16_t", "2", "", "Hue value (0-359)." },
  { "saturation", "uint8_t", "1", "", "Saturation value (0-255)." },
  { "value", "uint8_t", "1", "", "Value/Brightness (0-255)." },
};

inline constexpr Field FIELDS_35[] = {
  { "hue", "uint16_t", "2", "", "Hue value (0-359)." },
  { "saturation", "uint8_t", "1", "", "Saturation value (0-255)." },
  { "value", "uint8_t", "1", "", "Value/Brightness (0-255)." },
};

inline constexpr Field FIELDS_36[] = {
  { "legacyLedConfig", "uint32_t", "4", "", "Packed LED configuration (position, function, overlay, color, direction, params). See C code for bit packing details." },
};

inline constexpr Field FIELDS_37[] = {
  { "ledIndex", "uint8_t", "1", "", "Index of the LED to configure (0 to LED_MAX_STRIP_LENGTH - 1)." },
  { "legacyLedConfig", "uint32_t", "4", "", "Packed LED configuration to set." },
};

inline constexpr Field FIELDS_38[] = {
  { "rssiChannel", "uint8_t", "1", "", "AUX channel index (1-based) used for RSSI, or 0 if disabled (rxConfig()->rssi_channel)." },
};

inline constexpr Field FIELDS_39[] = {
  { "rssiChannel", "uint8_t", "1", "", "AUX channel index (1-based) to use for RSSI, or 0 to disable." },
};

inline constexpr Field FIELDS_40[] = {
  { "adjustmentIndex", "uint8_t", "1", "", "Index of the adjustment slot (0 to MAX_SIMULTANEOUS_ADJUSTMENT_COUNT - 1)." },
  { "auxChannelIndex", "uint8_t", "1", "", "0-based index of the AUX channel controlling the adjustment value." },
  { "rangeStartStep", "uint8_t", "1", "", "Start step (0-20) of the control channel range." },
  { "rangeEndStep", "uint8_t", "1", "", "End step (0-20) of the control channel range." },
  { "adjustmentFunction", "uint8_t", "1", "", "Function/parameter being adjusted (e.g., PID gain, rate). See rcAdjustments.h enum." },
  { "auxSwitchChannelIndex", "uint8_t", "1", "", "0-based index of the AUX channel acting as an enable switch (or 0 if always enabled)." },
};

inline constexpr Field FIELDS_41[] = {
  { "rangeIndex", "uint8_t", "1", "", "Index of the adjustment range to set (0 to MAX_ADJUSTMENT_RANGE_COUNT - 1)." },
  { "adjustmentIndex", "uint8_t", "1", "", "Adjustment slot index (0 to MAX_SIMULTANEOUS_ADJUSTMENT_COUNT - 1)." },
  { "auxChannelIndex", "uint8_t", "1", "", "0-based index of the control AUX channel." },
  { "rangeStartStep", "uint8_t", "1", "", "Start step (0-20)." },
  { "rangeEndStep", "uint8_t", "1", "", "End step (0-20)." },
  { "adjustmentFunction", "uint8_t", "1", "", "Function/parameter being adjusted." },
  { "auxSwitchChannelIndex", "uint8_t", "1", "", "0-based index of the enable switch AUX channel (or 0)." },
};

inline constexpr Field FIELDS_44[] = {
  { "vbatScale", "uint8_t", "1", "Scale / 10", "Voltage sensor scale factor / 10 (batteryMetersConfig()->voltage.scale / 10). 0 if USE_ADC disabled." },
  { "vbatMinCell", "uint8_t", "1", "0.1V", "Minimum cell voltage / 10 (currentBatteryProfile->voltage.cellMin / 10). 0 if USE_ADC disabled." },
  { "vbatMaxCell", "uint8_t", "1", "0.1V", "Maximum cell voltage / 10 (currentBatteryProfile->voltage.cellMax / 10). 0 if USE_ADC disabled." },
  { "vbatWarningCell", "uint8_t", "1", "0.1V", "Warning cell voltage / 10 (currentBatteryProfile->voltage.cellWarning / 10). 0 if USE_ADC disabled." },
};

inline constexpr Field FIELDS_45[] = {
  { "vbatScale", "uint8_t", "1", "Scale / 10", "Sets batteryMetersConfigMutable()->voltage.scale = value 10 (if USE_ADC)." },
  { "vbatMinCell", "uint8_t", "1", "0.1V", "Sets currentBatteryProfileMutable->voltage.cellMin = value 10 (if USE_ADC)." },
  { "vbatMaxCell", "uint8_t", "1", "0.1V", "Sets currentBatteryProfileMutable->voltage.cellMax = value 10 (if USE_ADC)." },
  { "vbatWarningCell", "uint8_t", "1", "0.1V", "Sets currentBatteryProfileMutable->voltage.cellWarning = value 10 (if USE_ADC)." },
};

inline constexpr Field FIELDS_46[] = {
  { "rangefinderAltitude", "uint32_t", "4", "cm", "Latest altitude reading from the rangefinder (rangefinderGetLatestAltitude()). 0 if USE_RANGEFINDER disabled or no reading." },
};

inline constexpr Field FIELDS_47[] = {
  { "rcMap", "uint8_t[MAX_MAPPABLE_RX_INPUTS]", "MAX_MAPPABLE_RX_INPUTS", "", "Array defining the mapping from input channel index to logical function (Roll, Pitch, Yaw, Throttle, Aux1...)." },
};

inline constexpr Field FIELDS_48[] = {
  { "rcMap", "uint8_t[MAX_MAPPABLE_RX_INPUTS]", "MAX_MAPPABLE_RX_INPUTS", "", "Array defining the new channel mapping." },
};

inline constexpr Field FIELDS_50[] = {
  { "flashReady", "uint8_t", "1", "", "Boolean: 1 if flash chip is ready, 0 otherwise. (flashIsReady()). 0 if USE_FLASHFS disabled." },
  { "sectorCount", "uint32_t", "4", "", "Total number of sectors on the flash chip (geometry->sectors). 0 if USE_FLASHFS disabled." },
  { "totalSize", "uint32_t", "4", "", "Total size of the flash chip in bytes (geometry->totalSize). 0 if USE_FLASHFS disabled." },
  { "usedSize", "uint32_t", "4", "", "Currently used size in bytes (FlashFS offset) (flashfsGetOffset()). 0 if USE_FLASHFS disabled." },
};

inline constexpr Field FIELDS_51[] = {
  { "address", "uint32_t", "4", "", "Starting address to read from within the FlashFS volume." },
  { "size", "uint16_t", "2", "", "(Optional) Number of bytes to read. Defaults to 128 if not provided." },
  { "address", "uint32_t", "4", "", "The starting address from which data was actually read." },
  { "data", "uint8_t[]", "Variable", "", "The data read from flash. Length is MIN(requested size, remaining buffer space, remaining flashfs data)." },
};

inline constexpr Field FIELDS_53[] = {
  { "looptime", "uint16_t", "2", "µs", "Configured loop time (gyroConfig()->looptime)." },
};

inline constexpr Field FIELDS_54[] = {
  { "looptime", "uint16_t", "2", "µs", "New loop time to set (gyroConfigMutable()->looptime)." },
};

inline constexpr Field FIELDS_55[] = {
  { "failsafeDelay", "uint8_t", "1", "0.1s", "Delay before failsafe stage 1 activates (failsafeConfig()->failsafe_delay)." },
  { "failsafeOffDelay", "uint8_t", "1", "0.1s", "Delay after signal recovery before returning control (failsafeConfig()->failsafe_off_delay)." },
  { "failsafeThrottle", "uint16_t", "2", "PWM", "Throttle level during failsafe stage 2 (currentBatteryProfile->failsafe_throttle)." },
  { "legacyKillSwitch", "uint8_t", "1", "-", "Legacy flag, always 0." },
  { "failsafeThrottleLowDelay", "uint16_t", "2", "ms", "Delay for throttle-based failsafe detection (failsafeConfig()->failsafe_throttle_low_delay)." },
  { "failsafeProcedure", "uint8_t", "1", "Enum", "Failsafe procedure (Drop, RTH, Land, etc.) (failsafeConfig()->failsafe_procedure)." },
  { "failsafeRecoveryDelay", "uint8_t", "1", "0.1s", "Delay after RTH finishes before attempting recovery (failsafeConfig()->failsafe_recovery_delay)." },
  { "failsafeFWRollAngle", "uint16_t", "2", "deci-degrees", "Fixed wing failsafe roll angle (failsafeConfig()->failsafe_fw_roll_angle)." },
  { "failsafeFWPitchAngle", "uint16_t", "2", "deci-degrees", "Fixed wing failsafe pitch angle (failsafeConfig()->failsafe_fw_pitch_angle)." },
  { "failsafeFWYawRate", "uint16_t", "2", "deg/s", "Fixed wing failsafe yaw rate (failsafeConfig()->failsafe_fw_yaw_rate)." },
  { "failsafeStickThreshold", "uint16_t", "2", "PWM units", "Stick movement threshold to exit failsafe (failsafeConfig()->failsafe_stick_motion_threshold)." },
  { "failsafeMinDistance", "uint16_t", "2", "meters", "Minimum distance from home for RTH failsafe (failsafeConfig()->failsafe_min_distance)." },
  { "failsafeMinDistanceProc", "uint8_t", "1", "Enum", "Failsafe procedure if below min distance (failsafeConfig()->failsafe_min_distance_procedure)." },
};

inline constexpr Field FIELDS_56[] = {
  { "failsafeDelay", "uint8_t", "1", "0.1s", "Sets failsafeConfigMutable()->failsafe_delay." },
  { "failsafeOffDelay", "uint8_t", "1", "0.1s", "Sets failsafeConfigMutable()->failsafe_off_delay." },
  { "failsafeThrottle", "uint16_t", "2", "PWM", "Sets currentBatteryProfileMutable->failsafe_throttle." },
  { "legacyKillSwitch", "uint8_t", "1", "-", "Ignored." },
  { "failsafeThrottleLowDelay", "uint16_t", "2", "ms", "Sets failsafeConfigMutable()->failsafe_throttle_low_delay." },
  { "failsafeProcedure", "uint8_t", "1", "Enum", "Sets failsafeConfigMutable()->failsafe_procedure." },
  { "failsafeRecoveryDelay", "uint8_t", "1", "0.1s", "Sets failsafeConfigMutable()->failsafe_recovery_delay." },
  { "failsafeFWRollAngle", "uint16_t", "2", "deci-degrees", "Sets failsafeConfigMutable()->failsafe_fw_roll_angle (casted to int16_t)." },
  { "failsafeFWPitchAngle", "uint16_t", "2", "deci-degrees", "Sets failsafeConfigMutable()->failsafe_fw_pitch_angle (casted to int16_t)." },
  { "failsafeFWYawRate", "uint16_t", "2", "deg/s", "Sets failsafeConfigMutable()->failsafe_fw_yaw_rate (casted to int16_t)." },
  { "failsafeStickThreshold", "uint16_t", "2", "PWM units", "Sets failsafeConfigMutable()->failsafe_stick_motion_threshold." },
  { "failsafeMinDistance", "uint16_t", "2", "meters", "Sets failsafeConfigMutable()->failsafe_min_distance." },
  { "failsafeMinDistanceProc", "uint8_t", "1", "Enum", "Sets failsafeConfigMutable()->failsafe_min_distance_procedure." },
};

inline constexpr Field FIELDS_57[] = {
  { "sdCardSupported", "uint8_t", "1", "", "Bitmask: Bit 0 = 1 if SD card support compiled in (USE_SDCARD)." },
  { "sdCardState", "uint8_t", "1", "", "Enum (mspSDCardState_e): Current state (Not Present, Fatal, Card Init, FS Init, Ready). 0 if USE_SDCARD disabled." },
  { "fsError", "uint8_t", "1", "", "Last filesystem error code (afatfs_getLastError()). 0 if USE_SDCARD disabled." },
  { "freeSpaceKB", "uint32_t", "4", "", "Free space in KiB (afatfs_getContiguousFreeSpace() / 1024). 0 if USE_SDCARD disabled." },
  { "totalSpaceKB", "uint32_t", "4", "", "Total space in KiB (sdcard_getMetadata()->numBlocks / 2). 0 if USE_SDCARD disabled." },
};

inline constexpr Field FIELDS_58[] = {
  { "blackboxDevice", "uint8_t", "1", "", "Always 0 (API no longer supported)." },
  { "blackboxRateNum", "uint8_t", "1", "", "Always 0." },
  { "blackboxRateDenom", "uint8_t", "1", "", "Always 0." },
  { "blackboxPDenom", "uint8_t", "1", "", "Always 0." },
};

inline constexpr Field FIELDS_62[] = {
  { "osdDriverType", "uint8_t", "1", "Enum", "OSD_DRIVER_MAX7456 if USE_OSD, else OSD_DRIVER_NONE." },
  { "videoSystem", "uint8_t", "1", "Enum", "Video system (Auto/PAL/NTSC) (osdConfig()->video_system). Sent even if OSD disabled." },
  { "units", "uint8_t", "1", "Enum", "Measurement units (Metric/Imperial) (osdConfig()->units). Sent even if OSD disabled." },
  { "rssiAlarm", "uint8_t", "1", "%", "RSSI alarm threshold (osdConfig()->rssi_alarm). Sent even if OSD disabled." },
  { "capAlarm", "uint16_t", "2", "mAh/mWh", "Capacity alarm threshold (currentBatteryProfile->capacity.warning). Sent even if OSD disabled." },
  { "timerAlarm", "uint16_t", "2", "seconds", "Timer alarm threshold (osdConfig()->time_alarm). Sent even if OSD disabled." },
  { "altAlarm", "uint16_t", "2", "meters", "Altitude alarm threshold (osdConfig()->alt_alarm). Sent even if OSD disabled." },
  { "distAlarm", "uint16_t", "2", "meters", "Distance alarm threshold (osdConfig()->dist_alarm). Sent even if OSD disabled." },
  { "negAltAlarm", "uint16_t", "2", "meters", "Negative altitude alarm threshold (osdConfig()->neg_alt_alarm). Sent even if OSD disabled." },
  { "itemPositions", "uint16_t[OSD_ITEM_COUNT]", "OSD_ITEM_COUNT 2", "Coordinates", "Packed X/Y position for each OSD item on screen 0 (osdLayoutsConfig()->item_pos[0][i]). Sent even if OSD disabled." },
};

inline constexpr Field FIELDS_63[] = {
  { "addr", "uint8_t", "1", "-", "Must be 0xFF (-1)." },
  { "videoSystem", "uint8_t", "1", "Enum", "Sets osdConfigMutable()->video_system." },
  { "units", "uint8_t", "1", "Enum", "Sets osdConfigMutable()->units." },
  { "rssiAlarm", "uint8_t", "1", "%", "Sets osdConfigMutable()->rssi_alarm." },
  { "capAlarm", "uint16_t", "2", "mAh/mWh", "Sets currentBatteryProfileMutable->capacity.warning." },
  { "timerAlarm", "uint16_t", "2", "seconds", "Sets osdConfigMutable()->time_alarm." },
  { "altAlarm", "uint16_t", "2", "meters", "Sets osdConfigMutable()->alt_alarm." },
  { "distAlarm", "uint16_t", "2", "meters", "(Optional) Sets osdConfigMutable()->dist_alarm." },
  { "negAltAlarm", "uint16_t", "2", "meters", "(Optional) Sets osdConfigMutable()->neg_alt_alarm." },
  { "itemIndex", "uint8_t", "1", "Index", "Index of the OSD item to position (0 to OSD_ITEM_COUNT - 1)." },
};

inline constexpr Field FIELDS_65[] = {
  { "address", "uint8_t or uint16_t", "1 or 2", "", "Starting address in font memory. Size depends on total payload size." },
  { "charData", "uint8_t[]", "Variable", "", "Character bitmap data (54 or 64 bytes per char, depending on format)." },
};

inline constexpr Field FIELDS_66[] = {
  { "vtxDeviceType", "uint8_t", "1", "", "Enum (VTXDEV_): Type of VTX device detected/configured. VTXDEV_UNKNOWN if none." },
  { "band", "uint8_t", "1", "", "VTX band number (from vtxSettingsConfig)." },
  { "channel", "uint8_t", "1", "", "VTX channel number (from vtxSettingsConfig)." },
  { "power", "uint8_t", "1", "", "VTX power level index (from vtxSettingsConfig)." },
  { "pitMode", "uint8_t", "1", "", "Boolean: 1 if VTX is currently in pit mode, 0 otherwise." },
  { "vtxReady", "uint8_t", "1", "", "Boolean: 1 if VTX device reported ready, 0 otherwise." },
  { "lowPowerDisarm", "uint8_t", "1", "", "Boolean: 1 if low power on disarm is enabled (from vtxSettingsConfig)." },
  { "vtxTableAvailable", "uint8_t", "1", "", "Boolean: 1 if VTX tables (band/power) are available for query." },
  { "bandCount", "uint8_t", "1", "", "Number of bands supported by the VTX device." },
  { "channelCount", "uint8_t", "1", "", "Number of channels per band supported by the VTX device." },
  { "powerCount", "uint8_t", "1", "", "Number of power levels supported by the VTX device." },
};

inline constexpr Field FIELDS_67[] = {
  { "bandChannelEncoded", "uint16_t", "2", "", "Encoded band/channel value: (band-1)8 + (channel-1). If <= VTXCOMMON_MSP_BANDCHAN_CHKVAL." },
  { "power", "uint8_t", "1", "", "Power level index to set (vtxSettingsConfigMutable()->power)." },
  { "pitMode", "uint8_t", "1", "", "Pit mode state to set (0=off, 1=on). Directly calls vtxCommonSetPitMode." },
  { "lowPowerDisarm", "uint8_t", "1", "", "Low power on disarm setting (vtxSettingsConfigMutable()->lowPowerDisarm)." },
  { "pitModeFreq", "uint16_t", "2", "", "Ignored. Betaflight extension." },
  { "band", "uint8_t", "1", "", "Explicit band number to set (vtxSettingsConfigMutable()->band). Overrides encoded value if present." },
  { "channel", "uint8_t", "1", "", "Explicit channel number to set (vtxSettingsConfigMutable()->channel). Overrides encoded value if present." },
  { "frequency", "uint16_t", "2", "", "Ignored. Betaflight extension." },
  { "bandCount", "uint8_t", "1", "", "Ignored. Betaflight extension." },
  { "channelCount", "uint8_t", "1", "", "Ignored. Betaflight extension." },
  { "powerCount", "uint8_t", "1", "", "Ignored. Betaflight extension (can potentially reduce reported power count if valid)." },
};

inline constexpr Field FIELDS_68[] = {
  { "gyroSyncDenom", "uint8_t", "1", "", "Always 1 (BF compatibility)." },
  { "pidProcessDenom", "uint8_t", "1", "", "Always 1 (BF compatibility)." },
  { "useUnsyncedPwm", "uint8_t", "1", "", "Always 1 (BF compatibility, INAV uses async PWM based on protocol)." },
  { "motorPwmProtocol", "uint8_t", "1", "", "Enum: Motor PWM protocol type (motorConfig()->motorPwmProtocol)." },
  { "motorPwmRate", "uint16_t", "2", "", "Hz: Motor PWM rate (if applicable) (motorConfig()->motorPwmRate)." },
  { "servoPwmRate", "uint16_t", "2", "", "Hz: Servo PWM rate (servoConfig()->servoPwmRate)." },
  { "legacyGyroSync", "uint8_t", "1", "", "Always 0 (BF compatibility)." },
};

inline constexpr Field FIELDS_69[] = {
  { "gyroSyncDenom", "uint8_t", "1", "", "Ignored." },
  { "pidProcessDenom", "uint8_t", "1", "", "Ignored." },
  { "useUnsyncedPwm", "uint8_t", "1", "", "Ignored." },
  { "motorPwmProtocol", "uint8_t", "1", "", "Sets motorConfigMutable()->motorPwmProtocol." },
  { "motorPwmRate", "uint16_t", "2", "", "Sets motorConfigMutable()->motorPwmRate." },
  { "servoPwmRate", "uint16_t", "2", "", "Sets servoConfigMutable()->servoPwmRate." },
  { "legacyGyroSync", "uint8_t", "1", "", "Ignored." },
};

inline constexpr Field FIELDS_70[] = {
  { "gyroMainLpfHz", "uint8_t", "1", "Hz", "Gyro main low-pass filter cutoff frequency (gyroConfig()->gyro_main_lpf_hz)." },
  { "dtermLpfHz", "uint16_t", "2", "Hz", "D-term low-pass filter cutoff frequency (pidProfile()->dterm_lpf_hz)." },
  { "yawLpfHz", "uint16_t", "2", "Hz", "Yaw low-pass filter cutoff frequency (pidProfile()->yaw_lpf_hz)." },
  { "legacyGyroNotchHz", "uint16_t", "2", "-", "Always 0 (Legacy)." },
  { "legacyGyroNotchCutoff", "uint16_t", "2", "-", "Always 1 (Legacy)." },
  { "bfCompatDtermNotchHz", "uint16_t", "2", "-", "Always 0 (BF compatibility)." },
  { "bfCompatDtermNotchCutoff", "uint16_t", "2", "-", "Always 1 (BF compatibility)." },
  { "bfCompatGyroNotch2Hz", "uint16_t", "2", "-", "Always 0 (BF compatibility)." },
  { "bfCompatGyroNotch2Cutoff", "uint16_t", "2", "-", "Always 1 (BF compatibility)." },
  { "accNotchHz", "uint16_t", "2", "Hz", "Accelerometer notch filter center frequency (accelerometerConfig()->acc_notch_hz)." },
  { "accNotchCutoff", "uint16_t", "2", "Hz", "Accelerometer notch filter cutoff frequency (accelerometerConfig()->acc_notch_cutoff)." },
  { "legacyGyroStage2LpfHz", "uint16_t", "2", "-", "Always 0 (Legacy)." },
};

inline constexpr Field FIELDS_71[] = {
  { "gyroMainLpfHz", "uint8_t", "1", "Hz", "Sets gyroConfigMutable()->gyro_main_lpf_hz. (Size >= 5)" },
  { "dtermLpfHz", "uint16_t", "2", "Hz", "Sets pidProfileMutable()->dterm_lpf_hz (constrained 0-500). (Size >= 5)" },
  { "yawLpfHz", "uint16_t", "2", "Hz", "Sets pidProfileMutable()->yaw_lpf_hz (constrained 0-255). (Size >= 5)" },
  { "legacyGyroNotchHz", "uint16_t", "2", "-", "Ignored. (Size >= 9)" },
  { "legacyGyroNotchCutoff", "uint16_t", "2", "-", "Ignored. (Size >= 9)" },
  { "bfCompatDtermNotchHz", "uint16_t", "2", "-", "Ignored. (Size >= 13)" },
  { "bfCompatDtermNotchCutoff", "uint16_t", "2", "-", "Ignored. (Size >= 13)" },
  { "bfCompatGyroNotch2Hz", "uint16_t", "2", "-", "Ignored. (Size >= 17)" },
  { "bfCompatGyroNotch2Cutoff", "uint16_t", "2", "-", "Ignored. (Size >= 17)" },
  { "accNotchHz", "uint16_t", "2", "Hz", "Sets accelerometerConfigMutable()->acc_notch_hz (constrained 0-255). (Size >= 21)" },
  { "accNotchCutoff", "uint16_t", "2", "Hz", "Sets accelerometerConfigMutable()->acc_notch_cutoff (constrained 1-255). (Size >= 21)" },
  { "legacyGyroStage2LpfHz", "uint16_t", "2", "-", "Ignored. (Size >= 22)" },
};

inline constexpr Field FIELDS_72[] = {
  { "legacyRollPitchItermIgnore", "uint16_t", "2", "-", "Always 0 (Legacy)." },
  { "legacyYawItermIgnore", "uint16_t", "2", "-", "Always 0 (Legacy)." },
  { "legacyYawPLimit", "uint16_t", "2", "-", "Always 0 (Legacy)." },
  { "bfCompatDeltaMethod", "uint8_t", "1", "-", "Always 0 (BF compatibility)." },
  { "bfCompatVbatPidComp", "uint8_t", "1", "-", "Always 0 (BF compatibility)." },
  { "bfCompatSetpointRelaxRatio", "uint8_t", "1", "-", "Always 0 (BF compatibility)." },
  { "reserved1", "uint8_t", "1", "-", "Always 0." },
  { "legacyPidSumLimit", "uint16_t", "2", "-", "Always 0 (Legacy)." },
  { "bfCompatItermThrottleGain", "uint8_t", "1", "-", "Always 0 (BF compatibility)." },
  { "accelLimitRollPitch", "uint16_t", "2", "dps / 10", "Axis acceleration limit for Roll/Pitch / 10 (pidProfile()->axisAccelerationLimitRollPitch / 10)." },
  { "accelLimitYaw", "uint16_t", "2", "dps / 10", "Axis acceleration limit for Yaw / 10 (pidProfile()->axisAccelerationLimitYaw / 10)." },
};

inline constexpr Field FIELDS_73[] = {
  { "legacyRollPitchItermIgnore", "uint16_t", "2", "-", "Ignored." },
  { "legacyYawItermIgnore", "uint16_t", "2", "-", "Ignored." },
  { "legacyYawPLimit", "uint16_t", "2", "-", "Ignored." },
  { "bfCompatDeltaMethod", "uint8_t", "1", "-", "Ignored." },
  { "bfCompatVbatPidComp", "uint8_t", "1", "-", "Ignored." },
  { "bfCompatSetpointRelaxRatio", "uint8_t", "1", "-", "Ignored." },
  { "reserved1", "uint8_t", "1", "-", "Ignored." },
  { "legacyPidSumLimit", "uint16_t", "2", "-", "Ignored." },
  { "bfCompatItermThrottleGain", "uint8_t", "1", "-", "Ignored." },
  { "accelLimitRollPitch", "uint16_t", "2", "dps / 10", "Sets pidProfileMutable()->axisAccelerationLimitRollPitch = value 10." },
  { "accelLimitYaw", "uint16_t", "2", "dps / 10", "Sets pidProfileMutable()->axisAccelerationLimitYaw = value 10." },
};

inline constexpr Field FIELDS_74[] = {
  { "accHardware", "uint8_t", "1", "", "Enum (accHardware_e): Accelerometer hardware type (accelerometerConfig()->acc_hardware)." },
  { "baroHardware", "uint8_t", "1", "", "Enum (baroHardware_e): Barometer hardware type (barometerConfig()->baro_hardware). 0 if USE_BARO disabled." },
  { "magHardware", "uint8_t", "1", "", "Enum (magHardware_e): Magnetometer hardware type (compassConfig()->mag_hardware). 0 if USE_MAG disabled." },
  { "pitotHardware", "uint8_t", "1", "", "Enum (pitotHardware_e): Pitot tube hardware type (pitotmeterConfig()->pitot_hardware). 0 if USE_PITOT disabled." },
  { "rangefinderHardware", "uint8_t", "1", "", "Enum (rangefinderHardware_e): Rangefinder hardware type (rangefinderConfig()->rangefinder_hardware). 0 if USE_RANGEFINDER disabled." },
  { "opflowHardware", "uint8_t", "1", "", "Enum (opticalFlowHardware_e): Optical flow hardware type (opticalFlowConfig()->opflow_hardware). 0 if USE_OPFLOW disabled." },
};

inline constexpr Field FIELDS_75[] = {
  { "accHardware", "uint8_t", "1", "", "Sets accelerometerConfigMutable()->acc_hardware." },
  { "baroHardware", "uint8_t", "1", "", "Sets barometerConfigMutable()->baro_hardware (if USE_BARO)." },
  { "magHardware", "uint8_t", "1", "", "Sets compassConfigMutable()->mag_hardware (if USE_MAG)." },
  { "pitotHardware", "uint8_t", "1", "", "Sets pitotmeterConfigMutable()->pitot_hardware (if USE_PITOT)." },
  { "rangefinderHardware", "uint8_t", "1", "", "Sets rangefinderConfigMutable()->rangefinder_hardware (if USE_RANGEFINDER)." },
  { "opflowHardware", "uint8_t", "1", "", "Sets opticalFlowConfigMutable()->opflow_hardware (if USE_OPFLOW)." },
};

inline constexpr Field FIELDS_78[] = {
  { "MultiWii version", "uint8_t", "1", "n/a", "Scaled version major100+minor" },
  { "Mixer Mode", "uint8_t", "1", "Enumeration", "Mixer type" },
  { "MSP Version", "uint8_t", "1", "n/a", "Scaled version major100+minor" },
};

inline constexpr Field FIELDS_79[] = {
  { "cycleTime", "uint16_t", "2", "µs", "Main loop cycle time (cycleTime)." },
  { "i2cErrors", "uint16_t", "2", "Count", "Number of I2C errors encountered (i2cGetErrorCounter()). 0 if USE_I2C not defined." },
  { "sensorStatus", "uint16_t", "2", "Bitmask", "Bitmask indicating available/active sensors (packSensorStatus()). See notes." },
  { "activeModesLow", "uint32_t", "4", "Bitmask", "First 32 bits of the active flight modes bitmask (packBoxModeFlags())." },
  { "profile", "uint8_t", "1", "Index", "Current configuration profile index (0-based) (getConfigProfile())." },
};

inline constexpr Field FIELDS_80[] = {
  { "accX", "int16_t", "2", "~1/512 G", "Raw accelerometer X reading, scaled (acc.accADCf[X] 512)." },
  { "accY", "int16_t", "2", "~1/512 G", "Raw accelerometer Y reading, scaled (acc.accADCf[Y] 512)." },
  { "accZ", "int16_t", "2", "~1/512 G", "Raw accelerometer Z reading, scaled (acc.accADCf[Z] 512)." },
  { "gyroX", "int16_t", "2", "deg/s", "Gyroscope X-axis rate (gyroRateDps(X))." },
  { "gyroY", "int16_t", "2", "deg/s", "Gyroscope Y-axis rate (gyroRateDps(Y))." },
  { "gyroZ", "int16_t", "2", "deg/s", "Gyroscope Z-axis rate (gyroRateDps(Z))." },
  { "magX", "int16_t", "2", "Raw units", "Raw magnetometer X reading (mag.magADC[X]). 0 if USE_MAG disabled." },
  { "magY", "int16_t", "2", "Raw units", "Raw magnetometer Y reading (mag.magADC[Y]). 0 if USE_MAG disabled." },
  { "magZ", "int16_t", "2", "Raw units", "Raw magnetometer Z reading (mag.magADC[Z]). 0 if USE_MAG disabled." },
};

inline constexpr Field FIELDS_81[] = {
  { "servoOutputs", "int16_t[MAX_SUPPORTED_SERVOS]", "MAX_SUPPORTED_SERVOS 2", "PWM", "Array of current servo output values (typically 1000-2000)." },
};

inline constexpr Field FIELDS_82[] = {
  { "motorOutputs", "uint16_t[8]", "16", "PWM", "Array of current motor output values (typically 1000-2000). Values beyond MAX_SUPPORTED_MOTORS are 0." },
};

inline constexpr Field FIELDS_83[] = {
  { "rcChannels", "uint16_t[]", "rxRuntimeConfig.channelCount 2", "PWM", "Array of current RC channel values (typically 1000-2000). Length depends on detected channels." },
};

inline constexpr Field FIELDS_84[] = {
  { "fixType", "uint8_t", "1", "Enum", "GPS fix type (gpsSol.fixType)." },
  { "numSat", "uint8_t", "1", "Count", "Number of satellites used in solution (gpsSol.numSat)." },
  { "latitude", "int32_t", "4", "deg 1e7", "Latitude (gpsSol.llh.lat)." },
  { "longitude", "int32_t", "4", "deg 1e7", "Longitude (gpsSol.llh.lon)." },
  { "altitude", "int16_t", "2", "meters", "Altitude above MSL (gpsSol.llh.alt / 100)." },
  { "speed", "uint16_t", "2", "cm/s", "Ground speed (gpsSol.groundSpeed)." },
  { "groundCourse", "uint16_t", "2", "deci-degrees", "Ground course (gpsSol.groundCourse)." },
  { "hdop", "uint16_t", "2", "HDOP 100", "Horizontal Dilution of Precision (gpsSol.hdop)." },
};

inline constexpr Field FIELDS_85[] = {
  { "distanceToHome", "uint16_t", "2", "meters", "Distance to the home point (GPS_distanceToHome)." },
  { "directionToHome", "uint16_t", "2", "degrees", "Direction to the home point (0-360) (GPS_directionToHome)." },
  { "gpsHeartbeat", "uint8_t", "1", "Boolean", "Indicates if GPS data is being received (gpsSol.flags.gpsHeartbeat)." },
};

inline constexpr Field FIELDS_86[] = {
  { "roll", "int16_t", "2", "deci-degrees", "Roll angle (attitude.values.roll)." },
  { "pitch", "int16_t", "2", "deci-degrees", "Pitch angle (attitude.values.pitch)." },
  { "yaw", "int16_t", "2", "degrees", "Yaw/Heading angle (DECIDEGREES_TO_DEGREES(attitude.values.yaw))." },
};

inline constexpr Field FIELDS_87[] = {
  { "estimatedAltitude", "int32_t", "4", "cm", "Estimated altitude above home/sea level (getEstimatedActualPosition(Z))." },
  { "variometer", "int16_t", "2", "cm/s", "Estimated vertical speed (getEstimatedActualVelocity(Z))." },
  { "baroAltitude", "int32_t", "4", "cm", "Latest raw altitude from barometer (baroGetLatestAltitude()). 0 if USE_BARO disabled." },
};

inline constexpr Field FIELDS_88[] = {
  { "vbat", "uint8_t", "1", "0.1V", "Battery voltage, scaled (getBatteryVoltage() / 10), constrained 0-255." },
  { "mAhDrawn", "uint16_t", "2", "mAh", "Consumed battery capacity (getMAhDrawn()), constrained 0-65535." },
  { "rssi", "uint16_t", "2", "0-1023 or %", "Received Signal Strength Indicator (getRSSI()). Units depend on source." },
  { "amperage", "int16_t", "2", "0.01A", "Current draw (getAmperage()), constrained -32768 to 32767." },
};

inline constexpr Field FIELDS_89[] = {
  { "legacyRcRate", "uint8_t", "1", "", "Always 100 (Legacy, unused)." },
  { "rcExpo", "uint8_t", "1", "", "Roll/Pitch RC Expo (currentControlRateProfile->stabilized.rcExpo8)." },
  { "rollRate", "uint8_t", "1", "", "Roll Rate (currentControlRateProfile->stabilized.rates[FD_ROLL])." },
  { "pitchRate", "uint8_t", "1", "", "Pitch Rate (currentControlRateProfile->stabilized.rates[FD_PITCH])." },
  { "yawRate", "uint8_t", "1", "", "Yaw Rate (currentControlRateProfile->stabilized.rates[FD_YAW])." },
  { "dynamicThrottlePID", "uint8_t", "1", "", "Dynamic Throttle PID (TPA) value (currentControlRateProfile->throttle.dynPID)." },
  { "throttleMid", "uint8_t", "1", "", "Throttle Midpoint (currentControlRateProfile->throttle.rcMid8)." },
  { "throttleExpo", "uint8_t", "1", "", "Throttle Expo (currentControlRateProfile->throttle.rcExpo8)." },
  { "tpaBreakpoint", "uint16_t", "2", "", "Throttle PID Attenuation (TPA) breakpoint (currentControlRateProfile->throttle.pa_breakpoint)." },
  { "rcYawExpo", "uint8_t", "1", "", "Yaw RC Expo (currentControlRateProfile->stabilized.rcYawExpo8)." },
};

inline constexpr Field FIELDS_90[] = {
  { "activeModes", "boxBitmask_t", "sizeof(boxBitmask_t)", "", "Bitmask of all active modes (packBoxModeFlags()). Size depends on boxBitmask_t definition." },
};

inline constexpr Field FIELDS_91[] = {
  { "midRc", "uint16_t", "2", "PWM", "Mid RC value (PWM_RANGE_MIDDLE, typically 1500)." },
  { "legacyMinThrottle", "uint16_t", "2", "-", "Always 0 (Legacy)." },
  { "maxThrottle", "uint16_t", "2", "PWM", "Maximum throttle command (getMaxThrottle())." },
  { "minCommand", "uint16_t", "2", "PWM", "Minimum motor command when disarmed (motorConfig()->mincommand)." },
  { "failsafeThrottle", "uint16_t", "2", "PWM", "Failsafe throttle level (currentBatteryProfile->failsafe_throttle)." },
  { "gpsType", "uint8_t", "1", "Enum", "GPS provider type (gpsConfig()->provider). 0 if USE_GPS disabled." },
  { "legacyGpsBaud", "uint8_t", "1", "-", "Always 0 (Legacy)." },
  { "gpsSbasMode", "uint8_t", "1", "Enum", "GPS SBAS mode (gpsConfig()->sbasMode). 0 if USE_GPS disabled." },
  { "legacyMwCurrentOut", "uint8_t", "1", "-", "Always 0 (Legacy)." },
  { "rssiChannel", "uint8_t", "1", "Index", "RSSI channel index (1-based) (rxConfig()->rssi_channel)." },
  { "reserved1", "uint8_t", "1", "-", "Always 0." },
  { "magDeclination", "uint16_t", "2", "0.1 degrees", "Magnetic declination / 10 (compassConfig()->mag_declination / 10). 0 if USE_MAG disabled." },
  { "vbatScale", "uint8_t", "1", "Scale / 10", "Voltage scale / 10 (batteryMetersConfig()->voltage.scale / 10). 0 if USE_ADC disabled." },
  { "vbatMinCell", "uint8_t", "1", "0.1V", "Min cell voltage / 10 (currentBatteryProfile->voltage.cellMin / 10). 0 if USE_ADC disabled." },
  { "vbatMaxCell", "uint8_t", "1", "0.1V", "Max cell voltage / 10 (currentBatteryProfile->voltage.cellMax / 10). 0 if USE_ADC disabled." },
  { "vbatWarningCell", "uint8_t", "1", "0.1V", "Warning cell voltage / 10 (currentBatteryProfile->voltage.cellWarning / 10). 0 if USE_ADC disabled." },
};

inline constexpr Field FIELDS_92[] = {
  { "boxNamesString", "char[]", "Variable", "", "String containing mode names separated by ';'. Null termination not guaranteed by MSP, relies on payload size. (serializeBoxNamesReply())." },
};

inline constexpr Field FIELDS_93[] = {
  { "pidNamesString", "char[]", "Variable", "", "String \"ROLL;PITCH;YAW;ALT;Pos;PosR;NavR;LEVEL;MAG;VEL;\". Null termination not guaranteed by MSP." },
};

inline constexpr Field FIELDS_94[] = {
  { "waypointIndex", "uint8_t", "1", "", "Index of the waypoint to retrieve (0 to NAV_MAX_WAYPOINTS - 1)." },
  { "waypointIndex", "uint8_t", "1", "Index", "Index of the returned waypoint." },
  { "action", "uint8_t", "1", "Enum", "Waypoint action type (navWaypointActions_e)." },
  { "latitude", "int32_t", "4", "deg 1e7", "Latitude coordinate." },
  { "longitude", "int32_t", "4", "deg 1e7", "Longitude coordinate." },
  { "altitude", "int32_t", "4", "cm", "Altitude coordinate (relative to home or sea level, see flag)." },
  { "param1", "uint16_t", "2", "Varies", "Parameter 1 (meaning depends on action)." },
  { "param2", "uint16_t", "2", "Varies", "Parameter 2 (meaning depends on action)." },
  { "param3", "uint16_t", "2", "Varies", "Parameter 3 (meaning depends on action)." },
  { "flag", "uint8_t", "1", "Bitmask", "Waypoint flags (NAV_WP_FLAG_)." },
};

inline constexpr Field FIELDS_95[] = {
  { "boxIds", "uint8_t[]", "Variable", "", "Array of permanent IDs for each configured box (serializeBoxReply()). Length depends on number of boxes." },
};

inline constexpr Field FIELDS_96[] = {
  { "min", "uint16_t", "2", "PWM", "Minimum servo endpoint (servoParams(i)->min)." },
  { "max", "uint16_t", "2", "PWM", "Maximum servo endpoint (servoParams(i)->max)." },
  { "middle", "uint16_t", "2", "PWM", "Middle/Neutral servo position (servoParams(i)->middle)." },
  { "rate", "uint8_t", "1", "% (-100 to 100)", "Servo rate/scaling (servoParams(i)->rate)." },
  { "reserved1", "uint8_t", "1", "-", "Always 0." },
  { "reserved2", "uint8_t", "1", "-", "Always 0." },
  { "legacyForwardChan", "uint8_t", "1", "-", "Always 255 (Legacy)." },
  { "legacyReversedSources", "uint32_t", "4", "-", "Always 0 (Legacy)." },
};

inline constexpr Field FIELDS_97[] = {
  { "navMode", "uint8_t", "1", "", "Enum (NAV_MODE_): Current navigation mode (None, RTH, WP, Hold, etc.) (NAV_Status.mode)." },
  { "navState", "uint8_t", "1", "", "Enum (NAV_STATE_): Current navigation state (NAV_Status.state)." },
  { "activeWpAction", "uint8_t", "1", "", "Enum (navWaypointActions_e): Action of the currently executing waypoint (NAV_Status.activeWpAction)." },
  { "activeWpNumber", "uint8_t", "1", "", "Index: Index of the currently executing waypoint (NAV_Status.activeWpNumber)." },
  { "navError", "uint8_t", "1", "", "Enum (NAV_ERROR_): Current navigation error code (NAV_Status.error)." },
  { "targetHeading", "int16_t", "2", "", "degrees: Target heading for heading controller (getHeadingHoldTarget())." },
};

inline constexpr Field FIELDS_99[] = {
  { "deadbandLow", "uint16_t", "2", "PWM", "Lower deadband limit for 3D mode (reversibleMotorsConfig()->deadband_low)." },
  { "deadbandHigh", "uint16_t", "2", "PWM", "Upper deadband limit for 3D mode (reversibleMotorsConfig()->deadband_high)." },
  { "neutral", "uint16_t", "2", "PWM", "Neutral throttle point for 3D mode (reversibleMotorsConfig()->neutral)." },
};

inline constexpr Field FIELDS_100[] = {
  { "deadband", "uint8_t", "1", "PWM", "General RC deadband for Roll/Pitch (rcControlsConfig()->deadband)." },
  { "yawDeadband", "uint8_t", "1", "PWM", "Specific deadband for Yaw (rcControlsConfig()->yaw_deadband)." },
  { "altHoldDeadband", "uint8_t", "1", "PWM", "Deadband for altitude hold adjustments (rcControlsConfig()->alt_hold_deadband)." },
  { "throttleDeadband", "uint16_t", "2", "PWM", "Deadband around throttle mid-stick (rcControlsConfig()->mid_throttle_deadband)." },
};

inline constexpr Field FIELDS_101[] = {
  { "gyroAlign", "uint8_t", "1", "", "Always 0 (Legacy alignment enum)." },
  { "accAlign", "uint8_t", "1", "", "Always 0 (Legacy alignment enum)." },
  { "magAlign", "uint8_t", "1", "", "Magnetometer alignment (compassConfig()->mag_align). 0 if USE_MAG disabled." },
  { "opflowAlign", "uint8_t", "1", "", "Optical flow alignment (opticalFlowConfig()->opflow_align). 0 if USE_OPFLOW disabled." },
};

inline constexpr Field FIELDS_102[] = {
  { "modeIndex", "uint8_t", "1", "", "Index of the LED mode (ledModeIndex_e). LED_MODE_COUNT for special colors." },
  { "directionOrSpecialIndex", "uint8_t", "1", "", "Index of the direction (ledDirection_e) or special color (ledSpecialColor_e)." },
  { "colorIndex", "uint8_t", "1", "", "Index of the color assigned from ledStripConfig()->colors." },
};

inline constexpr Field FIELDS_103[] = {
  { "cellCount", "uint8_t", "1", "Count", "Number of battery cells (getBatteryCellCount())." },
  { "capacity", "uint16_t", "2", "mAh", "Battery capacity (currentBatteryProfile->capacity.value)." },
  { "vbatScaled", "uint8_t", "1", "0.1V", "Battery voltage / 10 (getBatteryVoltage() / 10)." },
  { "mAhDrawn", "uint16_t", "2", "mAh", "Consumed capacity (getMAhDrawn())." },
  { "amperage", "int16_t", "2", "0.01A", "Current draw (getAmperage())." },
  { "batteryState", "uint8_t", "1", "Enum", "Current battery state (getBatteryState(), see BATTERY_STATE_)." },
  { "vbatActual", "uint16_t", "2", "0.01V", "Actual battery voltage (getBatteryVoltage())." },
};

inline constexpr Field FIELDS_105[] = {
  { "powerLevelIndex", "uint8_t", "1", "", "1-based index of the power level to query." },
  { "powerLevelIndex", "uint8_t", "1", "", "1-based index of the returned power level." },
  { "powerValue", "uint16_t", "2", "", "Always 0 (Actual power value in mW is not stored/returned via MSP)." },
  { "labelLength", "uint8_t", "1", "", "Length of the power level label string that follows." },
  { "label", "char[]", "Variable", "", "Power level label string (e.g., \"25\", \"200\"). Length given by previous field." },
};

inline constexpr Field FIELDS_106[] = {
  { "cycleTime", "uint16_t", "2", "µs", "Main loop cycle time." },
  { "i2cErrors", "uint16_t", "2", "Count", "I2C errors." },
  { "sensorStatus", "uint16_t", "2", "Bitmask", "Sensor status bitmask." },
  { "activeModesLow", "uint32_t", "4", "Bitmask", "First 32 active modes." },
  { "profile", "uint8_t", "1", "Index", "Current config profile index." },
  { "cpuLoad", "uint16_t", "2", "%", "Average system load percentage (averageSystemLoadPercent)." },
  { "armingFlags", "uint16_t", "2", "Bitmask", "Flight controller arming flags (armingFlags). Note: Truncated to 16 bits." },
  { "accCalibAxisFlags", "uint8_t", "1", "Bitmask", "Accelerometer calibrated axes flags (accGetCalibrationAxisFlags())." },
};

inline constexpr Field FIELDS_107[] = {
  { "overallHealth", "uint8_t", "1", "Boolean", "1 if all essential hardware is healthy, 0 otherwise (isHardwareHealthy())." },
  { "gyroStatus", "uint8_t", "1", "Enum", "Gyro hardware status (getHwGyroStatus())." },
  { "accStatus", "uint8_t", "1", "Enum", "Accelerometer hardware status (getHwAccelerometerStatus())." },
  { "magStatus", "uint8_t", "1", "Enum", "Compass hardware status (getHwCompassStatus())." },
  { "baroStatus", "uint8_t", "1", "Enum", "Barometer hardware status (getHwBarometerStatus())." },
  { "gpsStatus", "uint8_t", "1", "Enum", "GPS hardware status (getHwGPSStatus())." },
  { "rangefinderStatus", "uint8_t", "1", "Enum", "Rangefinder hardware status (getHwRangefinderStatus())." },
  { "pitotStatus", "uint8_t", "1", "Enum", "Pitot hardware status (getHwPitotmeterStatus())." },
  { "opflowStatus", "uint8_t", "1", "Enum", "Optical Flow hardware status (getHwOpticalFlowStatus())." },
};

inline constexpr Field FIELDS_108[] = {
  { "uid0", "uint32_t", "4", "", "First 32 bits of the unique ID (U_ID_0)." },
  { "uid1", "uint32_t", "4", "", "Middle 32 bits of the unique ID (U_ID_1)." },
  { "uid2", "uint32_t", "4", "", "Last 32 bits of the unique ID (U_ID_2)." },
};

inline constexpr Field FIELDS_109[] = {
  { "protocolVersion", "uint8_t", "1", "", "Always 1 (Stub version)." },
  { "numChannels", "uint8_t", "1", "", "Always 0 (Number of SV info channels reported)." },
  { "hdopHundreds", "uint8_t", "1", "", "HDOP / 100 (gpsSol.hdop / 100)." },
  { "hdopUnits", "uint8_t", "1", "", "HDOP / 100 (gpsSol.hdop / 100)." },
};

inline constexpr Field FIELDS_110[] = {
  { "lastMessageDt", "uint16_t", "2", "ms", "Time since last valid GPS message (gpsStats.lastMessageDt)." },
  { "errors", "uint32_t", "4", "Count", "Number of GPS communication errors (gpsStats.errors)." },
  { "timeouts", "uint32_t", "4", "Count", "Number of GPS communication timeouts (gpsStats.timeouts)." },
  { "packetCount", "uint32_t", "4", "Count", "Number of valid GPS packets received (gpsStats.packetCount)." },
  { "hdop", "uint16_t", "2", "HDOP 100", "Horizontal Dilution of Precision (gpsSol.hdop)." },
  { "eph", "uint16_t", "2", "cm", "Estimated Horizontal Position Accuracy (gpsSol.eph)." },
  { "epv", "uint16_t", "2", "cm", "Estimated Vertical Position Accuracy (gpsSol.epv)." },
};

inline constexpr Field FIELDS_111[] = {
  { "rssi", "uint8_t", "1", "%", "RSSI value (0-100) provided by the external source." },
};

inline constexpr Field FIELDS_112[] = {
  { "rssiSource", "uint8_t", "1", "", "Enum: Source of the RSSI value (getRSSISource())." },
  { "rtcDateTimeIsSet", "uint8_t", "1", "", "Boolean: 1 if the RTC has been set, 0 otherwise." },
};

inline constexpr Field FIELDS_113[] = {
  { "rcChannels", "uint16_t[]", "Variable (2 channelCount)", "PWM", "Array of RC channel values (typically 1000-2000). Number of channels determined by payload size." },
};

inline constexpr Field FIELDS_114[] = {
  { "fixType", "uint8_t", "1", "Enum", "GPS fix type." },
  { "numSat", "uint8_t", "1", "Count", "Number of satellites." },
  { "latitude", "int32_t", "4", "deg 1e7", "Latitude." },
  { "longitude", "int32_t", "4", "deg 1e7", "Longitude." },
  { "altitude", "int16_t", "2", "meters", "Altitude (converted to cm internally)." },
  { "speed", "uint16_t", "2", "cm/s", "Ground speed." },
  { "groundCourse", "uint16_t", "2", "???", "Ground course (units unclear from code, likely degrees or deci-degrees, ignored in current code)." },
};

inline constexpr Field FIELDS_116[] = {
  { "legacyRcRate", "uint8_t", "1", "", "Ignored." },
  { "rcExpo", "uint8_t", "1", "", "Sets currentControlRateProfile->stabilized.rcExpo8." },
  { "rollRate", "uint8_t", "1", "", "Sets currentControlRateProfile->stabilized.rates[FD_ROLL] (constrained)." },
  { "pitchRate", "uint8_t", "1", "", "Sets currentControlRateProfile->stabilized.rates[FD_PITCH] (constrained)." },
  { "yawRate", "uint8_t", "1", "", "Sets currentControlRateProfile->stabilized.rates[FD_YAW] (constrained)." },
  { "dynamicThrottlePID", "uint8_t", "1", "", "Sets currentControlRateProfile->throttle.dynPID (constrained)." },
  { "throttleMid", "uint8_t", "1", "", "Sets currentControlRateProfile->throttle.rcMid8." },
  { "throttleExpo", "uint8_t", "1", "", "Sets currentControlRateProfile->throttle.rcExpo8." },
  { "tpaBreakpoint", "uint16_t", "2", "", "Sets currentControlRateProfile->throttle.pa_breakpoint." },
  { "rcYawExpo", "uint8_t", "1", "", "(Optional) Sets currentControlRateProfile->stabilized.rcYawExpo8." },
};

inline constexpr Field FIELDS_119[] = {
  { "midRc", "uint16_t", "2", "PWM", "Ignored." },
  { "legacyMinThrottle", "uint16_t", "2", "-", "Ignored." },
  { "legacyMaxThrottle", "uint16_t", "2", "-", "Ignored." },
  { "minCommand", "uint16_t", "2", "PWM", "Sets motorConfigMutable()->mincommand (constrained 0-PWM_RANGE_MAX)." },
  { "failsafeThrottle", "uint16_t", "2", "PWM", "Sets currentBatteryProfileMutable->failsafe_throttle (constrained PWM_RANGE_MIN/MAX)." },
  { "gpsType", "uint8_t", "1", "Enum", "Sets gpsConfigMutable()->provider (if USE_GPS)." },
  { "legacyGpsBaud", "uint8_t", "1", "-", "Ignored." },
  { "gpsSbasMode", "uint8_t", "1", "Enum", "Sets gpsConfigMutable()->sbasMode (if USE_GPS)." },
  { "legacyMwCurrentOut", "uint8_t", "1", "-", "Ignored." },
  { "rssiChannel", "uint8_t", "1", "Index", "Sets rxConfigMutable()->rssi_channel (constrained 0-MAX_SUPPORTED_RC_CHANNEL_COUNT). Updates source." },
  { "reserved1", "uint8_t", "1", "-", "Ignored." },
  { "magDeclination", "uint16_t", "2", "0.1 degrees", "Sets compassConfigMutable()->mag_declination = value 10 (if USE_MAG)." },
  { "vbatScale", "uint8_t", "1", "Scale / 10", "Sets batteryMetersConfigMutable()->voltage.scale = value 10 (if USE_ADC)." },
  { "vbatMinCell", "uint8_t", "1", "0.1V", "Sets currentBatteryProfileMutable->voltage.cellMin = value 10 (if USE_ADC)." },
  { "vbatMaxCell", "uint8_t", "1", "0.1V", "Sets currentBatteryProfileMutable->voltage.cellMax = value 10 (if USE_ADC)." },
  { "vbatWarningCell", "uint8_t", "1", "0.1V", "Sets currentBatteryProfileMutable->voltage.cellWarning = value 10 (if USE_ADC)." },
};

inline constexpr Field FIELDS_121[] = {
  { "waypointIndex", "uint8_t", "1", "Index", "Index of the waypoint to set (0 to NAV_MAX_WAYPOINTS - 1)." },
  { "action", "uint8_t", "1", "Enum", "Waypoint action type." },
  { "latitude", "int32_t", "4", "deg 1e7", "Latitude coordinate." },
  { "longitude", "int32_t", "4", "deg 1e7", "Longitude coordinate." },
  { "altitude", "int32_t", "4", "cm", "Altitude coordinate." },
  { "param1", "uint16_t", "2", "Varies", "Parameter 1." },
  { "param2", "uint16_t", "2", "Varies", "Parameter 2." },
  { "param3", "uint16_t", "2", "Varies", "Parameter 3." },
  { "flag", "uint8_t", "1", "Bitmask", "Waypoint flags." },
};

inline constexpr Field FIELDS_122[] = {
  { "profileIndex", "uint8_t", "1", "", "Index of the profile to activate (0-based)." },
};

inline constexpr Field FIELDS_123[] = {
  { "heading", "int16_t", "2", "degrees", "Target heading (0-359)." },
};

inline constexpr Field FIELDS_124[] = {
  { "servoIndex", "uint8_t", "1", "Index", "Index of the servo to configure (0 to MAX_SUPPORTED_SERVOS - 1)." },
  { "min", "uint16_t", "2", "PWM", "Minimum servo endpoint." },
  { "max", "uint16_t", "2", "PWM", "Maximum servo endpoint." },
  { "middle", "uint16_t", "2", "PWM", "Middle/Neutral servo position." },
  { "rate", "uint8_t", "1", "%", "Servo rate/scaling." },
  { "reserved1", "uint8_t", "1", "-", "Ignored." },
  { "reserved2", "uint8_t", "1", "-", "Ignored." },
  { "legacyForwardChan", "uint8_t", "1", "-", "Ignored." },
  { "legacyReversedSources", "uint32_t", "4", "-", "Ignored." },
};

inline constexpr Field FIELDS_125[] = {
  { "motorValues", "uint16_t[8]", "16", "PWM", "Array of motor values to set when disarmed. Only affects first MAX_SUPPORTED_MOTORS." },
};

inline constexpr Field FIELDS_127[] = {
  { "deadbandLow", "uint16_t", "2", "PWM", "Sets reversibleMotorsConfigMutable()->deadband_low." },
  { "deadbandHigh", "uint16_t", "2", "PWM", "Sets reversibleMotorsConfigMutable()->deadband_high." },
  { "neutral", "uint16_t", "2", "PWM", "Sets reversibleMotorsConfigMutable()->neutral." },
};

inline constexpr Field FIELDS_128[] = {
  { "deadband", "uint8_t", "1", "PWM", "Sets rcControlsConfigMutable()->deadband." },
  { "yawDeadband", "uint8_t", "1", "PWM", "Sets rcControlsConfigMutable()->yaw_deadband." },
  { "altHoldDeadband", "uint8_t", "1", "PWM", "Sets rcControlsConfigMutable()->alt_hold_deadband." },
  { "throttleDeadband", "uint16_t", "2", "PWM", "Sets rcControlsConfigMutable()->mid_throttle_deadband." },
};

inline constexpr Field FIELDS_130[] = {
  { "gyroAlign", "uint8_t", "1", "", "Ignored." },
  { "accAlign", "uint8_t", "1", "", "Ignored." },
  { "magAlign", "uint8_t", "1", "", "Sets compassConfigMutable()->mag_align (if USE_MAG)." },
  { "opflowAlign", "uint8_t", "1", "", "Sets opticalFlowConfigMutable()->opflow_align (if USE_OPFLOW)." },
};

inline constexpr Field FIELDS_131[] = {
  { "modeIndex", "uint8_t", "1", "", "Index of the LED mode (ledModeIndex_e or LED_MODE_COUNT for special)." },
  { "directionOrSpecialIndex", "uint8_t", "1", "", "Index of the direction or special color." },
  { "colorIndex", "uint8_t", "1", "", "Index of the color to assign from ledStripConfig()->colors." },
};

inline constexpr Field FIELDS_134[] = {
  { "targetChannel", "uint8_t", "1", "Index", "Servo output channel index (0-based)." },
  { "inputSource", "uint8_t", "1", "Enum", "Input source for the mix (RC chan, Roll, Pitch...). See mixerSource_t." },
  { "rate", "uint16_t", "2", "% 100?", "Mixing rate/weight. Needs scaling check." },
  { "speed", "uint8_t", "1", "0-100", "Speed/Slew rate limit." },
  { "reserved1", "uint8_t", "1", "-", "Always 0." },
  { "legacyMax", "uint8_t", "1", "-", "Always 100 (Legacy)." },
  { "legacyBox", "uint8_t", "1", "-", "Always 0 (Legacy)." },
};

inline constexpr Field FIELDS_135[] = {
  { "ruleIndex", "uint8_t", "1", "Index", "Index of the rule to set (0 to MAX_SERVO_RULES - 1)." },
  { "targetChannel", "uint8_t", "1", "Index", "Servo output channel index." },
  { "inputSource", "uint8_t", "1", "Enum", "Input source for the mix." },
  { "rate", "uint16_t", "2", "% 100?", "Mixing rate/weight." },
  { "speed", "uint8_t", "1", "0-100", "Speed/Slew rate limit." },
  { "legacyMinMax", "uint16_t", "2", "-", "Ignored." },
  { "legacyBox", "uint8_t", "1", "-", "Ignored." },
};

inline constexpr Field FIELDS_136[] = {
  { "passthroughMode", "uint8_t", "1", "", "Type of passthrough (mspPassthroughType_e: Serial ID, Serial Function, ESC 4way)." },
  { "passthroughArgument", "uint8_t", "1", "", "Argument for the mode (e.g., Serial Port Identifier, Serial Function ID). Defaults to 0 if not sent." },
  { "status", "uint8_t", "1", "", "1 if passthrough started successfully, 0 on error (e.g., port not found). For 4way, returns number of ESCs found." },
};

inline constexpr Field FIELDS_137[] = {
  { "seconds", "int32_t", "4", "Seconds", "Seconds since epoch (or relative time if not set). 0 if RTC time unknown." },
  { "millis", "uint16_t", "2", "Milliseconds", "Millisecond part of the time. 0 if RTC time unknown." },
};

inline constexpr Field FIELDS_138[] = {
  { "seconds", "int32_t", "4", "Seconds", "Seconds component of time to set." },
  { "millis", "uint16_t", "2", "Milliseconds", "Millisecond component of time to set." },
};

inline constexpr Field FIELDS_140[] = {
  { "Message Text", "char[]", "Variable", "", "NUL terminated [debug message](https://github.com/iNavFlight/inav/blob/master/docs/development/serial_printf_debugging.md) text." },
};

inline constexpr Field FIELDS_141[] = {
  { "debugValues", "uint16_t[4]", "8", "", "First 4 values from the debug array." },
};

inline constexpr Field FIELDS_143[] = {
  { "tzOffsetMinutes", "int16_t", "2", "Minutes", "Time zone offset from UTC (timeConfig()->tz_offset)." },
  { "tzAutoDst", "uint8_t", "1", "Boolean", "Automatic daylight saving time enabled (timeConfig()->tz_automatic_dst)." },
};

inline constexpr Field FIELDS_144[] = {
  { "tzOffsetMinutes", "int16_t", "2", "Minutes", "Sets timeConfigMutable()->tz_offset." },
  { "tzOffsetMinutes", "int16_t", "2", "Minutes", "Sets timeConfigMutable()->tz_offset." },
  { "tzAutoDst", "uint8_t", "1", "Boolean", "Sets timeConfigMutable()->tz_automatic_dst." },
};

inline constexpr Field FIELDS_145[] = {
  { "settingName", "char[]", "Variable", "", "Null-terminated string containing the setting name (e.g., \"gyro_main_lpf_hz\")." },
  { "zeroByte", "uint8_t", "1", "", "Must be 0." },
  { "settingIndex", "uint16_t", "2", "", "Absolute index of the setting." },
  { "settingValue", "uint8_t[]", "Variable", "", "Raw byte value of the setting. Size depends on the setting's type (settingGetValueSize())." },
};

inline constexpr Field FIELDS_146[] = {
  { "settingIdentifier", "Varies", "Variable", "", "Setting name (null-terminated string) OR Index (0x00 followed by uint16_t index)." },
  { "settingValue", "uint8_t[]", "Variable", "", "Raw byte value to set for the setting. Size must match the setting's type." },
};

inline constexpr Field FIELDS_147[] = {
  { "throttleWeight", "uint16_t", "2", "Scaled (0-4000)", "Throttle weight 1000, offset by 2000. (Range -2.0 to +2.0 -> 0 to 4000)." },
  { "rollWeight", "uint16_t", "2", "Scaled (0-4000)", "Roll weight 1000, offset by 2000." },
  { "pitchWeight", "uint16_t", "2", "Scaled (0-4000)", "Pitch weight 1000, offset by 2000." },
  { "yawWeight", "uint16_t", "2", "Scaled (0-4000)", "Yaw weight 1000, offset by 2000." },
  { "throttleWeight", "uint16_t", "2", "Scaled (0-4000)", "Profile 2 Throttle weight." },
  { "rollWeight", "uint16_t", "2", "Scaled (0-4000)", "Profile 2 Roll weight." },
  { "pitchWeight", "uint16_t", "2", "Scaled (0-4000)", "Profile 2 Pitch weight." },
  { "yawWeight", "uint16_t", "2", "Scaled (0-4000)", "Profile 2 Yaw weight." },
};

inline constexpr Field FIELDS_148[] = {
  { "motorIndex", "uint8_t", "1", "Index", "Index of the motor to configure (0 to MAX_SUPPORTED_MOTORS - 1)." },
  { "throttleWeight", "uint16_t", "2", "Scaled (0-4000)", "Sets throttle weight from (value / 1000.0) - 2.0." },
  { "rollWeight", "uint16_t", "2", "Scaled (0-4000)", "Sets roll weight from (value / 1000.0) - 2.0." },
  { "pitchWeight", "uint16_t", "2", "Scaled (0-4000)", "Sets pitch weight from (value / 1000.0) - 2.0." },
  { "yawWeight", "uint16_t", "2", "Scaled (0-4000)", "Sets yaw weight from (value / 1000.0) - 2.0." },
};

inline constexpr Field FIELDS_149[] = {
  { "settingName", "char[]", "Variable", "", "Null-terminated setting name." },
  { "pgn", "uint16_t", "2", "", "Parameter Group Number (PGN) ID." },
  { "type", "uint8_t", "1", "", "Variable type (VAR_UINT8, VAR_FLOAT, etc.)." },
  { "section", "uint8_t", "1", "", "Setting section (MASTER_VALUE, PROFILE_VALUE, etc.)." },
  { "mode", "uint8_t", "1", "", "Setting mode (MODE_NORMAL, MODE_LOOKUP, etc.)." },
  { "minValue", "int32_t", "4", "", "Minimum allowed value (as signed 32-bit)." },
  { "maxValue", "uint32_t", "4", "", "Maximum allowed value (as unsigned 32-bit)." },
  { "settingIndex", "uint16_t", "2", "", "Absolute index of the setting." },
  { "profileIndex", "uint8_t", "1", "", "Current profile index (if applicable, else 0)." },
  { "profileCount", "uint8_t", "1", "", "Total number of profiles (if applicable, else 0)." },
  { "lookupNames", "char[]", "Variable", "", "(If mode == MODE_LOOKUP) Series of null-terminated strings for each possible value from min to max." },
  { "settingValue", "uint8_t[]", "Variable", "", "Current raw byte value of the setting." },
};

inline constexpr Field FIELDS_150[] = {
  { "pgn", "uint16_t", "2", "", "PGN ID to query. If omitted, returns all used PGNs." },
  { "pgn", "uint16_t", "2", "", "Parameter Group Number (PGN) ID." },
  { "startIndex", "uint16_t", "2", "", "Absolute index of the first setting in this group." },
  { "endIndex", "uint16_t", "2", "", "Absolute index of the last setting in this group." },
};

inline constexpr Field FIELDS_151[] = {
  { "identifier", "uint8_t", "1", "", "Port identifier (serialPortIdentifier_e)." },
  { "functionMask", "uint32_t", "4", "", "Bitmask of enabled functions (FUNCTION_)." },
  { "mspBaudIndex", "uint8_t", "1", "", "Baud rate index for MSP function." },
  { "gpsBaudIndex", "uint8_t", "1", "", "Baud rate index for GPS function." },
  { "telemetryBaudIndex", "uint8_t", "1", "", "Baud rate index for Telemetry function." },
  { "peripheralBaudIndex", "uint8_t", "1", "", "Baud rate index for other peripheral functions." },
};

inline constexpr Field FIELDS_152[] = {
  { "identifier", "uint8_t", "1", "", "Port identifier (serialPortIdentifier_e)." },
  { "functionMask", "uint32_t", "4", "", "Bitmask of functions to enable." },
  { "mspBaudIndex", "uint8_t", "1", "", "Baud rate index for MSP." },
  { "gpsBaudIndex", "uint8_t", "1", "", "Baud rate index for GPS." },
  { "telemetryBaudIndex", "uint8_t", "1", "", "Baud rate index for Telemetry." },
  { "peripheralBaudIndex", "uint8_t", "1", "", "Baud rate index for peripherals." },
};

inline constexpr Field FIELDS_153[] = {
  { "poiIndex", "uint8_t", "1", "Index", "Index of the POI slot (0 to RADAR_MAX_POIS - 1)." },
  { "state", "uint8_t", "1", "Enum", "Status of the POI (0=undefined, 1=armed, 2=lost)." },
  { "latitude", "int32_t", "4", "deg 1e7", "Latitude of the POI." },
  { "longitude", "int32_t", "4", "deg 1e7", "Longitude of the POI." },
  { "altitude", "int32_t", "4", "cm", "Altitude of the POI." },
  { "heading", "int16_t", "2", "degrees", "Heading of the POI." },
  { "speed", "uint16_t", "2", "cm/s", "Speed of the POI." },
  { "linkQuality", "uint8_t", "1", "0-4", "Link quality indicator." },
};

inline constexpr Field FIELDS_155[] = {
  { "sublinkID", "uint8_t", "1", "-", "Sublink identifier (usually 0)." },
  { "validLink", "uint8_t", "1", "Boolean", "Indicates if the link is currently valid (not in failsafe)." },
  { "rssiPercent", "uint8_t", "1", "%", "Uplink RSSI percentage (0-100)." },
  { "uplinkRSSI_dBm", "uint8_t", "1", "-dBm", "Uplink RSSI in dBm (sent as positive, e.g., 70 means -70dBm)." },
  { "downlinkLQ", "uint8_t", "1", "%", "Downlink Link Quality (0-100)." },
  { "uplinkLQ", "uint8_t", "1", "%", "Uplink Link Quality (0-100)." },
  { "uplinkSNR", "int8_t", "1", "dB", "Uplink Signal-to-Noise Ratio." },
};

inline constexpr Field FIELDS_156[] = {
  { "sublinkID", "uint8_t", "1", "-", "Sublink identifier (usually 0)." },
  { "uplinkTxPower", "uint16_t", "2", "mW?", "Uplink transmitter power level." },
  { "downlinkTxPower", "uint16_t", "2", "mW?", "Downlink transmitter power level." },
  { "band", "char[4]", "4", "-", "Operating band string (e.g., \"2G4\", \"900\")." },
  { "mode", "char[6]", "6", "-", "Operating mode/rate string (e.g., \"100HZ\", \"F1000\")." },
};

inline constexpr Field FIELDS_157[] = {
  { "quality", "uint8_t", "1", "0-255", "Quality of the measurement." },
  { "distanceMm", "int32_t", "4", "mm", "Measured distance. Negative value indicates out of range." },
};

inline constexpr Field FIELDS_158[] = {
  { "quality", "uint8_t", "1", "", "Quality of the measurement (0-255)." },
  { "motionX", "int32_t", "4", "", "Raw integrated flow value X." },
  { "motionY", "int32_t", "4", "", "Raw integrated flow value Y." },
};

inline constexpr Field FIELDS_159[] = {
  { "instance", "uint8_t", "1", "-", "Sensor instance number (for multi-GPS)." },
  { "gpsWeek", "uint16_t", "2", "-", "GPS week number (0xFFFF if unavailable)." },
  { "msTOW", "uint32_t", "4", "ms", "Milliseconds Time of Week." },
  { "fixType", "uint8_t", "1", "Enum", "Type of GPS fix." },
  { "satellitesInView", "uint8_t", "1", "Count", "Number of satellites used in solution." },
  { "hPosAccuracy", "uint16_t", "2", "cm", "Horizontal position accuracy estimate." },
  { "vPosAccuracy", "uint16_t", "2", "cm", "Vertical position accuracy estimate." },
  { "hVelAccuracy", "uint16_t", "2", "cm/s", "Horizontal velocity accuracy estimate." },
  { "hdop", "uint16_t", "2", "HDOP 100", "Horizontal Dilution of Precision." },
  { "longitude", "int32_t", "4", "deg 1e7", "Longitude." },
  { "latitude", "int32_t", "4", "deg 1e7", "Latitude." },
  { "mslAltitude", "int32_t", "4", "cm", "Altitude above Mean Sea Level." },
  { "nedVelNorth", "int32_t", "4", "cm/s", "North velocity (NED frame)." },
  { "nedVelEast", "int32_t", "4", "cm/s", "East velocity (NED frame)." },
  { "nedVelDown", "int32_t", "4", "cm/s", "Down velocity (NED frame)." },
  { "groundCourse", "uint16_t", "2", "deg 100", "Ground course (0-36000)." },
  { "trueYaw", "uint16_t", "2", "deg 100", "True heading/yaw (0-36000, 65535 if unavailable)." },
  { "year", "uint16_t", "2", "-", "Year (e.g., 2023)." },
  { "month", "uint8_t", "1", "-", "Month (1-12)." },
  { "day", "uint8_t", "1", "-", "Day of month (1-31)." },
  { "hour", "uint8_t", "1", "-", "Hour (0-23)." },
  { "min", "uint8_t", "1", "-", "Minute (0-59)." },
  { "sec", "uint8_t", "1", "-", "Second (0-59)." },
};

inline constexpr Field FIELDS_160[] = {
  { "instance", "uint8_t", "1", "-", "Sensor instance number." },
  { "timeMs", "uint32_t", "4", "ms", "Timestamp from the sensor." },
  { "magX", "int16_t", "2", "mGauss", "Front component reading." },
  { "magY", "int16_t", "2", "mGauss", "Right component reading." },
  { "magZ", "int16_t", "2", "mGauss", "Down component reading." },
};

inline constexpr Field FIELDS_161[] = {
  { "instance", "uint8_t", "1", "-", "Sensor instance number." },
  { "timeMs", "uint32_t", "4", "ms", "Timestamp from the sensor." },
  { "pressurePa", "float", "4", "Pa", "Absolute pressure." },
  { "temp", "int16_t", "2", "0.01 deg C", "Temperature." },
};

inline constexpr Field FIELDS_162[] = {
  { "instance", "uint8_t", "1", "-", "Sensor instance number." },
  { "timeMs", "uint32_t", "4", "ms", "Timestamp from the sensor." },
  { "diffPressurePa", "float", "4", "Pa", "Differential pressure." },
  { "temp", "int16_t", "2", "0.01 deg C", "Temperature." },
};

inline constexpr Field FIELDS_164[] = {
  { "cycleTime", "uint16_t", "2", "µs", "Main loop cycle time." },
  { "i2cErrors", "uint16_t", "2", "Count", "I2C errors." },
  { "sensorStatus", "uint16_t", "2", "Bitmask", "Sensor status bitmask." },
  { "cpuLoad", "uint16_t", "2", "%", "Average system load percentage." },
  { "profileAndBattProfile", "uint8_t", "1", "Packed", "Bits 0-3: Config profile index (getConfigProfile()), Bits 4-7: Battery profile index (getConfigBatteryProfile())." },
  { "armingFlags", "uint32_t", "4", "Bitmask", "Full 32-bit flight controller arming flags (armingFlags)." },
  { "activeModes", "boxBitmask_t", "sizeof(boxBitmask_t)", "Bitmask", "Full bitmask of active flight modes (packBoxModeFlags())." },
  { "mixerProfile", "uint8_t", "1", "Index", "Current mixer profile index (getConfigMixerProfile())." },
};

inline constexpr Field FIELDS_165[] = {
  { "quality", "uint8_t", "1", "0-255", "Raw quality indicator from the sensor (opflow.rawQuality). 0 if USE_OPFLOW disabled." },
  { "flowRateX", "int16_t", "2", "degrees/s", "Optical flow rate X (roll axis) (RADIANS_TO_DEGREES(opflow.flowRate[X])). 0 if USE_OPFLOW disabled." },
  { "flowRateY", "int16_t", "2", "degrees/s", "Optical flow rate Y (pitch axis) (RADIANS_TO_DEGREES(opflow.flowRate[Y])). 0 if USE_OPFLOW disabled." },
  { "bodyRateX", "int16_t", "2", "degrees/s", "Compensated body rate X (roll axis) (RADIANS_TO_DEGREES(opflow.bodyRate[X])). 0 if USE_OPFLOW disabled." },
  { "bodyRateY", "int16_t", "2", "degrees/s", "Compensated body rate Y (pitch axis) (RADIANS_TO_DEGREES(opflow.bodyRate[Y])). 0 if USE_OPFLOW disabled." },
};

inline constexpr Field FIELDS_166[] = {
  { "batteryFlags", "uint8_t", "1", "Bitmask", "Battery status flags: Bit 0=Full on plug-in, Bit 1=Use capacity threshold, Bit 2-3=Battery State enum (getBatteryState()), Bit 4-7=Cell Count (getBatteryCellCount())." },
  { "vbat", "uint16_t", "2", "0.01V", "Battery voltage (getBatteryVoltage())." },
  { "amperage", "uint16_t", "2", "0.01A", "Current draw (getAmperage())." },
  { "powerDraw", "uint32_t", "4", "mW", "Power draw (getPower())." },
  { "mAhDrawn", "uint32_t", "4", "mAh", "Consumed capacity (getMAhDrawn())." },
  { "mWhDrawn", "uint32_t", "4", "mWh", "Consumed energy (getMWhDrawn())." },
  { "remainingCapacity", "uint32_t", "4", "mAh/mWh", "Estimated remaining capacity (getBatteryRemainingCapacity())." },
  { "percentageRemaining", "uint8_t", "1", "%", "Estimated remaining capacity percentage (calculateBatteryPercentage())." },
  { "rssi", "uint16_t", "2", "0-1023 or %", "RSSI value (getRSSI())." },
};

inline constexpr Field FIELDS_167[] = {
  { "midRc", "uint16_t", "2", "PWM", "Mid RC value (PWM_RANGE_MIDDLE)." },
  { "legacyMinThrottle", "uint16_t", "2", "-", "Always 0 (Legacy)." },
  { "maxThrottle", "uint16_t", "2", "PWM", "Maximum throttle command (getMaxThrottle())." },
  { "minCommand", "uint16_t", "2", "PWM", "Minimum motor command (motorConfig()->mincommand)." },
  { "failsafeThrottle", "uint16_t", "2", "PWM", "Failsafe throttle level (currentBatteryProfile->failsafe_throttle)." },
  { "gpsType", "uint8_t", "1", "Enum", "GPS provider type (gpsConfig()->provider). 0 if USE_GPS disabled." },
  { "legacyGpsBaud", "uint8_t", "1", "-", "Always 0 (Legacy)." },
  { "gpsSbasMode", "uint8_t", "1", "Enum", "GPS SBAS mode (gpsConfig()->sbasMode). 0 if USE_GPS disabled." },
  { "rssiChannel", "uint8_t", "1", "Index", "RSSI channel index (1-based) (rxConfig()->rssi_channel)." },
  { "magDeclination", "uint16_t", "2", "0.1 degrees", "Magnetic declination / 10 (compassConfig()->mag_declination / 10). 0 if USE_MAG disabled." },
  { "vbatScale", "uint16_t", "2", "Scale", "Voltage scale (batteryMetersConfig()->voltage.scale). 0 if USE_ADC disabled." },
  { "vbatSource", "uint8_t", "1", "Enum", "Voltage source (batteryMetersConfig()->voltageSource). 0 if USE_ADC disabled." },
  { "cellCount", "uint8_t", "1", "Count", "Configured cell count (currentBatteryProfile->cells). 0 if USE_ADC disabled." },
  { "vbatCellDetect", "uint16_t", "2", "0.01V", "Cell detection voltage (currentBatteryProfile->voltage.cellDetect). 0 if USE_ADC disabled." },
  { "vbatMinCell", "uint16_t", "2", "0.01V", "Min cell voltage (currentBatteryProfile->voltage.cellMin). 0 if USE_ADC disabled." },
  { "vbatMaxCell", "uint16_t", "2", "0.01V", "Max cell voltage (currentBatteryProfile->voltage.cellMax). 0 if USE_ADC disabled." },
  { "vbatWarningCell", "uint16_t", "2", "0.01V", "Warning cell voltage (currentBatteryProfile->voltage.cellWarning). 0 if USE_ADC disabled." },
  { "capacityValue", "uint32_t", "4", "mAh/mWh", "Battery capacity (currentBatteryProfile->capacity.value)." },
  { "capacityWarning", "uint32_t", "4", "mAh/mWh", "Capacity warning threshold (currentBatteryProfile->capacity.warning)." },
  { "capacityCritical", "uint32_t", "4", "mAh/mWh", "Capacity critical threshold (currentBatteryProfile->capacity.critical)." },
  { "capacityUnit", "uint8_t", "1", "Enum", "Capacity unit (batteryMetersConfig()->capacity_unit)." },
};

inline constexpr Field FIELDS_168[] = {
  { "midRc", "uint16_t", "2", "PWM", "Ignored." },
  { "legacyMinThrottle", "uint16_t", "2", "-", "Ignored." },
  { "legacyMaxThrottle", "uint16_t", "2", "-", "Ignored." },
  { "minCommand", "uint16_t", "2", "PWM", "Sets motorConfigMutable()->mincommand (constrained)." },
  { "failsafeThrottle", "uint16_t", "2", "PWM", "Sets currentBatteryProfileMutable->failsafe_throttle (constrained)." },
  { "gpsType", "uint8_t", "1", "Enum", "Sets gpsConfigMutable()->provider (if USE_GPS)." },
  { "legacyGpsBaud", "uint8_t", "1", "-", "Ignored." },
  { "gpsSbasMode", "uint8_t", "1", "Enum", "Sets gpsConfigMutable()->sbasMode (if USE_GPS)." },
  { "rssiChannel", "uint8_t", "1", "Index", "Sets rxConfigMutable()->rssi_channel (constrained). Updates source." },
  { "magDeclination", "uint16_t", "2", "0.1 degrees", "Sets compassConfigMutable()->mag_declination = value 10 (if USE_MAG)." },
  { "vbatScale", "uint16_t", "2", "Scale", "Sets batteryMetersConfigMutable()->voltage.scale (if USE_ADC)." },
  { "vbatSource", "uint8_t", "1", "Enum", "Sets batteryMetersConfigMutable()->voltageSource (if USE_ADC, validated)." },
  { "cellCount", "uint8_t", "1", "Count", "Sets currentBatteryProfileMutable->cells (if USE_ADC)." },
  { "vbatCellDetect", "uint16_t", "2", "0.01V", "Sets currentBatteryProfileMutable->voltage.cellDetect (if USE_ADC)." },
  { "vbatMinCell", "uint16_t", "2", "0.01V", "Sets currentBatteryProfileMutable->voltage.cellMin (if USE_ADC)." },
  { "vbatMaxCell", "uint16_t", "2", "0.01V", "Sets currentBatteryProfileMutable->voltage.cellMax (if USE_ADC)." },
  { "vbatWarningCell", "uint16_t", "2", "0.01V", "Sets currentBatteryProfileMutable->voltage.cellWarning (if USE_ADC)." },
  { "capacityValue", "uint32_t", "4", "mAh/mWh", "Sets currentBatteryProfileMutable->capacity.value." },
  { "capacityWarning", "uint32_t", "4", "mAh/mWh", "Sets currentBatteryProfileMutable->capacity.warning." },
  { "capacityCritical", "uint32_t", "4", "mAh/mWh", "Sets currentBatteryProfileMutable->capacity.critical." },
  { "capacityUnit", "uint8_t", "1", "Enum", "Sets batteryMetersConfigMutable()->capacity_unit (validated). Updates OSD energy unit if changed." },
};

inline constexpr Field FIELDS_169[] = {
  { "vbatScale", "uint16_t", "2", "Scale", "Voltage scale (batteryMetersConfig()->voltage.scale)." },
  { "vbatSource", "uint8_t", "1", "Enum", "Voltage source (batteryMetersConfig()->voltageSource)." },
  { "cellCount", "uint8_t", "1", "Count", "Configured cell count (currentBatteryProfile->cells)." },
  { "vbatCellDetect", "uint16_t", "2", "0.01V", "Cell detection voltage (currentBatteryProfile->voltage.cellDetect)." },
  { "vbatMinCell", "uint16_t", "2", "0.01V", "Min cell voltage (currentBatteryProfile->voltage.cellMin)." },
  { "vbatMaxCell", "uint16_t", "2", "0.01V", "Max cell voltage (currentBatteryProfile->voltage.cellMax)." },
  { "vbatWarningCell", "uint16_t", "2", "0.01V", "Warning cell voltage (currentBatteryProfile->voltage.cellWarning)." },
  { "currentOffset", "uint16_t", "2", "mV", "Current sensor offset (batteryMetersConfig()->current.offset)." },
  { "currentScale", "uint16_t", "2", "Scale", "Current sensor scale (batteryMetersConfig()->current.scale)." },
  { "capacityValue", "uint32_t", "4", "mAh/mWh", "Battery capacity (currentBatteryProfile->capacity.value)." },
  { "capacityWarning", "uint32_t", "4", "mAh/mWh", "Capacity warning threshold (currentBatteryProfile->capacity.warning)." },
  { "capacityCritical", "uint32_t", "4", "mAh/mWh", "Capacity critical threshold (currentBatteryProfile->capacity.critical)." },
  { "capacityUnit", "uint8_t", "1", "Enum", "Capacity unit (batteryMetersConfig()->capacity_unit)." },
};

inline constexpr Field FIELDS_170[] = {
  { "vbatScale", "uint16_t", "2", "Scale", "Sets batteryMetersConfigMutable()->voltage.scale (if USE_ADC)." },
  { "vbatSource", "uint8_t", "1", "Enum", "Sets batteryMetersConfigMutable()->voltageSource (if USE_ADC, validated)." },
  { "cellCount", "uint8_t", "1", "Count", "Sets currentBatteryProfileMutable->cells (if USE_ADC)." },
  { "vbatCellDetect", "uint16_t", "2", "0.01V", "Sets currentBatteryProfileMutable->voltage.cellDetect (if USE_ADC)." },
  { "vbatMinCell", "uint16_t", "2", "0.01V", "Sets currentBatteryProfileMutable->voltage.cellMin (if USE_ADC)." },
  { "vbatMaxCell", "uint16_t", "2", "0.01V", "Sets currentBatteryProfileMutable->voltage.cellMax (if USE_ADC)." },
  { "vbatWarningCell", "uint16_t", "2", "0.01V", "Sets currentBatteryProfileMutable->voltage.cellWarning (if USE_ADC)." },
  { "currentOffset", "uint16_t", "2", "mV", "Sets batteryMetersConfigMutable()->current.offset." },
  { "currentScale", "uint16_t", "2", "Scale", "Sets batteryMetersConfigMutable()->current.scale." },
  { "capacityValue", "uint32_t", "4", "mAh/mWh", "Sets currentBatteryProfileMutable->capacity.value." },
  { "capacityWarning", "uint32_t", "4", "mAh/mWh", "Sets currentBatteryProfileMutable->capacity.warning." },
  { "capacityCritical", "uint32_t", "4", "mAh/mWh", "Sets currentBatteryProfileMutable->capacity.critical." },
  { "capacityUnit", "uint8_t", "1", "Enum", "Sets batteryMetersConfigMutable()->capacity_unit (validated). Updates OSD energy unit if changed." },
};

inline constexpr Field FIELDS_171[] = {
  { "throttleMid", "uint8_t", "1", "", "Throttle Midpoint (currentControlRateProfile->throttle.rcMid8)." },
  { "throttleExpo", "uint8_t", "1", "", "Throttle Expo (currentControlRateProfile->throttle.rcExpo8)." },
  { "dynamicThrottlePID", "uint8_t", "1", "", "TPA value (currentControlRateProfile->throttle.dynPID)." },
  { "tpaBreakpoint", "uint16_t", "2", "", "TPA breakpoint (currentControlRateProfile->throttle.pa_breakpoint)." },
  { "stabRcExpo", "uint8_t", "1", "", "Stabilized Roll/Pitch Expo (currentControlRateProfile->stabilized.rcExpo8)." },
  { "stabRcYawExpo", "uint8_t", "1", "", "Stabilized Yaw Expo (currentControlRateProfile->stabilized.rcYawExpo8)." },
  { "stabRollRate", "uint8_t", "1", "", "Stabilized Roll Rate (currentControlRateProfile->stabilized.rates[FD_ROLL])." },
  { "stabPitchRate", "uint8_t", "1", "", "Stabilized Pitch Rate (currentControlRateProfile->stabilized.rates[FD_PITCH])." },
  { "stabYawRate", "uint8_t", "1", "", "Stabilized Yaw Rate (currentControlRateProfile->stabilized.rates[FD_YAW])." },
  { "manualRcExpo", "uint8_t", "1", "", "Manual Roll/Pitch Expo (currentControlRateProfile->manual.rcExpo8)." },
  { "manualRcYawExpo", "uint8_t", "1", "", "Manual Yaw Expo (currentControlRateProfile->manual.rcYawExpo8)." },
  { "manualRollRate", "uint8_t", "1", "", "Manual Roll Rate (currentControlRateProfile->manual.rates[FD_ROLL])." },
  { "manualPitchRate", "uint8_t", "1", "", "Manual Pitch Rate (currentControlRateProfile->manual.rates[FD_PITCH])." },
  { "manualYawRate", "uint8_t", "1", "", "Manual Yaw Rate (currentControlRateProfile->manual.rates[FD_YAW])." },
};

inline constexpr Field FIELDS_172[] = {
  { "throttleMid", "uint8_t", "1", "", "Sets currentControlRateProfile_p->throttle.rcMid8." },
  { "throttleExpo", "uint8_t", "1", "", "Sets currentControlRateProfile_p->throttle.rcExpo8." },
  { "dynamicThrottlePID", "uint8_t", "1", "", "Sets currentControlRateProfile_p->throttle.dynPID." },
  { "tpaBreakpoint", "uint16_t", "2", "", "Sets currentControlRateProfile_p->throttle.pa_breakpoint." },
  { "stabRcExpo", "uint8_t", "1", "", "Sets currentControlRateProfile_p->stabilized.rcExpo8." },
  { "stabRcYawExpo", "uint8_t", "1", "", "Sets currentControlRateProfile_p->stabilized.rcYawExpo8." },
  { "stabRollRate", "uint8_t", "1", "", "Sets currentControlRateProfile_p->stabilized.rates[FD_ROLL] (constrained)." },
  { "stabPitchRate", "uint8_t", "1", "", "Sets currentControlRateProfile_p->stabilized.rates[FD_PITCH] (constrained)." },
  { "stabYawRate", "uint8_t", "1", "", "Sets currentControlRateProfile_p->stabilized.rates[FD_YAW] (constrained)." },
  { "manualRcExpo", "uint8_t", "1", "", "Sets currentControlRateProfile_p->manual.rcExpo8." },
  { "manualRcYawExpo", "uint8_t", "1", "", "Sets currentControlRateProfile_p->manual.rcYawExpo8." },
  { "manualRollRate", "uint8_t", "1", "", "Sets currentControlRateProfile_p->manual.rates[FD_ROLL] (constrained)." },
  { "manualPitchRate", "uint8_t", "1", "", "Sets currentControlRateProfile_p->manual.rates[FD_PITCH] (constrained)." },
  { "manualYawRate", "uint8_t", "1", "", "Sets currentControlRateProfile_p->manual.rates[FD_YAW] (constrained)." },
};

inline constexpr Field FIELDS_173[] = {
  { "airspeed", "uint32_t", "4", "cm/s", "Estimated/measured airspeed (getAirspeedEstimate()). 0 if USE_PITOT disabled or no valid data." },
};

inline constexpr Field FIELDS_174[] = {
  { "usageFlags", "uint8_t", "1", "", "Timer usage flags (truncated). TIM_USE_MOTOR or TIM_USE_SERVO." },
};

inline constexpr Field FIELDS_175[] = {
  { "brakingSpeedThreshold", "uint16_t", "2", "cm/s", "Speed above which braking engages (navConfig()->mc.braking_speed_threshold)." },
  { "brakingDisengageSpeed", "uint16_t", "2", "cm/s", "Speed below which braking disengages (navConfig()->mc.braking_disengage_speed)." },
  { "brakingTimeout", "uint16_t", "2", "ms", "Timeout before braking force reduces (navConfig()->mc.braking_timeout)." },
  { "brakingBoostFactor", "uint8_t", "1", "%", "Boost factor applied during braking (navConfig()->mc.braking_boost_factor)." },
  { "brakingBoostTimeout", "uint16_t", "2", "ms", "Timeout for the boost factor (navConfig()->mc.braking_boost_timeout)." },
  { "brakingBoostSpeedThreshold", "uint16_t", "2", "cm/s", "Speed threshold for boost engagement (navConfig()->mc.braking_boost_speed_threshold)." },
  { "brakingBoostDisengageSpeed", "uint16_t", "2", "cm/s", "Speed threshold for boost disengagement (navConfig()->mc.braking_boost_disengage_speed)." },
  { "brakingBankAngle", "uint8_t", "1", "degrees", "Maximum bank angle allowed during braking (navConfig()->mc.braking_bank_angle)." },
};

inline constexpr Field FIELDS_176[] = {
  { "brakingSpeedThreshold", "uint16_t", "2", "cm/s", "Sets navConfigMutable()->mc.braking_speed_threshold." },
  { "brakingDisengageSpeed", "uint16_t", "2", "cm/s", "Sets navConfigMutable()->mc.braking_disengage_speed." },
  { "brakingTimeout", "uint16_t", "2", "ms", "Sets navConfigMutable()->mc.braking_timeout." },
  { "brakingBoostFactor", "uint8_t", "1", "%", "Sets navConfigMutable()->mc.braking_boost_factor." },
  { "brakingBoostTimeout", "uint16_t", "2", "ms", "Sets navConfigMutable()->mc.braking_boost_timeout." },
  { "brakingBoostSpeedThreshold", "uint16_t", "2", "cm/s", "Sets navConfigMutable()->mc.braking_boost_speed_threshold." },
  { "brakingBoostDisengageSpeed", "uint16_t", "2", "cm/s", "Sets navConfigMutable()->mc.braking_boost_disengage_speed." },
  { "brakingBankAngle", "uint8_t", "1", "degrees", "Sets navConfigMutable()->mc.braking_bank_angle." },
};

inline constexpr Field FIELDS_177[] = {
  { "timerId", "uint8_t", "1", "", "Hardware timer identifier (e.g., TIM1, TIM2). Value depends on target." },
  { "usageFlags", "uint8_t", "1", "", "Timer usage flags (truncated). TIM_USE_MOTOR or TIM_USE_SERVO." },
};

inline constexpr Field FIELDS_178[] = {
  { "timerIndex", "uint8_t", "1", "", "Index of the hardware timer definition (0 to HARDWARE_TIMER_DEFINITION_COUNT - 1)." },
  { "timerIndex", "uint8_t", "1", "", "Timer index." },
  { "outputMode", "uint8_t", "1", "", "Output mode override (TIMER_OUTPUT_MODE_ enum)." },
  { "timerIndex", "uint8_t", "1", "", "Timer index requested." },
  { "outputMode", "uint8_t", "1", "", "Output mode override for the requested timer." },
};

inline constexpr Field FIELDS_179[] = {
  { "timerIndex", "uint8_t", "1", "", "Index of the hardware timer definition." },
  { "outputMode", "uint8_t", "1", "", "Output mode override (TIMER_OUTPUT_MODE_ enum) to set." },
};

inline constexpr Field FIELDS_180[] = {
  { "motorDirectionInverted", "uint8_t", "1", "", "Boolean: 1 if motor direction is reversed globally (mixerConfig()->motorDirectionInverted)." },
  { "reserved1", "uint8_t", "1", "", "Always 0 (Was yaw jump prevention limit)." },
  { "motorStopOnLow", "uint8_t", "1", "", "Boolean: 1 if motors stop at minimum throttle (mixerConfig()->motorstopOnLow)." },
  { "platformType", "uint8_t", "1", "", "Enum (platformType_e): Vehicle platform type (Multirotor, Airplane, etc.) (mixerConfig()->platformType)." },
  { "hasFlaps", "uint8_t", "1", "", "Boolean: 1 if the current mixer configuration includes flaps (mixerConfig()->hasFlaps)." },
  { "appliedMixerPreset", "uint16_t", "2", "", "Enum (mixerPreset_e): Mixer preset currently applied (mixerConfig()->appliedMixerPreset)." },
  { "maxMotors", "uint8_t", "1", "", "Constant: Maximum motors supported (MAX_SUPPORTED_MOTORS)." },
  { "maxServos", "uint8_t", "1", "", "Constant: Maximum servos supported (MAX_SUPPORTED_SERVOS)." },
};

inline constexpr Field FIELDS_181[] = {
  { "motorDirectionInverted", "uint8_t", "1", "", "Sets mixerConfigMutable()->motorDirectionInverted." },
  { "reserved1", "uint8_t", "1", "", "Ignored." },
  { "motorStopOnLow", "uint8_t", "1", "", "Sets mixerConfigMutable()->motorstopOnLow." },
  { "platformType", "uint8_t", "1", "", "Sets mixerConfigMutable()->platformType." },
  { "hasFlaps", "uint8_t", "1", "", "Sets mixerConfigMutable()->hasFlaps." },
  { "appliedMixerPreset", "uint16_t", "2", "", "Sets mixerConfigMutable()->appliedMixerPreset." },
  { "maxMotors", "uint8_t", "1", "", "Ignored." },
  { "maxServos", "uint8_t", "1", "", "Ignored." },
};

inline constexpr Field FIELDS_182[] = {
  { "layoutIndex", "uint8_t", "1", "", "Index of the OSD layout (0 to OSD_LAYOUT_COUNT - 1)." },
  { "layoutIndex", "uint8_t", "1", "", "Index of the OSD layout." },
  { "itemIndex", "uint16_t", "2", "", "Index of the OSD item (OSD_ITEM_ enum, 0 to OSD_ITEM_COUNT - 1)." },
  { "layoutCount", "uint8_t", "1", "", "Number of OSD layouts (OSD_LAYOUT_COUNT)." },
  { "itemCount", "uint8_t", "1", "", "Number of OSD items per layout (OSD_ITEM_COUNT)." },
  { "itemPositions", "uint16_t[OSD_ITEM_COUNT]", "OSD_ITEM_COUNT 2", "", "Packed X/Y positions for all items in the requested layout." },
  { "itemPosition", "uint16_t", "2", "", "Packed X/Y position for the requested item in the requested layout." },
};

inline constexpr Field FIELDS_183[] = {
  { "layoutIndex", "uint8_t", "1", "Index", "Index of the OSD layout (0 to OSD_LAYOUT_COUNT - 1)." },
  { "itemIndex", "uint8_t", "1", "Index", "Index of the OSD item (OSD_ITEM_ enum)." },
};

inline constexpr Field FIELDS_184[] = {
  { "rssiAlarm", "uint8_t", "1", "%", "RSSI alarm threshold (osdConfig()->rssi_alarm)." },
  { "timerAlarm", "uint16_t", "2", "seconds", "Timer alarm threshold (osdConfig()->time_alarm)." },
  { "altAlarm", "uint16_t", "2", "meters", "Altitude alarm threshold (osdConfig()->alt_alarm)." },
  { "distAlarm", "uint16_t", "2", "meters", "Distance alarm threshold (osdConfig()->dist_alarm)." },
  { "negAltAlarm", "uint16_t", "2", "meters", "Negative altitude alarm threshold (osdConfig()->neg_alt_alarm)." },
  { "gForceAlarm", "uint16_t", "2", "G 1000", "G-force alarm threshold (osdConfig()->gforce_alarm 1000)." },
  { "gForceAxisMinAlarm", "int16_t", "2", "G 1000", "Min G-force per-axis alarm (osdConfig()->gforce_axis_alarm_min 1000)." },
  { "gForceAxisMaxAlarm", "int16_t", "2", "G 1000", "Max G-force per-axis alarm (osdConfig()->gforce_axis_alarm_max 1000)." },
  { "currentAlarm", "uint8_t", "1", "0.1 A ?", "Current draw alarm threshold (osdConfig()->current_alarm). Units may need verification." },
  { "imuTempMinAlarm", "uint16_t", "2", "degrees C", "Min IMU temperature alarm (osdConfig()->imu_temp_alarm_min)." },
  { "imuTempMaxAlarm", "uint16_t", "2", "degrees C", "Max IMU temperature alarm (osdConfig()->imu_temp_alarm_max)." },
  { "baroTempMinAlarm", "uint16_t", "2", "degrees C", "Min Baro temperature alarm (osdConfig()->baro_temp_alarm_min). 0 if USE_BARO disabled." },
  { "baroTempMaxAlarm", "uint16_t", "2", "degrees C", "Max Baro temperature alarm (osdConfig()->baro_temp_alarm_max). 0 if USE_BARO disabled." },
  { "adsbWarnDistance", "uint16_t", "2", "meters", "ADSB warning distance (osdConfig()->adsb_distance_warning). 0 if USE_ADSB disabled." },
  { "adsbAlertDistance", "uint16_t", "2", "meters", "ADSB alert distance (osdConfig()->adsb_distance_alert). 0 if USE_ADSB disabled." },
};

inline constexpr Field FIELDS_185[] = {
  { "rssiAlarm", "uint8_t", "1", "%", "Sets osdConfigMutable()->rssi_alarm." },
  { "timerAlarm", "uint16_t", "2", "seconds", "Sets osdConfigMutable()->time_alarm." },
  { "altAlarm", "uint16_t", "2", "meters", "Sets osdConfigMutable()->alt_alarm." },
  { "distAlarm", "uint16_t", "2", "meters", "Sets osdConfigMutable()->dist_alarm." },
  { "negAltAlarm", "uint16_t", "2", "meters", "Sets osdConfigMutable()->neg_alt_alarm." },
  { "gForceAlarm", "uint16_t", "2", "G 1000", "Sets osdConfigMutable()->gforce_alarm = value / 1000.0f." },
  { "gForceAxisMinAlarm", "int16_t", "2", "G 1000", "Sets osdConfigMutable()->gforce_axis_alarm_min = value / 1000.0f." },
  { "gForceAxisMaxAlarm", "int16_t", "2", "G 1000", "Sets osdConfigMutable()->gforce_axis_alarm_max = value / 1000.0f." },
  { "currentAlarm", "uint8_t", "1", "0.1 A ?", "Sets osdConfigMutable()->current_alarm." },
  { "imuTempMinAlarm", "uint16_t", "2", "degrees C", "Sets osdConfigMutable()->imu_temp_alarm_min." },
  { "imuTempMaxAlarm", "uint16_t", "2", "degrees C", "Sets osdConfigMutable()->imu_temp_alarm_max." },
  { "baroTempMinAlarm", "uint16_t", "2", "degrees C", "Sets osdConfigMutable()->baro_temp_alarm_min (if USE_BARO)." },
  { "baroTempMaxAlarm", "uint16_t", "2", "degrees C", "Sets osdConfigMutable()->baro_temp_alarm_max (if USE_BARO)." },
};

inline constexpr Field FIELDS_186[] = {
  { "videoSystem", "uint8_t", "1", "", "Enum: Video system (Auto/PAL/NTSC) (osdConfig()->video_system)." },
  { "mainVoltageDecimals", "uint8_t", "1", "", "Count: Decimal places for main voltage display (osdConfig()->main_voltage_decimals)." },
  { "ahiReverseRoll", "uint8_t", "1", "", "Boolean: Reverse roll direction on Artificial Horizon (osdConfig()->ahi_reverse_roll)." },
  { "crosshairsStyle", "uint8_t", "1", "", "Enum: Style of the center crosshairs (osdConfig()->crosshairs_style)." },
  { "leftSidebarScroll", "uint8_t", "1", "", "Boolean: Enable scrolling for left sidebar (osdConfig()->left_sidebar_scroll)." },
  { "rightSidebarScroll", "uint8_t", "1", "", "Boolean: Enable scrolling for right sidebar (osdConfig()->right_sidebar_scroll)." },
  { "sidebarScrollArrows", "uint8_t", "1", "", "Boolean: Show arrows for scrollable sidebars (osdConfig()->sidebar_scroll_arrows)." },
  { "units", "uint8_t", "1", "", "Enum: Measurement units (Metric/Imperial) (osdConfig()->units)." },
  { "statsEnergyUnit", "uint8_t", "1", "", "Enum: Unit for energy display in post-flight stats (osdConfig()->stats_energy_unit)." },
};

inline constexpr Field FIELDS_187[] = {
  { "videoSystem", "uint8_t", "1", "", "Sets osdConfigMutable()->video_system." },
  { "mainVoltageDecimals", "uint8_t", "1", "", "Sets osdConfigMutable()->main_voltage_decimals." },
  { "ahiReverseRoll", "uint8_t", "1", "", "Sets osdConfigMutable()->ahi_reverse_roll." },
  { "crosshairsStyle", "uint8_t", "1", "", "Sets osdConfigMutable()->crosshairs_style." },
  { "leftSidebarScroll", "uint8_t", "1", "", "Sets osdConfigMutable()->left_sidebar_scroll." },
  { "rightSidebarScroll", "uint8_t", "1", "", "Sets osdConfigMutable()->right_sidebar_scroll." },
  { "sidebarScrollArrows", "uint8_t", "1", "", "Sets osdConfigMutable()->sidebar_scroll_arrows." },
  { "units", "uint8_t", "1", "", "Sets osdConfigMutable()->units." },
  { "statsEnergyUnit", "uint8_t", "1", "", "Sets osdConfigMutable()->stats_energy_unit." },
};

inline constexpr Field FIELDS_188[] = {
  { "batteryProfileIndex", "uint8_t", "1", "", "Index of the battery profile to activate (0-based)." },
};

inline constexpr Field FIELDS_189[] = {
  { "debugValues", "uint32_t[DEBUG32_VALUE_COUNT]", "DEBUG32_VALUE_COUNT 4", "", "Values from the debug array (typically 8 values)." },
};

inline constexpr Field FIELDS_190[] = {
  { "blackboxSupported", "uint8_t", "1", "", "Boolean: 1 if Blackbox is supported (USE_BLACKBOX), 0 otherwise." },
  { "blackboxDevice", "uint8_t", "1", "", "Enum (blackboxDevice_e): Target device for logging (blackboxConfig()->device). 0 if not supported." },
  { "blackboxRateNum", "uint16_t", "2", "", "Numerator for logging rate divider (blackboxConfig()->rate_num). 0 if not supported." },
  { "blackboxRateDenom", "uint16_t", "2", "", "Denominator for logging rate divider (blackboxConfig()->rate_denom). 0 if not supported." },
  { "blackboxIncludeFlags", "uint32_t", "4", "", "Bitmask: Flags for fields included/excluded from logging (blackboxConfig()->includeFlags)." },
};

inline constexpr Field FIELDS_191[] = {
  { "blackboxDevice", "uint8_t", "1", "", "Sets blackboxConfigMutable()->device." },
  { "blackboxRateNum", "uint16_t", "2", "", "Sets blackboxConfigMutable()->rate_num." },
  { "blackboxRateDenom", "uint16_t", "2", "", "Sets blackboxConfigMutable()->rate_denom." },
  { "blackboxIncludeFlags", "uint32_t", "4", "", "Sets blackboxConfigMutable()->includeFlags." },
};

inline constexpr Field FIELDS_192[] = {
  { "type", "uint8_t", "1", "", "Enum (tempSensorType_e): Type of the temperature sensor." },
  { "address", "uint64_t", "8", "", "Sensor address/ID (e.g., for 1-Wire sensors)." },
  { "alarmMin", "uint16_t", "2", "", "Min temperature alarm threshold (degrees C)." },
  { "alarmMax", "uint16_t", "2", "", "Max temperature alarm threshold (degrees C)." },
  { "osdSymbol", "uint8_t", "1", "", "Index: OSD symbol to use for this sensor (0 to TEMP_SENSOR_SYM_COUNT)." },
  { "label", "char[TEMPERATURE_LABEL_LEN]", "TEMPERATURE_LABEL_LEN", "", "User-defined label for the sensor." },
};

inline constexpr Field FIELDS_193[] = {
  { "type", "uint8_t", "1", "", "Sets sensor type." },
  { "address", "uint64_t", "8", "", "Sets sensor address/ID." },
  { "alarmMin", "uint16_t", "2", "", "Sets min alarm threshold." },
  { "alarmMax", "uint16_t", "2", "", "Sets max alarm threshold." },
  { "osdSymbol", "uint8_t", "1", "", "Sets OSD symbol index (validated)." },
  { "label", "char[TEMPERATURE_LABEL_LEN]", "TEMPERATURE_LABEL_LEN", "", "Sets sensor label (converted to uppercase)." },
};

inline constexpr Field FIELDS_194[] = {
  { "temperature", "int16_t", "2", "degrees C", "Current temperature reading. -1000 if sensor is invalid or reading failed." },
};

inline constexpr Field FIELDS_195[] = {
  { "simulatorVersion", "uint8_t", "1", "", "Version of the simulator protocol (SIMULATOR_MSP_VERSION)." },
  { "hitlFlags", "uint8_t", "1", "", "Bitmask: Options for HITL (HITL_ flags)." },
  { "gpsFixType", "uint8_t", "1", "", "(If HITL_HAS_NEW_GPS_DATA) Simulated GPS fix type." },
  { "gpsNumSat", "uint8_t", "1", "", "(If HITL_HAS_NEW_GPS_DATA) Simulated satellite count." },
  { "gpsLat", "uint32_t", "4", "", "(If HITL_HAS_NEW_GPS_DATA) Simulated latitude (1e7 deg)." },
  { "gpsLon", "uint32_t", "4", "", "(If HITL_HAS_NEW_GPS_DATA) Simulated longitude (1e7 deg)." },
  { "gpsAlt", "uint32_t", "4", "", "(If HITL_HAS_NEW_GPS_DATA) Simulated altitude (cm)." },
  { "gpsSpeed", "uint16_t", "2", "", "(If HITL_HAS_NEW_GPS_DATA) Simulated ground speed (cm/s)." },
  { "gpsCourse", "uint16_t", "2", "", "(If HITL_HAS_NEW_GPS_DATA) Simulated ground course (deci-deg)." },
  { "gpsVelN", "int16_t", "2", "", "(If HITL_HAS_NEW_GPS_DATA) Simulated North velocity (cm/s)." },
  { "gpsVelE", "int16_t", "2", "", "(If HITL_HAS_NEW_GPS_DATA) Simulated East velocity (cm/s)." },
  { "gpsVelD", "int16_t", "2", "", "(If HITL_HAS_NEW_GPS_DATA) Simulated Down velocity (cm/s)." },
  { "imuRoll", "int16_t", "2", "", "(If NOT HITL_USE_IMU) Simulated Roll (deci-deg)." },
  { "imuPitch", "int16_t", "2", "", "(If NOT HITL_USE_IMU) Simulated Pitch (deci-deg)." },
  { "imuYaw", "int16_t", "2", "", "(If NOT HITL_USE_IMU) Simulated Yaw (deci-deg)." },
  { "vbat", "uint8_t", "1", "", "(If HITL_EXT_BATTERY_VOLTAGE) Simulated battery voltage (0.1V units)." },
  { "airspeed", "uint16_t", "2", "", "(If HITL_AIRSPEED) Simulated airspeed (cm/s)." },
  { "extFlags", "uint8_t", "1", "", "(If HITL_EXTENDED_FLAGS) Additional flags (upper 8 bits)." },
  { "stabilizedRoll", "uint16_t", "2", "", "Stabilized Roll command output (-500 to 500)." },
  { "stabilizedPitch", "uint16_t", "2", "", "Stabilized Pitch command output (-500 to 500)." },
  { "stabilizedYaw", "uint16_t", "2", "", "Stabilized Yaw command output (-500 to 500)." },
  { "stabilizedThrottle", "uint16_t", "2", "", "Stabilized Throttle command output (-500 to 500 if armed, else -500)." },
  { "debugFlags", "uint8_t", "1", "", "Packed flags: Debug index (0-7), Platform type, Armed state, OSD feature status." },
  { "debugValue", "uint32_t", "4", "", "Current debug value (debug[simulatorData.debugIndex])." },
  { "attitudeRoll", "int16_t", "2", "", "Current estimated Roll (deci-deg)." },
  { "attitudePitch", "int16_t", "2", "", "Current estimated Pitch (deci-deg)." },
  { "attitudeYaw", "int16_t", "2", "", "Current estimated Yaw (deci-deg)." },
  { "osdHeader", "uint8_t", "1", "", "OSD RLE Header (255)." },
  { "osdRows", "uint8_t", "1", "", "(If OSD supported) Number of OSD rows." },
  { "osdCols", "uint8_t", "1", "", "(If OSD supported) Number of OSD columns." },
  { "osdStartY", "uint8_t", "1", "", "(If OSD supported) Starting row for RLE data." },
  { "osdStartX", "uint8_t", "1", "", "(If OSD supported) Starting column for RLE data." },
  { "osdRleData", "uint8_t[]", "Variable", "", "(If OSD supported) Run-length encoded OSD character data. Terminated by [0, 0]." },
};

inline constexpr Field FIELDS_196[] = {
  { "targetChannel", "uint8_t", "1", "", "Servo output channel index (0-based)." },
  { "inputSource", "uint8_t", "1", "", "Enum: Input source (mixerSource_t)." },
  { "rate", "uint16_t", "2", "", "Mixing rate/weight." },
  { "speed", "uint8_t", "1", "", "Speed/Slew rate limit (0-100)." },
  { "conditionId", "uint8_t", "1", "", "Logic Condition ID (0 to MAX_LOGIC_CONDITIONS - 1, or 255/-1 if none/disabled)." },
  { "targetChannel", "uint8_t", "1", "", "Profile 2 Target channel." },
  { "inputSource", "uint8_t", "1", "", "Profile 2 Input source." },
  { "rate", "uint16_t", "2", "", "Profile 2 Rate." },
  { "speed", "uint8_t", "1", "", "Profile 2 Speed." },
  { "conditionId", "uint8_t", "1", "", "Profile 2 Logic Condition ID." },
};

inline constexpr Field FIELDS_197[] = {
  { "ruleIndex", "uint8_t", "1", "", "Index of the rule to set (0 to MAX_SERVO_RULES - 1)." },
  { "targetChannel", "uint8_t", "1", "", "Servo output channel index." },
  { "inputSource", "uint8_t", "1", "", "Enum: Input source (mixerSource_t)." },
  { "rate", "uint16_t", "2", "", "Mixing rate/weight." },
  { "speed", "uint8_t", "1", "", "Speed/Slew rate limit (0-100)." },
  { "conditionId", "uint8_t", "1", "", "Logic Condition ID (255/-1 if none). Ignored if USE_PROGRAMMING_FRAMEWORK is disabled." },
};

inline constexpr Field FIELDS_198[] = {
  { "enabled", "uint8_t", "1", "", "Boolean: 1 if the condition is enabled." },
  { "activatorId", "uint8_t", "1", "", "ID of the activator condition (if any, 255 if none)." },
  { "operation", "uint8_t", "1", "", "Enum (logicConditionOp_e): Logical operation (AND, OR, XOR, etc.)." },
  { "operandAType", "uint8_t", "1", "", "Enum (logicOperandType_e): Type of the first operand (Flight Mode, GVAR, etc.)." },
  { "operandAValue", "uint32_t", "4", "", "Value/ID of the first operand." },
  { "operandBType", "uint8_t", "1", "", "Enum (logicOperandType_e): Type of the second operand." },
  { "operandBValue", "uint32_t", "4", "", "Value/ID of the second operand." },
  { "flags", "uint8_t", "1", "", "Bitmask: Condition flags (e.g., LC_FLAG_FIRST_TIME_TRUE)." },
};

inline constexpr Field FIELDS_199[] = {
  { "conditionIndex", "uint8_t", "1", "", "Index of the condition to set (0 to MAX_LOGIC_CONDITIONS - 1)." },
  { "enabled", "uint8_t", "1", "", "Boolean: 1 to enable the condition." },
  { "activatorId", "uint8_t", "1", "", "Activator condition ID." },
  { "operation", "uint8_t", "1", "", "Enum: Logical operation." },
  { "operandAType", "uint8_t", "1", "", "Enum: Type of operand A." },
  { "operandAValue", "uint32_t", "4", "", "Value/ID of operand A." },
  { "operandBType", "uint8_t", "1", "", "Enum: Type of operand B." },
  { "operandBValue", "uint32_t", "4", "", "Value/ID of operand B." },
  { "flags", "uint8_t", "1", "", "Bitmask: Condition flags." },
};

inline constexpr Field FIELDS_202[] = {
  { "conditionValues", "uint32_t[MAX_LOGIC_CONDITIONS]", "MAX_LOGIC_CONDITIONS 4", "", "Array of current values for each logic condition (logicConditionGetValue(i)). 1 for true, 0 for false, or numerical value depending on operation." },
};

inline constexpr Field FIELDS_203[] = {
  { "gvarValues", "uint32_t[MAX_GLOBAL_VARIABLES]", "MAX_GLOBAL_VARIABLES 4", "", "Array of current values for each global variable (gvGet(i))." },
};

inline constexpr Field FIELDS_204[] = {
  { "enabled", "uint8_t", "1", "", "Boolean: 1 if the PID is enabled." },
  { "setpointType", "uint8_t", "1", "", "Enum (logicOperandType_e): Type of the setpoint source." },
  { "setpointValue", "uint32_t", "4", "", "Value/ID of the setpoint source." },
  { "measurementType", "uint8_t", "1", "", "Enum (logicOperandType_e): Type of the measurement source." },
  { "measurementValue", "uint32_t", "4", "", "Value/ID of the measurement source." },
  { "gainP", "uint16_t", "2", "", "Proportional gain." },
  { "gainI", "uint16_t", "2", "", "Integral gain." },
  { "gainD", "uint16_t", "2", "", "Derivative gain." },
  { "gainFF", "uint16_t", "2", "", "Feed-forward gain." },
};

inline constexpr Field FIELDS_205[] = {
  { "pidIndex", "uint8_t", "1", "", "Index of the Programming PID to set (0 to MAX_PROGRAMMING_PID_COUNT - 1)." },
  { "enabled", "uint8_t", "1", "", "Boolean: 1 to enable the PID." },
  { "setpointType", "uint8_t", "1", "", "Enum: Type of the setpoint source." },
  { "setpointValue", "uint32_t", "4", "", "Value/ID of the setpoint source." },
  { "measurementType", "uint8_t", "1", "", "Enum: Type of the measurement source." },
  { "measurementValue", "uint32_t", "4", "", "Value/ID of the measurement source." },
  { "gainP", "uint16_t", "2", "", "Proportional gain." },
  { "gainI", "uint16_t", "2", "", "Integral gain." },
  { "gainD", "uint16_t", "2", "", "Derivative gain." },
  { "gainFF", "uint16_t", "2", "", "Feed-forward gain." },
};

inline constexpr Field FIELDS_206[] = {
  { "pidOutputs", "uint32_t[MAX_PROGRAMMING_PID_COUNT]", "MAX_PROGRAMMING_PID_COUNT 4", "", "Array of current output values for each Programming PID (programmingPidGetOutput(i))." },
};

inline constexpr Field FIELDS_207[] = {
  { "P", "uint8_t", "1", "", "Proportional gain (pidBank()->pid[i].P), constrained 0-255." },
  { "I", "uint8_t", "1", "", "Integral gain (pidBank()->pid[i].I), constrained 0-255." },
  { "D", "uint8_t", "1", "", "Derivative gain (pidBank()->pid[i].D), constrained 0-255." },
  { "FF", "uint8_t", "1", "", "Feed-forward gain (pidBank()->pid[i].FF), constrained 0-255." },
};

inline constexpr Field FIELDS_208[] = {
  { "P", "uint8_t", "1", "", "Sets Proportional gain (pidBankMutable()->pid[i].P)." },
  { "I", "uint8_t", "1", "", "Sets Integral gain (pidBankMutable()->pid[i].I)." },
  { "D", "uint8_t", "1", "", "Sets Derivative gain (pidBankMutable()->pid[i].D)." },
  { "FF", "uint8_t", "1", "", "Sets Feed-forward gain (pidBankMutable()->pid[i].FF)." },
};

inline constexpr Field FIELDS_210[] = {
  { "firmwareSize", "uint32_t", "4", "", "Total size of the incoming firmware file in bytes." },
};

inline constexpr Field FIELDS_211[] = {
  { "firmwareChunk", "uint8_t[]", "Variable", "", "Chunk of firmware data." },
};

inline constexpr Field FIELDS_212[] = {
  { "updateType", "uint8_t", "1", "", "Type of update (e.g., full flash, specific section - currently ignored/unused)." },
};

inline constexpr Field FIELDS_215[] = {
  { "safehomeIndex", "uint8_t", "1", "", "Index of the safe home location (0 to MAX_SAFE_HOMES - 1)." },
  { "safehomeIndex", "uint8_t", "1", "", "Index requested." },
  { "enabled", "uint8_t", "1", "", "Boolean: 1 if this safe home is enabled." },
  { "latitude", "int32_t", "4", "", "Latitude (1e7 deg)." },
  { "longitude", "int32_t", "4", "", "Longitude (1e7 deg)." },
};

inline constexpr Field FIELDS_216[] = {
  { "safehomeIndex", "uint8_t", "1", "", "Index of the safe home location (0 to MAX_SAFE_HOMES - 1)." },
  { "enabled", "uint8_t", "1", "", "Boolean: 1 to enable this safe home." },
  { "latitude", "int32_t", "4", "", "Latitude (1e7 deg)." },
  { "longitude", "int32_t", "4", "", "Longitude (1e7 deg)." },
};

inline constexpr Field FIELDS_217[] = {
  { "uptimeSeconds", "uint32_t", "4", "Seconds", "Time since boot (micros() / 1000000)." },
  { "flightTimeSeconds", "uint32_t", "4", "Seconds", "Accumulated flight time (getFlightTime())." },
  { "throttlePercent", "uint8_t", "1", "%", "Current throttle output percentage (getThrottlePercent(true))." },
  { "autoThrottleFlag", "uint8_t", "1", "Boolean", "1 if navigation is controlling throttle, 0 otherwise (navigationIsControllingThrottle())." },
};

inline constexpr Field FIELDS_218[] = {
  { "conditionIndex", "uint8_t", "1", "", "Index of the condition to retrieve (0 to MAX_LOGIC_CONDITIONS - 1)." },
  { "enabled", "uint8_t", "1", "", "Boolean: 1 if enabled." },
  { "activatorId", "uint8_t", "1", "", "Activator ID." },
  { "operation", "uint8_t", "1", "", "Enum: Logical operation." },
  { "operandAType", "uint8_t", "1", "", "Enum: Type of operand A." },
  { "operandAValue", "uint32_t", "4", "", "Value/ID of operand A." },
  { "operandBType", "uint8_t", "1", "", "Enum: Type of operand B." },
  { "operandBValue", "uint32_t", "4", "", "Value/ID of operand B." },
  { "flags", "uint8_t", "1", "", "Bitmask: Condition flags." },
};

inline constexpr Field FIELDS_219[] = {
  { "escRpm", "uint32_t", "4", "RPM", "RPM reported by the ESC." },
};

inline constexpr Field FIELDS_220[] = {
  { "motorCount", "uint8_t", "1", "", "Number of motors reporting telemetry (getMotorCount())." },
  { "escData", "escSensorData_t[]", "motorCount sizeof(escSensorData_t)", "", "Array of escSensorData_t structures containing voltage, current, temp, RPM, errors etc. for each ESC." },
};

inline constexpr Field FIELDS_221[] = {
  { "ledConfig", "ledConfig_t", "sizeof(ledConfig_t)", "", "Full configuration structure for the LED." },
};

inline constexpr Field FIELDS_222[] = {
  { "ledIndex", "uint8_t", "1", "", "Index of the LED to configure (0 to LED_MAX_STRIP_LENGTH - 1)." },
  { "ledConfig", "ledConfig_t", "sizeof(ledConfig_t)", "", "Full configuration structure for the LED." },
};

inline constexpr Field FIELDS_223[] = {
  { "approachIndex", "uint8_t", "1", "", "Index of the approach setting (0 to MAX_FW_LAND_APPOACH_SETTINGS - 1)." },
  { "approachIndex", "uint8_t", "1", "Index", "Index requested." },
  { "approachAlt", "uint32_t", "4", "cm", "Altitude for the approach phase." },
  { "landAlt", "uint32_t", "4", "cm", "Altitude for the final landing phase." },
  { "approachDirection", "uint8_t", "1", "Enum", "Direction of approach (From WP, Specific Heading)." },
  { "landHeading1", "int16_t", "2", "degrees", "Primary landing heading (if approachDirection requires it)." },
  { "landHeading2", "int16_t", "2", "degrees", "Secondary landing heading (if approachDirection requires it)." },
  { "isSeaLevelRef", "uint8_t", "1", "Boolean", "1 if altitudes are relative to sea level, 0 if relative to home." },
};

inline constexpr Field FIELDS_224[] = {
  { "approachIndex", "uint8_t", "1", "Index", "Index of the approach setting (0 to MAX_FW_LAND_APPOACH_SETTINGS - 1)." },
  { "approachAlt", "uint32_t", "4", "cm", "Sets approach altitude." },
  { "landAlt", "uint32_t", "4", "cm", "Sets landing altitude." },
  { "approachDirection", "uint8_t", "1", "Enum", "Sets approach direction." },
  { "landHeading1", "int16_t", "2", "degrees", "Sets primary landing heading." },
  { "landHeading2", "int16_t", "2", "degrees", "Sets secondary landing heading." },
  { "isSeaLevelRef", "uint8_t", "1", "Boolean", "Sets altitude reference." },
};

inline constexpr Field FIELDS_225[] = {
  { "ubxCommand", "uint8_t[]", "Variable (>= 8)", "", "Raw U-Blox UBX protocol command frame (including header, class, ID, length, payload, checksum)." },
};

inline constexpr Field FIELDS_226[] = {
  { "sensitivityCenter", "uint8_t", "1", "%", "Sensitivity at stick center (currentControlRateProfile->rateDynamics.sensitivityCenter)." },
  { "sensitivityEnd", "uint8_t", "1", "%", "Sensitivity at stick ends (currentControlRateProfile->rateDynamics.sensitivityEnd)." },
  { "correctionCenter", "uint8_t", "1", "%", "Correction strength at stick center (currentControlRateProfile->rateDynamics.correctionCenter)." },
  { "correctionEnd", "uint8_t", "1", "%", "Correction strength at stick ends (currentControlRateProfile->rateDynamics.correctionEnd)." },
  { "weightCenter", "uint8_t", "1", "%", "Transition weight at stick center (currentControlRateProfile->rateDynamics.weightCenter)." },
  { "weightEnd", "uint8_t", "1", "%", "Transition weight at stick ends (currentControlRateProfile->rateDynamics.weightEnd)." },
};

inline constexpr Field FIELDS_227[] = {
  { "sensitivityCenter", "uint8_t", "1", "%", "Sets sensitivity at center." },
  { "sensitivityEnd", "uint8_t", "1", "%", "Sets sensitivity at ends." },
  { "correctionCenter", "uint8_t", "1", "%", "Sets correction at center." },
  { "correctionEnd", "uint8_t", "1", "%", "Sets correction at ends." },
  { "weightCenter", "uint8_t", "1", "%", "Sets weight at center." },
  { "weightEnd", "uint8_t", "1", "%", "Sets weight at ends." },
};

inline constexpr Field FIELDS_228[] = {
  { "enabled", "uint8_t", "1", "", "Boolean: 1 if EZ-Tune is enabled (ezTune()->enabled)." },
  { "filterHz", "uint16_t", "2", "", "Filter frequency used during tuning (ezTune()->filterHz)." },
  { "axisRatio", "uint8_t", "1", "", "Roll vs Pitch axis tuning ratio (ezTune()->axisRatio)." },
  { "response", "uint8_t", "1", "", "Desired response characteristic (ezTune()->response)." },
  { "damping", "uint8_t", "1", "", "Desired damping characteristic (ezTune()->damping)." },
  { "stability", "uint8_t", "1", "", "Stability preference (ezTune()->stability)." },
  { "aggressiveness", "uint8_t", "1", "", "Aggressiveness preference (ezTune()->aggressiveness)." },
  { "rate", "uint8_t", "1", "", "Resulting rate setting (ezTune()->rate)." },
  { "expo", "uint8_t", "1", "", "Resulting expo setting (ezTune()->expo)." },
  { "snappiness", "uint8_t", "1", "", "Snappiness preference (ezTune()->snappiness)." },
};

inline constexpr Field FIELDS_229[] = {
  { "enabled", "uint8_t", "1", "", "Sets enabled state." },
  { "filterHz", "uint16_t", "2", "", "Sets filter frequency." },
  { "axisRatio", "uint8_t", "1", "", "Sets axis ratio." },
  { "response", "uint8_t", "1", "", "Sets response characteristic." },
  { "damping", "uint8_t", "1", "", "Sets damping characteristic." },
  { "stability", "uint8_t", "1", "", "Sets stability preference." },
  { "aggressiveness", "uint8_t", "1", "", "Sets aggressiveness preference." },
  { "rate", "uint8_t", "1", "", "Sets rate setting." },
  { "expo", "uint8_t", "1", "", "Sets expo setting." },
  { "snappiness", "uint8_t", "1", "", "(Optional) Sets snappiness preference." },
};

inline constexpr Field FIELDS_230[] = {
  { "mixerProfileIndex", "uint8_t", "1", "", "Index of the mixer profile to activate (0-based)." },
};

inline constexpr Field FIELDS_231[] = {
  { "maxVehicles", "uint8_t", "1", "", "Maximum number of vehicles tracked (MAX_ADSB_VEHICLES). 0 if USE_ADSB disabled." },
  { "callsignLength", "uint8_t", "1", "", "Maximum length of callsign string (ADSB_CALL_SIGN_MAX_LENGTH). 0 if USE_ADSB disabled." },
  { "totalVehicleMsgs", "uint32_t", "4", "", "Total vehicle messages received (getAdsbStatus()->vehiclesMessagesTotal). 0 if USE_ADSB disabled." },
  { "totalHeartbeatMsgs", "uint32_t", "4", "", "Total heartbeat messages received (getAdsbStatus()->heartbeatMessagesTotal). 0 if USE_ADSB disabled." },
  { "Vehicle Data (Repeated maxVehicles times):", "", "", "", "" },
  { "callsign", "char[ADSB_CALL_SIGN_MAX_LENGTH]", "ADSB_CALL_SIGN_MAX_LENGTH", "", "Vehicle callsign (padded with nulls)." },
  { "icao", "uint32_t", "4", "", "ICAO 24-bit address." },
  { "latitude", "int32_t", "4", "", "Latitude (1e7 deg)." },
  { "longitude", "int32_t", "4", "", "Longitude (1e7 deg)." },
  { "altitude", "int32_t", "4", "", "Altitude (cm)." },
  { "heading", "int16_t", "2", "", "Heading (degrees)." },
  { "tslc", "uint8_t", "1", "", "Time Since Last Communication (seconds)." },
  { "emitterType", "uint8_t", "1", "", "Enum: Type of ADSB emitter." },
  { "ttl", "uint8_t", "1", "", "Time-to-live counter for this entry." },
};

inline constexpr Field FIELDS_232[] = {
  { "maxElements", "uint8_t", "1", "", "Maximum number of custom elements (MAX_CUSTOM_ELEMENTS)." },
  { "maxTextLength", "uint8_t", "1", "", "Maximum length of the text part (OSD_CUSTOM_ELEMENT_TEXT_SIZE - 1)." },
  { "maxParts", "uint8_t", "1", "", "Maximum number of parts per element (CUSTOM_ELEMENTS_PARTS)." },
};

inline constexpr Field FIELDS_233[] = {
  { "elementIndex", "uint8_t", "1", "", "Index of the custom element (0 to MAX_CUSTOM_ELEMENTS - 1)." },
  { "Parts Data (Repeated CUSTOM_ELEMENTS_PARTS times):", "", "", "", "" },
  { "partType", "uint8_t", "1", "", "Enum (customElementType_e): Type of this part (Text, Variable, Symbol)." },
  { "partValue", "uint16_t", "2", "", "Value/ID associated with this part (GVAR index, Symbol ID, etc.)." },
  { "Visibility Data:", "", "", "", "" },
  { "visibilityType", "uint8_t", "1", "", "Enum (logicOperandType_e): Type of visibility condition source." },
  { "visibilityValue", "uint16_t", "2", "", "Value/ID of the visibility condition source (e.g., Logic Condition ID)." },
  { "Text Data:", "", "", "", "" },
  { "elementText", "char[OSD_CUSTOM_ELEMENT_TEXT_SIZE - 1]", "OSD_CUSTOM_ELEMENT_TEXT_SIZE - 1", "", "Static text part of the element (null padding likely)." },
};

inline constexpr Field FIELDS_234[] = {
  { "elementIndex", "uint8_t", "1", "", "Index of the custom element (0 to MAX_CUSTOM_ELEMENTS - 1)." },
  { "Parts Data (Repeated CUSTOM_ELEMENTS_PARTS times):", "", "", "", "" },
  { "partType", "uint8_t", "1", "", "Enum (customElementType_e): Type of this part." },
  { "partValue", "uint16_t", "2", "", "Value/ID associated with this part." },
  { "Visibility Data:", "", "", "", "" },
  { "visibilityType", "uint8_t", "1", "", "Enum (logicOperandType_e): Type of visibility condition source." },
  { "visibilityValue", "uint16_t", "2", "", "Value/ID of the visibility condition source." },
  { "Text Data:", "", "", "", "" },
  { "elementText", "char[OSD_CUSTOM_ELEMENT_TEXT_SIZE - 1]", "OSD_CUSTOM_ELEMENT_TEXT_SIZE - 1", "", "Static text part of the element." },
};

inline constexpr Field FIELDS_235[] = {
  { "timerId", "uint8_t", "1", "", "Hardware timer identifier (e.g., TIM1, TIM2). SITL uses index." },
  { "usageFlags", "uint32_t", "4", "", "Full 32-bit timer usage flags (TIM_USE_)." },
  { "pinLabel", "uint8_t", "1", "", "Label for special pin usage (PIN_LABEL_ enum, e.g., PIN_LABEL_LED). 0 (PIN_LABEL_NONE) otherwise." },
};

inline constexpr Field FIELDS_236[] = {
  { "min", "uint16_t", "2", "PWM", "Minimum servo endpoint (servoParams(i)->min)." },
  { "max", "uint16_t", "2", "PWM", "Maximum servo endpoint (servoParams(i)->max)." },
  { "middle", "uint16_t", "2", "PWM", "Middle/Neutral servo position (servoParams(i)->middle)." },
  { "rate", "uint8_t", "1", "% (-100 to 100)", "Servo rate/scaling (servoParams(i)->rate)." },
};

inline constexpr Field FIELDS_237[] = {
  { "servoIndex", "uint8_t", "1", "Index", "Index of the servo to configure (0 to MAX_SUPPORTED_SERVOS - 1)." },
  { "min", "uint16_t", "2", "PWM", "Sets minimum servo endpoint." },
  { "max", "uint16_t", "2", "PWM", "Sets maximum servo endpoint." },
  { "middle", "uint16_t", "2", "PWM", "Sets middle/neutral servo position." },
  { "rate", "uint8_t", "1", "%", "Sets servo rate/scaling." },
};

inline constexpr Field FIELDS_238[] = {
  { "geozoneIndex", "uint8_t", "1", "", "Index of the geozone (0 to MAX_GEOZONES_IN_CONFIG - 1)." },
  { "geozoneIndex", "uint8_t", "1", "", "Index requested." },
  { "type", "uint8_t", "1", "", "Enum (GEOZONE_TYPE_): Zone type (Inclusion/Exclusion)." },
  { "shape", "uint8_t", "1", "", "Enum (GEOZONE_SHAPE_): Zone shape (Polygon/Circular)." },
  { "minAltitude", "uint32_t", "4", "", "Minimum allowed altitude within the zone (cm)." },
  { "maxAltitude", "uint32_t", "4", "", "Maximum allowed altitude within the zone (cm)." },
  { "isSeaLevelRef", "uint8_t", "1", "", "Boolean: 1 if altitudes are relative to sea level, 0 if relative to home." },
  { "fenceAction", "uint8_t", "1", "", "Enum (GEOZONE_ACTION_): Action to take upon boundary violation." },
  { "vertexCount", "uint8_t", "1", "", "Number of vertices defined for this zone." },
};

inline constexpr Field FIELDS_239[] = {
  { "geozoneIndex", "uint8_t", "1", "", "Index of the geozone (0 to MAX_GEOZONES_IN_CONFIG - 1)." },
  { "type", "uint8_t", "1", "", "Enum (GEOZONE_TYPE_): Zone type." },
  { "shape", "uint8_t", "1", "", "Enum (GEOZONE_SHAPE_): Zone shape." },
  { "minAltitude", "uint32_t", "4", "", "Minimum allowed altitude (cm)." },
  { "maxAltitude", "uint32_t", "4", "", "Maximum allowed altitude (cm)." },
  { "isSeaLevelRef", "uint8_t", "1", "", "Boolean: Altitude reference." },
  { "fenceAction", "uint8_t", "1", "", "Enum (GEOZONE_ACTION_): Fence action." },
  { "vertexCount", "uint8_t", "1", "", "Number of vertices to be defined (used for validation later)." },
};

inline constexpr Field FIELDS_240[] = {
  { "geozoneIndex", "uint8_t", "1", "", "Index of the geozone." },
  { "vertexId", "uint8_t", "1", "", "Index of the vertex within the zone (0-based). For circles, 0 = center." },
  { "geozoneIndex", "uint8_t", "1", "Index", "Geozone index requested." },
  { "vertexId", "uint8_t", "1", "Index", "Vertex index requested." },
  { "latitude", "int32_t", "4", "deg 1e7", "Vertex latitude." },
  { "longitude", "int32_t", "4", "deg 1e7", "Vertex longitude." },
  { "geozoneIndex", "uint8_t", "1", "Index", "Geozone index requested." },
  { "vertexId", "uint8_t", "1", "Index", "Vertex index requested (always 0 for center)." },
  { "centerLatitude", "int32_t", "4", "deg 1e7", "Center latitude." },
  { "centerLongitude", "int32_t", "4", "deg 1e7", "Center longitude." },
  { "radius", "uint32_t", "4", "cm", "Radius of the circular zone." },
};

inline constexpr Field FIELDS_241[] = {
  { "geozoneIndex", "uint8_t", "1", "Index", "Geozone index." },
  { "vertexId", "uint8_t", "1", "Index", "Vertex index (0-based)." },
  { "latitude", "int32_t", "4", "deg 1e7", "Vertex latitude." },
  { "longitude", "int32_t", "4", "deg 1e7", "Vertex longitude." },
  { "geozoneIndex", "uint8_t", "1", "Index", "Geozone index." },
  { "vertexId", "uint8_t", "1", "Index", "Vertex index (must be 0 for center)." },
  { "centerLatitude", "int32_t", "4", "deg 1e7", "Center latitude." },
  { "centerLongitude", "int32_t", "4", "deg 1e7", "Center longitude." },
  { "radius", "uint32_t", "4", "cm", "Radius of the circular zone." },
};

inline constexpr Message REGISTRY[] = {
  { "MSP_API_VERSION", 1u, "0x01", Direction::Out, "Provides the MSP protocol version and the INAV API version.", FIELDS_0, 3, false },
  { "MSP_FC_VARIANT", 2u, "0x02", Direction::Out, "Identifies the flight controller firmware variant (e.g., INAV, Betaflight).", FIELDS_1, 1, false },
  { "MSP_FC_VERSION", 3u, "0x03", Direction::Out, "Provides the specific version number of the flight controller firmware.", FIELDS_2, 3, false },
  { "MSP_BOARD_INFO", 4u, "0x04", Direction::Out, "Provides information about the specific hardware board and its capabilities.", FIELDS_3, 6, true },
  { "MSP_BUILD_INFO", 5u, "0x05", Direction::Out, "Provides build date, time, and Git revision of the firmware.", FIELDS_4, 3, false },
  { "MSP_INAV_PID", 6u, "0x06", Direction::Out, "Retrieves legacy INAV-specific PID controller related settings. Many fields are now obsolete or placeholders.", FIELDS_5, 12, false },
  { "MSP_SET_INAV_PID", 7u, "0x07", Direction::In, "Sets legacy INAV-specific PID controller related settings.", FIELDS_6, 12, false },
  { "MSP_NAME", 10u, "0x0a", Direction::Out, "Returns the user-defined craft name.", FIELDS_7, 1, true },
  { "MSP_SET_NAME", 11u, "0x0b", Direction::In, "Sets the user-defined craft name.", FIELDS_8, 1, true },
  { "MSP_NAV_POSHOLD", 12u, "0x0c", Direction::Out, "Retrieves navigation position hold and general manual/auto flight parameters. Some parameters depend on the platform type (Multirotor vs Fixed Wing).", FIELDS_9, 8, false },
  { "MSP_SET_NAV_POSHOLD", 13u, "0x0d", Direction::In, "Sets navigation position hold and general manual/auto flight parameters.", FIELDS_10, 8, false },
  { "MSP_CALIBRATION_DATA", 14u, "0x0e", Direction::Out, "Retrieves sensor calibration data (Accelerometer zero/gain, Magnetometer zero/gain, Optical Flow scale).", FIELDS_11, 14, false },
  { "MSP_SET_CALIBRATION_DATA", 15u, "0x0f", Direction::In, "Sets sensor calibration data.", FIELDS_12, 13, false },
  { "MSP_POSITION_ESTIMATION_CONFIG", 16u, "0x10", Direction::Out, "Retrieves parameters related to the INAV position estimation fusion weights and GPS minimum satellite count.", FIELDS_13, 7, false },
  { "MSP_SET_POSITION_ESTIMATION_CONFIG", 17u, "0x11", Direction::In, "Sets parameters related to the INAV position estimation fusion weights and GPS minimum satellite count.", FIELDS_14, 7, false },
  { "MSP_WP_MISSION_LOAD", 18u, "0x12", Direction::In, "Commands the FC to load the waypoint mission stored in non-volatile memory (e.g., EEPROM or FlashFS) into the active mission buffer.", FIELDS_15, 1, false },
  { "MSP_WP_MISSION_SAVE", 19u, "0x13", Direction::In, "Commands the FC to save the currently active waypoint mission from RAM to non-volatile memory (e.g., EEPROM or FlashFS).", FIELDS_16, 1, false },
  { "MSP_WP_GETINFO", 20u, "0x14", Direction::Out, "Retrieves information about the waypoint mission capabilities and the status of the currently loaded mission.", FIELDS_17, 4, false },
  { "MSP_RTH_AND_LAND_CONFIG", 21u, "0x15", Direction::Out, "Retrieves configuration parameters related to Return-to-Home (RTH) and automatic landing behaviors.", FIELDS_18, 13, false },
  { "MSP_SET_RTH_AND_LAND_CONFIG", 22u, "0x16", Direction::In, "Sets configuration parameters related to Return-to-Home (RTH) and automatic landing behaviors.", FIELDS_19, 13, false },
  { "MSP_FW_CONFIG", 23u, "0x17", Direction::Out, "Retrieves configuration parameters specific to Fixed Wing navigation.", FIELDS_20, 8, false },
  { "MSP_SET_FW_CONFIG", 24u, "0x18", Direction::In, "Sets configuration parameters specific to Fixed Wing navigation.", FIELDS_21, 8, false },
  { "MSP_MODE_RANGES", 34u, "0x22", Direction::Out, "Returns all defined mode activation ranges (aux channel assignments for flight modes).", FIELDS_22, 4, false },
  { "MSP_SET_MODE_RANGE", 35u, "0x23", Direction::In, "Sets a single mode activation range by its index.", FIELDS_23, 5, false },
  { "MSP_FEATURE", 36u, "0x24", Direction::Out, "Returns a bitmask of enabled features.", FIELDS_24, 1, false },
  { "MSP_SET_FEATURE", 37u, "0x25", Direction::In, "Sets the enabled features using a bitmask. Clears all previous features first.", FIELDS_25, 1, false },
  { "MSP_BOARD_ALIGNMENT", 38u, "0x26", Direction::Out, "Returns the sensor board alignment angles relative to the craft frame.", FIELDS_26, 3, false },
  { "MSP_SET_BOARD_ALIGNMENT", 39u, "0x27", Direction::In, "Sets the sensor board alignment angles.", FIELDS_27, 3, false },
  { "MSP_CURRENT_METER_CONFIG", 40u, "0x28", Direction::Out, "Retrieves the configuration for the current sensor.", FIELDS_28, 4, false },
  { "MSP_SET_CURRENT_METER_CONFIG", 41u, "0x29", Direction::In, "Sets the configuration for the current sensor.", FIELDS_29, 4, false },
  { "MSP_MIXER", 42u, "0x2a", Direction::Out, "Retrieves the mixer type (Legacy, INAV always returns QuadX).", FIELDS_30, 1, false },
  { "MSP_SET_MIXER", 43u, "0x2b", Direction::In, "Sets the mixer type (Legacy, ignored by INAV).", FIELDS_31, 1, false },
  { "MSP_RX_CONFIG", 44u, "0x2c", Direction::Out, "Retrieves receiver configuration settings. Some fields are Betaflight compatibility placeholders.", FIELDS_32, 15, false },
  { "MSP_SET_RX_CONFIG", 45u, "0x2d", Direction::In, "Sets receiver configuration settings.", FIELDS_33, 15, false },
  { "MSP_LED_COLORS", 46u, "0x2e", Direction::Out, "Retrieves the HSV color definitions for configurable LED colors.", FIELDS_34, 3, false },
  { "MSP_SET_LED_COLORS", 47u, "0x2f", Direction::In, "Sets the HSV color definitions for configurable LED colors.", FIELDS_35, 3, false },
  { "MSP_LED_STRIP_CONFIG", 48u, "0x30", Direction::Out, "Retrieves the configuration for each LED on the strip (legacy packed format).", FIELDS_36, 1, false },
  { "MSP_SET_LED_STRIP_CONFIG", 49u, "0x31", Direction::In, "Sets the configuration for a single LED on the strip using the legacy packed format.", FIELDS_37, 2, false },
  { "MSP_RSSI_CONFIG", 50u, "0x32", Direction::Out, "Retrieves the channel used for analog RSSI input.", FIELDS_38, 1, false },
  { "MSP_SET_RSSI_CONFIG", 51u, "0x33", Direction::In, "Sets the channel used for analog RSSI input.", FIELDS_39, 1, false },
  { "MSP_ADJUSTMENT_RANGES", 52u, "0x34", Direction::Out, "Returns all defined RC adjustment ranges (tuning via aux channels).", FIELDS_40, 6, false },
  { "MSP_SET_ADJUSTMENT_RANGE", 53u, "0x35", Direction::In, "Sets a single RC adjustment range configuration by its index.", FIELDS_41, 7, false },
  { "MSP_CF_SERIAL_CONFIG", 54u, "0x36", Direction::Out, "Deprecated command to get serial port configuration.", nullptr, 0, false },
  { "MSP_SET_CF_SERIAL_CONFIG", 55u, "0x37", Direction::In, "Deprecated command to set serial port configuration.", nullptr, 0, false },
  { "MSP_VOLTAGE_METER_CONFIG", 56u, "0x38", Direction::Out, "Retrieves legacy voltage meter configuration (scaled values).", FIELDS_44, 4, false },
  { "MSP_SET_VOLTAGE_METER_CONFIG", 57u, "0x39", Direction::In, "Sets legacy voltage meter configuration (scaled values).", FIELDS_45, 4, false },
  { "MSP_SONAR_ALTITUDE", 58u, "0x3a", Direction::Out, "Retrieves the altitude measured by the primary rangefinder (sonar or lidar).", FIELDS_46, 1, false },
  { "MSP_RX_MAP", 64u, "0x40", Direction::Out, "Retrieves the RC channel mapping array (AETR, etc.).", FIELDS_47, 1, true },
  { "MSP_SET_RX_MAP", 65u, "0x41", Direction::In, "Sets the RC channel mapping array.", FIELDS_48, 1, true },
  { "MSP_REBOOT", 68u, "0x44", Direction::Out, "Commands the flight controller to reboot.", nullptr, 0, false },
  { "MSP_DATAFLASH_SUMMARY", 70u, "0x46", Direction::Out, "Retrieves summary information about the onboard dataflash chip (if present and used for Blackbox via FlashFS).", FIELDS_50, 4, false },
  { "MSP_DATAFLASH_READ", 71u, "0x47", Direction::InOut, "Reads a block of data from the onboard dataflash (FlashFS).", FIELDS_51, 4, true },
  { "MSP_DATAFLASH_ERASE", 72u, "0x48", Direction::In, "Erases the entire onboard dataflash chip (FlashFS volume).", nullptr, 0, false },
  { "MSP_LOOP_TIME", 73u, "0x49", Direction::Out, "Retrieves the configured loop time (PID loop frequency denominator).", FIELDS_53, 1, false },
  { "MSP_SET_LOOP_TIME", 74u, "0x4a", Direction::In, "Sets the configured loop time.", FIELDS_54, 1, false },
  { "MSP_FAILSAFE_CONFIG", 75u, "0x4b", Direction::Out, "Retrieves the failsafe configuration settings.", FIELDS_55, 13, false },
  { "MSP_SET_FAILSAFE_CONFIG", 76u, "0x4c", Direction::In, "Sets the failsafe configuration settings.", FIELDS_56, 13, false },
  { "MSP_SDCARD_SUMMARY", 79u, "0x4f", Direction::Out, "Retrieves summary information about the SD card status and filesystem.", FIELDS_57, 5, false },
  { "MSP_BLACKBOX_CONFIG", 80u, "0x50", Direction::Out, "Legacy command to retrieve Blackbox configuration. Superseded by MSP2_BLACKBOX_CONFIG.", FIELDS_58, 4, false },
  { "MSP_SET_BLACKBOX_CONFIG", 81u, "0x51", Direction::In, "Legacy command to set Blackbox configuration. Superseded by MSP2_SET_BLACKBOX_CONFIG.", nullptr, 0, false },
  { "MSP_TRANSPONDER_CONFIG", 82u, "0x52", Direction::Out, "Get VTX Transponder settings (likely specific to RaceFlight/Betaflight, not standard INAV VTX).", nullptr, 0, false },
  { "MSP_SET_TRANSPONDER_CONFIG", 83u, "0x53", Direction::In, "Set VTX Transponder settings.", nullptr, 0, false },
  { "MSP_OSD_CONFIG", 84u, "0x54", Direction::Out, "Retrieves OSD configuration settings and layout for screen 0.", FIELDS_62, 10, true },
  { "MSP_SET_OSD_CONFIG", 85u, "0x55", Direction::In, "Sets OSD configuration or a single item's position on screen 0.", FIELDS_63, 10, false },
  { "MSP_OSD_CHAR_READ", 86u, "0x56", Direction::Out, "Reads character data from the OSD font memory.", nullptr, 0, false },
  { "MSP_OSD_CHAR_WRITE", 87u, "0x57", Direction::In, "Writes character data to the OSD font memory.", FIELDS_65, 2, true },
  { "MSP_VTX_CONFIG", 88u, "0x58", Direction::Out, "Retrieves the current VTX (Video Transmitter) configuration and capabilities.", FIELDS_66, 11, false },
  { "MSP_SET_VTX_CONFIG", 89u, "0x59", Direction::In, "Sets the VTX configuration (band, channel, power, pit mode). Supports multiple protocol versions/extensions based on payload size.", FIELDS_67, 11, false },
  { "MSP_ADVANCED_CONFIG", 90u, "0x5a", Direction::Out, "Retrieves advanced hardware-related configuration (PWM protocols, rates). Some fields are BF compatibility placeholders.", FIELDS_68, 7, false },
  { "MSP_SET_ADVANCED_CONFIG", 91u, "0x5b", Direction::In, "Sets advanced hardware-related configuration (PWM protocols, rates).", FIELDS_69, 7, false },
  { "MSP_FILTER_CONFIG", 92u, "0x5c", Direction::Out, "Retrieves filter configuration settings (Gyro, D-term, Yaw, Accel). Some fields are BF compatibility placeholders or legacy.", FIELDS_70, 12, false },
  { "MSP_SET_FILTER_CONFIG", 93u, "0x5d", Direction::In, "Sets filter configuration settings. Handles different payload lengths for backward compatibility.", FIELDS_71, 12, false },
  { "MSP_PID_ADVANCED", 94u, "0x5e", Direction::Out, "Retrieves advanced PID tuning parameters. Many fields are BF compatibility placeholders.", FIELDS_72, 11, false },
  { "MSP_SET_PID_ADVANCED", 95u, "0x5f", Direction::In, "Sets advanced PID tuning parameters.", FIELDS_73, 11, false },
  { "MSP_SENSOR_CONFIG", 96u, "0x60", Direction::Out, "Retrieves the configured hardware type for various sensors.", FIELDS_74, 6, false },
  { "MSP_SET_SENSOR_CONFIG", 97u, "0x61", Direction::In, "Sets the configured hardware type for various sensors.", FIELDS_75, 6, false },
  { "MSP_SPECIAL_PARAMETERS", 98u, "0x62", Direction::Out, "Betaflight specific, likely unused/unimplemented in INAV.", nullptr, 0, false },
  { "MSP_SET_SPECIAL_PARAMETERS", 99u, "0x63", Direction::In, "Betaflight specific, likely unused/unimplemented in INAV.", nullptr, 0, false },
  { "MSP_IDENT", 100u, "0x64", Direction::Out, "Provides basic flight controller identity information. Not implemented in modern INAV, but used by legacy versions and MultiWii.", FIELDS_78, 3, false },
  { "MSP_STATUS", 101u, "0x65", Direction::Out, "Provides basic flight controller status including cycle time, errors, sensor status, active modes (first 32), and the current configuration profile.", FIELDS_79, 5, false },
  { "MSP_RAW_IMU", 102u, "0x66", Direction::Out, "Provides raw sensor readings from the IMU (Accelerometer, Gyroscope, Magnetometer).", FIELDS_80, 9, false },
  { "MSP_SERVO", 103u, "0x67", Direction::Out, "Provides the current output values for all supported servos.", FIELDS_81, 1, true },
  { "MSP_MOTOR", 104u, "0x68", Direction::Out, "Provides the current output values for the first 8 motors.", FIELDS_82, 1, false },
  { "MSP_RC", 105u, "0x69", Direction::Out, "Provides the current values of the received RC channels.", FIELDS_83, 1, true },
  { "MSP_RAW_GPS", 106u, "0x6a", Direction::Out, "Provides raw GPS data (fix status, coordinates, altitude, speed, course).", FIELDS_84, 8, false },
  { "MSP_COMP_GPS", 107u, "0x6b", Direction::Out, "Provides computed GPS values: distance and direction to home.", FIELDS_85, 3, false },
  { "MSP_ATTITUDE", 108u, "0x6c", Direction::Out, "Provides the current attitude estimate (roll, pitch, yaw).", FIELDS_86, 3, false },
  { "MSP_ALTITUDE", 109u, "0x6d", Direction::Out, "Provides estimated altitude, vertical speed (variometer), and raw barometric altitude.", FIELDS_87, 3, false },
  { "MSP_ANALOG", 110u, "0x6e", Direction::Out, "Provides analog sensor readings: battery voltage, current consumption (mAh), RSSI, and current draw (Amps).", FIELDS_88, 4, false },
  { "MSP_RC_TUNING", 111u, "0x6f", Direction::Out, "Retrieves RC tuning parameters (rates, expos, TPA) for the current control rate profile.", FIELDS_89, 10, false },
  { "MSP_ACTIVEBOXES", 113u, "0x71", Direction::Out, "Provides the full bitmask of currently active flight modes (boxes).", FIELDS_90, 1, true },
  { "MSP_MISC", 114u, "0x72", Direction::Out, "Retrieves miscellaneous configuration settings, mostly related to RC, GPS, Mag, and Battery voltage (legacy formats).", FIELDS_91, 16, false },
  { "MSP_BOXNAMES", 116u, "0x74", Direction::Out, "Provides a semicolon-separated string containing the names of all available flight modes (boxes).", FIELDS_92, 1, true },
  { "MSP_PIDNAMES", 117u, "0x75", Direction::Out, "Provides a semicolon-separated string containing the names of the PID controllers.", FIELDS_93, 1, true },
  { "MSP_WP", 118u, "0x76", Direction::InOut, "Get/Set a single waypoint from the mission plan.", FIELDS_94, 10, false },
  { "MSP_BOXIDS", 119u, "0x77", Direction::Out, "Provides a list of permanent IDs associated with the available flight modes (boxes).", FIELDS_95, 1, true },
  { "MSP_SERVO_CONFIGURATIONS", 120u, "0x78", Direction::Out, "Retrieves the configuration parameters for all supported servos (min, max, middle, rate). Legacy format with unused fields.", FIELDS_96, 8, false },
  { "MSP_NAV_STATUS", 121u, "0x79", Direction::Out, "Retrieves the current status of the navigation system.", FIELDS_97, 6, false },
  { "MSP_NAV_CONFIG", 122u, "0x7a", Direction::Unknown, "", nullptr, 0, false },
  { "MSP_3D", 124u, "0x7c", Direction::Out, "Retrieves settings related to 3D/reversible motor operation.", FIELDS_99, 3, false },
  { "MSP_RC_DEADBAND", 125u, "0x7d", Direction::Out, "Retrieves RC input deadband settings.", FIELDS_100, 4, false },
  { "MSP_SENSOR_ALIGNMENT", 126u, "0x7e", Direction::Out, "Retrieves sensor alignment settings (legacy format).", FIELDS_101, 4, false },
  { "MSP_LED_STRIP_MODECOLOR", 127u, "0x7f", Direction::Out, "Retrieves the color index assigned to each LED mode and function/direction combination, including special colors.", FIELDS_102, 3, false },
  { "MSP_BATTERY_STATE", 130u, "0x82", Direction::Out, "Provides battery state information, formatted primarily for DJI FPV Goggles compatibility.", FIELDS_103, 7, false },
  { "MSP_VTXTABLE_BAND", 137u, "0x89", Direction::InOut, "Retrieves information about a specific VTX band from the VTX table. (Implementation missing in provided fc_msp.c)", nullptr, 0, false },
  { "MSP_VTXTABLE_POWERLEVEL", 138u, "0x8a", Direction::InOut, "Retrieves information about a specific VTX power level from the VTX table.", FIELDS_105, 5, true },
  { "MSP_STATUS_EX", 150u, "0x96", Direction::Out, "Provides extended flight controller status, including CPU load, arming flags, and calibration status, in addition to MSP_STATUS fields.", FIELDS_106, 8, false },
  { "MSP_SENSOR_STATUS", 151u, "0x97", Direction::Out, "Provides the hardware status for each individual sensor system.", FIELDS_107, 9, false },
  { "MSP_UID", 160u, "0xa0", Direction::Out, "Provides the unique identifier of the microcontroller.", FIELDS_108, 3, false },
  { "MSP_GPSSVINFO", 164u, "0xa4", Direction::Out, "Provides satellite signal strength information (legacy U-Blox compatibility stub).", FIELDS_109, 4, false },
  { "MSP_GPSSTATISTICS", 166u, "0xa6", Direction::Out, "Provides debugging statistics for the GPS communication link.", FIELDS_110, 7, false },
  { "MSP_SET_TX_INFO", 186u, "0xba", Direction::In, "Allows a transmitter LUA script (or similar) to send runtime information (currently only RSSI) to the firmware.", FIELDS_111, 1, false },
  { "MSP_TX_INFO", 187u, "0xbb", Direction::Out, "Provides information potentially useful for transmitter LUA scripts.", FIELDS_112, 2, false },
  { "MSP_SET_RAW_RC", 200u, "0xc8", Direction::In, "Provides raw RC channel data to the flight controller, typically used when the receiver is connected via MSP (e.g., MSP RX feature).", FIELDS_113, 1, true },
  { "MSP_SET_RAW_GPS", 201u, "0xc9", Direction::In, "Provides raw GPS data to the flight controller, typically for simulation or external GPS injection.", FIELDS_114, 7, false },
  { "MSP_SET_BOX", 203u, "0xcb", Direction::In, "Sets the state of flight modes (boxes). (Likely unused/obsolete in INAV).", nullptr, 0, false },
  { "MSP_SET_RC_TUNING", 204u, "0xcc", Direction::In, "Sets RC tuning parameters (rates, expos, TPA) for the current control rate profile.", FIELDS_116, 10, false },
  { "MSP_ACC_CALIBRATION", 205u, "0xcd", Direction::In, "Starts the accelerometer calibration procedure.", nullptr, 0, false },
  { "MSP_MAG_CALIBRATION", 206u, "0xce", Direction::In, "Starts the magnetometer calibration procedure.", nullptr, 0, false },
  { "MSP_SET_MISC", 207u, "0xcf", Direction::In, "Sets miscellaneous configuration settings (legacy formats/scaling).", FIELDS_119, 16, false },
  { "MSP_RESET_CONF", 208u, "0xd0", Direction::In, "Resets all configuration settings to their default values and saves to EEPROM.", nullptr, 0, false },
  { "MSP_SET_WP", 209u, "0xd1", Direction::In, "Sets a single waypoint in the mission plan.", FIELDS_121, 9, false },
  { "MSP_SELECT_SETTING", 210u, "0xd2", Direction::In, "Selects the active configuration profile and saves it.", FIELDS_122, 1, false },
  { "MSP_SET_HEAD", 211u, "0xd3", Direction::In, "Sets the target heading for the heading hold controller (e.g., during MAG mode).", FIELDS_123, 1, false },
  { "MSP_SET_SERVO_CONFIGURATION", 212u, "0xd4", Direction::In, "Sets the configuration for a single servo (legacy format).", FIELDS_124, 9, false },
  { "MSP_SET_MOTOR", 214u, "0xd6", Direction::In, "Sets the disarmed motor values, typically used for motor testing or propeller balancing functions in a configurator.", FIELDS_125, 1, false },
  { "MSP_SET_NAV_CONFIG", 215u, "0xd7", Direction::Unknown, "", nullptr, 0, false },
  { "MSP_SET_3D", 217u, "0xd9", Direction::In, "Sets parameters related to 3D/reversible motor operation.", FIELDS_127, 3, false },
  { "MSP_SET_RC_DEADBAND", 218u, "0xda", Direction::In, "Sets RC input deadband values.", FIELDS_128, 4, false },
  { "MSP_SET_RESET_CURR_PID", 219u, "0xdb", Direction::In, "Resets the PIDs of the current profile to their default values. Does not save.", nullptr, 0, false },
  { "MSP_SET_SENSOR_ALIGNMENT", 220u, "0xdc", Direction::In, "Sets sensor alignment (legacy format).", FIELDS_130, 4, false },
  { "MSP_SET_LED_STRIP_MODECOLOR", 221u, "0xdd", Direction::In, "Sets the color index for a specific LED mode/function combination.", FIELDS_131, 3, false },
  { "MSP_SET_ACC_TRIM", 239u, "0xef", Direction::In, "Sets the accelerometer trim values (leveling calibration).", nullptr, 0, false },
  { "MSP_ACC_TRIM", 240u, "0xf0", Direction::Out, "Gets the accelerometer trim values.", nullptr, 0, false },
  { "MSP_SERVO_MIX_RULES", 241u, "0xf1", Direction::Out, "Retrieves the custom servo mixer rules (legacy format).", FIELDS_134, 7, false },
  { "MSP_SET_SERVO_MIX_RULE", 242u, "0xf2", Direction::In, "Sets a single custom servo mixer rule (legacy format).", FIELDS_135, 7, false },
  { "MSP_SET_PASSTHROUGH", 245u, "0xf5", Direction::InOut, "Enables serial passthrough mode to peripherals like ESCs (BLHeli 4-way) or other serial devices.", FIELDS_136, 3, false },
  { "MSP_RTC", 246u, "0xf6", Direction::Out, "Retrieves the current Real-Time Clock time.", FIELDS_137, 2, false },
  { "MSP_SET_RTC", 247u, "0xf7", Direction::In, "Sets the Real-Time Clock time.", FIELDS_138, 2, false },
  { "MSP_EEPROM_WRITE", 250u, "0xfa", Direction::In, "Saves the current configuration from RAM to non-volatile memory (EEPROM/Flash).", nullptr, 0, false },
  { "MSP_DEBUGMSG", 253u, "0xfd", Direction::Out, "Retrieves debug (\"serial printf\") messages from the firmware.", FIELDS_140, 1, true },
  { "MSP_DEBUG", 254u, "0xfe", Direction::Out, "Retrieves values from the firmware's debug[] array (legacy 16-bit version).", FIELDS_141, 1, false },
  { "MSP_V2_FRAME", 255u, "0xff", Direction::In, "This ID is used as a payload indicator within an MSPv1 message structure ($M>) to signify that the following payload conforms to the MSPv2 format. It's not a command itself.", nullptr, 0, false },
  { "MSP2_COMMON_TZ", 4097u, "0x1001", Direction::Out, "Gets the time zone offset configuration.", FIELDS_143, 2, false },
  { "MSP2_COMMON_SET_TZ", 4098u, "0x1002", Direction::In, "Sets the time zone offset configuration.", FIELDS_144, 3, false },
  { "MSP2_COMMON_SETTING", 4099u, "0x1003", Direction::InOut, "Gets the value of a specific configuration setting, identified by name or index.", FIELDS_145, 4, true },
  { "MSP2_COMMON_SET_SETTING", 4100u, "0x1004", Direction::In, "Sets the value of a specific configuration setting, identified by name or index.", FIELDS_146, 2, true },
  { "MSP2_COMMON_MOTOR_MIXER", 4101u, "0x1005", Direction::Out, "Retrieves the current motor mixer configuration (throttle, roll, pitch, yaw weights for each motor) for the primary and secondary mixer profiles.", FIELDS_147, 8, false },
  { "MSP2_COMMON_SET_MOTOR_MIXER", 4102u, "0x1006", Direction::In, "Sets the motor mixer weights for a single motor in the primary mixer profile.", FIELDS_148, 5, false },
  { "MSP2_COMMON_SETTING_INFO", 4103u, "0x1007", Direction::InOut, "Gets detailed information about a specific configuration setting (name, type, range, flags, current value, etc.).", FIELDS_149, 12, true },
  { "MSP2_COMMON_PG_LIST", 4104u, "0x1008", Direction::InOut, "Gets a list of Parameter Group Numbers (PGNs) used by settings, along with the start and end setting indexes for each group. Can request info for a single PGN.", FIELDS_150, 4, false },
  { "MSP2_COMMON_SERIAL_CONFIG", 4105u, "0x1009", Direction::Out, "Retrieves the configuration for all available serial ports.", FIELDS_151, 6, false },
  { "MSP2_COMMON_SET_SERIAL_CONFIG", 4106u, "0x100a", Direction::In, "Sets the configuration for one or more serial ports.", FIELDS_152, 6, false },
  { "MSP2_COMMON_SET_RADAR_POS", 4107u, "0x100b", Direction::In, "Sets the position and status information for a \"radar\" Point of Interest (POI). Used for displaying other craft/objects on the OSD map.", FIELDS_153, 8, false },
  { "MSP2_COMMON_SET_RADAR_ITD", 4108u, "0x100c", Direction::In, "Sets radar information to display (likely internal/unused).", nullptr, 0, false },
  { "MSP2_COMMON_SET_MSP_RC_LINK_STATS", 4109u, "0x100d", Direction::In, "Provides RC link statistics (RSSI, LQ) to the FC, typically from an MSP-based RC link (like ExpressLRS). Sent periodically by the RC link.", FIELDS_155, 7, false },
  { "MSP2_COMMON_SET_MSP_RC_INFO", 4110u, "0x100e", Direction::In, "Provides additional RC link information (power levels, band, mode) to the FC from an MSP-based RC link. Sent less frequently than link stats.", FIELDS_156, 5, false },
  { "MSP2_SENSOR_RANGEFINDER", 7937u, "0x1f01", Direction::In, "Provides rangefinder data (distance, quality) from an external MSP-based sensor.", FIELDS_157, 2, false },
  { "MSP2_SENSOR_OPTIC_FLOW", 7938u, "0x1f02", Direction::In, "Provides optical flow data (motion, quality) from an external MSP-based sensor.", FIELDS_158, 3, false },
  { "MSP2_SENSOR_GPS", 7939u, "0x1f03", Direction::In, "Provides detailed GPS data from an external MSP-based GPS module.", FIELDS_159, 23, false },
  { "MSP2_SENSOR_COMPASS", 7940u, "0x1f04", Direction::In, "Provides magnetometer data from an external MSP-based compass module.", FIELDS_160, 5, false },
  { "MSP2_SENSOR_BAROMETER", 7941u, "0x1f05", Direction::In, "Provides barometer data from an external MSP-based barometer module.", FIELDS_161, 4, false },
  { "MSP2_SENSOR_AIRSPEED", 7942u, "0x1f06", Direction::In, "Provides airspeed data from an external MSP-based pitot sensor module.", FIELDS_162, 4, false },
  { "MSP2_SENSOR_HEADTRACKER", 7943u, "0x1f07", Direction::In, "Provides head tracker orientation data.", nullptr, 0, false },
  { "MSP2_INAV_STATUS", 8192u, "0x2000", Direction::Out, "Provides comprehensive flight controller status, extending MSP_STATUS_EX with full arming flags, battery profile, and mixer profile.", FIELDS_164, 8, true },
  { "MSP2_INAV_OPTICAL_FLOW", 8193u, "0x2001", Direction::Out, "Provides data from the optical flow sensor.", FIELDS_165, 5, false },
  { "MSP2_INAV_ANALOG", 8194u, "0x2002", Direction::Out, "Provides detailed analog sensor readings, superseding MSP_ANALOG with higher precision and additional fields.", FIELDS_166, 9, false },
  { "MSP2_INAV_MISC", 8195u, "0x2003", Direction::Out, "Retrieves miscellaneous configuration settings, superseding MSP_MISC with higher precision and capacity fields.", FIELDS_167, 21, false },
  { "MSP2_INAV_SET_MISC", 8196u, "0x2004", Direction::In, "Sets miscellaneous configuration settings, superseding MSP_SET_MISC.", FIELDS_168, 21, false },
  { "MSP2_INAV_BATTERY_CONFIG", 8197u, "0x2005", Direction::Out, "Retrieves the configuration specific to the battery voltage and current sensors and capacity settings for the current battery profile.", FIELDS_169, 13, false },
  { "MSP2_INAV_SET_BATTERY_CONFIG", 8198u, "0x2006", Direction::In, "Sets the battery voltage/current sensor configuration and capacity settings for the current battery profile.", FIELDS_170, 13, false },
  { "MSP2_INAV_RATE_PROFILE", 8199u, "0x2007", Direction::Out, "Retrieves the rates and expos for the current control rate profile, including both stabilized and manual flight modes. Supersedes MSP_RC_TUNING.", FIELDS_171, 14, false },
  { "MSP2_INAV_SET_RATE_PROFILE", 8200u, "0x2008", Direction::In, "Sets the rates and expos for the current control rate profile (stabilized and manual). Supersedes MSP_SET_RC_TUNING.", FIELDS_172, 14, false },
  { "MSP2_INAV_AIR_SPEED", 8201u, "0x2009", Direction::Out, "Retrieves the estimated or measured airspeed.", FIELDS_173, 1, false },
  { "MSP2_INAV_OUTPUT_MAPPING", 8202u, "0x200a", Direction::Out, "Retrieves the output mapping configuration (identifies which timer outputs are used for Motors/Servos). Legacy version sending only 8-bit usage flags.", FIELDS_174, 1, false },
  { "MSP2_INAV_MC_BRAKING", 8203u, "0x200b", Direction::Out, "Retrieves configuration parameters for the multirotor braking mode feature.", FIELDS_175, 8, false },
  { "MSP2_INAV_SET_MC_BRAKING", 8204u, "0x200c", Direction::In, "Sets configuration parameters for the multirotor braking mode feature.", FIELDS_176, 8, false },
  { "MSP2_INAV_OUTPUT_MAPPING_EXT", 8205u, "0x200d", Direction::Out, "Retrieves extended output mapping configuration (timer ID and usage flags). Obsolete, use MSP2_INAV_OUTPUT_MAPPING_EXT2.", FIELDS_177, 2, false },
  { "MSP2_INAV_TIMER_OUTPUT_MODE", 8206u, "0x200e", Direction::InOut, "Get or list the output mode override for hardware timers (e.g., force ONESHOT, DSHOT).", FIELDS_178, 5, false },
  { "MSP2_INAV_SET_TIMER_OUTPUT_MODE", 8207u, "0x200f", Direction::In, "Set the output mode override for a specific hardware timer.", FIELDS_179, 2, false },
  { "MSP2_INAV_MIXER", 8208u, "0x2010", Direction::Out, "Retrieves INAV-specific mixer configuration details.", FIELDS_180, 8, false },
  { "MSP2_INAV_SET_MIXER", 8209u, "0x2011", Direction::In, "Sets INAV-specific mixer configuration details.", FIELDS_181, 8, false },
  { "MSP2_INAV_OSD_LAYOUTS", 8210u, "0x2012", Direction::InOut, "Gets OSD layout information (counts, positions for a specific layout, or position for a specific item).", FIELDS_182, 7, true },
  { "MSP2_INAV_OSD_SET_LAYOUT_ITEM", 8211u, "0x2013", Direction::In, "Sets the position of a single OSD item within a specific layout.", FIELDS_183, 2, false },
  { "MSP2_INAV_OSD_ALARMS", 8212u, "0x2014", Direction::Out, "Retrieves OSD alarm threshold settings.", FIELDS_184, 15, false },
  { "MSP2_INAV_OSD_SET_ALARMS", 8213u, "0x2015", Direction::In, "Sets OSD alarm threshold settings.", FIELDS_185, 13, false },
  { "MSP2_INAV_OSD_PREFERENCES", 8214u, "0x2016", Direction::Out, "Retrieves OSD display preferences (video system, units, styles, etc.).", FIELDS_186, 9, false },
  { "MSP2_INAV_OSD_SET_PREFERENCES", 8215u, "0x2017", Direction::In, "Sets OSD display preferences.", FIELDS_187, 9, false },
  { "MSP2_INAV_SELECT_BATTERY_PROFILE", 8216u, "0x2018", Direction::In, "Selects the active battery profile and saves configuration.", FIELDS_188, 1, false },
  { "MSP2_INAV_DEBUG", 8217u, "0x2019", Direction::Out, "Retrieves values from the firmware's 32-bit debug[] array. Supersedes MSP_DEBUG.", FIELDS_189, 1, true },
  { "MSP2_BLACKBOX_CONFIG", 8218u, "0x201a", Direction::Out, "Retrieves the Blackbox configuration. Supersedes MSP_BLACKBOX_CONFIG.", FIELDS_190, 5, false },
  { "MSP2_SET_BLACKBOX_CONFIG", 8219u, "0x201b", Direction::In, "Sets the Blackbox configuration. Supersedes MSP_SET_BLACKBOX_CONFIG.", FIELDS_191, 4, false },
  { "MSP2_INAV_TEMP_SENSOR_CONFIG", 8220u, "0x201c", Direction::Out, "Retrieves the configuration for all onboard temperature sensors.", FIELDS_192, 6, true },
  { "MSP2_INAV_SET_TEMP_SENSOR_CONFIG", 8221u, "0x201d", Direction::In, "Sets the configuration for all onboard temperature sensors.", FIELDS_193, 6, true },
  { "MSP2_INAV_TEMPERATURES", 8222u, "0x201e", Direction::Out, "Retrieves the current readings from all configured temperature sensors.", FIELDS_194, 1, false },
  { "MSP_SIMULATOR", 8223u, "0x201f", Direction::InOut, "Handles Hardware-in-the-Loop (HITL) simulation data exchange. Receives simulated sensor data and options, sends back control outputs and debug info.", FIELDS_195, 33, true },
  { "MSP2_INAV_SERVO_MIXER", 8224u, "0x2020", Direction::Out, "Retrieves the custom servo mixer rules, including programming framework condition IDs, for primary and secondary mixer profiles. Supersedes MSP_SERVO_MIX_RULES.", FIELDS_196, 10, false },
  { "MSP2_INAV_SET_SERVO_MIXER", 8225u, "0x2021", Direction::In, "Sets a single custom servo mixer rule, including programming framework condition ID. Supersedes MSP_SET_SERVO_MIX_RULE.", FIELDS_197, 6, false },
  { "MSP2_INAV_LOGIC_CONDITIONS", 8226u, "0x2022", Direction::Out, "Retrieves the configuration of all defined Logic Conditions.", FIELDS_198, 8, false },
  { "MSP2_INAV_SET_LOGIC_CONDITIONS", 8227u, "0x2023", Direction::In, "Sets the configuration for a single Logic Condition by its index.", FIELDS_199, 9, false },
  { "MSP2_INAV_GLOBAL_FUNCTIONS", 8228u, "0x2024", Direction::Unknown, "", nullptr, 0, false },
  { "MSP2_INAV_SET_GLOBAL_FUNCTIONS", 8229u, "0x2025", Direction::Unknown, "", nullptr, 0, false },
  { "MSP2_INAV_LOGIC_CONDITIONS_STATUS", 8230u, "0x2026", Direction::Out, "Retrieves the current evaluated status (true/false or numerical value) of all logic conditions.", FIELDS_202, 1, true },
  { "MSP2_INAV_GVAR_STATUS", 8231u, "0x2027", Direction::Out, "Retrieves the current values of all Global Variables (GVARS).", FIELDS_203, 1, true },
  { "MSP2_INAV_PROGRAMMING_PID", 8232u, "0x2028", Direction::Out, "Retrieves the configuration of all Programming PIDs.", FIELDS_204, 9, false },
  { "MSP2_INAV_SET_PROGRAMMING_PID", 8233u, "0x2029", Direction::In, "Sets the configuration for a single Programming PID by its index.", FIELDS_205, 10, false },
  { "MSP2_INAV_PROGRAMMING_PID_STATUS", 8234u, "0x202a", Direction::Out, "Retrieves the current output value of all Programming PIDs.", FIELDS_206, 1, true },
  { "MSP2_PID", 8240u, "0x2030", Direction::Out, "Retrieves the standard PID controller gains (P, I, D, FF) for the current PID profile.", FIELDS_207, 4, false },
  { "MSP2_SET_PID", 8241u, "0x2031", Direction::In, "Sets the standard PID controller gains (P, I, D, FF) for the current PID profile.", FIELDS_208, 4, false },
  { "MSP2_INAV_OPFLOW_CALIBRATION", 8242u, "0x2032", Direction::In, "Starts the optical flow sensor calibration procedure.", nullptr, 0, false },
  { "MSP2_INAV_FWUPDT_PREPARE", 8243u, "0x2033", Direction::In, "Prepares the flight controller to receive a firmware update via MSP.", FIELDS_210, 1, false },
  { "MSP2_INAV_FWUPDT_STORE", 8244u, "0x2034", Direction::In, "Stores a chunk of firmware data received via MSP.", FIELDS_211, 1, true },
  { "MSP2_INAV_FWUPDT_EXEC", 8245u, "0x2035", Direction::In, "Executes the firmware update process (flashes the stored firmware and reboots).", FIELDS_212, 1, false },
  { "MSP2_INAV_FWUPDT_ROLLBACK_PREPARE", 8246u, "0x2036", Direction::In, "Prepares the flight controller to perform a firmware rollback to the previously stored version.", nullptr, 0, false },
  { "MSP2_INAV_FWUPDT_ROLLBACK_EXEC", 8247u, "0x2037", Direction::In, "Executes the firmware rollback process (flashes the stored backup firmware and reboots).", nullptr, 0, false },
  { "MSP2_INAV_SAFEHOME", 8248u, "0x2038", Direction::InOut, "Get or Set configuration for a specific Safe Home location.", FIELDS_215, 5, false },
  { "MSP2_INAV_SET_SAFEHOME", 8249u, "0x2039", Direction::In, "Sets the configuration for a specific Safe Home location.", FIELDS_216, 4, false },
  { "MSP2_INAV_MISC2", 8250u, "0x203a", Direction::Out, "Retrieves miscellaneous runtime information including timers and throttle status.", FIELDS_217, 4, false },
  { "MSP2_INAV_LOGIC_CONDITIONS_SINGLE", 8251u, "0x203b", Direction::InOut, "Gets the configuration for a single Logic Condition by its index.", FIELDS_218, 9, false },
  { "MSP2_INAV_ESC_RPM", 8256u, "0x2040", Direction::Out, "Retrieves the RPM reported by each ESC via telemetry.", FIELDS_219, 1, false },
  { "MSP2_INAV_ESC_TELEM", 8257u, "0x2041", Direction::Out, "Retrieves the full telemetry data structure reported by each ESC.", FIELDS_220, 2, true },
  { "MSP2_INAV_LED_STRIP_CONFIG_EX", 8264u, "0x2048", Direction::Out, "Retrieves the full configuration for each LED on the strip using the ledConfig_t structure. Supersedes MSP_LED_STRIP_CONFIG.", FIELDS_221, 1, true },
  { "MSP2_INAV_SET_LED_STRIP_CONFIG_EX", 8265u, "0x2049", Direction::In, "Sets the configuration for a single LED on the strip using the ledConfig_t structure. Supersedes MSP_SET_LED_STRIP_CONFIG.", FIELDS_222, 2, true },
  { "MSP2_INAV_FW_APPROACH", 8266u, "0x204a", Direction::InOut, "Get or Set configuration for a specific Fixed Wing Autoland approach.", FIELDS_223, 8, false },
  { "MSP2_INAV_SET_FW_APPROACH", 8267u, "0x204b", Direction::In, "Sets the configuration for a specific Fixed Wing Autoland approach.", FIELDS_224, 7, false },
  { "MSP2_INAV_GPS_UBLOX_COMMAND", 8272u, "0x2050", Direction::In, "Sends a raw command directly to a U-Blox GPS module connected to the FC.", FIELDS_225, 1, true },
  { "MSP2_INAV_RATE_DYNAMICS", 8288u, "0x2060", Direction::Out, "Retrieves Rate Dynamics configuration parameters for the current control rate profile.", FIELDS_226, 6, false },
  { "MSP2_INAV_SET_RATE_DYNAMICS", 8289u, "0x2061", Direction::In, "Sets Rate Dynamics configuration parameters for the current control rate profile.", FIELDS_227, 6, false },
  { "MSP2_INAV_EZ_TUNE", 8304u, "0x2070", Direction::Out, "Retrieves the current EZ-Tune parameters.", FIELDS_228, 10, false },
  { "MSP2_INAV_EZ_TUNE_SET", 8305u, "0x2071", Direction::In, "Sets the EZ-Tune parameters and triggers an update.", FIELDS_229, 10, false },
  { "MSP2_INAV_SELECT_MIXER_PROFILE", 8320u, "0x2080", Direction::In, "Selects the active mixer profile and saves configuration.", FIELDS_230, 1, false },
  { "MSP2_ADSB_VEHICLE_LIST", 8336u, "0x2090", Direction::Out, "Retrieves the list of currently tracked ADSB (Automatic Dependent Surveillance–Broadcast) vehicles.", FIELDS_231, 14, true },
  { "MSP2_INAV_CUSTOM_OSD_ELEMENTS", 8448u, "0x2100", Direction::Out, "Retrieves counts related to custom OSD elements defined by the programming framework.", FIELDS_232, 3, false },
  { "MSP2_INAV_CUSTOM_OSD_ELEMENT", 8449u, "0x2101", Direction::InOut, "Gets the configuration of a single custom OSD element defined by the programming framework.", FIELDS_233, 9, true },
  { "MSP2_INAV_SET_CUSTOM_OSD_ELEMENTS", 8450u, "0x2102", Direction::In, "Sets the configuration of a single custom OSD element defined by the programming framework.", FIELDS_234, 9, true },
  { "MSP2_INAV_OUTPUT_MAPPING_EXT2", 8461u, "0x210d", Direction::Out, "Retrieves the full extended output mapping configuration (timer ID, full 32-bit usage flags, and pin label). Supersedes MSP2_INAV_OUTPUT_MAPPING_EXT.", FIELDS_235, 3, false },
  { "MSP2_INAV_SERVO_CONFIG", 8704u, "0x2200", Direction::Out, "Retrieves the configuration parameters for all supported servos (min, max, middle, rate). Supersedes MSP_SERVO_CONFIGURATIONS.", FIELDS_236, 4, false },
  { "MSP2_INAV_SET_SERVO_CONFIG", 8705u, "0x2201", Direction::In, "Sets the configuration parameters for a single servo. Supersedes MSP_SET_SERVO_CONFIGURATION.", FIELDS_237, 5, false },
  { "MSP2_INAV_GEOZONE", 8720u, "0x2210", Direction::InOut, "Get configuration for a specific Geozone.", FIELDS_238, 9, false },
  { "MSP2_INAV_SET_GEOZONE", 8721u, "0x2211", Direction::In, "Sets the main configuration for a specific Geozone (type, shape, altitude, action). This command resets (clears) all vertices associated with the zone.", FIELDS_239, 8, false },
  { "MSP2_INAV_GEOZONE_VERTEX", 8722u, "0x2212", Direction::InOut, "Get a specific vertex (or center+radius for circular zones) of a Geozone.", FIELDS_240, 11, false },
  { "MSP2_INAV_SET_GEOZONE_VERTEX", 8723u, "0x2213", Direction::In, "Sets a specific vertex (or center+radius for circular zones) for a Geozone.", FIELDS_241, 9, false },
  { "MSP2_BETAFLIGHT_BIND", 12288u, "0x3000", Direction::In, "Initiates the receiver binding procedure for supported serial protocols (CRSF, SRXL2).", nullptr, 0, false },
}; inline constexpr size_t REGISTRY_COUNT = sizeof(REGISTRY)/sizeof(REGISTRY[0]);
} // namespace msp
