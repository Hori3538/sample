#ifndef MY_TURTLESIM_CONTROLLER_H
#define MY_TURTLESIM_CONTROLLER_H

#include<ros/ros.h>
#include"turtlesim/Pose.h"
#include"geometry_msgs/Twist.h"
class MyTurtlesimController
{
    public:
        MyTurtlesimController();
        void process();

    private:
        void pose_callback(const turtlesim::Pose::ConstPtr &);
        void go_straight();
        void turn();

        int hz;

        ros::NodeHandle nh;
        ros::NodeHandle private_nh;
        ros::Subscriber sub_pose;
        ros::Publisher pub_cmd_vel;
        turtlesim::Pose current_pose;
};



#endif
