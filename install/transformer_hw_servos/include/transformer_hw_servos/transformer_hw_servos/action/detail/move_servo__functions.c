// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from transformer_hw_servos:action/MoveServo.idl
// generated code does not contain a copyright notice
#include "transformer_hw_servos/action/detail/move_servo__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `channels`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
transformer_hw_servos__action__MoveServo_Goal__init(transformer_hw_servos__action__MoveServo_Goal * msg)
{
  if (!msg) {
    return false;
  }
  // channels
  if (!rosidl_runtime_c__int32__Sequence__init(&msg->channels, 0)) {
    transformer_hw_servos__action__MoveServo_Goal__fini(msg);
    return false;
  }
  // pulse_us
  // speed_us_per_s
  // use_trapezoid
  // accel_us_per_s2
  return true;
}

void
transformer_hw_servos__action__MoveServo_Goal__fini(transformer_hw_servos__action__MoveServo_Goal * msg)
{
  if (!msg) {
    return;
  }
  // channels
  rosidl_runtime_c__int32__Sequence__fini(&msg->channels);
  // pulse_us
  // speed_us_per_s
  // use_trapezoid
  // accel_us_per_s2
}

bool
transformer_hw_servos__action__MoveServo_Goal__are_equal(const transformer_hw_servos__action__MoveServo_Goal * lhs, const transformer_hw_servos__action__MoveServo_Goal * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // channels
  if (!rosidl_runtime_c__int32__Sequence__are_equal(
      &(lhs->channels), &(rhs->channels)))
  {
    return false;
  }
  // pulse_us
  if (lhs->pulse_us != rhs->pulse_us) {
    return false;
  }
  // speed_us_per_s
  if (lhs->speed_us_per_s != rhs->speed_us_per_s) {
    return false;
  }
  // use_trapezoid
  if (lhs->use_trapezoid != rhs->use_trapezoid) {
    return false;
  }
  // accel_us_per_s2
  if (lhs->accel_us_per_s2 != rhs->accel_us_per_s2) {
    return false;
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_Goal__copy(
  const transformer_hw_servos__action__MoveServo_Goal * input,
  transformer_hw_servos__action__MoveServo_Goal * output)
{
  if (!input || !output) {
    return false;
  }
  // channels
  if (!rosidl_runtime_c__int32__Sequence__copy(
      &(input->channels), &(output->channels)))
  {
    return false;
  }
  // pulse_us
  output->pulse_us = input->pulse_us;
  // speed_us_per_s
  output->speed_us_per_s = input->speed_us_per_s;
  // use_trapezoid
  output->use_trapezoid = input->use_trapezoid;
  // accel_us_per_s2
  output->accel_us_per_s2 = input->accel_us_per_s2;
  return true;
}

transformer_hw_servos__action__MoveServo_Goal *
transformer_hw_servos__action__MoveServo_Goal__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_Goal * msg = (transformer_hw_servos__action__MoveServo_Goal *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_Goal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(transformer_hw_servos__action__MoveServo_Goal));
  bool success = transformer_hw_servos__action__MoveServo_Goal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
transformer_hw_servos__action__MoveServo_Goal__destroy(transformer_hw_servos__action__MoveServo_Goal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    transformer_hw_servos__action__MoveServo_Goal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
transformer_hw_servos__action__MoveServo_Goal__Sequence__init(transformer_hw_servos__action__MoveServo_Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_Goal * data = NULL;

  if (size) {
    data = (transformer_hw_servos__action__MoveServo_Goal *)allocator.zero_allocate(size, sizeof(transformer_hw_servos__action__MoveServo_Goal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = transformer_hw_servos__action__MoveServo_Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        transformer_hw_servos__action__MoveServo_Goal__fini(&data[i - 1]);
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
transformer_hw_servos__action__MoveServo_Goal__Sequence__fini(transformer_hw_servos__action__MoveServo_Goal__Sequence * array)
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
      transformer_hw_servos__action__MoveServo_Goal__fini(&array->data[i]);
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

transformer_hw_servos__action__MoveServo_Goal__Sequence *
transformer_hw_servos__action__MoveServo_Goal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_Goal__Sequence * array = (transformer_hw_servos__action__MoveServo_Goal__Sequence *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_Goal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = transformer_hw_servos__action__MoveServo_Goal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
transformer_hw_servos__action__MoveServo_Goal__Sequence__destroy(transformer_hw_servos__action__MoveServo_Goal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    transformer_hw_servos__action__MoveServo_Goal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
transformer_hw_servos__action__MoveServo_Goal__Sequence__are_equal(const transformer_hw_servos__action__MoveServo_Goal__Sequence * lhs, const transformer_hw_servos__action__MoveServo_Goal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_Goal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_Goal__Sequence__copy(
  const transformer_hw_servos__action__MoveServo_Goal__Sequence * input,
  transformer_hw_servos__action__MoveServo_Goal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(transformer_hw_servos__action__MoveServo_Goal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    transformer_hw_servos__action__MoveServo_Goal * data =
      (transformer_hw_servos__action__MoveServo_Goal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!transformer_hw_servos__action__MoveServo_Goal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          transformer_hw_servos__action__MoveServo_Goal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_Goal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"
// Member `final_pulses_us`
// already included above
// #include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
transformer_hw_servos__action__MoveServo_Result__init(transformer_hw_servos__action__MoveServo_Result * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    transformer_hw_servos__action__MoveServo_Result__fini(msg);
    return false;
  }
  // final_pulses_us
  if (!rosidl_runtime_c__int32__Sequence__init(&msg->final_pulses_us, 0)) {
    transformer_hw_servos__action__MoveServo_Result__fini(msg);
    return false;
  }
  // total_estimated_duration_s
  return true;
}

void
transformer_hw_servos__action__MoveServo_Result__fini(transformer_hw_servos__action__MoveServo_Result * msg)
{
  if (!msg) {
    return;
  }
  // success
  // message
  rosidl_runtime_c__String__fini(&msg->message);
  // final_pulses_us
  rosidl_runtime_c__int32__Sequence__fini(&msg->final_pulses_us);
  // total_estimated_duration_s
}

bool
transformer_hw_servos__action__MoveServo_Result__are_equal(const transformer_hw_servos__action__MoveServo_Result * lhs, const transformer_hw_servos__action__MoveServo_Result * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  // final_pulses_us
  if (!rosidl_runtime_c__int32__Sequence__are_equal(
      &(lhs->final_pulses_us), &(rhs->final_pulses_us)))
  {
    return false;
  }
  // total_estimated_duration_s
  if (lhs->total_estimated_duration_s != rhs->total_estimated_duration_s) {
    return false;
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_Result__copy(
  const transformer_hw_servos__action__MoveServo_Result * input,
  transformer_hw_servos__action__MoveServo_Result * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  // final_pulses_us
  if (!rosidl_runtime_c__int32__Sequence__copy(
      &(input->final_pulses_us), &(output->final_pulses_us)))
  {
    return false;
  }
  // total_estimated_duration_s
  output->total_estimated_duration_s = input->total_estimated_duration_s;
  return true;
}

transformer_hw_servos__action__MoveServo_Result *
transformer_hw_servos__action__MoveServo_Result__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_Result * msg = (transformer_hw_servos__action__MoveServo_Result *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_Result), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(transformer_hw_servos__action__MoveServo_Result));
  bool success = transformer_hw_servos__action__MoveServo_Result__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
transformer_hw_servos__action__MoveServo_Result__destroy(transformer_hw_servos__action__MoveServo_Result * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    transformer_hw_servos__action__MoveServo_Result__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
transformer_hw_servos__action__MoveServo_Result__Sequence__init(transformer_hw_servos__action__MoveServo_Result__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_Result * data = NULL;

  if (size) {
    data = (transformer_hw_servos__action__MoveServo_Result *)allocator.zero_allocate(size, sizeof(transformer_hw_servos__action__MoveServo_Result), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = transformer_hw_servos__action__MoveServo_Result__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        transformer_hw_servos__action__MoveServo_Result__fini(&data[i - 1]);
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
transformer_hw_servos__action__MoveServo_Result__Sequence__fini(transformer_hw_servos__action__MoveServo_Result__Sequence * array)
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
      transformer_hw_servos__action__MoveServo_Result__fini(&array->data[i]);
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

transformer_hw_servos__action__MoveServo_Result__Sequence *
transformer_hw_servos__action__MoveServo_Result__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_Result__Sequence * array = (transformer_hw_servos__action__MoveServo_Result__Sequence *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_Result__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = transformer_hw_servos__action__MoveServo_Result__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
transformer_hw_servos__action__MoveServo_Result__Sequence__destroy(transformer_hw_servos__action__MoveServo_Result__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    transformer_hw_servos__action__MoveServo_Result__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
transformer_hw_servos__action__MoveServo_Result__Sequence__are_equal(const transformer_hw_servos__action__MoveServo_Result__Sequence * lhs, const transformer_hw_servos__action__MoveServo_Result__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_Result__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_Result__Sequence__copy(
  const transformer_hw_servos__action__MoveServo_Result__Sequence * input,
  transformer_hw_servos__action__MoveServo_Result__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(transformer_hw_servos__action__MoveServo_Result);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    transformer_hw_servos__action__MoveServo_Result * data =
      (transformer_hw_servos__action__MoveServo_Result *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!transformer_hw_servos__action__MoveServo_Result__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          transformer_hw_servos__action__MoveServo_Result__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_Result__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `current_pulses_us`
// already included above
// #include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `phase`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
transformer_hw_servos__action__MoveServo_Feedback__init(transformer_hw_servos__action__MoveServo_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // current_pulses_us
  if (!rosidl_runtime_c__int32__Sequence__init(&msg->current_pulses_us, 0)) {
    transformer_hw_servos__action__MoveServo_Feedback__fini(msg);
    return false;
  }
  // progress
  // estimated_remaining_s
  // phase
  if (!rosidl_runtime_c__String__init(&msg->phase)) {
    transformer_hw_servos__action__MoveServo_Feedback__fini(msg);
    return false;
  }
  return true;
}

void
transformer_hw_servos__action__MoveServo_Feedback__fini(transformer_hw_servos__action__MoveServo_Feedback * msg)
{
  if (!msg) {
    return;
  }
  // current_pulses_us
  rosidl_runtime_c__int32__Sequence__fini(&msg->current_pulses_us);
  // progress
  // estimated_remaining_s
  // phase
  rosidl_runtime_c__String__fini(&msg->phase);
}

bool
transformer_hw_servos__action__MoveServo_Feedback__are_equal(const transformer_hw_servos__action__MoveServo_Feedback * lhs, const transformer_hw_servos__action__MoveServo_Feedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // current_pulses_us
  if (!rosidl_runtime_c__int32__Sequence__are_equal(
      &(lhs->current_pulses_us), &(rhs->current_pulses_us)))
  {
    return false;
  }
  // progress
  if (lhs->progress != rhs->progress) {
    return false;
  }
  // estimated_remaining_s
  if (lhs->estimated_remaining_s != rhs->estimated_remaining_s) {
    return false;
  }
  // phase
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->phase), &(rhs->phase)))
  {
    return false;
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_Feedback__copy(
  const transformer_hw_servos__action__MoveServo_Feedback * input,
  transformer_hw_servos__action__MoveServo_Feedback * output)
{
  if (!input || !output) {
    return false;
  }
  // current_pulses_us
  if (!rosidl_runtime_c__int32__Sequence__copy(
      &(input->current_pulses_us), &(output->current_pulses_us)))
  {
    return false;
  }
  // progress
  output->progress = input->progress;
  // estimated_remaining_s
  output->estimated_remaining_s = input->estimated_remaining_s;
  // phase
  if (!rosidl_runtime_c__String__copy(
      &(input->phase), &(output->phase)))
  {
    return false;
  }
  return true;
}

transformer_hw_servos__action__MoveServo_Feedback *
transformer_hw_servos__action__MoveServo_Feedback__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_Feedback * msg = (transformer_hw_servos__action__MoveServo_Feedback *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_Feedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(transformer_hw_servos__action__MoveServo_Feedback));
  bool success = transformer_hw_servos__action__MoveServo_Feedback__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
transformer_hw_servos__action__MoveServo_Feedback__destroy(transformer_hw_servos__action__MoveServo_Feedback * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    transformer_hw_servos__action__MoveServo_Feedback__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
transformer_hw_servos__action__MoveServo_Feedback__Sequence__init(transformer_hw_servos__action__MoveServo_Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_Feedback * data = NULL;

  if (size) {
    data = (transformer_hw_servos__action__MoveServo_Feedback *)allocator.zero_allocate(size, sizeof(transformer_hw_servos__action__MoveServo_Feedback), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = transformer_hw_servos__action__MoveServo_Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        transformer_hw_servos__action__MoveServo_Feedback__fini(&data[i - 1]);
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
transformer_hw_servos__action__MoveServo_Feedback__Sequence__fini(transformer_hw_servos__action__MoveServo_Feedback__Sequence * array)
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
      transformer_hw_servos__action__MoveServo_Feedback__fini(&array->data[i]);
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

transformer_hw_servos__action__MoveServo_Feedback__Sequence *
transformer_hw_servos__action__MoveServo_Feedback__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_Feedback__Sequence * array = (transformer_hw_servos__action__MoveServo_Feedback__Sequence *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_Feedback__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = transformer_hw_servos__action__MoveServo_Feedback__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
transformer_hw_servos__action__MoveServo_Feedback__Sequence__destroy(transformer_hw_servos__action__MoveServo_Feedback__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    transformer_hw_servos__action__MoveServo_Feedback__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
transformer_hw_servos__action__MoveServo_Feedback__Sequence__are_equal(const transformer_hw_servos__action__MoveServo_Feedback__Sequence * lhs, const transformer_hw_servos__action__MoveServo_Feedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_Feedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_Feedback__Sequence__copy(
  const transformer_hw_servos__action__MoveServo_Feedback__Sequence * input,
  transformer_hw_servos__action__MoveServo_Feedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(transformer_hw_servos__action__MoveServo_Feedback);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    transformer_hw_servos__action__MoveServo_Feedback * data =
      (transformer_hw_servos__action__MoveServo_Feedback *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!transformer_hw_servos__action__MoveServo_Feedback__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          transformer_hw_servos__action__MoveServo_Feedback__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_Feedback__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `goal`
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"

bool
transformer_hw_servos__action__MoveServo_SendGoal_Request__init(transformer_hw_servos__action__MoveServo_SendGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    transformer_hw_servos__action__MoveServo_SendGoal_Request__fini(msg);
    return false;
  }
  // goal
  if (!transformer_hw_servos__action__MoveServo_Goal__init(&msg->goal)) {
    transformer_hw_servos__action__MoveServo_SendGoal_Request__fini(msg);
    return false;
  }
  return true;
}

void
transformer_hw_servos__action__MoveServo_SendGoal_Request__fini(transformer_hw_servos__action__MoveServo_SendGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // goal
  transformer_hw_servos__action__MoveServo_Goal__fini(&msg->goal);
}

bool
transformer_hw_servos__action__MoveServo_SendGoal_Request__are_equal(const transformer_hw_servos__action__MoveServo_SendGoal_Request * lhs, const transformer_hw_servos__action__MoveServo_SendGoal_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // goal
  if (!transformer_hw_servos__action__MoveServo_Goal__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_SendGoal_Request__copy(
  const transformer_hw_servos__action__MoveServo_SendGoal_Request * input,
  transformer_hw_servos__action__MoveServo_SendGoal_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // goal
  if (!transformer_hw_servos__action__MoveServo_Goal__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  return true;
}

transformer_hw_servos__action__MoveServo_SendGoal_Request *
transformer_hw_servos__action__MoveServo_SendGoal_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_SendGoal_Request * msg = (transformer_hw_servos__action__MoveServo_SendGoal_Request *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_SendGoal_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(transformer_hw_servos__action__MoveServo_SendGoal_Request));
  bool success = transformer_hw_servos__action__MoveServo_SendGoal_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
transformer_hw_servos__action__MoveServo_SendGoal_Request__destroy(transformer_hw_servos__action__MoveServo_SendGoal_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    transformer_hw_servos__action__MoveServo_SendGoal_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence__init(transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_SendGoal_Request * data = NULL;

  if (size) {
    data = (transformer_hw_servos__action__MoveServo_SendGoal_Request *)allocator.zero_allocate(size, sizeof(transformer_hw_servos__action__MoveServo_SendGoal_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = transformer_hw_servos__action__MoveServo_SendGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        transformer_hw_servos__action__MoveServo_SendGoal_Request__fini(&data[i - 1]);
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
transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence__fini(transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence * array)
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
      transformer_hw_servos__action__MoveServo_SendGoal_Request__fini(&array->data[i]);
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

transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence *
transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence * array = (transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence__destroy(transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence__are_equal(const transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence * lhs, const transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_SendGoal_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence__copy(
  const transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence * input,
  transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(transformer_hw_servos__action__MoveServo_SendGoal_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    transformer_hw_servos__action__MoveServo_SendGoal_Request * data =
      (transformer_hw_servos__action__MoveServo_SendGoal_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!transformer_hw_servos__action__MoveServo_SendGoal_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          transformer_hw_servos__action__MoveServo_SendGoal_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_SendGoal_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
transformer_hw_servos__action__MoveServo_SendGoal_Response__init(transformer_hw_servos__action__MoveServo_SendGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    transformer_hw_servos__action__MoveServo_SendGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
transformer_hw_servos__action__MoveServo_SendGoal_Response__fini(transformer_hw_servos__action__MoveServo_SendGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
transformer_hw_servos__action__MoveServo_SendGoal_Response__are_equal(const transformer_hw_servos__action__MoveServo_SendGoal_Response * lhs, const transformer_hw_servos__action__MoveServo_SendGoal_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accepted
  if (lhs->accepted != rhs->accepted) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_SendGoal_Response__copy(
  const transformer_hw_servos__action__MoveServo_SendGoal_Response * input,
  transformer_hw_servos__action__MoveServo_SendGoal_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // accepted
  output->accepted = input->accepted;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

transformer_hw_servos__action__MoveServo_SendGoal_Response *
transformer_hw_servos__action__MoveServo_SendGoal_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_SendGoal_Response * msg = (transformer_hw_servos__action__MoveServo_SendGoal_Response *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_SendGoal_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(transformer_hw_servos__action__MoveServo_SendGoal_Response));
  bool success = transformer_hw_servos__action__MoveServo_SendGoal_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
transformer_hw_servos__action__MoveServo_SendGoal_Response__destroy(transformer_hw_servos__action__MoveServo_SendGoal_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    transformer_hw_servos__action__MoveServo_SendGoal_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence__init(transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_SendGoal_Response * data = NULL;

  if (size) {
    data = (transformer_hw_servos__action__MoveServo_SendGoal_Response *)allocator.zero_allocate(size, sizeof(transformer_hw_servos__action__MoveServo_SendGoal_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = transformer_hw_servos__action__MoveServo_SendGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        transformer_hw_servos__action__MoveServo_SendGoal_Response__fini(&data[i - 1]);
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
transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence__fini(transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence * array)
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
      transformer_hw_servos__action__MoveServo_SendGoal_Response__fini(&array->data[i]);
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

transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence *
transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence * array = (transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence__destroy(transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence__are_equal(const transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence * lhs, const transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_SendGoal_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence__copy(
  const transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence * input,
  transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(transformer_hw_servos__action__MoveServo_SendGoal_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    transformer_hw_servos__action__MoveServo_SendGoal_Response * data =
      (transformer_hw_servos__action__MoveServo_SendGoal_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!transformer_hw_servos__action__MoveServo_SendGoal_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          transformer_hw_servos__action__MoveServo_SendGoal_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_SendGoal_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"

bool
transformer_hw_servos__action__MoveServo_SendGoal_Event__init(transformer_hw_servos__action__MoveServo_SendGoal_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    transformer_hw_servos__action__MoveServo_SendGoal_Event__fini(msg);
    return false;
  }
  // request
  if (!transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence__init(&msg->request, 0)) {
    transformer_hw_servos__action__MoveServo_SendGoal_Event__fini(msg);
    return false;
  }
  // response
  if (!transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence__init(&msg->response, 0)) {
    transformer_hw_servos__action__MoveServo_SendGoal_Event__fini(msg);
    return false;
  }
  return true;
}

void
transformer_hw_servos__action__MoveServo_SendGoal_Event__fini(transformer_hw_servos__action__MoveServo_SendGoal_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence__fini(&msg->request);
  // response
  transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence__fini(&msg->response);
}

bool
transformer_hw_servos__action__MoveServo_SendGoal_Event__are_equal(const transformer_hw_servos__action__MoveServo_SendGoal_Event * lhs, const transformer_hw_servos__action__MoveServo_SendGoal_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_SendGoal_Event__copy(
  const transformer_hw_servos__action__MoveServo_SendGoal_Event * input,
  transformer_hw_servos__action__MoveServo_SendGoal_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!transformer_hw_servos__action__MoveServo_SendGoal_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!transformer_hw_servos__action__MoveServo_SendGoal_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

transformer_hw_servos__action__MoveServo_SendGoal_Event *
transformer_hw_servos__action__MoveServo_SendGoal_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_SendGoal_Event * msg = (transformer_hw_servos__action__MoveServo_SendGoal_Event *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_SendGoal_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(transformer_hw_servos__action__MoveServo_SendGoal_Event));
  bool success = transformer_hw_servos__action__MoveServo_SendGoal_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
transformer_hw_servos__action__MoveServo_SendGoal_Event__destroy(transformer_hw_servos__action__MoveServo_SendGoal_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    transformer_hw_servos__action__MoveServo_SendGoal_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence__init(transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_SendGoal_Event * data = NULL;

  if (size) {
    data = (transformer_hw_servos__action__MoveServo_SendGoal_Event *)allocator.zero_allocate(size, sizeof(transformer_hw_servos__action__MoveServo_SendGoal_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = transformer_hw_servos__action__MoveServo_SendGoal_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        transformer_hw_servos__action__MoveServo_SendGoal_Event__fini(&data[i - 1]);
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
transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence__fini(transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence * array)
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
      transformer_hw_servos__action__MoveServo_SendGoal_Event__fini(&array->data[i]);
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

transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence *
transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence * array = (transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence__destroy(transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence__are_equal(const transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence * lhs, const transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_SendGoal_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence__copy(
  const transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence * input,
  transformer_hw_servos__action__MoveServo_SendGoal_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(transformer_hw_servos__action__MoveServo_SendGoal_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    transformer_hw_servos__action__MoveServo_SendGoal_Event * data =
      (transformer_hw_servos__action__MoveServo_SendGoal_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!transformer_hw_servos__action__MoveServo_SendGoal_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          transformer_hw_servos__action__MoveServo_SendGoal_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_SendGoal_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"

bool
transformer_hw_servos__action__MoveServo_GetResult_Request__init(transformer_hw_servos__action__MoveServo_GetResult_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    transformer_hw_servos__action__MoveServo_GetResult_Request__fini(msg);
    return false;
  }
  return true;
}

void
transformer_hw_servos__action__MoveServo_GetResult_Request__fini(transformer_hw_servos__action__MoveServo_GetResult_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
}

bool
transformer_hw_servos__action__MoveServo_GetResult_Request__are_equal(const transformer_hw_servos__action__MoveServo_GetResult_Request * lhs, const transformer_hw_servos__action__MoveServo_GetResult_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_GetResult_Request__copy(
  const transformer_hw_servos__action__MoveServo_GetResult_Request * input,
  transformer_hw_servos__action__MoveServo_GetResult_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  return true;
}

transformer_hw_servos__action__MoveServo_GetResult_Request *
transformer_hw_servos__action__MoveServo_GetResult_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_GetResult_Request * msg = (transformer_hw_servos__action__MoveServo_GetResult_Request *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_GetResult_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(transformer_hw_servos__action__MoveServo_GetResult_Request));
  bool success = transformer_hw_servos__action__MoveServo_GetResult_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
transformer_hw_servos__action__MoveServo_GetResult_Request__destroy(transformer_hw_servos__action__MoveServo_GetResult_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    transformer_hw_servos__action__MoveServo_GetResult_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence__init(transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_GetResult_Request * data = NULL;

  if (size) {
    data = (transformer_hw_servos__action__MoveServo_GetResult_Request *)allocator.zero_allocate(size, sizeof(transformer_hw_servos__action__MoveServo_GetResult_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = transformer_hw_servos__action__MoveServo_GetResult_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        transformer_hw_servos__action__MoveServo_GetResult_Request__fini(&data[i - 1]);
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
transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence__fini(transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence * array)
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
      transformer_hw_servos__action__MoveServo_GetResult_Request__fini(&array->data[i]);
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

transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence *
transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence * array = (transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence__destroy(transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence__are_equal(const transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence * lhs, const transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_GetResult_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence__copy(
  const transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence * input,
  transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(transformer_hw_servos__action__MoveServo_GetResult_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    transformer_hw_servos__action__MoveServo_GetResult_Request * data =
      (transformer_hw_servos__action__MoveServo_GetResult_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!transformer_hw_servos__action__MoveServo_GetResult_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          transformer_hw_servos__action__MoveServo_GetResult_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_GetResult_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result`
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"

bool
transformer_hw_servos__action__MoveServo_GetResult_Response__init(transformer_hw_servos__action__MoveServo_GetResult_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // result
  if (!transformer_hw_servos__action__MoveServo_Result__init(&msg->result)) {
    transformer_hw_servos__action__MoveServo_GetResult_Response__fini(msg);
    return false;
  }
  return true;
}

void
transformer_hw_servos__action__MoveServo_GetResult_Response__fini(transformer_hw_servos__action__MoveServo_GetResult_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // result
  transformer_hw_servos__action__MoveServo_Result__fini(&msg->result);
}

bool
transformer_hw_servos__action__MoveServo_GetResult_Response__are_equal(const transformer_hw_servos__action__MoveServo_GetResult_Response * lhs, const transformer_hw_servos__action__MoveServo_GetResult_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // result
  if (!transformer_hw_servos__action__MoveServo_Result__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_GetResult_Response__copy(
  const transformer_hw_servos__action__MoveServo_GetResult_Response * input,
  transformer_hw_servos__action__MoveServo_GetResult_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // result
  if (!transformer_hw_servos__action__MoveServo_Result__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  return true;
}

transformer_hw_servos__action__MoveServo_GetResult_Response *
transformer_hw_servos__action__MoveServo_GetResult_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_GetResult_Response * msg = (transformer_hw_servos__action__MoveServo_GetResult_Response *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_GetResult_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(transformer_hw_servos__action__MoveServo_GetResult_Response));
  bool success = transformer_hw_servos__action__MoveServo_GetResult_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
transformer_hw_servos__action__MoveServo_GetResult_Response__destroy(transformer_hw_servos__action__MoveServo_GetResult_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    transformer_hw_servos__action__MoveServo_GetResult_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence__init(transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_GetResult_Response * data = NULL;

  if (size) {
    data = (transformer_hw_servos__action__MoveServo_GetResult_Response *)allocator.zero_allocate(size, sizeof(transformer_hw_servos__action__MoveServo_GetResult_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = transformer_hw_servos__action__MoveServo_GetResult_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        transformer_hw_servos__action__MoveServo_GetResult_Response__fini(&data[i - 1]);
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
transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence__fini(transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence * array)
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
      transformer_hw_servos__action__MoveServo_GetResult_Response__fini(&array->data[i]);
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

transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence *
transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence * array = (transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence__destroy(transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence__are_equal(const transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence * lhs, const transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_GetResult_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence__copy(
  const transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence * input,
  transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(transformer_hw_servos__action__MoveServo_GetResult_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    transformer_hw_servos__action__MoveServo_GetResult_Response * data =
      (transformer_hw_servos__action__MoveServo_GetResult_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!transformer_hw_servos__action__MoveServo_GetResult_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          transformer_hw_servos__action__MoveServo_GetResult_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_GetResult_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
// already included above
// #include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"

bool
transformer_hw_servos__action__MoveServo_GetResult_Event__init(transformer_hw_servos__action__MoveServo_GetResult_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    transformer_hw_servos__action__MoveServo_GetResult_Event__fini(msg);
    return false;
  }
  // request
  if (!transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence__init(&msg->request, 0)) {
    transformer_hw_servos__action__MoveServo_GetResult_Event__fini(msg);
    return false;
  }
  // response
  if (!transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence__init(&msg->response, 0)) {
    transformer_hw_servos__action__MoveServo_GetResult_Event__fini(msg);
    return false;
  }
  return true;
}

void
transformer_hw_servos__action__MoveServo_GetResult_Event__fini(transformer_hw_servos__action__MoveServo_GetResult_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence__fini(&msg->request);
  // response
  transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence__fini(&msg->response);
}

bool
transformer_hw_servos__action__MoveServo_GetResult_Event__are_equal(const transformer_hw_servos__action__MoveServo_GetResult_Event * lhs, const transformer_hw_servos__action__MoveServo_GetResult_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_GetResult_Event__copy(
  const transformer_hw_servos__action__MoveServo_GetResult_Event * input,
  transformer_hw_servos__action__MoveServo_GetResult_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!transformer_hw_servos__action__MoveServo_GetResult_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!transformer_hw_servos__action__MoveServo_GetResult_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

transformer_hw_servos__action__MoveServo_GetResult_Event *
transformer_hw_servos__action__MoveServo_GetResult_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_GetResult_Event * msg = (transformer_hw_servos__action__MoveServo_GetResult_Event *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_GetResult_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(transformer_hw_servos__action__MoveServo_GetResult_Event));
  bool success = transformer_hw_servos__action__MoveServo_GetResult_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
transformer_hw_servos__action__MoveServo_GetResult_Event__destroy(transformer_hw_servos__action__MoveServo_GetResult_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    transformer_hw_servos__action__MoveServo_GetResult_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence__init(transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_GetResult_Event * data = NULL;

  if (size) {
    data = (transformer_hw_servos__action__MoveServo_GetResult_Event *)allocator.zero_allocate(size, sizeof(transformer_hw_servos__action__MoveServo_GetResult_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = transformer_hw_servos__action__MoveServo_GetResult_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        transformer_hw_servos__action__MoveServo_GetResult_Event__fini(&data[i - 1]);
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
transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence__fini(transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence * array)
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
      transformer_hw_servos__action__MoveServo_GetResult_Event__fini(&array->data[i]);
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

transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence *
transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence * array = (transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence__destroy(transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence__are_equal(const transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence * lhs, const transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_GetResult_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence__copy(
  const transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence * input,
  transformer_hw_servos__action__MoveServo_GetResult_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(transformer_hw_servos__action__MoveServo_GetResult_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    transformer_hw_servos__action__MoveServo_GetResult_Event * data =
      (transformer_hw_servos__action__MoveServo_GetResult_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!transformer_hw_servos__action__MoveServo_GetResult_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          transformer_hw_servos__action__MoveServo_GetResult_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_GetResult_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `feedback`
// already included above
// #include "transformer_hw_servos/action/detail/move_servo__functions.h"

bool
transformer_hw_servos__action__MoveServo_FeedbackMessage__init(transformer_hw_servos__action__MoveServo_FeedbackMessage * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    transformer_hw_servos__action__MoveServo_FeedbackMessage__fini(msg);
    return false;
  }
  // feedback
  if (!transformer_hw_servos__action__MoveServo_Feedback__init(&msg->feedback)) {
    transformer_hw_servos__action__MoveServo_FeedbackMessage__fini(msg);
    return false;
  }
  return true;
}

void
transformer_hw_servos__action__MoveServo_FeedbackMessage__fini(transformer_hw_servos__action__MoveServo_FeedbackMessage * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // feedback
  transformer_hw_servos__action__MoveServo_Feedback__fini(&msg->feedback);
}

bool
transformer_hw_servos__action__MoveServo_FeedbackMessage__are_equal(const transformer_hw_servos__action__MoveServo_FeedbackMessage * lhs, const transformer_hw_servos__action__MoveServo_FeedbackMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // feedback
  if (!transformer_hw_servos__action__MoveServo_Feedback__are_equal(
      &(lhs->feedback), &(rhs->feedback)))
  {
    return false;
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_FeedbackMessage__copy(
  const transformer_hw_servos__action__MoveServo_FeedbackMessage * input,
  transformer_hw_servos__action__MoveServo_FeedbackMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // feedback
  if (!transformer_hw_servos__action__MoveServo_Feedback__copy(
      &(input->feedback), &(output->feedback)))
  {
    return false;
  }
  return true;
}

transformer_hw_servos__action__MoveServo_FeedbackMessage *
transformer_hw_servos__action__MoveServo_FeedbackMessage__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_FeedbackMessage * msg = (transformer_hw_servos__action__MoveServo_FeedbackMessage *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_FeedbackMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(transformer_hw_servos__action__MoveServo_FeedbackMessage));
  bool success = transformer_hw_servos__action__MoveServo_FeedbackMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
transformer_hw_servos__action__MoveServo_FeedbackMessage__destroy(transformer_hw_servos__action__MoveServo_FeedbackMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    transformer_hw_servos__action__MoveServo_FeedbackMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence__init(transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_FeedbackMessage * data = NULL;

  if (size) {
    data = (transformer_hw_servos__action__MoveServo_FeedbackMessage *)allocator.zero_allocate(size, sizeof(transformer_hw_servos__action__MoveServo_FeedbackMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = transformer_hw_servos__action__MoveServo_FeedbackMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        transformer_hw_servos__action__MoveServo_FeedbackMessage__fini(&data[i - 1]);
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
transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence__fini(transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence * array)
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
      transformer_hw_servos__action__MoveServo_FeedbackMessage__fini(&array->data[i]);
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

transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence *
transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence * array = (transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence *)allocator.allocate(sizeof(transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence__destroy(transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence__are_equal(const transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence * lhs, const transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_FeedbackMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence__copy(
  const transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence * input,
  transformer_hw_servos__action__MoveServo_FeedbackMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(transformer_hw_servos__action__MoveServo_FeedbackMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    transformer_hw_servos__action__MoveServo_FeedbackMessage * data =
      (transformer_hw_servos__action__MoveServo_FeedbackMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!transformer_hw_servos__action__MoveServo_FeedbackMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          transformer_hw_servos__action__MoveServo_FeedbackMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!transformer_hw_servos__action__MoveServo_FeedbackMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
