// Author: 
// MCEN 5115 Mario Kart Balloon Battle
// XX/XX/2020
//
// ENTER DESCRIPTION ABOUT WHAT THIS FILE DOES.....

#include <Arduino.h>
#include "IMUSensor.h"

IMUSensor::IMUSensor(int SCAPin, int SCLPin, int SDOPin, int CSPin) {
    /*
    <Enter description>

    Input: None
    
    Output: None
    */

    // Define variables as internal and private to the class using pointers
    this->SCAPin = SCAPin;
    this->SCLPin = SCLPin;
    this->SDOPin = SDOPin;
    this->CSPin = CSPin;

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


}

