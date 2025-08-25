cmake_minimum_required(VERSION 3.8)
project(software_pwm)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

find_package(rclcpp REQUIRED)

find_package(rclcpp_action REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "action/MoveServo.action"
)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GPIOD REQUIRED IMPORTED_TARGET libgpiod)

add_executable(software_pwm_node src/software_pwm_node.cpp)
target_include_directories(software_pwm_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>)
target_compile_features(software_pwm_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

ament_target_dependencies(software_pwm_node rclcpp rclcpp_action)
target_link_libraries(software_pwm_node PkgConfig::GPIOD)
install(TARGETS software_pwm_node
  DESTINATION lib/${PROJECT_NAME})


  rosidl_target_interfaces(software_pwm_node
  ${PROJECT_NAME} "rosidl_typesupport_cpp"
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
