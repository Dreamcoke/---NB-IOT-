/***************************************************************************
 * 文件名称 ：bc95.c
 * 描    述 ：BC95测试函数库，包含COAP通信的部分AT命令        
 * 实验平台 ：STM32F103vet6开发板
 * 硬件连接 ：无
 * 库版本   ：STM32F10x_StdPeriph_Lib_V3.5.0
*****************************************************************************/
#include "bc95.h"
#include "mcu_config.h"
#include "systick.h"
#include "string.h"
#include "delay.h"


/*-------------------------- 变 量 声 明 ---------------------------------------*/

extern u8   buf_address;                                            // 缓存首地址初始值为0
extern char bc95_buf[BUF_MAX];                                      // 串口2接收缓存

/*-------------------------- 常 量 声 明 ---------------------------------------*/
char *bc95_data="AT+NMGS=4,31323200";                            // 上传的数据，可根据在电信IOT平台定义的数据格式上传数据

/******************************************************************************
* 函数名称: bc95_init
* 描    述: BC95配置初始化
* 输入参数: 无
* 输    出: 无
* 返    回: 0 --- 出错  1 --- 正确
* 说    明: 
*******************************************************************************/
u8 bc95_init(void)
{
  //printf("**************** BC95配置初始化 ****************\r\n");
	
	// BC95复位
	bc95_send_cmd("AT+NRB","OK",1,4000);
   
	// 发送AT确保AT命令有效
	if(bc95_send_cmd("AT","OK",2,500)) 
	{
			
	}
	else
	{
	   GPIO_SetBits(GPIOB,GPIO_Pin_5);
		 return 0;
	}
	
	// 选择频段5
	if(bc95_send_cmd("AT+NBAND=5","OK",1,1000))
	{
     printf("2.配置为频段号5\r\n");
	}
	else
	{
	   printf("配置频段号失败\r\n");
		 return 0;
	}
	
  // 查询频段号            
	if(bc95_send_cmd("AT+NBAND?","+NBAND:5",2,500))
	{
     printf("3.获取频段号：5\r\n");
	}
	else
	{
	   printf("获取频段号有误\r\n");
		 return 0;
	}
	
	// 获取卡号，类似于读卡操作            
	if(bc95_send_cmd("AT+CIMI","46011",4,2000))
	{
     printf("4.获取卡号成功\r\n");
	}
	else
	{
	   printf("获取卡号失败\r\n");
		 return 0;
	}
  
	// 开启射频             
	if(bc95_send_cmd("AT+CFUN=1","OK",2,3000))
	{
     printf("5.开启射频成功\r\n");
	}
	else
	{
	   printf("开启射频失败\r\n");
		 return 0;
	}
  
	// 配置电信平台的CDP服务器地址，这个COAP协议的IP地址是固定的
	if(bc95_send_cmd("AT+NCDP=117.60.157.137,5683","OK",1,500))
	{
     printf("6.配置电信平台的CDP服务器地址\r\n");
	}
	else
	{
	   printf("配置CDP服务器地址失败\r\n");
		 return 0;
	}
	// 激活网络	
	if(bc95_send_cmd("AT+CGATT=1","OK",1,500)) 
	{
     printf("7.成功激活网路\r\n");
	}
	else
	{
	   printf("激活网络失败\r\n");
		 return 0;
	}

	
	
	
	// 查询信号值	
	if(bc95_send_cmd("AT+CSQ","OK",2,1000)) 
	{
     printf("8.信号值为：\r\n%s\r\n",bc95_buf);
	}
	else
	{
	   printf("信号获取失败\r\n");
		 return 0;
	}
	
	// 查询网络是否注册
	if(bc95_send_cmd("AT+CEREG?","+CEREG:0,1",5,1000)) 
	{
     printf("7.网络注册成功\r\n");
	}
	else
	{
	   printf("网络注册失败\r\n");
		 return 0;
	}
		
	/*查询注册模式
	if(bc95_send_cmd("AT+NMGS=3,313232","OK",5,1000)) 
	{
     printf("9.绑定成功\r\n");
	}
	else
	{
	   printf("绑定失败\r\n");
		 return 0;
	}
	*/

	// 开始注册到IOT平台
	//if(bc95_send_cmd("AT+QLWSREGIND=0","+QLWEVTIND:3",1,2000)) 
	//{
  //   printf("10.成功注册到IOT平台，可以发送数据\r\n");
	//}
	//else
	//{
	//   printf("注册失败\r\n");
	//	 return 0;
	//}
	return 1;
}


/******************************************************************************
* 函数名称: bc95_send_data
* 描    述: bc95发送数据到电信IOT平台
* 输入参数: 无
* 输    出: 无
* 返    回: 0 --- 出错  1 --- 正确
* 说    明:         
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
	   printf("数据发送成功\r\n");
	}
	else
	{
	   printf("数据发送失败\r\n");
		 return 0;
	}
  clear_bc95_buf();
	return 1;
}

/******************************************************************************
* 函数名称: bc95_receive 
* 描    述: bc95接收电信IOT平台的数据
* 输入参数: 无
* 输    出: 无
* 返    回: 0 --- 出错  1 --- 正确
* 说    明: 
*******************************************************************************/
void bc95_receive(void)
{
	if(find_string("+NNMI:"))
	{
		delay_ms(60);
		printf("接收到平台下发的数据：%s\r\n",bc95_buf);
		if(find_string("2,0100"))
		{
			printf("点亮LED灯\r\n");
		   LED_ON;
		}
		else if(find_string("2,0101"))
		{
			printf("熄灭LED灯\r\n");
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
