/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Elevator.h"

levelData Elevator::kLevel[4];

std::shared_ptr<frc::Joystick> Elevator::JOY_ele;
std::shared_ptr<frc::Joystick> Elevator::joystick1;

std::shared_ptr<rev::CANSparkMax> Elevator::CSM_NEO_0;
std::shared_ptr<rev::CANSparkMax> Elevator::CSM_NEO_1;
// std::shared_ptr<rev::CANSparkMax> Elevator::CSM_RED; // 29
// std::shared_ptr<WPI_TalonSRX> Elevator::TAL_RED;

std::shared_ptr<rev::CANSparkMax> Elevator::CSM_Sub;

std::shared_ptr<rev::CANEncoder> Elevator::CE_Main;
std::shared_ptr<rev::CANEncoder> Elevator::CE_Sub;

std::shared_ptr<frc::SpeedControllerGroup> Elevator::SCG_main;

std::shared_ptr<WPI_VictorSPX> Elevator::VIC_Car_left;
std::shared_ptr<WPI_VictorSPX> Elevator::VIC_Car_right;

std::shared_ptr<frc::SpeedControllerGroup> Elevator::carrige; 

std::shared_ptr<frc::DigitalInput> Elevator::cargoLimitSwitch;

bool Elevator::hasIn = false;

// bool Elevator::preCargo = false;
bool Elevator::curCargo = false;

Elevator::Elevator() : Subsystem("Elevator") {


// calibrate and set level Encoder Data
  kLevel[kFree].setData(-1,-1);
  kLevel[kBottom].setData(0,0);
  kLevel[kMid].setData(0,0);
  kLevel[kTop].setData(0,0);

  joystick1.reset(new frc::Joystick(0));
  JOY_ele.reset(new frc::Joystick(1));

  CSM_NEO_0.reset(new rev::CANSparkMax(3,rev::CANSparkMax::MotorType::kBrushless));
  CSM_NEO_1.reset(new rev::CANSparkMax(8,rev::CANSparkMax::MotorType::kBrushless));
  // TAL_RED.reset(new WPI_TalonSRX(29));

  CSM_NEO_0->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  CSM_NEO_1->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  // CSM_NEO_0->SetInverted(true);

  CE_Main.reset(new rev::CANEncoder(*CSM_NEO_0));
  SCG_main = std::make_shared<frc::SpeedControllerGroup>(*CSM_NEO_0,*CSM_NEO_1);

  // Victor right 23  victor left 27 
  VIC_Car_left.reset(new WPI_VictorSPX(27));
  VIC_Car_right.reset(new WPI_VictorSPX(24));
  
  VIC_Car_right->SetInverted(true);

  carrige = std::make_shared<frc::SpeedControllerGroup>(*VIC_Car_left, *VIC_Car_right);

  cargoLimitSwitch.reset(new frc::DigitalInput(3));

  // NEO_PID.setPara(1, 0, 0);
  // RED_PID.setPara(1, 0, 0);

  CSM_Sub.reset(new rev::CANSparkMax(33, rev::CANSparkMaxLowLevel::MotorType::kBrushless));
  CE_Sub.reset(new rev::CANEncoder(*CSM_Sub));
  CSM_Sub->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
}

void Elevator::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}


void Elevator::Periodic() {
  curCargo = ! cargoLimitSwitch->Get();
  if(!hasIn && curCargo)
  {
    hasIn = true;
  }
  else if(hasIn)
  {
    index ++;
  }

  // True means Cargo on the ship!

  // double xspd = joystick1->GetThrottle();
  double xspd = 0.4;

#ifdef We_Have_Fix_Switch
  if( !hasIn && joystick1->GetRawButton(1)) {
    VIC_Car_left->Set(xspd);
    VIC_Car_right->Set(-xspd);
  }
  else if( hasIn && ++index <=10 ) 
  {
    VIC_Car_left->Set(0.2);
    VIC_Car_right->Set(-0.2);
  }
  else
  {
    carrige->Set(0);
  }
#endif

  if(joystick1->GetRawButton(1))
  {
    VIC_Car_left->Set(xspd);
    VIC_Car_right->Set(-xspd);
  }

  double ospd = JOY_ele->GetThrottle();
  if(!joystick1->GetRawButton(1))
  {
    if(JOY_ele -> GetRawButton(1))
    {
     VIC_Car_left->Set(ospd);
     VIC_Car_right->Set(-ospd);
     hasIn = false;
     index = -2;
    }
   else
    {
      carrige->Set(0);
    }
  }


// 电梯上下逻辑
  double spd = 0.5;
  if( JOY_ele -> GetRawButton(5)){
    SCG_main -> Set(spd);
    // CSM_Sub  -> Set(spd);
    printf("Ele up\n");
  }
  else if(JOY_ele -> GetRawButton(10)){
    SCG_main -> Set(-spd);
    // CSM_Sub  -> Set(-spd);
    // printf("Ele down\n");
  }
  else{
    SCG_main -> Set(0);
    // CSM_Sub  -> Set(0);
  }
  
  if( JOY_ele -> GetRawButton(6))
  {
    CSM_Sub -> Set(spd);
  }
  else if(JOY_ele -> GetRawButton(9))
  {
    CSM_Sub -> Set(-spd);
  }
  else
  {
    CSM_Sub -> Set(0);
  }
  
  printf("encoder_Sub: %.2f\n", CE_Sub -> GetPosition());
}

double Elevator::limit(double x) {
  if( std::abs(x) < 0.3 ) {
    return 0;
  } else {
    return x;
  }
}

double Elevator::NeoPosition() {
  return CE_Main->GetPosition() * kMainEncoderRate;
}

double Elevator::RedPosition() {
  return CE_Sub->GetPosition() * kRedEncoderRate;
}

// void Elevator::moveToLevel(levelValue target) {
  // if(true) {
  //   NEO_PID.push(eleData[(int) target].kMain - NeoPosition());
  //   RED_PID.push(eleData[(int) target].kSub  - RedPosition());
    
  //   SCG_main->Set(NEO_PID.outputValue);

  //   TAL_Red->PIDWrite(RED_PID.outputValue);
  // }
// }