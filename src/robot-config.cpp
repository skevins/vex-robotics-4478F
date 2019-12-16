#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
limit auton = limit(Brain.ThreeWirePort.B);
motor leftDrive = motor(PORT1, ratio18_1, false);
motor rightDrive = motor(PORT4, ratio18_1, true);
motor leftLift = motor(PORT7, ratio36_1, false);
motor rightLift = motor(PORT10, ratio36_1, true);
motor inverter = motor(PORT11, ratio36_1, false);
motor intakeLeft = motor(PORT14, ratio18_1, false);
motor intakeRight = motor(PORT17, ratio18_1, true);
inertial inert = inertial(PORT3);
motor strafe = motor(PORT20, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}