// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// GYRO                 inertial      11              
// Controller1          controller                    
// frontLeft            motor         1               
// frontRight           motor         2               
// backLeft             motor         3               
// backRight            motor         4               
// leftFlipOut          motor         5               
// rightFlipOut         motor         6               
// middleIntake         motor         7               
// finalIntake          motor         12              
// leftEncoder          encoder       A, B            
// rightEncoder         encoder       C, D            
// backEncoder          encoder       E, F            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "trig.h"
#include "custommath.h"
#include "odom.h"

enum motorIndex {
  _bL_ = 0,
  _bR_ = 1,
  _fR_ = 2,                 //enum to simplify human readability for motor speed indices in the motor speeds array
  _fL_ = 3
};

enum autonSquare {
  leftRed,
  rightRed,
  leftBlue,               //enum to simplify human readability of autonomous start positions
  rightBlue,
  none
};

struct preautonStats {
  int tx;
  int ty;                             //structure to act as a container for touch screen variables
  autonSquare touchedSquare = none;
  bool autSel = false;
} p;

using namespace vex;

competition Competition;

void stopAllDrive(brakeType bT) {
  /** 
   * Stops all motors with a specific brakeType.
   */
  backLeft.stop(bT);
  backRight.stop(bT);
  frontLeft.stop(bT);
  frontRight.stop(bT);
}

void resetGyro() {
  /**
   * Stops all motors then calibrates the gyro. I have to experiment with delays to make sure that the code only resumes when the gyro is done.
   */
  stopAllDrive(hold);
  GYRO.calibrate();
}

void drawGoal(int x, int y, color ballC) {
  /* this draws a black circle filled with a colored ball in the middle, looks exactly like a goal from top down */
  /* give color::transparent for ballC to make a goal with no ball */
  Brain.Screen.drawCircle(x, y, 9, color::transparent);
  Brain.Screen.drawCircle(x, y, 8, color::transparent);
  Brain.Screen.drawCircle(x, y, 7, color::transparent);
  Brain.Screen.drawCircle(x, y, 6, ballC);
}

void renderScreen() {
  //for reference the screen is 480 x 272 pixels
  Brain.Screen.clearScreen();
  Brain.Screen.setPenColor("#777777"); //change border color of squares to a slightly darker gray, separates tiles
    
  for (int ROW = 0; ROW < 6; ROW++) 
    for (int COL = 0; COL < 6; COL++) 
      Brain.Screen.drawRectangle( (COL * 35) + 133 , (ROW * 35) + 18 , 35 , 35 , "#888888");
  //^^ The above nested loop generates the 6x6 grid of field tiles in gray

  switch(p.touchedSquare) {
    case leftRed:
      Brain.Screen.drawRectangle(133, 53, 35, 35, color::white); break;
    case rightRed:
      Brain.Screen.drawRectangle(133, 158, 35, 35, color::white); break;                                                                        
    case leftBlue:                                                          //logic to highlight the square that was pressed
      Brain.Screen.drawRectangle(308, 158, 35, 35, color::white); break;
    case rightBlue:
      Brain.Screen.drawRectangle(308, 53, 35, 35, color::white); break;
    default:
      //do nothing if there is no chosen square
    break;
  }

  Brain.Screen.setPenColor(color::red);
  Brain.Screen.drawRectangle(113, 20, 3, 205, color::red);   //draw leftmost red line

  Brain.Screen.setPenColor(color::blue);
  Brain.Screen.drawRectangle(363, 20, 3, 205, color::blue);  //draw rightmost blue line 

  Brain.Screen.setPenColor(color::white); //change to white

  Brain.Screen.drawRectangle(133, 120, 35, 2);               //draw two horizontal white lines on the left
  Brain.Screen.drawRectangle(133, 124, 35, 2);               //
                                                
  Brain.Screen.drawRectangle(167, 18, 2, 209);               //draw vertical white line on the left

  Brain.Screen.drawRectangle(235, 18, 2, 209);               //draw two vertical white lines in the center                                  
  Brain.Screen.drawRectangle(239, 18, 2, 209);               //

  Brain.Screen.drawRectangle(307, 18, 2, 209);               //draw vertical white line on the right

  Brain.Screen.drawRectangle(308, 120, 34, 2);               //draw two horizontal white lines on the right                                                                                    
  Brain.Screen.drawRectangle(308, 124, 34, 2);               //

  Brain.Screen.setPenColor("#444444"); //change color to a dark gray

  Brain.Screen.drawRectangle(133, 18, 209, 2); //
  Brain.Screen.drawRectangle(133, 226, 209, 2);//     Draw field border walls in dark gray
  Brain.Screen.drawRectangle(133, 18, 2, 209); //                                                
  Brain.Screen.drawRectangle(341, 18, 2, 209); //

  Brain.Screen.setPenColor("#222222"); //set color to a very dark gray, pretty much black

  drawGoal(144, 29, color::blue);              //                
  drawGoal(238, 29, color::red);               //draw top three goals
  drawGoal(331, 29, color::red);               //

  drawGoal(144, 123, color::blue);             // 
  drawGoal(238, 123, color::transparent);      //draw middle three goals
  drawGoal(331, 123, color::red);              //

  drawGoal(144, 216, color::blue);             // 
  drawGoal(238, 216, color::blue);             //draw bottom three goals
  drawGoal(331, 216, color::red);              //

  Brain.Screen.drawCircle(155, 40, 6, color::red);
  Brain.Screen.drawCircle(320, 40, 6, color::blue);
  Brain.Screen.drawCircle(320, 205, 6, color::blue);
  Brain.Screen.drawCircle(155, 205, 6, color::red);
  Brain.Screen.drawCircle(238, 70, 6, color::red);          //DRAW ALL THE DAMN BALLS )that arent in goals(
  Brain.Screen.drawCircle(238, 175, 6, color::blue);
  Brain.Screen.drawCircle(238, 107, 6, color::red);
  Brain.Screen.drawCircle(238, 139, 6, color::blue);
  Brain.Screen.drawCircle(222, 123, 6, color::blue);
  Brain.Screen.drawCircle(254, 123, 6, color::red);

  if (p.autSel == false) { 
    Brain.Screen.drawRectangle(0, 0, 80, 272, "#007F00");       //Draw left and right confirmation buttons
    Brain.Screen.drawRectangle(400, 0, 80, 272, "#007F00");
  }
  else {
    Brain.Screen.drawRectangle(0, 0, 80, 272, "#00007F");       //Draw left and right unconfirmation buttons
    Brain.Screen.drawRectangle(400, 0, 80, 272, "#00007F");
  }
  Brain.Screen.printAt(4, 17, false, "Confirm");       //
  Brain.Screen.printAt(4, 234, false, "Confirm");      //     Draw confirm text on confirm buttons
  Brain.Screen.printAt(405, 17, false, "Confirm");     //
  Brain.Screen.printAt(405, 234, false, "Confirm");    //
}

