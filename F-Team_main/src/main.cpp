/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\MasukVex 09                                      */
/*    Created:      Tue Sep 10 2019                                           */
/*    Description:  V5 project                                                */
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

void pre_auton( void ) {

}

void autonomous( void ) {

}

void usercontrol( void ) {
  while (1) {
    frontLeft.spin(directionType::fwd, Controller1.Axis3.value(), velocityUnits::pct);
    frontRight.spin(directionType::fwd, Controller1.Axis2.value(), velocityUnits::pct);

    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

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