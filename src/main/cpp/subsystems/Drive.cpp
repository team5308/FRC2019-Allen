/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drive.h"

std::shared_ptr<frc::Joystick> Drive::joystick;

std::shared_ptr<rev::CANSparkMax> Drive::CSM_NEO_left;
std::shared_ptr<rev::CANSparkMax> Drive::CSM_CIM_left;
std::shared_ptr<WPI_TalonSRX>     Drive::TAL_CIM_left;

std::shared_ptr<rev::CANSparkMax> Drive::CSM_NEO_right;
std::shared_ptr<rev::CANSparkMax> Drive::CSM_CIM_right;
std::shared_ptr<WPI_TalonSRX>     Drive::TAL_CIM_right;

std::shared_ptr<ytz5308::SparkMaxEncoder> Drive::CE_left;
std::shared_ptr<rev::CANEncoder> Drive::CE_right;

std::shared_ptr<frc::SpeedControllerGroup> Drive::SCG_left;
std::shared_ptr<frc::SpeedControllerGroup> Drive::SCG_right;

std::shared_ptr<frc::DifferentialDrive> Drive::DIFF;

std::shared_ptr<NetworkTable> Drive::limelight = nt::NetworkTableInstance::GetDefault().GetTable("limeliht");

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

  CE_left.reset(new ytz5308::SparkMaxEncoder(*CSM_NEO_left));
  CE_right.reset(new rev::CANEncoder(*CSM_NEO_right));

  SCG_left = std::make_shared<frc::SpeedControllerGroup>(*CSM_NEO_left, *CSM_CIM_left,*TAL_CIM_left);
  SCG_right = std::make_shared<frc::SpeedControllerGroup>(*CSM_NEO_right, *CSM_CIM_right,*TAL_CIM_right);

  drivePID.setPara(0.00018, 0, 0);
  rightPID.setPara(0.00018, 0, 0);

  DIFF.reset(new frc::DifferentialDrive(*SCG_left,*SCG_right));

  kDiffRate = -0.93;
  if(Pneumatics::drive_Mode0->Get())
  {
    printf("pen: True\n");
  }
  else
  {
    printf("pen: False\n");
  }
  
}

void Drive::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Drive::Periodic(){

  tx = limelight->GetNumber("tx", 0.0);
  ty = limelight->GetNumber("ty", 0.0);

  if(joystick->GetRawButtonPressed(2))
  {
    Pneumatics::drive_Mode0->Set(!Pneumatics::drive_Mode0->Get());
  }

  if(joystick->GetRawButton(3))
  {
    SCG_left->Set(0.5);
    SCG_right->Set(-0.5);
  }
  else
  {
    DIFF->ArcadeDrive(suoqu(-joystick->GetY()), suoqu(joystick->GetX()));
  }
  
  printf("left: %.2f   right: %.2f\n", CE_left->GetPosition(), CE_right->GetPosition());
  printf("leftV: %.2f   rightV:%.2f\n", CE_left->GetVelocity(), CE_right->GetVelocity());
  printf("tx: %f, ty: %f\n", tx, ty);
}