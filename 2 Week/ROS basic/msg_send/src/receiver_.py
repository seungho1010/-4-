#!/usr/bin/env python

import rospy
from std_msgs.msg import String

name = "receiver"
sub_topic = "msg_to_receiver"

def callback(data):
    rospy.loginfo("I heard %s", data.data)

rospy.init_node(name)
rospy.Subscriber(sub_topic, String, callback)

rospy.spin()