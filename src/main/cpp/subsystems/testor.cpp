/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                          */                                          
/* Filename: testor.cpp                                               */
/* Project: Allen-Test-V2                                                    */
/*----------------------------------------------------------------------------*/

#include "subsystems/testor.h"

std::shared_ptr<rev::CANSparkMax> testor::CSM_NEO_test;
std::shared_ptr<rev::CANEncoder> testor::CE_NEO_test;

std::shared_ptr<frc::Joystick> testor::joy;

std::shared_ptr<PigeonIMU> testor::imu;

testor::testor() : Subsystem("testor") {
  CSM_NEO_test.reset(new rev::CANSparkMax(9, rev::CANSparkMax::MotorType::kBrushless));
  CE_NEO_test.reset(new rev::CANEncoder(*CSM_NEO_test));
  joy.reset(new frc::Joystick(0));

  imu.reset(new PigeonIMU(25));
}

void testor::InitDefaultCommand() {
}

void testor::Periodic() {
  test_default();
}

void testor::test_default() 
{
  // double curPos = CE_NEO_test->GetPosition();
  // printf("rev Encoder: %.2f", curPos);
  
  if(joy->GetRawButton(4))
  {
    printf("rev Encoder: %.2f\n", CE_NEO_test->GetPosition());
    CSM_NEO_test->Set(0.2);
  }
  else
  {
    printf("0\n");
    CSM_NEO_test->Set(0);
  }

  
}