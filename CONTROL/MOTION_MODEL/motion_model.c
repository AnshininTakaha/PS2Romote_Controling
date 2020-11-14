#include "motion_model.h"


MotorControlType MotorControlDEF;
s16 TargetSpeedOne,TargetSpeedTwo,TargetSpeedThr,TargetSpeedFor;

//运动模型分析
//根据需要的X,Y，自旋的速度来对底盘的四个轮子进行判断

void Chassis_Algorithm_Model(uint16_t VxSpeed,uint16_t VySpeed,uint16_t Vspin)
{

    MotorControlDEF.Vx=VxSpeed;
    MotorControlDEF.Vy=VySpeed;
    MotorControlDEF.Vspin=Vspin;
      
    TargetSpeedOne = MotorControlDEF.Vx*0.71 + MotorControlDEF.Vy*0.71 - MotorControlDEF.Vspin;
    TargetSpeedTwo =-(-MotorControlDEF.Vx*0.71 + MotorControlDEF.Vy*0.71 - MotorControlDEF.Vspin);
		//TargetSpeedTwo =-MotorControlDEF.Vx*0.71 + MotorControlDEF.Vy*0.71 - MotorControlDEF.Vspin;
    TargetSpeedThr =-MotorControlDEF.Vx*0.71 - MotorControlDEF.Vy*0.71 - MotorControlDEF.Vspin;
    TargetSpeedFor =-(MotorControlDEF.Vx*0.71 - MotorControlDEF.Vy*0.71 - MotorControlDEF.Vspin);
		//TargetSpeedFor =MotorControlDEF.Vx*0.71 - MotorControlDEF.Vy*0.71 - MotorControlDEF.Vspin;
    
}

