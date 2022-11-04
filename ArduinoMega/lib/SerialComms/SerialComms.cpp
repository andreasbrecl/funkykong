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

void SerialComms::sendSerial() {
    /*
    This function will send UART serial comms to the raspberry pi.

    Input:  None

    Output: None
    */
    
    // Print serial data
    Serial.println(sendCommand);
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