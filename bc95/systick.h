#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

/*--------------------�� �� �� ��-----------------------*/

void systick_init_config(void);          // ϵͳ�δ�ʱ�ӳ�ʼ��
void SysTickDelayTime_Counter(void);     // ��ȡ����

void delay_us(u32 us);                   // ΢����ʱ
void delay_ms(u16 ms);                   // ������ʱ
void delay_s(u32 s);                     // ����ʱ

#endif 


