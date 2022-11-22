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
#include "UltrasonicSensor.h"

// Define const pins for arudino Uno interaction
const int fireLogicPin = 3;
const int reloadLogicPin = 2; 

// Define const pins for ultrasonic sensors
const int sonicTrigPin1 = 45;
const int sonicEchoPin1 = 48;

const int sonicTrigPin2 = 49;
const int sonicEchoPin2 = 42;

const int sonicTrigPin3 = 44;
const int sonicEchoPin3 = 41;

const int sonicTrigPin4 = 47;
const int sonicEchoPin4 = 40;

const int sonicTrigPin5 = 46;
const int sonicEchoPin5 = 43;

// Define distanceVector array
float distanceValue1;
float distanceValue2;
float distanceValue3;
float distanceValue4;
float distanceValue5;

// Serial speed constant
const int serialSpeed = 9600;

// Create objects for classes
UltrasonicSensor ultrasonic1(sonicTrigPin1, sonicEchoPin1);
UltrasonicSensor ultrasonic2(sonicTrigPin2, sonicEchoPin2);
UltrasonicSensor ultrasonic3(sonicTrigPin3, sonicEchoPin3);
UltrasonicSensor ultrasonic4(sonicTrigPin4, sonicEchoPin4);
UltrasonicSensor ultrasonic5(sonicTrigPin5, sonicEchoPin5);

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
  distanceValue1 = ultrasonic1.distanceCalculations();
  Serial.print("Distance 1:");
  Serial.println(distanceValue1);
  distanceValue2 = ultrasonic2.distanceCalculations();
  Serial.print("Distance 2:");
  Serial.println(distanceValue2);
  distanceValue3 = ultrasonic3.distanceCalculations();
  Serial.print("Distance 3:");  
  Serial.println(distanceValue3);
  distanceValue4 = ultrasonic4.distanceCalculations();
  Serial.print("Distance 4:");
  Serial.println(distanceValue4);
  distanceValue5 = ultrasonic5.distanceCalculations();
  Serial.print("Distance 5:");
  Serial.println(distanceValue5);
  Serial.println("==================");

  delay(500);
}


