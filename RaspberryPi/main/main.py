#!/usr/bin/env python3
"""
Author: Andrea Brecl
Date: 11/2/2022

This script will initalize the main functionality of the Raspberry
Pi software. The raspberry pi will be responsible for determining
the image recognition and processing the data inputs from the arduino.
It will take in the data, then determine the motion planning required
to put the system into the correct location.
"""

# Import classes
from lib.uart_comms import UARTComms


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
    baudRate = 9600
    timeout = 1

    # Create UART object
    UART = UARTComms(port, baudRate, timeout)

    while True:
        # Recieve UART comms data
        inputtedData = UART.recieveData()
        print(inputtedData)

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