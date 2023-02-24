#include "SWM181.h"

#include <math.h>


void SerialInit(void);

int main(void)
{
 	uint32_t i;
 	
 	SystemInit();
	
	SerialInit();
	
	GPIO_Init(GPIOD, PIN0, 1, 0, 0, 0);
	GPIO_Init(GPIOB, PIN8, 1, 0, 0, 0);
	GPIO_Init(GPIOB, PIN9, 1, 0, 0, 0);
	GPIO_ClrBit(GPIOD, PIN0);
	GPIO_ClrBit(GPIOB, PIN8);
	GPIO_ClrBit(GPIOB, PIN9);
    
 	while(1)
 	{
 		GPIO_InvBit(GPIOD, PIN0);
 		GPIO_InvBit(GPIOB, PIN8);
 		GPIO_InvBit(GPIOB, PIN9);
 		for(i=0; i<5000000; i++) i=i;
		
  		printf("Hi, World!\r\n");
 	}
}

void SerialInit(void)
{
	UART_InitStructure UART_initStruct;
	
	PORT_Init(PORTA, PIN0, FUNMUX_UART0_RXD, 1);	//GPIOA.0配置为UART0输入引脚
	PORT_Init(PORTA, PIN1, FUNMUX_UART0_TXD, 0);	//GPIOA.1配置为UART0输出引脚
 	
 	UART_initStruct.Baudrate = 57600;
	UART_initStruct.DataBits = UART_DATA_8BIT;
	UART_initStruct.Parity = UART_PARITY_NONE;
	UART_initStruct.StopBits = UART_STOP_1BIT;
	UART_initStruct.RXThreshold = 3;
	UART_initStruct.RXThresholdIEn = 0;
	UART_initStruct.TXThreshold = 3;
	UART_initStruct.TXThresholdIEn = 0;
	UART_initStruct.TimeoutTime = 10;
	UART_initStruct.TimeoutIEn = 0;
 	UART_Init(UART0, &UART_initStruct);
	UART_Open(UART0);
}

/****************************************************************************************************************************************** 
* 函数名称: fputc()
* 功能说明: printf()使用此函数完成实际的串口打印动作
* 输    入: int ch		要打印的字符
*			FILE *f		文件句柄
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
int fputc(int ch, FILE *f)
{
	UART_WriteByte(UART0, ch);
	
	while(UART_IsTXBusy(UART0));
 	
	return ch;
}
