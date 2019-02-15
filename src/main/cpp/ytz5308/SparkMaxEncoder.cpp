/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ytz5308/SparkMaxEncoder.h"

namespace ytz5308 {

SparkMaxEncoder::SparkMaxEncoder(rev::CANSparkMax& device) : rev::CANEncoder(device) {
    
    isInverted = false;
    orgPos = 0;
}

double SparkMaxEncoder::GetPosition() {
    return (isInverted ? -1 : 1) * (rev::CANEncoder::GetPosition() - orgPos);
}

double SparkMaxEncoder::GetVelocity() {
    return (isInverted ? -1 : 1) * rev::CANEncoder::GetVelocity();
}

bool SparkMaxEncoder::GetInverted() {
    return isInverted;
}

void SparkMaxEncoder::SetInverted() {
    isInverted = !isInverted;
}

void SparkMaxEncoder::SetInverted(bool mode) {
    isInverted = mode;
}

void SparkMaxEncoder::Reset() {
    orgPos = rev::CANEncoder::GetPosition();
}

} // ytz5308