/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"

std::shared_ptr<rev::CANSparkMax> Elevator::CSM_NEO_0;
std::shared_ptr<rev::CANSparkMax> Elevator::CSM_NEO_1;
std::shared_ptr<rev::CANSparkMax> Elevator::CSM_RED;

std::shared_ptr<frc::SpeedControllerGroup> Elevator::SCG_main;

Elevator::Elevator() : Subsystem("ExampleSubsystem") {
  CSM_NEO_0.reset(new rev::CANSparkMax(1,rev::CANSparkMax::MotorType::kBrushless));
  CSM_NEO_1.reset(new rev::CANSparkMax(2,rev::CANSparkMax::MotorType::kBrushless));
  CSM_RED.reset(new rev::CANSparkMax(3,rev::CANSparkMax::MotorType::kBrushed));

  CSM_NEO_0->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  CSM_NEO_1->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  SCG_main = std::make_shared<frc::SpeedControllerGroup>(*CSM_NEO_0,*CSM_NEO_1);
}

void Elevator::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
