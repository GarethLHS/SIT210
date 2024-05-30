import paho.mqtt.client as mqtt
import RPi.GPIO as GPIO
import time


# GPIO pin for the LED
LED_PIN = 21

channel_ID = "2482749"

# The hostname of the ThingSpeak MQTT broker.
mqtt_host = "mqtt3.thingspeak.com"

# Your MQTT credentials for the device
mqtt_client_ID = "KggtIxUzNg4RJQ49GyUnFw0"
mqtt_username = "KggtIxUzNg4RJQ49GyUnFw0"
mqtt_password = "h8voyNkF1v4COtNqQuCTj2XT"

# https://au.mathworks.com/help/thingspeak/mqtt-basics.html
# Callback function to handle connection
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    # Subscribe to the channel's MQTT topic upon connection
    client.subscribe("channels/2482749/subscribe/fields/field3") #Bucket empty or not


# Callback function to handle message received
def on_message(client, userdata, msg):
    #if msg.topic == "field3":
        # Check if the message indicates turning on or off
    if msg.payload.decode() == "1":
        print("BUCKET IS EMPTY")
        print("Turning LED on")
        GPIO.output(LED_PIN, GPIO.HIGH)
        time.sleep(1)
        GPIO.output(LED_PIN, GPIO.LOW)
        time.sleep(1)
        GPIO.output(LED_PIN, GPIO.HIGH)
        time.sleep(1)
        GPIO.output(LED_PIN, GPIO.LOW)
        time.sleep(1)
        GPIO.output(LED_PIN, GPIO.HIGH)
    elif msg.payload.decode() == "0":
        print("BUCKET IS FULL")
        print("Turning LED off")
        GPIO.output(LED_PIN, GPIO.LOW)

try:
    # Set up GPIO
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(LED_PIN, GPIO.OUT)

    # Create an MQTT client instance
    client = mqtt.Client(client_id=mqtt_client_ID)

    # Set the username and password for the MQTT client
    client.username_pw_set(username=mqtt_username, password=mqtt_password)

    # Set the callbacks
    client.on_connect = on_connect
    client.on_message = on_message

    # Connect to the MQTT broker
    client.connect(mqtt_host, 1883, 60)

    # Start the MQTT client loop
    client.loop_forever()

except KeyboardInterrupt:
    print("Exiting due to keyboard interrupt")

except Exception as e:
    print("An error occurred:", str(e))

finally:
    # Clean up GPIO
    GPIO.cleanup()
