#ifndef __CONTROL_H
#define __CONTROL_H

#include "sys.h"

//extern EncoderType GetEncoder;
//extern s16 MotorspeedOne,MotorspeedTwo,MotorSpeedThr,MotorSpeedFor;
//int M1,M2,M3;
    
//#define kp			500  	//比例系数
//#define ki			15 	//积分系数
//#define kd			100  	//微分系数
#define errILim	    500	//误差积分上限

//#define TargetSpeetOne    20;
//#define TargetSpeetTwo    20;
//#define TargetSpeetThr    20;
//#define TargetSpeetFor    20;


typedef struct
{
	float errNow;//当前的误差
	float ctrOut;//控制量输出

	/*PID算法内部变量，其值不能修改*/
	float errOld;
	float errP;
	float errI;
	float errD;
    float kp;
    float ki;
    float kd;
}PID_AbsoluteType;

void PID_AbsoluteMode(PID_AbsoluteType* PID);
void MotorOne_PidContorl(void);
void MotorTwo_PidContorl(void);
void MotorThr_PidContorl(void);
void MotorFor_PidContorl(void);

#endif 

