#ifndef __InitAD7177_H
#define	__InitAD7177_H

#include "sys.h"

extern struct ad717x_device device1 ;
extern struct ad717x_device device2 ;
extern struct ad717x_device device3 ;
extern struct ad717x_device device4 ;
extern struct ad717x_device device5 ;
extern struct ad717x_device device6 ;
extern struct ad717x_device device7 ;
extern struct ad717x_device device8 ;
extern  ad717x_st_reg ad7177_2_regs[]; 

void InitAD7177(struct ad717x_device *device,uint32_t addr);

#endif
