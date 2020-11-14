#include "dji.h"

unsigned char sbus_rx_buffer[18];
short bb;
	RC_Ctl_t test;
	

void DJI_USART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	// �򿪴���GPIO��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// �򿪴��������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  // ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	  // ��USART Rx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = 100000;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No  ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(USART1, &USART_InitStructure);
	//����DMA
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
	// ʹ�ܴ���
	USART_Cmd(USART1, ENABLE);	  
	//�����ж�
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
}


void DJI_DMA_Init(void)
{
    DMA_InitTypeDef DMA_InitStructure;
	  // ����DMAʱ��
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		// ����DMAԴ��ַ���������ݼĴ�����ַ*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR);;
		// �ڴ��ַ(Ҫ����ı�����ָ��)
		DMA_InitStructure.DMA_MemoryBaseAddr =(uint32_t)&sbus_rx_buffer;
		// ���򣺴��ڴ浽����	
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
		// �����С	
		DMA_InitStructure.DMA_BufferSize = 18;
		// �����ַ����	    
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		// �ڴ��ַ����
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		// �������ݵ�λ	
		DMA_InitStructure.DMA_PeripheralDataSize = 
	  DMA_PeripheralDataSize_Byte;
		// �ڴ����ݵ�λ
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
		// DMAģʽ��һ�λ���ѭ��ģʽ
		DMA_InitStructure.DMA_Mode = DMA_Mode_Circular ;
		// ���ȼ�����
		DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh; 
		// ��ֹ�ڴ浽�ڴ�Ĵ���
		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
		// ����DMAͨ��		   
		DMA_Init( DMA1_Channel5, &DMA_InitStructure);		
		//DMA�ж�ʹ��
//		DMA_ITConfig(DMA1_Channel5,DMA_IT_TC,ENABLE);
		// ʹ��DMA
		DMA_Cmd ( DMA1_Channel5,ENABLE);
    
}



void DJI_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  /* ����NVICΪ���ȼ���1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /* DMA1 ͨ��1*/
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
  /* ������ռ���ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* ���������ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж�ͨ�� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /* DMA1 ͨ��1*/
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  /* ������ռ���ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* ���������ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  /* ʹ���ж�ͨ�� */
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



