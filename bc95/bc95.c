/***************************************************************************
 * �ļ����� ��bc95.c
 * ��    �� ��BC95���Ժ����⣬����COAPͨ�ŵĲ���AT����        
 * ʵ��ƽ̨ ��STM32F103vet6������
 * Ӳ������ ����
 * ��汾   ��STM32F10x_StdPeriph_Lib_V3.5.0
*****************************************************************************/
#include "bc95.h"
#include "mcu_config.h"
#include "systick.h"
#include "string.h"
#include "delay.h"


/*-------------------------- �� �� �� �� ---------------------------------------*/

extern u8   buf_address;                                            // �����׵�ַ��ʼֵΪ0
extern char bc95_buf[BUF_MAX];                                      // ����2���ջ���

/*-------------------------- �� �� �� �� ---------------------------------------*/
char *bc95_data="AT+NMGS=4,31323200";                            // �ϴ������ݣ��ɸ����ڵ���IOTƽ̨��������ݸ�ʽ�ϴ�����

/******************************************************************************
* ��������: bc95_init
* ��    ��: BC95���ó�ʼ��
* �������: ��
* ��    ��: ��
* ��    ��: 0 --- ����  1 --- ��ȷ
* ˵    ��: 
*******************************************************************************/
u8 bc95_init(void)
{
  //printf("**************** BC95���ó�ʼ�� ****************\r\n");
	
	// BC95��λ
	bc95_send_cmd("AT+NRB","OK",1,4000);
   
	// ����ATȷ��AT������Ч
	if(bc95_send_cmd("AT","OK",2,500)) 
	{
			
	}
	else
	{
	   GPIO_SetBits(GPIOB,GPIO_Pin_5);
		 return 0;
	}
	
	// ѡ��Ƶ��5
	if(bc95_send_cmd("AT+NBAND=5","OK",1,1000))
	{
     printf("2.����ΪƵ�κ�5\r\n");
	}
	else
	{
	   printf("����Ƶ�κ�ʧ��\r\n");
		 return 0;
	}
	
  // ��ѯƵ�κ�            
	if(bc95_send_cmd("AT+NBAND?","+NBAND:5",2,500))
	{
     printf("3.��ȡƵ�κţ�5\r\n");
	}
	else
	{
	   printf("��ȡƵ�κ�����\r\n");
		 return 0;
	}
	
	// ��ȡ���ţ������ڶ�������            
	if(bc95_send_cmd("AT+CIMI","46011",4,2000))
	{
     printf("4.��ȡ���ųɹ�\r\n");
	}
	else
	{
	   printf("��ȡ����ʧ��\r\n");
		 return 0;
	}
  
	// ������Ƶ             
	if(bc95_send_cmd("AT+CFUN=1","OK",2,3000))
	{
     printf("5.������Ƶ�ɹ�\r\n");
	}
	else
	{
	   printf("������Ƶʧ��\r\n");
		 return 0;
	}
  
	// ���õ���ƽ̨��CDP��������ַ�����COAPЭ���IP��ַ�ǹ̶���
	if(bc95_send_cmd("AT+NCDP=117.60.157.137,5683","OK",1,500))
	{
     printf("6.���õ���ƽ̨��CDP��������ַ\r\n");
	}
	else
	{
	   printf("����CDP��������ַʧ��\r\n");
		 return 0;
	}
	// ��������	
	if(bc95_send_cmd("AT+CGATT=1","OK",1,500)) 
	{
     printf("7.�ɹ�������·\r\n");
	}
	else
	{
	   printf("��������ʧ��\r\n");
		 return 0;
	}

	
	
	
	// ��ѯ�ź�ֵ	
	if(bc95_send_cmd("AT+CSQ","OK",2,1000)) 
	{
     printf("8.�ź�ֵΪ��\r\n%s\r\n",bc95_buf);
	}
	else
	{
	   printf("�źŻ�ȡʧ��\r\n");
		 return 0;
	}
	
	// ��ѯ�����Ƿ�ע��
	if(bc95_send_cmd("AT+CEREG?","+CEREG:0,1",5,1000)) 
	{
     printf("7.����ע��ɹ�\r\n");
	}
	else
	{
	   printf("����ע��ʧ��\r\n");
		 return 0;
	}
		
	/*��ѯע��ģʽ
	if(bc95_send_cmd("AT+NMGS=3,313232","OK",5,1000)) 
	{
     printf("9.�󶨳ɹ�\r\n");
	}
	else
	{
	   printf("��ʧ��\r\n");
		 return 0;
	}
	*/

	// ��ʼע�ᵽIOTƽ̨
	//if(bc95_send_cmd("AT+QLWSREGIND=0","+QLWEVTIND:3",1,2000)) 
	//{
  //   printf("10.�ɹ�ע�ᵽIOTƽ̨�����Է�������\r\n");
	//}
	//else
	//{
	//   printf("ע��ʧ��\r\n");
	//	 return 0;
	//}
	return 1;
}


/******************************************************************************
* ��������: bc95_send_data
* ��    ��: bc95�������ݵ�����IOTƽ̨
* �������: ��
* ��    ��: ��
* ��    ��: 0 --- ����  1 --- ��ȷ
* ˵    ��:         
*******************************************************************************/
u8 bc95_send_data(u16 ID)
{ 
	char data[0x78];
	char buf[256];
	char string_data[256];
	sprintf(string_data,"%d",ID);
	sprintf(data,"AT+NMGS=%d,%s",strlen(string_data),char2ascii(string_data,buf));
	
	if(bc95_send_cmd((char *)data,"OK",1,3000))
	{
	   printf("���ݷ��ͳɹ�\r\n");
	}
	else
	{
	   printf("���ݷ���ʧ��\r\n");
		 return 0;
	}
  clear_bc95_buf();
	return 1;
}

/******************************************************************************
* ��������: bc95_receive 
* ��    ��: bc95���յ���IOTƽ̨������
* �������: ��
* ��    ��: ��
* ��    ��: 0 --- ����  1 --- ��ȷ
* ˵    ��: 
*******************************************************************************/
void bc95_receive(void)
{
	if(find_string("+NNMI:"))
	{
		delay_ms(60);
		printf("���յ�ƽ̨�·������ݣ�%s\r\n",bc95_buf);
		if(find_string("2,0100"))
		{
			printf("����LED��\r\n");
		   LED_ON;
		}
		else if(find_string("2,0101"))
		{
			printf("Ϩ��LED��\r\n");
		   LED_OFF;
		}
    clear_bc95_buf();		
	}	
}

char* char2ascii(char* s,char* out){
	int i = 0, n;
    char *p;
    p = out;
    for (i = 0; i < strlen(s); i++)
    {
        n = sprintf(p, "%x", s[i]);
        p += n;
    }
    return out;
}
