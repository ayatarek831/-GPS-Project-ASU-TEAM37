#include "tm4c123gh6pm.h"
#include "tm4c123.h"

long double torad(long double degree) {
    long double rad = degree / (180 / (22 / 7));
    return rad;
}
//============================== Distance Calculation ==============================
double distance_calc(double previousLat,double previousLong,double clatitude,double clongitude)
{
	
// to calculate the distance between 2 logitudes , 2 latitudes 
long double lat1 = torad(previousLat);
long double long1 = torad(previousLong);
long double lat2 = torad(clatitude);
long double long2 = torad(clongitude);

// calculating haversine formula
long double latdiff = lat2 - lat1;
long double longdiff = long2 - long1;
double dis_part1 = (pow(sin(latdiff / 2), 2)) + (pow(sin(longdiff / 2), 2) * cos(lat1) * cos(lat2));
double radius = 6371;      // radius of the earth in km
double distance = 2 * radius * asin(sqrt(dis_part1)) * 1000;  // distance in m
return distance;
}
double convert_Lat(double lati){
double mm_lat;
int dd_lat;
dd_lat = (lati / 100);
mm_lat = lati - (dd_lat* 100);
mm_lat = mm_lat / 60;
return dd_lat + mm_lat;
}
double convert_Lon(double loni){
double mm_longi;
int dd_longi;
dd_longi = (loni / 100);
mm_longi = loni - (dd_longi * 100);
mm_longi = mm_longi / 60;
return dd_longi + mm_longi;
}


