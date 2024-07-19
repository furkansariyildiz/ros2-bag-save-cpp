cmake_minimum_required(VERSION 3.8)
project(ros2_bag_save_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosbag2_cpp REQUIRED)
find_package(topic_tools REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(rosbag2_storage REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rosidl_typesupport_cpp REQUIRED)
find_package(rosbag2_transport  REQUIRED)


include_directories(include)

add_executable(ros2_bag_save src/ros2_bag_save.cpp)
target_link_libraries(ros2_bag_save ${catkin_LIBRARIES})
ament_target_dependencies(ros2_bag_save 
                          rclcpp 
                          rosbag2_cpp
                          topic_tools 
                          std_msgs
                          std_srvs
                          rosbag2_storage                         
                          rosidl_typesupport_cpp
                          rosbag2_transport 
)


install(TARGETS 
        ros2_bag_save
        DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
        launch
        config 
        DESTINATION share/${PROJECT_NAME}
)

# rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
ament_package()
