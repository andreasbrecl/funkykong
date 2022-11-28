// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 11/03/2022
//
// This class determines the inputs for the lines sensors on
// the system. This helps determine if the system is going to
// go out of bounds.

#include <Arduino.h>
#include "LineSensor.h"

LineSensor::LineSensor(int lineAnalogPin, int lineDigitalPin) {
    /*
    This function will initalize the object for the line sensors.

    Input:  lineAnalogPin <int> - Analog pin for line sensor
            lineDigitalPin <int> - Digital pin for line sensor
    
    Output: None
    */
    // Define variables as internal and private to the class using pointers
    this->lineAnalogPin = lineAnalogPin;
    this->lineDigitalPin = lineDigitalPin;

    // Initialize the pins on the arduino
    initialize();
}

bool LineSensor::lineSensorOutputs() {
    /*
    This function will determine if the line sensor is reading
    a 1 or 0 for if it is over the line.

    Input:  None

    Output: lineSensorVector <float><array> - This is a array of line values found by sensors
    */
    // Create vector of values
    lineSensorValue = 1 - digitalRead(lineDigitalPin);

    // Return vector of values
    return lineSensorValue;
}

void LineSensor::initialize() {
    /*
    Initalize the pinsouts for the line sensors.

    Input:  None
    
    Output: None
    */
    
    // Set input pins
    pinMode(lineAnalogPin, INPUT);
    pinMode(lineDigitalPin, INPUT);
}

