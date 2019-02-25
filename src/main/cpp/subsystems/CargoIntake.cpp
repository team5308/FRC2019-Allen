/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                          */                                                  */
/* Filename: CagoIntake.cpp                                               */
/* Project: Allen-Test-V2                                                    */
/*----------------------------------------------------------------------------*/

#include "subsystems/CargoIntake.h"
#include <cstdio>

std::shared_ptr<rev::CANSparkMax> CargoIntake::CSM_NEO_Rab;
std::shared_ptr<frc::Joystick> CargoIntake::joystick;
std::shared_ptr<ytz5308::SparkMaxEncoder> CargoIntake::CE_Rab_Encoder;
std::shared_ptr<WPI_VictorSPX> CargoIntake::VIC_775_Rab;

std::shared_ptr<frc::DigitalInput> CargoIntake::armLimit;

double CargoIntake::spd = 0.4;
double CargoIntake::curPos = 0;
double CargoIntake::cargoSpeed = 0;

CargoIntake::CargoIntake() : Subsystem("CargoIntake") {
  
  armLimit.reset(new frc::DigitalInput(9));

  CSM_NEO_Rab.reset(new rev::CANSparkMax(1, rev::CANSparkMaxLowLevel::MotorType::kBrushless));
  CSM_NEO_Rab->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  CE_Rab_Encoder.reset(new ytz5308::SparkMaxEncoder(*CSM_NEO_Rab));

  VIC_775_Rab.reset(new WPI_VictorSPX(22));
  joystick.reset(new frc::Joystick(0));

  curPos = CE_Rab_Encoder->GetPosition();

}

void CargoIntake::InitDefaultCommand() {
}

void CargoIntake::Periodic() {

  if(armLimit->Get())
  {
    // RevDigit::GetInstance()->Display("True");
  }
  else
  {
    // // set it to 0
    CE_Rab_Encoder -> Reset();
    // RevDigit::GetInstance()->Display("Flas");
  }
  

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
  printf("CE: %.2f\n", CE_Rab_Encoder->GetPosition());
}
