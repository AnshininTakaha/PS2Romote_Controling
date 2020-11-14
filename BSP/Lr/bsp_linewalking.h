#ifndef __BSP_LINEWALKING_H__
#define __BSP_LINEWALKING_H__	

#ifdef __cplusplus
 extern "C"
#endif

#include "stm32f10x.h"

#define LineWalk_X1_RCC		RCC_APB2Periph_GPIOC
#define LineWalk_X2_RCC		RCC_APB2Periph_GPIOC
#define LineWalk_X3_RCC   RCC_APB2Periph_GPIOC
#define LineWalk_X4_RCC		RCC_APB2Periph_GPIOC

#define LineWalk_X1_PIN		GPIO_Pin_10
#define LineWalk_X2_PIN		GPIO_Pin_2
#define LineWalk_X3_PIN	    GPIO_Pin_11
#define LineWalk_X4_PIN	    GPIO_Pin_3

#define LineWalk_X1_PORT	GPIOC
#define LineWalk_X2_PORT	GPIOC
#define LineWalk_X3_PORT	GPIOC
#define LineWalk_X4_PORT	GPIOC


void GetLineWalking_GPIO(void);
void test_Line(void);             
void Hw_config(void);

#endif
