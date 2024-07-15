#include <ros2_bag_save_cpp/ros2_bag_save.hpp>



Ros2BagSave::Ros2BagSave():
Node("ros2_bag_save_cpp_node")
{

}



Ros2BagSave::~Ros2BagSave()
{

}



int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Ros2BagSave>());

    return 0;
}