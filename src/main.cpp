#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// inert                inertial      1               
// auton                bumper        C               
// rightDrive           motor         20              
// rightLift            motor         6               
// rightIntake          motor         10              
// inverter             motor         3               
// leftDrive            motor         11              
// leftLift             motor         14              
// leftIntake           motor         5               
// invertLimit          limit         B               
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;

competition Competition;
int path = 0;

float sign(float a) {
  return (a < 0) ? -1 : 1; 
}
bool complete = false;

void flipout() {
  inverter.setPosition(0, degrees);
  while(!invertLimit.pressing()) {
    inverter.spin(forward, 100, percent);
  } inverter.setVelocity(90, percent);
  inverter.rotateFor(reverse, 600, degrees, true);
  leftLift.rotateFor(reverse, 300, degrees, false);
  rightLift.rotateFor(reverse, 300, degrees, true);
  rightLift.rotateFor(forward, 300, degrees, false);
  leftLift.rotateFor(forward, 300, degrees, false);
  wait(1000, msec);
  inverter.rotateTo(0, degrees, 80, velocityUnits::pct, false);
}
void stack() {
  while(!invertLimit.pressing()) {
    inverter.spin(forward, 10, percent);
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
void gyroTurn(double target, double precision, int speed){
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
  auton.pressed(switchPath);
}

void stuff() {
  //im stuff
}
void autonomous(void) {
  switch(path) {
    case 0: 
      leftDrive.spin(forward, 75, percent);
      rightDrive.spin(forward, 75, percent);
      wait(2000, msec);
      leftDrive.spin(reverse, 75, percent);
      rightDrive.spin(reverse, 75, percent);
      wait(2000, msec);
      leftDrive.stop(brakeType::hold);
      rightDrive.stop(brakeType::hold);
      flipout();
    case 1:
      stuff();
    case 2:
      stuff();
    case 3:
      stuff();
    case 4:
      stuff();
  }
}

void usercontrol(void) {
  /*flipout();
  wait(11111, msec);
  inert.calibrate();
  inert.setHeading(0, degrees);
  gyroTurn(90, 3, 40);
  gyroTurn(-90, 3, 40);*/
  Controller1.ButtonA.pressed(flipout);
  Controller1.ButtonY.pressed(stack);
  while (1) {
    
    leftDrive.spin(forward, Controller1.Axis3.position(), percent);
    rightDrive.spin(reverse, Controller1.Axis2.position(), percent);

    if (Controller1.ButtonL1.pressing()) {
      leftLift.spin(reverse, 80, percent);
      rightLift.spin(reverse, 80, percent);
    } else if (Controller1.ButtonL2.pressing()) {
      leftLift.spin(forward, 80, percent);
      rightLift.spin(forward, 80, percent);
    } else {
      leftLift.stop(brakeType::hold);
      rightLift.stop(brakeType::hold);
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
        inverter.spin(forward, 85, percent);
      }
    } else if (Controller1.ButtonDown.pressing()) {
      inverter.spin(reverse, 85, percent);
    } else {
      inverter.stop(brakeType::hold);  
    }
    /*Brain.Screen.clearLine();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print(inert.)*/
    if (Controller1.ButtonX.pressing() && !invertLimit.pressing()) {
      inverter.spin(forward, 15, percent);
    } 
    if (Controller1.ButtonB.pressing()) {
      leftLift.spin(reverse, 20, percent);
      rightLift.spin(reverse, 20, percent);
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
