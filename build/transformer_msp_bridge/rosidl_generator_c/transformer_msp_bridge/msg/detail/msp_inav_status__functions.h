// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from transformer_msp_bridge:msg/MspInavStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "transformer_msp_bridge/msg/msp_inav_status.h"


#ifndef TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__FUNCTIONS_H_
#define TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "transformer_msp_bridge/msg/rosidl_generator_c__visibility_control.h"

#include "transformer_msp_bridge/msg/detail/msp_inav_status__struct.h"

/// Initialize msg/MspInavStatus message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * transformer_msp_bridge__msg__MspInavStatus
 * )) before or use
 * transformer_msp_bridge__msg__MspInavStatus__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_transformer_msp_bridge
bool
transformer_msp_bridge__msg__MspInavStatus__init(transformer_msp_bridge__msg__MspInavStatus * msg);

/// Finalize msg/MspInavStatus message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_transformer_msp_bridge
void
transformer_msp_bridge__msg__MspInavStatus__fini(transformer_msp_bridge__msg__MspInavStatus * msg);

/// Create msg/MspInavStatus message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * transformer_msp_bridge__msg__MspInavStatus__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_transformer_msp_bridge
transformer_msp_bridge__msg__MspInavStatus *
transformer_msp_bridge__msg__MspInavStatus__create(void);

/// Destroy msg/MspInavStatus message.
/**
 * It calls
 * transformer_msp_bridge__msg__MspInavStatus__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_transformer_msp_bridge
void
transformer_msp_bridge__msg__MspInavStatus__destroy(transformer_msp_bridge__msg__MspInavStatus * msg);

/// Check for msg/MspInavStatus message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_transformer_msp_bridge
bool
transformer_msp_bridge__msg__MspInavStatus__are_equal(const transformer_msp_bridge__msg__MspInavStatus * lhs, const transformer_msp_bridge__msg__MspInavStatus * rhs);

/// Copy a msg/MspInavStatus message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_transformer_msp_bridge
bool
transformer_msp_bridge__msg__MspInavStatus__copy(
  const transformer_msp_bridge__msg__MspInavStatus * input,
  transformer_msp_bridge__msg__MspInavStatus * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_transformer_msp_bridge
const rosidl_type_hash_t *
transformer_msp_bridge__msg__MspInavStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_transformer_msp_bridge
const rosidl_runtime_c__type_description__TypeDescription *
transformer_msp_bridge__msg__MspInavStatus__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_transformer_msp_bridge
const rosidl_runtime_c__type_description__TypeSource *
transformer_msp_bridge__msg__MspInavStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_transformer_msp_bridge
const rosidl_runtime_c__type_description__TypeSource__Sequence *
transformer_msp_bridge__msg__MspInavStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of msg/MspInavStatus messages.
/**
 * It allocates the memory for the number of elements and calls
 * transformer_msp_bridge__msg__MspInavStatus__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_transformer_msp_bridge
bool
transformer_msp_bridge__msg__MspInavStatus__Sequence__init(transformer_msp_bridge__msg__MspInavStatus__Sequence * array, size_t size);

/// Finalize array of msg/MspInavStatus messages.
/**
 * It calls
 * transformer_msp_bridge__msg__MspInavStatus__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_transformer_msp_bridge
void
transformer_msp_bridge__msg__MspInavStatus__Sequence__fini(transformer_msp_bridge__msg__MspInavStatus__Sequence * array);

/// Create array of msg/MspInavStatus messages.
/**
 * It allocates the memory for the array and calls
 * transformer_msp_bridge__msg__MspInavStatus__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_transformer_msp_bridge
transformer_msp_bridge__msg__MspInavStatus__Sequence *
transformer_msp_bridge__msg__MspInavStatus__Sequence__create(size_t size);

/// Destroy array of msg/MspInavStatus messages.
/**
 * It calls
 * transformer_msp_bridge__msg__MspInavStatus__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_transformer_msp_bridge
void
transformer_msp_bridge__msg__MspInavStatus__Sequence__destroy(transformer_msp_bridge__msg__MspInavStatus__Sequence * array);

/// Check for msg/MspInavStatus message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_transformer_msp_bridge
bool
transformer_msp_bridge__msg__MspInavStatus__Sequence__are_equal(const transformer_msp_bridge__msg__MspInavStatus__Sequence * lhs, const transformer_msp_bridge__msg__MspInavStatus__Sequence * rhs);

/// Copy an array of msg/MspInavStatus messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_transformer_msp_bridge
bool
transformer_msp_bridge__msg__MspInavStatus__Sequence__copy(
  const transformer_msp_bridge__msg__MspInavStatus__Sequence * input,
  transformer_msp_bridge__msg__MspInavStatus__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // TRANSFORMER_MSP_BRIDGE__MSG__DETAIL__MSP_INAV_STATUS__FUNCTIONS_H_
