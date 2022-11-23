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

    def initializePath():
        """
        This funciton will align the robot as needed so that it
        can navigate to the fire zone. This is the first process
        to run each time the drone is turned on. It first will
        identify the side of the arena its on, then position
        itself a set distance from the main wall. This will help
        localize the robot's motion.

        Input:  inputtedData <list> <str> - Sensor input from the Mega

        Output: movementCommand <str> - Command for how robot needs to move
                systemMode <str> - Defines mode for the system
        """

    def pathToShootingLocation():
        """
        
        """
        pass

    def pathToReloadStation():
        """
        
        """
        pass

    def shootAtTarget():
        """
        
        """
        pass

    def reloadRobot():
        """
        
        """
        pass


    def mainPathPlanning(self, inputtedData, currentModeInformation):
        """
        This is the main function that will handle which part of
        the motion planning process our system is on.

        Input:  inputtedData <list> <str> - Sensor input from the Mega
                currentModeInformation <list> <str> <int> - Information on what mode the system is in

        Output: currentModeInformationUpdated <list> <str> <int> - Updated information on what mode the system is in
                movementCommand <str> - Command for how robot needs to move
        """
        # Pull current mode data
        systemMode = currentModeInformation[0]
        time1 = currentModeInformation[1]
        time2 = currentModeInformation[2]

        # Initialize and localize the robot's motion
        if systemMode == "Initialize":
            movementCommand = self.initializePath(inputtedData)

        # Go to the shooting location
        elif systemMode == "GoToShoot":
            movementCommand = self.pathToShootingLocation(inputtedData)

        # travel path for reload
        elif systemMode == "GoToReload":
            movementCommand = self.pathToReloadStation(inputtedData) 

        # Fire projectiles
        elif systemMode == "Shoot":
            movementCommand = self.shootAtTarget(inputtedData)

        # System is in reload mode
        elif systemMode == "Reload":
            movementCommand = self.reloadRobot(inputtedData) 


        # Remake current mode information
        currentModeInformationUpdated = [systemMode, time1, time2]

        # Return values
        return currentModeInformationUpdated, movementCommand