#ifndef __MOTION_MODEL_H
#define __MOTION_MODEL_H

#include "sys.h"

typedef struct
{
	s16 Vx;   																			
	s16 Vy;    																			
	s16 Vspin;    																			
	
}MotorControlType;



void Chassis_Algorithm_Model(uint16_t VxSpeed,uint16_t VySpeed,uint16_t Vspin);

#endif
