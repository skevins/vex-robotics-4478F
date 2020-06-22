#include "vex.h"
#include "trig.h"
#include "iostream"
#include "custommath.h"
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// GYRO                 inertial      11              
// Controller1          controller                    
// frontLeft            motor         1               
// frontRight           motor         2               
// backLeft             motor         3               
// backRight            motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;

competition Competition;

void pre_auton(void) {

  vexcodeInit();
}

void autonomous(void) {

}

void usercontrol(void) {
  GYRO.calibrate();
  wait(2000, msec);
  double goalAngle = 0;
  double normalizer;
  while (1) {
    double gyroAngle = GYRO.heading();       //grab and store the gyro value
    double joyX = -Controller1.Axis4.position();      //
    double joyY = -Controller1.Axis3.position();      // Set variables for each joystick axis
    double joyZ = Controller1.Axis1.position()/20; // this here is divided by 20 to make rotation slower and less unwieldy
    
    goalAngle += joyZ;

    if (goalAngle >= 360) {
      goalAngle -= 360;
    }                                       //adjust goalAngle to wrap around to 0 from 360 and vice versa
    if (goalAngle <= 0) {
      goalAngle = 360 - fabs(goalAngle);
    }

    double vel = (sqrt((joyX * joyX) + (joyY * joyY)) / M_SQRT2); //get velocity value out of joystick values

    double x2 = vel * (dcos(datan2(joyY, joyX) - gyroAngle));
    double y2 = vel * (dsin(datan2(joyY, joyX) - gyroAngle));

    if (x2 == 0) {
      x2 = 0.0001; //safeguard against x2 being zero so no errors occur.
    }
    
    double fL = dsin(datan(y2 / x2) + 45) * sqrt((x2 * x2) + (y2 * y2)); //Set the motors to their appropriate speed based on the formula (each are offset by a factor of pi/2 to account for the 90 degree difference in the wheels)
    double fR = dsin(datan(y2 / x2) + 135) * sqrt((x2 * x2) + (y2 * y2));
    double bR = dsin(datan(y2 / x2) + 225) * sqrt((x2 * x2) + (y2 * y2));
    double bL = dsin(datan(y2 / x2) + 315) * sqrt((x2 * x2) + (y2 * y2));

    if(x2 < 0) { //Inverts the motors when x2 is less than 0 to account for the nonnegative sine curve
      fL *= -1;
      fR *= -1;
      bR *= -1;
      bL *= -1;
    }

    double angleError = (gyroAngle - goalAngle);
    if (angleError > 180) {
      angleError = -((360 - gyroAngle) + goalAngle);
    }

    if (angleError < -180) {
      angleError = (360 - goalAngle) + gyroAngle;
    }
    fL -= angleError; //Include the value of the turning axis in the output. We found it most comfortable to reduce the turning strength significantly, but the constant (2) can be adjusted to your driver's preference
    fR -= angleError;
    bR -= angleError;
    bL -= angleError;

    double maxAxis = MAX(fabs(joyX), fabs(joyY), fabs(angleError)); //Find the maximum input given by the controller's axes and the angle corrector
    double maxOutput = MAX(fabs(fL), fabs(fR), fabs(bR), fabs(bL)); //Find the maximum output that the drive program has calculated
      //why the hell does the max function not support 4 arguments like why the fck do i have to do this nested max function bs
    if(maxOutput == 0 || maxAxis == 0)
    {
      normalizer = 0; //Prevent the undefined value for normalizer
    }
    else
    {
      normalizer = maxAxis / maxOutput;
    }
  
    /*fL *= normalizer;
    fR *= normalizer;
    bR *= normalizer;
    bL *= normalizer;*/
    
    /*std::cout << fL << std::endl;
    std::cout << fR << std::endl;
    std::cout << bR << std::endl;
    std::cout << bL << std::endl;*/
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(5, 5);

    Brain.Screen.print("fL: ");
    Brain.Screen.print(fL);
    Brain.Screen.newLine();
    
    Brain.Screen.print("fR: ");
    Brain.Screen.print(fR);
    Brain.Screen.newLine();
    
    Brain.Screen.print("bR: ");
    Brain.Screen.print(bR);
    Brain.Screen.newLine();
    
    Brain.Screen.print("bL: ");
    Brain.Screen.print(bL);
    Brain.Screen.newLine();
  
    Brain.Screen.print("gA: ");
    Brain.Screen.print(goalAngle);
    Brain.Screen.newLine();
    
    Brain.Screen.print("gyro: ");
    Brain.Screen.print(gyroAngle);
    Brain.Screen.newLine();

    frontLeft.spin(forward, fL, percent);
    frontRight.spin(forward, fR, percent);
    backLeft.spin(forward, bL, percent);
    backRight.spin(forward, bR, percent);
    
    //need TESTING ON AN ACTUAL ROBOT TOPAJ{EPOTJH{PIOADTIPH{BIPDT} hzh aey5hye6q565q63563hfrfxtgsfrzrxtgfrzt4exrfe4zr4frf4e34re3f4s3er545re3fr3f54re3
    //i got testing:)
    wait(20, msec); 
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
