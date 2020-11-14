#ifndef __GPIO_H
#define __GPIO_H

#include "sys.h"

//控制电机正反转
#define MotorOne_Clockwise  		{GPIO_SetBits(Motor_Aspect_PORT,  GPIO_Pin_1)	;	GPIO_ResetBits(Motor_Aspect_PORT,  GPIO_Pin_2);}
#define MotorTwo_Clockwise  		{GPIO_SetBits(Motor_Aspect_PORT,  GPIO_Pin_3)	;	GPIO_ResetBits(Motor_Aspect_PORT,  GPIO_Pin_4);}
#define MotorThr_Clockwise  		{GPIO_SetBits(Motor_Aspect_PORT,  GPIO_Pin_5)	;	GPIO_ResetBits(Motor_Aspect_PORT,  GPIO_Pin_10);}
#define MotorFor_Clockwise          {GPIO_SetBits(Motor_Aspect_PORT,  GPIO_Pin_11)	;	GPIO_ResetBits(Motor_Aspect_PORT,  GPIO_Pin_12);}

#define MotorOne_Anticlockwise     	{GPIO_SetBits(Motor_Aspect_PORT,  GPIO_Pin_2)	;	GPIO_ResetBits(Motor_Aspect_PORT,  GPIO_Pin_1);}
#define MotorTwo_Anticlockwise     	{GPIO_SetBits(Motor_Aspect_PORT,  GPIO_Pin_4)	;	GPIO_ResetBits(Motor_Aspect_PORT,  GPIO_Pin_3);}
#define MotorThr_Anticlockwise      {GPIO_SetBits(Motor_Aspect_PORT,  GPIO_Pin_10)	;	GPIO_ResetBits(Motor_Aspect_PORT,  GPIO_Pin_5);}
#define MotorFor_Anticlockwise      {GPIO_SetBits(Motor_Aspect_PORT,  GPIO_Pin_12)	;	GPIO_ResetBits(Motor_Aspect_PORT,  GPIO_Pin_11);}

#define MotorOne_Stop			    {GPIO_ResetBits(Motor_Aspect_PORT,  GPIO_Pin_1)	;	GPIO_ResetBits(Motor_Aspect_PORT,  GPIO_Pin_2);}
#define MotorTwo_Stop     			{GPIO_ResetBits(Motor_Aspect_PORT,  GPIO_Pin_3)	;	GPIO_ResetBits(Motor_Aspect_PORT,  GPIO_Pin_4);}
#define MotorThr_Stop     			{GPIO_ResetBits(Motor_Aspect_PORT,  GPIO_Pin_5)	;	GPIO_ResetBits(Motor_Aspect_PORT,  GPIO_Pin_10);}
#define MotorFor_Stop               {GPIO_ResetBits(Motor_Aspect_PORT,  GPIO_Pin_11)	;	GPIO_ResetBits(Motor_Aspect_PORT,  GPIO_Pin_12);}


#define Motor_Aspect_PORT   GPIOC

#define Motor_Aspect_CLK    RCC_APB2Periph_GPIOC   //用PC0-3

//stm32跑马灯配置
#define LED0_PORT   GPIOA
#define LED0_Pin    GPIO_Pin_8
#define LED0_CLK    RCC_APB2Periph_GPIOA

#define LED1_PORT   GPIOD
#define LED1_Pin    GPIO_Pin_2
#define LED1_CLK    RCC_APB2Periph_GPIOD

#define LED0 PAout(8)// PE5
#define LED1 PDout(2)// PB5	


void LED_GPIO_Config(void);

void GPIO_Aspect_Config(void);
void GPIO_Config(uint32_t RCC_APB2Periph, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode);

#endif

