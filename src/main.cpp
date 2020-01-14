#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// auton                bumper        C               
// rightDrive           motor         9               
// rightLift            motor         6               
// rightIntake          motor         10              
// inverterLeft         motor         3               
// leftDrive            motor         2               
// leftLift             motor         11              
// leftIntake           motor         5               
// invertLimit          limit         B               
// inverterRight        motor         8               
// inert                inertial      1               
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;

competition Competition;
int path = 0;

void drStraight(int deg, int vel) {
  leftDrive.setVelocity(vel, percent);
  rightDrive.setVelocity(vel, percent);
  leftDrive.rotateFor(forward, deg, degrees, false);
  rightDrive.rotateFor(reverse, deg, degrees, false);
}

float sign(float a) {
  return (a < 0) ? -1 : 1; 
}
bool complete = false;


void flipout() {
  leftLift.setVelocity(100, percent);
  rightLift.setVelocity(100, percent);
  inverterLeft.setPosition(0, degrees);
  inverterLeft.setVelocity(90, percent);
  inverterRight.setPosition(0, degrees);
  inverterRight.setVelocity(90, percent);
  inverterLeft.rotateFor(forward, 650, degrees, false);
  inverterRight.rotateFor(forward, 650, degrees, false);
  wait(1000, msec);
  leftIntake.spin(reverse, 70, percent);
  rightIntake.spin(reverse, 70, percent);
  wait(700, msec);
  leftIntake.stop(brakeType::coast);
  rightIntake.stop(brakeType::coast);
  inverterLeft.rotateFor(reverse, 320, degrees,false);
  inverterRight.rotateFor(reverse, 320, degrees,false);
  wait(700, msec);
  leftLift.rotateFor(reverse, 350, degrees, false);
  rightLift.rotateFor(reverse, 350, degrees, false);
  inverterLeft.rotateFor(forward, 50, degrees, false);
  inverterRight.rotateFor(forward, 50, degrees, false);
  wait(1000, msec);
}
void stack() {
  while(!invertLimit.pressing()) {
    inverterLeft.spin(forward, 10, percent);
    inverterRight.spin(forward, 10, percent);
  } 
  leftIntake.spin(reverse, 15, percent);
  rightIntake.spin(reverse, 15, percent);
  leftDrive.spin(reverse, 15, percent);
  rightDrive.spin(reverse, 15, percent);
  wait(1000, msec);
  leftIntake.stop();
  rightIntake.stop();
  leftDrive.stop();
  rightDrive.stop(); 
}
/*void gyroTurn(double target, double precision, int speed){
  while (inert.rotation(degrees) < target + precision){
    leftDrive.spin(forward, speed, percent);
    rightDrive.spin(forward, speed, percent);
  }
  while (inert.rotation(degrees) > target - precision){
    leftDrive.spin(reverse, speed, percent);
    rightDrive.spin(reverse, speed, percent);
  }
  if (inert.rotation(degrees) > target - precision && inert.rotation(degrees) < target + precision){
    leftDrive.stop(brakeType::hold);
    rightDrive.stop(brakeType::hold);
  }
  else {
    gyroTurn(target, precision, speed/2);
  }
}*/
void gyroTurn(double target, double precision, int speed) {
  if (target < 0) {

    leftDrive.spin(reverse, speed, percent);
    rightDrive.spin(reverse, speed, percent);
    
    waitUntil((inert.rotation(degrees) > (fabs(target) - precision)) 
    && (inert.rotation(degrees) < (fabs(target) + precision)));

    leftDrive.stop(brakeType::hold);
    rightDrive.stop(brakeType::hold);

    wait(250, msec);
    
    if (!((inert.rotation(degrees) > (fabs(target) - (precision/2))) 
    && (inert.rotation(degrees) < (fabs(target) + (precision/2))))) {
      gyroTurn(target, precision/2, speed/3);
    }

  } else if (target > 0) {

    leftDrive.spin(forward, speed, percent);
    rightDrive.spin(forward, speed, percent);
    
    waitUntil((inert.rotation(degrees) > (fabs(target) - precision)) 
    && (inert.rotation(degrees) < (fabs(target) + precision)));

    leftDrive.stop(brakeType::hold);
    rightDrive.stop(brakeType::hold);

    wait(250, msec);
    
    if (!((inert.rotation(degrees) > (fabs(target) - (precision/2))) 
    && (inert.rotation(degrees) < (fabs(target) + (precision/2))))) {
      gyroTurn(target, precision/2, speed/3);
    }
  }
}

