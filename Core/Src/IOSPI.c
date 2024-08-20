#include "IOSPI.h"

unsigned char OutputBuf1[10]={0x00,0x00,0x00};
unsigned char OutputBuf2[10]={0x00,0x00,0x00};

/*******************************************************************************
* 函 数 名：AD_IOSPI_Init
* 函数原形：void AD_IOSPI_Init(void)
* 功能描述: AD IO口模拟SPI，初始化设置 
* 输入参数：unsigned char AD_ID
* 输出参数：无
* 返 回 值：无
* 先决条件：
* 被调用函数：
* 作    者：钟银彪
* 日    期: 2016-02-25
*******************************************************************************/
void AD_IOSPI_Init(unsigned char AD_ID)
{
  
  switch(AD_ID)
  {
  case 1:
    {
      EnableIOSPI(1); //使能 IOSPI_CS
    }
    break;
  case 2:
    {      
      EnableIOSPI(2); //使能 IOSPI_CS
    }
    break; 
	case 3:
    {      
      EnableIOSPI(3); //使能 IOSPI_CS
    }
    break; 
	case 4:
    {      
      EnableIOSPI(4); //使能 IOSPI_CS
    }
    break; 
	case 5:
    {      
      EnableIOSPI(5); //使能 IOSPI_CS
    }
    break; 
	case 6:
    {      
      EnableIOSPI(6); //使能 IOSPI_CS
    }
    break; 
	case 7:
    {      
      EnableIOSPI(7); //使能 IOSPI_CS
    }
    break; 
	case 8:
    {      
      EnableIOSPI(8); //使能 IOSPI_CS
    }
    break; 
  default:break;
  }
}
/*******************************************************************************
* 函 数 名：EnableIOSPI
* 函数原形：void EnableIOSPI(unsigned char select_ADC)
* 功能描述: 模拟IOSPI，片选使能
* 输入参数：片选芯片编号  unsigned char select_ADC
* 输出参数：无
* 返 回 值：无
* 先决条件：
* 被调用函数：
* 作    者：钟银彪
* 日    期: 2016-02-25
*******************************************************************************/
void EnableIOSPI(unsigned char select_ADC)
{
  switch(select_ADC)
  {
  case 1:       IOSPI1_CS_CLEAR; break;
  case 2:       IOSPI2_CS_CLEAR; break;
	case 3:       IOSPI3_CS_CLEAR; break;
	case 4:       IOSPI4_CS_CLEAR; break;
	case 5:       IOSPI5_CS_CLEAR; break;
	case 6:       IOSPI6_CS_CLEAR; break;
	case 7:       IOSPI7_CS_CLEAR; break;
	case 8:       IOSPI8_CS_CLEAR; break;
  default : break;
  }
}

/*******************************************************************************
* 函 数 名：DisableIOSPI
* 函数原形：void DisableIOSPI(unsigned char select_ADC)
* 功能描述: 模拟IOSPI，片选禁用
* 输入参数：片选芯片编号  unsigned char select_ADC
* 输出参数：无
* 返 回 值：无
* 先决条件：
* 被调用函数：
* 作    者：钟银彪
* 日    期: 2016-02-25
*******************************************************************************/
void DisableIOSPI(unsigned char select_ADC)
{
  switch(select_ADC)
  {
  case 1:       IOSPI1_CS_SET; break;
  case 2:       IOSPI2_CS_SET; break;
	case 3:       IOSPI3_CS_SET; break;
	case 4:       IOSPI4_CS_SET; break;
	case 5:       IOSPI5_CS_SET; break;
	case 6:       IOSPI6_CS_SET; break;
	case 7:       IOSPI7_CS_SET; break;
	case 8:       IOSPI8_CS_SET; break;
  default : break;
  }
}

/*******************************************************************************
* 函数名：IOSPI_writeData
* 函数原形：void IOSPI_writeData()
* 功能描述: 发送SPI发送缓冲区的数据。
* 输入参数：SPI1=1，SPI2=2,SPI3=3,的选择（select_ADC)
* 输出参数：无
* 返回值：  无
* 先决条件：
* 被调用函数：
* 日期:    2015-02-05
*******************************************************************************/
unsigned char IOSPI_writeData(unsigned char select_ADC,
			      unsigned char *data,
                              unsigned char bytesNumber)
{
  unsigned char writeData[8] ={0,0,0,0,0,0,0,0};
  unsigned char byte = 0;
  for(byte = 0;byte< bytesNumber;byte++)
  {
    writeData[byte] = data[byte] ;     //把要发送的数据放入writeData中
  }
  
  for(byte = 0;byte < bytesNumber;byte ++)
  {
    switch(select_ADC)
    {
			case 1:      EnableIOSPI(1);      break;
			case 2:      EnableIOSPI(2);      break;
			case 3:      EnableIOSPI(3);      break;
			case 4:      EnableIOSPI(4);      break;
			case 5:      EnableIOSPI(5);      break;
			case 6:      EnableIOSPI(6);      break;
			case 7:      EnableIOSPI(7);      break;
			case 8:      EnableIOSPI(8);      break;
      
    default : break;
    
    }	
		IOSPI1_Write8Bits(writeData[byte]);
  }
  rt_hw_us_delay(1);					
  return(bytesNumber);
}

