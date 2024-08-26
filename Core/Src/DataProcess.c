#include "DataProcess.h"

#define REF_R 2500.0			//参考电阻阻值，单位欧姆

Data_t data;
Flag_t Flag;

extern rt_uint8_t Relay_State;
extern float	V_AD1_Ch03, V_AD1_Ch13, V_AD1_Ch23,
							V_AD2_Ch03, V_AD2_Ch13, V_AD2_Ch23,
							V_AD3_Ch03, V_AD3_Ch13, V_AD3_Ch23,
							V_AD4_Ch03, V_AD4_Ch13, V_AD4_Ch23,
							V_AD5_Ch03, V_AD5_Ch13, V_AD5_Ch23,
							V_AD6_Ch03, V_AD6_Ch13, V_AD6_Ch23,
							V_AD7_Ch03, V_AD7_Ch13, V_AD7_Ch23,
							V_AD8_Ch03, V_AD8_Ch13, V_AD8_Ch23;
float Vsam_N, Vsam_P, Vref_N, Vref_P = 0;
float R1, R2, R3, R4 = 0;

extern rt_sem_t get_data_process_sem(void);

void data_process_thread_entry(void *parameter)
{
	while(1)
	{
		rt_sem_t data_process_sem = get_data_process_sem();
		rt_err_t result = rt_sem_take(data_process_sem, RT_WAITING_FOREVER);
		
		Cal_Resistance_8_Channel();
	}
}

void Cal_Resistance_8_Channel(void)
{
	switch(Relay_State)
	{
		case 1:{
			Vsam_P = (V_AD1_Ch13+V_AD2_Ch13+V_AD3_Ch13+V_AD4_Ch13+V_AD5_Ch13+V_AD6_Ch13+V_AD7_Ch13+V_AD8_Ch13)/8.0;
			Vref_P = (V_AD1_Ch23+V_AD2_Ch23+V_AD3_Ch23+V_AD4_Ch23+V_AD5_Ch23+V_AD6_Ch23+V_AD7_Ch23+V_AD8_Ch23)/8.0;
		}break;
		case 2:{
			Vsam_N = (V_AD1_Ch13+V_AD2_Ch13+V_AD3_Ch13+V_AD4_Ch13+V_AD5_Ch13+V_AD6_Ch13+V_AD7_Ch13+V_AD8_Ch13)/8.0;
			Vref_N = (V_AD1_Ch23+V_AD2_Ch23+V_AD3_Ch23+V_AD4_Ch23+V_AD5_Ch23+V_AD6_Ch23+V_AD7_Ch23+V_AD8_Ch23)/8.0;
			data.R1 = REF_R*(Vsam_P - Vsam_N)/(Vref_P - Vref_N);
			rt_kprintf("R1 : %d\r\n", (int)data.R1);
		}break;
		case 3:{
			Vsam_P = (V_AD1_Ch13+V_AD2_Ch13+V_AD3_Ch13+V_AD4_Ch13+V_AD5_Ch13+V_AD6_Ch13+V_AD7_Ch13+V_AD8_Ch13)/8.0;
			Vref_P = (V_AD1_Ch23+V_AD2_Ch23+V_AD3_Ch23+V_AD4_Ch23+V_AD5_Ch23+V_AD6_Ch23+V_AD7_Ch23+V_AD8_Ch23)/8.0;
		}break;
		case 4:{
			Vsam_N = (V_AD1_Ch13+V_AD2_Ch13+V_AD3_Ch13+V_AD4_Ch13+V_AD5_Ch13+V_AD6_Ch13+V_AD7_Ch13+V_AD8_Ch13)/8.0;
			Vref_N = (V_AD1_Ch23+V_AD2_Ch23+V_AD3_Ch23+V_AD4_Ch23+V_AD5_Ch23+V_AD6_Ch23+V_AD7_Ch23+V_AD8_Ch23)/8.0;
			data.R2 = REF_R*(Vsam_P - Vsam_N)/(Vref_P - Vref_N);
			rt_kprintf("R2 : %d\r\n", (int)data.R2);
		}break;
		case 5:{
			Vsam_P = (V_AD1_Ch13+V_AD2_Ch13+V_AD3_Ch13+V_AD4_Ch13+V_AD5_Ch13+V_AD6_Ch13+V_AD7_Ch13+V_AD8_Ch13)/8.0;
			Vref_P = (V_AD1_Ch23+V_AD2_Ch23+V_AD3_Ch23+V_AD4_Ch23+V_AD5_Ch23+V_AD6_Ch23+V_AD7_Ch23+V_AD8_Ch23)/8.0;
		}break;
		case 6:{
			Vsam_N = (V_AD1_Ch13+V_AD2_Ch13+V_AD3_Ch13+V_AD4_Ch13+V_AD5_Ch13+V_AD6_Ch13+V_AD7_Ch13+V_AD8_Ch13)/8.0;
			Vref_N = (V_AD1_Ch23+V_AD2_Ch23+V_AD3_Ch23+V_AD4_Ch23+V_AD5_Ch23+V_AD6_Ch23+V_AD7_Ch23+V_AD8_Ch23)/8.0;
			data.R3 = REF_R*(Vsam_P - Vsam_N)/(Vref_P - Vref_N);
			rt_kprintf("R3 : %d\r\n", (int)data.R3);
		}break;
		case 7:{
			Vsam_P = (V_AD1_Ch13+V_AD2_Ch13+V_AD3_Ch13+V_AD4_Ch13+V_AD5_Ch13+V_AD6_Ch13+V_AD7_Ch13+V_AD8_Ch13)/8.0;
			Vref_P = (V_AD1_Ch23+V_AD2_Ch23+V_AD3_Ch23+V_AD4_Ch23+V_AD5_Ch23+V_AD6_Ch23+V_AD7_Ch23+V_AD8_Ch23)/8.0;
		}break;
		case 0:{
			Vsam_N = (V_AD1_Ch13+V_AD2_Ch13+V_AD3_Ch13+V_AD4_Ch13+V_AD5_Ch13+V_AD6_Ch13+V_AD7_Ch13+V_AD8_Ch13)/8.0;
			Vref_N = (V_AD1_Ch23+V_AD2_Ch23+V_AD3_Ch23+V_AD4_Ch23+V_AD5_Ch23+V_AD6_Ch23+V_AD7_Ch23+V_AD8_Ch23)/8.0;
			data.R4 = REF_R*(Vsam_P - Vsam_N)/(Vref_P - Vref_N);
			rt_kprintf("R4 : %d\r\n", (int)data.R4);
		}break;
		default:break;
	}
}