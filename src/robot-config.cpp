#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
inertial inert = inertial(PORT20);
bumper auton = bumper(Brain.ThreeWirePort.B);
motor rightDrive = motor(PORT1, ratio18_1, false);
motor rightLift = motor(PORT4, ratio36_1, true);
motor rightIntake = motor(PORT7, ratio18_1, true);
motor inverter = motor(PORT10, ratio36_1, false);
motor leftDrive = motor(PORT11, ratio18_1, false);
motor leftLift = motor(PORT14, ratio36_1, false);
motor leftIntake = motor(PORT17, ratio18_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}