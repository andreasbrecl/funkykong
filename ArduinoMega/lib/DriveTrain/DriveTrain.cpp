// Author: Sean Newman
// MCEN 5115 Mario Kart Balloon Battle
// 10/31/2022
//
// This script will define the motors and for the drive train so that we cant move.

#include <Arduino.h>
#include "AccelStepper.h"
#include "MultiStepper.h"
#include "DriveTrain.h"

DriveTrain::DriveTrain(int BRdirPin, int BRstepPin, int BLdirPin, int BLstepPin, int FRdirPin, int FRstepPin, int FLdirPin, int FLstepPin, int motorInterfaceType, int maxSpeed, int stopSpeed ) {
    
    // Define variables as internal and private to the class using pointers
    this->BRdirPin = BRdirPin;
    this->BRstepPin = BRstepPin;
    this->BLdirPin = BLdirPin;
    this->BLstepPin = BLstepPin;
    this->FRdirPin = FRdirPin;
    this->FRstepPin = FRstepPin;
    this->FLdirPin = FLdirPin;
    this->FLstepPin = FLstepPin;
    this->motorInterfaceType = motorInterfaceType;
    this->maxSpeed = maxSpeed;
    this->stopSpeed = stopSpeed;
    // Initialize the pins on the Arduino
    initialize();
}

void DriveTrain::initialize() {
    // Define motors
    this->Front_Left = AccelStepper(motorInterfaceType, FLstepPin, FLdirPin);
    this->Front_Right = AccelStepper(motorInterfaceType, FRstepPin, FRdirPin);
    this->Back_Left = AccelStepper(motorInterfaceType, BLstepPin, BLdirPin);
    this->Back_Right = AccelStepper(motorInterfaceType, BRstepPin, BRdirPin);
}

void DriveTrain::forward(){
  Front_Left.setSpeed(maxSpeed);
  Front_Right.setSpeed(-maxSpeed);
  Back_Left.setSpeed(maxSpeed);
  Back_Right.setSpeed(-maxSpeed);
  // Step the motor with a constant speed as set by setSpeed():
  Front_Left.runSpeed();
  Front_Right.runSpeed();
  Back_Left.runSpeed();
  Back_Right.runSpeed();


}


void DriveTrain::Go_Right(){
  Front_Left.setSpeed(maxSpeed);
  Front_Right.setSpeed(maxSpeed);
  Back_Left.setSpeed(-maxSpeed);
  Back_Right.setSpeed(-maxSpeed);
  // Step the motor with a constant speed as set by setSpeed():
  Front_Left.runSpeed();
  Front_Right.runSpeed();
  Back_Left.runSpeed();
  Back_Right.runSpeed();
}

void DriveTrain::Diag_FRight(){
  Front_Left.setSpeed(maxSpeed);
  Front_Right.setSpeed(stopSpeed);
  Back_Left.setSpeed(stopSpeed);
  Back_Right.setSpeed(-maxSpeed);
  // Step the motor with a constant speed as set by setSpeed():
  Front_Left.runSpeed();
  Front_Right.runSpeed();
  Back_Left.runSpeed();
  Back_Right.runSpeed();
}

void DriveTrain::Diag_FLeft(){
  Front_Left.setSpeed(stopSpeed);
  Front_Right.setSpeed(-maxSpeed);
  Back_Left.setSpeed(maxSpeed);
  Back_Right.setSpeed(stopSpeed);
  // Step the motor with a constant speed as set by setSpeed():
  Front_Left.runSpeed();
  Front_Right.runSpeed();
  Back_Left.runSpeed();
  Back_Right.runSpeed();
}


void DriveTrain::Diag_BLeft(){
  Front_Left.setSpeed(-maxSpeed);
  Front_Right.setSpeed(stopSpeed);
  Back_Left.setSpeed(stopSpeed);
  Back_Right.setSpeed(maxSpeed);
  // Step the motor with a constant speed as set by setSpeed():
  Front_Left.runSpeed();
  Front_Right.runSpeed();
  Back_Left.runSpeed();
  Back_Right.runSpeed();
}

void DriveTrain::Diag_BRight(){
  Front_Left.setSpeed(stopSpeed);
  Front_Right.setSpeed(maxSpeed);
  Back_Left.setSpeed(-maxSpeed);
  Back_Right.setSpeed(stopSpeed);
  // Step the motor with a constant speed as set by setSpeed():
  Front_Left.runSpeed();
  Front_Right.runSpeed();
  Back_Left.runSpeed();
  Back_Right.runSpeed();
}

void DriveTrain::Go_Left(){
  Front_Left.setSpeed(-maxSpeed);
  Front_Right.setSpeed(-maxSpeed);
  Back_Left.setSpeed(maxSpeed);
  Back_Right.setSpeed(maxSpeed);
  // Step the motor with a constant speed as set by setSpeed():
  Front_Left.runSpeed();
  Front_Right.runSpeed();
  Back_Left.runSpeed();
  Back_Right.runSpeed();
}

void DriveTrain::Go_FLeft(){
Front_Left.setSpeed(maxSpeed);
Front_Left.runSpeed();
}

void DriveTrain::Go_FLeftB(){
Front_Left.setSpeed(-maxSpeed);
Front_Left.runSpeed();
}

