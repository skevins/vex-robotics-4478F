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
// rightFront           motor         8               
// leftArm              motor         20              
// rightArm             motor         9               
// leftBack             motor         19              
// intakeLeft           motor         18              
// intakeRight          motor         7               
// rightBack            motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
int pathChoice = 0;

void driveAuton (int leftFrontRotations, int rightFrontRotations, int globalSpeed) {
  leftFront.setVelocity(globalSpeed, velocityUnits::pct);
  rightFront.setVelocity(globalSpeed, velocityUnits::pct);
  leftFront.rotateFor(leftFrontRotations, rotationUnits::deg, false);
  rightFront.rotateFor(rightFrontRotations, rotationUnits::deg, false);
  leftBack.setVelocity(globalSpeed, velocityUnits::pct);
  rightBack.setVelocity(globalSpeed, velocityUnits::pct);
  leftBack.rotateFor(leftFrontRotations, rotationUnits::deg, false);
  rightBack.rotateFor(rightFrontRotations, rotationUnits::deg, false);
}
//this function is for moving the arm in autonomus
void armAuton (int speed, int degs) {
  leftArm.setVelocity(speed, velocityUnits::pct );
  rightArm.setVelocity(speed, velocityUnits::pct );
  leftArm.rotateFor( degs, rotationUnits::deg, false );
  rightArm.rotateFor( degs, rotationUnits::deg, false );
}
void intakeAuton(directionType dir) {
  intakeLeft.spin(dir, 100, velocityUnits::pct);
  intakeRight.spin(dir, 100, velocityUnits::pct);
}
void stopDrive() {
  leftFront.stop(brakeType::hold);
  rightFront.stop(brakeType::hold);
  leftBack.stop(brakeType::hold);
  rightBack.stop(brakeType::hold);
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
  Brain.Screen.printAt(x+16, y+24, false, "Confirm");
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

  if ((tx >= 252) && (tx <= 312) && (ty >= 90) && (ty <= 125) && (currentSelection != NONE)) {
    finalSelection = currentSelection;
    selectionStage = 1;
    Brain.Screen.clearScreen(); //get rid of residual stuff
  }

  wait(50, msec); // dont let the brain go crazy
}

void pre_auton( void ) {
  vexcodeInit();
  bool complete = false;
  
  while(!complete) {
    if (selectionStage == 0) {
      drawSquares(); 
    } else if (selectionStage == 1) {
      complete = true;
      Brain.Screen.clearScreen();
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
      intakeLeft.stop(brakeType::hold);
      intakeRight.stop(brakeType::hold);
      armAuton(80, 120);
      wait(300, msec);
      driveAuton(20, -20, 100);
      wait(20, msec);
      stopDrive();
      wait(30, msec);
      driveAuton(80, -80, 100);
      wait(700, msec);
      intakeAuton(directionType::rev);
      driveAuton(80, -80, 80);
      armAuton(80, -80);
      wait(300, msec);
      armAuton(80, 500);
      wait(600, msec);
      driveAuton(578, -570, 40);
      wait(1500, msec);
      armAuton(80, -400);
      wait(1000, msec);
      driveAuton(-560, 580, 60);
      wait(100, msec);
      armAuton(80, -60);
      wait(1100, msec);
      driveAuton(410, 410, 50);
      wait(1500, msec);
      driveAuton(1000, -1000, 50);
      wait(1500, msec);
      intakeAuton(directionType::fwd);
      driveAuton(20, -20, 75);
      wait(100, msec);
      armAuton(80, 550);
      wait(1000, msec);
      armAuton(80, -450);
  switch(finalSelection) {
    case TOPRED: {

      break;
    }
    case SECONDRED: {

      break;
    }
    case THIRDRED: {

      break;
    }
    case BOTTOMRED: {
      driveAuton(300, -300, 100);
      wait(1000, msec);
      driveAuton(-300, 300, 100);
      break;
    }
    case TOPBLUE: {

      break;
    }
    case SECONDBLUE: {

      break;
    }
    case THIRDBLUE: {

      break;
    }
    case BOTTOMBLUE: {
      driveAuton(300, -300, 100);
      wait(1000, msec);
      driveAuton(-300, 300, 100);
      break;
    }
  }  
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
double driveFactor = 1.25;

void switchDriveSpeed() {
  if (driveFactor == 1.25) {
    driveFactor = 2.50;
  } else if (driveFactor == 2.50) {
    driveFactor = 1.25;
  } else {
    driveFactor = 2; //backup in case something dumb happens and this code is reached
  }
}

void usercontrol(void) {
  // User control code here, inside the loop
  int armPCT = 60;
  int intakePCT = 75;
  while (1) {
    Controller1.ButtonX.pressed(switchDriveSpeed); // <-- Changes the scale at which the drive motors spin. Useful for precision movements

    // The following code drives the robot, while accounting for DRIFT THAT SHOULDNT BE THERE
    if (abs(Controller1.Axis3.position()) >= 4) {
      leftFront.spin(directionType::fwd, Controller1.Axis3.position()/driveFactor, velocityUnits::pct);
      leftBack.spin(directionType::fwd, Controller1.Axis3.position()/driveFactor, velocityUnits::pct);
    } else {
      leftFront.stop();
      leftBack.stop();
    }

    if (abs(Controller1.Axis2.position()) >= 4) {
      rightFront.spin(directionType::rev, Controller1.Axis2.position()/driveFactor, velocityUnits::pct);
      rightBack.spin(directionType::rev, Controller1.Axis2.position()/driveFactor, velocityUnits::pct);
    } else {
      rightFront.stop();
      rightBack.stop();
    } 

    // the following code raises the arm
    if (Controller1.ButtonL1.pressing()) {
      rightArm.spin(directionType::fwd, armPCT, velocityUnits::pct);
      leftArm.spin(directionType::fwd, armPCT, velocityUnits::pct);
    }
    // this is the reverse, lowering the arm
    else if (Controller1.ButtonL2.pressing()) {
      leftArm.spin(directionType::rev, armPCT-10, velocityUnits::pct);
      rightArm.spin(directionType::rev, armPCT-10, velocityUnits::pct);
    }
    //this makes sure that when we arent moving the arm it is locked in place
    else if (!Controller1.ButtonB.Pressing()) {
      leftArm.stop(brakeType::hold);
      rightArm.stop(brakeType::hold);
    }

    // the following code opens the claw
    if (Controller1.ButtonR1.pressing()) {
      intakeLeft.spin(directionType::rev, intakePCT, velocityUnits::pct);
      intakeRight.spin(directionType::rev, intakePCT, velocityUnits::pct);
    }
      
    // the following code closes the claw
    else if (Controller1.ButtonR2.pressing()) {
      intakeLeft.spin(directionType::fwd, intakePCT, velocityUnits::pct);
      intakeRight.spin(directionType::fwd, intakePCT, velocityUnits::pct);
    }
    //make sure the motor stops when we arent pressing the buttons
    else {
      intakeLeft.stop(brakeType::hold);
      intakeRight.stop(brakeType::hold);
    }
    if (Controller1.ButtonLeft.pressing()) {
      leftArm.spin(directionType::fwd, 50, velocityUnits::pct);
    } else if (Controller1.ButtonRight.pressing()) {
      rightArm.spin(directionType::fwd, 50, velocityUnits::pct);
    } else if (Controller1.ButtonB.pressing()) {
      rightArm.rotateTo(leftArm.rotation(rotationUnits::rev), rotationUnits::rev, false);
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
