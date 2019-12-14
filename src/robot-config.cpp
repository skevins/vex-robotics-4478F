#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor leftFront = motor(PORT19, ratio18_1, false);
motor rightFront = motor(PORT9, ratio18_1, false);
motor leftArm = motor(PORT12, ratio36_1, true);
motor rightArm = motor(PORT1, ratio36_1, false);
motor leftBack = motor(PORT20, ratio18_1, false);
motor intakeLeft = motor(PORT11, ratio18_1, false);
motor intakeRight = motor(PORT6, ratio18_1, true);
motor rightBack = motor(PORT10, ratio18_1, false);
pot autonSel = pot(Brain.ThreeWirePort.B);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}