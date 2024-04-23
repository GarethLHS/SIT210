
#include <Arduino.h>
#include <WiFiNINA.h>
#include <FirebaseClient.h>
#include <WiFiSSLClient.h>

#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PWD"

// The API key can be obtained from Firebase console > Project Overview > Project settings.
#define API_KEY "YOUR_API_KEY"

// User Email and password that already registerd or added in your project.
#define USER_EMAIL "ENTER_YOUR_EMAIL"
#define USER_PASSWORD "ENTER_YOUR_PASSWORD"
#define DATABASE_URL "YOUR_PROJECT_NAME-rtdb.asia-southeast1.firebasedatabase.app"

//declaring GPIO Pins for Arduino
#define LED_red A1
#define LED_blue A2
#define LED_green A3

//function prototypes
void printError(int code, const String &msg);
void asyncCB(AsyncResult &aResult);

DefaultNetwork network; // initilize with boolean parameter to enable/disable network reconnection

UserAuth user_auth(API_KEY, USER_EMAIL, USER_PASSWORD);

FirebaseApp app;

WiFiSSLClient ssl_client;

using AsyncClient = AsyncClientClass;

AsyncClient aClient(ssl_client, getNetwork(network));

RealtimeDatabase Database;


void setup()
{
  pinMode(LED_red, OUTPUT);
  pinMode(LED_green, OUTPUT);
  pinMode(LED_blue, OUTPUT);

  digitalWrite(LED_red, LOW);
  digitalWrite(LED_blue, LOW);
  digitalWrite(LED_green, LOW);

  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.printf("Firebase Client v%s\n", FIREBASE_CLIENT_VERSION);

  Serial.println("Initializing app...");


  app.setCallback(asyncCB);

  initializeApp(aClient, app, getAuth(user_auth));

  // Waits for app to be authenticated.
  // For asynchronous operation, this blocking wait can be ignored by calling app.loop() in loop().
  ms = millis();
  while (app.isInitialized() && !app.ready() && millis() - ms < 120 * 1000)
    ;

  app.getApp<RealtimeDatabase>(Database);

  Database.url(DATABASE_URL);

  Serial.println("Synchronous Get... ");


}

void loop()
{
    // This function is required for handling async operations and maintaining the authentication tasks.
    app.loop();

    // (For Async Only) This required when different AsyncClients than used in FirebaseApp assigned to the Realtime database functions.
    Database.loop();

    /*Serial.print("Get int... ");
    //TESTING reading value from firebase realtime database
    int v1 = Database.get<int>(aClient, "/test");
    if (aClient.lastError().code() == 0)
        Serial.println(v1);
    else
        printError(aClient.lastError().code(), aClient.lastError().message());
    */
    Serial.print("Get string... ");
    String v3 = Database.get<String>(aClient, "/LED");
    if (aClient.lastError().code() == 0){
        Serial.println(v3);
        if( v3 == "blue"){
            digitalWrite(LED_blue, HIGH);
            digitalWrite(LED_red, LOW);
            digitalWrite(LED_green, LOW);
        }
        else if( v3 == "red"){
            digitalWrite(LED_red, HIGH);
            digitalWrite(LED_blue, LOW);
            digitalWrite(LED_green, LOW);
        }
        else if (v3 == "green"){
            digitalWrite(LED_blue, LOW);
            digitalWrite(LED_green, HIGH);
            digitalWrite(LED_red, LOW);
        }
    }
    else
        printError(aClient.lastError().code(), aClient.lastError().message());

    

}

void asyncCB(AsyncResult &aResult)
{
    if (aResult.appEvent().code() > 0)
    {
        Firebase.printf("Event msg: %s, code: %d\n", aResult.appEvent().message().c_str(), aResult.appEvent().code());
    }

    if (aResult.isDebug())
    {
        Firebase.printf("Debug msg: %s\n", aResult.debug().c_str());
    }

    if (aResult.isError())
    {
        Firebase.printf("Error msg: %s, code: %d\n", aResult.error().message().c_str(), aResult.error().code());
    }
}

void printError(int code, const String &msg)
{
    Firebase.printf("Error, msg: %s, code: %d\n", msg.c_str(), code);
}