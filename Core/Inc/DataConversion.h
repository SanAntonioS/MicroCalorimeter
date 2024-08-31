#ifndef __DataConversion_H__
#define __DataConversion_H__

#include "sys.h" 

void data_conversion_thread_entry(void *parameter);
void DataConversion_Task(void);
void Get_R1(void);
void Get_R2(void);
void Get_R3(void);
void Get_R4(void);
void Get_Voltage(void);
void Change_Relay_State(void);
double RegValue_To_Voltage(uint32_t RegValue);
void Get_Resistance_1_Channel(void);
void Get_Resistance_8_Channel(void);

#endif
