#ifndef __24L01_H
#define __24L01_H	 		  
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//NRF24L01 ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/16 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  


/************************************************************
* TI LMP91200 REGISTER SET INITIALIZATION VALUES
************************************************************/

#define TI_LMP91200_CONFIG_REG_VALUE                  (0xB080)                 /* Temp Measurement, RTD, 2mA, PGA=5, VOCM=GND */                          
#define TI_LMP91200_CONFIG_REG_NEW_VALUE              (0xA080)                 /* Temp Measurement, RTD, 1mA, PGA=5, VOCM=GND */
#define TI_LMP91200_CONFIG_REG_TEST_VALUE             (0x0080)				   /* VOCM=GND */

#define Set_LMP91200_CSN  {GPIO_SetBits(GPIOC,GPIO_Pin_4);}
#define Clr_LMP91200_CSN  {GPIO_ResetBits(GPIOC,GPIO_Pin_4);}
		 
 

void LMP91200_Init(void);//��ʼ��

#endif











