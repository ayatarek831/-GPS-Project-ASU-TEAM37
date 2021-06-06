#include "tm4c123gh6pm.h"
#include <stdio.h>
#include "stdint.h"
#include <math.h>
#include "string.h"
#define PI 3.14159265359
#define RS 0x20																																		 //PORTA BIT5 mask 
#define RW 0x40 																																	 //PORTA BIT6 mask 
#define EN 0x80																																		 //PORTA BIT7 mask
void delayMs(int n);
void delayUs(int n);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);

//============================== LCD Intialization PORTA & PORTB ==============================
void LCD_init(void)
{
SYSCTL_RCGCGPIO_R |= 0x03; 																											  //PORTA & PORTB enable clock 
GPIO_PORTA_DIR_R |= 0xE0; 																											  //PORTA controls RS,E and R/W  (PA5,PA6,PA7 = 1)
GPIO_PORTA_DEN_R |= 0xE0; 																												//Enable digital function at PORTA (PA5,PA6,PA7 = 1)
GPIO_PORTA_AFSEL_R &= ~ 0XFF; 																									  //Disable Analog mode on PORTA
GPIO_PORTA_AMSEL_R &= ~ 0XFF;  					                                          //Disable Analog mode on PORTA
GPIO_PORTB_DIR_R |= 0xFF; 					                                              //PORTB as output  PB0-PB7
GPIO_PORTB_DEN_R = 0xFF; 								                                          //Enable digital function at PORTB PB0-PB7
delayMs(20);                                                                      //initialization sequence
LCD_command(0x30);                                                                //Wakeup
LCD_command(0x38); 											                                          //8-bits,2 display lines, 5x7 font
LCD_command(0x06); 											                                          //move cursor right
LCD_command(0x01); 											                                          //clear screen, move cursor to home
LCD_command(0x0F);                                                                //turn on display, cursor blinking
} 

void LCD_command(unsigned char command)
{
GPIO_PORTA_DATA_R = 0; 																								 						//RS =0, E=0, RW=0
GPIO_PORTB_DATA_R = command;
GPIO_PORTA_DATA_R = EN; 																													//pulse E
delayUs(0);
GPIO_PORTA_DATA_R = 0;
if (command < 4) 																																	//command 1 and 2 needs up to 1.64ms
	delayMs(2);
else
	delayUs(40); 																																		//all others 40 us
} 

void LCD_data(unsigned char data)
{
GPIO_PORTA_DATA_R = RS;                                                          //RS=1, E=0,RW=0 (A5 = 1)  NOTE:[RS =1 for data & Rs = 0 for Command]
GPIO_PORTB_DATA_R = data;
GPIO_PORTA_DATA_R = EN | RS; 																										 //pulse E
delayUs(0);
GPIO_PORTA_DATA_R = 0;
delayUs(40);
}

//============================== Display Array of Char ==============================
void LCD_STRING(char* str)
{
uint32_t size;
uint8_t up;
uint32_t y;
size = strlen(str);
up = 1;
for (y = 0; y < size; y++)
{
	delayMs(2);
	LCD_data(str[y]);

	if (((y + 1) % 16 == 0) && (up))
	{
		LCD_command(0xC0);
		up = 0;
	}
	else if (((y + 1) % 16 == 0) && (!up))
	{
		LCD_command(0x80);
		up = 1;
	}
}

}
//============================== delay n milliseconds (16 MHz CPU clock) ==============================
void delayMs(int n)
{
int i, j;
for(i = 0 ; i< n; i++) 
for(j = 0; j <3180; j++)
{} //do nothing for 1 ms
}

//============================== delay n microseconds (16 MHz CPU clock)==============================
void delayUs(int n)
{
int i, j; 
for(i = 0 ;i < n; i++) 
for(j = 0; j < 3; j++)
{} //do nothing for 1 us
}
