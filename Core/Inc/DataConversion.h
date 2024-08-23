#ifndef __DataConversion_H__
#define __DataConversion_H__

#include "sys.h" 

void data_conversion_thread_entry(void *parameter);
void Change_Relay_State(void);
float RegValue_To_Voltage(uint32_t RegValue);

#endif
