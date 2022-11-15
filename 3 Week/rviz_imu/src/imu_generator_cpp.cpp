#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "ros/package.h"
#include "tf2/LinearMath/Quaternion.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// imu_data.txt -> Imu topic

int main(int argc, char **argv){
    ros::init(argc, argv, "imu_generator");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<sensor_msgs::Imu>("imu", 1);
    ros::Rate loop_rate(10);

    sensor_msgs::Imu imu;
    imu.header.frame_id = "map";
    imu.header.seq = 0;

    string package_path = ros::package::getPath("rviz_imu");
    string file_name = package_path + "/src/imu_data.txt";
    string line;
    ifstream file(file_name);

    int seq = 0;
    float roll, pitch, yaw;
    while(ros::ok())
    {
        if(file.is_open()){
            if(getline(file, line)){
                char separator = ',';
                istringstream line_(line);
                string temp;
                int count = 0;
                while(getline(line_, temp, separator)) {
                    cout << temp << endl;
                    switch (count)
                    {
                        case 0:
                            roll = stof(temp.substr(7));
                            count += 1;
                            break;
                        case 1:
                            pitch = stof(temp.substr(9));
                            count += 1;
                            break;
                        case 2:
                            yaw = stof(temp.substr(7));
                            count = 0;
                            break;
                        default:
                            break;   
                    }
                }
            }
            tf2::Quaternion quat;
            quat.setRPY(roll, pitch, yaw);

            imu.header.seq += 1;
            imu.header.stamp = ros::Time::now();
            imu.orientation.x = quat.getX();
            imu.orientation.y = quat.getY();
            imu.orientation.z = quat.getZ();
            imu.orientation.w = quat.getW();
            pub.publish(imu);
            
            loop_rate.sleep();
        }

    }   
    file.close();
    return 0;
}