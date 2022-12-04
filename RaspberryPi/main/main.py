from __future__ import print_function
#!/usr/bin/env python3
"""
Author: Andrea Brecl,  Sean Newman
Date: 11/30/2022

This script will initalize the main functionality of the Raspberry
Pi software. The raspberry pi will be responsible for determining
the image recognition and processing the data inputs from the arduino.
It will take in the data, then determine the motion planning required
to put the system into the correct location.
"""

# Import classes
from lib.uart_comms import UARTComms
from lib.path_planning import PathPlanning
from lib.path_planning2 import PathPlanning2

# Import built in funcitons
import time
import sys
import signal

# Define global var
global globalExit
globalExit = "SeanToldMeToDoThis"

def executeFunctions():
    """
    This will execute the logic for what the system should be doing in
    its current state. Based on what it should be doing. It will then 
    determine the outputs it must send to the arduino for movement.

    Input:  None

    Output: None
    """
    # UART variables
    port = '/dev/ttyACM0'
    baudRate = 115200
    timeout = 1

    # Define GPIO pins asd
    firePin = 17
    reloadPin = 27
    reloadDonePin = 22
    startPin = 23
    stopPin = 24

    # Path planning variables, times are in seconds
    diagTimeToShooting = 11
    leftRightTimeToShooting = 5
    forwardTimeToShooting = 3.25
    rotate90Time = 3.9
    rotate45Time = rotate90Time / 2
    timeList = [diagTimeToShooting, leftRightTimeToShooting, forwardTimeToShooting, rotate90Time, rotate45Time]
    
    # Path planning distances in CM
    initializationDistance = 15
    shootingDistance = 30
    pathDistanceList = [initializationDistance, shootingDistance]

    # Initial movement criterias
    movementCommand = "A"
    systemMode = "Initialize"
    time1 = time.time()
    time2 = time.time()
    subMode = "Initialize"
    sideColor = "None"
    currentModeInformation = [systemMode, time1, time2, subMode, sideColor]

    # Create UART object
    UART = UARTComms(port, baudRate, timeout)
    path = PathPlanning(firePin, reloadPin, reloadDonePin, startPin, stopPin)
    path2 = PathPlanning2(firePin, reloadPin, reloadDonePin, startPin, stopPin)

    # Test variables
    currentModeInformation[0] = "GoToReload"
    currentModeInformation[3] = "MoveBack"
    currentModeInformation[4] = "Red"
    #currentModeInformation[0] = "GoToShoot"
    #currentModeInformation[3] = "RotateForward"
    #currentModeInformation[4] = "Red"

    while True:
        # Recieve UART comms data
        if currentModeInformation[3] != "AimShooter":
            inputtedData = UART.recieveData()

        # Check if data is recieved
        if inputtedData[-1] == True:
            
            # Run motion planning functionality
            #currentModeInformation, movementCommand = path.mainPathPlanning(inputtedData, currentModeInformation, timeList, pathDistanceList)
            currentModeInformation, movementCommand, timeList = path2.mainPathPlanning(inputtedData, currentModeInformation, timeList, pathDistanceList)

        # Check if program should end
        if movementCommand == "Exit" or globalExit == "Exit":
            print("Bruh moment")
            UART.writeData("A")
            sys.exit(0)
            
        # Send command to arduino
        UART.writeData(movementCommand)

        # If keyboard interupt end cycle
        signal.signal(signal.SIGINT, catchTheSignal)

def catchTheSignal(signal, frame):
    """
    """
    global globalExit
    globalExit = "Exit"
    

def main():
    """
    This excutes the primarly defs of the main scipt.

    Input:  None

    Output: None
    """
    # Execute main functionaliy
    executeFunctions()

if __name__ == "__main__":
    main()