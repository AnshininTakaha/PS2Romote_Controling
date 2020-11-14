#ifndef __CAN_H
#define __CAN_H

#include "sys.h"

#define CANx          CAN1
#define CAN_CLK       RCC_APB1Periph_CAN1
#define CAN_RX_PORT   GPIOA
#define CAN_RX_Pin    GPIO_Pin_11
#define CAN_RX_CLK    RCC_APB2Periph_GPIOA

#define CAN_TX_PORT   GPIOA
#define CAN_TX_Pin    GPIO_Pin_12
#define CAN_TX_CLK    RCC_APB2Periph_GPIOA

typedef struct
{
	union
	{
		u8 DATA_8[2];
		u16 DATA_16;
	}ZY_Type;
	
}GD;

void CAN_GPIO_Config(void);
void CAN_MODE_Config(void);
void CAN_Filter_Config(void);
void CAN_Config(void);
void CAN_RxMes_Init(CanRxMsg *RxMessage);
void USB_LP_CAN1_RX0_IRQHandler(void);
																			 
#endif  /*__CAN_H*/


