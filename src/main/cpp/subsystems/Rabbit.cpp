/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                          */                                                  */
/* Filename: Rabbit.cpp                                               */
/* Project: Allen-Test-V2                                                    */
/*----------------------------------------------------------------------------*/

#include "subsystems/Rabbit.h"
std::shared_ptr<frc::Joystick> Rabbit::JOY_rab;

std::shared_ptr<WPI_TalonSRX> Rabbit::TAL_rab;
std::shared_ptr<rev::CANSparkMax> Rabbit::CSM_rab;

std::shared_ptr<rev::CANEncoder> Rabbit::CE_rab;

std::shared_ptr<frc::Solenoid> Rabbit::SOL_rab; 

std::shared_ptr<frc::Solenoid> Rabbit::SOL_delift;
std::shared_ptr<frc::DoubleSolenoid> Rabbit::SOL_deDick;

Rabbit::Rabbit() : Subsystem("ExampleSubsystem") {
  JOY_rab.reset(new frc::Joystick(0));
  
  TAL_rab.reset(new WPI_TalonSRX(1));

  CSM_rab.reset(new rev::CANSparkMax(0,rev::CANSparkMax::MotorType::kBrushless));
  
  CE_rab.reset(new rev::CANEncoder(*CSM_rab));

  SOL_deDick.reset(new frc::DoubleSolenoid(11, 2, 3));
  SOL_deDick->Set( (frc::DoubleSolenoid::Value) 1);
}

void Rabbit::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Rabbit::Periodic(){
  double goal = 130 / 3;

  if(JOY_rab -> GetRawButton(6)){// up
    if(CE_rab -> GetPosition() > goal){
      TAL_rab -> Set(0.5);
    }else{
      TAL_rab -> Set(0.0);
    }
  }

  if(JOY_rab -> GetRawButton(7)){// down
    if(CE_rab -> GetPosition() < goal){
      TAL_rab -> Set(-0.5);
    }else{
      TAL_rab -> Set(0.0);
  }
  }

  if(JOY_rab -> GetRawButtonPressed(6))
  {
    printf("Fucked!\n");
    SOL_deDick -> Set( (frc::DoubleSolenoid::Value) 2);
    // SOL_deDick -> Set( (frc::DoubleSolenoid::Value) (3 - (int) SOL_deDick->Get()));
  }
  else if(JOY_rab -> GetRawButtonPressed(5))
  {
    SOL_deDick->Set((frc::DoubleSolenoid::Value) 1);
  }
  
  
}
