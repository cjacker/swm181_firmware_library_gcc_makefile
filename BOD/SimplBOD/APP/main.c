#include "SWM181.h"


int main(void)
{	
	SystemInit();
	
	GPIO_Init(GPIOA, PIN5, 1, 0, 0, 0);			//输出，接LED
	
	SYS->BODCR |= (0x01 << SYS_BODCR_IE_Pos);
	
	IRQ_Connect(IRQ0_15_BOD, IRQ6_IRQ, 0);
	
	while(1==1)
	{
		GPIO_ClrBit(GPIOA, PIN5);
	}
}

void IRQ6_Handler(void)
{
	GPIO_SetBit(GPIOA, PIN5);
}
