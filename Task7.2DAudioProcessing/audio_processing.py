import RPi.GPIO as GPIO
import speech_recognition as sr

# Set up GPIO
GPIO.setmode(GPIO.BCM)
GREEN_LED_PIN = 16
BLUE_LED_PIN = 20
RED_LED_PIN = 21

# Setup LED pins as output
GPIO.setup(GREEN_LED_PIN, GPIO.OUT)
GPIO.setup(BLUE_LED_PIN, GPIO.OUT)
GPIO.setup(RED_LED_PIN, GPIO.OUT)

# Function to turn on the green LED
def turn_on_green_led():
    GPIO.output(GREEN_LED_PIN, GPIO.HIGH)
    print("Green LED turned on / KITCHEN LIGHT")

# Function to turn off the green LED
def turn_off_green_led():
    GPIO.output(GREEN_LED_PIN, GPIO.LOW)
    print("Green LED turned off / KITCHEN LIGHT")

# Function to turn on the blue LED
def turn_on_blue_led():
    GPIO.output(BLUE_LED_PIN, GPIO.HIGH)
    print("Blue LED turned on / BEDROOM LIGHT")

# Function to turn off the blue LED
def turn_off_blue_led():
    GPIO.output(BLUE_LED_PIN, GPIO.LOW)
    print("Blue LED turned off / BEDROOM LIGHT")

# Function to turn on the red LED
def turn_on_red_led():
    GPIO.output(RED_LED_PIN, GPIO.HIGH)
    print("Red LED turned on / HALLWAY LIGHT")

# Function to turn off the red LED
def turn_off_red_led():
    GPIO.output(RED_LED_PIN, GPIO.LOW)
    print("Red LED turned off / HALLWAY LIGHT")

# Function to turn on all the LEDs
def turn_on_all_lights():
    turn_on_green_led()
    turn_on_blue_led()
    turn_on_red_led()
    print("All lights turned on")

# Function to turn off all the LEDs
def turn_off_all_lights():
    turn_off_green_led()
    turn_off_blue_led()
    turn_off_red_led()
    print("All lights turned off")

# Function to listen for voice commands
def listen_for_commands():
    recognizer = sr.Recognizer()
    with sr.Microphone() as source:
        print("Listening for commands...")
        recognizer.adjust_for_ambient_noise(source)
        audio = recognizer.listen(source)

    try:
        command = recognizer.recognize_google(audio)
        print("Command:", command)
        if "turn on kitchen light" in command:
            turn_on_green_led()
        elif "turn off kitchen light" in command:
            turn_off_green_led()
        elif "turn on bedroom light" in command:
            turn_on_blue_led()
        elif "turn off bedroom light" in command:
            turn_off_blue_led()
        elif "turn on hallway light" in command:
            turn_on_red_led()
        elif "turn off hallway light" in command:
            turn_off_red_led()
        elif "turn on all lights" in command:
            turn_on_all_lights()
        elif "turn off all lights" in command:
            turn_off_all_lights()
        else:
            print("Command not recognized")
    except sr.UnknownValueError:
        print("Could not understand audio")
    except sr.RequestError as e:
        print("Could not request results from Google Speech Recognition service; {0}".format(e))

# Main loop
try:
    while True:
        listen_for_commands()
except KeyboardInterrupt:
    GPIO.cleanup()