/*******************************************************************************
* 函 数 名：IOSPI1_Write8Bits
* 函数原形：void IOSPI1_Write8Bits(unsigned char data)
* 功能描述: IOSPI1 写 8 Bits 数据
* 输入参数：待写入数据 data
* 输出参数：无
* 返 回 值：无
* 先决条件：
* 被调用函数：
* 作    者：钟银彪
* 日    期: 2016-12-27
*******************************************************************************/
void IOSPI1_Write8Bits(unsigned char data)
{
  unsigned int writeData =0;
  unsigned char bit = 0;
  writeData = data;   
  AD1_SCLK_HIGH;
  rt_hw_us_delay(1);
  for(bit = 0;bit< 8;bit++) 
  {
    if( writeData & 0x80)//从高位开始取值
    {
      AD1_MOSI_HIGH;
    }
    else
    {
      AD1_MOSI_LOW;
    }
    AD1_SCLK_LOW;
    rt_hw_us_delay(1);//时间可以减小
    AD1_SCLK_HIGH;
    rt_hw_us_delay(1);
    writeData <<=1;
  }   
}

/*******************************************************************************
* 函 数 名：IOSPI1_Read8Bits
* 函数原形：unsigned char IOSPI1_Read8Bits(void)
* 功能描述: IOSPI1 读 8BITS 数据
* 输入参数：无
* 输出参数：读取的 1 字节数据：Readdata 
* 返 回 值：无
* 先决条件：
* 被调用函数：
* 作    者：钟银彪
* 日    期: 2016-12-27
*******************************************************************************/
unsigned char IOSPI1_Read8Bits(void)
{
  unsigned char Readdata=0x00;
  unsigned char bit=0;
  for(bit = 0;bit< 8;bit++) 
  {
    AD1_SCLK_HIGH;//先高电平再低电平
    rt_hw_us_delay(1);
    AD1_SCLK_LOW; 
    rt_hw_us_delay(1);
    Readdata <<= 1;
    Readdata  |= AD1_MISO_IN ;  
  }
  AD1_SCLK_HIGH;//读取数据完成后，SCLK置高电平
  rt_hw_us_delay(1);     
  return Readdata;      
}

/*******************************************************************************
* 函数名：IOSPI_ReadData
* 函数原形：void IOSPI_ReadData()
* 功能描述: 接收IOSPI接受缓冲区的数据。
* 输入参数：select_ADC，data，bytesNumber
* 输出参数：无
* 返回值：bytesNumber
* 先决条件：
* 被调用函数：
* 日期:    2017-02-25
*******************************************************************************/
unsigned char IOSPI_ReadData( unsigned char select_ADC,
                             unsigned char *data,
                             unsigned char bytesNumber )
{
  unsigned char writeData[6] = {0, 0, 0, 0, 0, 0};
  unsigned char readData[6] = {0, 0, 0, 0, 0, 0};
  unsigned char byte = 0;
  
  for(byte = 0;byte < bytesNumber;byte ++)
  {
    writeData[byte] = data[byte];
    data[byte] = 0;
  }
  
  switch(select_ADC)
  {
		case 1:	    EnableIOSPI(1);    break;
		case 2:	    EnableIOSPI(2);    break;
		case 3:	    EnableIOSPI(3);    break;
		case 4:	    EnableIOSPI(4);    break;
		case 5:	    EnableIOSPI(5);    break;
		case 6:	    EnableIOSPI(6);    break;
		case 7:	    EnableIOSPI(7);    break;
		case 8:	    EnableIOSPI(8);    break;
    
  default : break;
  }
	rt_hw_us_delay(1);//对应手册 t1 ，最小可为 0  ，修改by 钟银彪，2017-2-27
	IOSPI1_Write8Bits(writeData[0]);
	rt_hw_us_delay(1);
	for(byte = 1;byte < bytesNumber;byte ++)
	{
	readData[byte] = IOSPI1_Read8Bits();
	}	
	rt_hw_us_delay(1);
  for(byte =0;byte < bytesNumber;byte ++)
  {
    data[byte] = readData[byte];
  } 
  return(bytesNumber);
}
