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
// leftArm              motor         2               
// rightArm             motor         9               
// leftBack             motor         5               
// intakeLeft           motor         7               
// intakeRight          motor         6               
// rightBack            motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

void driveAuton (int leftFrontRotations, int rightFrontRotations, int globalSpeed) {
  leftFront.setVelocity(globalSpeed, velocityUnits::pct);
  rightFront.setVelocity(globalSpeed, velocityUnits::pct);
  leftFront.rotateFor(leftFrontRotations, rotationUnits::deg, false);
  rightFront.rotateFor(rightFrontRotations, rotationUnits::deg, false);
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

  if ((tx >= 252) && (tx <= 312) && (ty >= 90) && (ty <= 125)) {
    finalSelection = currentSelection;
    selectionStage = 1;
    Brain.Screen.clearScreen(); //get rid of residual green bar
  }

  wait(50, msec); // dont let the brain go crazy
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

      confirmButton(252, 135);

      if ((tx >= 252) && (tx <= 297) && (ty >= 85) && (ty <= 130)) {
        pathChoice = 0;
      } else if ((tx >= 307) && (tx <= 352) && (ty >= 85) && (ty <= 130)) {
        pathChoice = 1;
      } else if ((tx >= 252) && (tx <= 352) && (ty >= 135) && (ty <= 170)) {
        selectionStage = 2;
      }

      if (pathChoice == 0) {
        Brain.Screen.drawRectangle(252, 85, 45, 45, "#ffffff");
        Brain.Screen.drawRectangle(307, 85, 45, 45, "#9e9e9e");
      } else if (pathChoice == 1) {
        Brain.Screen.drawRectangle(307, 85, 45, 45, "#ffffff");
        Brain.Screen.drawRectangle(252, 85, 45, 45, "#9e9e9e");
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
            Brain.Screen.drawLine(14, 162, 18, 162);
            Brain.Screen.drawLine(18, 162, 18, 108);
            Brain.Screen.drawRectangle(32, 112, 8, 8, "#ff9d00");
            Brain.Screen.drawCircle(36, 108, 4);
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

  wait(50, msec); // dont let the brain go crazy
}


void pre_auton( void ) {
  vexcodeInit();
  bool complete = false;
  
  while(!complete) {
    if (selectionStage == 0) {
      drawSquares(); 
    } else if (selectionStage == 1) {
      drawPaths();
    } else if (selectionStage == 2) {
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
  switch(finalSelection) {
    case TOPRED: {
      if (pathChoice == 0) {
        /*clawMotor.rotateFor(70, rotationUnits::deg, false);
        wait(100, msec);
        armAuton(80, 120);
        wait(200, msec);
        clawExtendLeft.setVelocity(25, velocityUnits::pct);
        clawExtendRight.setVelocity(25, velocityUnits::pct);
        clawExtendLeft.rotateFor(-125, rotationUnits::deg, false);
        clawExtendRight.rotateFor(-125, rotationUnits::deg, false);
        wait(700, msec);
        driveAuton(60, -60, 70);
        wait(500, msec);
        stopDrive();
        wait(200, msec);
        clawMotor.rotateFor(-70, rotationUnits::deg, false);
        wait(400, msec);
        armAuton(50, -175);
        wait(500, msec);
        clawMotor.rotateFor(70, rotationUnits::deg, false);
        wait(300, msec);
        armAuton(50, 550);
        wait(800, msec);
        driveAuton(620, -630, 20);
        wait(3000, msec);        
        clawMotor.rotateFor(-70, rotationUnits::deg, false);
        wait(100, msec);
        armAuton(55, -230);
        wait(900, msec);
        clawMotor.rotateFor(70, rotationUnits::deg, false);
        wait(100, msec);
        armAuton(50, 70);
        wait(400, msec);
        driveAuton(-600, 600, 70);
        wait(700, msec);
        armAuton(60, -160);
        wait(500, msec);
        driveAuton(-390, -390, 70);
        wait(900, msec);
        driveAuton(875, -875, 100);
        wait(1900, msec);
        clawMotor.rotateFor(-75, rotationUnits::deg, false);
        wait(100, msec);
        armAuton(75, 400);
        wait(600, msec);
        driveAuton(-100, 100, 20);
        clawExtendLeft.setVelocity(25, velocityUnits::pct);
        clawExtendRight.setVelocity(25, velocityUnits::pct);
        clawExtendLeft.rotateFor(125, rotationUnits::deg, false);
        clawExtendRight.rotateFor(125, rotationUnits::deg, false);*/
        armAuton(80, 200);
        wait(1000, msec);
        intakeAuton(directionType::rev);
        driveAuton(40, -40, 80);


      } else if (pathChoice == 1) {
        //empty if statements mean Aiden hasn't made a path for it yet.
      }
      break;
    }
    case SECONDRED: {
      if (pathChoice == 0) {

      } else if (pathChoice == 1) {
        
      }
      break;
    }
    case THIRDRED: {
      if (pathChoice == 0) {

      } else if (pathChoice == 1) {
        
      }
      break;
    }
    case BOTTOMRED: {
      if (pathChoice == 0) {
        driveAuton(300, -300, 100);
        wait(1000, msec);
        driveAuton(-300, 300, 100);
      } else if (pathChoice == 1) {
        
      }
      break;
    }
/*clawMotor.rotateFor(50, rotationUnits::deg, 100);
        wait(100, msec);
        driveAuton(110, -110, 20);
        wait(500, msec);
        armAuton(40, 540, 540);
        wait(400, msec);
        clawExtendLeft.setVelocity(50, velocityUnits::pct);
        clawExtendRight.setVelocity(50, velocityUnits::pct);
        clawExtendLeft.rotateFor(-140, deg, false);
        clawExtendRight.rotateFor(-140, deg, false);
        wait(700, msec);
        driveAuton(650, -650, 20);
        wait(3400, msec);
        armAuton(30, -300, -300);
        wait(30, msec);
        clawMotor.rotateFor(-50, rotationUnits::deg, 100);
        wait(2000, msec);
        clawMotor.rotateFor(50, rotationUnits::deg, 100);*/
    case TOPBLUE: {
      if (pathChoice == 0) {
        /*clawMotor.rotateFor(70, rotationUnits::deg, false);
        wait(100, msec);
        armAuton(80, 120);
        wait(200, msec);
        clawExtendLeft.setVelocity(25, velocityUnits::pct);
        clawExtendRight.setVelocity(25, velocityUnits::pct);
        clawExtendLeft.rotateFor(-125, rotationUnits::deg, false);
        clawExtendRight.rotateFor(-125, rotationUnits::deg, false);
        wait(700, msec);
        driveAuton(60, -60, 70);
        wait(500, msec);
        stopDrive();
        wait(200, msec);
        clawMotor.rotateFor(-70, rotationUnits::deg, false);
        wait(400, msec);
        armAuton(50, -175);
        wait(500, msec);
        clawMotor.rotateFor(70, rotationUnits::deg, false);
        wait(300, msec);
        armAuton(50, 550);
        wait(800, msec);
        driveAuton(620, -630, 20);
        wait(3000, msec);        
        clawMotor.rotateFor(-70, rotationUnits::deg, false);
        wait(100, msec);
        armAuton(55, -230);
        wait(900, msec);
        clawMotor.rotateFor(70, rotationUnits::deg, false);
        wait(100, msec);
        armAuton(50, 70);
        wait(400, msec);
        driveAuton(-600, 600, 70);
        wait(700, msec);
        armAuton(60, -160);
        wait(500, msec);
        driveAuton(390, 390, 70);
        wait(900, msec);
        driveAuton(875, -875, 100);
        wait(1900, msec);
        clawMotor.rotateFor(-75, rotationUnits::deg, false);
        wait(100, msec);
        armAuton(75, 400);
        wait(600, msec);
        driveAuton(-100, 100, 20);
        clawExtendLeft.setVelocity(25, velocityUnits::pct);
        clawExtendRight.setVelocity(25, velocityUnits::pct);
        clawExtendLeft.rotateFor(125, rotationUnits::deg, false);
        clawExtendRight.rotateFor(125, rotationUnits::deg, false);*/
      } else if (pathChoice == 1) {
        
      }
      break;
    }
    case SECONDBLUE: {
      if (pathChoice == 0) {

      } else if (pathChoice == 1) {
        
      }
      break;
    }
    case THIRDBLUE: {
      if (pathChoice == 0) {

      } else if (pathChoice == 1) {
        
      }
      break;
    }
    case BOTTOMBLUE: {
      if (pathChoice == 0) {
        driveAuton(300, -300, 100);
        wait(1000, msec);
        driveAuton(-300, 300, 100);
      } else if (pathChoice == 1) {
        
      }
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

void usercontrol(void) {
  // User control code here, inside the loop
  int armPCT = 60;
  int intakePCT = 75;

  while (1) {
    /*
    this is the controler map for controler one
    axis 3 = left side drive
    axis 2 = right side
    L1 bumper = raise arm
    L2 bumper = lower arm
    R1 bumper = open claw
    R2 bumper = close claw
    up button = claw extend
    down button = claw retract
    */
    // The following code drives the robot
    leftFront.spin(directionType::fwd, Controller1.Axis3.position()/1.75, velocityUnits::pct);
    rightFront.spin(directionType::rev, Controller1.Axis2.position()/1.75, velocityUnits::pct);
    leftBack.spin(directionType::fwd, Controller1.Axis3.position()/1.75, velocityUnits::pct);
    rightBack.spin(directionType::rev, Controller1.Axis2.position()/1.75, velocityUnits::pct);
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
    else {
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
    }
    /*if (Controller1.ButtonX.pressing()) {
      leftFront.spin(directionType::fwd, 50, velocityUnits::pct);
      rightFront.spin(directionType::rev, 50, velocityUnits::pct);
    }
    else if (Controller1.ButtonB.pressing()) {
      leftFront.spin(directionType::rev, 50, velocityUnits::pct);
      rightFront.spin(directionType::fwd, 50, velocityUnits::pct);
    }*/
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
