/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                          */                                                  */
/* Filename: Elevator.h                                               */
/* Project: Allen-Test-V2                                                    */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include "rev/CANSparkMax.h"
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

class Elevator : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  Elevator();
  void InitDefaultCommand() override;
  void Periodic();

  static double limit(double);

  static std::shared_ptr<frc::Joystick> JOY_ele;
  static std::shared_ptr<frc::XboxController> xbox;
  static std::shared_ptr<frc::Joystick> joy2;

  static std::shared_ptr<rev::CANSparkMax> CSM_NEO_0;
  static std::shared_ptr<rev::CANSparkMax> CSM_NEO_1;
  static std::shared_ptr<rev::CANSparkMax> CSM_RED;

  static std::shared_ptr<rev::CANEncoder> CE_1;
  static std::shared_ptr<rev::CANEncoder> CE_2;

  static std::shared_ptr<frc::SpeedControllerGroup> SCG_main;

  static std::shared_ptr<WPI_VictorSPX> VIC_Car_left;
  static std::shared_ptr<WPI_VictorSPX> VIC_Car_right;
  
  static std::shared_ptr<frc::SpeedControllerGroup> carrige;
};
