"""
Author: Andreas Brecl
Date: 11/23/2022

This class will be responsible for the path planning of the robot. 
It will trigger different modes and initalize the first location 
of the robot. Refer to commands document for what each sent command
represents
"""

from lib.pixycam_aiming import PixycamAiming
#import RPi.GPIO as GPIO  
import time

class PathPlanning:
    def __init__(self):
        """
        Contructor to inital the class of path planning.
        """
        # Define constructor variables
        pixyCam = PixycamAiming()
        self.pixyCam = pixyCam

    def initializePath(inputtedData, currentModeInformation, pathDistanceList):
        """
        This funciton will align the robot as needed so that it
        can navigate to the fire zone. This is the first process
        to run each time the drone is turned on. It first will
        identify the side of the arena its on, then position
        itself a set distance from the main wall. This will help
        localize the robot's motion.

        Input:  inputtedData <list> <str> - Sensor input from the Mega
                currentModeInformation <list> <str> <int> - Information on what mode the system is in
                pathDistanceList <list> <int> - Distances that are expected at different parts in time

        Output: movementCommand <str> - Command for how robot needs to move
                systemMode <str> - Defines mode for the system
                subMode <str> - Sub mode of process
                sideColor <str> - Determines the side the robot is on
        """
        # Pull current mode data
        systemMode = currentModeInformation[0]
        subMode = currentModeInformation[3]
        sideColor = currentModeInformation[4]

        # Pull distance values
        initializationDistance = pathDistanceList[0]
        
        # Split input data
        lineSensor1 = inputtedData[0]
        lineSensor2 = inputtedData[1]
        lineSensor3 = inputtedData[2]
        lineSensor4 = inputtedData[3]
        ultrasonicSensorReading1 = inputtedData[4]
        ultrasonicSensorReading2 = inputtedData[5]

        # Define color checks
        colorCheckRed = "Red"
        colorCheckGreen = "Green"

        # Define sub modes
        subModeInitialize = "Initialize"
        subModeFindWall = "FindWall"
        subModeAlignDistance = "AlignDistance"
        subModeMoveToSide = "MoveToSide"

        # Define movement commands
        stop = "A"
        forward = "B"
        backwards = "C"
        left = "D"
        right = "E"

        # Run inital rotation to determine size
        if subMode == subModeInitialize:
            
            # Start rotation
            movementCommand = "J"

            # Check if pixy camera has found information
            sideColor = "None" # ENTER UPDATED FUNCTION OUTPUT HERE

            # Check if color is found
            if sideColor == colorCheckRed or sideColor == colorCheckGreen:

                # Change system mode
                subMode = subModeFindWall

                # Stop motion
                movementCommand = stop

        # Run rotation to find the wall
        elif subMode == subModeFindWall:

            # Run rotation 
            movementCommand = "J"

            # Calculate percent different of ultrasonic readings
            percentDifference = abs(ultrasonicSensorReading1 - ultrasonicSensorReading2) / ultrasonicSensorReading1 * 100

            # See if value is within 5 %
            if percentDifference <= 5:

                # Stop motion
                movementCommand = stop

                # Change mode to movement forward or backwards
                subMode = subModeAlignDistance

        # Change mode to wall alignment
        elif subMode == subModeAlignDistance:

            # Calculate percent difference of measurements and needed distance
            percentDifferenceFromNeeded = abs(initializationDistance - ultrasonicSensorReading1) / initializationDistance * 100
            
            # Check if distance is within needed area
            if percentDifferenceFromNeeded <= 5:

                # Stop motion
                movementCommand = stop

                # Change submode
                subMode = subModeMoveToSide

            # Check if robot is too close to wall
            elif initializationDistance > ultrasonicSensorReading1:
                
                # Back robot up
                movementCommand = backwards
            
            # Check if robot is too far from wall
            elif initializationDistance < ultrasonicSensorReading1:
                
                # Move robot forward
                movementCommand = forward

        # Do movement of side to side
        elif subMode == subModeMoveToSide:

            # Chose movement based on side
            if sideColor == colorCheckRed:

                # Move vehicle left
                movementCommand = left

            elif sideColor == colorCheckGreen:

                # Move vehicle right
                movementCommand = right

            # Check if the boundry is reached
            if lineSensor1 == 1 or lineSensor2 == 1 or lineSensor3 == 1 or lineSensor4 == 1:

                # Stop vehicle
                movementCommand = stop

                # Change vehicle modes
                systemMode = "GoToShoot"
                subMode = "MoveDiag"

        # Return data
        return movementCommand, systemMode, subMode, sideColor

    def pathToShootingLocation(inputtedData):
        """
        This function will deal with the path to shooting location.

        Input:  inputtedData <list> <str> - Sensor input from the Mega

        Output: 
        """
        
        # Return data
        return movementCommand, systemMode 

    def pathToReloadStation(inputtedData):
        """
        
        """

        # Return data
        return movementCommand, systemMode 

    def shootAtTarget(inputtedData):
        """
        
        """

        # Return data
        return movementCommand, systemMode 

    def reloadRobot(inputtedData):
        """
        
        """

        # Return data
        return movementCommand, systemMode 

    def checkCollision():
        """
        
        """
        pass

    def mainPathPlanning(self, inputtedData, currentModeInformation, timeList, pathDistanceList):
        """
        This is the main function that will handle which part of
        the motion planning process our system is on.

        Input:  inputtedData <list> <str> - Sensor input from the Mega
                currentModeInformation <list> <str> <int> - Information on what mode the system is in
                timeList <list> <int> - Time it takes for motions to occur
                pathDistanceList <list> <int> - Distances that are expected at different parts in time

        Output: currentModeInformationUpdated <list> <str> <int> - Updated information on what mode the system is in
                movementCommand <str> - Command for how robot needs to move
        """
        # Pull current mode data
        systemMode = currentModeInformation[0]
        time1 = currentModeInformation[1]
        time2 = currentModeInformation[2]
        subMode = currentModeInformation[3]
        sideColor = currentModeInformation[4]

        # Initialize and localize the robot's motion
        if systemMode == "Initialize":
            movementCommand, systemMode, subMode, sideColor = self.initializePath(inputtedData, currentModeInformation, pathDistanceList)

        # Go to the shooting location
        elif systemMode == "GoToShoot":
            movementCommand, systemMode = self.pathToShootingLocation(inputtedData)

        # travel path for reload
        elif systemMode == "GoToReload":
            movementCommand, systemMode = self.pathToReloadStation(inputtedData) 

        # Fire projectiles
        elif systemMode == "Shoot":
            movementCommand, systemMode = self.shootAtTarget(inputtedData)

        # System is in reload mode
        elif systemMode == "Reload":
            movementCommand, systemMode = self.reloadRobot(inputtedData) 


        # Remake current mode information
        currentModeInformationUpdated = [systemMode, time1, time2, subMode, sideColor]

        # Return values
        return currentModeInformationUpdated, movementCommand