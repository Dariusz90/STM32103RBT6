#include "LMP91200.h"
#include "delay.h"
#include "spi.h"
//Mini STM32������
//NRF24L01 �������� 
//����ԭ��@ALIENTEK
//2010/6/16	  
	 
 							    
//��ʼ��LMP91200��SPI��
void LMP91200_Init(void)
	{
	GPIO_InitTypeDef GPIO_InitStructure;
 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE );	

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);

//	GPIO_SetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	GPIO_SetBits(GPIOC,GPIO_Pin_4);

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU  ;   //��������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);

	SPIx_Init();    //��ʼ��SPI
	

//	Set_LMP91200_CSN;    //SPIƬѡȡ��
	}



