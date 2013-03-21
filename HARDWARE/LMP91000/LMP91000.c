#include "LMP91000.h" 
//#include "delay.h" 
#include "delay.h"
//Mini STM32������
//24CXX��������(�ʺ�24C01~24C16,24C32~256δ��������!�д���֤!)
//����ԭ��@ALIENTEK
//2010/6/10
//V1.2


//��LMP91000ָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
u8 LMP91000_ReadOneByte(u8 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	IIC_Send_Byte(LMP91000_I2C_Address_W);	   //����������ַ
	IIC_Wait_Ack();
	IIC_Send_Byte(ReadAddr);	   //���ͼĴ�����ַ
	IIC_Wait_Ack();

	IIC_Start();  	 	   
	IIC_Send_Byte(LMP91000_I2C_Address_R);	   //����������ַ		   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);
	IIC_NAck();		   
    IIC_Stop();//����һ��ֹͣ����	    
	return temp;
}

//��LMP91000ָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void LMP91000_WriteOneByte(u8 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    IIC_Start();  
	IIC_Send_Byte(LMP91000_I2C_Address_W);	   //����������ַ	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr);   //���ͼĴ�����ַ
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //�����ֽ�							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//����һ��ֹͣ����
	delay_ms(10);	 
}



//���LMP91000�Ƿ�ready
//����1:ready
//����0:not ready��default��
u8 LMP91000_Status(void)
{
	u8 temp;
//	LM91000_ENABLE();
	temp=LMP91000_ReadOneByte(TI_LMP91000_STATUS_REG);			   
//	LM91000_DISABLE();
	return temp;											  
}


 void LMP91000_ENABLE(void)
 {
    GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PC�˿�ʱ��
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 //PC.6 �˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
 	GPIO_ResetBits(GPIOC,GPIO_Pin_6);						 //PC.6 ���0

 }


 void LMP91000_DISABLE(void)
 {
    GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PC�˿�ʱ��
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 //PC.6 �˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOC,GPIO_Pin_6);						 //PC.6 ���1

 }







