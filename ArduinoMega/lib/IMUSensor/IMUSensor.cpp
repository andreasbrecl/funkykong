// Author: 
// MCEN 5115 Mario Kart Balloon Battle
// XX/XX/2020
//
// ENTER DESCRIPTION ABOUT WHAT THIS FILE DOES.....

#include <Arduino.h>
#include "IMUSensor.h"
#include "SparkFunLSM6DSO.h"
#include "Wire.h"

IMUSensor::IMUSensor() {
    /*
    <Enter description>

    Input: None
    
    Output: None
    */

    // Define variables as internal and private to the class using pointers


    // Define variables as internal and private to the class using pointers


    // Initialize the pins on the arduino
    initialize();
}



void IMUSensor::initialize() {
    /*
    <Enter description>

    Input: None
    
    Output: None
    */
    
    // Initalize I2C
    Wire.begin();
}

