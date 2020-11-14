#include "can.h"

/*
 * 函数名：CAN_GPIO_Config
 * 描述  ：CAN的GPIO 配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
static void CAN_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//开启GPIOB和AFIO时钟
	RCC_APB2PeriphClockCmd(CAN_RX_CLK|CAN_TX_CLK, ENABLE);
	//引脚重定义
//	GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
	//配置CAN输入引脚   
	GPIO_InitStruct.GPIO_Pin   =  CAN_RX_Pin;
	GPIO_InitStruct.GPIO_Mode  =  GPIO_Mode_IPU;//配置为上拉输入模式
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(CAN_RX_PORT, &GPIO_InitStruct);
	//配置CAN输出引脚   
	GPIO_InitStruct.GPIO_Pin   =  CAN_TX_Pin;
	GPIO_InitStruct.GPIO_Mode  =  GPIO_Mode_AF_PP;//配置为复用推挽输出模式
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(CAN_TX_PORT, &GPIO_InitStruct);

}	

/*
 * 函数名：CAN_MODE_Config
 * 描述  ：CAN的模式 配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
void CAN_MODE_Config(void)
{
	CAN_InitTypeDef CAN_Initstruct;
	
	RCC_APB1PeriphClockCmd(CAN_CLK, ENABLE);
		/*CAN寄存器初始化(使程序更稳定)*/
	CAN_DeInit(CANx);
	CAN_StructInit(&CAN_Initstruct);
		/*CAN寄存器配置*/
	CAN_Initstruct.CAN_TTCM = DISABLE;                 //MCR-TTCM  关闭时间触发通信功能
	CAN_Initstruct.CAN_ABOM = DISABLE;                  //MCR-ABOM  使能自动离线管理 
	CAN_Initstruct.CAN_AWUM = DISABLE;                  //MCR-AWUM  开启自动唤醒模式
	CAN_Initstruct.CAN_NART = DISABLE;                 //MCR-NART  禁止报文自动重传
	CAN_Initstruct.CAN_RFLM = DISABLE;                 //MCR-RFLM  关闭接收FIFO 锁定功能  溢出时新报文会覆盖原有报文  
	CAN_Initstruct.CAN_TXFP = ENABLE;                 /*MCR-TXFP  发送FIFO优先级  DISABLE-优先级取决于报文ID 
	                                                               ENABLE-优先级取决于报文存入发送邮箱的先后顺序*/
	CAN_Initstruct.CAN_Mode = CAN_Mode_Normal;       //回环工作模式：CAN_Mode_LoopBack   正常工作模式：CAN_Mode_Normal
	
	/* ss=1（固定）
	 * bs1=5
	 * bs2=3         单位时间宽度为 (1+5+3) tq
	 * BRP=4         波特率即为 36/((1+5+3)*4) = 1 Mbps
	 */
	CAN_Initstruct.CAN_BS1 = CAN_BS1_5tq;              //BTR-TS1 时间段1 设为5tq
	CAN_Initstruct.CAN_BS2 = CAN_BS2_3tq;              //BTR-TS1 时间段2 设为3tq
	CAN_Initstruct.CAN_SJW = CAN_SJW_1tq;              //BTR-SJW 重新同步跳跃宽度 设为2tq
	CAN_Initstruct.CAN_Prescaler = 4;                  //BTR-BRP 波特率分频器  4分频
	
	CAN_Init(CANx, &CAN_Initstruct);
}

/*
 * 函数名：CAN_Filter_Config
 * 描述  ：CAN的过滤器 配置
 * 输入  ：无
 * 输出  : 无
 * 调用  ：内部调用
 */
void CAN_Filter_Config(void)
{
	CAN_FilterInitTypeDef CAN_FilterInitstruct;
	
	CAN_FilterInitstruct.CAN_FilterNumber = 0;                              //选择筛选器组    0-13
	CAN_FilterInitstruct.CAN_FilterMode = CAN_FilterMode_IdMask;            //工作在掩码模式
	CAN_FilterInitstruct.CAN_FilterScale = CAN_FilterScale_32bit;           //选择筛选器位宽为单个32位。

	CAN_FilterInitstruct.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitstruct.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitstruct.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitstruct.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitstruct.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;       //筛选器被关联到FIFO0
	
	CAN_FilterInitstruct.CAN_FilterActivation = ENABLE;                     //使能筛选器
	/*CAN筛选器结构体初始化*/
	CAN_FilterInit(&CAN_FilterInitstruct);
	
	/*使能CAN通信中断*/
	CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);         //FIFO0接收中断
//	CAN_ITConfig(CANx,CAN_IT_TME,ENABLE);

}

/*
 * 函数名：CAN_Config
 * 描述  ：完整配置CAN的功能
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */
void CAN_Config(void)
{
	CAN_GPIO_Config();
	CAN_MODE_Config();
	CAN_Filter_Config();
}

/*
 * 函数名：CAN_RxMes_Init
 * 描述  ：初始化 Rx Message数据结构体			RxMessage: 指向要初始化的数据结构体
 * 输入  ：接受报文结构体
 * 输出  : 无
 * 调用  ：外部调用
 */
void CAN_RxMes_Init(CanRxMsg *RxMessage)
{
	uint8_t ubCounter;
	
	RxMessage->StdId = 0x00;                            //储存报文的标准标识符11位，0-0x7FF       复位
	RxMessage->ExtId = 0x00;                            //储存报文的扩展标识符29位，0-0x1FFFFFFF  复位
	RxMessage->IDE = CAN_Id_Standard;                   //IDE扩展标识，                           复位
//	RxMessage->RTR = CAN_RTR_Data;                      //报文类型标志位，                        复位
	RxMessage->DLC = 0;                                 //数据帧的数据段长度，0-8                 复位
	RxMessage->FMI = 0;                                 //选择筛选器编号                          复位
	
	for(ubCounter = 0; ubCounter < 8; ubCounter++)
	{
		RxMessage->Data[ubCounter] = 0x00;                //报文数据段内容                          复位
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