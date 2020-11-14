#include "bsp_linewalking.h"
#include "stm32f10x.h"

int A,B,C,D=0;


//激活光电管的所有引脚 一共有4个
void GetLineWalking_GPIO(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin=LineWalk_X1_PIN;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=LineWalk_X2_PIN;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=LineWalk_X3_PIN;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=LineWalk_X4_PIN;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
}

void test_Line(void)
{ 
	//读取光电管的函数并把它赋值到 4个不同的值中 L_IN 左边里面的 L——OUT左边外面的
    A = GPIO_ReadInputDataBit (GPIOC, GPIO_Pin_10);
		B = GPIO_ReadInputDataBit (GPIOC, GPIO_Pin_2);
		C = GPIO_ReadInputDataBit (GPIOC, GPIO_Pin_11);
		D = GPIO_ReadInputDataBit (GPIOC, GPIO_Pin_3);
	
//  //通过判断灯的亮灭 来确定是左转 右转 直走 M是小转弯 P是大转弯
//	if((L_IN)&&(R_IN)&&(L_OUT==0)&&(R_OUT==0))	
// {
//	 go_straight=1;
// }
// else
//	 go_straight=0;

//	if((L_IN)&&(R_IN==0)&&(L_OUT==0)&&(R_OUT==0))
//	{
//	  M_turn_right=1;
//	}
//	else 
//		M_turn_right=0;
//	
//		if((R_IN)&&(L_IN==0)&&(R_OUT==0)&&(L_OUT==0))
//	{
//	  M_turn_left=1;
//	}
//	else 
//		M_turn_left=0;
//	
//		if((L_IN)&&(L_OUT)&&(R_IN==0)&&(R_OUT==0))
//	{
//	  P_turn_right=1;
//	}
//	else 
//		P_turn_right=0;
//	
//			if((R_IN)&&(R_OUT)&&(L_IN==0)&&(L_OUT==0))
//	{
//	  P_turn_left=1;
//	}
//	else 
//		P_turn_left=0;
//	
}
void Hw_config(void)
{
	test_Line();
	GetLineWalking_GPIO();
}
