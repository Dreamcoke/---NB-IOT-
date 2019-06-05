/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "mcu_config.h"




/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

extern u8   buf_address;                                            // �����׵�ַ��ʼֵΪ0
extern char bc95_buf[BUF_MAX];                                      // ����2���ջ���


 
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
extern void SysTickDelayTime_Counter(void);
void SysTick_Handler(void)
{
	SysTickDelayTime_Counter();
}


/*************************************************************************
* ��������: TIM2_IRQHandler
* ��    ��: ��ʱ��2�ж϶Ϸ�����
* ��    ��: ��
* ��    ��: ��
* ��    ��: �� 
* ˵    ��: ��
*************************************************************************/
void TIM2_IRQHandler(void) 
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)   // ���TIM2�����жϷ������
	{	
		 TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIM2�����жϱ�־

	}	
}


/*************************************************************************
* ��������:  USART2_IRQHandler 
* ��    ��:  ����2�жϷ�����
* �������:  ��
* ��    ��:  ��
* ��    ��:  ��
* ˵    ��:  ��
*************************************************************************/
void USART1_IRQHandler(void)                	
{
			u8 res=0;
			res =USART_ReceiveData(USART1);
			bc95_buf[buf_address] = res;        // �����յ����ַ����浽������
	    
			buf_address++;                      // ����ָ������ƶ�
			if(buf_address > BUF_MAX)       		// ���������,������ָ��ָ�򻺴���׵�ַ
			{
				buf_address = 0;
			}      
} 