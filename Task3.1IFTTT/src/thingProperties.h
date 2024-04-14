// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include <utility/wifi_drv.h>
#include "SPI.h"
#include <ArduinoHttpClient.h>

const char SSID[]         = SECRET_SSID;    // Network SSID (name)
const char PASS[]         = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)
const char KEY[]          = SECRET_KEY; 
const char IFTTT_Event[]  = SECRET_IFTTT_Event;

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);