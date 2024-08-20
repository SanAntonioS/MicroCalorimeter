#ifndef _EEPROM_H
#define _EEPROM_H

#include <rtthread.h>
#include <stdio.h>
#include "main.h"
#include "I2C.h"

#define AT24C01  127   //AT24C01有127个字节，是从0开始的
#define AT24C02  255   //AT24C02有255个字节，是从0开始的
#define AT24C04  511   //AT24C04有511个字节，是从0开始的
#define AT24C08  1023  //AT24C08有1023个字节，是从0开始的
#define AT24C16  2047  //AT24C16有2047个字节，是从0开始的
#define AT24C32  4095  //AT24C32有4095个字节，是从0开始的
#define AT24C64  8191  //AT24C64有8191个字节，是从0开始的
#define AT24C128 16383 //AT24C128有16383个字节，是从0开始的
#define AT24C256 32767 //AT24C256有32767个字节，是从0开始的

#define EE_TYPE AT24C256//若选用的芯片改变，只需修改此处

union Union_Data
{
  unsigned char Data_Unchar[4];
  float Data_Float;
  int Data_Int;
};

union Union_Data2
{
  unsigned char Data_Unchar[4];
  float Data_Float;
  int Data_Int;
};

uint8_t AT24Cxx_ReadOneByte(uint16_t addr);
uint16_t AT24Cxx_ReadTwoByte(uint16_t addr);
void AT24Cxx_WriteOneByte(uint16_t addr, uint8_t dt);
void AT24Cxx_WriteTwoByte(uint16_t addr,uint16_t dt);
void AT24Cxx_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite, uint8_t Len);
uint32_t AT24Cxx_ReadLenByte(uint16_t ReadAddr, uint8_t Len);
void AT24Cxx_Read(uint16_t ReadAddr, uint16_t *pBuffer, uint16_t NumToRead);
void AT24Cxx_Write(uint16_t WriteAddr, uint16_t *pBuffer, uint16_t NumToWrite);
void AT24Cxx_WRCheck(uint16_t addr, uint8_t dt);
void at24c256_test(void);

#endif
