#ifndef __PSTWO_H
#define __PSTWO_H
#include "stm32f10x.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "delay.h"

#define DELAY_TIME  delay_us(5) 
#define getBit(value, pos) ((value >> pos) & 1)
#define setBit(value, pos) value|(1 << pos)
#define clrBit(value, pos) value&(~(1 << pos))
#define toggleBit(value, pos) value^(1 << pos)
/*********************************************************
Copyright (C), 2015-2025, YFRobot.
www.yfrobot.com
File��PS2��������
Author��pinggai    Version:1.1     Data:2015/10/20
Description: PS2��������
             ���ӹ��ܣ�
			 1���������á����ģʽ�������̵�ģʽ�������������á����桱��ͨ���ֱ���ģʽ�������޷��ı�
			 2�������ֱ��𶯣�ͨ����ֵ�����ã��ı������𶯵����Ƶ�ʡ�
			                  ͨ����ֵ�����ã������Ҳ�С�𶯵����
History:  
V1.0: 	2015/05/16
1���ֱ����룬ʶ�𰴼�ֵ����ȡģ��ֵ��       
**********************************************************/	 
#define DI   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)            //PB12  ����

#define DO_H GPIO_SetBits(GPIOB, GPIO_Pin_13)        //����λ��
#define DO_L GPIO_ResetBits(GPIOB, GPIO_Pin_13)        //����λ��

#define CS_H GPIO_SetBits(GPIOB, GPIO_Pin_14)       //CS����
#define CS_L GPIO_ResetBits(GPIOB, GPIO_Pin_14)      //CS����

#define CLK_H GPIO_SetBits(GPIOB, GPIO_Pin_15)      //ʱ������
#define CLK_L GPIO_ResetBits(GPIOB, GPIO_Pin_15)      //ʱ������


//These are our button constants
#define PSB_SELECT      1
#define PSB_L3          2
#define PSB_R3          3
#define PSB_START       4
#define PSB_PAD_UP      5
#define PSB_PAD_RIGHT   6
#define PSB_PAD_DOWN    7
#define PSB_PAD_LEFT    8
#define PSB_L2          9
#define PSB_R2          10
#define PSB_L1          11
#define PSB_R1          12
#define PSB_GREEN       13
#define PSB_RED         14
#define PSB_BLUE        15
#define PSB_PINK        16

#define PSB_TRIANGLE    13
#define PSB_CIRCLE      14
#define PSB_CROSS       15
#define PSB_SQUARE      16

//#define WHAMMY_BAR		8

//These are stick values
#define PSS_RX 5                //��ҡ��X������
#define PSS_RY 6
#define PSS_LX 7
#define PSS_LY 8

extern u8 Data[9];
extern u16 MASK[16];
extern u16 Handkey;

void PS2_Init(void);
u8 PS2_RedLight(void);   //�ж��Ƿ�Ϊ���ģʽ
void PS2_ReadData(void); //���ֱ�����
void PS2_Cmd(u8 CMD);		  //���ֱ���������
u8 PS2_DataKey(void);		  //����ֵ��ȡ
bool PS2_isKey(u16 key);
u8 PS2_AnologData(u8 button); //�õ�һ��ҡ�˵�ģ����
void PS2_ClearData(void);	  //������ݻ�����
void PS2_Vibration(u8 motor1, u8 motor2);//������motor1  0xFF���������أ�motor2  0x40~0xFF

void PS2_EnterConfing(void);	 //��������
void PS2_TurnOnAnalogMode(void); //����ģ����
void PS2_VibrationMode(void);    //������
void PS2_ExitConfing(void);	     //�������
void PS2_SetInit(void);		     //���ó�ʼ��
void Select_PS2();
#endif




