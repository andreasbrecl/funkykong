// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 10/19/2020
//
// 

#include "Servo.h"

class Shooter{

    // Define public values
    public:

    // Define general values for shooter on and off
    // #define ON true
    // #define OFF false

    // Define functions in class
    Shooter(int, int, int, int, int, int);
    void shoot();

    // Define private values
    private:

    // Define private functions in class
    void initialize();

    // Define private variables
    int fireLogicPin;
    int servoPin;
    int reloadLogicPin;
    int fireTimeDelay;
    int servoLoadPosition;
    int servoFirePosition;

};