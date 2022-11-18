// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 10/24/2022
//
// Main scripts for operation of the Arduino Mega.
// The Arduino Uno will be operating the distance, tape sensors, IMU, 
// and motor drivers.

// Include general Arudino/C++ libraries
#include <Arduino.h>
#include <stdint.h>
#include <inttypes.h>

// Inlcude custom libraries
#include "IMUSensor.h"

// Define IMU array
double IMUReadings;

// Initalize angle and time
float angle = 0;
double time1 = 0;
double time2 = 0;

// Serial speed constant
const int serialSpeed = 9600;

// Create objects for classes
IMUSensor IMU;

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
  IMU.initialize();
  Serial.begin(serialSpeed);
  Serial.println("START");
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


// void reloadFunkyKong() {
//  /*
//  This function sets the reloadState variable to one. This is only activated when
//  a system interrupt is recieved by the arduino uno.
//
//  Input: None
//
//  Output: None
//  */
//  reloadState = 1;
//}


void ExecuteCommands() {
  /*
  This function runs the other functions for the core processes on the Arduino
  Uno. In this case it runs just the shooting function.

  Input: None

  Output: None
  */
  // Pull data from sensors
  //IMUReadings = IMU.calculateAngle(angle, time1);
  IMUReadings = IMU.readGyro();
  //time1 = millis();
  Serial.println(IMUReadings);
}

