/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/commands/Scheduler.h>

RevDigit Robot::m_revDigit;
OI Robot::m_oi;
CargoIntake Robot::cargoIntake;
Drive Robot::drive;
Pneumatics Robot::pneumatics;
Elevator Robot::elevator;
Rabbit Robot::rabbit;

testor Robot::Testor;

void Robot::RobotInit() {

  CargoIntake::CSM_NEO_Rab->SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
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
  
  m_oi.blink->Set(-0.21);

  if(m_revDigit.GetA())
  {
    Pneumatics::compressor->Start();
  }
  else if(m_revDigit.GetB())
  {
    Pneumatics::compressor->Stop();
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
  // m_revDigit.Display("SHUT");
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

void Robot::TestPeriodic() {
  Testor.test_default();
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
