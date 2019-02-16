/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/testor.h"

std::shared_ptr<rev::CANSparkMax> testor::CSM_NEO_test;
std::shared_ptr<rev::CANEncoder> testor::CE_NEO_test;

testor::testor() : Subsystem("testor") {
  CSM_NEO_test.reset(new rev::CANSparkMax(8, rev::CANSparkMax::MotorType::kBrushless));
  CE_NEO_test.reset(new rev::CANEncoder(*CSM_NEO_test));
  
}

void testor::InitDefaultCommand() {
}

void testor::test_default() 
{
  double curPos = CE_NEO_test->GetPosition();
  printf("rev Encoder: %.2f", curPos);
  
  while(curPos + 100 <= CE_NEO_test->GetPosition())
  {
    printf("rev Encoder: %.2f", CE_NEO_test->GetPosition());
    CSM_NEO_test->Set(0.2);
  }
  CSM_NEO_test->Set(0);
}