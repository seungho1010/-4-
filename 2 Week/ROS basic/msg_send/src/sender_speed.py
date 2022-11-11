#!/usr/bin/env python

import rospy
from std_msgs.msg import String

rospy.init_node('sender', anonymous=True)
pub = rospy.Publisher('long_string', String, queue_size=1)

hello_str = String()
rate = rospy.Rate(1)

data_size = rospy.get_param('~data_size_', 5) # unit M byte
pub_size = 1000000 * data_size

my_string = ""

for i in range(pub_size):
    my_string += "#"

while not rospy.is_shutdown():
    hello_str.data = my_string + ":" + str(rospy.get_rostime())
    pub.publish(hello_str)
    # rospy.loginfo(str(hello_str.data).split(":")[1])
    rate.sleep()