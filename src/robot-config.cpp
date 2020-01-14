#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
bumper auton = bumper(Brain.ThreeWirePort.C);
motor rightDrive = motor(PORT9, ratio18_1, false);
motor rightLift = motor(PORT6, ratio36_1, true);
motor rightIntake = motor(PORT10, ratio18_1, true);
motor inverterLeft = motor(PORT3, ratio36_1, false);
motor leftDrive = motor(PORT2, ratio18_1, false);
motor leftLift = motor(PORT11, ratio36_1, false);
motor leftIntake = motor(PORT5, ratio18_1, false);
limit invertLimit = limit(Brain.ThreeWirePort.B);
motor inverterRight = motor(PORT8, ratio36_1, true);
inertial inert = inertial(PORT1);

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