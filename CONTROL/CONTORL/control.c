#include "control.h"

extern EncoderType GetEncoder;
extern s16 TargetSpeedOne,TargetSpeedTwo,TargetSpeedThr,TargetSpeedFor;
//����ʽPID�㷨
void PID_AbsoluteMode(PID_AbsoluteType* PID)
{

	PID->errP = PID->errNow;  //��ȡ���ڵ�������kp����

	PID->errI += PID->errNow; //�����֣�����ki����

	if(errILim != 0)	   //΢�����޺�����
	{
	if(     PID->errI >  errILim)    PID->errI =  errILim;
	else if(PID->errI < -errILim)    PID->errI = -errILim;
	}

	PID->errD = PID->errNow - PID->errOld;//���΢�֣�����kd����

	PID->errOld = PID->errNow;	//�������ڵ����

	PID->ctrOut = PID->kp * PID->errP + PID->ki * PID->errI + PID->kd * PID->errD;//�������ʽPID���
}

s32 SpeedNowOne, SpeedControlOne;
s32 SpeedNowTwo, SpeedControlTwo;
s32 SpeedNowThr, SpeedControlThr;
s32 SpeedNowFor, SpeedControlFor;
PID_AbsoluteType PID_AbsoluteOne,PID_AbsoluteTwo,PID_AbsoluteThr,PID_AbsoluteFor;

void MotorOne_PidContorl(void)
{   
  PID_AbsoluteOne.kp=500; PID_AbsoluteOne.ki=15; PID_AbsoluteOne.kd=100;
	SpeedNowOne = GetEncoder.V1;
	PID_AbsoluteOne.errNow = TargetSpeedOne-SpeedNowOne;
	PID_AbsoluteMode(&PID_AbsoluteOne);
	SpeedControlOne = PID_AbsoluteOne.ctrOut;
	MotorSpeedSetOne(SpeedControlOne);
}

void MotorTwo_PidContorl(void)
{
	PID_AbsoluteTwo.kp=500; PID_AbsoluteTwo.ki=15; PID_AbsoluteTwo.kd=100;
  SpeedNowTwo = GetEncoder.V2;
	PID_AbsoluteTwo.errNow = TargetSpeedTwo-SpeedNowTwo;
	PID_AbsoluteMode(&PID_AbsoluteTwo);
	SpeedControlTwo = PID_AbsoluteTwo.ctrOut;
	MotorSpeedSetTwo(SpeedControlTwo);
}

void MotorThr_PidContorl(void)
{
	PID_AbsoluteThr.kp=500; PID_AbsoluteThr.ki=15; PID_AbsoluteThr.kd=100;
  SpeedNowThr = GetEncoder.V3;
	PID_AbsoluteThr.errNow = TargetSpeedThr-SpeedNowThr;
	PID_AbsoluteMode(&PID_AbsoluteThr);
	SpeedControlThr = PID_AbsoluteThr.ctrOut;
	MotorSpeedSetThr(SpeedControlThr);
}

void MotorFor_PidContorl(void)
{
	PID_AbsoluteFor.kp=300; PID_AbsoluteFor.ki=5; PID_AbsoluteFor.kd=50;
  SpeedNowFor = GetEncoder.V4;
	PID_AbsoluteFor.errNow = TargetSpeedFor-SpeedNowFor;
	PID_AbsoluteMode(&PID_AbsoluteFor);
	SpeedControlFor = PID_AbsoluteFor.ctrOut;
	MotorSpeedSetFor(SpeedControlFor);
}
