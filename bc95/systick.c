/*************************************************************************
 * 文件名称 ：systick.c
 * 描    述 ：通过系统滴答时钟SysTick中断实现ms(毫秒)、s(秒)的延时
 * 实验平台 ：STM32F103VET6开发板
 * 硬件连接 ：无                  
 * 库版本   ：STM32F10x_StdPeriph_Lib_V3.5.0 
**************************************************************************/

#include "systick.h"
#include "delay.h"

static u32 SysTickDelayTime;

/****************************************************************************
* 函数名称: systick_init_config
* 描    述: 初始化系统滴答时钟SysTick
* 输入参数: 无
* 输    出: 无
* 返    回: 无
* 说    明: 1)、SystemFrequency / 1000		  1ms中断一次
*			      2)、SystemFrequency / 100000	10us中断一次
*			      3)、SystemFrequency / 1000000	1us中断一次
* 计算方法: (SystemFrequency / Value)个系统时钟节拍中断一次
****************************************************************************/
void systick_init_config(void)
{
	while(SysTick_Config(SystemCoreClock / 1000));	// 初始化并使能系统滴答时钟,返回1表示计数设置太大			 
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;		  // 失能滴答定时器 
	
}

/****************************************************************************
* 函数名称: delay_us
* 描    述: 微秒延时
* 输入参数: us
* 输    出: 无
* 返    回: 无
* 说    明: 无
****************************************************************************/
/*
void delay_us(u32 us)
{ 
	SysTickDelayTime = us*1000000;		 
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;   	// 使能滴答定时器 
	while(SysTickDelayTime != 0);					        // 等待延时时间到
}
*/
/****************************************************************************
* 函数名称: delay_ms
* 描    述: 毫秒延时
* 输入参数: ms
* 输    出: 无
* 返    回: 无
* 说    明: 单位（ms）
****************************************************************************/
/*
void delay_ms(u16 ms)
{ 
	SysTickDelayTime = ms;		 
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;	  // 使能滴答定时器 
	while(SysTickDelayTime != 0);					      // 等待延时时间到
}
*/
/****************************************************************************
* 函数名称: delay_s
* 描    述: 秒延时
* 输入参数: s
* 输    出: 无
* 返    回: 无
* 说    明: 单位（1s）
****************************************************************************/
void delay_s(u32 s)
{ 
	SysTickDelayTime = s*1000;		 
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;	 // 使能滴答定时器 
	while(SysTickDelayTime != 0);					     // 等待延时时间到
}

/****************************************************************************
* 函数名称: SysTickDelayTime_Counter
* 描    述: 获取节拍函数
* 输入参数: 无
* 输    出: 无
* 返    回: 无
* 说    明: 在SysTick中断程序SysTick_Handler()调用(stm32f10x_it.c)
****************************************************************************/
void SysTickDelayTime_Counter(void)
{
	if (SysTickDelayTime > 0)
	{ 
		SysTickDelayTime--;
	}
}
