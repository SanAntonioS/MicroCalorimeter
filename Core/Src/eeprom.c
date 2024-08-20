#include "eeprom.h"

union Union_Data UnionDataERW;	//定义union类型的变量,用于打包转换上位机传送的浮点数

rt_uint8_t byte_value = 0;
float Kp = 2.0;
float res = 0.5;

/* 测试函数 */
void at24c256_test(void)
{
	UnionDataERW.Data_Float=Kp;//写入Kp
	for(int i=0;i<4;i++)
	{
		AT24Cxx_WriteOneByte((0x00+i),UnionDataERW.Data_Unchar[3-i]);
	}
	for(int i=0;i<4;i++)//读取Kp
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(0x00+i);
	}
	res=UnionDataERW.Data_Float;
	
//	char buffer[32];
//	sprintf(buffer, "%f\r\n", res);
//	rt_kprintf("%s", buffer);
}

/*******************************************************************************
* 函数名：  AT24Cxx_ReadOneByte
* 功能描述: 读取AT24Cxx中的一个字节
* 输入参数：无
* 输出参数：无
* 返回值：  读取AT24Cxx中的一个字节
* 先决条件：
* 被调用函数：
* 日期:    2015-03-05
*******************************************************************************/
uint8_t AT24Cxx_ReadOneByte(uint16_t addr)
{
  uint8_t temp = 0;
  
  I2C_Start();
  
  if(EE_TYPE > AT24C16)//如果EE_TYPE > AT24C16进入双字节寻址，否则进入单字节寻址
  {
    I2C_Send_Byte(0xA0);
    I2C_Wait_ACK();
    I2C_Send_Byte(addr>>8);//发送数据地址高位  
  }
  else
  {
    I2C_Send_Byte(0xA0+((addr/256)<<1));//器件地址+数据地址
  }
  
    I2C_Wait_ACK();
    I2C_Send_Byte(addr%256);//双字节时，发送数据地址低位；单字节时，发送数据地址低位
    I2C_Wait_ACK();
  
  I2C_Start();
  I2C_Send_Byte(0xA1+((addr/256)<<1));//进入接收模式（读命令）
  I2C_Wait_ACK();
  
  temp = I2C_Read_Byte(0);//0代表NACK
  I2C_Stop();
  
  return temp;
}

/*******************************************************************************
* 函数名：  AT24Cxx_WriteOneByte
* 功能描述: 向AT24Cxx中写一个字节
* 输入参数：无
* 输出参数：无
* 返回值：  
* 先决条件：
* 被调用函数：
* 日期:    2015-03-05
*******************************************************************************/
void AT24Cxx_WriteOneByte(uint16_t addr, uint8_t dt)
{
  I2C_Start();
  
  if(EE_TYPE > AT24C16)//如果EE_TYPE > AT24C16进入双字节寻址，否则进入单字节寻址
  {
    I2C_Send_Byte(0xA0);
    I2C_Wait_ACK();
    I2C_Send_Byte(addr>>8);//发送数据地址高位  
  }
  else
  {
    I2C_Send_Byte(0xA0+((addr/256)<<1));//器件地址+数据地址
  }
  
  I2C_Wait_ACK();
  I2C_Send_Byte(addr%256);//双字节时，发送数据地址低位；单字节时，发送数据地址低位
  I2C_Wait_ACK();
  
  I2C_Send_Byte(dt);
  I2C_Wait_ACK();
  I2C_Stop();
	rt_thread_delay(10);
  AT24Cxx_WRCheck(addr,dt);
}

/********************************************************************************
* 函数名：  AT24Cxx_WRCheck(uint16_t addr, uint8_t dt)
* 功能描述: 检测写入单个字节是否正确
* 输入参数：无
* 输出参数：无
* 返回值：  
* 先决条件：
* 被调用函数：
* 日期:    2021-08-07
*********************************************************************************/
void AT24Cxx_WRCheck(uint16_t addr, uint8_t dt)
{
  if(AT24Cxx_ReadOneByte(addr)!=dt)
    AT24Cxx_WriteOneByte(addr,dt);
  else
    return;    
}