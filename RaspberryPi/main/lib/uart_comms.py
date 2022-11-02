"""
Author: Andreas Brecl
Date: 11/2/2022

This class will deal with sending and recieving the UART 
communications between the raspberry pi and arduino.
"""

# Import libraries
import serial
import time

class UARTComms:
    def __init__(self, port, baudRate, timeout):
        """
        This function initalizes the object for the serial
        communications.

        Input:  None

        Output: None
        """
        # Define self vars
        self.port = port
        self.baudRate = baudRate
        self.timeout = timeout

    def recieveData():
        """
        This function will deal with recieveing data from
        the Arduino UART serial communcations.

        Input:  None

        Output: None
        """
        pass

    def writeData():
        """
        This function will deal with sending data from the
        Arudino UART serial communcations.

        Input:  None

        Output: None
        """
        pass

    def initalizeUART(self, ser):
        """
        This function will create the inital objects needed
        for serial communication.

        Inputs:  self <object> - Instance of a sepecific class

        Outputs: ser <object> - This is the serial communication object
        """
        # Create serial object
        ser = serial.Serial(self.port, self.baudRate, self.timeout)

        # Reset serial input buffer
        ser.reset_input_buffer()

        # Return serial information
        return ser