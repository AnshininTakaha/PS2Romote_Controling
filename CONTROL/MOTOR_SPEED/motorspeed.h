#ifndef __MOTORSPEED_H
#define __MOTORSPEED_H

#include "sys.h"

#define PWMPeriod      7199			//10k HZ
#define ECDPeriod      1559
#define TIMPeriod	   7199
#define PWMLOSS        3000

void MotorSpeedSetOne(s32 MotorSpeed);
void MotorSpeedSetTwo(s32 MotorSpeed);
void MotorSpeedSetThr(s32 MotorSpeed);
void MotorSpeedSetFor(s32 MotorSpeed);

#endif
