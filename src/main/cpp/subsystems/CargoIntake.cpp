/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoIntake.h"
#include <cstdio>

std::shared_ptr<rev::CANSparkMax> CargoIntake::CSM_NEO_Rab;
std::shared_ptr<frc::Joystick> CargoIntake::joystick;
double CargoIntake::spd = 0.1;
double CargoIntake::pre;

CargoIntake::CargoIntake() : Subsystem("CargoIntake") {

  CSM_NEO_Rab.reset(new rev::CANSparkMax(5, rev::CANSparkMaxLowLevel::MotorType::kBrushless));

  joystick.reset(new frc::Joystick(0));

}

void CargoIntake::InitDefaultCommand() {
}

void CargoIntake::Periodic() {

  spd = joystick->GetThrottle();
  spd = (int) (spd * 10) * 0.05;

  printf("%.2f\n", spd);

  if(joystick->GetRawButton(11))
  {
    CSM_NEO_Rab->Set(spd);

    printf("Get!\n");

    RevDigit::GetInstance()->Display("0501");
  }
  else if(joystick->GetRawButton(12))
  {
    CSM_NEO_Rab->Set(-spd);
    printf("Not Get!\n");
    RevDigit::GetInstance()->Display("0500");
  }
  else
  {
    CSM_NEO_Rab->Set(0);
    RevDigit::GetInstance()->Display("5308");
  }

  
}