/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <rev/CANEncoder.h>
#include <rev/CANSparkMax.h>

namespace ytz5308
{

class SparkMaxEncoder : public rev::CANEncoder {
  private:
    bool isInverted;
    double orgPos;
 public:
  
  explicit SparkMaxEncoder(rev::CANSparkMax& device);

  double GetPosition();
  double GetVelocity();
  bool GetInverted();

  void Reset();
  void SetInverted();
  void SetInverted(bool);
};

  
} // ytz5308

