#!/usr/bin/env python

import rospy
from std_msgs.msg import String

name = "third"
pub_topic = "msg_to_receiver"
sub_topic = "start_ctl"

OK = None
hello_str = String()

def callback(data):
    global OK
    OK = str(data.data)
    d = OK.split(":")

    if (len(d) == 2) and (d[0] == name) and (d[1] == "go"):
        hello_str.data = "my name is " + name
        pub.publish(hello_str)

rospy.init_node(name)

pub = rospy.Publisher(pub_topic, String, queue_size=1)
sub = rospy.Subscriber(sub_topic, String, callback)

rospy.spin()