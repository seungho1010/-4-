#!/usr/bin/env python

import rospy
from std_msgs.msg import String

name = "publisher"
pub_topic = "start_ctl"

rospy.init_node(name)
pub = rospy.Publisher(pub_topic, String, queue_size=1)

rate = rospy.Rate(2)
hello_str = String()

rospy.sleep(1)

sq = ["first", "second", "third", "fourth"]

i = 0
while not rospy.is_shutdown():
    pub_msg = String()
    pub_msg.data = sq[i] + ":go"
    pub.publish(pub_msg)
    rate.sleep()
    if i < 3:
        i = i + 1
    else:
        i = 0