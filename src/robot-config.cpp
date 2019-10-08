#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor leftFront = motor(PORT1, ratio18_1, true);
motor leftBack = motor(PORT2, ratio18_1, false);
motor rightFront = motor(PORT3, ratio18_1, true);
motor rightBack = motor(PORT4, ratio18_1, false);
motor leftArm = motor(PORT5, ratio18_1, true);
motor rightArm = motor(PORT6, ratio18_1, false);
motor clawMotor = motor(PORT7, ratio18_1, false);
motor clawExtend = motor(PORT8, ratio36_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}