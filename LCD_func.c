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
