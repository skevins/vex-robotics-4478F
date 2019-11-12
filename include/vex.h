/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

#include "robot-config.h"

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
                                                             
//basically names for the numbers that are given by the TouchscreenInput() function
const int TOPBLUE = 0;
const int SECONDBLUE = 1;
const int THIRDBLUE = 2;
const int BOTTOMBLUE = 3;
const int TOPRED = 4;
const int SECONDRED = 5;
const int THIRDRED = 6;
const int BOTTOMRED = 7;
const int NONE = 8;
