/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       nicocione                                                 */
/*    Created:      12/10/2023, 5:23:33 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
motor leftMotorA = motor(PORT1, ratio18_1, false);
motor leftMotorB = motor(PORT11, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT10, ratio18_1, true);
motor rightMotorB = motor(PORT20, ratio18_1, true);
motor roller = motor(PORT5, ratio18_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 231.77499999999998, 190.5, mm, 1);

controller Controller1 = controller(primary);




// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}



// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1RightShoulderControlMotorsStopped = true;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis1
      // right = Axis3 - Axis1
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();
      roller.setVelocity(95, percent);
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
      // check the ButtonR1/ButtonR2 status to control Spinner
      if (Controller1.ButtonR1.pressing()) {
        roller.spin(forward);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonR2.pressing()) {
        roller.spin(reverse);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (!Controller1RightShoulderControlMotorsStopped) {
        roller.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1RightShoulderControlMotorsStopped = true;
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);

#pragma endregion VEXcode Generated Robot Configuration
// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;

competition Competition;

float myVariable;

// "when driver control" hat block
int ondriver_drivercontrol_0() {
  return 0;
}

// "when started" hat block
int whenStarted1() {
  return 0;
}

// "when autonomous" hat block
int onauton_autonomous_0() {
  roller.stop();
  roller.setVelocity(95, percent);
  roller.spin(reverse);
   Drivetrain.setDriveVelocity(80, pct);
   Drivetrain.driveFor(-10, inches);
   Drivetrain.driveFor(30, inches);
   Drivetrain.turnFor(50, degrees);
   Drivetrain.driveFor(110, inches);
   Drivetrain.setDriveVelocity(100, pct);
   Drivetrain.turnFor(90, degrees);
   Drivetrain.driveFor(25, inches);
  //Above is auton skill match, below is regular match
  // wait(5, seconds);
  // roller.stop();
  // roller.setVelocity(95, percent);
  // roller.spin(reverse);
  // Drivetrain.driveFor(reverse, 7.0, inches, true);
  // Drivetrain.setDriveVelocity(20.0, percent);
  // Drivetrain.driveFor(forward, 20.0, inches, true);
  // wait(4, seconds);
  // Drivetrain.setDriveVelocity(85.0, percent);
  // Drivetrain.driveFor(reverse, 20.0, inches, true);
  // Drivetrain.turnFor(left, 52.028, degrees, true);
  // Drivetrain.driveFor(forward, 20.0, inches, true);
  // Drivetrain.turnFor(left, 55.0, degrees, true);
  // Drivetrain.driveFor(forward, 125.0, inches, true);
  // Drivetrain.turnFor(left, 85.0, degrees, true);
  // Drivetrain.driveFor(forward,30.0, inches, true);
  // Drivetrain.driveFor(reverse,30.0, inches, true);
  // Drivetrain.turnFor(left, 90.0, degrees, true);
  // Drivetrain.driveFor(forward,30.0, inches, true);

  return 0;
}

void VEXcode_driver_task() {
  // Start the driver control tasks....
  vex::task drive0(ondriver_drivercontrol_0);
  while(Competition.isDriverControl() && Competition.isEnabled()) {this_thread::sleep_for(10);}
  drive0.stop();
  return;
}

void VEXcode_auton_task() {
  // Start the auton control tasks....
  vex::task auto0(onauton_autonomous_0);
  while(Competition.isAutonomous() && Competition.isEnabled()) {this_thread::sleep_for(10);}
  auto0.stop();
  return;
}



int main() {
  vex::competition::bStopTasksBetweenModes = true;
  Competition.autonomous(VEXcode_auton_task);
  Competition.drivercontrol(VEXcode_driver_task);

  // post event registration

  // set default print color to black
  printf("\033[30m");

  // wait for rotation sensor to fully initialize
  wait(30, msec);

  whenStarted1();
}