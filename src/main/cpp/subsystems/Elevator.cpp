#include "subsystems/Elevator.h"

std::shared_ptr<frc::Joystick> Elevator::JOY_ele;

std::shared_ptr<rev::CANSparkMax> Elevator::CSM_NEO_0;
std::shared_ptr<rev::CANSparkMax> Elevator::CSM_NEO_1;
// std::shared_ptr<rev::CANSparkMax> Elevator::CSM_RED;
std::shared_ptr<WPI_TalonSRX> Elevator::TAL_RED;

std::shared_ptr<rev::CANEncoder> Elevator::CE_1;
// std::shared_ptr<rev::CANEncoder> Elevator::CE_2;

std::shared_ptr<frc::SpeedControllerGroup> Elevator::SCG_main;

std::shared_ptr<WPI_VictorSPX> Elevator::VIC_Car_left;
std::shared_ptr<WPI_VictorSPX> Elevator::VIC_Car_right;

std::shared_ptr<frc::SpeedControllerGroup> Elevator::carrige; 

Elevator::Elevator() : Subsystem("ExampleSubsystem") {
  JOY_ele.reset(new frc::Joystick(1));

  CSM_NEO_0.reset(new rev::CANSparkMax(3,rev::CANSparkMax::MotorType::kBrushless));
  CSM_NEO_1.reset(new rev::CANSparkMax(8,rev::CANSparkMax::MotorType::kBrushless));
  // CSM_RED.reset(new rev::CANSparkMax(8,rev::CANSparkMax::MotorType::kBrushed));
  TAL_RED.reset(new WPI_TalonSRX(29));

  CSM_NEO_0->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  CSM_NEO_1->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  // CSM_NEO_0->SetInverted(true);

  CE_1.reset(new rev::CANEncoder(*CSM_NEO_0));
  // CE_2.reset(new rev::CANEncoder(*CSM_RED));

  SCG_main = std::make_shared<frc::SpeedControllerGroup>(*CSM_NEO_0,*CSM_NEO_1);

  // Victor right 23  victor left 27 
  VIC_Car_left.reset(new WPI_VictorSPX(27));
  VIC_Car_right.reset(new WPI_VictorSPX(24));

  VIC_Car_right->SetInverted(true);
  
  carrige = std::make_shared<frc::SpeedControllerGroup>(*VIC_Car_left, *VIC_Car_right);
}

void Elevator::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Elevator::Periodic(){
  TAL_RED -> Set(limit(JOY_ele->GetY())); 

  if(JOY_ele->GetRawButton(12)){
    SCG_main->Set(0.2);
  }
  else if(JOY_ele->GetRawButton(11)){
    SCG_main->Set(-0.2);
  }
  else{
    SCG_main->Set(-0.05);
  }
  double xspd = JOY_ele->GetThrottle();
  if(JOY_ele->GetRawButton(1)) {
    carrige->Set(xspd);
  }
  else
  {
    carrige->Set(0);
  }
  printf("%.2f",CE_1->GetPosition());
}

double Elevator::limit(double x) {
  if( std::abs(x) < 0.3) {
    return 0;
  } else {
    return x;
  }
}
// /*----------------------------------------------------------------------------*/
// /* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
// /* Open Source Software - may be modified and shared by FRC teams. The code   */
// /* must be accompanied by the FIRST BSD license file in the root directory of */
// /* the project.                                                               */
// /*----------------------------------------------------------------------------*/

// #include "subsystems/Elevator.h"

// std::shared_ptr<frc::Joystick> Elevator::JOY_ele;

// std::shared_ptr<rev::CANSparkMax> Elevator::CSM_NEO_0;
// std::shared_ptr<rev::CANSparkMax> Elevator::CSM_NEO_1;
// std::shared_ptr<rev::CANSparkMax> Elevator::CSM_RED;
// // std::shared_ptr<WPI_TalonSRX> Elevator::TAL_RED;

// std::shared_ptr<rev::CANEncoder> Elevator::CE_1;
// std::shared_ptr<rev::CANEncoder> Elevator::CE_2;

// std::shared_ptr<frc::SpeedControllerGroup> Elevator::SCG_main;

// std::shared_ptr<WPI_VictorSPX> Elevator::VIC_Car_left;
// std::shared_ptr<WPI_VictorSPX> Elevator::VIC_Car_right;

// std::shared_ptr<frc::SpeedControllerGroup> Elevator::carrige; 


// Elevator::Elevator() : Subsystem("ExampleSubsystem") {
//   JOY_ele.reset(new frc::Joystick(1));

