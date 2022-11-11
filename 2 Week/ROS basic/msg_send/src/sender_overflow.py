#!/usr/bin/env python

import rospy
from std_msgs.msg import Int32

rospy.init_node('sender')

pub = rospy.Publisher('my_topic', Int32, queue_size=2)

rate = rospy.Rate(1000)
count = 1

start_time = rospy.get_rostime()

while pub.get_num_connections() == 0:
    continue

while not rospy.is_shutdown():
    pub.publish(count)
    count = count + 1
    rate.sleep()