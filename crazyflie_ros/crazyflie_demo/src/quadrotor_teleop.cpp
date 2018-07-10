#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Twist.h>

class TeleopImu
{

public:
  TeleopImu();
  ros::NodeHandle n;  
  ros::Subscriber sub;
  ros::Publisher  pub; 
  
  void callBack(const sensor_msgs::Imu::ConstPtr& imu);   

  double linear_x, linear_y, linear_z , angular_z ,angular_y ;  
  
};

  TeleopImu::TeleopImu()
  {
    sub = n.subscribe<sensor_msgs::Imu>("imu", 10, &TeleopImu::callBack, this);
    pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 10);
  }
  
  void TeleopImu::callBack(const sensor_msgs::Imu::ConstPtr& imu)   
  {
    geometry_msgs::Twist velocity_;  
 
    ros::Rate loop_rate(100);

    while (1)
    {
      linear_z = imu->linear_acceleration.z;
      linear_x = imu->linear_acceleration.x;
      linear_y = imu->linear_acceleration.x;
      angular_y = imu->angular_velocity.y;

      if(linear_x<-4 || linear_x>4) {  //linear_z<9.1 &&  //&& angular_y<-4){
 
         velocity_.linear.z = 0; 
         velocity_.linear.x = 0;       
         velocity_.linear.y = 0; 
         velocity_.angular.z = 0;
         pub.publish(velocity_);
         break; 
       }  
                    
      velocity_.linear.z =47400; //44050
      velocity_.linear.x =5;      //8
      velocity_.linear.y = 0;  //1  //0.3
      velocity_.angular.z =0 ;   //2//3

      pub.publish(velocity_);
      ros::spin();      //ros::spinOnce();        
      loop_rate.sleep();
    }
     
    while(1);
  }


int main(int argc, char **argv)    
{                                  
  ros::init(argc, argv, "quadrotor_teleop");
  TeleopImu teleop;
  ros::spin();                      
}
