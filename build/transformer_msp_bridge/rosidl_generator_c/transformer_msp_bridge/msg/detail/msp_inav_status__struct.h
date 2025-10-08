// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from transformer_msp_bridge:msg/MspInavStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "transformer_msp_bridge/msg/msp_inav_status.h"


#ifndef TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__STRUCT_H_
#define TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'active_modes'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/MspInavStatus in the package transformer_msp_bridge.
/**
  * MSP2_INAV_STATUS decoded status message
  * cycle time in microseconds
 */
typedef struct transformer_msp_bridge__msg__MspInavStatus
{
  uint16_t cycle_time_us;
  /// accumulated I2C errors
  uint16_t i2c_errors;
  /// sensor status bitmask (firmware-defined)
  uint16_t sensor_status;
  /// average CPU load percentage (0-100)
  uint16_t cpu_load_percent;
  /// profile indices
  uint8_t config_profile;
  uint8_t battery_profile;
  uint8_t mixer_profile;
  /// full 32-bit arming flags bitmask
  uint32_t arming_flags;
  /// raw active modes bitmask bytes
  rosidl_runtime_c__uint8__Sequence active_modes;
} transformer_msp_bridge__msg__MspInavStatus;

// Struct for a sequence of transformer_msp_bridge__msg__MspInavStatus.
typedef struct transformer_msp_bridge__msg__MspInavStatus__Sequence
{
  transformer_msp_bridge__msg__MspInavStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} transformer_msp_bridge__msg__MspInavStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__STRUCT_H_
