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
  while (1) {

    int l = Controller1.Axis3.position();
    int r = Controller1.Axis2.position();

    if (ls < l)
      ls += 5;
    else if (ls > l) 
      ls -= 5;

    if (rs < r)
      rs += 5;
    else if (rs > r)
      rs -= 5;
    
    leftDrive.spin(forward, ls, percent);
    rightDrive.spin(reverse, rs, percent);

    if (Controller1.ButtonL1.pressing()) {
      
    }
    /*Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(l);
    Controller1.Screen.print(ls);
    Controller1.Screen.print(r);
    Controller1.Screen.print(rs);*/
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
