#include <ros2_bag_save_cpp/ros2_bag_save.hpp>



Ros2BagSave::Ros2BagSave() : Node("rosbag_recorder"), is_recording_(false)
{
    start_recording_service_ = this->create_service<std_srvs::srv::Trigger>(
        "start_recording", 
        [this](const std_srvs::srv::Trigger::Request::SharedPtr /*request*/, std_srvs::srv::Trigger::Response::SharedPtr response) {
            this->startRecording();
            response->success = true;
            response->message = "Recording started";
        });

    stop_recording_service_ = this->create_service<std_srvs::srv::Trigger>(
        "stop_recording", 
        [this](const std_srvs::srv::Trigger::Request::SharedPtr /*request*/, std_srvs::srv::Trigger::Response::SharedPtr response) {
            this->stopRecording();
            response->success = true;
            response->message = "Recording stopped";
        });

    bag_filename_ = "/home/furkan/rosbag_records/test.bag";
}

Ros2BagSave::~Ros2BagSave()
{
    stopRecording();
}

void Ros2BagSave::startRecording()
{
    if (is_recording_) {
        RCLCPP_WARN(this->get_logger(), "Already recording");
        return;
    }

    writer_ = std::make_shared<rosbag2_cpp::Writer>();
    rosbag2_storage::StorageOptions storage_options;
    storage_options.uri = bag_filename_;
    storage_options.storage_id = "sqlite3";

    rosbag2_cpp::ConverterOptions converter_options;
    converter_options.input_serialization_format = "cdr";
    converter_options.output_serialization_format = "cdr";

    writer_->open(storage_options, converter_options);
    is_recording_ = true;

    createSubscriptions();

    RCLCPP_INFO(this->get_logger(), "Recording started");
}

void Ros2BagSave::stopRecording()
{
    if (!is_recording_) {
        RCLCPP_WARN(this->get_logger(), "Not currently recording");
        return;
    }

    writer_.reset();
    dynamic_subscribers_.clear();
    is_recording_ = false;
    RCLCPP_INFO(this->get_logger(), "Recording stopped");
}

void Ros2BagSave::createSubscriptions()
{
    // Add your topics here, e.g., "/example_topic1", "/example_topic2"
    std::vector<std::string> topics = {"/example_topic1", "/example_topic2"};

    for (const auto &topic : topics)
    {
        auto callback = [this, topic](const std::shared_ptr<rclcpp::SerializedMessage> msg) {
            this->dynamicTopicCallback(msg, topic);
        };

        auto subscription = this->create_generic_subscription(
            topic, 
            "std_msgs/msg/String",  // replace with the actual type if needed
            rclcpp::QoS(10),
            callback);
        dynamic_subscribers_.push_back(subscription);
    }
}

void Ros2BagSave::dynamicTopicCallback(const std::shared_ptr<rclcpp::SerializedMessage> message, const std::string &topic_name)
{
    if (is_recording_) {
        auto bag_message = std::make_shared<rosbag2_storage::SerializedBagMessage>();
        bag_message->time_stamp = this->now().nanoseconds();
        bag_message->topic_name = topic_name;

        // Allocate memory and copy serialized data
        bag_message->serialized_data = std::make_shared<rcutils_uint8_array_t>();
        *bag_message->serialized_data = rcutils_get_zero_initialized_uint8_array();
        rcutils_allocator_t allocator = rcutils_get_default_allocator();
        rcutils_uint8_array_init(bag_message->serialized_data.get(), message->size(), &allocator);
        memcpy(bag_message->serialized_data->buffer, message->get_rcl_serialized_message().buffer, message->size());

        writer_->write(bag_message);
    }
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Ros2BagSave>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}