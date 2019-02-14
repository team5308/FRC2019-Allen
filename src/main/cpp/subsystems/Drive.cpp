/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drive.h"

std::shared_ptr<frc::Joystick> Drive::JOY;

std::shared_ptr<rev::CANSparkMax> Drive::CSM_NEO_LEFT;
std::shared_ptr<rev::CANSparkMax> Drive::CSM_CIM_LEFT;
std::shared_ptr<WPI_TalonSRX>     Drive::TAL_CIM_LEFT;

std::shared_ptr<rev::CANSparkMax> Drive::CSM_NEO_RIGHT;
std::shared_ptr<rev::CANSparkMax> Drive::CSM_CIM_RIGHT;
std::shared_ptr<WPI_TalonSRX>     Drive::TAL_CIM_RIGHT;

std::shared_ptr<frc::SpeedControllerGroup> Drive::SCG_LEFT;
std::shared_ptr<frc::SpeedControllerGroup> Drive::SCG_RIGHT;

std::shared_ptr<frc::DifferentialDrive> Drive::DIFF;

Drive::Drive() : Subsystem("ExampleSubsystem") {
  JOY.reset(new frc::Joystick(1));

  CSM_NEO_LEFT.reset(new rev::CANSparkMax(6,rev::CANSparkMax::MotorType::kBrushless));
  CSM_CIM_LEFT.reset(new rev::CANSparkMax(7,rev::CANSparkMax::MotorType::kBrushed));
  TAL_CIM_LEFT.reset(new WPI_TalonSRX(21));

  CSM_NEO_RIGHT.reset(new rev::CANSparkMax(4,rev::CANSparkMax::MotorType::kBrushless));
  CSM_CIM_RIGHT.reset(new rev::CANSparkMax(5,rev::CANSparkMax::MotorType::kBrushed));
  TAL_CIM_RIGHT.reset(new WPI_TalonSRX(25)); 

  SCG_LEFT = std::make_shared<frc::SpeedControllerGroup>(*CSM_CIM_LEFT,*TAL_CIM_LEFT);
  SCG_RIGHT = std::make_shared<frc::SpeedControllerGroup>(*CSM_CIM_RIGHT,*TAL_CIM_RIGHT);

  DIFF.reset(new frc::DifferentialDrive(*SCG_LEFT,*SCG_RIGHT));
}

void Drive::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

inline double abs(double x){
  if(x < 0){
    return -x;
  }else{
    return x;
  }
}

double suoqu(double x){
  if(x < 0.14){
    return 0.0;
  }else{
    return x;
  }
}

void Drive::Periodic(){
  DIFF -> ArcadeDrive(suoqu(JOY -> GetY()), suoqu(JOY -> GetX()));
}