cmake_minimum_required(VERSION 3.8)
project(transformer_hw_servos)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# Interface
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/SetServoPulse.srv"
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GPIOD REQUIRED IMPORTED_TARGET libgpiod)
find_package(Threads REQUIRED)

add_executable(servos_node src/servos_node.cpp)
target_compile_features(servos_node PUBLIC c_std_99 cxx_std_17)
target_include_directories(servos_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
ament_target_dependencies(servos_node rclcpp)
target_link_libraries(servos_node PkgConfig::GPIOD)

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

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
