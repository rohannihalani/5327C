#include "main.h"
#include "roboto/debug.hpp"
#include "roboto/roboto.hpp"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>

const float PI = 3.1415926;
int flySpeed = 0;
int inSpeed = 0;
bool goingDown = false;
bool r1Engaged = false;
bool r2Engaged = false;
bool l1Engaged = false;
bool l2Engaged = false;
bool isRed = true;
pros::ADIDigitalOut expansion('B', true);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  driveLeftBack.tare_position();
  driveLeftFront.tare_position();
  driveRightBack.tare_position();
  driveRightFront.tare_position();
  driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  inertial_sensor.reset();

  // pros::lcd::initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

void toggleFlySpeed() {
  if (flySpeed == 0) {
    flySpeed = 1;
    flywheel = 127;
    flywheel2 = -127;
  } else if (flySpeed == 1 && goingDown == false) {
    flySpeed = 2;
    flywheel = 95;
    flywheel2 = -95;
  } else if (flySpeed == 2) {
    flySpeed = 1;
    goingDown = true;
    flywheel = 74;
    flywheel2 = -74;
  } else if (flySpeed == 1 && goingDown == true) {
    flySpeed = 0;
    goingDown = false;
    flywheel = 127;
    flywheel2 = -127;
  }
}
void toggleIntake() {
  if (inSpeed == 0) {
    inSpeed = 1;
    intake = -127;
  } else if (inSpeed == 1 && goingDown == false) {
    inSpeed = 2;
    intake = 0;
  } else if (inSpeed == 2) {
    inSpeed = 1;
    goingDown = true;
    intake = 127;
  } else if (inSpeed == 1 && goingDown == true) {
    inSpeed = 0;
    goingDown = false;
    intake = 0;
  }
}

void auton1() {
  intake.move(127);
  flywheel.move(127);
  drive(-30, 30, -315);
  pros::delay(100);
  drive(-45, 45, 35);
  pros::delay(500);
  indexer.set_value(true);
  pros::delay(300);
  indexer.set_value(false);
  pros::delay(300);
  indexer.set_value(true);
  pros::delay(300);
  indexer.set_value(false);
  pros::delay(300);
  drive(-60, 60, 45);
  indexer.set_value(true);
  pros::delay(300);
  indexer.set_value(false);
  pros::delay(300);
  indexer.set_value(true);
  pros::delay(300);
  indexer.set_value(false);
  pros::delay(300);
  drive(-75, 75, 55);
  indexer.set_value(true);
  pros::delay(300);
  indexer.set_value(false);
  pros::delay(300);
  indexer.set_value(true);
  pros::delay(300);
  indexer.set_value(false);
  pros::delay(300);
}

void auton2() {
  intake.move(127);
  flywheel.move(127);
  drive(90, 1, 0);
  pros::delay(300);
  drive(1, 10, -330);
  indexer.set_value(true);
  pros::delay(300);
  indexer.set_value(false);
  pros::delay(300);
  indexer.set_value(true);
  pros::delay(300);
  indexer.set_value(false);
  drive(1, 20, -325);
  indexer.set_value(true);
  pros::delay(300);
  indexer.set_value(false);
  pros::delay(300);
  indexer.set_value(true);
  pros::delay(300);
  indexer.set_value(false);
  drive(0, 20, -320);
  indexer.set_value(true);
  pros::delay(300);
  indexer.set_value(false);
  pros::delay(300);
  indexer.set_value(true);
  pros::delay(300);
  indexer.set_value(false);
}

void auton3() {
  flywheel.move(127);
  rotate(-10);
  indexer.set_value(true);
  pros::delay(300);
  indexer.set_value(false);
}

void auton4() {
  flywheel.move(127);
  flywheel2.move(127);
  pros::delay(5000);
  indexer.set_value(true);
  pros::delay(300);
  indexer.set_value(false);
  indexer.set_value(true);
  pros::delay(300);
  indexer.set_value(false);
  indexer.set_value(true);
  pros::delay(300);
  indexer.set_value(false);
}

void rightSideAuton() {
  if (isRed) {
    intake.move(-127);
  } else {
    intake.move(127);
  }
  drive(15, 0, 180);
  driveLeftBack.move(127);
  driveLeftFront.move(127);
  driveRightBack.move(127);
  driveRightFront.move(127);
  pros::delay(500);
  driveStop();
  rotate(0);
}

void leftSideAuton() {
  if (isRed) {
    intake.move(-127);
  } else {
    intake.move(127);
  }
  move(127);
  pros::delay(500);
  driveStop();
  rotate(0);
}

void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

  float leftJoystick;
  float rightJoystick;
  bool buttonA;
  bool buttonB;
  bool l2;
  bool x;

  Quack wheat = setup_graph(&flywheel, &flywheel2);
  pros::Task update_graph(update, (void *)&wheat, "graph");

  while (true) {
    controller.print(1, 0, "flywheel Velocity: %d", flywheel.get_voltage());
    // driver control
    leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    buttonA = controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);
    buttonB = controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);
    l2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
    x = controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);

    driveRightBack.move(rightJoystick);
    driveRightFront.move(rightJoystick);
    driveLeftBack.move(leftJoystick);
    driveLeftFront.move(leftJoystick);

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) &&
        r1Engaged == false) {
      toggleFlySpeed();
      r1Engaged = true;
    } else if (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      r1Engaged = false;
    }

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) &&
        l1Engaged == false) {
      toggleIntake();
      l1Engaged = true;
    } else if (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      l1Engaged = false;
    }

    if (l2) {
      intake = -35;
    }

    if (x) {
      expansion.set_value(false);
    }

    if (buttonA) {
      indexer.set_value(true);
      pros::delay(100);
      indexer.set_value(false);
    }
    pros::delay(5);
  }
}
