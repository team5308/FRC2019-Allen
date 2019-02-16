/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Rabbit.h"
std::shared_ptr<frc::Joystick> Rabbit::JOY_rab;

std::shared_ptr<WPI_TalonSRX> Rabbit::TAL_rab;
std::shared_ptr<rev::CANSparkMax> Rabbit::CSM_rab;

std::shared_ptr<rev::CANEncoder> Rabbit::CE_rab;

std::shared_ptr<frc::Solenoid> Rabbit::SOL_rab; 

std::shared_ptr<frc::Solenoid> Rabbit::SOL_delift;
std::shared_ptr<frc::Solenoid> Rabbit::SOL_deDick;

Rabbit::Rabbit() : Subsystem("ExampleSubsystem") {
  JOY_rab.reset(new frc::Joystick(2));
  
  TAL_rab.reset(new WPI_TalonSRX(1));

  CSM_rab.reset(new rev::CANSparkMax(0,rev::CANSparkMax::MotorType::kBrushless));
  
  CE_rab.reset(new rev::CANEncoder(*CSM_rab));
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
}
