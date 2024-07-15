cmake_minimum_required(VERSION 3.8)
project(ros2_bag_save_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosbag2_cpp REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(include)

add_executable(ros2_bag_save src/ros2_bag_save.cpp)
target_link_libraries(ros2_bag_save ${catkin_LIBRARIES})
ament_target_dependencies(ros2_bag_save rclcpp rosbag2_cpp std_msgs)

install(TARGETS 
        ros2_bag_save
        DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
        launch
        config 
        DESTINATION share/${PROJECT_NAME}
)

ament_package()
