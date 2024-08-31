#ifndef __MainTask_H__
#define __MainTask_H__
#include "sys.h"

typedef struct uart1
{
	uint16_t 	len;
	uint8_t		rx_data[255];
	char		tx_data[255];
	bool			rx_flag;
}uart1_t;

void main_task_thread_entry(void *parameter);
void Baseline_Controller(void);
void PID_Controller(float T_History, float T_Target, float *PWM_Duty);
void AT_Controller(float T_History, float T_Target, float *PWM_Duty);
void UpdatePWM(float *PWM_Duty);

#endif
