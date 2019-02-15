/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

namespace ytz5308 {

const double PI = 3.1415926;

class DriveInfo {
 public:

  static constexpr const double lWheel = 6 * PI * 2.54;
  static constexpr const double kHigh  = lWheel / 7.16;;
  static constexpr const double kLow   = lWheel / 22.67;
};


}