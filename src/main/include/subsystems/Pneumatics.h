/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                          */ 
/* Filename: Pneumatics.cpp                                               */
/* Project: Allen-Test-V2                                                    */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>

class Pneumatics : public frc::Subsystem {
 public:
  static std::shared_ptr<frc::Compressor> compressor;
  static std::shared_ptr<frc::DoubleSolenoid> drive_Mode0;
  static std::shared_ptr<frc::Joystick> JOY1;
  static std::shared_ptr<frc::Joystick> coJoy;

 private:
 static std::shared_ptr<frc::DigitalInput> chickenLimitSwitch;

 public:
  Pneumatics();
  void InitDefaultCommand() override;    
  void Periodic(); 
};
