#include "tm4c123gh6pm.h"
#include "TM4C123.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define RS 0x20 											     //PORTA BIT5 mask
#define RW 0x40 									         //PORTA BIT6 mask 
#define EN 0x80 									         //PORTA BIT7 mask

/*Team 37 Contributers
        Name                        |   ID
====================================|========
Mahmoud Sayed Mahmoud Helmy         | 1804992
Mahmoud Mohamed Mohsen Abdelaziz    | 1807302
Mahmoud Yasser Mohamed Sayed        | 1802179
Aya Mohamed Abdelhalem              | 1804570
Aya allah Tarek                     | 1809845
Aya Mohamed Elhussieny              | 1804970

*/


//============================== Function Prototypes ==============================
char UART_Read(void);
void UART2_Init(void);
int distance(int degree_lat1, double min_lat1, int degree_lon1, double min_lon1, int degree_lat2, double min_lat2, int degree_lon2, double min_lon2);
char IntToChar(int,int);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);
void LCD_STRING(char* str);
void delayMs(int n);
void delayUs(int n);

void PORTF_init(void);
void LED_ON(uint32_t distance);
//============================== MAIN FUNCTION ==============================
int main(void)
{
SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2) );
PORTF_init();
LCD_init();
LED_ON(10); 

    }  





