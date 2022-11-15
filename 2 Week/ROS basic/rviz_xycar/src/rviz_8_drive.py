#! /usr/bin/env python

import rospy
import time
from xycar_motor.msg import xycar_motor

motor_cotrol = xycar_motor()

rospy.init_node('driver')

pub = rospy.Publisher('xycar_motor', xycar_motor, queue_size=1)

def motor_pub(angle, speed):
    global pub
    global motor_control

    motor_cotrol.angle = angle
    motor_cotrol.speed = speed

    pub.publish(motor_cotrol)

speed = 3

# 
angles = [-50, 0, 50, 0]
num_rep = [40, 30, 40, 30]
mode = len(angles)

counter = 0
current_mode = 0

while not rospy.is_shutdown():
    
    if counter < num_rep[current_mode]:
        motor_pub(angles[current_mode], speed)
        time.sleep(0.1)
        counter += 1
    else:
        
        current_mode += 1
        if current_mode >= mode:
            current_mode = 0
        counter = 0
        motor_pub(angles[current_mode], speed)
        time.sleep(0.1)
        counter += 1