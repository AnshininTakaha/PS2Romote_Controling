#include "dji.h"

unsigned char sbus_rx_buffer[18];
short bb;
	RC_Ctl_t test;
	

void DJI_USART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	// 打开串口GPIO的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// 打开串口外设的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  // 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	  // 将USART Rx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = 100000;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No  ;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(USART1, &USART_InitStructure);
	//串口DMA
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
	// 使能串口
	USART_Cmd(USART1, ENABLE);	  
	//串口中断
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
}


void DJI_DMA_Init(void)
{
    DMA_InitTypeDef DMA_InitStructure;
	  // 开启DMA时钟
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		// 设置DMA源地址：串口数据寄存器地址*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR);;
		// 内存地址(要传输的变量的指针)
		DMA_InitStructure.DMA_MemoryBaseAddr =(uint32_t)&sbus_rx_buffer;
		// 方向：从内存到外设	
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
		// 传输大小	
		DMA_InitStructure.DMA_BufferSize = 18;
		// 外设地址不增	    
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		// 内存地址自增
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		// 外设数据单位	
		DMA_InitStructure.DMA_PeripheralDataSize = 
	  DMA_PeripheralDataSize_Byte;
		// 内存数据单位
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
		// DMA模式，一次或者循环模式
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular ;
		// 优先级：高
		DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; 
		// 禁止内存到内存的传输
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		// 配置DMA通道		   
		DMA_Init( DMA1_Channel5, &DMA_InitStructure);		
		//DMA中断使能
//		DMA_ITConfig(DMA1_Channel5,DMA_IT_TC,ENABLE);
		// 使能DMA
		DMA_Cmd ( DMA1_Channel5,ENABLE);
    
}



void DJI_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  /* 配置NVIC为优先级组1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /* DMA1 通道1*/
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
  /* 配置抢占优先级 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 配置子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断通道 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /* DMA1 通道1*/
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  /* 配置抢占优先级 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 配置子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  /* 使能中断通道 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


void RemoteDataProcess(uint8_t *pData)
{
if(pData == NULL)
{
return;
}
test.rc.ch0 = ((int16_t)pData[0] | ((int16_t)pData[1] << 8)) & 0x07FF;
test.rc.ch1 = (((int16_t)pData[1] >> 3) | ((int16_t)pData[2] << 5))
& 0x07FF;
test.rc.ch2 = (((int16_t)pData[2] >> 6) | ((int16_t)pData[3] << 2) |
((int16_t)pData[4] << 10)) & 0x07FF;
test.rc.ch3 = (((int16_t)pData[4] >> 1) | ((int16_t)pData[5]<<7)) &
0x07FF;
test.rc.s1 = ((pData[5] >> 4) & 0x000C) >> 2;
test.rc.s2 = ((pData[5] >> 4) & 0x0003);
test.mouse.x = ((int16_t)pData[6]) | ((int16_t)pData[7] << 8);
test.mouse.y = ((int16_t)pData[8]) | ((int16_t)pData[9] << 8);
test.mouse.z = ((int16_t)pData[10]) | ((int16_t)pData[11] << 8);
test.mouse.press_l = pData[12];
test.mouse.press_r = pData[13];
test.key.v = ((int16_t)pData[14]);

	test.rc.ch0 -=1024;
	test.rc.ch1 -=1024;
	test.rc.ch2 -=1012;
	test.rc.ch3 -=1024;
 
  Chassis_Algorithm_Model(test.rc.ch0,test.rc.ch1,test.rc.ch2);
	
	


}

void USART1_IRQHandler (void)
{
if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
{
	
	(void)USART1->SR;
	(void)USART1->DR;
	
	DMA_Cmd ( DMA1_Channel5 ,DISABLE);
//	count=DMA_GetCurrDataCounter(DMA1_Channel5);
//	printf("%d\n",count);
//	delay_ms(100);
//	 count++;

	DMA_SetCurrDataCounter(DMA1_Channel5, 18); 
	DMA1_Channel5->CCR |=0x0001;
	DMA_Cmd(DMA1_Channel5, ENABLE);
	if(DMA_GetCurrDataCounter(DMA1_Channel5) == 18)
		{  
				RemoteDataProcess(sbus_rx_buffer); 
		}	
		
//			RC_CtrlData.rc.ch3 -=1024;
//	    speed=(RC_CtrlData.rc.ch3)*0.9;
//			turn=(RC_CtrlData.rc.ch0)*0.4;
//       Speed_luo(turn,speed);
//			Speed_Turn(turn);
//      Speed_control(speed);

} 

}



