#!/usr/bin/env python

"""
imu_data.txt -> IMU Topic
"""

import rospy, math, os, rospkg
from sensor_msgs.msg import Imu

from tf.transformations import euler_from_quaternion, quaternion_from_euler

degrees2rad = float(math.pi)/float(180.0)
rad2degrees = float(180.0)/float(math.pi)

rospy.init_node("imu_generator")

pub = rospy.Publisher('imu', Imu, queue_size=1)

data = []

path = rospkg.RosPack().get_path('rviz_imu') + "/src/imu_data.txt"
f = file(path, "r")
lines = f.readlines()

for line in lines:
  tmp = line.split(",")
  extract = []
  for i in tmp:
    extract.append(float(i.split(":")[1]))
  data.append(extract)

imuMsg = Imu()
imuMsg.header.frame_id = "map"

r = rospy.Rate(10)
seq = 0

while not rospy.is_shutdown():
  if seq < len(data):
    msg_data = quaternion_from_euler(data[seq][0], data[seq][1], data[seq][2])

    imuMsg.orientation.x = msg_data[0]
    imuMsg.orientation.y = msg_data[1]
    imuMsg.orientation.z = msg_data[2]
    imuMsg.orientation.w = msg_data[3]

    imuMsg.header.stamp = rospy.Time.now()
    imuMsg.header.seq = seq
    seq += 1
    
    pub.publish(imuMsg)
    r.sleep()
  else:
    continue