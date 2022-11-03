// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 10/25/2020
//
// This sets up the IMU sensor class header file.

#include "SparkFunLSM6DSO.h"
#include "Wire.h"

class IMUSensor {
    /*
    This class will determine the readings on the IMU sensor.
    */

    // Define public values
    public:

        // Define objects in class
        IMUSensor();

    // Define private values
    private:

        // Define private functions in class
        void initialize();

        // Define private objects
        LSM6DSO myIMU;

        // Define int private variables

    
};