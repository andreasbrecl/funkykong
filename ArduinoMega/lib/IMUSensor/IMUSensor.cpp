// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 11/04/2022
//
// ENTER DESCRIPTION ABOUT WHAT THIS FILE DOES.....

#include <Arduino.h>
#include "IMUSensor.h"
#include "SparkFunLSM6DSO.h"
#include "Wire.h"

IMUSensor::IMUSensor() {
    /*
    <Enter description>

    Input: None
    
    Output: None
    */

    // Define variables as internal and private to the class using pointers


    // Define variables as internal and private to the class using pointers


    // Initialize the pins on the arduino
    initialize();
}

IMUSensor::IMUOutputs IMUSensor::calculateAngle(float angle) {
    /*
    This function calculates the current angle of the system.

    Input:  angle <float> - Angle system is at
            time1 <long int> - inital refernce time

    Output: angle <float> - Angle system is at
            time2 <long int> - final refernce time
    */
    // Pull data
    gyroX = readGyro();
    accelX = readAccel();

    // Calculate time 2
    time2 = millis();

    // Calculate dt
    dt = time2 - time1;

    // Calculate alpha
    time2 = millis();
    
    alpha = (tau)/(tau + dt);

    // Calculate angle
    angle = (1 - alpha)*(angle + gyroX * dt)+(alpha)*(accelX);

    // Define IMUOuputs
    currentIMU.angle = angle;
    currentIMU.time2 = time2;

    // Return data
    return currentIMU;
}

float IMUSensor::readGyro() {
    /*
    This function will read in the information for the gryo from
    the IMU on the system.

    Input:  None

    Output: gyroX <float> - Gyro reading in rad/s
    */
    gyroX = myIMU.readFloatGyroX();

    // Return info
    return gyroX;
}

float IMUSensor::readAccel() {
    /*
    This function will read in the information for the accel from
    the IMU on the system.

    Input:  None

    Output: accelX <float> - Accel reading in rad/s
    */
    accelX = myIMU.readFloatAccelX();

    // Return info
    return accelX;
}

void IMUSensor::initialize() {
    /*
    <Enter description>

    Input: None
    
    Output: None
    */
    
    // Initalize I2C
    Wire.begin();
}

