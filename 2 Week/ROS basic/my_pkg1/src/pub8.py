#!/usr/bin/env python

# eight-figure step
import rospy
import math
from geometry_msgs.msg import Twist

rospy.init_node('my_node', anonymous=True)
# anonymous = True -> Add a random number after the node
pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)

turn_rate = 5
radius_ = 40

left_turn = Twist()
left_turn.linear.x = 2.0
left_turn.linear.y = 0.0
left_turn.linear.z = 0.0
left_turn.angular.x = 0.0
left_turn.angular.y = 0.0
left_turn.angular.z = (180 / math.pi) / radius_

right_turn = Twist()
right_turn.linear.x = 2.0
right_turn.linear.y = 0.0
right_turn.linear.z = 0.0
right_turn.angular.x = 0.0
right_turn.angular.y = 0.0
right_turn.angular.z = -1 * (180 / math.pi) / radius_

# 1Hz
rate = rospy.Rate(1)

# for turn change
turn_flag = 0 
while not rospy.is_shutdown():   
    if turn_flag < turn_rate:
	pub.publish(left_turn)
	# print("left_turn")
	turn_flag += 1
    elif turn_flag < turn_rate*2:
	pub.publish(right_turn)
	# print("right_turn")
	turn_flag += 1
	if turn_flag == turn_rate*2:
	    turn_flag = 0
    # for 1Hz
    rate.sleep()
