/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include "rev/CANSparkMax.h"
#include <frc/WPILib.h>

class Elevator : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  Elevator();
  void InitDefaultCommand() override;
  void Periodic();

  static std::shared_ptr<frc::Joystick> JOY_ele;

  static std::shared_ptr<rev::CANSparkMax> CSM_NEO_0;
  static std::shared_ptr<rev::CANSparkMax> CSM_NEO_1;
  static std::shared_ptr<rev::CANSparkMax> CSM_RED;

  static std::shared_ptr<rev::CANEncoder> CE_1;
  static std::shared_ptr<rev::CANEncoder> CE_2;

  static std::shared_ptr<frc::SpeedControllerGroup> SCG_main;
};
