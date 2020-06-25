#ifndef _ODOM_
#define _ODOM_

#include "vex.h"
#include "math.h"
#include "custommath.h"
#include "trig.h"

float robotX;
float robotY;

//QUADRANTS USED IN THIS CODE
//      |
//   2  |  1
//-------------
//   4  |  3
//      |

int getQuadrantOfPoint(float _x, float _y)  {
  switch(sign(_x)) {
    case -1:
      return sign(_y) == -1 ? 4 : 2;
    break;
    case 1:
      return sign(_y) == -1 ? 3 : 1; 
    break;
    default: return 0; break;
  }
}    

float distanceToPoint(float _x, float _y) {
  return sqrt( (_x - robotX) + (_y - robotY) );
}

void moveRobotToPoint(float gX, float gY, int gAngle, int speed) { //g means goal

float dist = distanceToPoint(gX, gY);
int gyroAngle = GYRO.heading(degrees);



}

#endif //_ODOM_