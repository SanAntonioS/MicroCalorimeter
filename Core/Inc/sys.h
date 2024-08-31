#ifndef  __SYS_H__
#define  __SYS_H__

#define	HIGH_VERSION

#include "rtthread.h"
#include "gpio.h"
#include "math.h"
#include "usart.h"
#include "stdbool.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "I2C.h"
#include "cpu_usage.h"
#include "eeprom.h"
#include "AD717x.h"
#include "InitAD7177.h"
#include "IOSPI.h"
#include "DataConversion.h"
#include "DataProcess.h"
#include "CRC16.h"
#include "ModbusRtu.h"
#include "MainTask.h"

//电流正向，继电器向上打
#define	IOUT_P	HAL_GPIO_WritePin(Relay6_L_GPIO_Port, Relay6_L_Pin, GPIO_PIN_SET);\
								HAL_GPIO_WritePin(Relay6_R_GPIO_Port, Relay6_R_Pin, GPIO_PIN_RESET)
								
//电流反向，继电器向下打
#define	IOUT_N	HAL_GPIO_WritePin(Relay6_L_GPIO_Port, Relay6_L_Pin, GPIO_PIN_RESET);\
								HAL_GPIO_WritePin(Relay6_R_GPIO_Port, Relay6_R_Pin, GPIO_PIN_SET)
								
#define	Choose_R1	HAL_GPIO_WritePin(Relay1_L_GPIO_Port, Relay1_L_Pin, GPIO_PIN_SET);\
									HAL_GPIO_WritePin(Relay1_R_GPIO_Port, Relay1_R_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay3_L_GPIO_Port, Relay3_L_Pin, GPIO_PIN_SET);\
									HAL_GPIO_WritePin(Relay3_R_GPIO_Port, Relay3_R_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay7_L_GPIO_Port, Relay7_L_Pin, GPIO_PIN_SET);\
									HAL_GPIO_WritePin(Relay7_R_GPIO_Port, Relay7_R_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay5_L_GPIO_Port, Relay5_L_Pin, GPIO_PIN_SET);\
									HAL_GPIO_WritePin(Relay5_R_GPIO_Port, Relay5_R_Pin, GPIO_PIN_RESET)
									
#define	Choose_R2	HAL_GPIO_WritePin(Relay1_L_GPIO_Port, Relay1_L_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay1_R_GPIO_Port, Relay1_R_Pin, GPIO_PIN_SET);\
									HAL_GPIO_WritePin(Relay3_L_GPIO_Port, Relay3_L_Pin, GPIO_PIN_SET);\
									HAL_GPIO_WritePin(Relay3_R_GPIO_Port, Relay3_R_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay7_L_GPIO_Port, Relay7_L_Pin, GPIO_PIN_SET);\
									HAL_GPIO_WritePin(Relay7_R_GPIO_Port, Relay7_R_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay5_L_GPIO_Port, Relay5_L_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay5_R_GPIO_Port, Relay5_R_Pin, GPIO_PIN_SET)
								
#define	Choose_R3	HAL_GPIO_WritePin(Relay4_L_GPIO_Port, Relay4_L_Pin, GPIO_PIN_SET);\
									HAL_GPIO_WritePin(Relay4_R_GPIO_Port, Relay4_R_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay3_L_GPIO_Port, Relay3_L_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay3_R_GPIO_Port, Relay3_R_Pin, GPIO_PIN_SET);\
									HAL_GPIO_WritePin(Relay7_L_GPIO_Port, Relay7_L_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay7_R_GPIO_Port, Relay7_R_Pin, GPIO_PIN_SET);\
									HAL_GPIO_WritePin(Relay8_L_GPIO_Port, Relay8_L_Pin, GPIO_PIN_SET);\
									HAL_GPIO_WritePin(Relay8_R_GPIO_Port, Relay8_R_Pin, GPIO_PIN_RESET)

#define	Choose_R4	HAL_GPIO_WritePin(Relay4_L_GPIO_Port, Relay4_L_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay4_R_GPIO_Port, Relay4_R_Pin, GPIO_PIN_SET);\
									HAL_GPIO_WritePin(Relay3_L_GPIO_Port, Relay3_L_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay3_R_GPIO_Port, Relay3_R_Pin, GPIO_PIN_SET);\
									HAL_GPIO_WritePin(Relay7_L_GPIO_Port, Relay7_L_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay7_R_GPIO_Port, Relay7_R_Pin, GPIO_PIN_SET);\
									HAL_GPIO_WritePin(Relay8_L_GPIO_Port, Relay8_L_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay8_R_GPIO_Port, Relay8_R_Pin, GPIO_PIN_SET)
									
#define Choose_V	HAL_GPIO_WritePin(Relay1_L_GPIO_Port, Relay1_L_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay1_R_GPIO_Port, Relay1_R_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay2_L_GPIO_Port, Relay2_L_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay2_R_GPIO_Port, Relay2_R_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay3_L_GPIO_Port, Relay3_L_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay3_R_GPIO_Port, Relay3_R_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay4_L_GPIO_Port, Relay4_L_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay4_R_GPIO_Port, Relay4_R_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay5_L_GPIO_Port, Relay5_L_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay5_R_GPIO_Port, Relay5_R_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay6_L_GPIO_Port, Relay6_L_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay6_R_GPIO_Port, Relay6_R_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay7_L_GPIO_Port, Relay7_L_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay7_R_GPIO_Port, Relay7_R_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay8_L_GPIO_Port, Relay8_L_Pin, GPIO_PIN_RESET);\
									HAL_GPIO_WritePin(Relay8_R_GPIO_Port, Relay8_R_Pin, GPIO_PIN_RESET)


void rt_hw_us_delay(rt_uint32_t us);


#endif
