#include "sys.h"
#include "stm32f10x_it.h" 
#include "can.h"
#include "pstwo.h"

#define  LED   ZY_GD.ZY_Type.DATA_16
extern 	 GD    ZY_GD;
extern   RC_Ctl_t test;
extern int PS2_Key;
uint16_t nCount=0;
extern EncoderType GetEncoder;


void TIM6_IRQHandler(void)
{
	//清除中断
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
	//获取编码器的值
	Encoder_Get_Config();
	
	//通过编码器获取的值进行绝对是PID计算
	//然后进行赋值
	MotorOne_PidContorl();
	MotorTwo_PidContorl();
	MotorThr_PidContorl();
  MotorFor_PidContorl();
}

int T_C = 0;
void TIM7_IRQHandler(void)
{
	//清除中断
	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);
	//PS2按键值获取
	Select_PS2();
}

//圈数计算
void TIM2_IRQHandler(void)
{
  if (TIM2 -> CR1 & 0X0010)		  //小心注意
   {
			GetEncoder.rcnt1 -= 1;
   }
   else GetEncoder.rcnt1 += 1;

   TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 
}



/////////////////

void TIM3_IRQHandler(void)
{
  if (TIM3 -> CR1 & 0X0010)		  //小心注意
   {
			GetEncoder.rcnt2 -= 1;
   }
   else GetEncoder.rcnt2 += 1;

   TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
}

//////////////////

void TIM4_IRQHandler(void)
{
  if (TIM4 -> CR1 & 0X0010)		  //小心注意
   {
			GetEncoder.rcnt3 -= 1;
   }
   else GetEncoder.rcnt3 += 1;
   TIM_ClearITPendingBit(TIM4, TIM_IT_Update); 
}

void TIM5_IRQHandler(void)
{
  if (TIM5 -> CR1 & 0X0010)		  //小心注意
   {
			GetEncoder.rcnt4 -= 1;
   }
   else GetEncoder.rcnt4 += 1;
   TIM_ClearITPendingBit(TIM5, TIM_IT_Update); 
}


 
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
