/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>

#include <ctre/Phoenix.h>
#include <rev/CANSparkMax.h>
#include <rev/CANEncoder.h>
#include <rev/CANSparkMaxLowLevel.h>
#include <frc/WPILib.h>


class Rabbit : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

  /*Rabit: */
  static std::shared_ptr<frc::Joystick> JOY_rab;

  static std::shared_ptr<WPI_TalonSRX> TAL_rab;
  static std::shared_ptr<rev::CANSparkMax> CSM_rab;
  
  static std::shared_ptr<rev::CANEncoder> CE_rab;

  static std::shared_ptr<frc::Solenoid> SOL_rab;

  /*Deanck*/
  static std::shared_ptr<frc::Solenoid> SOL_delift;
  static std::shared_ptr<frc::Solenoid> SOL_deDick;


 public:
  Rabbit();
  void InitDefaultCommand() override;
  void Periodic() override;
};
