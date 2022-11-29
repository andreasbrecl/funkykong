import RPi.GPIO as GPIO  
import time


def main():
    """
    This excutes the primarly defs of the main scipt.

    Input:  None

    Output: None
    """
    # Define pins

    # Define pin type
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(firePin, GPIO.OUT)
    GPIO.setup(reloadPin, GPIO.IN)
    GPIO.setup(reloadDonePin, GPIO.IN)

    while True:
        

if __name__ == "__main__":
    main()