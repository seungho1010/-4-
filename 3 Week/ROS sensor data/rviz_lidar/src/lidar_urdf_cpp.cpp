#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "sensor_msgs/Range.h"

#include <iostream>
using namespace std;

// /scan topic -> /scan1, /scan2, /scan3, /scan4

static ros::Publisher pub1;
static ros::Publisher pub2;
static ros::Publisher pub3;
static ros::Publisher pub4;

static sensor_msgs::Range range;

void msgCallback(const sensor_msgs::LaserScan& laserscan_){

    range.header.frame_id = "front";
    range.header.stamp = ros::Time::now();
    range.range = laserscan_.ranges[90];
    pub1.publish(range);   

    range.header.frame_id = "right";
    range.header.stamp = ros::Time::now();
    range.range = laserscan_.ranges[180];
    pub2.publish(range);  

    range.header.frame_id = "back";
    range.header.stamp = ros::Time::now();
    range.range = laserscan_.ranges[270];
    pub3.publish(range);  

    range.header.frame_id = "left";
    range.header.stamp = ros::Time::now();
    range.range = laserscan_.ranges[0];
    pub4.publish(range);  
    ros::Duration(0.5).sleep();
}

int main(int argc, char **argv){

    ros::init(argc, argv, "laser_cpp");
    ros::NodeHandle nh;

    pub1 = nh.advertise<sensor_msgs::Range>("scan1", 1);
    pub2 = nh.advertise<sensor_msgs::Range>("scan2", 1);
    pub3 = nh.advertise<sensor_msgs::Range>("scan3", 1);
    pub4 = nh.advertise<sensor_msgs::Range>("scan4", 1);

    range.radiation_type = sensor_msgs::Range::ULTRASOUND;
    range.min_range = 0.02;
    range.max_range = 2.0;
    range.field_of_view = (30.0 / 180.0) * 3.14;

    ros::Subscriber sub = nh.subscribe("/scan", 1, msgCallback);
    ros::spin();
    return 0;
}

// https://www.intorobotics.com/how-to-use-sensor_msgs-range-ros-for-multiple-sensors-with-rosserial/