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
std::shared_ptr<rev::CANEncoder> CargoIntake::CE_Rab_Encoder;
std::shared_ptr<WPI_VictorSPX> CargoIntake::VIC_775_Rab;

double CargoIntake::spd = 0.4;
double CargoIntake::curPos = 0;
double CargoIntake::cargoSpeed = 0;

CargoIntake::CargoIntake() : Subsystem("CargoIntake") {

  CSM_NEO_Rab.reset(new rev::CANSparkMax(1, rev::CANSparkMaxLowLevel::MotorType::kBrushless));
  CSM_NEO_Rab->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  CE_Rab_Encoder.reset(new rev::CANEncoder(*CSM_NEO_Rab));

  VIC_775_Rab.reset(new WPI_VictorSPX(22));

  joystick.reset(new frc::Joystick(0));

  curPos = CE_Rab_Encoder->GetPosition();

}

void CargoIntake::InitDefaultCommand() {
}

void CargoIntake::Periodic() {

  if(joystick->GetRawButton(11))
  {
    CSM_NEO_Rab->Set(spd);
    RevDigit::GetInstance()->Display("0501");
  }
  else if(joystick->GetRawButton(12))
  {
    CSM_NEO_Rab->Set(-spd);
    RevDigit::GetInstance()->Display("0500");
  }
  else
  {
    CSM_NEO_Rab->Set(0);
  }

  cargoSpeed = joystick->GetThrottle();

   if(joystick->GetRawButton(1))
  {
    VIC_775_Rab->Set(cargoSpeed);
  }
  else
  {
    VIC_775_Rab->Set(0);
  }
  // printf("%.2f\n", CE_Rab_Encoder->GetPosition());
}
