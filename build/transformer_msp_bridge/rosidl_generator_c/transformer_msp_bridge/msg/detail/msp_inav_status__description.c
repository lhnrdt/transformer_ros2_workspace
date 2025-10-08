// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from transformer_msp_bridge:msg/MspInavStatus.idl
// generated code does not contain a copyright notice

#include "transformer_msp_bridge/msg/detail/msp_inav_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_transformer_msp_bridge
const rosidl_type_hash_t *
transformer_msp_bridge__msg__MspInavStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xcb, 0xec, 0xd6, 0x43, 0x2a, 0x01, 0xcb, 0x1d,
      0x44, 0xcd, 0x5a, 0xf3, 0x59, 0xc5, 0x4d, 0x75,
      0x3d, 0x61, 0x4d, 0xba, 0x17, 0x77, 0x15, 0xd1,
      0x6e, 0x78, 0x44, 0xf4, 0x68, 0xae, 0x1f, 0xd1,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char transformer_msp_bridge__msg__MspInavStatus__TYPE_NAME[] = "transformer_msp_bridge/msg/MspInavStatus";

// Define type names, field names, and default values
static char transformer_msp_bridge__msg__MspInavStatus__FIELD_NAME__cycle_time_us[] = "cycle_time_us";
static char transformer_msp_bridge__msg__MspInavStatus__FIELD_NAME__i2c_errors[] = "i2c_errors";
static char transformer_msp_bridge__msg__MspInavStatus__FIELD_NAME__sensor_status[] = "sensor_status";
static char transformer_msp_bridge__msg__MspInavStatus__FIELD_NAME__cpu_load_percent[] = "cpu_load_percent";
static char transformer_msp_bridge__msg__MspInavStatus__FIELD_NAME__config_profile[] = "config_profile";
static char transformer_msp_bridge__msg__MspInavStatus__FIELD_NAME__battery_profile[] = "battery_profile";
static char transformer_msp_bridge__msg__MspInavStatus__FIELD_NAME__mixer_profile[] = "mixer_profile";
static char transformer_msp_bridge__msg__MspInavStatus__FIELD_NAME__arming_flags[] = "arming_flags";
static char transformer_msp_bridge__msg__MspInavStatus__FIELD_NAME__active_modes[] = "active_modes";

static rosidl_runtime_c__type_description__Field transformer_msp_bridge__msg__MspInavStatus__FIELDS[] = {
  {
    {transformer_msp_bridge__msg__MspInavStatus__FIELD_NAME__cycle_time_us, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {transformer_msp_bridge__msg__MspInavStatus__FIELD_NAME__i2c_errors, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {transformer_msp_bridge__msg__MspInavStatus__FIELD_NAME__sensor_status, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {transformer_msp_bridge__msg__MspInavStatus__FIELD_NAME__cpu_load_percent, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {transformer_msp_bridge__msg__MspInavStatus__FIELD_NAME__config_profile, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {transformer_msp_bridge__msg__MspInavStatus__FIELD_NAME__battery_profile, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {transformer_msp_bridge__msg__MspInavStatus__FIELD_NAME__mixer_profile, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {transformer_msp_bridge__msg__MspInavStatus__FIELD_NAME__arming_flags, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {transformer_msp_bridge__msg__MspInavStatus__FIELD_NAME__active_modes, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
transformer_msp_bridge__msg__MspInavStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {transformer_msp_bridge__msg__MspInavStatus__TYPE_NAME, 40, 40},
      {transformer_msp_bridge__msg__MspInavStatus__FIELDS, 9, 9},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# MSP2_INAV_STATUS decoded status message\n"
  "# cycle time in microseconds\n"
  "uint16 cycle_time_us\n"
  "# accumulated I2C errors\n"
  "uint16 i2c_errors\n"
  "# sensor status bitmask (firmware-defined)\n"
  "uint16 sensor_status\n"
  "# average CPU load percentage (0-100)\n"
  "uint16 cpu_load_percent\n"
  "# profile indices\n"
  "uint8 config_profile\n"
  "uint8 battery_profile\n"
  "uint8 mixer_profile\n"
  "# full 32-bit arming flags bitmask\n"
  "uint32 arming_flags\n"
  "# raw active modes bitmask bytes\n"
  "uint8[] active_modes";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
transformer_msp_bridge__msg__MspInavStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {transformer_msp_bridge__msg__MspInavStatus__TYPE_NAME, 40, 40},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 451, 451},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
transformer_msp_bridge__msg__MspInavStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *transformer_msp_bridge__msg__MspInavStatus__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
