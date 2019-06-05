#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

/*--------------------函 数 声 明-----------------------*/

void systick_init_config(void);          // 系统滴答时钟初始化
void SysTickDelayTime_Counter(void);     // 获取节拍

void delay_us(u32 us);                   // 微秒延时
void delay_ms(u16 ms);                   // 毫秒延时
void delay_s(u32 s);                     // 秒延时

#endif 


