cmake_minimum_required(VERSION 3.8)
project(transformer_description)

find_package(ament_cmake REQUIRED)

# Install URDF/Xacro and launch files
install(DIRECTORY urdf
  DESTINATION share/${PROJECT_NAME}
)
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)
install(DIRECTORY model
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
