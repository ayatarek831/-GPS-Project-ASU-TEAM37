#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926535

double degtorad(double deg);
double radtodeg(double rad);
double deg_DD(int degree,double min);
double Min(double x);


// get 2 coordinates from GPS function in Degrees Decimal Minutes (DDM) and return the distance

int distance(double lat1 , double lon1 , double lat2 , double lon2) {
    double lon;
    double dist;

    double Latitude1, long1 , Latitude2 , long2;

       int deg_lat1 = Deg(lat1);
       double min_lat1 = Min(lat1);
       int deg_lon1 = Deg(lon1);
       double min_lon1 = Min(lon1);

        int deg_lat2 = Deg(lat2);
        double min_lat2 = Min(lat2);
        int deg_lon2 = Deg(lon2);
        double min_lon2 = Min(lon2);

    Latitude1 = deg_DD(deg_lat1 , min_lat1);
    long1 = deg_DD(deg_lon1 , min_lon1);
    Latitude2 = deg_DD(deg_lat2 , min_lat2);
    long2 = deg_DD(deg_lon2 , min_lon2);

    if ((Latitude1 == Latitude2) && (long1 == long2)) {
        return 0;
        }
    else {
        lon = long1 - long2;
        dist = (sin(degtorad(Latitude1)) * sin(degtorad(Latitude2))) + (cos(degtorad(Latitude1)) * cos(degtorad(Latitude2)) * cos(degtorad(lon)));
        dist = acos(dist);
        dist = radtodeg(dist);
        dist = dist * 60 * 1.1515;
        dist = dist * 1.609344 * 1000;

        return (dist);
        }
    }

//this function take the coordinates from gps and return its degree

int Deg(double x) {
int Degree;
x = x /100;
Degree = (int)x;
return Degree;
}

//this function take the coordinates from gps and return its minutes

double Min(double x) {
double minute;
int Degree = Deg(x);
minute = x - (Degree*100);
return minute;

}
void delay(){
   for (int c = 1; c <= 32767; c++)
       for (int d = 1; d <= 32767; d++)
       {}

   return 0;
}


// this function convert from degree to radian
double degtorad(double deg) {
    return (deg * PI / 180);
}
// this function convert from radian to degree
double radtodeg(double rad) {
    return (rad * 180 / PI);
}
    // this function convert from Degrees Decimal Minutes (DDM) to Degrees Decimal (DD)
double deg_DD(int degree,double min) {
    double deg;
    deg = degree +(min/60);
    return deg;
}


    // test distance function
       // test distance function
    int main() {
        int sum = 0;
        double lat1 = 3013.3309;
        double lon1 = 3128.2457;



            while ( sum <= 100) {
                delay();

        double lat2 = 3013.4052;
        double lon2 = 3127.7824;



        int d = distance(lat1 , lon1 , lat2 , lon2);  //dummy data
      //  sum += d;

       lat1 = lat2;
       lon1 = lon2;

       printf("distance is %d meters\n" , d);
            }

    }
