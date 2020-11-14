#include "stm32f10x.h"
#include "delay.h"
#include "can.h"
#include "pstwo.h"

#define  LED   ZY_GD.ZY_Type.DATA_16
extern 	 GD    ZY_GD;
extern   RC_Ctl_t test;
int PS2_Key;
 int main(void)
 {	
		delay_init();
    TIM_Configuration();
		PS2_Init();
	  LED_GPIO_Config(); 
    NVIC_Configuration();
    GPIO_Aspect_Config();
    while(1)
		{
    delay_ms(50);	 //延时很重要不可去，不然会炸鸡
			
			
		}
	}
