#ifndef __CRC16_H__
#define __CRC16_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

uint16_t calculate_crc16_modbus(uint8_t* data, size_t len);


#endif
