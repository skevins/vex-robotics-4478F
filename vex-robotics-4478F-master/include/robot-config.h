using namespace vex;

extern brain Brain;

// VEXcode devices
extern inertial GYRO;
extern controller Controller1;
extern motor frontLeft;
extern motor frontRight;
extern motor backLeft;
extern motor backRight;
extern motor LeftFlipOut;
extern motor RightFlipOut;
extern motor MiddleIntakeMotor;
extern motor FinalIntakeMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );