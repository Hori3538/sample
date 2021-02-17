#include "my_turtlesim_controller/my_turtlesim_controller.h"

MyTurtlesimController::MyTurtlesimController():private_nh("~")
{
    private_nh.param("hz", hz, {10});
    sub_pose = nh.subscribe("/turtle1/pose", 10, &MyTurtlesimController::pose_callback, this);

    pub_cmd_vel = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1);
}

void MyTurtlesimController::pose_callback(const turtlesim::Pose::ConstPtr &msg)
{
    current_pose = *msg;
}

void MyTurtlesimController::go_straight()
{
    std::cout<<current_pose<<std::endl;
    geometry_msgs::Twist cmd_vel;
    cmd_vel.linear.x = 0.1;
    pub_cmd_vel.publish(cmd_vel);
}
void MyTurtlesimController::turn()
{
    std::cout<<current_pose<<std::endl;
    geometry_msgs::Twist cmd_vel;
    cmd_vel.angular.z = 0.1;
    pub_cmd_vel.publish(cmd_vel);
}

void MyTurtlesimController::process()
{
    ros::Rate loop_rate(hz);
    double dist = 0;
    double bef_x = current_pose.x;
    double bef_y = current_pose.y;
    double theta = 0;
    double bef_theta = 0;
    while(ros::ok())
    {
        if (theta <= 4*M_PI/5){
            turn();
            if (bef_theta == 0){
                bef_theta = current_pose.theta;
            }

            double delta_theta = current_pose.theta - bef_theta;
            if (delta_theta < 0){
                delta_theta += 2*M_PI;
            }
            theta += delta_theta;
            bef_x = current_pose.x;
            bef_y = current_pose.y;
            bef_theta = current_pose.theta;
            dist = 0;
            std::cout << theta << std::endl;
        }
        else if (dist <= 2.0){
            go_straight();
            dist += std::sqrt(std::pow(current_pose.x - bef_x, 2)+std::pow(current_pose.y - bef_y, 2));
            bef_x = current_pose.x;
            bef_y = current_pose.y;
            bef_theta = current_pose.theta;

        }
        else{
            theta = 0;
        }
        ros::spinOnce();
        loop_rate.sleep();
    }
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "my_turtlesim_controller");
    MyTurtlesimController my_turtlesim_controller;

    my_turtlesim_controller.process();
    return 0;
}
