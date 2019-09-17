/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       4478F                                                     */
/*    Created:      Tue Sep 10 2019                                           */
/*    Description:  Main robot code                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
// A global instance of vex::competition
vex::competition Competition;

//Declaring motors
vex::motor backLeft = vex::motor( vex::PORT1);
vex::motor backRight = vex::motor( vex::PORT2, true);
vex::motor frontLeft = vex::motor( vex::PORT3, true);
vex::motor frontRight = vex::motor( vex::PORT4);
vex::motor lift1 = vex::motor( vex::PORT5);
vex::motor lift2 = vex::motor( vex::PORT6);   //SOME MOTORS MAY NEED REVERSING
vex::motor clawGrabber = vex::motor( vex::PORT8);
vex::motor clawAdjuster = vex::motor( vex::PORT8);

//Create controller object
vex::controller Controller1 = vex::controller();

//variables for convenience
vex::velocityUnits veloc = vex::velocityUnits::pct;

//variables for math
int leftPower, rightPower;

//Pre-auton, not in use currently
void pre_auton( void ) {

}

//auton, will program
void autonomous( void ) {

}

//main user control
void usercontrol( void ) {
  while (1) {
    //calculate percentage of power used based on the joysticks. make sure it doesnt go below 50%.
    if (Controller1.Axis3.value() > 10) { //a little more than zero to compensate for potential drift.
      leftPower = (Controller1.Axis3.value() / 127) * 100;
      if (leftPower < 50) {
        leftPower = 50;
      }
    } else leftPower = 0;

    if (Controller1.Axis2.value() > 10) { //higher than zero to compensate for drift {
      rightPower = (Controller1.Axis2.value() / 127) * 100;
      if (rightPower < 50) {
        rightPower = 50;
      }
    } else rightPower = 0;
    //simply spin motors when the joysticks are tilted, if the left/right buttons are not pressed
    if (!Controller1.ButtonLeft.pressing() && !Controller1.ButtonRight.pressing()) {
      //if we are not pressing both buttons, spin the motors at a certain power based on joysticks
      frontLeft.spin(directionType::fwd, leftPower, veloc);
      frontRight.spin(directionType::fwd, rightPower, veloc);
      backLeft.spin(directionType::fwd, leftPower, veloc);
      backRight.spin(directionType::fwd, rightPower, veloc);
    } else if (Controller1.ButtonRight.pressing() && !Controller1.ButtonLeft.pressing()) {
      //If we are pressing the right button but not the left, move right
      backRight.spin(directionType::rev, 100, veloc);
      frontLeft.spin(directionType::rev, 100, veloc);
      frontRight.spin(directionType::fwd, 100, veloc);
      backLeft.spin(directionType::fwd, 100, veloc);
    } else if (Controller1.ButtonLeft.pressing() && !Controller1.ButtonRight.pressing()) {
      //if not pressing the right button, but we are pressing the left, move left.
      backRight.spin(directionType::fwd, 100, veloc);
      frontLeft.spin(directionType::fwd, 100, veloc);
      frontRight.spin(directionType::rev, 100, veloc);
      backLeft.spin(directionType::rev, 100, veloc);
    } 


    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//Temporary debugging function, for testing controller and seeing how it works.
/*void debug(void) {
  Brain.Screen.clearLine();
  Brain.Screen.clearScreen();
  Brain.Screen.print(Controller1.Axis1.value());
  Brain.Screen.print(" ");
  Brain.Screen.print(Controller1.Axis2.value());
  Brain.Screen.print(" ");
  Brain.Screen.print(Controller1.Axis3.value());
  Brain.Screen.print(" ");
  Brain.Screen.print(Controller1.Axis4.value());
  
  vex::task::sleep(100);
}*/

int main() {
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}