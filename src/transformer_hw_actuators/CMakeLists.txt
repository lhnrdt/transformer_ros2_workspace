cmake_minimum_required(VERSION 3.16)
project(transformer_hw_actuators)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Always generate compile_commands.json for editor integration
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GPIOD REQUIRED libgpiod)

# Interfaces (generate BEFORE ament_package and before targets that include them)
set(action_files action/MoveActuator.action)
rosidl_generate_interfaces(${PROJECT_NAME}
  ${action_files}
  DEPENDENCIES builtin_interfaces
)

include_directories(include ${GPIOD_INCLUDE_DIRS})

add_executable(actuator_node src/actuator_node.cpp)
ament_target_dependencies(actuator_node rclcpp rclcpp_action)

# Ensure generated headers + typesupport are available to this target
add_dependencies(actuator_node ${PROJECT_NAME}__rosidl_generator_cpp)
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")

target_include_directories(actuator_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/rosidl_generator_cpp>
  $<INSTALL_INTERFACE:include>)

target_link_libraries(actuator_node ${GPIOD_LIBRARIES} ${cpp_typesupport_target})

install(TARGETS actuator_node DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY launch DESTINATION share/${PROJECT_NAME}/)
install(DIRECTORY config DESTINATION share/${PROJECT_NAME}/)

ament_export_dependencies(rosidl_default_runtime)
ament_package()