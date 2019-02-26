/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                          */                            
/* Filename: Pneumatics.cpp                                               */
/* Project: Allen-Test-V2                                                    */
/*----------------------------------------------------------------------------*/

#include "subsystems/Pneumatics.h"

std::shared_ptr<frc::Compressor> Pneumatics::compressor;
std::shared_ptr<frc::DoubleSolenoid> Pneumatics::drive_Mode0;
std::shared_ptr<frc::Joystick> Pneumatics::JOY1;

Pneumatics::Pneumatics() : Subsystem("Pneumatics") {
  
  compressor.reset(new frc::Compressor(11));
  drive_Mode0.reset(new frc::DoubleSolenoid(11, 6, 7));

  drive_Mode0->Set( (frc::DoubleSolenoid::Value) 1);

  JOY1.reset(new frc::Joystick(0));

  // chickenLimitSwitch.reset(new frc::DigitalInput(8));
}


void Pneumatics::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Pneumatics::Periodic(){
    if(JOY1 -> GetRawButton(6))
  {
    drive_Mode0 -> Set( (frc::DoubleSolenoid::Value) 2);
  }
  else if(JOY1 -> GetRawButton(5))
  {
    drive_Mode0->Set((frc::DoubleSolenoid::Value) 1);
  }
}
