#include "IOSPI.h"

unsigned char OutputBuf1[10]={0x00,0x00,0x00};
unsigned char OutputBuf2[10]={0x00,0x00,0x00};

/*******************************************************************************
* �� �� ����AD_IOSPI_Init
* ����ԭ�Σ�void AD_IOSPI_Init(void)
* ��������: AD IO��ģ��SPI����ʼ������ 
* ���������unsigned char AD_ID
* �����������
* �� �� ֵ����
* �Ⱦ�������
* �����ú�����
* ��    �ߣ�������
* ��    ��: 2016-02-25
*******************************************************************************/
void AD_IOSPI_Init(unsigned char AD_ID)
{
  
  switch(AD_ID)
  {
  case 1:
    {
      EnableIOSPI(1); //ʹ�� IOSPI_CS
    }
    break;
  case 2:
    {      
      EnableIOSPI(2); //ʹ�� IOSPI_CS
    }
    break; 
	case 3:
    {      
      EnableIOSPI(3); //ʹ�� IOSPI_CS
    }
    break; 
	case 4:
    {      
      EnableIOSPI(4); //ʹ�� IOSPI_CS
    }
    break; 
	case 5:
    {      
      EnableIOSPI(5); //ʹ�� IOSPI_CS
    }
    break; 
	case 6:
    {      
      EnableIOSPI(6); //ʹ�� IOSPI_CS
    }
    break; 
	case 7:
    {      
      EnableIOSPI(7); //ʹ�� IOSPI_CS
    }
    break; 
	case 8:
    {      
      EnableIOSPI(8); //ʹ�� IOSPI_CS
    }
    break; 
  default:break;
  }
}
/*******************************************************************************
* �� �� ����EnableIOSPI
* ����ԭ�Σ�void EnableIOSPI(unsigned char select_ADC)
* ��������: ģ��IOSPI��Ƭѡʹ��
* ���������ƬѡоƬ���  unsigned char select_ADC
* �����������
* �� �� ֵ����
* �Ⱦ�������
* �����ú�����
* ��    �ߣ�������
* ��    ��: 2016-02-25
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
* �� �� ����DisableIOSPI
* ����ԭ�Σ�void DisableIOSPI(unsigned char select_ADC)
* ��������: ģ��IOSPI��Ƭѡ����
* ���������ƬѡоƬ���  unsigned char select_ADC
* �����������
* �� �� ֵ����
* �Ⱦ�������
* �����ú�����
* ��    �ߣ�������
* ��    ��: 2016-02-25
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
* ��������IOSPI_writeData
* ����ԭ�Σ�void IOSPI_writeData()
* ��������: ����SPI���ͻ����������ݡ�
* ���������SPI1=1��SPI2=2,SPI3=3,��ѡ��select_ADC)
* �����������
* ����ֵ��  ��
* �Ⱦ�������
* �����ú�����
* ����:    2015-02-05
*******************************************************************************/
unsigned char IOSPI_writeData(unsigned char select_ADC,
			      unsigned char *data,
                              unsigned char bytesNumber)
{
  unsigned char writeData[8] ={0,0,0,0,0,0,0,0};
  unsigned char byte = 0;
  for(byte = 0;byte< bytesNumber;byte++)
  {
    writeData[byte] = data[byte] ;     //��Ҫ���͵����ݷ���writeData��
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
* �� �� ����IOSPI1_Write8Bits
* ����ԭ�Σ�void IOSPI1_Write8Bits(unsigned char data)
* ��������: IOSPI1 д 8 Bits ����
* �����������д������ data
* �����������
* �� �� ֵ����
* �Ⱦ�������
* �����ú�����
* ��    �ߣ�������
* ��    ��: 2016-12-27
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
    if( writeData & 0x80)//�Ӹ�λ��ʼȡֵ
    {
      AD1_MOSI_HIGH;
    }
    else
    {
      AD1_MOSI_LOW;
    }
    AD1_SCLK_LOW;
    rt_hw_us_delay(1);//ʱ����Լ�С
    AD1_SCLK_HIGH;
    rt_hw_us_delay(1);
    writeData <<=1;
  }   
}

/*******************************************************************************
* �� �� ����IOSPI1_Read8Bits
* ����ԭ�Σ�unsigned char IOSPI1_Read8Bits(void)
* ��������: IOSPI1 �� 8BITS ����
* �����������
* �����������ȡ�� 1 �ֽ����ݣ�Readdata 
* �� �� ֵ����
* �Ⱦ�������
* �����ú�����
* ��    �ߣ�������
* ��    ��: 2016-12-27
*******************************************************************************/
unsigned char IOSPI1_Read8Bits(void)
{
  unsigned char Readdata=0x00;
  unsigned char bit=0;
  for(bit = 0;bit< 8;bit++) 
  {
    AD1_SCLK_HIGH;//�ȸߵ�ƽ�ٵ͵�ƽ
    rt_hw_us_delay(1);
    AD1_SCLK_LOW; 
    rt_hw_us_delay(1);
    Readdata <<= 1;
    Readdata  |= AD1_MISO_IN ;  
  }
  AD1_SCLK_HIGH;//��ȡ������ɺ�SCLK�øߵ�ƽ
  rt_hw_us_delay(1);     
  return Readdata;      
}

/*******************************************************************************
* ��������IOSPI_ReadData
* ����ԭ�Σ�void IOSPI_ReadData()
* ��������: ����IOSPI���ܻ����������ݡ�
* ���������select_ADC��data��bytesNumber
* �����������
* ����ֵ��bytesNumber
* �Ⱦ�������
* �����ú�����
* ����:    2017-02-25
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
	rt_hw_us_delay(1);//��Ӧ�ֲ� t1 ����С��Ϊ 0  ���޸�by �����룬2017-2-27
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
