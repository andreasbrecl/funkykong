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

    // Define Maximum speed, we wont ever go this high but it is necessary for the motors to move
  Front_Left.setMaxSpeed(1500);
  Front_Right.setMaxSpeed(1000);
  Back_Left.setMaxSpeed(1000);
  Back_Right.setMaxSpeed(1000);
}

void DriveTrain::processCommand(String driveMode){

  //This function processes the commands received from the python to move the robot.
  // Currently the commands are set up as full strings so that they are easy to interpret for the humans
  // They can be adjusted to single characters if necessary
        if(driveMode == "forward"){
          Serial.println("Going Forward");
          forward();
          
        }
        else if(driveMode == "backward"){
          backward();
          Serial.println("Going backward");
        }
        else if(driveMode == "left"){
          Go_Left();
          Serial.println("Going Left");
        }
        else if(driveMode == "right"){
          Go_Right();
          Serial.println("Going Right");
        }
        if(driveMode == "fleft"){
          Diag_FLeft();
          Serial.println("Going Diagonal Forwards Left");
        }
        else if(driveMode == "bleft"){
          Diag_BLeft();
          Serial.println("Going Diagonal Backwards Left");
        }
        else if(driveMode == "fright"){
          Diag_FRight();
          Serial.println("Going Diagonal Forwards Right");
        }
        else if(driveMode == "bright"){
          Diag_BRight();
          Serial.println("Going Diagonal Backwards Right");
        }
        else if(driveMode == "ccw"){
          CounterClockwise();
          Serial.println("Going Counter Clockwise");
        }
        else if (driveMode == "cw"){
          Clockwise();
          Serial.println("Going Clockwise");
        }
        else if(driveMode == "Shtop"){
          Stop();
          Serial.println("Stopping! ");
          
        }
        /*
        else{
          // default to stop if there is no recogniable command, this can be adjusted to something else later
          Stop();
          Serial.println("Stopping! ");
          
        }
        */
}

void DriveTrain::forward(){

  //This function moves the robot forward at a set speed

  //Set the speed of the stepping of the motor. A negative can be added/removed to change the direction the motor is spinning.
  Front_Left.setSpeed(-maxSpeed);
  Front_Right.setSpeed(-maxSpeed);
  Back_Left.setSpeed(-maxSpeed);
  Back_Right.setSpeed(maxSpeed);
  // Step the motor with a constant speed as set by setSpeed():
  Front_Left.runSpeed();
  Front_Right.runSpeed();
  Back_Left.runSpeed();
  Back_Right.runSpeed();


}

void DriveTrain::backward(){

  //This function moves the robot backward at a set speed

  //Set the speed of the stepping of the motor. A negative can be added/removed to change the direction the motor is spinning.

  Front_Left.setSpeed(maxSpeed);
  Front_Right.setSpeed(maxSpeed);
  Back_Left.setSpeed(maxSpeed);
  Back_Right.setSpeed(-maxSpeed);
  // Step the motor with a constant speed as set by setSpeed():
  Front_Left.runSpeed();
  Front_Right.runSpeed();
  Back_Left.runSpeed();
  Back_Right.runSpeed();


}


void DriveTrain::Go_Right(){

  //This function moves the robot laterally to the right at a set speed

  //Set the speed of the stepping of the motor. A negative can be added/removed to change the direction the motor is spinning.

  Front_Left.setSpeed(-maxSpeed);
  Front_Right.setSpeed(maxSpeed);
  Back_Left.setSpeed(maxSpeed);
  Back_Right.setSpeed(maxSpeed);
  // Step the motor with a constant speed as set by setSpeed():
  Front_Left.runSpeed();
  Front_Right.runSpeed();
  Back_Left.runSpeed();
  Back_Right.runSpeed();
}

