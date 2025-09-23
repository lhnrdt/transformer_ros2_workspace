cmake_minimum_required(VERSION 3.8)
project(transformer_msp_bridge)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Always generate compile_commands.json for editor integration
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(diagnostic_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

include_directories(include)

set(MSG_FILES
  "msg/MspInavStatus.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${MSG_FILES}
  DEPENDENCIES std_msgs
)
# Add path to external iNav MSP headers (relative to workspace src layout)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../external/inav/src/main)

add_library(msp_protocol
  src/msp_parser.cpp
  src/msp_builders.cpp
  src/crc.cpp
  src/msp_utils.cpp
  src/msp_registry.cpp
)
ament_target_dependencies(msp_protocol rclcpp)
target_compile_features(msp_protocol PUBLIC cxx_std_17)
target_include_directories(msp_protocol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../external/inav/src/main)

add_library(serial_port
  src/serial_port.cpp
)
target_compile_features(serial_port PUBLIC cxx_std_17)

add_library(${PROJECT_NAME}_decoders
  src/decoders/battery_decoder.cpp
  src/decoders/system_decoder.cpp
  src/decoders/attitude_decoder.cpp
  src/decoders/imu_decoder.cpp
  src/decoders/gps_decoder.cpp
  src/decoders/rc_decoder.cpp
  src/decoders/altitude_decoder.cpp
  src/decoders/inav_status_decoder.cpp
  src/decoders/sensor_decoder.cpp
  src/decoders/servo_motor_decoder.cpp
)
target_link_libraries(${PROJECT_NAME}_decoders msp_protocol)
ament_target_dependencies(${PROJECT_NAME}_decoders rclcpp sensor_msgs diagnostic_msgs rosidl_default_runtime)
target_compile_features(${PROJECT_NAME}_decoders PUBLIC cxx_std_17)
add_dependencies(${PROJECT_NAME}_decoders ${PROJECT_NAME}__cpp)
target_include_directories(${PROJECT_NAME}_decoders PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/rosidl_generator_cpp>
)
rosidl_get_typesupport_target(decoders_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(${PROJECT_NAME}_decoders ${decoders_typesupport_target})

add_executable(transformer_msp_bridge_node
  src/transformer_msp_bridge_node.cpp
)
target_link_libraries(transformer_msp_bridge_node msp_protocol serial_port ${PROJECT_NAME}_decoders)
ament_target_dependencies(transformer_msp_bridge_node rclcpp std_msgs geometry_msgs sensor_msgs diagnostic_msgs)
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(transformer_msp_bridge_node ${cpp_typesupport_target})
add_dependencies(transformer_msp_bridge_node ${PROJECT_NAME}__cpp)
target_compile_features(transformer_msp_bridge_node PUBLIC cxx_std_17)

install(TARGETS msp_protocol serial_port ${PROJECT_NAME}_decoders
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

install(TARGETS transformer_msp_bridge_node
  RUNTIME DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME})
install(DIRECTORY msg
  DESTINATION share/${PROJECT_NAME})
install(DIRECTORY config
  DESTINATION share/${PROJECT_NAME})

# Export include directories and dependencies before ament_package
ament_export_include_directories(include)
ament_export_dependencies(rclcpp std_msgs geometry_msgs sensor_msgs rosidl_default_runtime)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(test_battery_decoder
    test/test_battery_decoder.cpp)
  if(TARGET test_battery_decoder)
    target_link_libraries(test_battery_decoder ${PROJECT_NAME}_decoders msp_protocol)
    ament_target_dependencies(test_battery_decoder rclcpp sensor_msgs diagnostic_msgs)
  endif()

  ament_add_gtest(test_system_decoder
    test/test_system_decoder.cpp)
  if(TARGET test_system_decoder)
    target_link_libraries(test_system_decoder ${PROJECT_NAME}_decoders msp_protocol)
    ament_target_dependencies(test_system_decoder rclcpp diagnostic_msgs)
  endif()

  ament_add_gtest(test_attitude_decoder
    test/test_attitude_decoder.cpp)
  if(TARGET test_attitude_decoder)
    target_link_libraries(test_attitude_decoder ${PROJECT_NAME}_decoders msp_protocol)
    ament_target_dependencies(test_attitude_decoder rclcpp geometry_msgs)
  endif()

  ament_add_gtest(test_imu_decoder
    test/test_imu_decoder.cpp)
  if(TARGET test_imu_decoder)
    target_link_libraries(test_imu_decoder ${PROJECT_NAME}_decoders msp_protocol)
    ament_target_dependencies(test_imu_decoder rclcpp sensor_msgs)
  endif()

  ament_add_gtest(test_gps_decoder
    test/test_gps_decoder.cpp)
  if(TARGET test_gps_decoder)
    target_link_libraries(test_gps_decoder ${PROJECT_NAME}_decoders msp_protocol)
    ament_target_dependencies(test_gps_decoder rclcpp sensor_msgs geometry_msgs std_msgs)
  endif()

  ament_add_gtest(test_rc_decoder
    test/test_rc_decoder.cpp)
  if(TARGET test_rc_decoder)
    target_link_libraries(test_rc_decoder ${PROJECT_NAME}_decoders msp_protocol)
    ament_target_dependencies(test_rc_decoder rclcpp std_msgs)
  endif()

  ament_add_gtest(test_altitude_decoder
    test/test_altitude_decoder.cpp)
  if(TARGET test_altitude_decoder)
    target_link_libraries(test_altitude_decoder ${PROJECT_NAME}_decoders msp_protocol)
    ament_target_dependencies(test_altitude_decoder rclcpp std_msgs geometry_msgs)
  endif()

  ament_add_gtest(test_inav_status_decoder
    test/test_inav_status_decoder.cpp)
  if(TARGET test_inav_status_decoder)
    target_link_libraries(test_inav_status_decoder ${PROJECT_NAME}_decoders msp_protocol)
    ament_target_dependencies(test_inav_status_decoder rclcpp std_msgs geometry_msgs)
  endif()

  ament_add_gtest(test_sensor_decoder
    test/test_sensor_decoder.cpp)
  if(TARGET test_sensor_decoder)
    target_link_libraries(test_sensor_decoder ${PROJECT_NAME}_decoders msp_protocol)
    ament_target_dependencies(test_sensor_decoder rclcpp std_msgs geometry_msgs)
  endif()

  ament_add_gtest(test_servo_motor_decoder
    test/test_servo_motor_decoder.cpp)
  if(TARGET test_servo_motor_decoder)
    target_link_libraries(test_servo_motor_decoder ${PROJECT_NAME}_decoders msp_protocol)
    ament_target_dependencies(test_servo_motor_decoder rclcpp sensor_msgs)
  endif()

  ament_add_gtest(test_system_decoder_extended
    test/test_system_decoder_extended.cpp)
  if(TARGET test_system_decoder_extended)
    target_link_libraries(test_system_decoder_extended ${PROJECT_NAME}_decoders msp_protocol)
    ament_target_dependencies(test_system_decoder_extended rclcpp diagnostic_msgs)
  endif()

  ament_add_gtest(test_msp_parser
    test/test_msp_parser.cpp)
  if(TARGET test_msp_parser)
    target_link_libraries(test_msp_parser msp_protocol)
    ament_target_dependencies(test_msp_parser rclcpp)
  endif()

  ament_add_gtest(test_msp_parser_fuzz
    test/test_msp_parser_fuzz.cpp)
  if(TARGET test_msp_parser_fuzz)
    target_link_libraries(test_msp_parser_fuzz msp_protocol)
    ament_target_dependencies(test_msp_parser_fuzz rclcpp)
    target_compile_definitions(test_msp_parser_fuzz PRIVATE -DMSP_FUZZ_TEST)
  endif()

  ament_add_gtest(test_msp_parser_hardening
    test/test_msp_parser_hardening.cpp)
  if(TARGET test_msp_parser_hardening)
    target_link_libraries(test_msp_parser_hardening msp_protocol)
    ament_target_dependencies(test_msp_parser_hardening rclcpp)
  endif()

  ament_add_gtest(test_crc
    test/test_crc.cpp)
  if(TARGET test_crc)
    target_link_libraries(test_crc msp_protocol)
  endif()
endif()

ament_package()
