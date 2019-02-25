/*----------------------------------------------------------------------------*/
/*MIT                                                                         */
/* Github: @WuYuanhun                                                         */
/* Author: Cetian Liu                                                         */
/* Date: 2019/02/01                                                           */
/* Filename: BasicPID.cpp                                                     */
/*----------------------------------------------------------------------------*/

#include "BasicPID.h"

BasicPID::BasicPID() {
    rm_sum = 0;
    cycNum = 1000;
}

BasicPID::BasicPID(double p, double i, double d, int cycle_num = 100) 
                            : kp(p), ki(i), kd(d), cycNum(cycle_num) {
    rm_sum = 0;
}

void BasicPID::setP(double p) {
    this->kp = p;
}

void BasicPID::setI(double i) {
    this->ki = i;
}

void BasicPID::setD(double d) {
    this->kd = d;
}

void BasicPID::setPara(double p, double i, double d) {
    this->kp = p;
    this->ki = i;
    this->kd = d;
}

void BasicPID::push(double err) {
    rm_sum += err;
    rm.push(err);
    while(rm.size() > cycNum) {
        rm_sum -= rm.front(); 
        rm.pop();
    }
    output();
}

void BasicPID::output() {
    outputValue  = kp * rm.back();
    outputValue += ki * rm_sum / cycNum;
    outputValue += kd * (rm.back() - rm.front());
    printf("outputValue: %.2f\n org: %.2f\n", outputValue, rm.back());
}

void BasicPID::info() {
    printf("[Basic PID info] ci value: %.2f\n", rm_sum);
}