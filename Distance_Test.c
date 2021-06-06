#include "tm4c123gh6pm.h"
#include <stdio.h>
#include "stdint.h"
#include <math.h>
#include "string.h"
#define PI 3.14159265359

//============================== Functions Prototypes ==============================
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);
void LCD_STRING(char* str);
void delayMs(int n);
void delayUs(int n);
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
void LED_ON(uint32_t distance){
char distance_str[32];
if (distance >= 100)
{
	GPIO_PORTF_DATA_R |= 0x02 ;             //turn on RED LEDs (0000 0010)
	LCD_command(1);                         //clear display 
	LCD_command(0x80);                      //lcd cursor location
	delayMs(500);
	sprintf(distance_str, "The Distance is %d meter", distance);
	LCD_STRING(distance_str);

}
else
{	
	GPIO_PORTF_DATA_R |= 0x00 ;                        //turn OFF LED
	LCD_command(1);                                    //clear display 
	LCD_command(0x80);                                 //lcd cursor location 
	LCD_STRING("The Distance < 100 meter");
	sprintf(distance_str, "The Distance is %d meter", distance);
	LCD_STRING(distance_str);
}
}
