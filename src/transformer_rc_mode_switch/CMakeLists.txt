cmake_minimum_required(VERSION 3.8)
project(transformer_rc_mode_switch)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Always generate compile_commands.json for editor integration
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(std_msgs REQUIRED)
find_package(transformer_controller REQUIRED)

add_executable(rc_mode_switch_node src/rc_mode_switch_node.cpp)
target_include_directories(rc_mode_switch_node PUBLIC include)
ament_target_dependencies(rc_mode_switch_node rclcpp rclcpp_action std_msgs transformer_controller)

install(TARGETS rc_mode_switch_node
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY include/
  DESTINATION include)

install(DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch)

ament_package()
