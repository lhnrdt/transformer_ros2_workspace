cmake_minimum_required(VERSION 3.8)
project(transformer_controller)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(transformer_hw_actuators REQUIRED)
find_package(transformer_hw_servos REQUIRED)

set(action_files
  "action/TransformMode.action"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${action_files}
  DEPENDENCIES builtin_interfaces
)

add_executable(transformer_controller_node src/transformer_controller_node.cpp)
ament_target_dependencies(transformer_controller_node rclcpp rclcpp_action transformer_hw_actuators transformer_hw_servos)
rosidl_target_interfaces(transformer_controller_node
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

install(TARGETS transformer_controller_node DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY action launch config DESTINATION share/${PROJECT_NAME} OPTIONAL)

ament_package()
