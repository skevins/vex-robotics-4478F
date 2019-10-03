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

//this function draws a red square at coordinates
void redSquare(int x, int y) {
  Brain.Screen.drawRectangle(x, y, 35, 35, "#ff0000");
}

//this draws a blue square are given coordinates
void blueSquare(int x, int y) {
  Brain.Screen.drawRectangle(x, y, 35, 35, "#0000ff");
}