/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "v5.h"
#include "v5_vcs.h"

using namespace vex; //thank justins kneecaps for this, minus many vex::'s

//brain
brain Brain;

//controller
controller controller1 = controller();

//competition object
competition Competition;

//motors
motor leftFront = motor(PORT1, true);
motor leftBack = motor(PORT2);
motor rightFront = motor (PORT3, true);
motor rightBack = motor (PORT4);
motor leftArm= motor (PORT5, true);
motor rightArm= motor (PORT6);
motor clawMotor= motor (PORT7);
motor clawExtend = motor (PORT8);

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

//this function draws a red square at coordinates
void redSquare(int x, int y) {
  Brain.Screen.drawRectangle(x, y, 35, 35, "#ff0000");
}

//this draws a blue square are given coordinates
void blueSquare(int x, int y) {
  Brain.Screen.drawRectangle(x, y, 35, 35, "#0000ff");
}

void highlightedSquare(int x, int y) {
  Brain.Screen.drawRectangle(x, y, 35, 35, "#ffffff");
}

void graySquare(int x, int y) {
  Brain.Screen.drawRectangle(x, y, 35, 35, "#9e9e9e");
}

void confirmButton(int x, int y) {
  Brain.Screen.drawRectangle(x, y, 100, 35, "#00ff00");
}
//function for receiving touchscreen input
int currentSelection = NONE;
int TouchscreenInput() {
  
  int tx = Brain.Screen.xPosition();
  int ty = Brain.Screen.yPosition();

  if (Brain.Screen.pressing()) {
    if ((tx >= 180) && (tx <= 216)) {
      if ((ty >= 36) && (ty <= 72)) {
        currentSelection = TOPBLUE;
      } else if ((ty > 72) && (ty <= 108)) {
        currentSelection = SECONDBLUE;
      } else if ((ty > 108) && (ty <= 144)) {
        currentSelection = THIRDBLUE;
      } else if ((ty > 144) && (ty <= 180)) {
        currentSelection = BOTTOMBLUE;
      }
    }
    if ((tx >= 0) && (tx <= 36)) {
      if ((ty >= 36) && (ty <= 72)) {
        currentSelection = TOPRED;
      } else if ((ty > 72) && (ty <= 108)) {
        currentSelection = SECONDRED;
      } else if ((ty > 108) && (ty <= 144)) {
        currentSelection = THIRDRED;
      } else if ((ty > 144) && (ty <= 180)) {
        currentSelection = BOTTOMRED;
      }
    }
  }
  return currentSelection;
}