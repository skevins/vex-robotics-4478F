using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern bumper auton;
extern motor rightDrive;
extern motor rightLift;
extern motor rightIntake;
extern motor inverterLeft;
extern motor leftDrive;
extern motor leftLift;
extern motor leftIntake;
extern limit invertLimit;
extern motor inverterRight;
extern inertial inert;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );