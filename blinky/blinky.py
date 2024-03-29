import RPi.GPIO as GPIO
import time

ORANGE = 3

def main():
    GPIO.setmode(GPIO.BOARD)
    
    print("FLASHING ORANGE LIGHT")
    
    GPIO.setup(ORANGE, GPIO.OUT)
    count = 0
    try:
        while count < 8:
            GPIO.output(ORANGE, GPIO.HIGH)
            print("ORANGE LIGHT ON")
            time.sleep(1)
            GPIO.output(ORANGE, GPIO.LOW)
            print("ORANGE LIGHT OFF")
            time.sleep(1)
            count = count + 1
    except KeyboardInterrupt:
        print("\nExiting program")
    finally:
        GPIO.cleanup()

if __name__ == "__main__":
    main()


