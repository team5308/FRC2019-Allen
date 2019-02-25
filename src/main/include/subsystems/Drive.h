/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                          */                                                  */
/* Filename: Drive.h                                               */
/* Project: Allen-Test-V2                                                    */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include "rev/CANSparkMax.h"
#include <rev/CANEncoder.h>
#include "BasicPID.h"
// #include "DriveInfo.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"

#include "ytz5308/SparkMaxEncoder.h"

#include "Pneumatics.h"

inline double abs(double x){
  if(x < 0){
    return -x;
  }else{
    return x;
  }
}

inline double suoqu(double x){
  if(abs(x) < 0.13){
    return 0.0;
  }else{
    return x;
  }
}

class Drive : public frc::Subsystem {
 private:

  static constexpr double deadBanValueMin = 0.2;
  static constexpr double rightSideOpter = -0.92;

  static constexpr double highModek = 6 * 3.1415926 * 2.54 / 7.16;
  static constexpr double lowModek  = 6 * 3.1415926 * 2.54 / 22.67;

  static double applyDeadBan(double);

  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  // BasicPID drivePID;
  // BasicPID rightPID;

  // BasicPID forPID;
  

  void forward(double);
 public:
  Drive();
  double driveSpeed;
  int index;
  void InitDefaultCommand() override; 
  void Periodic() override;

  static std::shared_ptr<frc::Joystick> joystick;

  static std::shared_ptr<rev::CANSparkMax> CSM_NEO_left;
  static std::shared_ptr<rev::CANSparkMax> CSM_CIM_left;
  static std::shared_ptr<WPI_TalonSRX>     TAL_CIM_left;

  static std::shared_ptr<rev::CANSparkMax> CSM_NEO_right;
  static std::shared_ptr<rev::CANSparkMax> CSM_CIM_right;
  static std::shared_ptr<WPI_TalonSRX>     TAL_CIM_right;

  static std::shared_ptr<rev::CANEncoder> CE_left;
  static std::shared_ptr<rev::CANEncoder> CE_right;

  static std::shared_ptr<frc::SpeedControllerGroup> SCG_left;
  static std::shared_ptr<frc::SpeedControllerGroup> SCG_right;

  static std::shared_ptr<frc::DifferentialDrive> DIFF;

  static std::shared_ptr<NetworkTable> limelight;

  double tx,ty;

  double kDiffRate;

  bool kInverted;

  void autoTest();

  void ArcadeDrive(double, double, bool);
};
