// Generated by gencpp from file pick_ball_mbot_msgs/void_obstacleResponse.msg
// DO NOT EDIT!


#ifndef PICK_BALL_MBOT_MSGS_MESSAGE_VOID_OBSTACLERESPONSE_H
#define PICK_BALL_MBOT_MSGS_MESSAGE_VOID_OBSTACLERESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace pick_ball_mbot_msgs
{
template <class ContainerAllocator>
struct void_obstacleResponse_
{
  typedef void_obstacleResponse_<ContainerAllocator> Type;

  void_obstacleResponse_()
    : result(false)  {
    }
  void_obstacleResponse_(const ContainerAllocator& _alloc)
    : result(false)  {
  (void)_alloc;
    }



   typedef uint8_t _result_type;
  _result_type result;





  typedef boost::shared_ptr< ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator> const> ConstPtr;

}; // struct void_obstacleResponse_

typedef ::pick_ball_mbot_msgs::void_obstacleResponse_<std::allocator<void> > void_obstacleResponse;

typedef boost::shared_ptr< ::pick_ball_mbot_msgs::void_obstacleResponse > void_obstacleResponsePtr;
typedef boost::shared_ptr< ::pick_ball_mbot_msgs::void_obstacleResponse const> void_obstacleResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace pick_ball_mbot_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'pick_ball_mbot_msgs': ['/home/hyh/mc_ws/src/pick_ball_mbot/pick_ball_mbot_msgs/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "eb13ac1f1354ccecb7941ee8fa2192e8";
  }

  static const char* value(const ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xeb13ac1f1354ccecULL;
  static const uint64_t static_value2 = 0xb7941ee8fa2192e8ULL;
};

template<class ContainerAllocator>
struct DataType< ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "pick_ball_mbot_msgs/void_obstacleResponse";
  }

  static const char* value(const ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool result\n\
";
  }

  static const char* value(const ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.result);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct void_obstacleResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::pick_ball_mbot_msgs::void_obstacleResponse_<ContainerAllocator>& v)
  {
    s << indent << "result: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.result);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PICK_BALL_MBOT_MSGS_MESSAGE_VOID_OBSTACLERESPONSE_H
