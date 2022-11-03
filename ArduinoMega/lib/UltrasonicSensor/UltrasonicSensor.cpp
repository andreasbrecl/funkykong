// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 11/02/2020
//
// This class will determine the sensor read outs for the ultrasonic
// sensors on the system. It will then output these to the main
// script.

#include <Arduino.h>
#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int sonicTrigPin1, int sonicTrigPin2, int sonicTrigPin3, int sonicTrigPin4, int sonicTrigPin5, int sonicEchoPin1, int sonicEchoPin2, int sonicEchoPin3, int sonicEchoPin4, int sonicEchoPin5) {
    /*
    This function will define the objects created in the ultrasonic
    sensor class. It will take in inputs from the pins to sense
    distance.

    Input:  sonicTrigPin1 <int> - Pin for ultrasonic sensor 1 trigger
            sonicTrigPin2 <int> - Pin for ultrasonic sensor 2 trigger
            sonicTrigPin3 <int> - Pin for ultrasonic sensor 3 trigger
            sonicTrigPin4 <int> - Pin for ultrasonic sensor 4 trigger
            sonicTrigPin5 <int> - Pin for ultrasonic sensor 5 trigger
            sonicEchoPin1 <int> - Pin for ultrasonic sensor 1 echo
            sonicEchoPin2 <int> - Pin for ultrasonic sensor 2 echo
            sonicEchoPin3 <int> - Pin for ultrasonic sensor 3 echo
            sonicEchoPin4 <int> - Pin for ultrasonic sensor 4 echo
            sonicEchoPin5 <int> - Pin for ultrasonic sensor 5 echo
    
    Output: None
    */
    // Define variables as internal and private to the class using pointers
    this->sonicTrigPin1 = sonicTrigPin1;
    this->sonicTrigPin2 = sonicTrigPin2;
    this->sonicTrigPin3 = sonicTrigPin3;
    this->sonicTrigPin4 = sonicTrigPin4;
    this->sonicTrigPin5 = sonicTrigPin5;
    this->sonicEchoPin1 = sonicEchoPin1;
    this->sonicEchoPin2 = sonicEchoPin2;
    this->sonicEchoPin3 = sonicEchoPin3;
    this->sonicEchoPin4 = sonicEchoPin4;
    this->sonicEchoPin5 = sonicEchoPin5;

    // Initialize the pins on the arduino
    initialize();
}

float* UltrasonicSensor::distanceCalculations() {
    /*
    This functino will calculate the distance that each sensor
    calculates.

    Input:  None

    Output: distanceVector <float><array> - This is a array of distance values found by sensors
    */

    // Clear the trig pin conditions
    digitalWrite(sonicTrigPin1, LOW);
    digitalWrite(sonicTrigPin2, LOW);
    digitalWrite(sonicTrigPin3, LOW);
    digitalWrite(sonicTrigPin4, LOW);
    digitalWrite(sonicTrigPin5, LOW);

    // Delay for 2 microseconds
    delayMicroseconds(clearDelay);

    // Set trigger pin to high
    digitalWrite(sonicTrigPin1, HIGH);
    digitalWrite(sonicTrigPin2, HIGH);
    digitalWrite(sonicTrigPin3, HIGH);
    digitalWrite(sonicTrigPin4, HIGH);
    digitalWrite(sonicTrigPin5, HIGH);

    // Delay for 10 microseconds
    delayMicroseconds(senseDelay);

    // Set pins to low
    digitalWrite(sonicTrigPin1, LOW);
    digitalWrite(sonicTrigPin2, LOW);
    digitalWrite(sonicTrigPin3, LOW);
    digitalWrite(sonicTrigPin4, LOW);
    digitalWrite(sonicTrigPin5, LOW);

    // Sense via the echo pins
    duration1 = pulseIn(sonicEchoPin1, HIGH);
    duration2 = pulseIn(sonicEchoPin2, HIGH);
    duration3 = pulseIn(sonicEchoPin3, HIGH);
    duration4 = pulseIn(sonicEchoPin4, HIGH);
    duration5 = pulseIn(sonicEchoPin5, HIGH);

    // Calculate the distance found in centimeters
    distance1 = duration1*halfSpeedOfSound;
    distance2 = duration2*halfSpeedOfSound;
    distance3 = duration3*halfSpeedOfSound;
    distance4 = duration4*halfSpeedOfSound;
    distance5 = duration5*halfSpeedOfSound;

    // Create distance vector
    distanceVector[0] = distance1;
    distanceVector[1] = distance2;
    distanceVector[2] = distance3;
    distanceVector[3] = distance4;
    distanceVector[4] = distance5;

    // Return the array of values
    return distanceVector;
}

void UltrasonicSensor::initialize() {
    /*
    This function will initalize the pins needed for the ultrasonic
    sensors

    Input: None
    
    Output: None
    */

    // Define output pins
    pinMode(sonicTrigPin1, OUTPUT);
    pinMode(sonicTrigPin2, OUTPUT);
    pinMode(sonicTrigPin3, OUTPUT);
    pinMode(sonicTrigPin4, OUTPUT);
    pinMode(sonicTrigPin5, OUTPUT);

    // Define input pins
    pinMode(sonicEchoPin1, INPUT);
    pinMode(sonicEchoPin2, INPUT);
    pinMode(sonicEchoPin3, INPUT);
    pinMode(sonicEchoPin4, INPUT);
    pinMode(sonicEchoPin5, INPUT);
}

