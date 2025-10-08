// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from transformer_msp_bridge:msg/MspInavStatus.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "transformer_msp_bridge/msg/detail/msp_inav_status__struct.h"
#include "transformer_msp_bridge/msg/detail/msp_inav_status__functions.h"

#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool transformer_msp_bridge__msg__msp_inav_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[58];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("transformer_msp_bridge.msg._msp_inav_status.MspInavStatus", full_classname_dest, 57) == 0);
  }
  transformer_msp_bridge__msg__MspInavStatus * ros_message = _ros_message;
  {  // cycle_time_us
    PyObject * field = PyObject_GetAttrString(_pymsg, "cycle_time_us");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->cycle_time_us = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // i2c_errors
    PyObject * field = PyObject_GetAttrString(_pymsg, "i2c_errors");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->i2c_errors = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // sensor_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "sensor_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->sensor_status = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // cpu_load_percent
    PyObject * field = PyObject_GetAttrString(_pymsg, "cpu_load_percent");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->cpu_load_percent = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // config_profile
    PyObject * field = PyObject_GetAttrString(_pymsg, "config_profile");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->config_profile = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // battery_profile
    PyObject * field = PyObject_GetAttrString(_pymsg, "battery_profile");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->battery_profile = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // mixer_profile
    PyObject * field = PyObject_GetAttrString(_pymsg, "mixer_profile");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->mixer_profile = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // arming_flags
    PyObject * field = PyObject_GetAttrString(_pymsg, "arming_flags");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->arming_flags = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // active_modes
    PyObject * field = PyObject_GetAttrString(_pymsg, "active_modes");
    if (!field) {
      return false;
    }
    if (PyObject_CheckBuffer(field)) {
      // Optimization for converting arrays of primitives
      Py_buffer view;
      int rc = PyObject_GetBuffer(field, &view, PyBUF_SIMPLE);
      if (rc < 0) {
        Py_DECREF(field);
        return false;
      }
      Py_ssize_t size = view.len / sizeof(uint8_t);
      if (!rosidl_runtime_c__uint8__Sequence__init(&(ros_message->active_modes), size)) {
        PyErr_SetString(PyExc_RuntimeError, "unable to create uint8__Sequence ros_message");
        PyBuffer_Release(&view);
        Py_DECREF(field);
        return false;
      }
      uint8_t * dest = ros_message->active_modes.data;
      rc = PyBuffer_ToContiguous(dest, &view, view.len, 'C');
      if (rc < 0) {
        PyBuffer_Release(&view);
        Py_DECREF(field);
        return false;
      }
      PyBuffer_Release(&view);
    } else {
      PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'active_modes'");
      if (!seq_field) {
        Py_DECREF(field);
        return false;
      }
      Py_ssize_t size = PySequence_Size(field);
      if (-1 == size) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      if (!rosidl_runtime_c__uint8__Sequence__init(&(ros_message->active_modes), size)) {
        PyErr_SetString(PyExc_RuntimeError, "unable to create uint8__Sequence ros_message");
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      uint8_t * dest = ros_message->active_modes.data;
      for (Py_ssize_t i = 0; i < size; ++i) {
        PyObject * item = PySequence_Fast_GET_ITEM(seq_field, i);
        if (!item) {
          Py_DECREF(seq_field);
          Py_DECREF(field);
          return false;
        }
        assert(PyLong_Check(item));
        uint8_t tmp = (uint8_t)PyLong_AsUnsignedLong(item);

        memcpy(&dest[i], &tmp, sizeof(uint8_t));
      }
      Py_DECREF(seq_field);
    }
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * transformer_msp_bridge__msg__msp_inav_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of MspInavStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("transformer_msp_bridge.msg._msp_inav_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "MspInavStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  transformer_msp_bridge__msg__MspInavStatus * ros_message = (transformer_msp_bridge__msg__MspInavStatus *)raw_ros_message;
  {  // cycle_time_us
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->cycle_time_us);
    {
      int rc = PyObject_SetAttrString(_pymessage, "cycle_time_us", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // i2c_errors
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->i2c_errors);
    {
      int rc = PyObject_SetAttrString(_pymessage, "i2c_errors", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // sensor_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->sensor_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "sensor_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // cpu_load_percent
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->cpu_load_percent);
    {
      int rc = PyObject_SetAttrString(_pymessage, "cpu_load_percent", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // config_profile
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->config_profile);
    {
      int rc = PyObject_SetAttrString(_pymessage, "config_profile", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // battery_profile
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->battery_profile);
    {
      int rc = PyObject_SetAttrString(_pymessage, "battery_profile", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mixer_profile
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->mixer_profile);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mixer_profile", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // arming_flags
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->arming_flags);
    {
      int rc = PyObject_SetAttrString(_pymessage, "arming_flags", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // active_modes
    PyObject * field = NULL;
    field = PyObject_GetAttrString(_pymessage, "active_modes");
    if (!field) {
      return NULL;
    }
    assert(field->ob_type != NULL);
    assert(field->ob_type->tp_name != NULL);
    assert(strcmp(field->ob_type->tp_name, "array.array") == 0);
    // ensure that itemsize matches the sizeof of the ROS message field
    PyObject * itemsize_attr = PyObject_GetAttrString(field, "itemsize");
    assert(itemsize_attr != NULL);
    size_t itemsize = PyLong_AsSize_t(itemsize_attr);
    Py_DECREF(itemsize_attr);
    if (itemsize != sizeof(uint8_t)) {
      PyErr_SetString(PyExc_RuntimeError, "itemsize doesn't match expectation");
      Py_DECREF(field);
      return NULL;
    }
    // clear the array, poor approach to remove potential default values
    Py_ssize_t length = PyObject_Length(field);
    if (-1 == length) {
      Py_DECREF(field);
      return NULL;
    }
    if (length > 0) {
      PyObject * pop = PyObject_GetAttrString(field, "pop");
      assert(pop != NULL);
      for (Py_ssize_t i = 0; i < length; ++i) {
        PyObject * ret = PyObject_CallFunctionObjArgs(pop, NULL);
        if (!ret) {
          Py_DECREF(pop);
          Py_DECREF(field);
          return NULL;
        }
        Py_DECREF(ret);
      }
      Py_DECREF(pop);
    }
    if (ros_message->active_modes.size > 0) {
      // populating the array.array using the frombytes method
      PyObject * frombytes = PyObject_GetAttrString(field, "frombytes");
      assert(frombytes != NULL);
      uint8_t * src = &(ros_message->active_modes.data[0]);
      PyObject * data = PyBytes_FromStringAndSize((const char *)src, ros_message->active_modes.size * sizeof(uint8_t));
      assert(data != NULL);
      PyObject * ret = PyObject_CallFunctionObjArgs(frombytes, data, NULL);
      Py_DECREF(data);
      Py_DECREF(frombytes);
      if (!ret) {
        Py_DECREF(field);
        return NULL;
      }
      Py_DECREF(ret);
    }
    Py_DECREF(field);
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
