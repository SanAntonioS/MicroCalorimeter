#include "eeprom.h"

union Union_Data UnionDataERW;	//����union���͵ı���,���ڴ��ת����λ�����͵ĸ�����
union Union_Data_Double UnionDataERW_Double;	//����union���͵ı���,���ڴ��ת����λ�����͵ĸ�����

extern Flag_t Flag;
extern Data_t data;
extern rt_sem_t get_eeprom_sem(void);

void eeprom_thread_entry(void *parameter)
{
	//�ϵ�һ�ζ�ȡ���д洢��EEPROM������
	EEPROM_Data_Init();
	
	while(1)
	{
		
		rt_sem_t eeprom_sem = get_eeprom_sem();
		rt_err_t result = rt_sem_take(eeprom_sem, RT_WAITING_FOREVER);
		
		if(result == RT_EOK){
			//---------------------д��Kp--------------------------
			if(Flag.Save_Kp_to_EEPROM){
				UnionDataERW.Data_Float = data.Kp;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_KP+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_KP+i);
				}
				data.Kp = UnionDataERW.Data_Float;
				Flag.Save_Kp_to_EEPROM = 0;
			}
			//---------------------д��Ki--------------------------
			if(Flag.Save_Ki_to_EEPROM){
				UnionDataERW.Data_Float = data.Ki;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_KI+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_KI+i);
				}
				data.Ki = UnionDataERW.Data_Float;
				Flag.Save_Ki_to_EEPROM = 0;
			}
			//---------------------д��Kd--------------------------
			if(Flag.Save_Kd_to_EEPROM){
				UnionDataERW.Data_Float = data.Kd;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_KD+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_KD+i);
				}
				data.Kd = UnionDataERW.Data_Float;
				Flag.Save_Kd_to_EEPROM = 0;
			}
			//---------------------д��Max_Temperature--------------------------
			if(Flag.Save_MaxT_to_EEPROM){
				UnionDataERW.Data_Float = data.Max_Temperature;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_MAXT+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_MAXT+i);
				}
				data.Max_Temperature = UnionDataERW.Data_Float;
				Flag.Save_MaxT_to_EEPROM = 0;
			}
			//---------------------д��Min_Temperature--------------------------
			if(Flag.Save_MinT_to_EEPROM){
				UnionDataERW.Data_Float = data.Min_Temperature;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_MINT+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_MINT+i);
				}
				data.Min_Temperature = UnionDataERW.Data_Float;
				Flag.Save_MinT_to_EEPROM = 0;
			}
			
			//---------------------д��Baseline_Temperature--------------------------
			if(Flag.Save_Baseline_Temperature_to_EEPROM){
				UnionDataERW.Data_Float = data.Baseline_Temperature;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_BaseT+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_BaseT+i);
				}
				data.Baseline_Temperature = UnionDataERW.Data_Float;
				Flag.Save_Baseline_Temperature_to_EEPROM = 0;
			}
			//---------------------д��Baseline_Voltage--------------------------
			if(Flag.Save_Baseline_Voltage_to_EEPROM){
				UnionDataERW_Double.Data_Double = data.Baseline_Voltage;
				for(int i=0;i<8;i++)
				{
					AT24Cxx_WriteOneByte((ADD_BaseV+i),UnionDataERW_Double.Data_Unchar[7-i]);
				}
				for(int i=0;i<8;i++)
				{
					UnionDataERW_Double.Data_Unchar[7-i]=AT24Cxx_ReadOneByte(ADD_BaseV+i);
				}
				data.Baseline_Voltage = UnionDataERW_Double.Data_Double;
				Flag.Save_Baseline_Voltage_to_EEPROM = 0;
			}
		}
	}
}

void EEPROM_Data_Init(void)
{
	//-------------------------��ȡ�洢��PIDֵ-----------------------------
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_KP+i);
	}
	data.Kp=UnionDataERW.Data_Float;
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_KI+i);
	}
	data.Ki=UnionDataERW.Data_Float;
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_KD+i);
	}
	data.Kd=UnionDataERW.Data_Float;
	//-------------------------��ȡ�洢�����Сֵ-----------------------------
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_MAXT+i);
	}
	data.Max_Temperature=UnionDataERW.Data_Float;
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_MINT+i);
	}
	data.Min_Temperature=UnionDataERW.Data_Float;
	//---------------------------��ȡ�洢����-----------------------------
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_BaseT+i);
	}
	data.Baseline_Temperature=UnionDataERW.Data_Float;
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_BaseV+i);
	}
	data.Baseline_Voltage=UnionDataERW.Data_Float;
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