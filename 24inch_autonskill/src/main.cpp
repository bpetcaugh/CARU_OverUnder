/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  Split Arcade                                              */
/*    This sample allows you to control the V5 Clawbot using the both         */
/*    joystick. Adjust the deadband value for more accurate movements.        */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// LeftMotor            motor         1
// RightMotor           motor         10
// ClawMotor            motor         3
// ArmMotor             motor         8
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

motor m1 = motor(PORT20, ratio18_1, true); // right
motor m2 = motor(PORT17, ratio18_1, false); // left
motor m3 = motor(PORT19, ratio18_1, false); // right
motor m4 = motor(PORT16, ratio18_1, true); // left
motor m5 = motor(PORT15, ratio18_1, false); // left
motor m6 = motor(PORT18, ratio18_1, true); // right
motor m7 = motor(PORT14, ratio18_1, false); // right

//sets up motor groups
motor_group LeftDriveSmart = motor_group(m2, m4, m5);
motor_group RightDriveSmart = motor_group(m1, m3, m6);

//sets up Drivetrain
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 317.5, 355.6, 40, mm);

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Deadband stops the motors when Axis values are close to zero.
  int deadband = 5;

  while (true) {

    //roller spins forward constantly
    m7.spin(forward, 100, percent);

    // Get the velocity percentage of the left motor. (Axis3 + Axis1)
    int leftMotorSpeed =
        Controller1.Axis3.position() + Controller1.Axis1.position();
    // Get the velocity percentage of the right motor. (Axis3 - Axis1)
    int rightMotorSpeed =
        Controller1.Axis3.position() - Controller1.Axis1.position();

    // Set the speed of the left motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(leftMotorSpeed) < deadband) {
      // Set the speed to zero.
      LeftDriveSmart.setVelocity(0, percent);
    } else {
      // Set the speed to leftMotorSpeed
      LeftDriveSmart.setVelocity(leftMotorSpeed, percent);
    }

    // Set the speed of the right motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(rightMotorSpeed) < deadband) {
      // Set the speed to zero
      RightDriveSmart.setVelocity(0, percent);
    } else {
      // Set the speed to rightMotorSpeed
      RightDriveSmart.setVelocity(rightMotorSpeed, percent);
    }

    // Spin both motors in the forward direction.
    LeftDriveSmart.spin(forward);
    RightDriveSmart.spin(forward);

  
  //drives backward to push first triball
  LeftDriveSmart.spin(reverse, 100, percent);
  RightDriveSmart.spin(reverse, 100, percent);
  wait(.2, seconds);
  Drivetrain.stop(coast);
  wait(.3, seconds);

  //drives forward past elevation bar area
  LeftDriveSmart.spin(forward, 100, percent);
  RightDriveSmart.spin(forward, 100, percent);
  wait(.4, seconds);
  Drivetrain.stop(coast);
  wait(.5, seconds);

  //turns 90 degrees right
  LeftDriveSmart.spin(forward, 100, percent);
  RightDriveSmart.spin(reverse, 100, percent);
  wait(0.4, seconds);
  Drivetrain.stop(hold);
  wait(0.35, seconds);

  //moves forward
  LeftDriveSmart.spin(forward, 100, percent);
  RightDriveSmart.spin(forward, 100, percent);
  wait(.35, seconds);
  Drivetrain.stop(coast);
  wait(.5, seconds);

  //turns 90 degrees right
  LeftDriveSmart.spin(forward, 100, percent);
  RightDriveSmart.spin(reverse, 100, percent);
  wait(0.4, seconds);
  Drivetrain.stop(hold);
  wait(0.35, seconds);

  //moves up to push second triball
  LeftDriveSmart.spin(forward, 100, percent);
  RightDriveSmart.spin(forward, 100, percent);
  wait(.4, seconds);
  Drivetrain.stop(coast);
  wait(.5, seconds);


  //turns left to be parralel with center bar
  LeftDriveSmart.spin(reverse, 100, percent);
  wait(.45, seconds);
  Drivetrain.stop(coast);
  wait(.5, seconds);


  //drives forward along bar to push triballs to Robot B
  LeftDriveSmart.spin(forward, 100, percent);
  RightDriveSmart.spin(forward, 100, percent);
  wait(1.6, seconds);
  Drivetrain.stop(coast);
  wait(.5, seconds);

  //drives backward to push any remaining triballs
  LeftDriveSmart.spin(reverse, 100, percent);
  RightDriveSmart.spin(reverse, 100, percent);
  wait(1.5, seconds);
  Drivetrain.stop(coast);
  wait(.5, seconds);

  wait(60, seconds);
  
  }


}
