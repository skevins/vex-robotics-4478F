#ifndef __SPED__
# define __SPED__ //@FuzzySn0wman

#include <math.h>

/*
written by aiden pringle very dumbly :)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))
*/

#ifndef radToDeg
# define radToDeg   (180/M_PI)
#endif
//macros because i think macros are cool and i just learned them these could be variables but they are macro because why the hell not
#ifndef degToRad
# define degToRad   (M_PI/180)
#endif

//multiple function declarations are required because of overloading, so that any type works.
/* dsin functions | returns sine of INPUT but input and output are in degrees, same goes for all other functions */
float dsin   (int INPUT)       { return sin(INPUT*degToRad); } 
float dsin   (double INPUT)    { return sin(INPUT*degToRad); }
float dsin   (float INPUT)     { return sin(INPUT*degToRad); }

/* dcos functions */
float dcos   (int INPUT)       { return cos(INPUT*degToRad); }
float dcos   (double INPUT)    { return cos(INPUT*degToRad); }
float dcos   (float INPUT)     { return cos(INPUT*degToRad); }

/* dtan functions */
float dtan   (int INPUT)       { return tan(INPUT*degToRad); }
float dtan   (double INPUT)    { return tan(INPUT*degToRad); }
float dtan   (float INPUT)     { return tan(INPUT*degToRad); }

/* atan2 functions */
float datan2 (int INPUT, int INPUT2)        { return atan2((double)INPUT, (double)INPUT2)*radToDeg; }
float datan2 (double INPUT, double INPUT2)  { return atan2(INPUT, INPUT2)*radToDeg; }
float datan2 (float INPUT, float INPUT2)    { return atan2(INPUT, INPUT2)*radToDeg; }

/* dacos functions */
float dacos  (int INPUT)       { return acos(INPUT)*radToDeg; } 
float dacos  (double INPUT)    { return acos(INPUT)*radToDeg; }
float dacos  (float INPUT)     { return acos(INPUT)*radToDeg; }

/* dasin functions */
float dasin  (int INPUT)       { return asin(INPUT)*radToDeg; } 
float dasin  (double INPUT)    { return asin(INPUT)*radToDeg; }
float dasin  (float INPUT)     { return asin(INPUT)*radToDeg; }

/* atan functions */
float datan  (int INPUT)       { return atan(INPUT)*radToDeg; } 
float datan  (double INPUT)    { return atan(INPUT)*radToDeg; }
float datan  (float INPUT)     { return atan(INPUT)*radToDeg; }
#endif //__SPED__