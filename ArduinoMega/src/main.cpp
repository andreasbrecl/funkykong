// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 10/24/2022
//
// Main scripts for operation of the Arduino Mega.
// The Arduino Uno will be operating the distance, tape sensors, IMU, 
// and motor drivers.

// Include general Arudino libraries
#include <Arduino.h>
#include <stdint.h>
#include <inttypes.h>

// Inlcude custom libraries
#include "UnoLogicDriver.h"
#include "UltrasonicSensor.h"
#include "LineSensor.h"
#include "IMUSensor.h"
#include "AccelStepper.h"
#include "MultiStepper.h"
#include "DriveTrain.h"
#include "LineSensor.h"
#include "SerialComms.h"

// Define const pins for arudino Uno interaction
const int fireLogicPin = 3;
const int reloadLogicPin = 2; 

// Define const pins for line sensors
const int lineAnalogPin1 = A12;
const int lineAnalogPin2 = A13;
const int lineAnalogPin3 = A14;
const int lineAnalogPin4 = A15;
const int lineDigitalPin1 = 46;
const int lineDigitalPin2 = 47;
const int lineDigitalPin3 = 48;
const int lineDigitalPin4 = 49;

// Define const pins for ultrasonic sensors
const int sonicTrigPin1 = 30;
const int sonicTrigPin2 = 32;
const int sonicTrigPin3 = 34;
const int sonicTrigPin4 = 36;
const int sonicTrigPin5 = 40;
const int sonicEchoPin1 = 31;
const int sonicEchoPin2 = 33;
const int sonicEchoPin3 = 35;
const int sonicEchoPin4 = 37;
const int sonicEchoPin5 = 41;

// Define const pins for motor drivers
const int BRdirPin = 22;
const int BRstepPin = 23;
const int BLdirPin = 24;
const int BLstepPin = 25;
const int FRdirPin = 26;
const int FRstepPin = 27;
const int FLdirPin = 28;
const int FLstepPin = 29;

// Define motor int vars
const int motorInterfaceType = 1;
const int maxSpeed = 900;
const int stopSpeed = 0;

// Define volitile variable 
volatile bool reloadState = 0;

// Define vehicle mode (0) - don't move, (1) - move to fire position, (2) - return to reload
int driveMode = 0;

// Define boolian vars
bool shouldFire = 0;

// Define distanceVector array
float* distanceVectorOutput;

// Define line sensor values
bool lineSensorValue1;
bool lineSensorValue2;
bool lineSensorValue3;
bool lineSensorValue4;

// Define IMU array
double* IMUReadingsVector;

// Initalize angle and time
float angle = 0;
long int time1 = 0;
long int time2 = 0;

// Serial speed constant
const int serialSpeed = 9600;

// Create objects for classes
UnoLogicDriver shooterLogic(fireLogicPin);
UltrasonicSensor ultrasonic(sonicTrigPin1, sonicTrigPin2, sonicTrigPin3, sonicTrigPin4, sonicTrigPin5, sonicEchoPin1, sonicEchoPin2, sonicEchoPin3, sonicEchoPin4, sonicEchoPin5);
IMUSensor IMU;
DriveTrain Mover(BRdirPin, BRstepPin, BLdirPin, BLstepPin, FRdirPin, FRstepPin, FLdirPin, FLstepPin, motorInterfaceType, maxSpeed, stopSpeed);
LineSensor lineSensor1(lineAnalogPin1, lineDigitalPin1);
LineSensor lineSensor2(lineAnalogPin2, lineDigitalPin2);
LineSensor lineSensor3(lineAnalogPin3, lineDigitalPin3);
LineSensor lineSensor4(lineAnalogPin4, lineDigitalPin4);

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

  // Check if reload state is set to one
  if (reloadState == 1) {
    // Set function here to change state
    driveMode = 2;

    // Set reload state back to 0
    reloadState = 0;
  }

  // Pull data from sensors
  distanceVectorOutput = ultrasonic.distanceCalculations();
  lineSensorValue1 = lineSensor1.lineSensorOutputs();
  lineSensorValue2 = lineSensor2.lineSensorOutputs();
  lineSensorValue3 = lineSensor3.lineSensorOutputs();
  lineSensorValue4 = lineSensor4.lineSensorOutputs();
  IMUReadingsVector = IMU.calculateAngle(angle);

  // Send data to raspberry pi

  
  // Pull data from raspberry pi


  // Send information to motor drivers


  // Send logic to weapon for firing
  shooterLogic.shouldFireLogic(shouldFire);
}

