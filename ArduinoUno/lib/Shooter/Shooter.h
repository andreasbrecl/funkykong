// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 10/19/2020
//
// This sets up the Shooter class header file.

#include "Servo.h"

class Shooter{
    /*
    This class will deal with firing the shooter and the logic for when
    it must either reload or start/stop firing projectiles.
    */

    // Define public values
    public:

    // Define general values for shooter on and off
    #define ON true
    #define OFF false

    // Define int public variables
    int timesFired;

    // Define functions in class
    Shooter(int, int, int, int, int, int);
    int shoot(int);

    // Define private values
    private:

    // Define Servo object
    Servo servo;

    // Define int private variables
    int fireLogicPin;
    int servoPin;
    int reloadLogicPin;
    int fireTimeDelay;
    int servoLoadPosition;
    int servoFirePosition;
    
    // Define bool private variables
    bool shouldFire;
    bool shouldReload;

    // Define private functions in class
    void initialize();
    void returnToReloadSignal();

};