#ifndef __CPUUSAGE_H__
#define __CPUUSAGE_H__
 
#include <rtthread.h>
#include <rthw.h>
 
#define CPU_UPDATE 1
 
void cpu_usage_get(rt_uint8_t *major, rt_uint8_t *minor);
void cpu_usage_init(void);
void cpu_usage_thread_entry(void *parameter);
 
#endif /*__ADC_H__ */

