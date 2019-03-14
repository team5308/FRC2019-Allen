/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                          */                                     
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

  CE_PID.setPara(1, 0, 0);
}

void CargoIntake::InitDefaultCommand() {
}

void CargoIntake::Periodic() {

  #ifdef Use_Arm_Limit_Switch_Option
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
  #endif
  

  if(joystick->GetRawButton(7))
  {
    CSM_NEO_Rab->Set(spd);
    // RevDigit::GetInstance()->Display("0501");
  }
  else if(joystick->GetRawButton(8))
  {
    CSM_NEO_Rab->Set(-spd);
    // RevDigit::GetInstance()->Display("0500");
  }
  else
  {
    CSM_NEO_Rab->Set(0);
  }

  // if(joystick->GetRawButton(2)){
  //   AutoLock(1);
  // }

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

void CargoIntake::AutoLock(int target){
  double CE_CurPos = CE_Rab_Encoder->GetPosition();
  double CE_TarPos = CE_CurPos;
  if(target == 1){
    double CE_TarPos = 30;
  }
  double CE_Error = CE_TarPos - CE_CurPos;

  while(CE_Error >= 1 || CE_Error <= -1){
    CE_CurPos = CE_Rab_Encoder->GetPosition();
    // CE_2_CurPos = CE_2->GetPosition();
    CE_Error = CE_CurPos - CE_TarPos;
    // CE_2_Error = CE_2_CurPos - CE_2_TarPo;
    CE_PID.push(CE_Error);
    double usingOutput1;
    if(CE_PID.outputValue >=1){
      usingOutput1 = 0.2;
    }
    else if(CE_PID.outputValue <=-1){
      usingOutput1 = -0.2;
    }
    else{
      usingOutput1 = CE_PID.outputValue * 0.2;
    }
    CSM_NEO_Rab -> Set(usingOutput1);
  }
}