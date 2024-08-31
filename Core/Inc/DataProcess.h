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
	
	float Baseline1_R1;
	float Baseline1_R2;
	float Baseline1_R3;
	float Baseline1_R4;
	float Baseline1_V;
	float Baseline1_T;
	
	float Baseline2_R1;
	float Baseline2_R2;
	float Baseline2_R3;
	float Baseline2_R4;
	float Baseline2_V;
	float Baseline2_T;
	
	float Baseline3_R1;
	float Baseline3_R2;
	float Baseline3_R3;
	float Baseline3_R4;
	float Baseline3_V;
	float Baseline3_T;
	
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
	
	bool Save_B1R1_to_EEPROM;
	bool Save_B1R2_to_EEPROM;
	bool Save_B1R3_to_EEPROM;
	bool Save_B1R4_to_EEPROM;
	bool Save_B1V_to_EEPROM;
	
	bool Save_B2R1_to_EEPROM;
	bool Save_B2R2_to_EEPROM;
	bool Save_B2R3_to_EEPROM;
	bool Save_B2R4_to_EEPROM;
	bool Save_B2V_to_EEPROM;
	
	bool Save_B3R1_to_EEPROM;
	bool Save_B3R2_to_EEPROM;
	bool Save_B3R3_to_EEPROM;
	bool Save_B3R4_to_EEPROM;
	bool Save_B3V_to_EEPROM;
}Flag_t;

void data_process_thread_entry(void *parameter);
void Cal_Resistance_1_Channel(void);
void Cal_Resistance_8_Channel(void);

#endif