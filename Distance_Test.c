#include "tm4c123gh6pm.h"
#include <stdio.h>
#include "stdint.h"
#include <math.h>
#include "string.h"
#define PI 3.14159265359

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
