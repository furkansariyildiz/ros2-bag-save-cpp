#ifndef ROS2_BAG_SAVE_HPP_
#define ROS2_BAG_SAVE_HPP_


#include <rclcpp/rclcpp.hpp>
#include <rosbag2_cpp/reader.hpp>
#include <rosbag2_cpp/writer.hpp>

#include <std_msgs/msg/string.hpp>


class Ros2BagSave: public rclcpp::Node
{
    private:
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr test_topic_subscriber_;

        std::unique_ptr<rosbag2_cpp::Writer> writer_;
        std::unique_ptr<rosbag2_cpp::Reader> reader_;

    protected:

    public:
        Ros2BagSave();

        ~Ros2BagSave();

};



#endif