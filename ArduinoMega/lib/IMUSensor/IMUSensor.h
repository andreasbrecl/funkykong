// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 10/25/2020
//
// This sets up the IMU sensor class header file.

class IMUSensor {
    /*
    This class will determine the readings on the IMU sensor.
    */

    // Define public values
    public:

        // Define objects in class
        IMUSensor(int, int, int, int);

    // Define private values
    private:

        // Define private functions in class
        void initialize();

        // Define int private variables
        int SCAPin;
        int SCLPin;
        int SDOPin;
        int CSPin;
    
};