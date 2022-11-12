// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 11/04/2022
//
// This sets up the serial comms sensor class header file.

#ifndef SERIALCOMMS_H
#define SERIALCOMMS_H

class SerialComms {
    /*
    This class will deal with sending and recieving the
    UART comms between the arudino and the raspberry pi.
    */

    // Define public 
    public:

        // Define objects in class
        SerialComms();

        // Define public functions
        void sendSerial(float,float,float,float,float,bool,bool,bool,bool,double);
        String recieveSerial();

        // Define public vars
        float distanceValue1;
        float distanceValue2;
        float distanceValue3;
        float distanceValue4;
        float distanceValue5;
        bool lineSensorValue1;
        bool lineSensorValue2;
        bool lineSensorValue3;
        bool lineSensorValue4;
        double IMUReadings;

        // Define public string vars
        String inputCommand;

    // Define private values
    private:

        // Define private funcitons
        void initalize();
};

#endif