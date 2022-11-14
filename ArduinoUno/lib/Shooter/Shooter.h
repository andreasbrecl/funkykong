// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 10/19/2020
//
// This sets up the Shooter class header file.

#include "Servo.h"

class Shooter {
    /*
    This class will deal with firing the shooter and the logic for when
    it must either reload or start/stop firing projectiles.
    */

    // Define public values
    public:

        // Define Servo object
        Servo servo1;

        // Define general values for shooter on and off
        #define ON true
        #define OFF false

        // Define int public variables
        int timesFired;

        // Define objects in class
        Shooter(int, int, int, int, int, int, int);

        // Define functions in class
        int shoot(int);
        void initialize();

    // Define private values
    private:

        // Define int private variables
        int fireLogicPin;
        int servoPin;
        int reloadLogicPin;
        int fireTimeDelay;
        int servoLoadPosition;
        int servoFirePosition;
        int triggerRelayPin;
        
        // Define bool private variables
        bool shouldFire;
        bool shouldReload;

        // Define private functions in class
        void returnToReloadSignal();

};