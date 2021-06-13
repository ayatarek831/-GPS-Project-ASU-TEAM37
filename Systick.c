#include "tm4c123gh6pm.h"

void SysTick_init(void)                     							//intialization of SysTick Timer
{
	NVIC_ST_CTRL_R = NVIC_ST_CTRL_R & ~(0x00000001); 					  //disable Timer
	NVIC_ST_RELOAD_R = 16000000 - 1; 		                        //to make 1 sec   //16000000
	NVIC_ST_CURRENT_R = 0; 			                     					  //to clear counter value and underflow flag of counter
	NVIC_ST_CTRL_R |= 0x5; 				 													
}

void l0_ms(void)
{
	NVIC_ST_CTRL_R = NVIC_ST_CTRL_R & ~(0x00000001);           
	NVIC_ST_RELOAD_R = (1600000 - 1); 		          				   //1600000
	NVIC_ST_CURRENT_R = 0; 				
	NVIC_ST_CTRL_R |= 0x5; 
}
void fractions_delay(int frac)
{
	int i;
	for (i = 0; i < frac; i++)
	{
		l0_ms();
		while ((NVIC_ST_CTRL_R & 0x00010000) == 0) {}
	}
	return;
}

void delay(int s, int d) 
{
		SysTick_init();
		if (s == 1) 
		{
			while ((NVIC_ST_CTRL_R & 0x00010000) == 0) {}
			fractions_delay(d);
			return;
		}
		else if (s == 0)
		{
			fractions_delay(d);
			return;
		}
		else 
		{
			while ((NVIC_ST_CTRL_R & 0x00010000) == 0) {}
			delay(s-1, d);
		}
}

