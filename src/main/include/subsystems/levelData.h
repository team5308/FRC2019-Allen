/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                          */                                     
/* Filename: levelData.h                                               */
/* Project: Allen-Test-V2                                                    */
/*----------------------------------------------------------------------------*/

#pragma once

enum levelValue {kFree = 0, kBottom = 1, kMid = 2, kTop = 3};

class levelData {

public:
  double kMain;
  double kSub;
  levelData ();
  levelData (levelValue);
  levelData (double, double);
  void setData(double, double);

  void calibrate();
};
