/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                         */                              
/* Filename: Drive.cpp                                                        */
/* Project: Allen-Test-V2                                                     */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drive.h"

std::shared_ptr<frc::Joystick> Drive::joystick;

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

std::shared_ptr<NetworkTable> Drive::limelight = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

bool Drive::autoMode = false;

Drive::Drive() : Subsystem("Drive") {
  joystick.reset(new frc::Joystick(0));

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

  CE_left->SetPositionConversionFactor(highModek);
  CE_right->SetPositionConversionFactor(highModek);

  SCG_left = std::make_shared<frc::SpeedControllerGroup>(*CSM_NEO_left, *CSM_CIM_left,*TAL_CIM_left);
  SCG_right = std::make_shared<frc::SpeedControllerGroup>(*CSM_NEO_right, *CSM_CIM_right,*TAL_CIM_right);

  SCG_left -> SetInverted(true);
  SCG_right -> SetInverted(true);
  kInverted = false;

  limelightPID.setPara(0.01,0.05,0);

}

void Drive::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Drive::Periodic(){


  tx = limelight->GetNumber("tx", 0.0);
  ty = limelight->GetNumber("ty", 0.0);
  autoMode = true;

  if(autoMode) 
  {
    // printf("limelight: tx: %.2f\n", tx);
    limelightPID.push(tx);
    double limelightSpeed = limelightPID.outputValue;
    if(joystick->GetRawButton(4))
    {
      SCG_left -> Set(-limelightSpeed);
      SCG_right -> Set(-limelightSpeed);
      return ;
    }
    else
    {
     SCG_left -> Set(0);
      SCG_right -> Set(0);
    }
    
    if (!autoMode) return ;
  }


  kInverted = !(joystick->GetPOV()==0);


  if(joystick->GetRawButtonPressed(2))
  {
    Pneumatics::drive_Mode0->Set((frc::DoubleSolenoid::Value) (3 - Pneumatics::drive_Mode0->Get()));
  }
  else if(joystick->GetRawButton(3))
  {
    SCG_left->Set(0.2);
    
    SCG_right->Set(-0.2);
  }
  else
  {
    ArcadeDrive(joystick->GetY(),  - joystick->GetX(), true);
  }

  #ifdef __DRIVE_OUT_PUT_Mode
  
  // printf("left: %.2f   right: %.2f\n", CE_left->GetPosition(), CE_right->GetPosition());
  
  #endif
  // printf("leftV: %.2f   rightV:%.2f\n", CE_left->GetVelocity(), CE_right->GetVelocity());
  // printf("tx: %f, ty: %f\n", tx, ty);
}

void Drive::ArcadeDrive(double x, double y, bool squareInput = true)
{
  x = (std::abs(x)>1 ? std::copysign(1, x) : x);
  x = abs(x)<0.2 ? 0 : x;
  
  y = (std::abs(y)>1 ? std::copysign(1, y) : y);
  y = abs(y)<0.2 ? 0 : y;
  
  if (squareInput) {
    x = std::copysign( x * x, x);
    y = std::copysign( y * y, y);
  }

  double leftOutput;
  double rightOutput;

  double maxInput = std::copysign( std::max( std::abs(x), std::abs(y)), x);

  if(x >= 0.0) {

    if( y >= 0.0){
      leftOutput = maxInput;
      rightOutput = x - y;
    } else {
      leftOutput = x + y;
      rightOutput = maxInput;
    }
  } else {
    
    if( y >= 0.0) {
      leftOutput = x + y;
      rightOutput = maxInput;
    } else {
      leftOutput = maxInput;
      rightOutput = x - y;
    }
  }
  
  SCG_left -> Set(applyDeadBan(leftOutput));
  SCG_right -> Set(applyDeadBan(rightOutput) * rightSideOpter );

}


double Drive::applyDeadBan(double x) {
  if(std::abs(x) <= deadBanValueMin) return 0;
  else return x;
}

void Drive::forward(double dis)
{
   
}