/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include "rev/CANSparkMax.h"
#include "BasicPID.h"
// #include "DriveInfo.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"

#include "ytz5308/SparkMaxEncoder.h"

#include "Pneumatics.h"

class Drive : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  BasicPID drivePID;
  BasicPID rightPID;

  static constexpr double highModek = 6 * 3.1415926 * 2.54 /
   7.16;
  void forward(double);
 public:
  Drive();
  double driveSpeed;
  int index;
  void InitDefaultCommand() override; 
  void Periodic() override;

  double tarPos;
  bool autoMode;
 
  static std::shared_ptr<frc::Joystick> JOY;

  static std::shared_ptr<rev::CANSparkMax> CSM_NEO_left;
  static std::shared_ptr<rev::CANSparkMax> CSM_CIM_left;
  static std::shared_ptr<WPI_TalonSRX>     TAL_CIM_left;

  static std::shared_ptr<rev::CANSparkMax> CSM_NEO_right;
  static std::shared_ptr<rev::CANSparkMax> CSM_CIM_right;
  static std::shared_ptr<WPI_TalonSRX>     TAL_CIM_right;

  static std::shared_ptr<ytz5308::SparkMaxEncoder> CE_left;
  static std::shared_ptr<rev::CANEncoder> CE_right;

  static std::shared_ptr<frc::SpeedControllerGroup> SCG_left;
  static std::shared_ptr<frc::SpeedControllerGroup> SCG_right;

  static std::shared_ptr<frc::DifferentialDrive> DIFF;

  static std::shared_ptr<NetworkTable> limelight;

  double tx,ty;

  double kDiffRate;

  void autoTest();
};
