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
// leftFront            motor         19              
// rightFront           motor         9               
// leftArm              motor         12              
// rightArm             motor         1               
// leftBack             motor         20              
// intakeLeft           motor         11              
// intakeRight          motor         6               
// rightBack            motor         10              
// autonSel             pot           B               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath>

using namespace vex;

// A global instance of competition
competition Competition;
int pathChoice = 0;

float floatAbs(float a) {
  if (a < 0) return a*-1; else return a;
}
void stopDrive() {
  leftFront.stop();
  rightFront.stop();
  leftBack.stop();
  rightBack.stop();
}
void drivePID(float target, float maxSpeed, int dir, int minSpeed) {
  Brain.Screen.setCursor(1,1);
  leftBack.setPosition(0, degrees);
  leftFront.setPosition(0, degrees);
  rightBack.setPosition(0, degrees);
  rightFront.setPosition(0, degrees);
  float deriv, error, prevError;
  float integ = 0;
  float intThres = 20;
  error = target;
  float kP = 0.2;
  float kI = 0.1;
  float kD = 0.1;
  bool complete = false; 
  while(!complete) {

    float leftVal = (floatAbs(leftFront.rotation(degrees)) + floatAbs(leftBack.rotation(degrees))) / 2;
    float rightVal = (floatAbs(rightFront.rotation(degrees)) + floatAbs(rightBack.rotation(degrees))) / 2;
    float currentVal = (leftVal + rightVal) / 2;

    prevError = error;

    error = target - currentVal; 

    if (floatAbs(error) < intThres) {
      integ += error;
    } else {
      integ = 0;
    }

    deriv = error - prevError;

    Brain.Screen.newLine();

    float SPEED = kP*error + kI*integ + kD*deriv;

    Brain.Screen.print(SPEED);

    SPEED = !(SPEED < maxSpeed) ? maxSpeed : SPEED;

    leftFront.spin(forward, dir*SPEED, velocityUnits::pct);
    leftBack.spin(forward, dir*SPEED, velocityUnits::pct);
    rightFront.spin(reverse, dir*SPEED, velocityUnits::pct);
    rightBack.spin(reverse, dir*SPEED, velocityUnits::pct);

    if (SPEED <= minSpeed) {
      stopDrive();
      complete = true;
    }

    task::sleep(40);
  }
}

