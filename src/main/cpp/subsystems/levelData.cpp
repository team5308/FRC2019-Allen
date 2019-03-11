/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                          */                                     
/* Filename: levelData.cpp                                               */
/* Project: Allen-Test-V2                                                    */
/*----------------------------------------------------------------------------*/

#include "subsystems/levelData.h"

levelData::levelData() {}

levelData::levelData(levelValue newType) {
  if(newType == kFree) {
    kMain = -1;
    kSub = -1;
  }
}

levelData::levelData(double kMain, double kSub) 
                          : kMain(kMain), kSub(kSub) {
  
}

void levelData::setData(double newkMain, double newkSub) {
  kMain = newkMain;
  kSub = newkSub;
}

//end struct leveData
