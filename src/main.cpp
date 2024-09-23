#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
class BasicPublisher : public rclcpp::Node
{
public:
    BasicPublisher()
    : Node("basic_publisher")
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("my_topic", 10);
        timer_ = this->create_wall_timer(
        std::chrono::milliseconds(500), std::bind(&BasicPublisher::timer_callback, this));
    }
    void timer_callback()
    {
        auto message = geometry_msgs::msg::Twist();
        message.linear.x = 0.5;
        message.angular.z = 0.1;
        RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.linear.x);
        publisher_->publish(message);
    }
private:
rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<BasicPublisher>());
    rclcpp::shutdown();
    return 0;
}