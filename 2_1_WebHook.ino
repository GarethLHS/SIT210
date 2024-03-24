// GarethLHS
// Subject: SIT210 Embedded System Development
// Task2.1WebHook

#include "thingProperties.h"

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define NUM_FIELDS 2 

DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

float temp = 0;
float humid = 0;
float light = 0;
const char *apiKey = WRITE_APIKEY;

void setup() {

   // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);
  
  dht.begin();


  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
}


void loop() {
  
  ArduinoCloud.update();
  // Wait a 2 seconds between measurements.
  delay(2000);
  light = analogRead(1);

  // Reading temperature or humidity takes about 250 milliseconds!
  humid = dht.readHumidity();
  // Read temperature as Celsius
  temp = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(humid) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Prints to Serial Console
  Serial.print("Temp: "); 
  Serial.print(temp);
  Serial.print(" *C\t");
  Serial.print("Humid: "); 
  Serial.print(humid);
  Serial.print(" %\t");
  Serial.print("light: "); 
  Serial.print(light);
  Serial.println(" %");


  char servername[] = "api.thingspeak.com";
  
  if (client.connect(servername, 80)) {
    Serial.println("GET - Temp: " + String(temp) + "*C\t" + "Humid:" + String(humid));
    // Make a HTTP request:
    client.println("GET /update?api_key=" + String(apiKey) + "&field1=" + String(temp) + "&field2=" + String(humid) +"&field3=" + String(light) + " HTTP/1.0");
    client.println();
    client.flush();
  }
  
  delay(5000);

}


