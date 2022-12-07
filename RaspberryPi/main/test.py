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

    while True:
        # Check start pin
        pass
        

if __name__ == "__main__":
    main()