void turnPID(float target, float maxSpeed, int dir, int minSpeed) {
  Brain.Screen.setCursor(1,1);
  leftBack.setPosition(0, degrees);
  leftFront.setPosition(0, degrees);
  rightBack.setPosition(0, degrees);
  rightFront.setPosition(0, degrees);
  float derivL, errorL, prevErrorL, derivR, errorR, prevErrorR;
  float integL = 0;
  float integR = 0;
  float intThres = 20;
  errorL = target;
  errorR = target;
  bool completeL = false;
  bool completeR = false;
  bool complete = false;
  float kP = 0.2;
  float kI = 0.1;
  float kD = 0.1;
  //everything below here goes into a 
  while(!complete) {
    if (!completeL) {
      float leftVal = (floatAbs(leftFront.rotation(degrees)) + floatAbs(leftBack.rotation(degrees))) / 2;

      prevErrorL = errorL;

      errorL = target - leftVal; 

      if (floatAbs(errorL) < intThres) {
        integL += errorL;
      } else {
        integL = 0;
      }

      derivL = errorL - prevErrorL;

      Brain.Screen.newLine();

      float SPEEDL = kP*errorL + kI*integL + kD*derivL;

      Brain.Screen.print(SPEEDL);

      SPEEDL = !(SPEEDL < maxSpeed) ? maxSpeed : SPEEDL; //min was acting weird so i went RAW

      leftFront.spin(forward, dir*SPEEDL, velocityUnits::pct);
      leftBack.spin(forward, dir*SPEEDL, velocityUnits::pct);

      if (SPEEDL <= minSpeed) {
        leftFront.stop();
        leftBack.stop();
        completeL = true;
      } 
    }
    if (!completeR) {
      float rightVal = (floatAbs(rightFront.rotation(degrees)) + floatAbs(rightBack.rotation(degrees))) / 2;

      prevErrorR = errorR;

      errorR = target - rightVal; 

      if (floatAbs(errorR) < intThres) {
        integR += errorR;
      } else {
        integR = 0;
      }

      derivR = errorR - prevErrorR;

      Brain.Screen.newLine();

      float SPEEDR = kP*errorR + kI*integR + kD*derivR;

      Brain.Screen.print(SPEEDR);

      SPEEDR = !(SPEEDR < maxSpeed) ? maxSpeed : SPEEDR; //min was acting weird so i went RAW

      rightFront.spin(forward, dir*SPEEDR, velocityUnits::pct);
      rightBack.spin(forward, dir*SPEEDR, velocityUnits::pct);

      if (SPEEDR <= minSpeed) {
        rightFront.stop();
        rightBack.stop();
        completeR = true;
      }
    }
    if (completeL && completeR) {
      stopDrive();
      complete = true;
    }
    task::sleep(40);
  }
}
void armPID(int target, int maxSpeed, int dir, int minSpeed) {
  Brain.Screen.setCursor(1,1);
  leftArm.setPosition(0, degrees);
  rightArm.setPosition(0, degrees);
  float deriv, error, prevError;
  float integ = 0;
  float intThres = 20;
  error = target;
  bool complete = false;
  float kP = 0.2;
  float kI = 0.1;
  float kD = 0.1;
  //everything below here goes into a 
  while(!complete) {

    float currentVal = (floatAbs(leftArm.rotation(degrees)) + floatAbs(rightArm.rotation(degrees))) / 2;

    prevError = error;

    error = target - currentVal; 

    if (floatAbs(error) < intThres) {
      integ += error;
    } else {
      integ = 0;
    }

    deriv = error - prevError;

    Brain.Screen.newLine();

    float SPEED = kP*error + kI*integ + kD*deriv;

    Brain.Screen.print(SPEED);

    SPEED = !(SPEED < maxSpeed) ? maxSpeed : SPEED;

    leftArm.spin(forward, dir*SPEED, velocityUnits::pct);
    rightArm.spin(forward, dir*SPEED, velocityUnits::pct);

    if (SPEED <= minSpeed) {
      leftArm.stop(brakeType::hold);
      rightArm.stop(brakeType::hold);
      complete = true;
    }

    task::sleep(40);
  }  
}

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

