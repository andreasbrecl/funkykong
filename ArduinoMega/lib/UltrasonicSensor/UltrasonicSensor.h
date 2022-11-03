// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 11/02/2020
//
// This sets up the Ultrasonic sensor class header file.

class UltrasonicSensor {
    /*
    This call will deal with collecting the data from the
    5 ultrasonic sensors on the system.
    */

    // Define public values
    public:

        // Define objects in class
        UltrasonicSensor(int, int, int, int, int, int, int, int, int, int);

        // Define output int variables
        int distance1;
        int distance2;
        int distance3;
        int distance4;
        int distance5;

        // Predefine float vector
        static float distanceVector[5];

        // Define functions
        float* distanceCalculations();

    // Define private values
    private:

        // Define pin int private variables
        int sonicTrigPin1;
        int sonicTrigPin2;
        int sonicTrigPin3;
        int sonicTrigPin4;
        int sonicTrigPin5;
        int sonicEchoPin1;
        int sonicEchoPin2;
        int sonicEchoPin3;
        int sonicEchoPin4;
        int sonicEchoPin5;

        // Define duration long private variables
        long duration1;
        long duration2;
        long duration3;
        long duration4;
        long duration5;

        // Delay timings
        int clearDelay = 2;
        int senseDelay = 10;

        // Speed of sound
        const float halfSpeedOfSound = 0.034 / 2;

        // Define private functions in class
        void initialize();
    
};