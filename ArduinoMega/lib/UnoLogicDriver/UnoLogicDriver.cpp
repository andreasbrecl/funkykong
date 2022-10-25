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


    // Define variables as internal and private to the class using pointers
    this->fireLogicPin = fireLogicPin;
    this->reloadLogicPin = reloadLogicPin;

    // Initialize the pins on the arduino
    initialize();
}

void UnoLogicDriver::shouldFireLogic(bool shouldFire) {
    this->shouldFire = shouldFire;

}

void UnoLogicDriver::initialize() {

    // Define pins out/in values
    pinMode(fireLogicPin, OUTPUT);

    // Set output as low
    digitalWrite(fireLogicPin, OFF);
}

// <LS:123,234,456,234!>