import RPi.GPIO as GPIO
from bluepy.btle import Peripheral, UUID
import time

# Set up GPIO
GPIO.setmode(GPIO.BCM)
GREEN_LED_PIN = 16
BLUE_LED_PIN = 20
RED_LED_PIN = 21
BUZZER_PIN = 23

# Setup LED pins as output
GPIO.setup(GREEN_LED_PIN, GPIO.OUT)
GPIO.setup(BLUE_LED_PIN, GPIO.OUT)
GPIO.setup(RED_LED_PIN, GPIO.OUT)
GPIO.setup(BUZZER_PIN, GPIO.OUT)

# Function to turn on the green LED
def turn_on_green_led():
    GPIO.output(GREEN_LED_PIN, GPIO.HIGH)
    print("Green LED turned on / OK TO KEEP REVERSING")

# Function to turn off the green LED
def turn_off_green_led():
    GPIO.output(GREEN_LED_PIN, GPIO.LOW)
    print("Green LED turned off")

# Function to turn on the blue LED
def turn_on_blue_led():
    GPIO.output(BLUE_LED_PIN, GPIO.HIGH)
    print("Blue LED turned on / SLOW DOWN ALMOST READY TO STOP")

# Function to turn off the blue LED
def turn_off_blue_led():
    GPIO.output(BLUE_LED_PIN, GPIO.LOW)
    print("Blue LED turned off")

# Function to turn on the red LED
def turn_on_red_led():
    GPIO.output(RED_LED_PIN, GPIO.HIGH)
    print("Red LED turned on / STOP REVERSING")

# Function to turn off the red LED
def turn_off_red_led():
    GPIO.output(RED_LED_PIN, GPIO.LOW)
    print("Red LED turned off")

# Function to turn off all the LEDs
def turn_off_all_leds():
    turn_off_green_led()
    turn_off_blue_led()
    turn_off_red_led()
    print("All lights turned off")

def play_buzzer(frequency, duration):
    buzzer = GPIO.PWM(BUZZER_PIN, frequency)
    buzzer.start(50)
    time.sleep(duration)
    buzzer.stop()
    time.sleep(0.2)



# Define the UUID of the Bluetooth service and characteristic
# Reference Assigned Numbers Bluetooth Documentation https://www.bluetooth.com/specifications/assigned-numbers/
SERVICE_UUID = "1824"         #Transport Discovery Service
CHARACTERISTIC_UUID = "2AF4"  #Event Statistics

def main():
    # Connects to the Arduino reverse sensor
    try:
        print("Connecting to ReverseSensor...")
        ReverseSensor = Peripheral()
        ReverseSensor.connect("D4:D4:DA:4E:63:86") #This is the MAC address of the Arduino Device.
        print("Connected to ReverseSensor")
    except Exception as e:
        print("Failed to connect to ReverseSensor:", e)
        return

    try:
        # Get the service and characteristic from the Bluetooth Arduino Reversing sensor
        service = ReverseSensor.getServiceByUUID(UUID(SERVICE_UUID))
        characteristic = service.getCharacteristics(UUID(CHARACTERISTIC_UUID))[0]

        # Main loop to read distance data
        while True:
            turn_off_all_leds();

            # Read the value of the characteristic (distance data)
            value = characteristic.read()
            distance = int.from_bytes(value, byteorder='little')

            # Print the received distance
            print("Distance:", distance, "cm")
            if distance > 10:
                turn_on_green_led()
                play_buzzer(100.00, 1.0);
            elif distance > 3:
                turn_on_blue_led()
                play_buzzer(200.00, 1.0);
            elif distance < 4:
                turn_on_red_led()
                play_buzzer(300.00, 0.5);

            # Wait 1 second between reads or reverse sensor
            time.sleep(1);
    except Exception as e:
        print("Error:", e)
    finally:
        # Disconnect from the ReverseSensor
        ReverseSensor.disconnect()
        print("Disconnected from ReverseSensor")


if __name__ == "__main__":
    # Main loop
    try:
        main()
    except KeyboardInterrupt:
        GPIO.cleanup()

