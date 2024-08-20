#ifndef  __SYS_H__
#define  __SYS_H__

#define	HIGH_VERSION

#include "rtthread.h"
#include "gpio.h"
#include "math.h"
#include "stdbool.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "I2C.h"
#include "cpu_usage.h"
#include "eeprom.h"
#include "AD717x.h"
#include "InitAD7177.h"
#include "IOSPI.h"
#include "DataConversion.h"

void rt_hw_us_delay(rt_uint32_t us);


#endif
