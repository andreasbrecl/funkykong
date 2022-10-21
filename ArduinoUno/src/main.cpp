// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 10/19/2020
//
// Main scripts for operation of the Arduino Uno.
// The Arduino Uno will be operating the shooting mechanism of the robot.
// The Uno will read in if a firing message is set and output if it has
// fired the full 12 times to initate the go back to base sequence.

// Include general Arduino libraries
#include <Arduino.h>
#include <stdint.h>
#include <inttypes.h>

// Inlcude custom libraries
#include "Servo.h"
#include "Shooter.h"

// Define pins being used for programs
const int fireLogicPin = 2;
const int servoPin = 3;
const int reloadLogicPin = 4;

// Define time constants
const int fireTimeDelay = 1500;

// Define servo constants
const int servoLoadPosition = 0;
const int servoFirePosition = 140;

// Create objects for class
Shooter shooter(int fireLogicPin, int servoPin, int reloadLogicPin, int fireTimeDelay, int servoLoadPosition, int servoFirePosition);

// Define functions
bool ExecuteCommands();

// Run setup code
void setup() {
  Serial.begin(9600);
}

void loop() {
  ExecuteCommands();
}

bool ExecuteCommands() {
  shooter.shoot();
}


// Need to make it count 12 times