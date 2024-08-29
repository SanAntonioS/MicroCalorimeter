#include "eeprom.h"

union Union_Data UnionDataERW;	//����union���͵ı���,���ڴ��ת����λ�����͵ĸ�����

rt_uint8_t byte_value = 0;
float Kp = 2.0;
float res = 0.5;

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
			
			//---------------------д��Baseline1_R1--------------------------
			if(Flag.Save_B1R1_to_EEPROM){
				UnionDataERW.Data_Float = data.Baseline1_R1;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_B1R1+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B1R1+i);
				}
				data.Baseline1_R1 = UnionDataERW.Data_Float;
				Flag.Save_B1R1_to_EEPROM = 0;
			}
			//---------------------д��Baseline1_R2--------------------------
			if(Flag.Save_B1R2_to_EEPROM){
				UnionDataERW.Data_Float = data.Baseline1_R2;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_B1R2+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B1R2+i);
				}
				data.Baseline1_R2 = UnionDataERW.Data_Float;
				Flag.Save_B1R2_to_EEPROM = 0;
			}
			//---------------------д��Baseline1_R3--------------------------
			if(Flag.Save_B1R3_to_EEPROM){
				UnionDataERW.Data_Float = data.Baseline1_R3;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_B1R3+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B1R3+i);
				}
				data.Baseline1_R3 = UnionDataERW.Data_Float;
				Flag.Save_B1R3_to_EEPROM = 0;
			}
			//---------------------д��Baseline1_R4--------------------------
			if(Flag.Save_B1R4_to_EEPROM){
				UnionDataERW.Data_Float = data.Baseline1_R4;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_B1R4+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B1R4+i);
				}
				data.Baseline1_R4 = UnionDataERW.Data_Float;
				Flag.Save_B1R4_to_EEPROM = 0;
			}
			//---------------------д��Baseline1_V--------------------------
			if(Flag.Save_B1V_to_EEPROM){
				UnionDataERW.Data_Float = data.Baseline1_V;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_B1V+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B1V+i);
				}
				data.Baseline1_V = UnionDataERW.Data_Float;
				Flag.Save_B1V_to_EEPROM = 0;
			}
			
			//---------------------д��Baseline2_R1--------------------------
			if(Flag.Save_B2R1_to_EEPROM){
				UnionDataERW.Data_Float = data.Baseline2_R1;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_B2R1+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B2R1+i);
				}
				data.Baseline2_R1 = UnionDataERW.Data_Float;
				Flag.Save_B2R1_to_EEPROM = 0;
			}
			//---------------------д��Baseline2_R2--------------------------
			if(Flag.Save_B2R2_to_EEPROM){
				UnionDataERW.Data_Float = data.Baseline2_R2;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_B2R2+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B2R2+i);
				}
				data.Baseline2_R2 = UnionDataERW.Data_Float;
				Flag.Save_B2R2_to_EEPROM = 0;
			}
			//---------------------д��Baseline2_R3--------------------------
			if(Flag.Save_B2R3_to_EEPROM){
				UnionDataERW.Data_Float = data.Baseline2_R3;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_B2R3+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B2R3+i);
				}
				data.Baseline2_R3 = UnionDataERW.Data_Float;
				Flag.Save_B2R3_to_EEPROM = 0;
			}
			//---------------------д��Baseline2_R4--------------------------
			if(Flag.Save_B2R4_to_EEPROM){
				UnionDataERW.Data_Float = data.Baseline2_R4;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_B2R4+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B2R4+i);
				}
				data.Baseline2_R4 = UnionDataERW.Data_Float;
				Flag.Save_B2R4_to_EEPROM = 0;
			}
			//---------------------д��Baseline2_V--------------------------
			if(Flag.Save_B2V_to_EEPROM){
				UnionDataERW.Data_Float = data.Baseline2_V;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_B2V+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B2V+i);
				}
				data.Baseline2_V = UnionDataERW.Data_Float;
				Flag.Save_B2V_to_EEPROM = 0;
			}
			
			//---------------------д��Baseline3_R1--------------------------
			if(Flag.Save_B3R1_to_EEPROM){
				UnionDataERW.Data_Float = data.Baseline3_R1;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_B3R1+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B3R1+i);
				}
				data.Baseline3_R1 = UnionDataERW.Data_Float;
				Flag.Save_B3R1_to_EEPROM = 0;
			}
			//---------------------д��Baseline3_R2--------------------------
			if(Flag.Save_B3R2_to_EEPROM){
				UnionDataERW.Data_Float = data.Baseline3_R2;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_B3R2+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B3R2+i);
				}
				data.Baseline3_R2 = UnionDataERW.Data_Float;
				Flag.Save_B3R2_to_EEPROM = 0;
			}
			//---------------------д��Baseline3_R3--------------------------
			if(Flag.Save_B3R3_to_EEPROM){
				UnionDataERW.Data_Float = data.Baseline3_R3;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_B3R3+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B3R3+i);
				}
				data.Baseline3_R3 = UnionDataERW.Data_Float;
				Flag.Save_B3R3_to_EEPROM = 0;
			}
			//---------------------д��Baseline3_R4--------------------------
			if(Flag.Save_B3R4_to_EEPROM){
				UnionDataERW.Data_Float = data.Baseline3_R4;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_B3R4+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B3R4+i);
				}
				data.Baseline3_R4 = UnionDataERW.Data_Float;
				Flag.Save_B3R4_to_EEPROM = 0;
			}
			//---------------------д��Baseline3_V--------------------------
			if(Flag.Save_B3V_to_EEPROM){
				UnionDataERW.Data_Float = data.Baseline3_V;
				for(int i=0;i<4;i++)
				{
					AT24Cxx_WriteOneByte((ADD_B3V+i),UnionDataERW.Data_Unchar[3-i]);
				}
				for(int i=0;i<4;i++)
				{
					UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B3V+i);
				}
				data.Baseline3_V = UnionDataERW.Data_Float;
				Flag.Save_B3V_to_EEPROM = 0;
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
	//-------------------------��ȡ�洢����1-----------------------------
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B1R1+i);
	}
	data.Baseline1_R1=UnionDataERW.Data_Float;
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B1R2+i);
	}
	data.Baseline1_R2=UnionDataERW.Data_Float;
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B1R3+i);
	}
	data.Baseline1_R3=UnionDataERW.Data_Float;
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B1R4+i);
	}
	data.Baseline1_R4=UnionDataERW.Data_Float;
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B1V+i);
	}
	data.Baseline1_V=UnionDataERW.Data_Float;
	//-------------------------��ȡ�洢����2-----------------------------
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B2R1+i);
	}
	data.Baseline2_R1=UnionDataERW.Data_Float;
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B2R2+i);
	}
	data.Baseline2_R2=UnionDataERW.Data_Float;
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B2R3+i);
	}
	data.Baseline2_R3=UnionDataERW.Data_Float;
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B2R4+i);
	}
	data.Baseline2_R4=UnionDataERW.Data_Float;
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B2V+i);
	}
	data.Baseline2_V=UnionDataERW.Data_Float;
	//-------------------------��ȡ�洢����3-----------------------------
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B3R1+i);
	}
	data.Baseline3_R1=UnionDataERW.Data_Float;
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B3R2+i);
	}
	data.Baseline3_R2=UnionDataERW.Data_Float;
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B3R3+i);
	}
	data.Baseline3_R3=UnionDataERW.Data_Float;
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B3R4+i);
	}
	data.Baseline3_R4=UnionDataERW.Data_Float;
	for(int i=0;i<4;i++)
	{
		UnionDataERW.Data_Unchar[3-i]=AT24Cxx_ReadOneByte(ADD_B3V+i);
	}
	data.Baseline3_V=UnionDataERW.Data_Float;
}

/* ���Ժ��� */
void at24c256_test(void)
{
	rt_kprintf("eeprom task\r\n");
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
	
	char buffer[32];
	sprintf(buffer, "%f\r\n", res);
	rt_kprintf("%s", buffer);
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