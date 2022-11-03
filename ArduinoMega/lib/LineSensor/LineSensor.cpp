// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 11/03/2022
//
// This class determines the inputs for the lines sensors on
// the system. This helps determine if the system is going to
// go out of bounds.

#include <Arduino.h>
#include "LineSensor.h"

LineSensor::LineSensor(int lineAnalogPin1, int lineAnalogPin2, int lineAnalogPin3, int lineAnalogPin4, int lineDigitalPin1, int lineDigitalPin2, int lineDigitalPin3, int lineDigitalPin4) {
    /*
    This function will initalize the object for the line sensors.

    Input:  lineAnalogPin1 <int> - Analog pin for line sensor
            lineAnalogPin2 <int> - Analog pin for line sensor
            lineAnalogPin3 <int> - Analog pin for line sensor
            lineAnalogPin4 <int> - Analog pin for line sensor
            lineDigitalPin1 <int> - Digital pin for line sensor
            lineDigitalPin2 <int> - Digital pin for line sensor
            lineDigitalPin3 <int> - Digital pin for line sensor
            lineDigitalPin4 <int> - Digital pin for line sensor
    
    Output: None
    */
    // Define variables as internal and private to the class using pointers
    this->lineAnalogPin1 = lineAnalogPin1;
    this->lineAnalogPin2 = lineAnalogPin2;
    this->lineAnalogPin3 = lineAnalogPin3;
    this->lineAnalogPin4 = lineAnalogPin4;
    this->lineDigitalPin1 = lineDigitalPin1;
    this->lineDigitalPin2 = lineDigitalPin2;
    this->lineDigitalPin3 = lineDigitalPin3;
    this->lineDigitalPin4 = lineDigitalPin4;

    // Initialize the pins on the arduino
    initialize();
}

bool* LineSensor::lineSensorOutputs() {
    /*
    This function will determine if the line sensor is reading
    a 1 or 0 for if it is over the line.

    Input:  None

    Output: lineSensorVector <float><array> - This is a array of line values found by sensors
    */
    // Create vector of values
    lineSensorVector[0] = digitalRead(lineDigitalPin1);
    lineSensorVector[1] = digitalRead(lineDigitalPin2);
    lineSensorVector[2] = digitalRead(lineDigitalPin3);
    lineSensorVector[3] = digitalRead(lineDigitalPin4);

    // Return vector of values
    return lineSensorVector;
}

void LineSensor::initialize() {
    /*
    Initalize the pinsouts for the line sensors.

    Input:  None
    
    Output: None
    */
    
    // Set input pins
    pinMode(lineAnalogPin1, INPUT);
    pinMode(lineAnalogPin2, INPUT);
    pinMode(lineAnalogPin3, INPUT);
    pinMode(lineAnalogPin4, INPUT);
    pinMode(lineDigitalPin1, INPUT);
    pinMode(lineDigitalPin2, INPUT);
    pinMode(lineDigitalPin3, INPUT);
    pinMode(lineDigitalPin4, INPUT);
}

