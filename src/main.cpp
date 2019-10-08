/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// leftFront            motor         1               
// leftBack             motor         2               
// rightFront           motor         3               
// rightBack            motor         4               
// leftArm              motor         5               
// rightArm             motor         6               
// clawMotor            motor         7               
// clawExtend           motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

void driveAuton (int leftFrontRotations, int rightFrontRotations, int leftBackRotations, int rightBackRotations, int globalSpeed) {
  leftBack.setVelocity(globalSpeed, velocityUnits::pct);
  leftFront.setVelocity(globalSpeed, velocityUnits::pct);
  rightBack.setVelocity(globalSpeed, velocityUnits::pct);
  rightFront.setVelocity(globalSpeed, velocityUnits::pct);
  leftBack.rotateFor(leftBackRotations, rotationUnits::rev, false);
  leftFront.rotateFor(leftFrontRotations, rotationUnits::rev, false);
  rightBack.rotateFor(rightBackRotations, rotationUnits::rev, false);
  rightFront.rotateFor(rightFrontRotations, rotationUnits::rev, false);
}
//this function is for moving the arm in autonomus
void armAuton (int time, int speed, int rotations) {
  leftArm.setVelocity(speed, velocityUnits::pct );
  rightArm.setVelocity(speed, velocityUnits::pct );
  leftArm.rotateFor( rotations, rotationUnits::rev, false );
  rightArm.rotateFor( rotations, rotationUnits::rev, false );
}

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

int selectionStage = 0;
int finalSelection;
//This is the function the draws all of the squares on the auton selection screen.
void drawSquares() {

  TouchscreenInput();

  int tx = Brain.Screen.xPosition();
  int ty = Brain.Screen.yPosition();

  Brain.Screen.setPenColor("#9e9e9e");

  for(int row = 1; row < 7; row++) {
    for(int column = 1; column < 7; column++) {
      int dx = column * 35 + column - 36;
      int dy = row * 35 + row - 36;
      if ((column == 1) && (row == 1)) {
        graySquare(0,0);
      } else if ((column == 2) && (row == 1)) {
        redSquare(dx, dy);
      } else if ((column == 5) && (row == 1)) {
        blueSquare(dx, dy);
      } else if ((column == 1) && (row == 2)) {
        if (currentSelection == TOPRED) {
          highlightedSquare(dx, dy);
        } else {
          redSquare(dx, dy);
        }
      } else if ((column == 6) && (row == 2)) {
        if (currentSelection == TOPBLUE) {
          highlightedSquare(dx, dy);
        } else {
          blueSquare(dx, dy);
        }
      } else {
        graySquare(dx, dy);
      }
      if ((column == 1) && (row == 3)) {
        if (currentSelection == SECONDRED) {
          highlightedSquare(dx, dy);
        } else {
          graySquare(dx, dy);
        }
      }
      if ((column == 1) && (row == 4)) {
        if (currentSelection == THIRDRED) {
          highlightedSquare(dx, dy);
        } else {
          graySquare(dx, dy);
        }
      }
      if ((column == 1) && (row == 5)) {
        if (currentSelection == BOTTOMRED) {
          highlightedSquare(dx, dy);
        } else {
          graySquare(dx, dy);
        }
      }
      if ((column == 6) && (row == 3)) {
        if (currentSelection == SECONDBLUE) {
          highlightedSquare(dx, dy);
        } else {
          graySquare(dx, dy);
        }
      }
      if ((column == 6) && (row == 4)) {
        if (currentSelection == THIRDBLUE) {
          highlightedSquare(dx, dy);
        } else {
          graySquare(dx, dy);
        }
      }
      if ((column == 6) && (row == 5)) {
        if (currentSelection == BOTTOMBLUE) {
          highlightedSquare(dx, dy);
        } else {
          graySquare(dx, dy);
        }
      }
      
      confirmButton(252, 90);

    }      
  } 

  if ((tx >= 252) && (tx <= 312) && (ty >= 90) && (ty <= 125)) {
    finalSelection = currentSelection;
    selectionStage = 1;
    Brain.Screen.clearScreen(); //get rid of residual green bar
  }

  task::sleep(50); // dont let the brain go crazy
}

