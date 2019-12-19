#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// auton                limit         B               
// leftDrive            motor         1               
// rightDrive           motor         4               
// leftLift             motor         7               
// rightLift            motor         10              
// inverter             motor         11              
// intakeLeft           motor         14              
// intakeRight          motor         17              
// inert                inertial      3               
// strafe               motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;

competition Competition;

int sel = 0;

float sign(float a) {
  return (a < 0) ? -1 : 1;
}

void autonSel() {
  if (sel <= 4) 
    sel++;
  else
    sel = 0;
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print(sel);
}

void pre_auton(void) {
  vexcodeInit();
  //executes autonSel when limitswitch is pressed
  auton.pressed(autonSel);
  while(1){
    wait(100, msec);
  }
}

void autonomous(void) {
  switch(sel) {
    case 0: {
      //Big Blue
    }
    case 1: {
      //Little blue
    }
    case 2: {
      //Big Red
    }
    case 3: {
      //Little red
    }
    case 4: {
      //Prog skills
    }
  }
}
int ls = 0;
int rs = 0;
void usercontrol(void) {
  int leftIntegral = 0;
  int rightIntegral = 0;
  int leftPrevError = 0;
  int rightPrevError = 0;
  int leftSpeed = 0;
  int rightSpeed = 0;
  float kP = 0;
  float kI = 0;
  float kD = 0;
  while (1) {

    int leftTarget = Controller1.Axis3.position();
    int rightTarget = Controller1.Axis2.position();

    int leftError = leftTarget - leftSpeed;
    int rightError = rightTarget - rightSpeed;
    
    if (leftError < 12) {
      leftIntegral += leftError;
    } else {
      leftIntegral = 0;
    }
    if (rightError < 12) {
      rightIntegral += rightError;
    } else {
      rightIntegral = 0;
    }
    
    int leftDerivative = leftError - leftPrevError;
    int rightDerivative = rightError - rightPrevError
    
    leftSpeed = kP*leftError + kI*leftIntegral + kD*leftDerivative;
    rightSpeed = kp*rightError +kI*rightIntegral + kD*rightDerivative;
    
    leftDrive.spin(forward, ls, percent);
    rightDrive.spin(reverse, rs, percent);
    
    int LeftPrevError = leftError;
    int rightPrevError = rightError;
    
    if (Controller1.ButtonR1.pressing()) {
      kP+=0.001;
    } else if (Controller1.ButtonR2.pressing()) {
      kp-=0.001;
    }
    
    wait(50, msec);
    
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
