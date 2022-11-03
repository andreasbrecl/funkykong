// Author: Andreas Brecl 
// MCEN 5115 Mario Kart Balloon Battle
// 11/03/2022
//
// This sets up the Line sensor class header file.

class LineSensor {
    /*
    This class will determine the boolean readings of the line
    sensor to see if it is over a white tape line or not.
    */

    // Define public values
    public:

        // Define objects in class
        LineSensor(int,int,int,int,int,int,int,int);

        // Define line sensor output variables
        bool lineSensorReading1;
        bool lineSensorReading2;
        bool lineSensorReading3;
        bool lineSensorReading4;

        // Create line sensor reading array
        static bool lineSensorVector[4];

        // Define functions
        bool* lineSensorOutputs();


    // Define private values
    private:

        // Define private int vars in class
        int lineAnalogPin1;
        int lineAnalogPin2;
        int lineAnalogPin3;
        int lineAnalogPin4;
        int lineDigitalPin1;
        int lineDigitalPin2;
        int lineDigitalPin3;
        int lineDigitalPin4;

        // Define private functions in class
        void initialize();
    
};