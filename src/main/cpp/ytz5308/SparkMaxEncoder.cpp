/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FRC Team 5308. All Rights Reserved.                */
/* Author: Cetian Liu                                                          */               
/* Filename: SparkMaxEncoder.cpp                                               */
/* Project: Allen-Test-V2                                                    */
/*----------------------------------------------------------------------------*/

#include "ytz5308/SparkMaxEncoder.h"

namespace ytz5308 {

SparkMaxEncoder::SparkMaxEncoder(rev::CANSparkMax& device) : rev::CANEncoder(device) {
    
    orgPos = 0;
}

double SparkMaxEncoder::Get() {
    return this->GetPosition() - orgPos; 
}

void SparkMaxEncoder::Reset() {
    orgPos = rev::CANEncoder::GetPosition();
}

} // ytz5308