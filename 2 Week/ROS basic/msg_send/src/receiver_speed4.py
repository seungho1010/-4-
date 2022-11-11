#!/usr/bin/env python

import rospy
from std_msgs.msg import String

name = "receiver4"

def callback(data):
    current_time = rospy.get_rostime()
    arrival_data = str(data.data).split(":")

    time_diff = ((float(str(current_time)) - float(arrival_data[1])) / 1000000000)
    string_size = len(arrival_data[0])
    
    rospy.loginfo(name)

    print_data(string_size, time_diff)
    cal_speed(string_size, time_diff)

def cal_speed(string_size, time_diff):
    try:
        speed_ = float(string_size / 1000000) / time_diff
        print_ = "Speed : {0:0.2f}MB/s".format(speed_)
        rospy.loginfo(print_)
    except ZeroDivisionError:
        rospy.loginfo("Too Fast")

def print_data(string_size, time_diff):
    print_ = "Data size: {0:d}MB, {1:0.5f}s".format(int(string_size / 1000000), time_diff)
    rospy.loginfo(print_)
    
rospy.init_node(name, anonymous=True)
rospy.loginfo("init")
rospy.Subscriber('long_string', String, callback)
rospy.spin()
