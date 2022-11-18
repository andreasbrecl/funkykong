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
    This function initalizes the IMU object.

    Input: None
    
    Output: None
    */
}

double IMUSensor::calculateAngle(double angle, double time1) {
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

    Serial.println(gyroX);
    Serial.println(accelX);

    // Calculate time 2
    time2 = millis();

    // Calculate dt
    dt = time2 - time1;

    // Calculate alpha
    alpha = (tau)/(tau + dt);

    // Calculate angle
    angle = (1 - alpha)*(angle + gyroX * dt)+(alpha)*(accelX);

    // Define array
    IMUReadings = angle;

    // Return data
    return IMUReadings;
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
    
    // Define objects
    LSM6DSO myIMU1;
    myIMU = myIMU1;

    // Initalize I2C
    Wire.begin();
    Serial.print("123");
}

