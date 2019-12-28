using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern inertial inert;
extern bumper auton;
extern motor rightDrive;
extern motor rightLift;
extern motor rightIntake;
extern motor inverter;
extern motor leftDrive;
extern motor leftLift;
extern motor leftIntake;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );