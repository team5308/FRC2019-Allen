/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                          */                                                  */
/* Filename: SparkMaxEncoder.h                                               */
/* Project: Allen-Test-V2                                                    */
/*----------------------------------------------------------------------------*/

#pragma once

#include <rev/CANEncoder.h>
#include <rev/CANSparkMax.h>

namespace ytz5308
{

class SparkMaxEncoder : public rev::CANEncoder {
  private:
    double orgPos;
 public:
  
  explicit SparkMaxEncoder(rev::CANSparkMax& device);

  void Reset();
  double Get();
};

  
} // ytz5308

