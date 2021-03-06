#include <ros/ros.h> 
#include <move_base_msgs/MoveBaseAction.h> 
#include <actionlib/client/simple_action_client.h> 
#include "geometry_msgs/PoseWithCovarianceStamped.h"    
#include "std_msgs/String.h"
 
using namespace std;
 
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient; 
 
#define GOHOME "HOME"
#define GODRAMING "DRAMING"
 
bool Callback_flag = false;
string msg_str = "";
 
/*******************************默认amcl初始点******************************************/
typedef struct _POSE
{
  double X;
  double Y;
  double Z;
  double or_x;
  double or_y;
  double or_z;
  double or_w;
} POSE;
 
POSE pose2 = {-8.15833854675, 3.15512728691, 0.0,  0.0, 0.0, -0.740479961141, 0.672078438241};
POSE pose1 = {-0.484616458416, 2.13149046898, 0.0,  0.0, 0.0, -0.749884700297, 0.661568542375};
POSE pose3 = {0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0};
POSE pose4 = {0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0};
 
void setHome( ros::Publisher pub)
{
    geometry_msgs::PoseWithCovarianceStamped msg_poseinit;
    msg_poseinit.header.frame_id = "map";
    msg_poseinit.header.stamp = ros::Time::now();
    msg_poseinit.pose.pose.position.x = -0.644479990005;
    msg_poseinit.pose.pose.position.y = 2.2030518055;
    msg_poseinit.pose.pose.position.z = 0;
    msg_poseinit.pose.pose.orientation.x = 0.0;
    msg_poseinit.pose.pose.orientation.y = 0.0;
    msg_poseinit.pose.pose.orientation.z = -0.746261929753;
    msg_poseinit.pose.pose.orientation.w = 0.665652410949;
// 　　<br>　　/×因为ros话题原理本身的问题，Setting pose 需要按照以下发送×/<br>
    pub.publish(msg_poseinit);
    ros::Duration(1.0).sleep();
    pub.publish(msg_poseinit);
    ros::Duration(1.0).sleep();
    pub.publish(msg_poseinit);
    ros::Duration(1.0).sleep();
}
 
void setGoal(POSE pose)
{
     //tell the action client that we want to spin a thread by default 
    MoveBaseClient ac("move_base", true); 
       
    //wait for the action server to come up 
    while(!ac.waitForServer(ros::Duration(5.0))){ 
        ROS_WARN("Waiting for the move_base action server to come up"); 
    } 
       
    move_base_msgs::MoveBaseGoal goal; 
       
    //we'll send a goal to the robot to move 1 meter forward 
    goal.target_pose.header.frame_id = "map"; 
    goal.target_pose.header.stamp = ros::Time::now(); 
    
    goal.target_pose.pose.position.x = pose.X;
    goal.target_pose.pose.position.y = pose.Y; 
    goal.target_pose.pose.position.z = pose.Z;  
    goal.target_pose.pose.orientation.x = pose.or_x;
    goal.target_pose.pose.orientation.y = pose.or_y;
    goal.target_pose.pose.orientation.z = pose.or_z;
    goal.target_pose.pose.orientation.w = pose.or_w;  
     
    ROS_INFO("Sending goal"); 
     
    ac.sendGoal(goal); 
       
    ac.waitForResult(); 
       
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) 
      ROS_INFO("it is successful"); 
     else 
       ROS_ERROR("The base failed  move to goal!!!");  
}
 
void poseCallback(const std_msgs::String::ConstPtr &msg)
{
     ROS_INFO_STREAM("Topic is Subscriber ");
     std::cout<<"get topic text: " << msg->data << std::endl;
      
     Callback_flag = true;
     msg_str = msg->data;
}  
 
int main(int argc, char** argv)
{ 
  ros::init(argc, argv, "base_pose_control"); 
  ros::NodeHandle nh;
  ros::Publisher pub_initialpose = nh.advertise<geometry_msgs::PoseWithCovarianceStamped>("/initialpose", 10);
  ros::Subscriber sub = nh.subscribe("/base/pose_topic",10,poseCallback); 
 
  //ros::Rate rate_loop(10);
 
  setHome(pub_initialpose);
   
 // setGoal(pose1);
  while(ros::ok())
  {
      if(Callback_flag == true)
      {
        Callback_flag = false;
 
        if(msg_str == GOHOME)
        {
            msg_str = "";
            setGoal(pose1);
        }
        else  if(msg_str == GODRAMING)
        {
            msg_str = "";
            setGoal(pose2);
        }
        else
        {
 
        }
      }
 
      ros::spinOnce();
     // rate_loop.sleep();
  }
   
 
  return 0; 
} 