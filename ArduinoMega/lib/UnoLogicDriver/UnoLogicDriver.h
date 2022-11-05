// Author: Andreas Brecl
// MCEN 5115 Mario Kart Balloon Battle
// 10/24/2022
//
// This sets up the Arduino Uno shooting logic class header file.

#ifndef UNOLOGICDRIVER_H
#define UNOLOGICDRIVER_H

class UnoLogicDriver {
    /*
    This class will determine the communication logic for sending shooting
    information to the Arduino Uno.
    */

   // Define public values
   public:

        // Define general values for shooter on and off
        #define ON HIGH
        #define OFF LOW

        // Define objects in class
        UnoLogicDriver(int);

        // Define public functions in class
        void shouldFireLogic(bool);

    // Define private values
    private:

        // Define int private variables
        int fireLogicPin;
        
        // Define boolian private vars
        bool shouldFire;

        // Define private functions in class
        void initialize();
    
};

#endif