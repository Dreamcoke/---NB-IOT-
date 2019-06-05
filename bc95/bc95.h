#ifndef __bc95_H
#define __bc95_H

#include "stm32f10x.h"

/*-------------------------- º¯ Êý Éù Ã÷	--------------------------*/

u8 bc95_send_data(u16 ID);
u8 bc95_init(void);
//u8 cdp_init(void);
void bc95_receive(void);
char* char2ascii(char* s,char* out);
#endif
