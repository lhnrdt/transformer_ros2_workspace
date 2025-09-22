cmake_minimum_required(VERSION 3.8)
project(msp_bridge)

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
  src/msp_protocol.cpp
  src/msp_registry.cpp
)
ament_target_dependencies(msp_protocol rclcpp)
target_compile_features(msp_protocol PUBLIC cxx_std_17)
target_include_directories(msp_protocol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../external/inav/src/main)

add_library(serial_port
  src/serial_port.cpp
)
target_compile_features(serial_port PUBLIC cxx_std_17)

add_executable(msp_bridge_node src/msp_bridge_node.cpp)
target_link_libraries(msp_bridge_node msp_protocol serial_port)
ament_target_dependencies(msp_bridge_node rclcpp std_msgs geometry_msgs sensor_msgs)
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(msp_bridge_node ${cpp_typesupport_target})
add_dependencies(msp_bridge_node ${PROJECT_NAME}__cpp)
target_compile_features(msp_bridge_node PUBLIC cxx_std_17)

install(TARGETS msp_protocol serial_port
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

install(TARGETS msp_bridge_node
  RUNTIME DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME})
install(DIRECTORY msg
  DESTINATION share/${PROJECT_NAME})

# Export include directories and dependencies before ament_package
ament_export_include_directories(include)
ament_export_dependencies(rclcpp std_msgs geometry_msgs sensor_msgs rosidl_default_runtime)

ament_package()
