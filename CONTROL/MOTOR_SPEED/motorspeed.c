#include "motorspeed.h "

//***********����ٶ�д��
void MotorSpeedSetOne(s32 MotorSpeed)
{
	s32 PWMOne_Set;
	
	//�޷�����ֹը��
    if(MotorSpeed > PWMPeriod-PWMLOSS)    MotorSpeed =   PWMPeriod-PWMLOSS ;//���� CCR��ֵ����С�ڻ����ARR��ֵ
	if(MotorSpeed <-(PWMPeriod-PWMLOSS))  MotorSpeed = -(PWMPeriod-PWMLOSS);
	
	//�ж�������
    if(MotorSpeed > 0)
	{
		PWMOne_Set=MotorSpeed;
		MotorOne_Clockwise;
	}
	if(MotorSpeed < 0) 
	{
		PWMOne_Set=-MotorSpeed;
		MotorOne_Anticlockwise;
	}
	
	TIM8->CCR1 = PWMOne_Set;//PC6
}
//////////////////////
void MotorSpeedSetTwo(s32 MotorSpeed)
{
	s32 PWMTwo_Set;
	
    if(MotorSpeed > PWMPeriod-PWMLOSS)    MotorSpeed =   PWMPeriod-PWMLOSS ;//���� CCR��ֵ����С�ڻ����ARR��ֵ
	if(MotorSpeed <-(PWMPeriod-PWMLOSS))  MotorSpeed = -(PWMPeriod-PWMLOSS);
	
    if(MotorSpeed > 0)
	{
		PWMTwo_Set=MotorSpeed;
		MotorTwo_Clockwise;
	}
	if(MotorSpeed < 0) 
	{
		PWMTwo_Set=-MotorSpeed;
		MotorTwo_Anticlockwise;
	}
	
	TIM8->CCR2 = PWMTwo_Set;//PC7
}
/////////////////////
void MotorSpeedSetThr(s32 MotorSpeed)
{
	s32 PWMThr_Set;
    
    if(MotorSpeed > PWMPeriod-PWMLOSS)    MotorSpeed =   PWMPeriod-PWMLOSS ;//���� CCR��ֵ����С�ڻ����ARR��ֵ
	if(MotorSpeed <-(PWMPeriod-PWMLOSS))  MotorSpeed = -(PWMPeriod-PWMLOSS);
	
    if(MotorSpeed > 0)
	{
		PWMThr_Set=MotorSpeed;
		MotorThr_Clockwise;
	}
	if(MotorSpeed < 0) 
	{
		PWMThr_Set=-MotorSpeed;
		MotorThr_Anticlockwise;
	}
	
	TIM8->CCR3 = PWMThr_Set;//PC8
}
/////////////////
void MotorSpeedSetFor(s32 MotorSpeed)
{
	s32 PWMFor_Set;
    
    if(MotorSpeed > PWMPeriod-PWMLOSS)    MotorSpeed =   PWMPeriod-PWMLOSS ;//���� CCR��ֵ����С�ڻ����ARR��ֵ
	if(MotorSpeed <-(PWMPeriod-PWMLOSS))  MotorSpeed = -(PWMPeriod-PWMLOSS);
	
    if(MotorSpeed > 0)
	{
		PWMFor_Set=MotorSpeed;
		MotorFor_Clockwise;
	}
	if(MotorSpeed < 0) 
	{
		PWMFor_Set=-MotorSpeed;
		MotorFor_Anticlockwise;
	}
	
	TIM8->CCR4 = PWMFor_Set;//PC9
}

