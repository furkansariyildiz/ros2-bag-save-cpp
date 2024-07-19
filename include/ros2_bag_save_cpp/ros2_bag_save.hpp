#ifndef ROS2_BAG_SAVE_HPP_
#define ROS2_BAG_SAVE_HPP_


#include <rclcpp/rclcpp.hpp>
#include <rosbag2_cpp/writer.hpp>
#include <rosbag2_storage/storage_options.hpp>
#include <rosbag2_cpp/writers/sequential_writer.hpp>
#include <std_srvs/srv/trigger.hpp>

#include <string>
#include <vector>



using namespace std;



class Ros2BagSave: public rclcpp::Node
{
    private:
        // unique_ptr<rosbag2_cpp::Writer> writer_;
        // unique_ptr<rosbag2_cpp::Reader> reader_;
        std::shared_ptr<rosbag2_cpp::Writer> writer_;
        vector<rclcpp::SubscriptionBase::SharedPtr> dynamic_subscribers_;
        bool is_recording_;
        string bag_filename_;
        rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr start_recording_service_;
        rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr stop_recording_service_;

        void startRecording();
        void stopRecording();
        void createSubscriptions();
        void dynamicTopicCallback(const std::shared_ptr<rclcpp::SerializedMessage> message, const std::string &topic_name);

    public:
        Ros2BagSave();

        ~Ros2BagSave();
};



#endif