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
#include <stdint.h>
#include <inttypes.h>

// Inlcude custom libraries
#include "Servo.h"
#include "Shooter.h"

// Define pins being used for programs
const int fireLogicPin = 2;
const int servoPin = 3;
const int reloadLogicPin = 4;
const int triggerRelayPin = 5;

// Define time constants
const int fireTimeDelay = 1500;

// Define servo constants
const int servoLoadPosition = 0;
const int servoFirePosition = 140;

// Serial speed constant
const int serialSpeed = 9600;

// Define fire logic
int timesFired = 0;

Servo servo1;

// Define functions
void ExecuteCommands();

// Run setup code
void setup() {
  /*
  Set up function for running Arduino Uno.

  Input: None

  Output: None
  */

  // Set serial speed
  Serial.begin(serialSpeed);
  // Define pin out/in values
  pinMode(reloadLogicPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(fireLogicPin, INPUT);
  pinMode(triggerRelayPin, OUTPUT);

  // Set initial output as low
  digitalWrite(reloadLogicPin, LOW);
  digitalWrite(triggerRelayPin, LOW);

  // Set initial servo position
  servo1.attach(servoPin);
  servo1.write(servoFirePosition);
}

void loop() {
  /*
  Main script look that runs commands to get proessing started. This is simple
  to prevent complication from building here.

  Input: None

  Output: None
  */
  if (1 == 1) {
      // Turn on shooter
      digitalWrite(triggerRelayPin, HIGH);

      // Set servo in load position
      servo1.write(servoLoadPosition);

      // Delay for 1.5 seconds
      delay(fireTimeDelay);

      // Set servo in fire position
      servo1.write(servoFirePosition);

      // Delay for 1.5 seconds
      delay(fireTimeDelay);
      
      // Increment times fired logic
      ++timesFired;
  } else {
      // Turn on shooter
      digitalWrite(triggerRelayPin, LOW);
  }

  // Check if all rounds are fired
  if (timesFired >= 12) {

      // Turn on shooter
      digitalWrite(triggerRelayPin, LOW);

      // Send signal to other arduino
      //returnToReloadSignal();

      // Reset counter
      timesFired = 0;
  }
}