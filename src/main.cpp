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

void usercontrol(void) {
  while (1) {
    leftDrive.spin(forward, fmin(fabs(Controller1.Axis3.position()/1.28), 6), percent);
    rightDrive.spin(reverse, fmin(fabs(Controller1.Axis2.position()/1.28), 6), percent);

    if (Controller1.ButtonL1.pressing()) {
      
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
