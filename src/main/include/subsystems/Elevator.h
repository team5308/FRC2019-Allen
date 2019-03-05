/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                          */ 
/* Filename: Elevator.h                                               */
/* Project: Allen-Test-V2                                                    */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include "rev/CANSparkMax.h"
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>
#include "BasicPID.h"

// enum levelValue {kFree = 0, kBottom = 1, kMid = 2, kTop = 3};

// struct levelData {
//   double kMain;
//   double kSub;
//   levelData () {};
//   levelData (double kMain, double kSub) : kMain(kMain), kSub(kSub) {};

//   virtual void calibrate();
//  };

class Elevator : public frc::Subsystem {
 private:
 double kMainEncoderRate;
 double kRedEncoderRate;

 public:

  // levelData  eleData[4];


  Elevator();
  void InitDefaultCommand() override;
  void Periodic();
  // void moveToLevel(levelValue);

  static double limit(double);

  static std::shared_ptr<frc::Joystick> JOY_ele;
  static std::shared_ptr<frc::Joystick> joystick1;

  static std::shared_ptr<rev::CANSparkMax> CSM_NEO_0;
  static std::shared_ptr<rev::CANSparkMax> CSM_NEO_1;

  static std::shared_ptr<WPI_TalonSRX> TAL_Red;

  static std::shared_ptr<rev::CANEncoder> CE_Main;

  static std::shared_ptr<frc::SpeedControllerGroup> SCG_main;

  static std::shared_ptr<WPI_VictorSPX> VIC_Car_left;
  static std::shared_ptr<WPI_VictorSPX> VIC_Car_right;
  
  static std::shared_ptr<frc::SpeedControllerGroup> carrige;

  static std::shared_ptr<frc::DigitalInput> cargoLimitSwitch;
  static bool preCargo;
  static bool curCargo;

  BasicPID NEO_PID;
  BasicPID RED_PID;

  double NeoPosition();
  double RedPosition();

  int index = 0;
  int stpIndex = 0;

  static bool hasIn;

};
