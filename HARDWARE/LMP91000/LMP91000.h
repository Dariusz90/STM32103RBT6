#ifndef __24CXX_H
#define __24CXX_H
#include "myiic.h"   
//Mini STM32������
//24CXX��������(�ʺ�24C01~24C16,24C32~256δ��������!�д���֤!)
//����ԭ��@ALIENTEK
//2010/6/10
//V1.2

u8 LMP91000_ReadOneByte(u8 ReadAddr);
void LMP91000_ENABLE(void);
void LMP91000_DISABLE(void);
u8 LMP91000_Status(void);
void LMP91000_WriteOneByte(u8 WriteAddr,u8 DataToWrite);

#endif



/************************************************************
* TI LMP91000 REGISTER SET ADDRESSES
************************************************************/

#define LMP91000_I2C_Address_R                         (0x91)                  // Device Address
#define LMP91000_I2C_Address_W                         (0x90)   
#define TI_LMP91000_STATUS_REG                         (0x00)                  /* Read only status register */
#define TI_LMP91000_LOCK_REG                           (0x01)                  /* Protection Register */
#define TI_LMP91000_TIACN_REG                          (0x10)                  /* TIA Control Register */
#define TI_LMP91000_REFCN_REG                          (0x11)                  /* Reference Control Register*/
#define TI_LMP91000_MODECN_REG                         (0x12)                  /* Mode Control Register */

#define TI_LMP91000_WRITE_LOCK                         (0x01)
#define TI_LMP91000_WRITE_UNLOCK                       (0x00)
#define TI_LMP91000_READY                              (0x01)
#define TI_LMP91000_NOT_READY                          (0x00)

/************************************************************
* TI LMP91000 REGISTER set VALUE
************************************************************/

#define TIACN_NEW_VALUE									(0x1f)	//0x1b:120k,100ohm   0x1f:350k,100ohm��ʵ��֤����RLOAD�������û��Ӱ��  
#define REFCN_NEW_VALUE									(0x4d)	//����Ϊ0xcd(ref_v=2.5V)�����Ϊ1.635V(air)~1.645V(water) ;
																//����Ϊ0x4d(ref_v=3.3V)�����Ϊ2.166V(air)~2.181V(water) ;
																// ���ó�0xdd�����۵缫�Ƿ���ˮ�adcxʼ����0x821��1.676v��

#define MODECN_NEW_VALUE								(0x03)	//ʵ��֤����ֻ������Ϊ3-lead,����Ϊ2-leadʱ���Ϊ0


/************************************************************
*������ѹΪ0.68V������ref_v=3.3V,������ѹΪ3.3��0.67��0.24=0.53V
*�������ѹ��Ϊ5V���򼫻���ѹΪ5��0.67��0.20=0.67V
*�缫�����Ϊ1��100nA���Ŵ�350k��vout=0.35��35mV����ADC�ֱ���
*Ϊ3.3/4.96=0.8mV��
*�������ᵽ���缫�ڿ�������ӦΪ60nA����vout=60nA��350k=21mV
*��������ˮ�Ϳ����У���VOUT���21mV����ɻ�����֤��·
*
************************************************************/




