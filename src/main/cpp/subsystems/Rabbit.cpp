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
  // SOL_de23->Set(frc::DoubleSoleno0id::kReverse);
}

void Rabbit::InitDefaultCommand() {
}

void Rabbit::Periodic(){
  if(JOY2 -> GetRawButtonPressed(3))
  {
    // SOL_de1->Set(true);
    SOL_de23 -> Set(frc::DoubleSolenoid::kForward);
  }
  else if(JOY2 -> GetRawButtonPressed(4))
  {
    // SOL_de1->Set(false);
    SOL_de23 -> Set(frc::DoubleSolenoid::kReverse);
  }

  if(JOY2 -> GetRawButtonPressed(2))
  {

    // SOL_de23->Set((frc::DoubleSolenoid::Value) (3 - SOL_de23->Get()));

    SOL_de1 -> Set( !SOL_de1->Get() );
  }
  if(SOL_de23->Get())
  {
    printf("Deack Unlock!\n");
  }
  else
  {
    printf("Deack Lock!\n");
  }
  
}
