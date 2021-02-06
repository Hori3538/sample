#include <ros/ros.h>
int main(int argc, char **argv){
    ros::init(argc, argv, "hello");
    ros::NodeHandle nh;
    ros::Rate rate(1);
    while(ros::ok()){
        ROS_INFO("Hello World!");
        rate.sleep();
        }
    return 0;
}
