#include "tm4c123gh6pm.h"
#include "TM4C123.h"
/*Team 37 Contributers
        Name                        |   ID
====================================|========
Mahmoud Sayed Mahmoud Helmy         | 1804992
Mahmoud Mohamed Mohsen Abdelaziz    | 1807302
Mahmoud Yasser Mohamed Sayed        | 1802179
Aya Mohamed Abdelhalim              | 1804570
Aya tallah Tarek                     | 1809845
Aya Mohamed Elhusseny              | 1804970

*/
//============================== VARIABLES ==============================
char data[26][12];                        
char* temp;
char Buffer[500];
double lat,lon;
int dd_lat,dd_longi;
double cLat,cLon,pLat = 0,pLon = 0,mm_lat, Latitude, mm_longi, Longitude;
double difLat,difLon;
int i;
double totaldistance = 0.0;
double distance =0.0;
int i=0,j=0,k=0;
//============================== MAIN FUNCTION ==============================

int main(void)
{
	SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2) );
//============================== Intialization ==============================
SysTick_init();
PORTF_init();
UART1_Init();
LCD_init();
//============================== Parsing ==============================
/*NOTE:
- The GPS module returns data in the form of NMEA responses
- For example, we used the GGA response
- $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47*/
//======================================================================
	
while(totaldistance<=100){
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

//===================== Conversions ================ 
Latitude = convert_Lat(lat); 												//Convert it to Degree Decimal
Longitude = convert_Lon(lon);
//=================================================

if (pLat == 0 && pLon == 0) 
{
pLat = Latitude;
pLon = Longitude;
}
cLat = Latitude;
cLon = Longitude;
distance =  distance_calc(cLat,cLon,pLat,pLon);
// Error Handling - 
if (distance <= 15) 
{            
totaldistance += distance;
}
pLat = cLat;
pLon = cLon;
LED_ON(totaldistance);
}
}
