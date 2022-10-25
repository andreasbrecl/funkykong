// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 10/24/2020
//
// This script will control the firing logic of the Uno.
// This will take in the input needed from the arduino
// communicating if its in the correct position to shoot.
// Along with this, it will determine if the Uno needs to
// reload.

#include <Arduino.h>
#include "UnoLogicDriver.h"

UnoLogicDriver::UnoLogicDriver(int fireLogicPin) {
    /*
    This function creates the object for the Uno logic
    driver. It takes in the pin that will be triggered
    for the logic operations.

    Input:  fireLogicPin <int> - Pin that will output fire logic

    Output: None
    */
    // Define variables as internal and private to the class using pointers
    this->fireLogicPin = fireLogicPin;

    // Initialize the pins on the arduino
    initialize();
}

void UnoLogicDriver::shouldFireLogic(bool shouldFire) {
    /*
    This function deals with the firing logic for the Arduino
    Uno. It takes in an input to see if the weapon should fire,
    then triggers a pin to send a HIGH signal out.

    Input:  shouldFire <bool> - Sends a true or false for if weapon should fire

    Output: None    
    */

    // Use private variables instead of public
    this->shouldFire = shouldFire;

    // Check if weapon should fire
    if (shouldFire == 1) {

        // Turn on weapon to fire
        digitalWrite(fireLogicPin, ON);

    } else {
        
        // Turn off weapon 
        digitalWrite(fireLogicPin, OFF);
    }
}

void UnoLogicDriver::initialize() {
    /*
    This function will initallize the pins to send signals
    to the Uno. This will set the pin value to its inital state
    of low or OFF.

    Input: None
    
    Output: None
    */

    // Define pins out/in values
    pinMode(fireLogicPin, OUTPUT);

    // Set output as low
    digitalWrite(fireLogicPin, OFF);
}

// <LS:123,234,456,234!>