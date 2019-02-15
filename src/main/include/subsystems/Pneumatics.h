/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>

class Pneumatics : public frc::Subsystem {
 public:
  static std::shared_ptr<frc::Compressor> compressor;
  static std::shared_ptr<frc::Solenoid> drive_Mode0; 

 
 public:
  Pneumatics();
  void InitDefaultCommand() override;     
};
