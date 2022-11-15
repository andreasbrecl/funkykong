// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 10/19/2020
//
// This script will control the firing of the shooter.
// It will take an input from the arudino mega and then
// using this input, either start firing or not fire the
// shooter on the robot.

#include <Arduino.h>
#include "Shooter.h"
#include "Servo.h"

Shooter::Shooter(int fireLogicPin, int servoPin, int reloadLogicPin, int fireTimeDelay, int servoLoadPosition, int servoFirePosition, int triggerRelayPin) {
    /*
    This function will define objects created in the shooter class. It will take
    in the desired inputs to set up the pin values, time delays, and inital servo
    positions.

    Input:  fireLogicPin <int> - Pin that will read from the other arduino it should fire.
            servoPin <int> - Pin that will output servo postition.
            reloadLogicPin <int> - Pin that will send output if reload must occur.
            fireTimeDelay <int> - This delay accounts for the 3 seconds delay between shooting.
            servoLoadPosition <int> - Servo position for loading.
            servoFirePosition <int> - Servo position for firing.

    Output: None
    */
    
    // Define variables as internal and private to the class using pointers
    this->fireLogicPin = fireLogicPin;
    this->servoPin = servoPin;
    this->reloadLogicPin = reloadLogicPin;
    this->fireTimeDelay = fireTimeDelay;
    this->servoLoadPosition = servoLoadPosition;
    this->servoFirePosition = servoFirePosition;
    this->triggerRelayPin = triggerRelayPin;

    // Define Servo
    this->servo1 = Servo();
    
    // Initialize the pins on the Arduino
    initialize();
}

int Shooter::shoot(int timesFired) {
    /*
    This function moves the servo based on the logic of if it should fire or not.
    It looks at the input from the other arduino and then counts the number of times
    that it has been fired. If it has been fired all 12 times, it runs another 
    function to send out a signal for return to reload area.
    
    Input:  timesFired <int> - Tracks number of shots taken.

    Output: timesFired <int> - Tracks number of shots taken.
    */

    // Define variables as internal and private to the class using pointers
    this->timesFired = timesFired;
    
    // Check if should fire command recieved
    shouldFire = digitalRead(fireLogicPin);
    if (1 == 1) {
        // Turn on shooter
        digitalWrite(triggerRelayPin, HIGH);

        // Set servo in load position
        servo1.write(servoLoadPosition);

        // Delay for 1.5 seconds
        delay(fireTimeDelay);

        // Set servo in fire position
        servo1.write(servoFirePosition);

        // Delay for 1.5 seconds
        delay(fireTimeDelay);
        
        // Increment times fired logic
        ++timesFired;
    } else {
        // Turn on shooter
        digitalWrite(triggerRelayPin, LOW);
    }

    // Check if all rounds are fired
    if (timesFired >= 12) {

        // Turn on shooter
        digitalWrite(triggerRelayPin, LOW);

        // Send signal to other arduino
        returnToReloadSignal();

        // Reset counter
        timesFired = 0;
    }

    return timesFired;
}

void Shooter::returnToReloadSignal() {
    /*
    This function sends an output to the other arudino instructing it that it is time
    to return to base so that it can be reloaded with more ammunition.

    Input: None

    Output: None
    */
    
    // Send boolian value output to other arudino 
    digitalWrite(reloadLogicPin, HIGH);

    // Delay for sometime so other arduino can recieve signal
    delay(fireTimeDelay);

    // Set value to low
    digitalWrite(reloadLogicPin, LOW);
}

void Shooter::initialize() {
    /*
    This function will initallize the shooter functionalatity of the arduino uno.
    It will set the pins to either inputs or outputs. Along with this it will set
    the initial position of the servo.

    Input: None
    
    Output: None
    */

    // Define pin out/in values
    pinMode(reloadLogicPin, OUTPUT);
    pinMode(fireLogicPin, INPUT);
    pinMode(triggerRelayPin, OUTPUT);

    // Set initial output as low
    digitalWrite(reloadLogicPin, LOW);
    digitalWrite(triggerRelayPin, LOW);

    // Set initial servo position
    servo1.attach(servoPin);
    servo1.write(servoFirePosition);
}