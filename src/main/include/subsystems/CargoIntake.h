/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                          */  
/* Filename: CargoIntake.h                                               */
/* Project: Allen-Test-V2                                                    */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <rev/CANSparkMax.h>
#include <rev/CANEncoder.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

#include "ytz5308/SparkMaxEncoder.h"

#include "RevDigit.h"

class CargoIntake : public frc::Subsystem {
 public:

 static std::shared_ptr<frc::DigitalInput> armLimit;

  static std::shared_ptr<rev::CANSparkMax> CSM_NEO_Rab;
  static std::shared_ptr<ytz5308::SparkMaxEncoder> CE_Rab_Encoder;

  static std::shared_ptr<WPI_VictorSPX> VIC_775_Rab;

  static std::shared_ptr<frc::Joystick> joystick;

  static double spd;
  static double curPos;
  static double cargoSpeed;
 public:
  CargoIntake();
  void InitDefaultCommand() override;
  void Periodic() override;
};
