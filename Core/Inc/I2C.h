
#ifndef _I2C_H
#define _I2C_H

#include "main.h"
#include <rtthread.h>

#define I2C_SCL GPIO_PIN_6
#define I2C_SDA GPIO_PIN_7
#define GPIO_I2C GPIOB
   
#define I2C_SCL_H HAL_GPIO_WritePin(GPIO_I2C, I2C_SCL, GPIO_PIN_SET);
#define I2C_SCL_L HAL_GPIO_WritePin(GPIO_I2C, I2C_SCL, GPIO_PIN_RESET);

#define I2C_SDA_H HAL_GPIO_WritePin(GPIO_I2C, I2C_SDA, GPIO_PIN_SET);
#define I2C_SDA_L HAL_GPIO_WritePin(GPIO_I2C, I2C_SDA, GPIO_PIN_RESET);


void I2C_Config(void);
void I2C_SDA_OUT(void);
void I2C_SDA_IN(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_ACK(void);
void I2C_NACK(void);
uint8_t   I2C_Wait_ACK(void);
void I2C_Send_Byte(uint8_t txd);
uint8_t   I2C_Read_Byte(uint8_t ack);
   
#endif

