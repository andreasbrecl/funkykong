// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 10/24/2020
//
// This script is a cope of the main script for arduino, specifically for driving and nothing else.

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

// Define const pins for arudino Uno interaction
const int fireLogicPin = 3;
const int reloadLogicPin = 2; 

// Define const pins for line sensors
const int lineAnalogPin1 = A12;
const int lineAnalogPin2 = A13;
const int lineAnalogPin3 = A14;
const int lineAnalogPin4 = A15;

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

// Define const pins for IMU


// Define const pins for motor drivers

const int BRdirPin = 22;
const int BRstepPin = 23;
const int BLdirPin = 24;
const int BLstepPin = 25;
const int FRdirPin = 26;
const int FRstepPin = 27;
const int FLdirPin = 28;
const int FLstepPin = 29;
const int motorInterfaceType = 1;
const int maxSpeed = 200;
const int stopSpeed = 0;

// Define volitile variable 
volatile bool reloadState = 0;

// Define vehicle mode (0) - don't move, (1) - move to fire position, (2) - return to reload
int driveMode = 0;

// Define boolian vars
bool shouldFire = 0;

// Serial speed constant
const int serialSpeed = 9600;

// Create objects for classes
UnoLogicDriver shooterLogic(fireLogicPin);
UltrasonicSensor ultrasonic();
LineSensor line();
IMUSensor IMU();
DriveTrain Mover( BRdirPin, BRstepPin, BLdirPin, BLstepPin, FRdirPin, FRstepPin, FLdirPin, FLstepPin, motorInterfaceType, maxSpeed, stopSpeed );






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

  // Set up system interupt
  pinMode(reloadLogicPin, INPUT_PULLUP);

  // Define interrupt pin
  attachInterrupt(digitalPinToInterrupt(reloadLogicPin), reloadFunkyKong, RISING);
}

void loop() {
  /*
  Main script look that runs commands to get proessing started. This is simple
  to prevent complication from building here.

  Input: None

  Output: None
  
   ExecuteCommands();
   */

  ExecuteCommands();


  
}

void reloadFunkyKong() {
  /*
  This function sets the reloadState variable to one. This is only activated when
  a system interrupt is recieved by the arduino uno.

  Input: None

  Output: None
  */
  reloadState = 1;
}

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
    
    
    // Set reload state back to 0
    reloadState = 0;
  }

  // Pull data from sensors


  // Send data to raspberry pi

  
  // Pull data from raspberry pi

  
  if (Serial.available() > 0) {
      String driveMode = Serial.readStringUntil('\n');
      //Serial.print("You sent me: ");
      Mover.processCommand(driveMode);
      // Serial.println(driveMode);
        

 
    }


  
  // Send information to motor drivers


  // Send logic to weapon for firing
  shooterLogic.shouldFireLogic(shouldFire);
}

