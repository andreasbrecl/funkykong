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
        LineSensor(int,int);

        // Create line sensor reading array
        bool lineSensorValue;

        // Define functions
        bool lineSensorOutputs();


    // Define private values
    private:

        // Define private int vars in class
        int lineAnalogPin;
        int lineDigitalPin;

        // Define private functions in class
        void initialize();
    
};