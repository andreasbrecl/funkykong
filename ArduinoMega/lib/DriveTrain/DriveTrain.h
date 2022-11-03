#include <Arduino.h>
#include "AccelStepper.h"
#include "MultiStepper.h"

class DriveTrain {
    /*
    This class will deal with firing the shooter and the logic for when
    it must either reload or start/stop firing projectiles.
    */

    // Define public values
    public:

        

        // Define objects in class
        DriveTrain(int, int, int, int, int, int,  int, int, int);

        void forward();
        void Go_Right();
        void Diag_FRight();
        void Diag_FLeft();
        void Diag_BLeft();
        void Diag_BRight();
        void Go_Left();
        void Go_FLeft();
        void Go_FLeftB();


        AccelStepper Front_Left;
        AccelStepper Front_Right ;
        AccelStepper Back_Left;
        AccelStepper Back_Right; 
    // Define private values
    private:

        // Define Servo object
        //Servo servo;
        

        // Define int private variables
        int BRdirPin;
        int BRstepPin;
        int BLdirPin;
        int BLstepPin;
        int FRdirPin;
        int FRstepPin;
        int FLdirPin;
        int FLstepPin;
        int motorInterfaceType;
    
        

        void initialize();

    
};