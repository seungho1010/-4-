#!/usr/bin/env python

import rospy
from std_msgs.msg import Int32

def callback(msg):
    rospy.loginfo("callback is being processed")
    rospy.sleep(5)
    print msg.data
    
rospy.init_node('receiver')
p_queue_size = rospy.get_param('~queue_size_', 10)
rospy.Subscriber('my_topic', Int32, callback, queue_size=p_queue_size)
rospy.spin()