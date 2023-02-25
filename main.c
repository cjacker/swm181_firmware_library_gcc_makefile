#include "SWM181.h"

#include <math.h>


void SerialInit(void);

int main(void)
{
 	uint32_t i;
 	
 	SystemInit();
	
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
 	}
}
