"""
Author: Andreas Brecl
Date: 11/2/2022

This class will deal with sending and recieving the UART 
communications between the raspberry pi and arduino.
"""

# Import libraries
import serial

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
        ser = serial.Serial(self.port, self.baudRate, timeout=self.timeout)
        self.ser = ser

        # Reset serial input buffer
        self.ser.reset_input_buffer()

    def recieveData(self):
        """
        This function will deal with recieveing data from
        the Arduino UART serial communcations.

        Input:  None

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

        Output: None
        """
        if self.ser.in_waiting() == False:
            # Add delimiter
            motorData = motorData + "\n"

            # Convert message to bytes
            motorDataBytes = bytes(motorData)

            # Write serial data
            self.ser.write(motorDataBytes)

    def decodeInputtedData(self, recievedData):
        """
        This function will determine specific readings of
        each sensor. The inputted data will be read in 
        the following way.
        format: <ls!X,ls@X,ls#X,ls$X,us!XXX.X,us@XXX.X,us#XXX.X,us$XXX.X,us$XXX.X,us%XXX.X,imu!XXX.X>

        Input:  recievedData <str> - Data passed by arduino

        Output: inputtedData <list><int> - Data values of sensors in a list
        """
        # See if data is being read
        isBeingReadStart = recievedData.find('<')
        isBeingReadEnd = recievedData.find('>')

        if isBeingReadStart != -1 and isBeingReadEnd != -1:
            # Split the data 
            splitData = recievedData.split(",")

            # Pull line sensor data
            lineSensorReading1 = int(splitData[0][4])
            lineSensorReading2 = int(splitData[1][3])
            lineSensorReading3 = int(splitData[2][3])
            lineSensorReading4 = int(splitData[3][3])

            # Pull ultra sonic sensor data
            ultrasonicSensorReading1 = float(splitData[4][3:-1])
            ultrasonicSensorReading2 = float(splitData[5][3:-1]) - 2.8
            ultrasonicSensorReading3 = float(splitData[6][3:-1])
            ultrasonicSensorReading4 = float(splitData[7][3:-1])
            ultrasonicSensorReading5 = float(splitData[8][3:-1])

            # Pull IMU data
            IMUSensorReading = float(splitData[9][4:-1])

            # Define if serial message being recieved
            serialIsRecieved = True

            # Combine into output
            inputtedData = [lineSensorReading1,lineSensorReading2,lineSensorReading3,lineSensorReading4,\
                ultrasonicSensorReading1,ultrasonicSensorReading2,ultrasonicSensorReading3,ultrasonicSensorReading4,\
                    ultrasonicSensorReading5,IMUSensorReading, serialIsRecieved]
            
            # Print data
            print(inputtedData)
        
        # Send back indication showing serial not recieved
        else:
            # Define if serial message being recieved
            serialIsRecieved = False

            # Pull line sensor data
            lineSensorReading1 = -1
            lineSensorReading2 = -1
            lineSensorReading3 = -1 
            lineSensorReading4 = -1 

            # Pull ultra sonic sensor data
            ultrasonicSensorReading1 = -1 
            ultrasonicSensorReading2 = -1 
            ultrasonicSensorReading3 = -1 
            ultrasonicSensorReading4 = -1 
            ultrasonicSensorReading5 = -1 

            # Pull IMU data
            IMUSensorReading = -1 

            # Combine into output
            inputtedData = [lineSensorReading1,lineSensorReading2,lineSensorReading3,lineSensorReading4,\
                ultrasonicSensorReading1,ultrasonicSensorReading2,ultrasonicSensorReading3,ultrasonicSensorReading4,\
                    ultrasonicSensorReading5,IMUSensorReading, serialIsRecieved]


        # Return data
        return inputtedData