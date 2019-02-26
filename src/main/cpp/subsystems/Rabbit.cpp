/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                          */        
/* Filename: Rabbit.cpp                                               */
/* Project: Allen-Test-V2                                                    */
/*----------------------------------------------------------------------------*/

#include "subsystems/Rabbit.h"
std::shared_ptr<frc::Joystick> Rabbit::JOY2;

std::shared_ptr<frc::Solenoid> Rabbit::SOL_de1;
std::shared_ptr<frc::DoubleSolenoid> Rabbit::SOL_de23;
// std::shared_ptr<frc::DoubleSolenoid> Rabbit::SOL_de23;

Rabbit::Rabbit() : Subsystem("ExampleSubsystem") {
  JOY2.reset(new frc::Joystick(1));

  SOL_de1.reset(new frc::Solenoid(11, 1));
  SOL_de23.reset(new frc::DoubleSolenoid(11, 2, 3));
}

void Rabbit::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.TRUE

void Rabbit::Periodic(){
  if(JOY2 -> GetRawButton(5))
  {
    SOL_de1->Set(true);
    
  }
  else if(JOY2 -> GetRawButton(6))
  {
    SOL_de1->Set(false);
  }
  if(JOY2 -> GetRawButton(3))
  {
    SOL_de23->Set(frc::DoubleSolenoid::kForward);
  }
  else if(JOY2 -> GetRawButton(4))
  {
    SOL_de23->Set(frc::DoubleSolenoid::kReverse);
  }  
  
}
