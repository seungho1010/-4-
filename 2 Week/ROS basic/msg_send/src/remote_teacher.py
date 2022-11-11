#!/usr/bin/env python

import rospy
import time
from msg_send.msg import my_msg
from std_msgs.msg import String

def call_back(data):
    name_ = data.last_name + ' ' + data.first_name
    current_time = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())
    print_ = 'Good morning' + name_ + current_time

    pub.publish(print_)

rospy.init_node('remote_teacher', anonymous=True)

pub = rospy.Publisher('msg_from_xycar', String, queue_size=1)
sub = rospy.Subscriber('msg_to_xycar', my_msg, call_back)

rospy.spin()