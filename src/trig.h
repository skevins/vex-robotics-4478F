#ifndef __SPED__
#define __SPED__ //@FuzzySn0wman

#include <math.h>

# define radToDeg   57.2957795130823
# define degToRad   0.01745329251994

//multiple function declarations are required because of overloading, so that any type works.
/* dsin functions | returns sine of INPUT but input and output are in degrees, same goes for all other functions */
float dsin   (int INPUT)       { return sin(INPUT*degToRad); } 
double dsin   (double INPUT)    { return sin(INPUT*degToRad); }
float dsin   (float INPUT)     { return sin(INPUT*degToRad); }

/* dcos functions */
float dcos   (int INPUT)       { return cos(INPUT*degToRad); }
double dcos   (double INPUT)    { return cos(INPUT*degToRad); }
float dcos   (float INPUT)     { return cos(INPUT*degToRad); }

/* dtan functions */
float dtan   (int INPUT)       { return tan(INPUT*degToRad); }
double dtan   (double INPUT)    { return tan(INPUT*degToRad); }
float dtan   (float INPUT)     { return tan(INPUT*degToRad); }

/* atan2 functions */
float datan2 (int INPUT, int INPUT2)        { return atan2((double)INPUT, (double)INPUT2)*radToDeg; }
double datan2 (double INPUT, double INPUT2)  { return atan2(INPUT, INPUT2)*radToDeg; }
float datan2 (float INPUT, float INPUT2)    { return atan2(INPUT, INPUT2)*radToDeg; }

/* dacos functions */
float dacos  (int INPUT)       { return acos(INPUT)*radToDeg; } 
double dacos  (double INPUT)    { return acos(INPUT)*radToDeg; }
float dacos  (float INPUT)     { return acos(INPUT)*radToDeg; }

/* dasin functions */
float dasin  (int INPUT)       { return asin(INPUT)*radToDeg; } 
double dasin  (double INPUT)    { return asin(INPUT)*radToDeg; }
float dasin  (float INPUT)     { return asin(INPUT)*radToDeg; }

/* atan functions */
float datan  (int INPUT)       { return atan(INPUT)*radToDeg; } 
double datan  (double INPUT)    { return atan(INPUT)*radToDeg; }
float datan  (float INPUT)     { return atan(INPUT)*radToDeg; }

#define toRadians(INPUT) \
  ((INPUT) * degToRad)

#define toDegrees(INPUT) \
  ((INPUT) * radToDeg)

#endif //__SPED__