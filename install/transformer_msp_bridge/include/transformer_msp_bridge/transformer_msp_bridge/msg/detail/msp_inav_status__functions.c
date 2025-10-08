// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from transformer_msp_bridge:msg/MspInavStatus.idl
// generated code does not contain a copyright notice
#include "transformer_msp_bridge/msg/detail/msp_inav_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `active_modes`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
transformer_msp_bridge__msg__MspInavStatus__init(transformer_msp_bridge__msg__MspInavStatus * msg)
{
  if (!msg) {
    return false;
  }
  // cycle_time_us
  // i2c_errors
  // sensor_status
  // cpu_load_percent
  // config_profile
  // battery_profile
  // mixer_profile
  // arming_flags
  // active_modes
  if (!rosidl_runtime_c__uint8__Sequence__init(&msg->active_modes, 0)) {
    transformer_msp_bridge__msg__MspInavStatus__fini(msg);
    return false;
  }
  return true;
}

void
transformer_msp_bridge__msg__MspInavStatus__fini(transformer_msp_bridge__msg__MspInavStatus * msg)
{
  if (!msg) {
    return;
  }
  // cycle_time_us
  // i2c_errors
  // sensor_status
  // cpu_load_percent
  // config_profile
  // battery_profile
  // mixer_profile
  // arming_flags
  // active_modes
  rosidl_runtime_c__uint8__Sequence__fini(&msg->active_modes);
}

bool
transformer_msp_bridge__msg__MspInavStatus__are_equal(const transformer_msp_bridge__msg__MspInavStatus * lhs, const transformer_msp_bridge__msg__MspInavStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // cycle_time_us
  if (lhs->cycle_time_us != rhs->cycle_time_us) {
    return false;
  }
  // i2c_errors
  if (lhs->i2c_errors != rhs->i2c_errors) {
    return false;
  }
  // sensor_status
  if (lhs->sensor_status != rhs->sensor_status) {
    return false;
  }
  // cpu_load_percent
  if (lhs->cpu_load_percent != rhs->cpu_load_percent) {
    return false;
  }
  // config_profile
  if (lhs->config_profile != rhs->config_profile) {
    return false;
  }
  // battery_profile
  if (lhs->battery_profile != rhs->battery_profile) {
    return false;
  }
  // mixer_profile
  if (lhs->mixer_profile != rhs->mixer_profile) {
    return false;
  }
  // arming_flags
  if (lhs->arming_flags != rhs->arming_flags) {
    return false;
  }
  // active_modes
  if (!rosidl_runtime_c__uint8__Sequence__are_equal(
      &(lhs->active_modes), &(rhs->active_modes)))
  {
    return false;
  }
  return true;
}

bool
transformer_msp_bridge__msg__MspInavStatus__copy(
  const transformer_msp_bridge__msg__MspInavStatus * input,
  transformer_msp_bridge__msg__MspInavStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // cycle_time_us
  output->cycle_time_us = input->cycle_time_us;
  // i2c_errors
  output->i2c_errors = input->i2c_errors;
  // sensor_status
  output->sensor_status = input->sensor_status;
  // cpu_load_percent
  output->cpu_load_percent = input->cpu_load_percent;
  // config_profile
  output->config_profile = input->config_profile;
  // battery_profile
  output->battery_profile = input->battery_profile;
  // mixer_profile
  output->mixer_profile = input->mixer_profile;
  // arming_flags
  output->arming_flags = input->arming_flags;
  // active_modes
  if (!rosidl_runtime_c__uint8__Sequence__copy(
      &(input->active_modes), &(output->active_modes)))
  {
    return false;
  }
  return true;
}

transformer_msp_bridge__msg__MspInavStatus *
transformer_msp_bridge__msg__MspInavStatus__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_msp_bridge__msg__MspInavStatus * msg = (transformer_msp_bridge__msg__MspInavStatus *)allocator.allocate(sizeof(transformer_msp_bridge__msg__MspInavStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(transformer_msp_bridge__msg__MspInavStatus));
  bool success = transformer_msp_bridge__msg__MspInavStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
transformer_msp_bridge__msg__MspInavStatus__destroy(transformer_msp_bridge__msg__MspInavStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    transformer_msp_bridge__msg__MspInavStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
transformer_msp_bridge__msg__MspInavStatus__Sequence__init(transformer_msp_bridge__msg__MspInavStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_msp_bridge__msg__MspInavStatus * data = NULL;

  if (size) {
    data = (transformer_msp_bridge__msg__MspInavStatus *)allocator.zero_allocate(size, sizeof(transformer_msp_bridge__msg__MspInavStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = transformer_msp_bridge__msg__MspInavStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        transformer_msp_bridge__msg__MspInavStatus__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
transformer_msp_bridge__msg__MspInavStatus__Sequence__fini(transformer_msp_bridge__msg__MspInavStatus__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      transformer_msp_bridge__msg__MspInavStatus__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

transformer_msp_bridge__msg__MspInavStatus__Sequence *
transformer_msp_bridge__msg__MspInavStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_msp_bridge__msg__MspInavStatus__Sequence * array = (transformer_msp_bridge__msg__MspInavStatus__Sequence *)allocator.allocate(sizeof(transformer_msp_bridge__msg__MspInavStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = transformer_msp_bridge__msg__MspInavStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
transformer_msp_bridge__msg__MspInavStatus__Sequence__destroy(transformer_msp_bridge__msg__MspInavStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    transformer_msp_bridge__msg__MspInavStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
transformer_msp_bridge__msg__MspInavStatus__Sequence__are_equal(const transformer_msp_bridge__msg__MspInavStatus__Sequence * lhs, const transformer_msp_bridge__msg__MspInavStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!transformer_msp_bridge__msg__MspInavStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
transformer_msp_bridge__msg__MspInavStatus__Sequence__copy(
  const transformer_msp_bridge__msg__MspInavStatus__Sequence * input,
  transformer_msp_bridge__msg__MspInavStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(transformer_msp_bridge__msg__MspInavStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    transformer_msp_bridge__msg__MspInavStatus * data =
      (transformer_msp_bridge__msg__MspInavStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!transformer_msp_bridge__msg__MspInavStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          transformer_msp_bridge__msg__MspInavStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!transformer_msp_bridge__msg__MspInavStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
