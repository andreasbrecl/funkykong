// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 11/02/2022
//
// This class will determine the sensor read outs for the ultrasonic
// sensors on the system. It will then output these to the main
// script.

#include <Arduino.h>
#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int sonicTrigPin, int sonicEchoPin) {
    /*
    This function will define the objects created in the ultrasonic
    sensor class. It will take in inputs from the pins to sense
    distance.

    Input:  sonicTrigPin <int> - Pin for ultrasonic sensor 1 trigger
            sonicEchoPin <int> - Pin for ultrasonic sensor 1 echo
    
    Output: None
    */
    // Define variables as internal and private to the class using pointers
    this->sonicTrigPin = sonicTrigPin;
    this->sonicEchoPin = sonicEchoPin;

    // Initialize the pins on the arduino
    initialize();
}

float UltrasonicSensor::distanceCalculations() {
    /*
    This functino will calculate the distance that each sensor
    calculates.

    Input:  None

    Output: distanceVector <float><array> - This is a array of distance values found by sensors
    */

    // Clear the trig pin conditions
    digitalWrite(sonicTrigPin, LOW);

    // Delay for 2 microseconds
    delayMicroseconds(clearDelay);

    // Set trigger pin to high
    digitalWrite(sonicTrigPin, HIGH);

    // Delay for 10 microseconds
    delayMicroseconds(senseDelay);

    // Set pins to low
    digitalWrite(sonicTrigPin, LOW);

    // Sense via the echo pins
    duration = pulseIn(sonicEchoPin, HIGH, timeout);

    // Calculate the distance found in centimeters
    distance = duration*halfSpeedOfSound;

    if ( duration == 0 ) {
        // Create distance vector
        distanceValue = 50;

    } else {
        // Create distance vector
        distanceValue = distance;
    }

    // Return the array of values
    return distanceValue;
}

void UltrasonicSensor::initialize() {
    /*
    This function will initalize the pins needed for the ultrasonic
    sensors

    Input: None
    
    Output: None
    */

    // Define output pins
    pinMode(sonicTrigPin, OUTPUT);

    // Define input pins
    pinMode(sonicEchoPin, INPUT);
}

