#include "eeprom.h"

union Union_Data UnionDataERW;	//����union���͵ı���,���ڴ��ת����λ�����͵ĸ�����

rt_uint8_t byte_value = 0;
float Kp = 2.0;
float res = 0.5;

/* ���Ժ��� */
void at24c256_test(void)
{
	UnionDataERW.Data_Float=Kp;//д��Kp
	for(int i=0;i<4;i++)
	{
		AT24Cxx_WriteOneByte((0x00+i),UnionDataERW.Data_Unchar[3-i]);
	}
	for(int i=0;i<4;i++)//��ȡKp
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(0x00+i);
	}
	res=UnionDataERW.Data_Float;
	
//	char buffer[32];
//	sprintf(buffer, "%f\r\n", res);
//	rt_kprintf("%s", buffer);
}

/*******************************************************************************
* ��������  AT24Cxx_ReadOneByte
* ��������: ��ȡAT24Cxx�е�һ���ֽ�
* �����������
* �����������
* ����ֵ��  ��ȡAT24Cxx�е�һ���ֽ�
* �Ⱦ�������
* �����ú�����
* ����:    2015-03-05
*******************************************************************************/
uint8_t AT24Cxx_ReadOneByte(uint16_t addr)
{
  uint8_t temp = 0;
  
  I2C_Start();
  
  if(EE_TYPE > AT24C16)//���EE_TYPE > AT24C16����˫�ֽ�Ѱַ��������뵥�ֽ�Ѱַ
  {
    I2C_Send_Byte(0xA0);
    I2C_Wait_ACK();
    I2C_Send_Byte(addr>>8);//�������ݵ�ַ��λ  
  }
  else
  {
    I2C_Send_Byte(0xA0+((addr/256)<<1));//������ַ+���ݵ�ַ
  }
  
    I2C_Wait_ACK();
    I2C_Send_Byte(addr%256);//˫�ֽ�ʱ���������ݵ�ַ��λ�����ֽ�ʱ���������ݵ�ַ��λ
    I2C_Wait_ACK();
  
  I2C_Start();
  I2C_Send_Byte(0xA1+((addr/256)<<1));//�������ģʽ�������
  I2C_Wait_ACK();
  
  temp = I2C_Read_Byte(0);//0����NACK
  I2C_Stop();
  
  return temp;
}

/*******************************************************************************
* ��������  AT24Cxx_WriteOneByte
* ��������: ��AT24Cxx��дһ���ֽ�
* �����������
* �����������
* ����ֵ��  
* �Ⱦ�������
* �����ú�����
* ����:    2015-03-05
*******************************************************************************/
void AT24Cxx_WriteOneByte(uint16_t addr, uint8_t dt)
{
  I2C_Start();
  
  if(EE_TYPE > AT24C16)//���EE_TYPE > AT24C16����˫�ֽ�Ѱַ��������뵥�ֽ�Ѱַ
  {
    I2C_Send_Byte(0xA0);
    I2C_Wait_ACK();
    I2C_Send_Byte(addr>>8);//�������ݵ�ַ��λ  
  }
  else
  {
    I2C_Send_Byte(0xA0+((addr/256)<<1));//������ַ+���ݵ�ַ
  }
  
  I2C_Wait_ACK();
  I2C_Send_Byte(addr%256);//˫�ֽ�ʱ���������ݵ�ַ��λ�����ֽ�ʱ���������ݵ�ַ��λ
  I2C_Wait_ACK();
  
  I2C_Send_Byte(dt);
  I2C_Wait_ACK();
  I2C_Stop();
	rt_thread_delay(10);
  AT24Cxx_WRCheck(addr,dt);
}

/********************************************************************************
* ��������  AT24Cxx_WRCheck(uint16_t addr, uint8_t dt)
* ��������: ���д�뵥���ֽ��Ƿ���ȷ
* �����������
* �����������
* ����ֵ��  
* �Ⱦ�������
* �����ú�����
* ����:    2021-08-07
*********************************************************************************/
void AT24Cxx_WRCheck(uint16_t addr, uint8_t dt)
{
  if(AT24Cxx_ReadOneByte(addr)!=dt)
    AT24Cxx_WriteOneByte(addr,dt);
  else
    return;    
}