/*----------------------------------------------------------------------------*/
/*MIT                                                                         */
/* Github: @WuYuanhun                                                         */
/* Author: Cetian Liu                                                         */
/* Date: 2019/02/01                                                           */
/* Filename: BasicPID.h                                                     */
/*----------------------------------------------------------------------------*/

#pragma once

#include <queue>
#include <cstdio>

class BasicPID {
 private:

  double kp;
  double ki;
  double kd;

  double cp;
  double ci;
  double cd;

  int cycNum;

  std::queue<double> rm;
  long double rm_sum;

 public:
  
  double outputValue;

  BasicPID();
  BasicPID(double, double, double, int);
  
  void setP(double);
  void setI(double);
  void setD(double);
  void setPara(double, double, double);

  void push(double);
  void output();

  void info();
};