void touchScreenLogic() {
  p.tx = Brain.Screen.xPosition();  // grab coordinates of the touch
  p.ty = Brain.Screen.yPosition();  //

  if (p.autSel == true) goto Render;

  //to make touching squares somewhat easier i included some adjacent tiles in the logic that when touched, count as one tile.
  if ((p.tx >= 133) && (p.tx <= 168)) {
    if ((p.ty >= 53) && (p.ty <= 121)) {               //is it the leftmost red-side position?
      p.touchedSquare = leftRed;
    }
    else if ((p.ty >= 123) && (p.ty <= 193)) {         //is it the rightmost red-side position?
      p.touchedSquare = rightRed;
    }
  }                                                                       //logic to determine which autonomous square was pressed, if any
  
  else if ((p.tx >= 308) && (p.tx <= 343)) {
    if ((p.ty >= 53) && (p.ty <= 121)) {               //is it the rightmost blue-side position?
      p.touchedSquare = rightBlue;
    }
    else if ((p.ty >= 123) && (p.ty <= 193)) {         //is it the leftmost blue-side position?
      p.touchedSquare = leftBlue;
    }
  }

  else if (((p.tx <= 80) || (p.tx >= 400)) && (p.touchedSquare != none)) {
    p.autSel = p.autSel ? false : true;
  }
  Render: renderScreen();
}


void pre_auton(void) {
  /* The pre_auton function draws the field diagram on the screen and sets up the auton path */
  renderScreen(); //draw the brain on the screen once.
  Brain.Screen.pressed(touchScreenLogic); //callback so that the drawing and logic code is only executed when the screen is touched. (this saves tons of resources as opposed to a loop)
}

void autonomous(void) {
  Brain.Screen.clearScreen(); //vamos no auton
  thread ODOM = thread(tracking);
}

