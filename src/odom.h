#ifndef _ODOM_H_
#define _ODOM_H_

//yo my slime, i know you dont really know mandem like that, but i was wondering if, like, i could purchase summin styl fam. just a bit of grub my drilla

#include "vex.h"
#include "math.h"
#include "custommath.h"
#include "trig.h"

float rX = 0;
float rY = 0;
const float wheelCirc = 2.75 * M_PI; //circumference of a 2.75" omni wheel, the ones we use for tracking wheels. This is used to calculate the distance a wheel has traveled.

const int centerToLeft = 0; 
const int centerToRight = 0; //PLEASE CHANGE THESE ONCE WE KNOW WHAT THE REAL WORLD NUMBERS ARE
const int centerToBack = 0;

int tracking() {
  auto leftEnc = leftEncoder.position(degrees);
  auto rightEnc = rightEncoder.position(degrees); //store encoder values
  auto backEnc = backEncoder.position(degrees);
  
  auto prevLeft = leftEnc;
  auto prevRight = rightEnc; //initialize variables that contain encoder values from previous cycle
  auto prevBack = backEnc;

  float theta = GYRO.heading(degrees); //variables for the gyro angle
  float prevTheta = theta;

  float localOffset[2]; //arrays to substitute as geometry vectors
  float globalOffset[2];
  //im making some weird choices with the encoder and previous values
  while(true) {
    leftEnc = leftEncoder.position(degrees);
    rightEnc = rightEncoder.position(degrees); //store encoder values
    backEnc = backEncoder.position(degrees);

    float deltaLeft = ((leftEnc - prevLeft) / 360) * wheelCirc;
    float deltaRight = ((rightEnc - prevRight) / 360) * wheelCirc; //calculate distance traveled by each tracking wheel represented in inches
    float deltaBack = ((backEnc - prevBack) / 360) * wheelCirc;

    prevLeft = leftEnc;
    prevRight = rightEnc; //store previous values
    prevBack = leftEnc;

    theta = GYRO.heading(degrees); //store gyro angle

    float deltaTheta = theta - prevTheta; //calculate change in angle since last cycle

    if ((fabs(deltaTheta) < 0.5) || ((deltaLeft - deltaRight) < 0.5)) { //calculate local offset. if there is no change in orientation, it is just the tracking wheel distances.
      localOffset[0] = deltaBack;    
      localOffset[1] = deltaRight;
    } else {                                                            //if the orientation has changed, then the local offset is calculated.  
      auto temp = 2 * dsin(theta/2);      
      localOffset[0] = temp * (deltaBack / deltaTheta) + centerToBack;
      localOffset[1] = temp * (deltaRight / deltaTheta) + centerToRight;
    }

    float averageOrientation = prevTheta + (deltaTheta/2); //calculate average orientation, which is the difference between the local and global offsets.
    prevTheta = theta; //store gyro angle for use in next cycle

    globalOffset[0] = (dcos(averageOrientation)*localOffset[0]) - (dsin(averageOrientation)*localOffset[1]); //calculate global offset vector
    globalOffset[1] = (dsin(averageOrientation)*localOffset[0]) - (dcos(averageOrientation)*localOffset[1]);

    rX += globalOffset[0]; //calculate position by compounding the global offset every cycle. the summation of all global offset vectors = current position.
    rY += globalOffset[1];

    this_thread::sleep_for(10);
  }
  return 69420; //funny return int because of thread
}

#endif //_ODOM_