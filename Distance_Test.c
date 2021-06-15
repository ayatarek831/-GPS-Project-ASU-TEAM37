#include "tm4c123gh6pm.h"

//============================== Intialize PORTF ==============================
void PORTF_init(void){                                                 
SYSCTL_RCGCGPIO_R |= 0x20;			       //enable clock of Port F
while((SYSCTL_PRGPIO_R & 0x20)==0); 	 //delay
GPIO_PORTF_AMSEL_R &= 0x00;            //disable analog
GPIO_PORTF_AFSEL_R &= 0x00;            //disable alternate function
GPIO_PORTF_LOCK_R = 0x4C4F434B;				 //unlock GPIO Port F
GPIO_PORTF_CR_R = 0x0E; 							 //enable changes to PF1-PF3 (0000 1110)
GPIO_PORTF_DEN_R |= 0x0E;              //enable PF1,PF2,PF3 (0000 1110)
GPIO_PORTF_DIR_R |= 0x0E;              //enable PF1-PF3 as output (0000 1110)
GPIO_PORTF_PCTL_R &= 0x00000000;       //PCTL GPIO
}
void LED(int color){
	GPIO_PORTF_DATA_R &= (~0x0E);
	GPIO_PORTF_DATA_R |= color;
}
void LED_ON(double distance){
char distance_str[32];
if (distance >= 100)
{
	LED(7);
	LCD_command(1);                         //clear display 
	LCD_command(0x80);                      //lcd cursor location
	delayMs(500);
	sprintf(distance_str, "distance =      %f", distance);
	LCD_STRING(distance_str);
}
else
{
	LED(2);
	LCD_command(1);                                    //clear display 
	LCD_command(0x80);                                 //lcd cursor location 
	sprintf(distance_str, "distance =      %f", distance);
	LCD_STRING(distance_str);
}
}