//This function changes the auton path, and is executed when 
//the bumper switch is pressed.
void switchPath() {
  if (path < 4) path++; else path = 0; 
  Brain.Screen.clearLine();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print(path);
}

void pre_auton(void) {
  vexcodeInit();
  inert.calibrate();
  auton.pressed(switchPath);
}

void stuff() {
  //im stuff
}
void autonomous(void) {
  switch(path) {
    case 0: 
      flipout();
      leftIntake.stop(brakeType::coast);
      rightIntake.stop(brakeType::coast);
      leftDrive.spin(forward, 75, percent);
      rightDrive.spin(reverse, 75, percent);
      wait(700, msec);
      leftDrive.spin(reverse, 75, percent);
      rightDrive.spin(forward, 75, percent);
      wait(700, msec);
      leftDrive.stop(brakeType::hold);
      rightDrive.stop(brakeType::hold);
      break;
    case 1:
      flipout();
      drStraight(600, 50); //1sec, travel forward and collect row of 4/intake preload

      break;
    case 2:
      stuff();
    case 3:
      stuff();
    case 4:
      stuff();
  }
}

void usercontrol(void) {
  int yes = 20;
  while (1) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print(leftDrive.rotation(degrees));
    Brain.Screen.newLine();
    Brain.Screen.print(inert.rotation(degrees));
    Brain.Screen.newLine();
    Brain.Screen.print(rightDrive.rotation(degrees));
    //Brain.Screen.print((fabs(leftDrive.rotation(degrees)) + fabs(rightDrive.rotation(degrees))) / 2);
    leftDrive.spin(forward, Controller1.Axis3.position(), percent);
    rightDrive.spin(reverse, Controller1.Axis2.position(), percent);

    if (Controller1.ButtonL1.pressing()) {

      leftLift.spin(reverse, 80, percent);
      rightLift.spin(reverse, 80, percent);
      inverterLeft.spin(forward, 100, percent);
      inverterRight.spin(forward, 100, percent);

    } else if (Controller1.ButtonL2.pressing()) {

      leftLift.spin(forward, 80, percent);
      rightLift.spin(forward, 80, percent);
      inverterLeft.spin(reverse, 100, percent);
      inverterRight.spin(reverse, 100, percent);

    } else {

      leftLift.stop(brakeType::hold);
      rightLift.stop(brakeType::hold);

      if (!Controller1.ButtonUp.pressing() && !Controller1.ButtonDown.pressing())

        inverterLeft.stop(brakeType::hold);
        inverterRight.stop(brakeType::hold);

    }
    if (Controller1.ButtonR1.pressing()) {

      leftIntake.spin(forward, 9, volt);
      rightIntake.spin(forward, 9, volt);

    } else if (Controller1.ButtonR2.pressing()) {

      leftIntake.spin(reverse, 9, volt);
      rightIntake.spin(reverse, 9, volt);

    } else {

      leftIntake.stop(brakeType::hold);
      rightIntake.stop(brakeType::hold);

    }
    if (Controller1.ButtonUp.pressing()) {

      if (!invertLimit.pressing()) {

        inverterLeft.spin(forward, 85, percent);
        inverterRight.spin(forward, 85, percent);

      }
    } else if (Controller1.ButtonDown.pressing()) {

      inverterLeft.spin(reverse, 85, percent);
      inverterRight.spin(reverse, 85, percent);

    }
    if (Controller1.ButtonX.pressing() && !invertLimit.pressing()) {

      inverterLeft.spin(forward, 20, percent);
      inverterRight.spin(forward, 20, percent);

    } 
    if (Controller1.ButtonB.pressing()) {

      leftLift.spin(reverse, 35, percent);
      rightLift.spin(reverse, 35, percent);

      inverterLeft.spin(forward, 44, percent);
      inverterRight.spin(forward, 44, percent);

    } 
    if (Controller1.ButtonRight.pressing()) {

      rightLift.spin(reverse, 50, percent);

    } else if (Controller1.ButtonLeft.pressing()) {

      leftLift.spin(reverse, 50, percent);

    }
    if (Controller1.ButtonA.pressing()) {

      leftIntake.spin(reverse, 20, percent);
      rightIntake.spin(reverse, 20, percent);
      leftDrive.spin(reverse, yes, percent);
      rightDrive.spin(reverse, yes, percent);

    }

    if (Controller1.ButtonY.pressing()) {

      leftDrive.spin(forward, 30, percent);
      rightDrive.spin(forward, 30, percent);

    }
    wait(20, msec); 
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
