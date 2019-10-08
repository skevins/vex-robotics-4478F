using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor leftFront;
extern motor leftBack;
extern motor rightFront;
extern motor rightBack;
extern motor leftArm;
extern motor rightArm;
extern motor clawMotor;
extern motor clawExtend;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );