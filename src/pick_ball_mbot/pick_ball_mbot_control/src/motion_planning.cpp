#include <ros/ros.h>
#include <string>
#include <vector>
#include <algorithm>
#include <pick_ball_mbot_msgs/BallPositionStamp.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Twist.h>
#include <pick_ball_mbot_msgs/void_obstacle.h>
#include <pick_ball_mbot_msgs/PathPlanning.h>
#include <actionlib_msgs/GoalID.h>
#include <list>

#define LeftBoundary                200
#define RightBoundary               400
#define FilterFactor                0.2
#define NoBallDuarationTime         40
#define NoBallTurnDuarationTime     100

using namespace std;

geometry_msgs::Twist vel_msg;
uint NoBallDuaration = 0; 
uint NoBallTurnDuaration = 0; 
bool obstacle = false;
bool NoBall = false;
bool PathRequest = false;

geometry_msgs::Point PostionFilter(geometry_msgs::Point BallPosition)
{   
    static geometry_msgs::Point LastPosition;
    geometry_msgs::Point Position;

    Position.x = (1 - FilterFactor)*BallPosition.x + FilterFactor * LastPosition.x;
    Position.y = (1 - FilterFactor)*BallPosition.y + FilterFactor * LastPosition.y;
    Position.z = (1 - FilterFactor)*BallPosition.z + FilterFactor * LastPosition.z;

    LastPosition = Position;

    return Position;
}

geometry_msgs::Point CalculatePostion(vector<geometry_msgs::Point> BallPosition)
{
    double XPosition = 0;
    double YPosition = 0;
    double ZPosition = 0;
    geometry_msgs::Point Position;

    for(vector<geometry_msgs::Point>::iterator it = BallPosition.begin(); it < BallPosition.end(); it++)
    {
        XPosition += it->x;
        YPosition += it->y;
        ZPosition += it->z;
    }

    Position.x = XPosition/BallPosition.size();
    Position.y = YPosition/BallPosition.size();
    Position.z = ZPosition/BallPosition.size();

    return Position;
}

/*
* Set positions of most balls
*/
geometry_msgs::Point SetPositonGoal(const pick_ball_mbot_msgs::BallPositionStamp::ConstPtr &BallPositionStampMsg)
{
    vector<geometry_msgs::Point> BallPosition(BallPositionStampMsg->Position);
    vector<geometry_msgs::Point> LeftBalls;
    vector<geometry_msgs::Point> MidBalls;
    vector<geometry_msgs::Point> RightBalls;

    geometry_msgs::Point GoalPosition;

    size_t maxsize = 0;

    /*Divide the balls into different areas*/
    for(vector<geometry_msgs::Point>::iterator it = BallPosition.begin(); it < BallPosition.end(); it++)
    {
        if(it->x < LeftBoundary)
            LeftBalls.push_back(*it);
        else if(it->x > RightBoundary)
            RightBalls.push_back(*it);
        else
            MidBalls.push_back(*it);
    }

    maxsize = max(LeftBalls.size(), RightBalls.size());
    maxsize = max(maxsize, MidBalls.size());

    if(maxsize == LeftBalls.size() && maxsize == MidBalls.size() && maxsize == RightBalls.size())
        GoalPosition = CalculatePostion(MidBalls);

    else if(maxsize == LeftBalls.size() && maxsize == MidBalls.size())
        GoalPosition = CalculatePostion(MidBalls);

    else if(maxsize == MidBalls.size() && maxsize == RightBalls.size())
        GoalPosition = CalculatePostion(MidBalls);

    else if(maxsize == LeftBalls.size() && maxsize == RightBalls.size())
        GoalPosition = CalculatePostion(LeftBalls);

    else
    {
        if(maxsize == LeftBalls.size())
            GoalPosition = CalculatePostion(LeftBalls);

        else if(maxsize == MidBalls.size())
            GoalPosition = CalculatePostion(MidBalls);

        else 
            GoalPosition = CalculatePostion(RightBalls);
    }
    return GoalPosition;
}

