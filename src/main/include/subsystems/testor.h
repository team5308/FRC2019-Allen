/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                          */                                                  */
/* Filename: testor.h                                               */
/* Project: Allen-Test-V2                                                    */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <rev/CANSparkMax.h>
#include <rev/CANEncoder.h>

#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

class testor : public frc::Subsystem {
 private:
 static std::shared_ptr<rev::CANSparkMax> CSM_NEO_test;
 static std::shared_ptr<rev::CANEncoder> CE_NEO_test;

  static std::shared_ptr<frc::Joystick> joy;

  static std::shared_ptr<PigeonIMU> imu;

 public:
  testor();
  void InitDefaultCommand() override;
  void Periodic() override;
  void test_default();
};
