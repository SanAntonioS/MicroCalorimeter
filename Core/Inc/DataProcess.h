#ifndef __DataProcess_H__
#define __DataProcess_H__

#include "sys.h" 

typedef struct Data
{
	float R1;
	float R2;
	float R3;
	float R4;
	float Voltage;
	uint8_t sensor;
	float T_PT100;
	float T_PT100_Fliter;
	float R_PT100;
	float T2_PT100;
	float T2_PT100_Fliter;
	float R2_PT100;
	float Power;
	float T_Target;
	float T_OpenPID_Target;
	float Kp;
	float Ki;
	float Kd;
	float Max_Power;
	
	double NTC_A;
	double NTC_B;
	double NTC_C;
	double NTC_D;
	double NTC_E;
	double NTC_F;
	double NTC_A2;
	double NTC_B2;
	double NTC_C2;
	double NTC_D2;
	double NTC_E2;
	double NTC_F2;
	
	float Max_Temperature;
	float Min_Temperature;
	
	float Debug_Output;
}Data_t;

typedef struct Flag
{
	bool Timer_1Hz;
	bool Send_Timer_1S;
	bool Send_Timer_8S;
	
	bool Start_Control;
	bool Start_AT;
	bool COM;
	//声明全局变量，作为数据寄存器 读取完成标志，即置位时方可进行数据转换--------
	bool AD1_Ch01_Pt100_P_Get;
	bool AD1_Ch01_REF_P_Get;
	bool AD1_Ch01_REF_N_Get;
	bool AD1_Ch01_Pt100_N_Get;
	bool AD1_Ch12_Pt100_P_Get;
	bool AD1_Ch12_REF_P_Get;
	bool AD1_Ch12_REF_N_Get;
	bool AD1_Ch12_Pt100_N_Get;
	
	bool AD2_Ch01_REF_P_Get;
	bool AD2_Ch01_Pt100_P_Get;
	bool AD2_Ch01_Pt100_N_Get;
	bool AD2_Ch01_REF_N_Get;
	bool AD2_Ch12_REF_P_Get;
	bool AD2_Ch12_Pt100_P_Get;
	bool AD2_Ch12_Pt100_N_Get;
	bool AD2_Ch12_REF_N_Get;
	
	bool ADC1_PT100_T_ConverEnd;
	bool ADC2_PT100_T_ConverEnd;
	bool ADC1_PT100_T2_ConverEnd;
	bool ADC2_PT100_T2_ConverEnd;
	
	bool Refrigerator_State;
	bool RecirculatingBath_State;
	bool BigHeater_State;
	bool SmallHeater_State;
	bool Modbus_State;
	bool EV1_State;
	bool EV2_State;
	bool EV3_State;
	bool EV4_State;
	
	bool Save_PID_to_EEPROM;
	bool Save_NTC_to_EEPROM;
	
	float Flash_EEPROM;
	int Save_PID_To;
	
	int Relay_State;
	
	bool Debug_Output_State;
	bool Debug_Temperature_Transmit;
	bool Debug_Resistance_Transmit;
	
	bool T_Target_Update;
}Flag_t;

void data_process_thread_entry(void *parameter);
void Cal_Resistance_8_Channel(void);

#endif