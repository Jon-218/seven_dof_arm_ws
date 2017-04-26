#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/tf.h>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "tf_test");
	ros::NodeHandle nh;

	tf::TransformListener listerner;
	ros::Rate rate(150);

	//while (nh.ok())
	//{
		tf::StampedTransform transform;
		try{
			listerner.lookupTransform( "/base_link", "/elbow_roll_link", ros::Time(0), transform);
		}
		catch (tf::TransformException ex) {
			ROS_ERROR("%s", ex.what());
			ros::Duration(1.0).sleep();
		}
		
		tf::Vector3 pose_origin(0, 0, 0);
		tf::Vector3 pose_new = transform.operator*(pose_origin);
		std::cout<<pose_new.x()<<":"<<pose_new.y()<<":"<<pose_new.z()<<std::endl;
	//}

}
