/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CalibrateArmEncoder.h"

CalibrateArmEncoder::CalibrateArmEncoder() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::cargoIntake);
}

// Called just before this Command runs the first time
void CalibrateArmEncoder::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CalibrateArmEncoder::Execute() {
  while(!Robot::cargoIntake.armLimit->Get()) {
    Robot::cargoIntake.CSM_NEO_Rab -> Set(-0.2);
  }
  Robot::cargoIntake.CE_Rab_Encoder -> Reset();
}

// Make this return true when this Command no longer needs to run execute()
bool CalibrateArmEncoder::IsFinished() { return false; }

// Called once after isFinished returns true
void CalibrateArmEncoder::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CalibrateArmEncoder::Interrupted() {}
