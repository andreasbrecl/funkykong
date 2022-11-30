import RPi.GPIO as GPIO
import gpiozero
import time


def main():
    """
    This excutes the primarly defs of the main scipt.

    Input:  None

    Output: None
    """
    # Define GPIO pins
    firePin = 17
    reloadPin = 27
    reloadDonePin = 22
    startPin = 23
    stopPin = 24

    # Logic values
    reloadDone = 0

    # Define pin type
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(firePin, GPIO.OUT)
    GPIO.setup(reloadPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
    GPIO.setup(startPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
    GPIO.setup(stopPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
    GPIO.setup(reloadDonePin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

    while True:
        # Check start pin
        if GPIO.input(startPin):

            # Print that the pin has started
            print("Start Pin Pressed")

        # Stop pin
        if GPIO.input(stopPin):

            # Print pin is pressed'
            print("Stop Pin Pressed")

        # Check if reload pin is triggerd
        if GPIO.input(reloadPin) == False and reloadDone == 0:
            GPIO.output(firePin, 1)
            print("Shooting")
        else:
            GPIO.output(firePin, 0)
            print("Reloading")
            reloadDone = 1

        if GPIO.input(reloadDonePin):

            # Reloaded
            print("Reloaded")
            reloadDone = 0

        time.sleep(1)
        

if __name__ == "__main__":
    main()