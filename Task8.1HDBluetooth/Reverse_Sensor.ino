#include <ArduinoBLE.h>
#include <Ultrasonic.h>

#define TRIGGER_PIN  14
#define ECHO_PIN     13
#define BAUD_RATE    9600

// Bluetooth® Low Energy Reverse sensor Service Transport Discovery Service
BLEService ReverseSensorService("1824");

// Bluetooth® Low Energy Distance Characteristic Event Statistic
BLEUnsignedCharCharacteristic DistanceChar("2AF4", BLERead | BLENotify);


int oldDistance = 0;  // last distance reading from ultrasonic sensor
long previousMillis = 0;  // last time the distance was checked, in ms

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN); // Define ultrasonic sensor

void setup() {
  Serial.begin(BAUD_RATE);
  while (!Serial);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  }

  BLE.setLocalName("ReverseSensorService");
  BLE.setAdvertisedService(ReverseSensorService);
  ReverseSensorService.addCharacteristic(DistanceChar);
  BLE.addService(ReverseSensorService);
  DistanceChar.writeValue(oldDistance);

  BLE.advertise();
  
  Serial.println("Bluetooth® device active, waiting for connections...");
}

void loop() {
  BLEDevice central = BLE.central();
  Serial.println("starting main loop");
  Serial.print("Ultrasonic sensor distance in cm: ");
  Serial.println(ultrasonic.read());
  delay(1000);
  
  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());

    digitalWrite(LED_BUILTIN, HIGH);

    while (central.connected()) {
      long currentMillis = millis();

      if (currentMillis - previousMillis >= 200) {
        previousMillis = currentMillis;
        updateDistance();
      }
    }

    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}

void updateDistance() {
  int distance = ultrasonic.read();
  
  if (distance != oldDistance) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    DistanceChar.writeValue(distance);
    oldDistance = distance;
  }
}
