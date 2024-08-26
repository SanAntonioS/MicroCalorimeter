#include "DataConversion.h"

unsigned long RegisterValue_AD1_Ch03 = 0;
unsigned long RegisterValue_AD1_Ch13 = 0;
unsigned long RegisterValue_AD1_Ch23 = 0;

float V_AD1_Ch03 = 0;
float V_AD1_Ch13 = 0;
float V_AD1_Ch23 = 0;
float V_AD2_Ch03 = 0;
float V_AD2_Ch13 = 0;
float V_AD2_Ch23 = 0;
float V_AD3_Ch03 = 0;
float V_AD3_Ch13 = 0;
float V_AD3_Ch23 = 0;
float V_AD4_Ch03 = 0;
float V_AD4_Ch13 = 0;
float V_AD4_Ch23 = 0;
float V_AD5_Ch03 = 0;
float V_AD5_Ch13 = 0;
float V_AD5_Ch23 = 0;
float V_AD6_Ch03 = 0;
float V_AD6_Ch13 = 0;
float V_AD6_Ch23 = 0;
float V_AD7_Ch03 = 0;
float V_AD7_Ch13 = 0;
float V_AD7_Ch23 = 0;
float V_AD8_Ch03 = 0;
float V_AD8_Ch13 = 0;
float V_AD8_Ch23 = 0;

char sendBuffer[128];
rt_uint8_t AD1_Channel_State = 0;
rt_uint8_t Relay_State = 0;
rt_uint8_t AD_State = 0;

extern rt_sem_t get_semaphore(void);
extern rt_sem_t get_data_process_sem(void);

void data_conversion_thread_entry(void *parameter)
{
	#if 1
	while (1)
	{
		rt_sem_t sem = get_semaphore();
		
		rt_err_t result = rt_sem_take(sem, RT_WAITING_FOREVER);
    if (result == RT_EOK) {	
			Get_Resistance_8_Channel();
		}
	}
	#endif
}