//function for drawing possible paths for robot in pre-auton diagram
int pathChoice = 0;
void drawPaths() {
  int tx = Brain.Screen.xPosition();
  int ty = Brain.Screen.yPosition();
  for(int row = 1; row < 7; row++) {
    for(int column = 1; column < 7; column++) {
      int dx = column * 35 + column - 36;
      int dy = row * 35 + row - 36;
      if ((column == 1) && (row == 1)) {
        graySquare(0, 0);
      } else if ((column == 2) && (row == 1)) {
        redSquare(dx, dy);
      } else if ((column == 5) && (row == 1)) {
        blueSquare(dx, dy);
      } else if ((column == 1) && (row == 2)) {
        redSquare(dx, dy);
      } else if ((column == 6) && (row == 2)) {
        blueSquare(dx, dy);
      } else {
        graySquare(dx, dy);
      }

      Brain.Screen.drawRectangle(252, 85, 45, 45, "#9e9e9e");
      Brain.Screen.drawRectangle(307, 85, 45, 45, "#9e9e9e");

      if ((tx >= 252) && (tx <= 297) && (ty >= 85) && (ty <= 130)) {
        pathChoice = 0;
      } else if ((tx >= 307) && (tx <= 352) && (ty >= 85) && (ty <= 130)) {
        pathChoice = 1;
      }

      if (pathChoice == 0) {
        Brain.Screen.drawRectangle(252, 85, 45, 45, "#ffffff");
      } else if (pathChoice == 1) {
        Brain.Screen.drawRectangle(307, 85, 45, 45, "#ffffff");
      }

      switch (finalSelection) {
        case TOPRED: {
          if (pathChoice == 0) {

          } else if (pathChoice == 1) {

          }
        }
        case SECONDRED: {
          if (pathChoice == 0) {

          } else if (pathChoice == 1) {

          }
        }
        case THIRDRED: {
          if (pathChoice == 0) {

          } else if (pathChoice == 1) {

          }
        }
        case BOTTOMRED: {
          if (pathChoice == 0) {

          } else if (pathChoice == 1) {

          }
        }
        case TOPBLUE: {
          if (pathChoice == 0) {

          } else if (pathChoice == 1) {

          } 
        }
        case SECONDBLUE: {
          if (pathChoice == 0) {

          } else if (pathChoice == 1) {

          }
        }
        case THIRDBLUE: {
          if (pathChoice == 0) {

          } else if (pathChoice == 1) {

          }
        }
        case BOTTOMBLUE: {
          if (pathChoice == 0) {

          } else if (pathChoice == 1) {

          }
        }
      }
    }
  } 

  task::sleep(50); // dont let the brain go crazy
}


void pre_auton( void ) {
  vexcodeInit();
  bool complete = false;
  
  while(!complete) {
    if (selectionStage == 0) {
      drawSquares(); 
    } else if (selectionStage == 1) {
      drawPaths();
    }
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  int strafePCT = 50;
  int armPCT = 100;
  int clawPCT = 100;
  int clawExtendPCT = 50;

  while (1) {
    /*
    this is the controler map for controler one
    axis 3 = left side drive
    axis 2 = right side
    left button = strafe left 
    right button = strafe right
    L1 bumper = raise arm
    L2 bumper = lower arm
    R1 bumper = open claw
    R2 bumper = close claw
    up button = claw extend
    down button = claw retract
    */
    // The following code drives the robot
    leftBack.spin(directionType::fwd, Controller1.Axis3.position(), velocityUnits::pct);
    leftFront.spin(directionType::fwd, Controller1.Axis3.position(), velocityUnits::pct);
    rightBack.spin(directionType::rev, Controller1.Axis2.position(), velocityUnits::pct);
    rightFront.spin(directionType::rev, Controller1.Axis2.position(), velocityUnits::pct);

    // the following code is for strafing
    if (Controller1.ButtonLeft.pressing()) {
      leftBack.spin(directionType::fwd, strafePCT, velocityUnits::pct);
      leftFront.spin(directionType::rev, strafePCT, velocityUnits::pct);
      rightFront.spin(directionType::rev, strafePCT, velocityUnits::pct);
      rightBack.spin(directionType::fwd, strafePCT, velocityUnits::pct);
    }
    //this strafes the other way
    if (Controller1.ButtonRight.pressing()) {
      leftBack.spin(directionType::rev, strafePCT, velocityUnits::pct);
      leftFront.spin(directionType::fwd, strafePCT, velocityUnits::pct);
      rightFront.spin(directionType::fwd, strafePCT, velocityUnits::pct);
      rightBack.spin(directionType::rev, strafePCT, velocityUnits::pct);
    }
    // the following code raises the arm
    if (Controller1.ButtonL1.pressing()) {
      leftArm.stop(brakeType::coast);
      rightArm.stop(brakeType::coast);
      leftArm.spin(directionType::fwd, armPCT, velocityUnits::pct);
      rightArm.spin(directionType::fwd, armPCT, velocityUnits::pct);
    }
    // this is the reverse, lowering the arm
    else if (Controller1.ButtonL2.pressing()) {
      leftArm.spin(directionType::rev, armPCT, velocityUnits::pct);
      rightArm.spin(directionType::rev, armPCT, velocityUnits::pct);
    }
    //this makes sure that when we arent moving the arm it is locked in place
    else {
      leftArm.stop(brakeType::hold);
      rightArm.stop(brakeType::hold);
    }

    // the following code opens the claw
    if (Controller1.ButtonR1.pressing()) {
      clawMotor.spin(directionType::fwd, clawPCT, velocityUnits::pct);
    }
      
    // the following code closes the claw
    if (Controller1.ButtonR2.pressing()) {
      clawMotor.spin(directionType::rev, clawPCT, velocityUnits::pct);
    }
    //this code will extend the claw
    if (Controller1.ButtonUp.pressing()) {
      clawExtend.stop(brakeType::coast);
      clawExtend.spin(directionType::fwd, clawExtendPCT, velocityUnits::pct);
    }

    //this code will retract the claw
    else if (Controller1.ButtonDown.pressing()) {
      clawExtend.stop(brakeType::coast);
      clawExtend.spin(directionType::rev, clawExtendPCT, velocityUnits::pct);
    }

    // this locks the arm extender in place when it is not being used
    else {
      clawExtend.stop(brakeType::hold);
    }
    task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
