#ifndef __CONTROL_H
#define __CONTROL_H

#include "sys.h"

//extern EncoderType GetEncoder;
//extern s16 MotorspeedOne,MotorspeedTwo,MotorSpeedThr,MotorSpeedFor;
//int M1,M2,M3;
    
//#define kp			500  	//����ϵ��
//#define ki			15 	//����ϵ��
//#define kd			100  	//΢��ϵ��
#define errILim	    500	//����������

//#define TargetSpeetOne    20;
//#define TargetSpeetTwo    20;
//#define TargetSpeetThr    20;
//#define TargetSpeetFor    20;


typedef struct
{
	float errNow;//��ǰ�����
	float ctrOut;//���������

	/*PID�㷨�ڲ���������ֵ�����޸�*/
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

