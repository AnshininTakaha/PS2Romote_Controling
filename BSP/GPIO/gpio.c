#include "gpio.h"

//*****************∑ΩœÚøÿ÷∆GPIO≈‰÷√
void GPIO_Aspect_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(Motor_Aspect_CLK, ENABLE);	
   
	
	GPIO_InitStruct.GPIO_Pin   =  GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode  =  GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(Motor_Aspect_PORT, &GPIO_InitStruct);
    

	GPIO_ResetBits(Motor_Aspect_PORT,  GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4| GPIO_Pin_10|GPIO_Pin_5|GPIO_Pin_12|GPIO_Pin_11);

}
//stm32≈‹¬Ìµ∆≈‰÷√
void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(LED0_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(LED1_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin   =  LED0_Pin;
	GPIO_InitStruct.GPIO_Mode  =  GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(LED0_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin   =  LED1_Pin;
	GPIO_InitStruct.GPIO_Mode  =  GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(LED1_PORT, &GPIO_InitStruct);


	GPIO_SetBits(LED0_PORT,  LED0_Pin);
	GPIO_SetBits(LED1_PORT,  LED1_Pin);

}

void GPIO_Config(uint32_t RCC_APB2Periph, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin; 

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
	
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}

