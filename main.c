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
//====================pasrsin initialization=================
char data[26][12];
char* temp;
char Buffer[500];
double Latitude[50],Longitude[50];
double lat,lon;
double lat2,lon2;
int deg_lat;
double min_lat;
int deg_lon;
double min_lon;
int deg_lat2;
double min_lat2;
int deg_lon2;
double min_lon2;
//============================== VARIABLES ==============================
int i;
double totaldistance = 0.0;
double distance =0.0;
int i=0,j=0,k=0;

//============================== Distance calc ==============================
double distance_calc(double previousLat,double previousLong,double latitude,double longitude)
{
	
// to calculate the distance between 2 logitudes , 2 latitudes 
		double pi = 3.141592653589793;
    double fLong = (longitude - previousLong) * (pi/180);// d2r is a constant to convert to radian defined in the header
    double fLat = (latitude - previousLat) * (pi/180);
    double a = pow(sin(fLat/2.0), 2) + cos(previousLat*(pi/180)) * cos(latitude*(pi/180)) * pow(sin(fLong/2.0), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = 6371 * c;		// R is the radius of the Earth Defined in the header file  
    return d * 1000;
}

//============================== MAIN FUNCTION ==============================
	int main(void)
	{
		SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2) );
PORTF_init();
LCD_init();
UART1_Init();		
LED_ON(10); 
Latitude[0] =0.0;
Longitude[0]=0.0;		
//============================== Parsing ==============================
delayMs(600000);

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

lat=atof(data[2]);
lon=atof(data[4]);

deg_lat = Deg(lat);
min_lat = Min(lat);
deg_lon = Deg(lon);
min_lon = Min(lon);
	
Latitude[0] = deg_DD(deg_lat , min_lat);
Longitude[0] = deg_DD(deg_lon , min_lon);		
//======================================//		
while(totaldistance <= 100){

delayMs(1000);	
	
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

lat2=atof(data[2]);
lon2=atof(data[4]);

deg_lat2 = Deg(lat);
min_lat2 = Min(lat);
deg_lon2 = Deg(lon);
min_lon2 = Min(lon);


Latitude[1] = deg_DD(deg_lat2 , min_lat2);
Longitude[1] = deg_DD(deg_lon2 , min_lon2);

distance = distance_calc(Latitude[0], Longitude[0],Latitude[1],Longitude[1]);
	totaldistance+=distance;

Latitude[0] = Latitude[1];
Longitude[0] = Longitude[1];

}

LED_ON(totaldistance);
}
 





