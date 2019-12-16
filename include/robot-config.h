using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern limit auton;
extern motor leftDrive;
extern motor rightDrive;
extern motor leftLift;
extern motor rightLift;
extern motor inverter;
extern motor intakeLeft;
extern motor intakeRight;
extern inertial inert;
extern motor strafe;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );