// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 10/19/2020
//
// This script will control the firing of the shooter.
// It will take an input from the arudino mega and then
// using this input, either start firing or not fire the
// shooter on the robot.

#include <Arduino.h>
#include "Shooter.h"
#include "Servo.h"

Shooter::Shooter(int fireLogicPin, int servoPin, int reloadLogicPin, int fireTimeDelay, int servoLoadPosition, int servoFirePosition) {
    
    // Define variables as internal and private to the class using pointers
    this->fireLogicPin = fireLogicPin;
    this->servoPin = servoPin;
    this->reloadLogicPin = reloadLogicPin;
    this->fireTimeDelay = fireTimeDelay;
    this->servoLoadPosition = servoLoadPosition;
    this->servoFirePosition = servoFirePosition;
    
    // Initialize the pins on the Arduino
    initialize();
}

void Shooter::shoot() {
    return;
}

void Shooter::initialize() {
    // Define pin out/in values
    pinMode(reloadLogicPin, OUTPUT);
    pinMode(servoPin, OUTPUT);
    pinMode(fireLogicPin, INPUT);
}