void DriveTrain::Diag_FRight(){

  //This function moves the robot forward and diagonally to the right at a set speed

  //Set the speed of the stepping of the motor. A negative can be added/removed to change the direction the motor is spinning.

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

void DriveTrain::Diag_FLeft(){

  //This function moves the robot forward and diagonally to the left at a set speed

  //Set the speed of the stepping of the motor. A negative can be added/removed to change the direction the motor is spinning.


  Front_Left.setSpeed(stopSpeed);
  Front_Right.setSpeed(-maxSpeed);
  Back_Left.setSpeed(-maxSpeed);
  Back_Right.setSpeed(stopSpeed);
  // Step the motor with a constant speed as set by setSpeed():
  Front_Left.runSpeed();
  Front_Right.runSpeed();
  Back_Left.runSpeed();
  Back_Right.runSpeed();
}


void DriveTrain::Diag_BLeft(){

  //This function moves the robot backward and diagonally to the left at a set speed

  //Set the speed of the stepping of the motor. A negative can be added/removed to change the direction the motor is spinning.

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

void DriveTrain::Diag_BRight(){
  //This function moves the robot backward and diagonally to the right at a set speed

  //Set the speed of the stepping of the motor. A negative can be added/removed to change the direction the motor is spinning.
  Front_Left.setSpeed(stopSpeed);
  Front_Right.setSpeed(maxSpeed);
  Back_Left.setSpeed(maxSpeed);
  Back_Right.setSpeed(stopSpeed);
  // Step the motor with a constant speed as set by setSpeed():
  Front_Left.runSpeed();
  Front_Right.runSpeed();
  Back_Left.runSpeed();
  Back_Right.runSpeed();
}

void DriveTrain::Go_Left(){
  //This function moves the robot laterally to the left at a set speed

  //Set the speed of the stepping of the motor. A negative can be added/removed to change the direction the motor is spinning.

  Front_Left.setSpeed(maxSpeed);
  Front_Right.setSpeed(-maxSpeed);
  Back_Left.setSpeed(-maxSpeed);
  Back_Right.setSpeed(-maxSpeed);
  // Step the motor with a constant speed as set by setSpeed():
  Front_Left.runSpeed();
  Front_Right.runSpeed();
  Back_Left.runSpeed();
  Back_Right.runSpeed();
}

void DriveTrain::CounterClockwise(){

  //This function rotates the robot clockwise

  //Set the speed of the stepping of the motor. A negative can be added/removed to change the direction the motor is spinning.

  Front_Left.setSpeed(-maxSpeed);
  Front_Right.setSpeed(maxSpeed);
  Back_Left.setSpeed(-maxSpeed);
  Back_Right.setSpeed(-maxSpeed);
  // Step the motor with a constant speed as set by setSpeed():
  Front_Left.runSpeed();
  Front_Right.runSpeed();
  Back_Left.runSpeed();
  Back_Right.runSpeed();


}

void DriveTrain::Clockwise(){

  //This function rotates the robot counterclockwise

  //Set the speed of the stepping of the motor. A negative can be added/removed to change the direction the motor is spinning.

  Front_Left.setSpeed(maxSpeed);
  Front_Right.setSpeed(-maxSpeed);
  Back_Left.setSpeed(maxSpeed);
  Back_Right.setSpeed(maxSpeed);
  // Step the motor with a constant speed as set by setSpeed():
  Front_Left.runSpeed();
  Front_Right.runSpeed();
  Back_Left.runSpeed();
  Back_Right.runSpeed();


}

void DriveTrain::Stop(){

  //This function stops the rotation of the motors

  //Set the speed of the stepping of the motor. A negative can be added/removed to change the direction the motor is spinning.

  Front_Left.setSpeed(stopSpeed);
  Front_Right.setSpeed(stopSpeed);
  Back_Left.setSpeed(stopSpeed);
  Back_Right.setSpeed(stopSpeed);
  // Step the motor with a constant speed as set by setSpeed():
  Front_Left.runSpeed();
  Front_Right.runSpeed();
  Back_Left.runSpeed();
  Back_Right.runSpeed();
}
void DriveTrain::Go_FLeft(){
//This function was for debugging only a single motor, going forwards

Front_Left.setSpeed(-maxSpeed);
Front_Left.runSpeed();
}

void DriveTrain::Go_FLeftB(){
//This function was for debugging only a single motor, going backwards  
Front_Left.setSpeed(maxSpeed);
Front_Left.runSpeed();
}