void usercontrol(void) {
  /**
   * All of our drive code, used to move the robot around.
   */
  Controller1.ButtonA.pressed(resetGyro); //bind a button to reset the gyro

  double goalAngle = 0, angleIntegral = 0, angleError = 0;
  double normalizer, angleDerivative, previousAngle;
  double kP = 1.5, kI = 0.015, kD = 0.8;                      //i wonder if the doubles consume too much memory compared to floats?? if we add odometry it might get dicey with memory
  double motorSpeeds[4];

  while (1) {
    double gyroAngle = GYRO.heading();       //grab and store the gyro value as a double for precision

    double joyX = Controller1.Axis4.position();       // Set variables for each joystick axis
    double joyY = -Controller1.Axis3.position();      // joyY is negative because driving would be backwards otherwise
    double joyZ = Controller1.Axis1.position()/30.0;    // this here is divided by 30 to make rotation slower and less unwieldy
    
    goalAngle += joyZ; //shift the goal angle when the right joystick is tilted

    if (goalAngle >= 360) 
      goalAngle -= 360;       //adjust goalAngle to wrap around to 0 from 360 and vice versa
    if (goalAngle <= 0)
      goalAngle = 360 - fabs(goalAngle);
    
    double vel = (sqrt((joyX * joyX) + (joyY * joyY)) / M_SQRT2); //get velocity value out of joystick values

    double x2 = vel * (dcos(datan2(joyY, joyX) - gyroAngle));     //i believe these generate coordinates based off the joystick
    double y2 = vel * (dsin(datan2(joyY, joyX) - gyroAngle));     //values. they are used to calculate the direction the robot should move by simulating a graph


    if (x2 == 0) 
      x2 = 0.0001; //safeguard against x2 being zero so no errors occur.
    
    double datanx2y2 = datan(y2/x2);            //save the code from calculating this every single run of the for loop
    double sqrtx2y2 = sqrt((x2*x2) + (y2*y2));  //^^ i believe this line finds the length of the segment made by the joystick to the home position
    
    for(int i = 0, addAngle = 45; i <= 3; i++, addAngle += 90)  //calculates motor speeds and puts them into an array
      motorSpeeds[i] = -dsin(datanx2y2 + addAngle) * sqrtx2y2;  //add angle offsets each motor calc by 90 degrees because the wheels are offset themselves

    if (x2 < 0)                                         //Inverts the motors when x2 is less than 0 to account for the nonnegative sine curve
      for(int i = 0; i <= 3; i++)
        motorSpeeds[i] *= -1;

    previousAngle = angleError;                         //store previous error value for use in derivative

    angleError = gyroAngle - goalAngle;               //difference between the current angle and the goal angle
    
    if (angleError > 180)                               //adjust the angle error to force the pid to follow the shortest
      angleError = -((360 - gyroAngle) + goalAngle);    //direction to the goal
    
    if (angleError < -180)                              //^^second part of above comment
      angleError = (360 - goalAngle) + gyroAngle;       //
    
    if (fabs(angleError) < 10)                          //if the angle error is small enough, activate the integral
      angleIntegral += angleError;                      //
    else                                                //
      angleIntegral = 0;                                //set it to 0 if it's too big

    angleDerivative = previousAngle - angleError;       //calculation of derivative pid value

    double turnValue = (angleError*kP) + (kI*angleIntegral) + (kD*angleDerivative); //final pid calculation

    for(int i = 0; i <= 3; i++) 
      motorSpeeds[i] -= turnValue; //apply turning
    
    double maxAxis = MAX(fabs(joyX), fabs(joyY), fabs(angleError)); //Find the maximum input given by the controller's axes and the angle corrector
    double maxOutput = MAX(fabs(motorSpeeds[0]), fabs(motorSpeeds[1]), fabs(motorSpeeds[2]), fabs(motorSpeeds[3])); //Find the maximum output that the drive program has calculated
      
    if (maxOutput == 0 || maxAxis == 0)
      normalizer = 0; //Prevent the undefined value for normalizer
    else
      normalizer = maxAxis / maxOutput; //calculate normalizer

    for (int i = 0; i <= 3; i++) 
      motorSpeeds[i] *= normalizer; //caps motor speeds to 100 without losing the ratio between each value

    backLeft.spin(forward, motorSpeeds[_bL_], percent);
    backRight.spin(forward, motorSpeeds[_bR_], percent);    //spin the motors at their calculated/stored speeds.
    frontRight.spin(forward, motorSpeeds[_fR_], percent);
    frontLeft.spin(forward, motorSpeeds[_fL_], percent);

    if (Controller1.ButtonR1.pressing()) {     //brings ball straight up and into tower
      leftFlipOut.spin(forward, 100, percent);
      rightFlipOut.spin(forward, 100, percent);
      middleIntake.spin(reverse, 100, percent);
      finalIntake.spin(reverse, 100, percent);
    }
    else if(Controller1.ButtonL1.pressing()) { //brings ball to hoarder cell, by spinning the roller above it backwards
      leftFlipOut.spin(forward, 100, percent);
      rightFlipOut.spin(forward, 100, percent);
      middleIntake.spin(forward, 100, percent);
      finalIntake.spin(reverse, 100, percent);
    }
    else if(Controller1.ButtonR2.pressing()) { //bring balls up, does not shoot them out
      leftFlipOut.spin(reverse, 100, percent);
      rightFlipOut.spin(reverse, 100, percent);
      middleIntake.spin(forward, 100, percent);
      finalIntake.stop(coast);
    }
    else if (Controller1.ButtonL2.pressing()) { //outtake balls
      leftFlipOut.spin(reverse, 100, percent);
      rightFlipOut.spin(reverse, 100, percent);
      middleIntake.spin(reverse, 100, percent);
      finalIntake.stop(coast);
    }
    else {                                    //stops all intake motors
      leftFlipOut.stop(coast);
      rightFlipOut.stop(coast);
      middleIntake.stop(coast);
      finalIntake.stop(coast);
    }
    wait(10, msec); 
  }
}

int main() {
  vexcodeInit();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) { wait(100, msec); }
} 