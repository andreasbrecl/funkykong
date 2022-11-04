// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 11/04/2022
//
// This sets up the serial comms sensor class header file.

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
        void sendSerial();
        String recieveSerial();

        // Define public string vars
        String inputCommand;

    // Define private values
    private:

        // Define private funcitons
        void initalize();

        // Define string
        String sendCommand;
};
