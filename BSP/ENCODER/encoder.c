#include "encoder.h"


//*************��������ȡ �� ��ǰ�ٶȼ���
EncoderType GetEncoder;

void EncodeOne_Get(void)
{
	s32 CNT1_Now,CNT1_Last;
	GetEncoder.cnt1=TIM2->CNT;                      //��ȡ��ǰ��������
	CNT1_Last=GetEncoder.CNT1;                      //��һ�α�������
	CNT1_Now=GetEncoder.cnt1+(GetEncoder.rcnt1*(ECDPeriod+1));//��ǰת������������
	GetEncoder.V1=CNT1_Now-CNT1_Last;                 //��ǰ����ٶ�=��ǰ����-�ϴ�����
	GetEncoder.CNT1=CNT1_Now;                          //��ǰ������ֵ����һ�μ�����ϴ�����
}

void EncodeTwo_Get(void)
{
	s32 CNT2_Now,CNT2_Last;
	GetEncoder.cnt2=TIM3->CNT;
	CNT2_Last=GetEncoder.CNT2;
	CNT2_Now=GetEncoder.cnt2+(GetEncoder.rcnt2*(ECDPeriod+1));
	GetEncoder.V2=CNT2_Now-CNT2_Last;
	GetEncoder.CNT2=CNT2_Now;
}

void EncodeThr_Get(void)
{
	s32 CNT3_Now,CNT3_Last;
	GetEncoder.cnt3=TIM4->CNT;
	CNT3_Last=GetEncoder.CNT3;
	CNT3_Now=GetEncoder.cnt3+(GetEncoder.rcnt3*(ECDPeriod+1));
	GetEncoder.V3=CNT3_Now-CNT3_Last;
	GetEncoder.CNT3=CNT3_Now;
}

void EncodeFor_Get(void)
{
	s32 CNT4_Now,CNT4_Last;
	GetEncoder.cnt4=TIM5->CNT;                      //��ȡ��ǰ��������
	CNT4_Last=GetEncoder.CNT4;                      //��һ�α�������
	CNT4_Now=GetEncoder.cnt4+(GetEncoder.rcnt4*(ECDPeriod+1));//��ǰת������������
	GetEncoder.V4=CNT4_Now-CNT4_Last;                 //��ǰ����ٶ�=��ǰ����-�ϴ�����
	GetEncoder.CNT4=CNT4_Now;                          //��ǰ������ֵ����һ�μ�����ϴ�����
}

void Encoder_Get_Config(void)
{
	EncodeOne_Get();
	EncodeTwo_Get();
	EncodeThr_Get();
  EncodeFor_Get();
}

