/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                          */                                                  */
/* Filename: Robot.cpp                                               */
/* Project: Allen-Test-V2                                                    */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/commands/Scheduler.h>

RevDigit Robot::m_revDigit;
OI Robot::m_oi;

Pneumatics Robot::pneumatics;

CargoIntake Robot::cargoIntake;
Drive Robot::drive;
Elevator Robot::elevator;
Rabbit Robot::rabbit;

testor Robot::Testor;

void Robot::RobotInit() {

  CargoIntake::CSM_NEO_Rab->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  // Testor.test_default();
  frc::CameraServer::GetInstance()->StartAutomaticCapture("cam", 0);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  
  // m_oi.blink->Set(-0.21);

  if(m_revDigit.GetA())
  {
    Pneumatics::compressor->Stop();
    // Rabbit::SOL_deDick->Set(false);
  }
  else if(m_revDigit.GetB())
  {
    Pneumatics::compressor->Start();
    // Rabbit::SOL_deDick->Set(true);
  } 
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {
  CargoIntake::CSM_NEO_Rab->SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
}

void Robot::DisabledPeriodic() {
  m_revDigit.Display(frc::DriverStation::GetInstance().GetBatteryVoltage());
  frc::Scheduler::GetInstance()->Run(); 
  }

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString code to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons to
 * the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit() {
  // std::string autoSelected = frc::SmartDashboard::GetString(
  //     "Auto Selector", "Default");
  // if (autoSelected == "My Auto") {
  //   m_autonomousCommand = &m_myAuto;
  // } else {
  //   m_autonomousCommand = &m_defaultAuto;
  // }

  // m_autonomousCommand = m_chooser.GetSelected();

  // if (m_autonomousCommand != nullptr) {
  //   m_autonomousCommand->Start();
  // }
}
 
void Robot::AutonomousPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
   CargoIntake::CSM_NEO_Rab->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

}

void Robot::TeleopPeriodic() { frc::Scheduler::GetInstance()->Run(); }
  
void Robot::TestInit() {
  printf("test Mode\n");
}

void Robot::TestPeriodic() {
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
