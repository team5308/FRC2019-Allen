/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drive.h"

std::shared_ptr<frc::Joystick> Drive::JOY;

std::shared_ptr<rev::CANSparkMax> Drive::CSM_NEO_left;
std::shared_ptr<rev::CANSparkMax> Drive::CSM_CIM_left;
std::shared_ptr<WPI_TalonSRX>     Drive::TAL_CIM_left;

std::shared_ptr<rev::CANSparkMax> Drive::CSM_NEO_right;
std::shared_ptr<rev::CANSparkMax> Drive::CSM_CIM_right;
std::shared_ptr<WPI_TalonSRX>     Drive::TAL_CIM_right;

std::shared_ptr<rev::CANEncoder> Drive::CE_left;
std::shared_ptr<rev::CANEncoder> Drive::CE_right;

std::shared_ptr<frc::SpeedControllerGroup> Drive::SCG_left;
std::shared_ptr<frc::SpeedControllerGroup> Drive::SCG_right;

std::shared_ptr<frc::DifferentialDrive> Drive::DIFF;

Drive::Drive() : Subsystem("Drive") {
  JOY.reset(new frc::Joystick(0));

  CSM_NEO_left.reset(new rev::CANSparkMax(6,rev::CANSparkMax::MotorType::kBrushless));
  CSM_CIM_left.reset(new rev::CANSparkMax(7,rev::CANSparkMax::MotorType::kBrushed));
  TAL_CIM_left.reset(new WPI_TalonSRX(21));
  CSM_CIM_left->SetInverted(true);

  CSM_NEO_left->SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
  CSM_CIM_left->SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);

  CSM_NEO_right.reset(new rev::CANSparkMax(4,rev::CANSparkMax::MotorType::kBrushless));
  CSM_CIM_right.reset(new rev::CANSparkMax(5,rev::CANSparkMax::MotorType::kBrushed));
  TAL_CIM_right.reset(new WPI_TalonSRX(25));
  CSM_CIM_right->SetInverted(true);

  CSM_NEO_right->SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
  CSM_CIM_right->SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);

  CE_left.reset(new rev::CANEncoder(*CSM_NEO_left));
  CE_right.reset(new rev::CANEncoder(*CSM_NEO_right));

  SCG_left = std::make_shared<frc::SpeedControllerGroup>(*CSM_NEO_left, *CSM_CIM_left,*TAL_CIM_left);
  SCG_right = std::make_shared<frc::SpeedControllerGroup>(*CSM_NEO_right, *CSM_CIM_right,*TAL_CIM_right);

  
  // SCG_left->SetInverted(true);
  // SCG_right->SetInverted(true);

  DIFF.reset(new frc::DifferentialDrive(*SCG_left,*SCG_right));
}

void Drive::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

inline double abs(double x){
  if(x < 0){
    return -x;
  }else{
    return x;
  }
}

double suoqu(double x){
  if(abs(x) < 0.14){
    return 0.0;
  }else{
    return x;
  }
}

void Drive::Periodic(){
  
  // SCG_left->Set(-0.2);
  // SCG_right->Set(-0.2);
  if(JOY->GetRawButtonPressed(2))
  {
    Pneumatics::drive_Mode0->Set(!Pneumatics::drive_Mode0->Get());
    if(Pneumatics:: drive_Mode0->Get())
    {
      printf("True\n");
    }
    else
    {
      printf("Flase\n");
    }
  }
  printf("left: %.2f   right: %.2f\n", CE_left->GetPosition(), CE_right->GetPosition());
  DIFF -> ArcadeDrive(-suoqu(JOY -> GetY()), suoqu(JOY -> GetX()));
}