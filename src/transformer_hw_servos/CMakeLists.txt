cmake_minimum_required(VERSION 3.8)
project(transformer_hw_servos)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(builtin_interfaces REQUIRED)

# Interface (action definition)
rosidl_generate_interfaces(${PROJECT_NAME}
  "action/MoveServo.action"
  DEPENDENCIES builtin_interfaces
)

find_package(Threads REQUIRED)
find_library(LGPIO_LIB lgpio REQUIRED)

add_executable(servos_node
  src/servos_node.cpp
  src/backends/lgpio_backend.cpp
  src/backends/pca9685_backend.cpp
)
target_compile_features(servos_node PUBLIC c_std_99 cxx_std_17)
target_include_directories(servos_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/rosidl_generator_cpp>
)
ament_target_dependencies(servos_node rclcpp rclcpp_action)
target_link_libraries(servos_node ${LGPIO_LIB})

# Link against generated typesupport target (recommended pattern)
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(servos_node ${cpp_typesupport_target})
target_link_libraries(servos_node Threads::Threads)

install(TARGETS servos_node
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch)

install(DIRECTORY config/
  DESTINATION share/${PROJECT_NAME}/config)

install(DIRECTORY action/
  DESTINATION share/${PROJECT_NAME}/action)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(rosidl_default_runtime)

ament_package()
