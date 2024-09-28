/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      9/3/2024, 4:49:28 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
//other devices
brain  Brain;
controller Controller1 = controller(primary);
//wheel motors
motor leftFront = motor(PORT1, ratio18_1, false);
motor rightFront = motor(PORT2, ratio18_1, true);
motor leftBack = motor(PORT3, ratio18_1, false);
motor rightBack = motor(PORT4, ratio18_1, true);
//chain motor
motor chainMotor = motor(PORT5, ratio6_1, false);
//pneumatics
vex::pneumatics Pneumatic1 = vex::pneumatics(Brain.ThreeWirePort.A); //Finish this line later, I guess
//sensors
inertial Gyro = inertial(PORT6);


//global variables
float pi = 3.1415;
float diameter = 4.00;
float gearRatio = 1.0;



//custom functions


//turn wheels, try to drive
void drive(int lspeed, int rspeed, int wt){
  leftFront.spin(fwd, lspeed, percent);
  leftBack.spin(fwd, lspeed, percent);
  rightFront.spin(fwd, rspeed, percent);
  rightBack.spin(fwd, rspeed, percent);
  wait(wt, msec);
}

//user control driving
void userControlDrive(int lspeed, int rspeed, int wt){
  while (true){
    //Braking/Triggered by X
    if (Controller1.ButtonX.pressing()){
      driveBrake();
    }
    //driving
    lspeed=Controller1.Axis3.position(pct);
    rspeed=Controller1.Axis2.position(pct);
    drive(lspeed, rspeed, 10);
  }
}

//turn chain/intake/escalator
int chainSpeed = 50;
void chainMoterSpin(int chainDirection){
  //Button Y triggers this
  if (Controller1.ButtonY.pressing()){
    if (chainDirection == 0){
      //forward
      chainMotor.spin(fwd, chainSpeed, percent);
    }
    else{
      //backward
      chainMotor.spin(reverse, chainSpeed, percent);
    }
  }
}

//clamp the mobile goal
void clampMobileGoal(){
  //Catches mobile goal using pistons
  //Activated by B and A
  Pneumatic1.set(true);
  wait(10, msec);
}


//brake, don't turn wheels
void driveBrake(){
  leftFront.stop(brake);
  leftBack.stop(brake);
  rightFront.stop(brake);
  rightBack.stop(brake); 
}

//autonomous driving
void inchDrive(float target){
  float x = 0;
  leftFront.setPosition(0, rev);
  x = leftFront.position(rev) * diameter * pi * gearRatio;
  //if the target is greater than 0, drive forward
  if (target>=0){ 
    while (x <= target){
    drive(50, 50, 10);
    x = leftFront.position(rev) * diameter * pi * gearRatio;
    }
  }
  //if the target is less than 0, drive backward
  else if (target <0){
    while (x <=fabs(target)){
      drive(-50, -50, 10);
      x = -leftFront.position(rev) * diameter * pi * gearRatio;
    }
  }
  drive(0, 0, 0);
}

//autonomous turning
void gyroPrint(){
  float heading = Gyro.rotation(deg);
  Brain.Screen.printAt(1, 60, "heading = %2f. degrees", heading);
}
//test Gyro turn function
void newGyroTurnFunction(float target, int maxSpeed = 100){
  Gyro.setRotation(0.0, deg);
  float speed = maxSpeed;
  while(true){
    driveVolts(speed, -speed, 10);
  }
}

void driveVolts(int lspeed, int rspeed, int wt){
  lspeed=lspeed*120;
  rspeed=rspeed*120;
  leftFront.spin(forward, lspeed, voltageUnits::mV);
  rightFront.spin(forward, rspeed, voltageUnits::mV);
  leftBack.spin(forward, lspeed, voltageUnits::mV);
  rightBack.spin(forward, rspeed, voltageUnits::mV);
  wait(wt, msec);
}


//right turn
void gyroTurnRight(float target){
  float heading = 0.0;
  Gyro.setRotation(0.0, degrees);
  while(heading <= target){
    drive(50, -50, 10);
    heading = Gyro.rotation(deg);
  }
  drive(0, 0, 0);
}
//left turn
void gyroTurnLeft(float target){
  float heading = 0.0;
  Gyro.setRotation(0.0, degrees);
  while(heading >= target){
    drive(-50, 50, 10);
    heading = Gyro.rotation(deg);
  }
  drive(0, 0, 0);
}







/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
