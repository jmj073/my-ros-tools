#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/empty.hpp"
#include <iostream>
#include <cerrno>

namespace rcl = rclcpp;

int main(int argc, char *argv[]) {
  rcl::init(argc, argv);
  auto args = rcl::remove_ros_arguments(argc, argv);

  if (args.size() != 2 && args.size() != 3) {
    std::cerr << "Invalid number of arguments: " << args.size() << std::endl;
    rcl::shutdown();
    return EINVAL;
  }

  auto node = rcl::Node::make_shared(args[1]);

  std::cout << node->get_node_names()[0] << std::endl;

  if (args.size() == 3) {
    auto& name = args[2];
    auto pub = node->create_publisher<std_msgs::msg::Empty>(name, 10);
    std::cout << pub->get_topic_name() << std::endl;
  }

  rcl::shutdown();
}
