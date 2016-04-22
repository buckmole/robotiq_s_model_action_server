#include "robotiq_action_server/robotiq_s_model_action_server.h"

namespace
{
  // Defines a default for the s model
  robotiq_action_server::SModelGripperParams s_defaults()
  {
    robotiq_action_server::SModelGripperParams params;
    params.min_rad_ = 0.049529;
    params.max_rad_ = 0.932808;

    params.min_effort_ = 40.0; // This is a guess. Could not find data with quick search.
    params.max_effort_ = 100.0;

    return params;
  }
}

int main(int argc, char** argv)
{
  // Can be renamed with standard ROS-node launch interface
  ros::init(argc, argv, "gripper_action_server");
  
  // Private Note Handle for retrieving parameter arguments to the server
  ros::NodeHandle private_nh("~");

  std::string gripper_name;
  private_nh.param<std::string>("gripper_name", gripper_name, "gripper");

  // Fill out S-Model Params
  robotiq_action_server::SModelGripperParams cparams = s_defaults();
  
  // Min because fingers can push forward before the mechanical stops are reached
  private_nh.param<double>("min_rad", cparams.min_rad_, cparams.min_rad_);
  private_nh.param<double>("max_rad", cparams.max_rad_, cparams.max_rad_);
  private_nh.param<double>("min_effort", cparams.min_effort_, cparams.min_effort_);
  private_nh.param<double>("max_effort", cparams.max_effort_, cparams.max_effort_);

  ROS_INFO("Initializing Robotiq action server for gripper: %s", gripper_name.c_str());

  // The name of the gripper -> this server communicates over name/inputs and name/outputs
  robotiq_action_server::SModelGripperActionServer gripper (gripper_name, cparams);

  ROS_INFO("Robotiq action-server spinning for gripper: %s", gripper_name.c_str());
  ros::spin();
}
