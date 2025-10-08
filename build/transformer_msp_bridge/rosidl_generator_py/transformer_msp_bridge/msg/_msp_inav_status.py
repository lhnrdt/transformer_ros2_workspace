# generated from rosidl_generator_py/resource/_idl.py.em
# with input from transformer_msp_bridge:msg/MspInavStatus.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

# Member 'active_modes'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_MspInavStatus(type):
    """Metaclass of message 'MspInavStatus'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('transformer_msp_bridge')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'transformer_msp_bridge.msg.MspInavStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__msp_inav_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__msp_inav_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__msp_inav_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__msp_inav_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__msp_inav_status

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class MspInavStatus(metaclass=Metaclass_MspInavStatus):
    """Message class 'MspInavStatus'."""

    __slots__ = [
        '_cycle_time_us',
        '_i2c_errors',
        '_sensor_status',
        '_cpu_load_percent',
        '_config_profile',
        '_battery_profile',
        '_mixer_profile',
        '_arming_flags',
        '_active_modes',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'cycle_time_us': 'uint16',
        'i2c_errors': 'uint16',
        'sensor_status': 'uint16',
        'cpu_load_percent': 'uint16',
        'config_profile': 'uint8',
        'battery_profile': 'uint8',
        'mixer_profile': 'uint8',
        'arming_flags': 'uint32',
        'active_modes': 'sequence<uint8>',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('uint8')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.cycle_time_us = kwargs.get('cycle_time_us', int())
        self.i2c_errors = kwargs.get('i2c_errors', int())
        self.sensor_status = kwargs.get('sensor_status', int())
        self.cpu_load_percent = kwargs.get('cpu_load_percent', int())
        self.config_profile = kwargs.get('config_profile', int())
        self.battery_profile = kwargs.get('battery_profile', int())
        self.mixer_profile = kwargs.get('mixer_profile', int())
        self.arming_flags = kwargs.get('arming_flags', int())
        self.active_modes = array.array('B', kwargs.get('active_modes', []))

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.cycle_time_us != other.cycle_time_us:
            return False
        if self.i2c_errors != other.i2c_errors:
            return False
        if self.sensor_status != other.sensor_status:
            return False
        if self.cpu_load_percent != other.cpu_load_percent:
            return False
        if self.config_profile != other.config_profile:
            return False
        if self.battery_profile != other.battery_profile:
            return False
        if self.mixer_profile != other.mixer_profile:
            return False
        if self.arming_flags != other.arming_flags:
            return False
        if self.active_modes != other.active_modes:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def cycle_time_us(self):
        """Message field 'cycle_time_us'."""
        return self._cycle_time_us

    @cycle_time_us.setter
    def cycle_time_us(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'cycle_time_us' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'cycle_time_us' field must be an unsigned integer in [0, 65535]"
        self._cycle_time_us = value

    @builtins.property
    def i2c_errors(self):
        """Message field 'i2c_errors'."""
        return self._i2c_errors

    @i2c_errors.setter
    def i2c_errors(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'i2c_errors' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'i2c_errors' field must be an unsigned integer in [0, 65535]"
        self._i2c_errors = value

    @builtins.property
    def sensor_status(self):
        """Message field 'sensor_status'."""
        return self._sensor_status

    @sensor_status.setter
    def sensor_status(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'sensor_status' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'sensor_status' field must be an unsigned integer in [0, 65535]"
        self._sensor_status = value

    @builtins.property
    def cpu_load_percent(self):
        """Message field 'cpu_load_percent'."""
        return self._cpu_load_percent

    @cpu_load_percent.setter
    def cpu_load_percent(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'cpu_load_percent' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'cpu_load_percent' field must be an unsigned integer in [0, 65535]"
        self._cpu_load_percent = value

    @builtins.property
    def config_profile(self):
        """Message field 'config_profile'."""
        return self._config_profile

    @config_profile.setter
    def config_profile(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'config_profile' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'config_profile' field must be an unsigned integer in [0, 255]"
        self._config_profile = value

    @builtins.property
    def battery_profile(self):
        """Message field 'battery_profile'."""
        return self._battery_profile

    @battery_profile.setter
    def battery_profile(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'battery_profile' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'battery_profile' field must be an unsigned integer in [0, 255]"
        self._battery_profile = value

    @builtins.property
    def mixer_profile(self):
        """Message field 'mixer_profile'."""
        return self._mixer_profile

    @mixer_profile.setter
    def mixer_profile(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'mixer_profile' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'mixer_profile' field must be an unsigned integer in [0, 255]"
        self._mixer_profile = value

    @builtins.property
    def arming_flags(self):
        """Message field 'arming_flags'."""
        return self._arming_flags

    @arming_flags.setter
    def arming_flags(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'arming_flags' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'arming_flags' field must be an unsigned integer in [0, 4294967295]"
        self._arming_flags = value

    @builtins.property
    def active_modes(self):
        """Message field 'active_modes'."""
        return self._active_modes

    @active_modes.setter
    def active_modes(self, value):
        if self._check_fields:
            if isinstance(value, array.array):
                assert value.typecode == 'B', \
                    "The 'active_modes' array.array() must have the type code of 'B'"
                self._active_modes = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 256 for val in value)), \
                "The 'active_modes' field must be a set or sequence and each value of type 'int' and each unsigned integer in [0, 255]"
        self._active_modes = array.array('B', value)
