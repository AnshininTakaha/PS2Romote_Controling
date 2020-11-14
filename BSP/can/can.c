#include "can.h"

/*
 * ��������CAN_GPIO_Config
 * ����  ��CAN��GPIO ����
 * ����  ����
 * ���  : ��
 * ����  ���ڲ�����
 */
static void CAN_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//����GPIOB��AFIOʱ��
	RCC_APB2PeriphClockCmd(CAN_RX_CLK|CAN_TX_CLK, ENABLE);
	//�����ض���
//	GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
	//����CAN��������   
	GPIO_InitStruct.GPIO_Pin   =  CAN_RX_Pin;
	GPIO_InitStruct.GPIO_Mode  =  GPIO_Mode_IPU;//����Ϊ��������ģʽ
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(CAN_RX_PORT, &GPIO_InitStruct);
	//����CAN�������   
	GPIO_InitStruct.GPIO_Pin   =  CAN_TX_Pin;
	GPIO_InitStruct.GPIO_Mode  =  GPIO_Mode_AF_PP;//����Ϊ�����������ģʽ
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(CAN_TX_PORT, &GPIO_InitStruct);

}	

/*
 * ��������CAN_MODE_Config
 * ����  ��CAN��ģʽ ����
 * ����  ����
 * ���  : ��
 * ����  ���ڲ�����
 */
void CAN_MODE_Config(void)
{
	CAN_InitTypeDef CAN_Initstruct;
	
	RCC_APB1PeriphClockCmd(CAN_CLK, ENABLE);
		/*CAN�Ĵ�����ʼ��(ʹ������ȶ�)*/
	CAN_DeInit(CANx);
	CAN_StructInit(&CAN_Initstruct);
		/*CAN�Ĵ�������*/
	CAN_Initstruct.CAN_TTCM = DISABLE;                 //MCR-TTCM  �ر�ʱ�䴥��ͨ�Ź���
	CAN_Initstruct.CAN_ABOM = DISABLE;                  //MCR-ABOM  ʹ���Զ����߹��� 
	CAN_Initstruct.CAN_AWUM = DISABLE;                  //MCR-AWUM  �����Զ�����ģʽ
	CAN_Initstruct.CAN_NART = DISABLE;                 //MCR-NART  ��ֹ�����Զ��ش�
	CAN_Initstruct.CAN_RFLM = DISABLE;                 //MCR-RFLM  �رս���FIFO ��������  ���ʱ�±��ĻḲ��ԭ�б���  
	CAN_Initstruct.CAN_TXFP = ENABLE;                 /*MCR-TXFP  ����FIFO���ȼ�  DISABLE-���ȼ�ȡ���ڱ���ID 
	                                                               ENABLE-���ȼ�ȡ���ڱ��Ĵ��뷢��������Ⱥ�˳��*/
	CAN_Initstruct.CAN_Mode = CAN_Mode_Normal;       //�ػ�����ģʽ��CAN_Mode_LoopBack   ��������ģʽ��CAN_Mode_Normal
	
	/* ss=1���̶���
	 * bs1=5
	 * bs2=3         ��λʱ����Ϊ (1+5+3) tq
	 * BRP=4         �����ʼ�Ϊ 36/((1+5+3)*4) = 1 Mbps
	 */
	CAN_Initstruct.CAN_BS1 = CAN_BS1_5tq;              //BTR-TS1 ʱ���1 ��Ϊ5tq
	CAN_Initstruct.CAN_BS2 = CAN_BS2_3tq;              //BTR-TS1 ʱ���2 ��Ϊ3tq
	CAN_Initstruct.CAN_SJW = CAN_SJW_1tq;              //BTR-SJW ����ͬ����Ծ��� ��Ϊ2tq
	CAN_Initstruct.CAN_Prescaler = 4;                  //BTR-BRP �����ʷ�Ƶ��  4��Ƶ
	
	CAN_Init(CANx, &CAN_Initstruct);
}

/*
 * ��������CAN_Filter_Config
 * ����  ��CAN�Ĺ����� ����
 * ����  ����
 * ���  : ��
 * ����  ���ڲ�����
 */
void CAN_Filter_Config(void)
{
	CAN_FilterInitTypeDef CAN_FilterInitstruct;
	
	CAN_FilterInitstruct.CAN_FilterNumber = 0;                              //ѡ��ɸѡ����    0-13
	CAN_FilterInitstruct.CAN_FilterMode = CAN_FilterMode_IdMask;            //����������ģʽ
	CAN_FilterInitstruct.CAN_FilterScale = CAN_FilterScale_32bit;           //ѡ��ɸѡ��λ��Ϊ����32λ��

	CAN_FilterInitstruct.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitstruct.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitstruct.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitstruct.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitstruct.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;       //ɸѡ����������FIFO0
	
	CAN_FilterInitstruct.CAN_FilterActivation = ENABLE;                     //ʹ��ɸѡ��
	/*CANɸѡ���ṹ���ʼ��*/
	CAN_FilterInit(&CAN_FilterInitstruct);
	
	/*ʹ��CANͨ���ж�*/
	CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);         //FIFO0�����ж�
//	CAN_ITConfig(CANx,CAN_IT_TME,ENABLE);

}

/*
 * ��������CAN_Config
 * ����  ����������CAN�Ĺ���
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void CAN_Config(void)
{
	CAN_GPIO_Config();
	CAN_MODE_Config();
	CAN_Filter_Config();
}

/*
 * ��������CAN_RxMes_Init
 * ����  ����ʼ�� Rx Message���ݽṹ��			RxMessage: ָ��Ҫ��ʼ�������ݽṹ��
 * ����  �����ܱ��Ľṹ��
 * ���  : ��
 * ����  ���ⲿ����
 */
void CAN_RxMes_Init(CanRxMsg *RxMessage)
{
	uint8_t ubCounter;
	
	RxMessage->StdId = 0x00;                            //���汨�ĵı�׼��ʶ��11λ��0-0x7FF       ��λ
	RxMessage->ExtId = 0x00;                            //���汨�ĵ���չ��ʶ��29λ��0-0x1FFFFFFF  ��λ
	RxMessage->IDE = CAN_Id_Standard;                   //IDE��չ��ʶ��                           ��λ
//	RxMessage->RTR = CAN_RTR_Data;                      //�������ͱ�־λ��                        ��λ
	RxMessage->DLC = 0;                                 //����֡�����ݶγ��ȣ�0-8                 ��λ
	RxMessage->FMI = 0;                                 //ѡ��ɸѡ�����                          ��λ
	
	for(ubCounter = 0; ubCounter < 8; ubCounter++)
	{
		RxMessage->Data[ubCounter] = 0x00;                //�������ݶ�����                          ��λ
	}
	
}


CanRxMsg RxMessage;
GD ZY_GD;
void USB_LP_CAN1_RX0_IRQHandler(void)
{

	 if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)
	{
        CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
        CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
        
				if((RxMessage.StdId==0x03) && (RxMessage.IDE==CAN_ID_STD ))
				{
					ZY_GD.ZY_Type.DATA_8[0]=RxMessage.Data[0];
					ZY_GD.ZY_Type.DATA_8[1]=RxMessage.Data[1];
				}      
   }
}