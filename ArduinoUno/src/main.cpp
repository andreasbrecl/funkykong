// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 10/19/2020
//
// Main scripts for operation of the Arduino Uno.
// The Arduino Uno will be operating the shooting mechanism of the robot.
// The Uno will read in if a firing message is set and output if it has
// fired the full 12 times to initate the go back to base sequence.

// Include general Arduino librariess
#include <Arduino.h>

// Inlcude custom libraries
#include "Servo.h"
#include "Shooter.h"

// Define pins being used for programs
const int fireLogicPin = 2;
const int servoPin = 11;
const int reloadLogicPin = 4;
const int triggerRelayPin = 5;

// Define time constants
const int fireTimeDelay = 1500;

// Define servo constants
const int servoLoadPosition = 0;
const int servoFirePosition = 120;

// Serial speed constant
const int serialSpeed = 115200;

// Define fire logic
int timesFired = 0;

// Create objects for class
Shooter shooter(fireLogicPin, servoPin, reloadLogicPin, fireTimeDelay, servoLoadPosition, servoFirePosition, triggerRelayPin);

// Run setup code
void setup() {
  /*
  Set up function for running Arduino Uno.

  Input: None

  Output: None
  */

  // Set serial speed
  Serial.begin(115200);

  // Initalize servo
  shooter.initialize();
}

void loop() {
  /*
  This function runs the other functions for the core processes on the Arduino
  Uno. In this case it runs just the shooting function.

  Input: None

  Output: None
  */

  // Activate the shooting functionality from the shooting class
  timesFired = shooter.shoot(timesFired);
}