#include <stdio.h>
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <control_msgs/FollowJointTrajectoryAction.h>

bool flag = false;

void print_start(const control_msgs::FollowJointTrajectoryActionGoal& start_msg) {
	std::cout<<"start it"<<std::endl;
	flag = true;
}

void print_stop(const control_msgs::FollowJointTrajectoryActionResult& stop_msg) {
	std::cout<<"stop it"<<std::endl;
	flag = false;
}

int main(int ac, char* av[])
{
	ros::init(ac, av, "print_path");
	ros::NodeHandle nh;

	tf::TransformListener listener;

	ros::Subscriber start_sub = nh.subscribe("/seven_dof_arm_joint_controller/follow_joint_trajectory/goal", 1000, &print_start);
	ros::Subscriber stop_sub = nh.subscribe("/seven_dof_arm_joint_controller/follow_joint_trajectory/result", 1000, &print_stop);
	
	tf::StampedTransform transform;

	while(nh.ok())
	{
		ros::spinOnce();
		ros::Duration(0.2).sleep();
		if(flag) {
			listener.lookupTransform("/grasping_frame", "/base_link", ros::Time(0), transform);
			std::cout<<transform.getOrigin().z()<<std::endl<<transform.getRotation().z()<<std::endl;
			std::cout<<"got it"<<std::endl;
		}		else
			std::cout<<"-"<<std::endl;
	}
}
