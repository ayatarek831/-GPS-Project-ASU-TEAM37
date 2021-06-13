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
PORTF_init();
LCD_init();
LED_ON(10); 
		
//============================== Parsing ==============================
while(1){
for(i=0;i<150;i++)
{
	Buffer[i] = UART1_Read();
}
temp = strstr(Buffer,"$GPGGA");         // find GGA data inside GPS data block
if(*temp=='$')                         // start of a line
{                 
	i=0;
	k=0;
	while(temp[j]!='\x0a')       // end of a line
	{     
		if(temp[j]!=',')
		{
			data[i][k] = temp[j];
			k++;
		}
		else
		{
			data[i][k] = '\0';
			i++;
			k=0;
		}
		j++;
	}
	j=0;
}

Latitude[0]=atof(data[2]);
Longitude[0]=atof(data[4]);

distance = distance_calc(30.244776028800565, 31.461346753073578,30.244975300103558, 31.463567622130945);
LED_ON(distance);
}		
		

    }  





