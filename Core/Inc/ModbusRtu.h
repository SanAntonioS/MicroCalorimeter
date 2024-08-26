#ifndef __ModbusRtu_H__
#define __ModbusRtu_H__
#include "sys.h"

#pragma pack(1)
typedef union
{
	float f;
	char c[4];
}FLOAT_CONV;

typedef union
{
	double d;
	char c[8];
}DOUBLE_CONV;

typedef union
{
	uint16_t d;
	char c[2];
}UINT16_CONV;

typedef struct uart3
{
	uint16_t 	len;
	uint8_t		rx_data[255];
	uint8_t		tx_data[255];
	bool			rx_flag;
}uart3_t;


typedef struct Register
{
	float Pv;	
	float Kp;
	float Ki;
	float Sv;
	float Resistance;
	float OUT;
	double NTC_A;
	double NTC_B;
	double NTC_C;
	double NTC_D;
	double NTC_E;
	double NTC_F;
	float Pv_OpenLoop;
	uint16_t EV1;
	uint16_t EV2;
	uint16_t EV3;
	uint16_t EV4;
	uint16_t Modbus_Switch;
	float Kd;
	float Pv2;
	float Resistance2;
	double NTC_A2;
	double NTC_B2;
	double NTC_C2;
	double NTC_D2;
	double NTC_E2;
	double NTC_F2;
	uint16_t AT;
	float Max_Temperature;
	float Min_Temperature;
}Register_t;
#pragma pack()

void data_send_thread_entry(void *parameter);
void ModbusRtuTask(void);
float LtoB_Float(float data);
double LtoB_Double(double data);
uint16_t LtoB_Uint16(uint16_t data);

#endif
