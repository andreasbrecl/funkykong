"""
Author: Andreas Brecl
Date: 11/23/2022

This class will be responsible for the path planning of the robot. 
It will trigger different modes and initalize the first location 
of the robot. Refer to commands document for what each sent command
represents
"""

from lib.pixycam_aiming import PixycamAiming
import RPi.GPIO as GPIO  
import time

class PathPlanning:
    def __init__(self, firePin, reloadPin):
        """
        Contructor to inital the class of path planning. Takes
        in pin values for GPIO.

        Input:  firePin <int> - Fire pin value
                reloadPin <int> - reload pin value

        Output: None
        """
        # Define constructor variables
        self.firePin = firePin
        self.reloadPin = reloadPin

        # Define pixycam information
        pixyCam = PixycamAiming()
        self.pixyCam = pixyCam

        # Define pins
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(firePin, GPIO.OUT)
        GPIO.setup(reloadPin, GPIO.IN)


    def initializePath(self, inputtedData, currentModeInformation, pathDistanceList):
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
                time1 <int> - system time
        """
        # Pull current mode data
        systemMode = currentModeInformation[0]
        time1 = currentModeInformation[1]
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
        rotateRight = "J"
        rotateLeft = "K"
        
        # Run inital rotation to determine size
        if subMode == subModeInitialize:
            
            # Start rotation
            movementCommand = rotateRight

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

            # Check distance between items
            movementCommand = self.verifyForwardFacing(ultrasonicSensorReading1, ultrasonicSensorReading2)

            # Checkmovement command
            if movementCommand == stop:

                # Change submode
                subMode = subModeAlignDistance

        # Change mode to wall alignment
        elif subMode == subModeAlignDistance:

            # Check distance between items
            movementCommand = self.checkDistance(initializationDistance, ultrasonicSensorReading1)

            # Checkmovement command
            if movementCommand == stop:

                # Change submode
                subMode = subModeMoveToSide

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

                # Calculate start of movement time
                time1 = time.time()

        # Return data
        return movementCommand, systemMode, subMode, sideColor, time1

    def pathToShootingLocation(self, inputtedData, currentModeInformation, timeList, pathDistanceList):
        """
        This function will deal with the path to shooting location.

        Input:  inputtedData <list> <str> - Sensor input from the Mega
                currentModeInformation <list> <str> <int> - Information on what mode the system is in
                pathDistanceList <list> <int> - Distances that are expected at different parts in time
                timeList <list> <int> - Drive time values for actions

        Output: movementCommand <str> - Command for how robot needs to move
                systemMode <str> - Defines mode for the system
                subMode <str> - Sub mode of process
                time1 <int> - system time
        """
        # Pull current mode data
        systemMode = currentModeInformation[0]
        time1 = currentModeInformation[1]
        subMode = currentModeInformation[3]
        sideColor = currentModeInformation[4]

        # Pull timing values
        diagTimeToShooting = timeList[0]
        leftRightTimeToShooting = timeList[1]

        # Define color checks
        colorCheckRed = "Red"
        colorCheckGreen = "Green"

        # Define sub modes
        subModeMoveDiag = "MoveDiag"
        subModeMoveSidways = "MoveSidways"

        # Define movement commands
        stop = "A"
        forward = "B"
        backwards = "C"
        left = "D"
        right = "E"
        diagFowardRight = "F"
        diagFowardLeft = "G"
        diagBackRight = "H"
        diagBackLeft = "I"
        rotateRight = "J"
        rotateLeft = "K"

        # See if system is in diagonal movement mode
        if subMode == subModeMoveDiag:

            # Chose movement based on side
            if sideColor == colorCheckRed:

                # Move vehicle diag forward right
                movementCommand = self.moveBasedOnTime(diagTimeToShooting, time1, diagFowardRight)

            elif sideColor == colorCheckGreen:

                # Move vehicle diag forward left
                movementCommand = self.moveBasedOnTime(diagTimeToShooting, time1, diagFowardLeft)

            if movementCommand == stop:

                # Change mode
                subMode = subModeMoveSidways

                # Reset time
                time1 = time.time()

        # Move system sidways
        elif subMode == subModeMoveSidways:

            # Chose movement based on side
            if sideColor == colorCheckRed:

                # Move vehicle right
                movementCommand = self.moveBasedOnTime(leftRightTimeToShooting, time1, right)

            elif sideColor == colorCheckGreen:

                # Move vehicle left
                movementCommand = self.moveBasedOnTime(leftRightTimeToShooting, time1, left)

            if movementCommand == stop:

                # Change mode
                systemMode = "Shoot"
                subMode = "AimShooter"

        # Return data
        return movementCommand, systemMode, subMode, time1

    
    def shootAtTarget(self, inputtedData, currentModeInformation, pathDistanceList):
        """
        This function will deal with shooting the shooter at
        the detected target. It will locate the enemy balloon
        and then rotate towards it. Once it has fired the full
        magazine, it will stop this function.

        Input:  inputtedData <list> <str> - Sensor input from the Mega
                currentModeInformation <list> <str> <int> - Information on what mode the system is in
                pathDistanceList <list> <int> - Distances that are expected at different parts in time

        Output: movementCommand <str> - Command for how robot needs to move
                systemMode <str> - Defines mode for the system
                subMode <str> - Sub mode of process
                time1 <int> - system time
        """
        # Pull current mode data
        systemMode = currentModeInformation[0]
        time1 = currentModeInformation[1]
        subMode = currentModeInformation[3]
        
        # Pull distance values
        shootingDistance = pathDistanceList[1]
        
        # Split input data
        ultrasonicSensorReading1 = inputtedData[4]
        ultrasonicSensorReading2 = inputtedData[5]

        # Define color checks
        colorCheckRed = "Red"
        colorCheckGreen = "Green"

        # Define sub modes
        subModeAimShooter = "AimShooter"
        subModeFixOrientation = "FixOrientation"
        subModeFixDistance = "FixDistance"

        # Define movement commands
        stop = "A"
        forward = "B"
        backwards = "C"
        rotateRight = "J"
        rotateLeft = "K"

        # Predefine pixy cam
        pixyCamAim = "None"
        pixyCamAimLeft = "Left"
        pixyCamAimRight = "Right"
        pixyCamAimCenter = "Center"
        
        # Enter Aim shooter mode
        if subMode == subModeAimShooter:

            # Read in data
            pixyCamAim = "None" # ADD FUNCTION READ IN HERE

            # Check what direction to aim
            if pixyCamAim == pixyCamAimLeft:
                
                # Rotate left to aim
                movementCommand = rotateLeft

                # Set GPIO low
                GPIO.output(self.firePin, 0)

                # See if reload is triggered
                if GPIO.input(self.reloadPin):

                    # Change mode
                    subMode = subModeFixOrientation
            
            # Check to aim right
            elif pixyCamAim == pixyCamAimRight:

                # Rotate right
                movementCommand = rotateRight

                # Set GPIO low
                GPIO.output(self.firePin, 0)

                # See if reload is triggered
                if GPIO.input(self.reloadPin):

                    # Change mode
                    subMode = subModeFixOrientation
                

            elif pixyCamAim == pixyCamAimCenter:

                # Stop moving
                movementCommand = stop

                # Trigger firing
                GPIO.output(self.firePin, 1)

                # See if reload is triggered
                if GPIO.input(self.reloadPin):

                    # Change mode
                    subMode = subModeFixOrientation
                    
                    # Set GPIO low
                    GPIO.output(self.firePin, 0)

        # Fix how robot is oriented         
        elif subMode == subModeFixOrientation:
            
            # Fix how it is facing
            movementCommand = self.verifyForwardFacing(self, ultrasonicSensorReading1, ultrasonicSensorReading2)

            # Checkmovement command
            if movementCommand == stop:

                # Change submode
                subMode = subModeFixDistance

        # Fix distance robot is off wall
        elif subMode == subModeFixDistance:

            # Check distance between items
            movementCommand = self.checkDistance(shootingDistance, ultrasonicSensorReading1)

            # Checkmovement command
            if movementCommand == stop:

                # Change submode
                systemMode = "GoToReload"
                subMode = "MoveDiag"

                # Calculate time
                time1 = time.time()

        # Return data
        return movementCommand, systemMode, subMode, time1

    
    def pathToReloadStation(inputtedData):
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

    def moveBasedOnTime(desiredTime, time1, movementCommand):
        """
        This function will deal with the movements based on
        the inputted time and the movement wanted. It will
        also do the checks for if the time requirements are
        met.

        Input:  desiredTime =

        Output: movementCommand <str> - Movement command to be sent to system
        """
        # Define movement
        stop = "A"

        # calculate time2
        time2 = time.time()

        # Calculate time difference
        timeDifference = time2 - time1

        # Check if motion should stop
        if timeDifference >= desiredTime:
            movementCommand = stop

        # Return command
        return movementCommand

    def verifyForwardFacing(self, ultrasonic1, ultrasonic2):
        """
        This function will determine if the system is facing
        forward by comparing the ultrasonic readings of the
        system.

        Input:  ultrasonic1 <int> - Ultrasonic reading from sensor 1
                ultrasonic2 <int> - Ultrasonic reading from sensor 2

        Output: movementCommand <str> - Movement command to be sent to system
        """
        # Define movements
        stop = "A"
        rotateRight = "J"
        rotateLeft = "K"

        # Run rotation 
        if ultrasonic1 > ultrasonic2 and ultrasonic1 < 20 and ultrasonic2 < 20:
            movementCommand = rotateLeft
        elif ultrasonic2 > ultrasonic1 and ultrasonic1 < 20 and ultrasonic2 < 20:
            movementCommand = rotateRight
        else:
            movementCommand = rotateLeft

        # Calculate percent different of ultrasonic readings
        percentDifference = self.calculatePercentage(ultrasonic1, ultrasonic2)

        # See if value is within 5 %
        if percentDifference <= 5:

            # Stop motion
            movementCommand = stop
        
        # Return command
        return movementCommand
        

    def checkDistance(self, ultrasonic, expectedDistance):
        """
        This function checks if the ultrasonic sensor distances
        are too close, too far, or correct distance from target.

        Input:  ultrasonic <int> - Ultrasonic sensor reading
                expectedDistance <int> - Distance needed at location
        
        Output: movementCommand <str> - Movement command to be sent to system
        """
        # Define movements
        stop = "A"
        forward = "B"
        backwards = "C"

        # Calculate percent difference of measurements and needed distance
        percentDifferenceFromNeeded = self.calculatePercentage(expectedDistance, ultrasonic)
        
        # Check if distance is within needed area
        if percentDifferenceFromNeeded <= 5:

            # Stop motion
            movementCommand = stop

        # Check if robot is too close to wall
        elif expectedDistance > ultrasonic:
            
            # Back robot up
            movementCommand = backwards
        
        # Check if robot is too far from wall
        elif expectedDistance < ultrasonic:
            
            # Move robot forward
            movementCommand = forward

        return movementCommand

    def calculatePercentage(variable1, variable2):
        """
        This function will compute the average value between two
        variables.

        Input:  variable1 <int> - Variable 1 input
                variable2 <int> - Variable 2 input
        
        Output: percentDifference <int> - Percent difference between values
        """
        # Calculate percentage
        percentDifference = abs(variable1 - variable2) / variable1 * 100
        
        # Return values
        return percentDifference

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
            movementCommand, systemMode, subMode, sideColor, time1 = self.initializePath(inputtedData, currentModeInformation, pathDistanceList)

        # Go to the shooting location
        elif systemMode == "GoToShoot":
            movementCommand, systemMode, subMode, time1 = self.pathToShootingLocation(inputtedData, currentModeInformation, timeList, pathDistanceList)

        # travel path for reload
        elif systemMode == "GoToReload":
            movementCommand, systemMode, subMode, time1 = self.pathToReloadStation(inputtedData, currentModeInformation, timeList, pathDistanceList) 

        # Fire projectiles
        elif systemMode == "Shoot":
            movementCommand, systemMode, subMode, time1 = self.shootAtTarget(inputtedData, currentModeInformation, pathDistanceList)

        # System is in reload mode
        elif systemMode == "Reload":
            movementCommand, systemMode, subMode, time1 = self.reloadRobot(inputtedData) 


        # Remake current mode information
        currentModeInformationUpdated = [systemMode, time1, time2, subMode, sideColor]

        # Return values
        return currentModeInformationUpdated, movementCommand