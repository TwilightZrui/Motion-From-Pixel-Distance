#include <iostream>
#include "ros/ros.h"
#include <geometry_msgs/PoseStamped.h>

center_goal = geometry_msgs::PoseStamped();

void chatterCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    center_goal.header.stamp = ros::Time::now(); 
    center_goal.header.frame_id = "map";  //有没有~需要根据代码里的其他部分看。
    center_goal.pose.pose.position.x = msg.pose.pose.position.x;  //把中心坐标的x y z 赋给导航目标的x y z 
    center_goal.pose.pose.position.y = msg.pose.pose.position.y;
    center_goal.pose.pose.position.z = 0.0;
    center_goal.pose.pose.orientation.x =  0.0;
    center_goal.pose.pose.orientation.y =  0.0;
    center_goal.pose.pose.orientation.z =  0.0;
    center_goal.pose.pose.orientation.w =  1.0;
}
 
int main(int argc, char **argv)
{
    ros::init(argc,argv,"spark2center");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("你的消息名称",1,chatterCallback);
    ros::Publisher pub = n.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1);
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
        pub.publish(center_goal);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}