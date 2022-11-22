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
const int lineAnalogPin1 = A0;
const int lineDigitalPin1 = 50;

const int lineAnalogPin2 = A1;
const int lineDigitalPin2 = 51;

const int lineAnalogPin3 = A2;
const int lineDigitalPin3 = 52;

const int lineAnalogPin4 = A3;
const int lineDigitalPin4 = 53;

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

// Define vehicle mode 
String driveMode = "A";

// Define boolian vars
bool shouldFire = 0;

// Define distanceVector array
float distanceValue1;
float distanceValue2;
float distanceValue3;
float distanceValue4;
float distanceValue5;

// Define line sensor values
bool lineSensorValue1;
bool lineSensorValue2;
bool lineSensorValue3;
bool lineSensorValue4;

// Define IMU array
double IMUReadings;

// Initalize angle and time
float angle = 0;
double time1 = 0;
double time2 = 0;

// Serial speed constant
const int serialSpeed = 9600;

// Create objects for classes
UnoLogicDriver shooterLogic(fireLogicPin);
UltrasonicSensor ultrasonic1(sonicTrigPin1, sonicEchoPin1);
UltrasonicSensor ultrasonic2(sonicTrigPin2, sonicEchoPin2);
UltrasonicSensor ultrasonic3(sonicTrigPin3, sonicEchoPin3);
UltrasonicSensor ultrasonic4(sonicTrigPin4, sonicEchoPin4);
UltrasonicSensor ultrasonic5(sonicTrigPin5, sonicEchoPin5);
IMUSensor IMU;
DriveTrain Mover(BRdirPin, BRstepPin, BLdirPin, BLstepPin, FRdirPin, FRstepPin, FLdirPin, FLstepPin, motorInterfaceType, maxSpeed, stopSpeed);
LineSensor lineSensor1(lineAnalogPin1, lineDigitalPin1);
LineSensor lineSensor2(lineAnalogPin2, lineDigitalPin2);
LineSensor lineSensor3(lineAnalogPin3, lineDigitalPin3);
LineSensor lineSensor4(lineAnalogPin4, lineDigitalPin4);
SerialComms serialComms;

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
  distanceValue2 = ultrasonic2.distanceCalculations();
  distanceValue3 = ultrasonic3.distanceCalculations();
  distanceValue4 = ultrasonic4.distanceCalculations();
  distanceValue5 = ultrasonic5.distanceCalculations();
  lineSensorValue1 = lineSensor1.lineSensorOutputs();
  lineSensorValue2 = lineSensor2.lineSensorOutputs();
  lineSensorValue3 = lineSensor3.lineSensorOutputs();
  lineSensorValue4 = lineSensor4.lineSensorOutputs();
  IMUReadings = IMU.calculateAngle(angle, time1);
  time1 = millis();

  // Send data to raspberry pi
  serialComms.sendSerial(distanceValue1, distanceValue2, distanceValue3, distanceValue4, distanceValue5,
    lineSensorValue1, lineSensorValue2, lineSensorValue3, lineSensorValue4, IMUReadings);
  
  // Pull data from raspberry pi
  driveMode = serialComms.recieveSerial();

  // Send information to motor drivers
  // ENTER DRIVEMODE COMMAND HERE

  // Send logic to weapon for firing
  shooterLogic.shouldFireLogic(shouldFire);
}

