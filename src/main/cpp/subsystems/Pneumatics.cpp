/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                          */                                                  */
/* Filename: Pneumatics.cpp                                               */
/* Project: Allen-Test-V2                                                    */
/*----------------------------------------------------------------------------*/

#include "subsystems/Pneumatics.h"

std::shared_ptr<frc::Compressor> Pneumatics::compressor;
std::shared_ptr<frc::DoubleSolenoid> Pneumatics::drive_Mode0;

Pneumatics::Pneumatics() : Subsystem("Pneumatics") {
  
  compressor.reset(new frc::Compressor(11));
  drive_Mode0.reset(new frc::DoubleSolenoid(11, 6, 7));

  drive_Mode0->Set( (frc::DoubleSolenoid::Value) 1);

  // chickenLimitSwitch.reset(new frc::DigitalInput(8));
}


void Pneumatics::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

