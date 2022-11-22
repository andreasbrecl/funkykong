// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 10/25/2020
//
// This sets up the IMU sensor class header file.

#include "SparkFunLSM6DSO.h"
#include "Wire.h"

#ifndef IMUSENSOR_H
#define IMUSENSOR_H

class IMUSensor {
    /*
    This class will determine the readings on the IMU sensor.
    */

    // Define public values
    public:

        // Define objects in class
        IMUSensor();

        // Define public functions in class
        double calculateAngle(double, double);
        void initialize();

        // Define public float variables
        float angle = 0;
        double angleNew = 0;

        // Define public long int
        double time1;
        double time2;

        // Define output array
        double IMUReadings;

    // Define private values
    private:

        // Define private objects
        LSM6DSO myIMU;

        // Define float private variables
        float gyroX;
        float accelX;
        float alpha;
        float tau = 1/1000;

        // Define long int private variables
        long int dt;

        // Define private functions in class
        float readGyro();
        float readAccel();
};

#endif