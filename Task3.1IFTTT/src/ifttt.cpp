#include <SPI.h>
#include <Arduino.h>

#include <Wire.h>
#include <ArtronShop_BH1750.h>

#include "arduino_secrets.h"
#include "thingProperties.h"


ArtronShop_BH1750 bh1750(0x23, &Wire); // Non Jump ADDR: 0x23, Jump ADDR: 0x5C
void IFTTT_Webhook_Sunlight(char* value);

WiFiSSLClient client;


bool start_msg = false;
bool stop_msg = true;
bool sunlight = false;

void setup() {

   // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);
  

  Wire.begin();
    while (!bh1750.begin()) {
      Serial.println("BH1750 not found !");
      delay(1000);
    }

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
  delay(500);
  
  float light = bh1750.light();
  Serial.print("Light: ");
  Serial.print(light);
  Serial.print(" lx");
  Serial.println();
  delay(1000);
  

  if(light > 20000.00){
    sunlight = true;

    if (stop_msg){
      //send one start message
      Serial.println("IFTT TRIGGER START SUNLIGHT");
      IFTTT_Webhook_Sunlight("Sun_Up");
      start_msg = true;
      stop_msg = false;
    }
  }else{
      sunlight = false;
      if(start_msg){
        //send one start message
        Serial.println("IFTT TRIGGER STOP SUNLIGHT");
        IFTTT_Webhook_Sunlight("Sun_Down");
        stop_msg = true;
        start_msg = false;
      }
  }
  
  
  delay(500);

}


void IFTTT_Webhook_Sunlight(char* value){

  char servername[] = "maker.ifttt.com";
    if (client.connectSSL(servername, 443)) {
      // Make a HTTP request:
      
      Serial.println("Trigger GET Request");
      client.print("GET /trigger/");
      client.print(IFTTT_Event);
      client.print("/with/key/");
      client.print(SECRET_KEY);
      client.print("?value1=");
      client.print(value);
      client.println(" HTTP/1.0");
      client.println("Host: " + String(servername));
      client.println("Connection: close");
      client.println();
      client.flush();
    
  }
  
  return ;

}
