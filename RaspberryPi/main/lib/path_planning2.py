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

class PathPlanning2:
    def __init__(self, firePin, reloadPin, reloadDonePin, startPin, stopPin):
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
        self.reloadDonePin = reloadDonePin
        self.startPin = startPin
        self.stopPin = stopPin

        # Define pixycam information
        pixyCam = PixycamAiming()
        self.pixyCam = pixyCam

        # Define pins
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(firePin, GPIO.OUT)
        GPIO.setup(reloadPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
        GPIO.setup(reloadDonePin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
        GPIO.setup(startPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
        GPIO.setup(stopPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

        # Set pin modes
        GPIO.output(firePin, 1)
        GPIO.output(firePin, 0)


    def initializePath(self, inputtedData, currentModeInformation, pathDistanceList, timeList):
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

        # Pull rotate time
        rotate90Time = timeList[3]

        # Define color checks
        colorCheckRed = "Red"
        colorCheckGreen = "Green"

        # Define sub modes
        subModeInitialize = "Initialize"
        subModeFindWall = "FindWall"
        subModeAlignDistance = "AlignDistance"
        subModeMoveToSide = "MoveToSide"
        subModeRotate = "Rotate"
        subModeRotateForward = "RotateForward"

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

            # print mode
            print(subModeInitialize)
            
            # Start rotation
            movementCommand = rotateRight

            # Check if pixy camera has found information
            sideColor = self.pixyCam.RedorGreens()

            # Check if color is found
            if sideColor == colorCheckRed or sideColor == colorCheckGreen:

                # Change system mode
                subMode = subModeFindWall

                # Stop motion
                movementCommand = stop

        # Run rotation to find the wall
        elif subMode == subModeFindWall:

            # Print mode
            print(subModeFindWall)

            # Check distance between items
            movementCommand = self.verifyForwardFacing(ultrasonicSensorReading1, ultrasonicSensorReading2)

            # Checkmovement command
            if movementCommand == stop:

                # Change submode
                subMode = subModeAlignDistance

        # Change mode to wall alignment
        elif subMode == subModeAlignDistance:

            # Print mode
            print(subModeAlignDistance)

            # Check distance between items
            movementCommand = self.checkDistance(initializationDistance, ultrasonicSensorReading1)

            # Checkmovement command
            if movementCommand == stop:

                # Change submode
                subMode = subModeRotate

                # Update time 
                time1 = time.time()
                
        # Rotate robot
        elif subMode == subModeRotate:

            # Print mode
            print(subModeRotate)

            # Chose movement based on side
            if sideColor == colorCheckRed:

                # Move vehicle left
                movementCommand = self.moveBasedOnTime(rotate90Time, time1, rotateLeft)

            elif sideColor == colorCheckGreen:

                # Move vehicle right
                movementCommand = self.moveBasedOnTime(rotate90Time, time1, rotateRight)

            # Check if rotation stopped
            if movementCommand == stop:

                # Switch mode
                subMode = subModeMoveToSide
                
                # Update time
                time1 = time.time()


        # Do movement of side to side
        elif subMode == subModeMoveToSide:

            # Print mode
            print(subModeMoveToSide)

            # Move vehicle forward
            movementCommand = forward

            # Check if the boundry is reached
            if lineSensor1 == 1 or lineSensor2 == 1 or lineSensor3 == 1 or lineSensor4 == 1:

                if lineSensor1 == 1 and lineSensor2 == 1 and lineSensor3 == 1 and lineSensor4 == 1:

                    pass

                else:

                    # Stop vehicle
                    movementCommand = stop

                    # Change vehicle modes
                    systemMode = "GoToShoot"
                    subMode = "MoveForward"

                    # Calculate start of movement time
                    time1 = time.time()

        # Rotate the system so it faces forward
        elif subMode == subModeRotateForward:

            # Print mode
            print(subModeRotate)

            # Chose movement based on side
            if sideColor == colorCheckRed:

                # Move vehicle left
                movementCommand = self.moveBasedOnTime(rotate90Time, time1, rotateRight)

            elif sideColor == colorCheckGreen:

                # Move vehicle right
                movementCommand = self.moveBasedOnTime(rotate90Time, time1, rotateLeft)

            # Check if rotation stopped
            if movementCommand == stop:

                # Change vehicle modes
                systemMode = "GoToShoot"
                subMode = "MoveForward"
                
                # Update time
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
        forwardTimeToShooting = timeList[2]
        rotate90Time = timeList[3]

        # Define color checks
        colorCheckRed = "Red"
        colorCheckGreen = "Green"

        # Define sub modes
        subModeMoveDiag = "MoveDiag"
        subModeMoveSidways = "MoveSidways"
        subModeMoveForward = "MoveForward"
        subModeRotateSidways = "RotateSidways"
        subModeRotateForward = "RotateForward"

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

            # Print mode
            print(subModeMoveDiag)

            # Chose movement based on side
            if sideColor == colorCheckRed:

                # Move vehicle diag forward right
                movementCommand = self.moveBasedOnTime(diagTimeToShooting, time1, diagFowardRight)

            elif sideColor == colorCheckGreen:

                # Move vehicle diag forward left
                movementCommand = self.moveBasedOnTime(diagTimeToShooting, time1, diagFowardLeft)

            if movementCommand == stop:

                # Change mode
                subMode = subModeRotateSidways

                # Reset time
                time1 = time.time()

        # Rotate the system so it faces forward
        elif subMode == subModeRotateSidways:

            # Print mode
            print(subModeRotateSidways)

            # Chose movement based on side
            if sideColor == colorCheckRed:

                # Move vehicle left
                movementCommand = self.moveBasedOnTime(rotate90Time, time1, rotateRight)

            elif sideColor == colorCheckGreen:

                # Move vehicle right
                movementCommand = self.moveBasedOnTime(rotate90Time, time1, rotateLeft)

            # Check if rotation stopped
            if movementCommand == stop:

                # Change vehicle modes
                subMode = subModeMoveSidways
                
                # Update time
                time1 = time.time()

        # Move system sidways
        elif subMode == subModeMoveSidways:

            # Print mode
            print(subModeMoveSidways)

            # Move vehicle right
            movementCommand = self.moveBasedOnTime(leftRightTimeToShooting, time1, stop)

            # Check if stop command recieved
            if movementCommand == stop:

                # Change mode
                subMode = subModeRotateForward

                # Update time
                time1 = time.time()

        # Rotate the system so it faces forward
        elif subMode == subModeRotateForward:

            # Print mode
            print(subModeRotateSidways)

            # Chose movement based on side
            if sideColor == colorCheckRed:

                # Move vehicle left
                movementCommand = self.moveBasedOnTime(rotate90Time, time1, rotateLeft)

            elif sideColor == colorCheckGreen:

                # Move vehicle right
                movementCommand = self.moveBasedOnTime(rotate90Time, time1, rotateRight)

            # Check if rotation stopped
            if movementCommand == stop:

                # Change mode
                systemMode = "Shoot"
                subMode = "AimShooter"
                
                # Update time
                time1 = time.time()

        # Move to forward location
        elif subMode == subModeMoveForward:

            # Print mode
            print(subModeMoveForward)

            # Determine movement
            movementCommand = self.moveBasedOnTime(forwardTimeToShooting, time1, forward)

            if movementCommand == stop:
                
                # Change mode
                subMode = subModeMoveDiag

                # Update time
                time1 = time.time()

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

        # Movement command
        movementCommand = stop

        # Predefine pixy cam
        pixyCamAim = "N"
        pixyCamAimLeft = "L"
        pixyCamAimRight = "R"
        pixyCamAimCenter = "C"
        
        # Enter Aim shooter mode
        if subMode == subModeAimShooter:

            # Print mode
            print(subModeAimShooter)

            # Read in data
            pixyCamAim = self.pixyCam.GetBlue()

            # Check what direction to aim
            if pixyCamAim == pixyCamAimLeft:
                
                # Rotate left to aim
                movementCommand = rotateLeft

                # Set GPIO low
                GPIO.output(self.firePin, 0)

                # See if reload is triggered
                #if GPIO.input(self.reloadPin):

                    # Change mode
                #    subMode = subModeFixOrientation
            
            # Check to aim right
            elif pixyCamAim == pixyCamAimRight:

                # Rotate right
                movementCommand = rotateRight

                # Set GPIO low
                GPIO.output(self.firePin, 0)

                # See if reload is triggered
                #if GPIO.input(self.reloadPin):

                    # Change mode
                #    subMode = subModeFixOrientation
                

            elif pixyCamAim == pixyCamAimCenter:

                # Stop moving
                movementCommand = stop

                # Trigger firing
                GPIO.output(self.firePin, 1)

                # See if reload is triggered
                #if GPIO.input(self.reloadPin):

                    # Change mode
                #    subMode = subModeFixOrientation
                    
                    # Set GPIO low
                #    GPIO.output(self.firePin, 0)

            print(pixyCamAim)

        # Fix how robot is oriented         
        elif subMode == subModeFixOrientation:

            # Print mode
            print(subModeFixOrientation)
            
            # Fix how it is facing
            movementCommand = self.verifyForwardFacing(self, ultrasonicSensorReading1, ultrasonicSensorReading2)

            # Checkmovement command
            if movementCommand == stop:

                # Change submode
                subMode = subModeFixDistance

        # Fix distance robot is off wall
        elif subMode == subModeFixDistance:

            # Print mode
            print(subModeFixDistance)

            # Check distance between items
            movementCommand = self.checkDistance(shootingDistance, ultrasonicSensorReading1)

            # Checkmovement command
            if movementCommand == stop:

                # Change submode
                systemMode = "GoToReload"
                subMode = "MoveSidways"

                # Calculate time
                time1 = time.time()

        # Return data
        return movementCommand, systemMode, subMode, time1

    
    def pathToReloadStation(self, inputtedData, currentModeInformation, timeList):
        """
        This function will deal with the pathfinding from the
        shooting position to the reload station. It will align
        itself with the lines around the border of the arena
        and then back itself into the reload corner.

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
        leftRightTimeToShooting = timeList[1]

        # Split input data
        lineSensorReading1 = inputtedData[0]
        lineSensorReading2 = inputtedData[1]
        lineSensorReading3 = inputtedData[2]
        lineSensorReading4 = inputtedData[3]

        # Define color checks
        colorCheckRed = "Red"
        colorCheckGreen = "Green"

        # Define sub modes
        subModeMoveDiag = "MoveDiag"
        subModeMoveSidways = "MoveSidways"
        subModeMoveBack = "MoveBack"
        subModeMoveForward = "MoveForward"
        subModeAlignSide = "AlignSide"
        subModeReload = "Reload"
        subModeAlignBack = "AlignBack"

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

        # Enter sidways movement mode
        if subMode == subModeMoveSidways:

            # Print mode
            print(subModeMoveSidways)

            # Check what side the robot is on
            if sideColor == colorCheckGreen:
                
                # Move right
                movementCommand = self.moveBasedOnTime(leftRightTimeToShooting, time1, right)

            elif sideColor == colorCheckRed:
        
                # Move left
                movementCommand = self.moveBasedOnTime(leftRightTimeToShooting, time1, left)

            # Check if movement has compleded 
            if movementCommand == stop:

                # Change mode
                subMode = subModeMoveDiag

        # Move diagonal until line is hit
        if subMode == subModeMoveDiag:

            # Print mode
            print(subModeMoveDiag)

            # Check what side the robot is on
            if sideColor == colorCheckGreen:
                
                # Move diag back right
                movementCommand = diagBackRight

            elif sideColor == colorCheckRed:
        
                # Move diag back left
                movementCommand = diagBackLeft

            # Check if system has run into side lines
            if lineSensorReading1 == 1 or lineSensorReading2 == 1 or lineSensorReading3 == 1 or lineSensorReading4 == 1:

                # Stop system
                movementCommand = stop

                # Change mode
                subMode = subModeAlignSide

        # Align robot on side
        elif subMode == subModeAlignSide:

            # Print mode
            print(subModeAlignSide)

            # Check what side the robot is on
            if sideColor == colorCheckGreen:
                
                # Align vehicle
                movementCommand = self.alignOnLines(lineSensorReading1, lineSensorReading4, sideColor)

                # Check if alignment has stopped
                if movementCommand == stop:

                    # Change mode
                    subMode = subModeMoveBack

            elif sideColor == colorCheckRed:

                # Align vehicle
                movementCommand = self.alignOnLines(lineSensorReading2, lineSensorReading3, sideColor)

                # Check if alignment has stopped
                if movementCommand == stop:

                    # Change mode
                    subMode = subModeMoveBack

        # Enter move backwards mode
        elif subMode == subModeMoveBack:

            # Print mode
            print(subModeMoveBack)

            # Start backwards movement
            movementCommand = backwards

            # Check what side the robot is on
            if sideColor == colorCheckGreen and lineSensorReading3 == 1:
                
                # Stop movement
                movementCommand = stop

                # Change mode
                subMode = subModeAlignBack

            elif sideColor == colorCheckRed and lineSensorReading4 == 1:
        
                # Stop movement
                movementCommand = stop

                # Change mode
                subMode = subModeAlignBack
            
        # Align rear of vehicle
        elif subMode == subModeAlignBack:
                
            # Print mode
            print(subModeAlignBack)

            # Align vehicle
            movementCommand = self.alignOnLines(lineSensorReading3, lineSensorReading4, "Rear")

            # Check if alignment has stopped
            if movementCommand == stop:

                # Change mode
                    subMode = subModeReload
                
        # Enter reload mode
        elif subMode == subModeReload:

            # Print mode
            print(subModeReload)

            # Wait for reload done input
            if GPIO.input(self.reloadDonePin):

                # Change modes
                systemMode = "GoToShoot"
                subMode = "MoveForward"

                # Update time
                time1 = time.time()

        # Return data
        return movementCommand, systemMode, subMode, time1
    
    def alignOnLines(self, line1, line2, sideColor):
        """
        This function will deal with aligning the vehicle on
        the line that it has run into. This will allow it to
        move straight on its next motion.

        Input:  line1 <int> - Line sensor reading
                line2 <int> - Line sensor reading

        Output: movementCommand <str> - Motion vehicle needs to take
        """
        # Define movements
        stop = "A"
        backwards = "C"
        left = "D"
        right = "E"
        rotateRight = "J"
        rotateLeft = "K"

        # Define checks
        colorCheckRed = "Red"
        colorCheckGreen = "Green"
        colorCheckRear = "Rear"

        # Check what side the vehicle is on
        if sideColor == colorCheckGreen:

            # Check if only front sensor is triggered   
            if line1 == 1:

                # Trigger rotation
                movementCommand = rotateLeft
            
            # Check if only back sensor is triggered
            elif line2 == 1:
            
                # Trigger rotation
                movementCommand = rotateRight
                
            # Check if neither are triggered
            elif line1 == 0 and line2 == 0:
            
                # Move right
                movementCommand = right
                
            # Check if both are triggerd
            elif line1 == 1 and line2 == 1:
                
                # Stop movement
                movementCommand = stop

        # Check for other side
        elif sideColor == colorCheckRed:
            
            # Check if only front sensor is triggered   
            if line1 == 1:

                # Trigger rotation
                movementCommand = rotateRight
            
            # Check if only back sensor is triggered
            elif line2 == 1:
            
                # Trigger rotation
                movementCommand = rotateLeft
                
            # Check if neither are triggered
            elif line1 == 0 and line2 == 0:
            
                # Move right
                movementCommand = left
                
            # Check if both are triggerd
            elif line1 == 1 and line2 == 1:
                
                # Stop movement
                movementCommand = stop

        elif sideColor == colorCheckRear:

            # Check if only front sensor is triggered   
            if line1 == 1:

                # Trigger rotation
                movementCommand = rotateRight
            
            # Check if only back sensor is triggered
            elif line2 == 1:
            
                # Trigger rotation
                movementCommand = rotateLeft
                
            # Check if neither are triggered
            elif line1 == 0 and line2 == 0:
            
                # Move right
                movementCommand = backwards
                
            # Check if both are triggerd
            elif line1 == 1 and line2 == 1:
                
                # Stop movement
                movementCommand = stop

        return movementCommand

    def checkCollision():
        """
        
        """
        pass

    def moveBasedOnTime(self, desiredTime, time1, movementCommand):
        """
        This function will deal with the movements based on
        the inputted time and the movement wanted. It will
        also do the checks for if the time requirements are
        met.

        Input:  desiredTime <int> - Time of movement

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
        if ultrasonic1 > ultrasonic2 and ultrasonic1 < 25 and ultrasonic2 < 25:
            movementCommand = rotateLeft
        elif ultrasonic2 > ultrasonic1 and ultrasonic1 < 25 and ultrasonic2 < 25:
            movementCommand = rotateRight
        else:
            movementCommand = rotateLeft

        # Calculate percent different of ultrasonic readings
        percentDifference = self.calculatePercentage(ultrasonic1, ultrasonic2)

        # See if value is within 5 %
        if percentDifference <= 5 and ultrasonic1 < 25 and ultrasonic2 < 25:

            # Stop motion
            movementCommand = stop
        
        # Return command
        return movementCommand
        

    def checkDistance(self, expectedDistance, ultrasonic):
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
        if percentDifferenceFromNeeded <= 10:

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

    def calculatePercentage(self, variable1, variable2):
        """
        This function will compute the average value between two
        variables.

        Input:  variable1 <int> - Variable 1 input
                variable2 <int> - Variable 2 input
        
        Output: percentDifference <int> - Percent difference between values
        """
        # Calculate percentage
        if variable1 != 0:
            percentDifference = abs(variable1 - variable2) / variable1 * 100
        else:
            percentDifference = 10
        
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

        #systemMode = "Shoot"
        #currentModeInformation[3] = "AimShooter"

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

        # Remake current mode information
        currentModeInformationUpdated = [systemMode, time1, time2, subMode, sideColor]

        # Check if shooter should stop
        if GPIO.input(self.stopPin):
            movementCommand = "Exit"

        # Return values
        return currentModeInformationUpdated, movementCommand