//   CSM_NEO_0.reset(new rev::CANSparkMax(3,rev::CANSparkMax::MotorType::kBrushless));
//   CSM_NEO_1.reset(new rev::CANSparkMax(2,rev::CANSparkMax::MotorType::kBrushless));
//   CSM_RED.reset(new rev::CANSparkMax(8,rev::CANSparkMax::MotorType::kBrushed));
//   // TAL_RED.reset(new WPI_TalonSRX(29));

//   CSM_NEO_0->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
//   CSM_NEO_1->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

//   // CSM_NEO_0->SetInverted(true);

//   CE_1.reset(new rev::CANEncoder(*CSM_NEO_0));
//   CE_2.reset(new rev::CANEncoder(*CSM_RED));

//   SCG_main = std::make_shared<frc::SpeedControllerGroup>(*CSM_NEO_0,*CSM_NEO_1);

//   // Victor right 23  victor left 27 
//   VIC_Car_left.reset(new WPI_VictorSPX(27));
//   VIC_Car_right.reset(new WPI_VictorSPX(24));
  
//   VIC_Car_right->SetInverted(true);

//   carrige = std::make_shared<frc::SpeedControllerGroup>(*VIC_Car_left, *VIC_Car_right);

//   NEO_PID.setPara(1, 0, 0);
//   RED_PID.setPara(1, 0, 0);
// }

// void Elevator::InitDefaultCommand() {
//   // Set the default command for a subsystem here.
//   // SetDefaultCommand(new MySpecialCommand());
// }


// void Elevator::Periodic(){
//   // printf("t\n");
//   double spd = 0.2;
//   if(JOY_ele -> GetPOV(0)){
//     // printf("t1\n");
//     SCG_main -> Set(spd);
//   }
//   else if(JOY_ele -> GetPOV(180)){
//     SCG_main -> Set(-spd);
//   } 
//   else if(JOY_ele -> GetRawButton(2))
//   {
//     SCG_main -> Set(-0.05);
//   }
//   else{
//     SCG_main -> Set(0);
//   }

//   // TAL_RED->Set(JOY_ele -> GetY());
//   // printf("CE: %.2f\n", TAL_RED->GetSelectedSensorPosition(0));

//   double xspd = JOY_ele->GetThrottle();

//   if(JOY_ele->GetRawButton(1)) {
//     VIC_Car_left->Set(xspd);
//     VIC_Car_right->Set(-xspd);
//   }
//   else
//   {
//     carrige->Set(0);
//   }
  
//   // if(JOY_ele->GetRawButton(7)){
//   //   ChangeLevel(1);
//   // }
//   // else if(JOY_ele->GetRawButton(8)){
//   //   ChangeLevel(2);
//   // }
//   // else if(JOY_ele->GetRawButton(9)){
//   //   ChangeLevel(3);
//   // }
//   // else{
//   //   ChangeLevel(0);
//   // }
// }

// double Elevator::limit(double x) {
//   if( std::abs(x) < 0.3) {
//     return 0;
//   } else {
//     return x;
//   }
// }

// // void Elevator::ChangeLevel(int level) {
// //   double CE_1_CurPos = CE_1->GetPosition();
// //   double CE_2_CurPos = TAL_RED->GetSelectedSensorPosition(0) / 4096;
// //   double CE_1_TarPos = CE_1_CurPos;
// //   double CE_2_TarPos = CE_2_CurPos;

// //   if(level == 1){
// //     CE_1_TarPos = level1_1;
// //     CE_2_TarPos = level2_1;
// //   }
// //   else if(level == 2){
// //     CE_1_TarPos = level1_2;
// //     CE_2_TarPos = level2_2;
// //   }
// //   else if(level == 3){
// //     CE_1_TarPos = level1_3;
// //     CE_2_TarPos = level2_3;
// //   }
// //   else if(level == 0){
// //     CE_1_TarPos = CE_1_CurPos;
// //     CE_2_TarPos = CE_2_CurPos;
// //   }

// //   double CE_1_Error = CE_1_CurPos - CE_1_TarPos;
// //   double CE_2_Error = CE_2_CurPos - CE_2_TarPos;

// //   while(CE_1_Error != 0){
// //     CE_1_CurPos = CE_1->GetPosition();
// //     // CE_2_CurPos = CE_2->GetPosition();
// //     CE_1_Error = CE_1_CurPos - CE_1_TarPos;
// //     // CE_2_Error = CE_2_CurPos - CE_2_TarPo;
// //     NEO_PID.push(CE_1_Error);
// //     double usingOutput1;
// //     if(NEO_PID.outputValue >=1){
// //       usingOutput1 = 0.2;
// //     }
// //     else if(NEO_PID.outputValue <=-1){
// //       usingOutput1 = -0.2;
// //     }
// //     else{
// //       usingOutput1 = NEO_PID.outputValue * 0.2;
// //     }
// //     SCG_main -> Set(usingOutput1);
// //   }

// // }