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

        // Define struct
        struct IMUOutputs {
            float angle;
            long int time2;
        };

        // Define struct object
        IMUOutputs currentIMU;

        // Define objects in class
        IMUSensor();

        // Define public functions in class
        IMUOutputs calculateAngle(float);

        // Define public float variables
        float angle;

        // Define public long int
        long int time1;
        long int time2;

    // Define private values
    private:

        // Define private functions in class
        void initialize();
        float readGyro();
        float readAccel();

        // Define private objects
        LSM6DSO myIMU;

        // Define float private variables
        float gyroX;
        float accelX;
        float alpha;
        float tau = 0.25;
        
        // Define long int private variables
        long int dt;
};