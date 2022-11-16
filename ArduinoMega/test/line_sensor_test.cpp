// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 11/16/2022
//
// Test script for line sensor.

// Include general Arudino/C++ libraries
#include <Arduino.h>
#include <stdint.h>
#include <inttypes.h>

// Inlcude custom libraries
#include "LineSensor.h"

// Define const pins for line sensors
const int lineAnalogPin1 = A12;
const int lineDigitalPin1 = 46;

// Define line sensor values
bool lineSensorValue1;
bool lineSensorValue2;
bool lineSensorValue3;
bool lineSensorValue4;

// Define IMU array
double IMUReadings;

// Serial speed constant
const int serialSpeed = 9600;

// Create objects for classes
LineSensor lineSensor1(lineAnalogPin1, lineDigitalPin1);

// Define functions
void reloadFunkyKong();
void ExecuteCommands();

void setup() {
  /*
  Set up function for running Arduino Mega.

  Input: None

  Output: None
  */

  // Set serial speed
  Serial.begin(serialSpeed);

  /*
  // Set up system interupt
  pinMode(reloadLogicPin, INPUT_PULLUP);

  // Define interrupt pin
  attachInterrupt(digitalPinToInterrupt(reloadLogicPin), reloadFunkyKong, RISING);
  */
}

void loop() {
  /*
  Main script look that runs commands to get proessing started. This is simple
  to prevent complication from building here.

  Input: None

  Output: None
  */
  ExecuteCommands();
}


void ExecuteCommands() {
  /*
  This function runs the other functions for the core processes on the Arduino
  Uno. In this case it runs just the shooting function.

  Input: None

  Output: None
  */

  // Pull data from sensors
  lineSensorValue1 = lineSensor1.lineSensorOutputs();
  Serial.println(lineSensorValue1);
}

