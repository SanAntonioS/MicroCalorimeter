#ifndef __DataProcess_H__
#define __DataProcess_H__

#include "sys.h" 

typedef struct Data
{
	double R1;
	double R2;
	double R3;
	double R4;
	double Voltage;
	double V2;
	double V3;
	double V4;
	double V5;
	double V6;
	double V7;
	double V8;
	double V9;
	float averageR1;
	float averageR2;
	float averageR3;
	float averageR4;
	double averageVoltage;
	
	float Voltage_Target;
	float Power;
	float T_Target;
	float T_OpenPID_Target;
	float Kp;
	float Ki;
	float Kd;
	float Max_Power;
	
	float Baseline_Temperature;
	double Baseline_Voltage;
	
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
}Data_t;

typedef struct Flag
{
	bool Start_Control;
	bool Start_AT;
	bool Start_Baseline;
	
	bool Modbus_State;
	bool EV1_State;
	bool EV2_State;
	bool EV3_State;
	bool EV4_State;
	
	bool Save_Kp_to_EEPROM;
	bool Save_Ki_to_EEPROM;
	bool Save_Kd_to_EEPROM;
	bool Save_MaxT_to_EEPROM;
	bool Save_MinT_to_EEPROM;
	
	bool Save_Baseline_Temperature_to_EEPROM;
	bool Save_Baseline_Voltage_to_EEPROM;
}Flag_t;

void data_process_thread_entry(void *parameter);
void Cal_Resistance_1_Channel(void);
void Cal_Resistance_8_Channel(void);

#endif