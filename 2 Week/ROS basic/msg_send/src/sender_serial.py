#!/usr/bin/env python

import rospy
from std_msgs.msg import Int32

rospy.init_node('sender_serial')

pub = rospy.Publisher('my_topic', Int32, queue_size=10)

rate = rospy.Rate(1)
count = 1

end_number = rospy.get_param('~end_number', 15)
start_time = rospy.get_rostime()

while pub.get_num_connections() == 0:
    
    now = rospy.get_rostime()
    if now.secs - start_time.secs > 1:
        print "Num of connections: ", pub.get_num_connections()
        start_time = now

    if rospy.is_shutdown():
        break

print "Publish Start"

while not rospy.is_shutdown():
    if count <= end_number:
        pub.publish(count)
        count = count + 1
    else:
        break
    rate.sleep()