int autonSelection;
void pre_auton( void ) {
  vexcodeInit();
  while(true) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(autonSel.angle(degrees));
    Brain.Screen.newLine();
    int a = autonSel.angle(degrees);
    if ((a >= 0) && (a <= 15)) {
      Brain.Screen.print("Top Red");
      autonSelection = 1;
    } else if (a <= 42) {
      Brain.Screen.print("Bottom Red");
      autonSelection = 2;
    } else if (a <= 68) {
      Brain.Screen.print("Top Blue");
      autonSelection = 3;
    } else if (a <= 101) {
      Brain.Screen.print("Bottom Blue");
      autonSelection = 4;
    } else if (a <= 134) {
      Brain.Screen.print("Programming Skills");
      autonSelection = 5;
    } else {
      Brain.Screen.print("No program set");
      autonSelection = 0;
    }
    Brain.Screen.newLine();
    Brain.Screen.print(leftFront.rotation(degrees));
    Brain.Screen.newLine();
    Brain.Screen.print(leftBack.rotation(degrees));
    Brain.Screen.newLine();
    Brain.Screen.print(rightBack.rotation(degrees));
    Brain.Screen.newLine();
    Brain.Screen.print(rightFront.rotation(degrees));
    Brain.Screen.newLine();
    wait(50, msec);
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
  leftFront.setPosition(0, degrees);
  leftBack.setPosition(0, degrees);
  rightFront.setPosition(0, degrees);
  rightBack.setPosition(0, degrees);

  switch(autonSelection) {
    case 1: {
      //BIG BLUE
      intakeLeft.spin(reverse, 75, velocityUnits::pct);
      intakeRight.spin(reverse, 75, velocityUnits::pct);
      armAuton(100, 150);
      wait(500, msec);
      driveAuton(80, -80, 100);
      wait(500, msec);
      armAuton(40, -100);
      wait(1200, msec);
      intakeLeft.stop();
      intakeRight.stop();
      armPID(820, 80, 1, 50);
      driveAuton(25, 0, 50);
      wait(500, msec);
      drivePID(705, 60, 1, 15);
      intakeLeft.spin(reverse, 75, velocityUnits::pct);
      intakeRight.spin(reverse, 75, velocityUnits::pct);
      armAuton(25, -400);
      wait(2500, msec);
      intakeLeft.stop();
      intakeRight.stop();
      armAuton(50, 50);
      wait(300, msec);
      drivePID(880, 50, -1, 20);
      turnPID(450, 90, 1, 20);
      drivePID(1100, 75, 1, 20);
      armAuton(100, -110);
      wait(500, msec);
      intakeLeft.spin(directionType::fwd, 95, velocityUnits::pct);
      intakeRight.spin(directionType::fwd, 95, velocityUnits::pct);
      rightArm.spin(directionType::fwd, 30, velocityUnits::pct);
      leftArm.spin(directionType::fwd, 30, velocityUnits::pct);
      wait(3000, msec);
      intakeLeft.stop();
      intakeRight.stop();
      rightArm.stop(brakeType::hold);
      leftArm.stop(brakeType::hold);
      driveAuton(-250, 250, 30);
      break;

    }
    case 2: {
      //turnPID(200, 0.2, 0.1, 0.1, 70, true, -1);
      break;
    }
    case 3: {
      //armPID(500, 75, true, -1);
      break;
    }
    case 4: {

    }
    case 5: {

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
double driveFactor = 1.50;


}
void usercontrol(void) {
  // User control code here, inside the loop
  int armPCT = 60;
  int intakePCT = 75;
  while (1) {
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
    if (Controller1.ButtonUp.pressing()) {
      leftFront.spin(directionType::fwd, 50, velocityUnits::pct);
      leftBack.spin(directionType::fwd, 50, velocityUnits::pct);
      rightFront.spin(directionType::rev, 50, velocityUnits::pct);
      rightBack.spin(directionType::rev, 50, velocityUnits::pct);
    } else if (Controller1.ButtonDown.pressing()) {
      leftFront.spin(directionType::rev, 50, velocityUnits::pct);
      leftBack.spin(directionType::rev, 50, velocityUnits::pct);
      rightFront.spin(directionType::fwd, 50, velocityUnits::pct);
      rightBack.spin(directionType::fwd, 50, velocityUnits::pct);
    }
    // the following code raises the arm
    if (Controller1.ButtonL1.pressing()) {
      rightArm.spin(directionType::fwd, armPCT, velocityUnits::pct);
      leftArm.spin(directionType::fwd, armPCT, velocityUnits::pct);
    }
    // this is the reverse, lowering the arm
    else if (Controller1.ButtonL2.pressing()) {
      leftArm.spin(directionType::rev, armPCT-20, velocityUnits::pct);
      rightArm.spin(directionType::rev, armPCT-20, velocityUnits::pct);
    }
    //this makes sure that when we arent moving the arm it is locked in place
    else if (!Controller1.ButtonB.pressing()) {
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

    if (Controller1.ButtonY.pressing() && !Controller1.ButtonR1.pressing() && 
    !Controller1.ButtonR2.pressing() && !Controller1.ButtonL1.pressing() && 
    !Controller1.ButtonL2.pressing()) {
      intakeLeft.spin(directionType::fwd, intakePCT, velocityUnits::pct);
      intakeRight.spin(directionType::fwd, intakePCT, velocityUnits::pct);
      rightArm.spin(directionType::fwd, 29, velocityUnits::pct);
      leftArm.spin(directionType::fwd, 29, velocityUnits::pct);      
    }
    task::sleep(40); //Sleep the task for a short amount of time to prevent wasted resources.
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