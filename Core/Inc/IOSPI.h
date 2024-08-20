#ifndef __IOSPI_H
#define	__IOSPI_H

#include "sys.h"

#define NO_OF_BYTES 0x03

#define IOSPI1_CS_CLEAR         HAL_GPIO_WritePin(AD1_CS_GPIO_Port, AD1_CS_Pin, GPIO_PIN_RESET) 
#define IOSPI1_CS_SET           HAL_GPIO_WritePin(AD1_CS_GPIO_Port, AD1_CS_Pin, GPIO_PIN_SET) 
#define AD1_MOSI_HIGH           HAL_GPIO_WritePin(AD1_MOSI_GPIO_Port, AD1_MOSI_Pin, GPIO_PIN_SET)
#define AD1_SCLK_HIGH           HAL_GPIO_WritePin(AD1_SCLK_GPIO_Port, AD1_SCLK_Pin, GPIO_PIN_SET)
#define AD1_MOSI_LOW            HAL_GPIO_WritePin(AD1_MOSI_GPIO_Port, AD1_MOSI_Pin, GPIO_PIN_RESET) 
#define AD1_SCLK_LOW            HAL_GPIO_WritePin(AD1_SCLK_GPIO_Port, AD1_SCLK_Pin, GPIO_PIN_RESET) 
#define AD1_MISO_IN             HAL_GPIO_ReadPin(AD1_MISO_GPIO_Port, AD1_MISO_Pin)

#define IOSPI2_CS_CLEAR         HAL_GPIO_WritePin(AD2_CS_GPIO_Port, AD2_CS_Pin, GPIO_PIN_RESET)
#define IOSPI2_CS_SET           HAL_GPIO_WritePin(AD2_CS_GPIO_Port, AD2_CS_Pin, GPIO_PIN_SET) 
#define IOSPI3_CS_CLEAR         HAL_GPIO_WritePin(AD3_CS_GPIO_Port, AD3_CS_Pin, GPIO_PIN_RESET)
#define IOSPI3_CS_SET           HAL_GPIO_WritePin(AD3_CS_GPIO_Port, AD3_CS_Pin, GPIO_PIN_SET) 
#define IOSPI4_CS_CLEAR         HAL_GPIO_WritePin(AD4_CS_GPIO_Port, AD4_CS_Pin, GPIO_PIN_RESET)
#define IOSPI4_CS_SET           HAL_GPIO_WritePin(AD4_CS_GPIO_Port, AD4_CS_Pin, GPIO_PIN_SET) 
#define IOSPI5_CS_CLEAR         HAL_GPIO_WritePin(AD5_CS_GPIO_Port, AD5_CS_Pin, GPIO_PIN_RESET)
#define IOSPI5_CS_SET           HAL_GPIO_WritePin(AD5_CS_GPIO_Port, AD5_CS_Pin, GPIO_PIN_SET) 
#define IOSPI6_CS_CLEAR         HAL_GPIO_WritePin(AD6_CS_GPIO_Port, AD6_CS_Pin, GPIO_PIN_RESET)
#define IOSPI6_CS_SET           HAL_GPIO_WritePin(AD6_CS_GPIO_Port, AD6_CS_Pin, GPIO_PIN_SET) 
#define IOSPI7_CS_CLEAR         HAL_GPIO_WritePin(AD7_CS_GPIO_Port, AD7_CS_Pin, GPIO_PIN_RESET)
#define IOSPI7_CS_SET           HAL_GPIO_WritePin(AD7_CS_GPIO_Port, AD7_CS_Pin, GPIO_PIN_SET) 
#define IOSPI8_CS_CLEAR         HAL_GPIO_WritePin(AD8_CS_GPIO_Port, AD8_CS_Pin, GPIO_PIN_RESET)
#define IOSPI8_CS_SET           HAL_GPIO_WritePin(AD8_CS_GPIO_Port, AD8_CS_Pin, GPIO_PIN_SET) 


//ÉùÃ÷º¯Êý----------------------------------------------------------------------
void AD_IOSPI_Init(unsigned char AD_ID);
void EnableIOSPI(unsigned char select_ADC);
void DisableIOSPI(unsigned char select_ADC);
unsigned char IOSPI_writeData(unsigned char select_ADC,
			      unsigned char *data,
                              unsigned char bytesNumber);
void IOSPI1_Write8Bits(unsigned char data);
void IOSPI2_Write8Bits(unsigned char data);
void IOSPI3_Write8Bits(unsigned char data);
unsigned char IOSPI1_Read8Bits(void);
unsigned char IOSPI2_Read8Bits(void);
unsigned char IOSPI3_Read8Bits(void);
unsigned char IOSPI_ReadData( unsigned char select_ADC,
                                unsigned char *data,
                                unsigned char bytesNumber );

void DAC_IOSPI_Init(void);
void DAC_InitializeDAC8562(void);
void DAC_SPIinitialize(void);
void DAC_WriteData(unsigned int commandmode, unsigned int Data);
void DAC_WriteRegister(unsigned long int WriteData);
void DAC_SpiReadWrite(unsigned char *OutBuf, unsigned char NoOfBytes);
void DAC_WriteData_2(unsigned int commandmode, unsigned int Data);
void DAC_WriteRegister_2(unsigned long int WriteData);
void DAC_SpiReadWrite_2(unsigned char *OutBuf, unsigned char NoOfBytes);

#endif




