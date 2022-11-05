// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 11/02/2022
//
// This sets up the Ultrasonic sensor class header file.

#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

class UltrasonicSensor {
    /*
    This call will deal with collecting the data from the
    5 ultrasonic sensors on the system.
    */

    // Define public values
    public:

        // Define objects in class
        UltrasonicSensor(int, int);

        // Define output int variables
        float distance;

        // Predefine float vector
        float distanceValue;

        // Define functions
        float distanceCalculations();

    // Define private values
    private:

        // Define pin int private variables
        int sonicTrigPin;
        int sonicEchoPin;

        // Define duration long private variables
        long duration;

        // Delay timings
        int clearDelay = 2;
        int senseDelay = 10;

        // Speed of sound
        const float halfSpeedOfSound = 0.034 / 2;

        // Define private functions in class
        void initialize();
    
};

#endif