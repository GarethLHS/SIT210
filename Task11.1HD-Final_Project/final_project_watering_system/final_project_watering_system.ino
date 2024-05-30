#include "arduino_secrets.h"
#include "thingProperties.h"

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define NUM_FIELDS 2 

DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;
WiFiSSLClient client2; // used for IFTT we calls.

bool IFTT_message_sent = false;

//Function proptypes for IFTT Calls
void IFTT_WaterLOW();
void IFTT_BatteryLOW();

const int AirValue = 891;
const int WaterValue = 350;
int intervals = (AirValue - WaterValue)/3;
int soilMoistureValue = 0;

int Float_Switch_pin = A2;
//int Voltage_pin = A3;
int floatSwitchState = 0;

float temp = 0;
float humid = 0;
float voltage = 12.9000;

const char *apiKey = WRITE_APIKEY;

void setup() {

   // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);
  
  dht.begin();

  pinMode(Float_Switch_pin, INPUT);
  //pinMode(Voltage_pin, INPUT); 

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

  pinMode(3, OUTPUT); //Pin 3 is Water pump relay
  
}


void loop() {
  
  ArduinoCloud.update();
  
  // Reading temperature or humidity takes about 250 milliseconds!
  humid = dht.readHumidity();
  // Read temperature as Celsius
  temp = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(humid) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  soilMoistureValue = analogRead(A1);

  voltage = voltage - 00.001;  //simulated voltage draw ove time
  if (voltage < 10.00 ){
    IFTT_BatteryLOW();      // IFTT email Alert sent to charge battery manually or replace the battery
  }
  // Prints to Serial Console
  Serial.print("Temp: "); 
  Serial.print(temp);
  Serial.print(" *C\t");
  Serial.print("Humid: "); 
  Serial.print(humid);
  Serial.print(" %\t");
  Serial.print(voltage);
  Serial.print(" volts\t");
  Serial.print("Moisture sensor: ");
  Serial.print(soilMoistureValue); 

  floatSwitchState = digitalRead(Float_Switch_pin);

  if(floatSwitchState) 
  {
    digitalWrite(3, HIGH);
    Serial.println("\tFloat Switch OFF - Water bucket empty");
    IFTT_WaterLOW();
  }
  else
  {
    Serial.print("\tFloat Switch ON - Water bucket full\t");

    if(soilMoistureValue > WaterValue && soilMoistureValue < (WaterValue + intervals))
    {
      Serial.println("Very Wet - No Need to Water");
      digitalWrite(3, HIGH);
    }
    else if(soilMoistureValue > (WaterValue + intervals) && soilMoistureValue < (AirValue - intervals))
    {
      Serial.println("Wet  - No Need to Water");
      digitalWrite(3, HIGH);
    }
    else if(soilMoistureValue < AirValue && soilMoistureValue > (AirValue - intervals))
    {
      Serial.println("Soil is Dry Automatic watering started ");

      digitalWrite(3, LOW);
    }
    
    if(IFTT_message_sent)
    {
      IFTT_message_sent = false;
    }

  }


  char servername[] = "api.thingspeak.com";
  
  if (client.connect(servername, 80)) {
    
    // Make a HTTP request:
    client.println("GET /update?api_key=" + String(apiKey) + "&field1=" + String(temp) + "&field2=" + String(humid) +"&field3=" + String(floatSwitchState) +"&field4=" + String(soilMoistureValue) +"&field5=" + String(voltage)  + " HTTP/1.0");
    client.println();
    client.flush();
  }
  
  delay(5000);

}

void IFTT_BatteryLOW(){

  if(!IFTT_message_sent)
  {
    IFTT_message_sent = true;

    // If there's a successful connection
    if (client2.connectSSL("maker.ifttt.com", 443)){
      // Send HTTP request
      client2.println("GET /trigger/Battery LOW/with/key/<replace with your key>");
      client2.println(" HTTP/1.0");
      client2.println("Host: maker.ifttt.com");
      client2.println("Connection: close");
      client2.println();
      client2.flush();

      // Wait for the server's response
      while (client2.connected()) {
        if (client2.available()) {
          char c = client2.read();
          Serial.print(c); // Print response to serial monitor
        }
      }

      // Close the connection
      client2.stop();
    } else {
      // If connection failed, print an error message
      Serial.println("Connection failed");
    }
  }
}

void IFTT_WaterLOW(){
  
  if(!IFTT_message_sent)
  {
    IFTT_message_sent = true;
  
    //https://maker.ifttt.com/trigger/Water LOW Balcony/with/key/<replace with your key>

    Serial.println("IFTT Triger email - Water LOW");

    if (client2.connectSSL("maker.ifttt.com", 443)) {
      // Send HTTP request
      // Send HTTP request
      client2.println("GET /trigger/Water LOW Balcony/with/key/<replace with your key> HTTP/1.1");
      client2.println("Host: maker.ifttt.com");
      client2.println("Connection: close");
      client2.println();
      client2.flush();

      //Wait for the server's response The code below will print the response for the IFTT server used for troublshooting
      /*while (client2.connected())
      {
        if (client2.available())
        {
          char c = client2.read();
          Serial.print(c); // Print response to serial monitor
        }
      } 
      */
        // Close the connection
      //client2.stop();
      //else {
      // If connection failed, print an error message
      //Serial.println("Connection failed");

    }

  }

}