/*
* Find the nearest ball
*/
geometry_msgs::Point FindNearestPosition(const pick_ball_mbot_msgs::BallPositionStamp::ConstPtr &BallPositionStampMsg)
{
    vector<geometry_msgs::Point> BallPosition(BallPositionStampMsg->Position);

    geometry_msgs::Point GoalPosition;
    uint MaxCircleRadius = 0;
    size_t MaxCircleIndex = 0;

    /*find the nearest ball*/
    vector<geometry_msgs::Point>::iterator first = BallPosition.begin();
    for(vector<geometry_msgs::Point>::iterator it = BallPosition.begin(); it < BallPosition.end(); it++)
    {
        if(it->z > MaxCircleRadius)
        {
            MaxCircleRadius = it->z;
            MaxCircleIndex = distance(first,it);
        }
    }

    GoalPosition.x = BallPosition[MaxCircleIndex].x;
    GoalPosition.y = BallPosition[MaxCircleIndex].y;
    GoalPosition.z = BallPosition[MaxCircleIndex].z;

    return GoalPosition;
}


/* 
According to the position of balls or 
if there is obstacle to publish velocity 
*/
void PosCallback(const pick_ball_mbot_msgs::BallPositionStamp::ConstPtr &BallPositionStampMsg)
{
    static geometry_msgs::Point GoalPosition; //static variable, save last position and use it as goal position 

    //accoeding to if there is ball
    if(BallPositionStampMsg->Position.empty())
    {
        NoBallDuaration++;
        if(NoBallDuaration >= NoBallDuarationTime)
        {
            NoBallDuaration = NoBallDuarationTime;
            NoBall = true;
        }
    }
    else // there is ball
    {
        NoBallDuaration = 0;
        NoBallTurnDuaration = 0;
        NoBall = false;
        PathRequest = false;
        //GoalPosition = SetPositonGoal(BallPositionStampMsg);
        GoalPosition = FindNearestPosition(BallPositionStampMsg);

        GoalPosition = PostionFilter(GoalPosition);
    }
    

    if(!NoBall) //there is ball
    {
        if(obstacle) //there is obstacle
        {
            vel_msg.linear.x = 0.0;
            vel_msg.angular.z = 0.8;
        }
        else //no obstacle
        {
            vel_msg.angular.z = -0.005 * (GoalPosition.x - 320);
            vel_msg.linear.x = 0.4;
        }
    }
    else // No ball
    {
        NoBallTurnDuaration++;
        if(NoBallTurnDuaration >= NoBallTurnDuarationTime)
        {
            NoBallTurnDuaration = NoBallTurnDuarationTime;
            PathRequest = true;
        }

        if(!PathRequest) // NoBall is true and PahthRequest is false
        {
            vel_msg.linear.x = 0.0;
            vel_msg.angular.z = 0.8;
        }
    }
}

// obstacle 请求处理函数
bool handle_function(pick_ball_mbot_msgs::void_obstacle::Request &req,
					 pick_ball_mbot_msgs::void_obstacle::Response &res)
{

    if(req.obstacle)
        obstacle = true;
    else
        obstacle = false;

	res.result = true;

	return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "motion_planning");
    ros::NodeHandle nh;

    ros::Subscriber BallPos_sub = nh.subscribe("/Ball/Position", 10, &PosCallback);

    ros::Publisher VelMsg_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::Publisher PathPlanningCancle_Pub =  nh.advertise<actionlib_msgs::GoalID>("move_base/cancel", 1);

	ros::ServiceServer void_obstacle_service = nh.advertiseService("void_obstacle", handle_function);
    
    ros::ServiceClient PathPlanningRequestClient = nh.serviceClient<pick_ball_mbot_msgs::PathPlanning>("PathPlanning");


    pick_ball_mbot_msgs::PathPlanning srv;
    actionlib_msgs::GoalID first_goal;

    ros::Rate loop_rate(100); 

    while (nh.ok())
    {
        if(PathRequest)// 
        {
            srv.request.Request = true;
            if (PathPlanningRequestClient.call(srv))//接受应答
            {
                ROS_INFO("Response from server: %d", srv.response.Result);
            }
            else
            {
                ROS_ERROR("Failed to call service Service_demo");
            }
        }
        else
        {
            PathPlanningCancle_Pub.publish(first_goal); //Cancel path plannig 
            VelMsg_pub.publish(vel_msg);
        }
            
        ros::spinOnce();
        loop_rate.sleep();
    }
}