void Get_Resistance_8_Channel(void)
{
	//5sps->250ms 10sps->100ms
	rt_thread_delay(31);
	switch(AD1_Channel_State){
//		case 0:{
//			//读取寄存器值
//			RegisterValue_AD1_Ch03 = AD717X_ReadRegister(&device1,AD717X_DATA_REG);
//			V_AD1_Ch03 = RegValue_To_Voltage(RegisterValue_AD1_Ch03);
//			
//			//切换测量通道
//			ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
//			+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x01); 
//			AD717X_WriteRegister(&device1, AD717X_CHMAP0_REG);
//			
//			AD1_Channel_State++;
//		}break;
		case 0:{
			//读取寄存器值
			RegisterValue_AD1_Ch13 = AD717X_ReadRegister(&device1,AD717X_DATA_REG);
			V_AD1_Ch13 = RegValue_To_Voltage(RegisterValue_AD1_Ch13);
			
			ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
			+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x02); //切换测量通道
			AD717X_WriteRegister(&device1, AD717X_CHMAP0_REG);//写入配置
			
			AD1_Channel_State++;
		}break;
		case 1:{
			//读取寄存器值
			RegisterValue_AD1_Ch23 = AD717X_ReadRegister(&device1,AD717X_DATA_REG);
			V_AD1_Ch23 = RegValue_To_Voltage(RegisterValue_AD1_Ch23);
			
			//切换测量通道
			ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
			+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x01);
			AD717X_WriteRegister(&device1, AD717X_CHMAP0_REG);
			
			DisableIOSPI(1);
			AD_State = 2;
			AD1_Channel_State++;
		}break;
		case 2:{
			//读取寄存器值
			RegisterValue_AD1_Ch13 = AD717X_ReadRegister(&device2,AD717X_DATA_REG);
			V_AD2_Ch13 = RegValue_To_Voltage(RegisterValue_AD1_Ch13);
								
			ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
			+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x02); //切换测量通道
			AD717X_WriteRegister(&device2, AD717X_CHMAP0_REG);//写入配置
			
			AD1_Channel_State++;
		}break;
		case 3:{
			//读取寄存器值
			RegisterValue_AD1_Ch23 = AD717X_ReadRegister(&device2,AD717X_DATA_REG);
			V_AD2_Ch23 = RegValue_To_Voltage(RegisterValue_AD1_Ch23);
								
			//切换测量通道
			ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
			+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x01);
			AD717X_WriteRegister(&device2, AD717X_CHMAP0_REG);
			
			DisableIOSPI(2);
			AD_State = 3;
			AD1_Channel_State++;
		}break;
		case 4:{
			//读取寄存器值
			RegisterValue_AD1_Ch13 = AD717X_ReadRegister(&device3,AD717X_DATA_REG);
			V_AD3_Ch13 = RegValue_To_Voltage(RegisterValue_AD1_Ch13);
			
			
			ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
			+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x02); //切换测量通道
			AD717X_WriteRegister(&device3, AD717X_CHMAP0_REG);//写入配置
			
			AD1_Channel_State++;
		}break;
		case 5:{
			//读取寄存器值
			RegisterValue_AD1_Ch23 = AD717X_ReadRegister(&device3,AD717X_DATA_REG);
			V_AD3_Ch23 = RegValue_To_Voltage(RegisterValue_AD1_Ch23);
								
			//切换测量通道
			ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
			+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x01);
			AD717X_WriteRegister(&device3, AD717X_CHMAP0_REG);
			
			DisableIOSPI(3);
			AD_State = 4;
			AD1_Channel_State++;
		}break;
		case 6:{
			//读取寄存器值
			RegisterValue_AD1_Ch13 = AD717X_ReadRegister(&device4,AD717X_DATA_REG);
			V_AD4_Ch13 = RegValue_To_Voltage(RegisterValue_AD1_Ch13);
								
			ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
			+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x02); //切换测量通道
			AD717X_WriteRegister(&device4, AD717X_CHMAP0_REG);//写入配置
			
			AD1_Channel_State++;
		}break;
		case 7:{
			//读取寄存器值
			RegisterValue_AD1_Ch23 = AD717X_ReadRegister(&device4,AD717X_DATA_REG);
			V_AD4_Ch23 = RegValue_To_Voltage(RegisterValue_AD1_Ch23);
								
			//切换测量通道
			ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
			+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x01);
			AD717X_WriteRegister(&device4, AD717X_CHMAP0_REG);
			
			DisableIOSPI(4);
			AD_State = 5;
			AD1_Channel_State++;
		}break;
		case 8:{
			//读取寄存器值
			RegisterValue_AD1_Ch13 = AD717X_ReadRegister(&device5,AD717X_DATA_REG);
			V_AD5_Ch13 = RegValue_To_Voltage(RegisterValue_AD1_Ch13);
								
			ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
			+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x02); //切换测量通道
			AD717X_WriteRegister(&device5, AD717X_CHMAP0_REG);//写入配置
			
			AD1_Channel_State++;
		}break;
		case 9:{
			//读取寄存器值
			RegisterValue_AD1_Ch23 = AD717X_ReadRegister(&device5,AD717X_DATA_REG);
			V_AD5_Ch23 = RegValue_To_Voltage(RegisterValue_AD1_Ch23);
								
			//切换测量通道
			ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
			+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x01);
			AD717X_WriteRegister(&device5, AD717X_CHMAP0_REG);
			
			DisableIOSPI(5);
			AD_State = 6;
			AD1_Channel_State++;
		}break;
		case 10:{
			//读取寄存器值
			RegisterValue_AD1_Ch13 = AD717X_ReadRegister(&device6,AD717X_DATA_REG);
			V_AD6_Ch13 = RegValue_To_Voltage(RegisterValue_AD1_Ch13);
								
			ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
			+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x02); //切换测量通道
			AD717X_WriteRegister(&device6, AD717X_CHMAP0_REG);//写入配置
			
			AD1_Channel_State++;
		}break;
		case 11:{
			//读取寄存器值
			RegisterValue_AD1_Ch23 = AD717X_ReadRegister(&device6,AD717X_DATA_REG);
			V_AD6_Ch23 = RegValue_To_Voltage(RegisterValue_AD1_Ch23);
								
			//切换测量通道
			ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
			+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x01);
			AD717X_WriteRegister(&device6, AD717X_CHMAP0_REG);
			
			DisableIOSPI(6);
			AD_State = 7;
			AD1_Channel_State++;
		}break;

		case 12:{
			//读取寄存器值
			RegisterValue_AD1_Ch13 = AD717X_ReadRegister(&device7,AD717X_DATA_REG);
			V_AD7_Ch13 = RegValue_To_Voltage(RegisterValue_AD1_Ch13);
								
			ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
			+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x02); //切换测量通道
			AD717X_WriteRegister(&device7, AD717X_CHMAP0_REG);//写入配置
			
			AD1_Channel_State++;
		}break;
		case 13:{
			//读取寄存器值
			RegisterValue_AD1_Ch23 = AD717X_ReadRegister(&device7,AD717X_DATA_REG);
			V_AD7_Ch23 = RegValue_To_Voltage(RegisterValue_AD1_Ch23);
								
			//切换测量通道
			ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
			+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x01);
			AD717X_WriteRegister(&device7, AD717X_CHMAP0_REG);
			
			DisableIOSPI(7);
			AD_State = 8;
			AD1_Channel_State++;
		}break;

		case 14:{
			//读取寄存器值
			RegisterValue_AD1_Ch13 = AD717X_ReadRegister(&device8,AD717X_DATA_REG);
			V_AD8_Ch13 = RegValue_To_Voltage(RegisterValue_AD1_Ch13);
								
			ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
			+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x02); //切换测量通道
			AD717X_WriteRegister(&device8, AD717X_CHMAP0_REG);//写入配置
			
			AD1_Channel_State++;
		}break;
		case 15:{
			//读取寄存器值
			RegisterValue_AD1_Ch23 = AD717X_ReadRegister(&device8,AD717X_DATA_REG);
			V_AD8_Ch23 = RegValue_To_Voltage(RegisterValue_AD1_Ch23);
								
			//切换测量通道
			ad7177_2_regs[7].value = AD717X_CHMAP_REG_CH_EN + AD717X_CHMAP_REG_SETUP_SEL(0)
			+ AD717X_CHMAP_REG_AINPOS(0x03) + AD717X_CHMAP_REG_AINNEG(0x01);
			AD717X_WriteRegister(&device8, AD717X_CHMAP0_REG);
			
			//测量完一轮改变继电器
			Change_Relay_State();
			
			rt_sem_t data_process_sem = get_data_process_sem();
			rt_sem_release(data_process_sem);
			
			DisableIOSPI(8);
			AD_State = 1;
			AD1_Channel_State=0;
		}break;
		default: break;
	}
	
	ad7177_2_regs[1].value = 0x0200;
	switch(AD_State){
		case 1:	AD717X_WriteRegister(&device1, AD717X_ADCMODE_REG);break;
		case 2:	AD717X_WriteRegister(&device2, AD717X_ADCMODE_REG);break;
		case 3:	AD717X_WriteRegister(&device3, AD717X_ADCMODE_REG);break;
		case 4:	AD717X_WriteRegister(&device4, AD717X_ADCMODE_REG);break;
		case 5:	AD717X_WriteRegister(&device5, AD717X_ADCMODE_REG);break;
		case 6:	AD717X_WriteRegister(&device6, AD717X_ADCMODE_REG);break;
		case 7:	AD717X_WriteRegister(&device7, AD717X_ADCMODE_REG);break;
		case 8:	AD717X_WriteRegister(&device8, AD717X_ADCMODE_REG);break;
		default:break;
	}
}

void Change_Relay_State(void)
{
	switch(Relay_State){
		
		case 0:{
			IOUT_N;
			Choose_R1;
			Relay_State++;
		}break;
		case 1:{
			IOUT_P;
			Choose_R2;
			Relay_State++;
		}break;
		case 2:{
			IOUT_N;
			Choose_R2;
			Relay_State++;
		}break;
		case 3:{
			IOUT_P;
			Choose_R3;
			Relay_State++;
		}break;
		case 4:{
			IOUT_N;
			Choose_R3;
			Relay_State++;
		}break;
		case 5:{
			IOUT_P;
			Choose_R4;
			Relay_State++;
		}break;
		case 6:{
			IOUT_N;
			Choose_R4;
			Relay_State++;
		}break;
		case 7:{
			IOUT_P;
			Choose_R1;
			Relay_State=0;
		}break;
		default:break;
	}
}

float RegValue_To_Voltage(uint32_t RegValue)
{	
	float Volt=0;//热电偶对应电势值
  Volt=(((float)RegValue/2147483648.0-1)*2.5); //放大10倍，2.5V参考电压
  return Volt;//返回对应电势值  
}