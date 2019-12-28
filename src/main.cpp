#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// inert                inertial      20              
// auton                bumper        B               
// rightDrive           motor         1               
// rightLift            motor         4               
// rightIntake          motor         7               
// inverter             motor         10              
// leftDrive            motor         11              
// leftLift             motor         14              
// leftIntake           motor         17              
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;

competition Competition;
int path = 0;

float sign(float a) {
  return (a < 0) ? -1 : 1; 
}
bool complete = false;
void gyroTurn(float target, float error, float speed) {
  float originalTarget = target;
  target += inert.heading(degrees);
  target = (target < 0) ? 360 - fabs(target) : target;
  target = (target > 360) ? target - 360 : target;
  while(!complete) {
    leftDrive.spin(forward, sign(originalTarget) * speed, percent);
    rightDrive.spin(forward, sign(originalTarget) * speed, percent);

    complete = (inert.heading(degrees) < (target + error) 
    && inert.heading(degrees) > (target - error));
  } complete = false;
}

void switchPath() {
  if (path < 4) path++; else path = 0; 
}

void pre_auton(void) {
  vexcodeInit();
  while(1) {
    auton.pressed(switchPath);
  }
}

void stuff() {
  //im stuff
}
void autonomous(void) {
  switch(path) {
    case 0: 
      stuff();
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
  inert.calibrate();
  wait(2000, msec);
  gyroTurn(90, 5, 10);
  wait(5000, msec);
  gyroTurn(-90, 5, 10);
  while (1) {
    
    leftDrive.spin(forward, Controller1.Axis3.position(), percent);
    rightDrive.spin(reverse, Controller1.Axis2.position(), percent);

    if (Controller1.ButtonL1.pressing()) {
      leftLift.spin(forward, 80, percent);
      rightLift.spin(reverse, 80, percent);
    } else if (Controller1.ButtonL2.pressing()) {
      leftLift.spin(reverse, 80, percent);
      rightLift.spin(forward, 80, percent);
    } else {
      leftLift.stop(brakeType::coast);
      rightLift.stop(brakeType::coast);
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
      inverter.spin(forward, 85, percent);
    } else if (Controller1.ButtonDown.pressing()) {
      inverter.spin(reverse, 85, percent);
    } else {
      inverter.stop(brakeType::hold);  
    }
    /*Brain.Screen.clearLine();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print(inert.)*/
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
