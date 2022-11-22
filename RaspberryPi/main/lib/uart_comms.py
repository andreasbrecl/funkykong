"""
Author: Andreas Brecl
Date: 11/2/2022

This class will deal with sending and recieving the UART 
communications between the raspberry pi and arduino.
"""

# Import libraries
import serial
import time
import re

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

        # Create serial object
        self.ser = serial.Serial(self.port, self.baudRate, self.timeout)

        # Reset serial input buffer
        self.ser.reset_input_buffer()

    def recieveData(self):
        """
        This function will deal with recieveing data from
        the Arduino UART serial communcations.

        Input:  ser <object> - This is the serial communication
                self <object> - Instance of a sepecific class

        Output: inputedData <str> - String of sensor input from Arduino
        """
        # Pull UART Data
        recievedData = self.ser.readline().decode('utf-8').rstrip()

        # Seperate data
        inputtedData = self.decodeInputtedData(recievedData)

        # return UART data
        return inputtedData

    def writeData(self, motorData):
        """
        This function will deal with sending data from the
        Arudino UART serial communcations.

        Input:  motorData <str> - Information for how motors should move
                ser <object> - This is the serial communication

        Output: None
        """
        # Add delimiter
        motorData = motorData + "\n"

        # Convert message to bytes
        motorDataBytes = bytes(motorData, 'utf-8')

        # Write serial data
        self.ser.write(motorDataBytes)

    def decodeInputtedData(self, recievedData):
        """
        This function will determine specific readings of
        each sensor. The inputted data will be read in 
        the following way.
        format: <ls!X,ls@X,ls#X,ls$X,us!XXX.X,us@XXX.X,us#XXX.X,us$XXX.X,us$XXX.X,us%XXX.X,imu!XXX.X>

        Input:  recievedData <str> - Data passed by arduino
                self <object> - Instance of a sepecific class

        Output: inputtedData <list><int> - Data values of sensors in a list
        """
        # Split the data 
        splitData = recievedData.split(",")

        # Pull line sensor data
        lineSensorReading1 = splitData[0][4]
        lineSensorReading2 = splitData[1][3]
        lineSensorReading3 = splitData[2][3]
        lineSensorReading4 = splitData[3][3]

        # Pull ultra sonic sensor data
        ultrasonicSensorReading1 = splitData[4][3:-1]
        ultrasonicSensorReading2 = splitData[5][3:-1]
        ultrasonicSensorReading3 = splitData[6][3:-1]
        ultrasonicSensorReading4 = splitData[7][3:-1]
        ultrasonicSensorReading5 = splitData[8][3:-1]

        # Pull IMU data
        IMUSensorReading = splitData[9][4:-1]

        # Combine into output
        inputtedData = [lineSensorReading1,lineSensorReading2,lineSensorReading3,lineSensorReading4,\
            ultrasonicSensorReading1,ultrasonicSensorReading2,ultrasonicSensorReading3,ultrasonicSensorReading4,\
                ultrasonicSensorReading5,IMUSensorReading]

        # Return data
        return inputtedData