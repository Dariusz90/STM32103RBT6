#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "lcd.h"
#include "myiic.h"
#include "LMP91000.h"
#include "ds18b20.h"
#include "adc.h"
#include "spi.h"
#include "LMP91200.h"

//Mini STM32�����巶������16
//IIC ʵ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com



const u8 TEXT_Buffer[]={"MiniSTM32 IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)
int main(void)
 {
//	u8 key;
//	u16 i=0;
	u16 adc_91000,adc_91200,reg_read_data=0,reg_write_data=0;
	float LMP91000_VOUT,LMP91200_VOUT,Temp_Integer,Temp_Decimal;
 	short temp;
	u8 read_val[5] = {0xff};
    u8 status = TI_LMP91000_NOT_READY; 
 	SystemInit();
	delay_init(72);	     //��ʱ��ʼ��
	NVIC_Configuration();
 	uart_init(9600);
 	LED_Init();
 	KEY_Init();
	Adc_Init();
	IIC_Init();			//IIC��ʼ��
	LMP91200_Init();    //��ʼ��PH
	delay_ms(500);
	printf("\nHello XXL");



/************************************************************
* �����缫��ʼ�������ݲɼ�
************************************************************/	
	LMP91000_ENABLE();
																				 // enable LM
    while (status == TI_LMP91000_NOT_READY)                                      // wait while device is not ready
    	status = LMP91000_ReadOneByte(TI_LMP91000_STATUS_REG);                   // Read device ready status

	read_val[0] = LMP91000_ReadOneByte(TI_LMP91000_LOCK_REG);                     // Read from lock register default value 0x01
	read_val[1] = LMP91000_ReadOneByte(TI_LMP91000_TIACN_REG);                    // Read TIA control register default value 0x03
	read_val[2] = LMP91000_ReadOneByte(TI_LMP91000_REFCN_REG);                    // Read Reference control register default value 0x20
	read_val[3] = LMP91000_ReadOneByte(TI_LMP91000_MODECN_REG);                   // Read Mode control register default value 0x00
  
	LMP91000_WriteOneByte(TI_LMP91000_LOCK_REG, TI_LMP91000_WRITE_UNLOCK);        // unlock the registers for write
 
	LMP91000_WriteOneByte(TI_LMP91000_TIACN_REG, TIACN_NEW_VALUE);                // Modify TIA control register
	LMP91000_WriteOneByte(TI_LMP91000_REFCN_REG, REFCN_NEW_VALUE);                // Modify REF control register
	LMP91000_WriteOneByte(TI_LMP91000_MODECN_REG, MODECN_NEW_VALUE);              // Modify MODE control register

	read_val[1] = LMP91000_ReadOneByte(TI_LMP91000_TIACN_REG);                    // Read to confirm register is modified
	read_val[2] = LMP91000_ReadOneByte(TI_LMP91000_REFCN_REG);                    // Read to confirm register is modified
	read_val[3] = LMP91000_ReadOneByte(TI_LMP91000_MODECN_REG);                   // Read to confirm register is modified
	read_val[4] = LMP91000_ReadOneByte(TI_LMP91000_STATUS_REG);  
// test if write/read values match
	if (read_val[1] == TIACN_NEW_VALUE)
	{
//    while (1)                                                                  // no error: blink LED continuously
//    {
        delay_ms(500);
        LED1=!LED1;//�̵���˸
//    } 
	} else
	{
		delay_ms(500);
		LED0=!LED0;//�����˸                            // error
	}   

// ��ȡLMP91000�����ѹ
//    while(1)
//    {	
       adc_91000=Get_Adc(ADC_Channel_8);
	   LMP91000_VOUT=(float)adc_91000*(3.3/4096);
	   LMP91000_VOUT=LMP91000_VOUT;
	   printf("\n\nDO=%fv ",LMP91000_VOUT);

	   temp=DS18B20_Get_Temp();
	   if(temp<0)
	   {
			temp=-temp;
	   }
	   Temp_Integer=temp/10;
	   Temp_Integer=Temp_Integer;	   //����
	   Temp_Decimal=temp%10;
	   Temp_Decimal=Temp_Decimal;	   //С��
       printf(" Temp=%f.%fc " __TIME__ "",Temp_Integer,Temp_Decimal);

   	   delay_ms(1000);
//    }
	LMP91000_WriteOneByte(TI_LMP91000_LOCK_REG, TI_LMP91000_WRITE_LOCK);          // lock the registers  
	LMP91000_DISABLE();

/************************************************************
* PH�缫��ʼ�������ݲɼ�,�����ڿ�������ˮ����ˮ��vout����1.420��1.429�����ܵ缫����
************************************************************/	

  Clr_LMP91200_CSN;
  	
  reg_write_data = TI_LMP91200_CONFIG_REG_TEST_VALUE;                               // value to write 
  reg_read_data = SPIx_ReadWriteByte(reg_write_data);                     // Write to config register, read old value  
  reg_read_data = SPIx_ReadWriteByte(reg_write_data);                     // Write again to read previous update
  reg_read_data = SPIx_ReadWriteByte(reg_write_data);                     // Write again to read previous update,if not read this time,bit-15 will be wrong
  
//  Set_LMP91200_CSN;
while(1)
  // test if write/read values match
{

    if (reg_write_data == reg_read_data)
    {
	    adc_91200=Get_Adc(ADC_Channel_9);
	    LMP91200_VOUT=(float)adc_91200*(3.3/4096);
	    LMP91200_VOUT=LMP91200_VOUT;
		LED1=!LED1;								   //��ȷ���̵���
	    delay_ms(500);	
    }
    else
    {
	    LED0=!LED0;								   //������Ƶ���
	    delay_ms(300);
    }
}

/************************************************************
* �¶ȴ�������ʼ�������ݲɼ�
************************************************************/	

	while(DS18B20_Init())//��ʼ��DS18B20,����18B20
	{
		delay_ms(600);
//		error_report();//DS18B20 δ����
	}

	while(1)
	{
	 	temp=DS18B20_Get_Temp();
		if(temp<0)
		{
			temp=-temp;
		}
		Temp_Integer=temp/10;
		Temp_Integer=Temp_Integer;	   //����
		Temp_Decimal=temp%10;
		Temp_Decimal=Temp_Decimal;	   //С��
		delay_ms(500);
		LED1=!LED1;//DS1��˸
	}





/************************************************************
* ����ɨ��
************************************************************/	


	  
#if 0
	while(1)
	{
		key=KEY_Scan();
		if(key==1)//KEY0����,д��24C02
		{
           ;
		}
		if(key==3)//KEY_UP����,��ȡ�ַ�������ʾ
		{
           ;
		}
		i++;
		delay_ms(10);

	}
#endif
 }

