#!/usr/bin/env python

import rospy
import time
from std_msgs.msg import Int32

def do_job(count):
    for i in range(0, count):
        k = i + 1
        pub.publish(k)

def list_append_time():
    start.append(start_time)
    end.append(end_time)
    sleep.append(sleep_time)


rospy.init_node('teacher')
pub = rospy.Publisher('msg_to_students', Int32, queue_size=0)
rate = rospy.Rate(5)

while not rospy.is_shutdown():
    start = []
    end = []
    sleep = []

    num = input("input count number >")

    rate.sleep()

    total_start = time.time()

    for j in range(0, 5):
        start_time = time.time()
        do_job(num)
        end_time = time.time()

        rate.sleep()
        sleep_time = time.time()
        list_append_time()

        total_end = time.time()

    for t in range(0, 5):
        sleep[t] = sleep[t] - end[t]
        end[t] = end[t] - start[t]

    for result in range(0, 5):
        print "spend time > ", round(end[result], 4), 's'
        print "sleep time > ", round(sleep[result], 4), 's, 1 cycle time > ', round(end[result], 4) + round(sleep[result], 4), 's'

    print "------------------------------"
    print "total time > ", round((total_end - total_start), 4), 's'
    print "------------------------------\n\n"

    end_flag = input("Try again? ( Yes : 1 / No : 0 )")
    if end_flag == 0:
        break
    elif end_flag == 1:
        continue
    else:
        end_flag = input("Please enter 1 or 0")