// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 11/04/2022
//
// This class will determine the sensor read outs for the ultrasonic
// sensors on the system. It will then output these to the main
// script.

#include <Arduino.h>
#include "SerialComms.h"

SerialComms::SerialComms() {
    /*
    This function is the constructor for the object for serial 
    communications. It will take in the UART communication information
    for the system to operate.

    Input:  None

    Output: None
    */

    // Initalize items
    initalize();
}

void SerialComms::sendSerial(float distanceValue1, float distanceValue2, float distanceValue3, float distanceValue4, float distanceValue5, bool lineSensorValue1, bool lineSensorValue2, bool lineSensorValue3, bool lineSensorValue4, double IMUReadings) {
    /*
    This function will send UART serial comms to the raspberry pi.

    Input:  None

    Output: None
    */
    
    // Print serial data
    Serial.print("<ls!");
    Serial.print(lineSensorValue1);
    Serial.print(",ls@");
    Serial.print(lineSensorValue2);
    Serial.print(",ls#");
    Serial.print(lineSensorValue3);
    Serial.print(",ls$");
    Serial.print(lineSensorValue4);
    Serial.print(",us!");
    Serial.print(distanceValue1,1);
    Serial.print(",us@");
    Serial.print(distanceValue2,1);
    Serial.print(",us#");
    Serial.print(distanceValue3,1);
    Serial.print(",us$");
    Serial.print(distanceValue4,1);
    Serial.print(",us%");
    Serial.print(distanceValue5,1);
    Serial.print(",imu!");
    Serial.print(IMUReadings,1);
    Serial.println(">");
}

String SerialComms::recieveSerial() {
    /*
    This function will send UART serial comms to the raspberry pi.

    Input:  None

    Output: None
    */
    // See if string data is avaliable
    if (Serial.available() > 0) {

        // Pull data
        inputCommand = Serial.readStringUntil('\n');
    }

    return inputCommand;
}

void SerialComms::initalize() {
    /*
    This function initalizes the serial comms.

    Input:  None

    Output: None
    */
}