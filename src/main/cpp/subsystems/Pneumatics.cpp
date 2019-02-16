/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Pneumatics.h"

std::shared_ptr<frc::Compressor> Pneumatics::compressor;
std::shared_ptr<frc::Solenoid> Pneumatics::drive_Mode0;

Pneumatics::Pneumatics() : Subsystem("Pneumatics") {
  
  compressor.reset(new frc::Compressor(11));
  drive_Mode0.reset(new frc::Solenoid(11, 0));

  drive_Mode0->Set(true);
}


void Pneumatics::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

