/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"

std::shared_ptr<frc::Joystick> Elevator::JOY_ele;
std::shared_ptr<frc::XboxController> Elevator::xbox;
std::shared_ptr<frc::Joystick> Elevator:: joy2;

std::shared_ptr<rev::CANSparkMax> Elevator::CSM_NEO_0;
std::shared_ptr<rev::CANSparkMax> Elevator::CSM_NEO_1;
std::shared_ptr<rev::CANSparkMax> Elevator::CSM_RED;

std::shared_ptr<rev::CANEncoder> Elevator::CE_1;
std::shared_ptr<rev::CANEncoder> Elevator::CE_2;

std::shared_ptr<frc::SpeedControllerGroup> Elevator::SCG_main;

std::shared_ptr<WPI_VictorSPX> Elevator::VIC_Car_left;
std::shared_ptr<WPI_VictorSPX> Elevator::VIC_Car_right;

std::shared_ptr<frc::SpeedControllerGroup> Elevator::carrige; 


Elevator::Elevator() : Subsystem("ExampleSubsystem") {
  JOY_ele.reset(new frc::Joystick(0));
  xbox.reset(new frc::XboxController(2));
  joy2.reset(new frc::Joystick(1));

  CSM_NEO_0.reset(new rev::CANSparkMax(3,rev::CANSparkMax::MotorType::kBrushless));
  CSM_NEO_1.reset(new rev::CANSparkMax(2,rev::CANSparkMax::MotorType::kBrushless));
  CSM_RED.reset(new rev::CANSparkMax(8,rev::CANSparkMax::MotorType::kBrushed));

  CSM_NEO_0->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  CSM_NEO_1->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  // CSM_NEO_0->SetInverted(true);

  CE_1.reset(new rev::CANEncoder(*CSM_NEO_0));
  CE_2.reset(new rev::CANEncoder(*CSM_RED));

  SCG_main = std::make_shared<frc::SpeedControllerGroup>(*CSM_NEO_0,*CSM_NEO_1);

  // Victor right 23  victor left 27 
  VIC_Car_left.reset(new WPI_VictorSPX(27));
  VIC_Car_right.reset(new WPI_VictorSPX(23));
  
  VIC_Car_right->SetInverted(true);

  carrige = std::make_shared<frc::SpeedControllerGroup>(*VIC_Car_left, *VIC_Car_right);
}

void Elevator::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}


void Elevator::Periodic(){
  double spd = 0.2;
  if(joy2 -> GetRawButton(11)){
    SCG_main -> Set(spd);
  }
  else if(joy2 -> GetRawButton(12)){
    SCG_main -> Set(-spd);
  } 
  else 
  {
    SCG_main -> Set(-0.05);
  }

  double xspd = JOY_ele->GetThrottle();

  if(JOY_ele->GetRawButton(1)) {
    carrige->Set(xspd);
  }
  else
  {
    carrige->Set(0);
  }
  printf("speed: %.2f\n", xspd); 
}

double Elevator::limit(double x) {
  if( std::abs(x) < 0.3) {
    return 0;
  } else {
    return x;
  }
}