/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"

std::shared_ptr<frc::Joystick> Elevator::JOY_ele;

std::shared_ptr<rev::CANSparkMax> Elevator::CSM_NEO_0;
std::shared_ptr<rev::CANSparkMax> Elevator::CSM_NEO_1;
std::shared_ptr<rev::CANSparkMax> Elevator::CSM_RED;

std::shared_ptr<rev::CANEncoder> Elevator::CE_1;
std::shared_ptr<rev::CANEncoder> Elevator::CE_2;

std::shared_ptr<frc::SpeedControllerGroup> Elevator::SCG_main;

Elevator::Elevator() : Subsystem("ExampleSubsystem") {
  JOY_ele.reset(new frc::Joystick(1));

  CSM_NEO_0.reset(new rev::CANSparkMax(4,rev::CANSparkMax::MotorType::kBrushless));
  CSM_NEO_1.reset(new rev::CANSparkMax(6,rev::CANSparkMax::MotorType::kBrushless));
  CSM_RED.reset(new rev::CANSparkMax(8,rev::CANSparkMax::MotorType::kBrushed));

  CSM_NEO_0->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  CSM_NEO_1->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  CE_1.reset(new rev::CANEncoder(*CSM_NEO_0));
  CE_2.reset(new rev::CANEncoder(*CSM_RED));

  SCG_main = std::make_shared<frc::SpeedControllerGroup>(*CSM_NEO_0,*CSM_NEO_1);
}

void Elevator::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}


void Elevator::Periodic(){
  if(JOY_ele -> GetRawButtonPressed(4)){
    SCG_main -> Set(0.5);
  }
  else if(JOY_ele -> GetRawButtonPressed(5)){
    SCG_main -> Set(-0.5);
  }
  else 
  {
    SCG_main -> Set(0);
  }
}
