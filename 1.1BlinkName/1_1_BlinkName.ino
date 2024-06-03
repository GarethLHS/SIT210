#include <Arduino.h>

struct KeyValue {
    char key;
    const char *value;
};

struct KeyValue moorse_code[] = {
    {'A', ".-"},
    {'B', "-..."},
    {'C', "-.-."},
    {'D', "-.."},
    {'E', "."},
    {'F', "..-."},
    {'G', "--."},
    {'H', "...."},
    {'I', ".."},
    {'J', ".---"},
    {'K', "-.-"},
    {'L', ".-.."},
    {'M', "--"},
    {'N', "-."},
    {'O', "---"},
    {'P', ".--."},
    {'Q', "--.-"},
    {'R', ".-."},
    {'S', "..."},
    {'T', "-"},
    {'U', "..-"},
    {'V', "...-"},
    {'W', ".--"},
    {'X', "-..-"},
    {'Y', "-.--"},
    {'Z', "--.."}
};

const int ledPin = 13; // LED connected to digital pin 13

void blinkMorseCode(const char *morse) {
    for (int i = 0; morse[i] != '\0'; ++i) {
        if (morse[i] == '.') {
            digitalWrite(ledPin, HIGH);
            delay(250); // Dot duration
            digitalWrite(ledPin, LOW);
            delay(250); // Inter-element spacing
        } else if (morse[i] == '-') {
            digitalWrite(ledPin, HIGH);
            delay(750); // Dash duration
            digitalWrite(ledPin, LOW);
            delay(250); // Inter-element spacing
        } else if (morse[i] == ' ') {
            delay(750); // Inter-character spacing
        }
    }
}

void setup() {
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
    while (!Serial) {
        ; // Wait for serial port to connect.
    }
    delay(1000);
    Serial.println("Morse Code Mapping:");
    for (const auto &kv : moorse_code) {
        Serial.print("[");
        Serial.print(kv.key);
        Serial.print("]\t");
        Serial.println(kv.value);
    }

    Serial.println("\nMorse Code for 'GARETH':");
    const char *garethMorse = "GARETH";
    blinkMorseCode(garethMorse);
}

void loop() {
    // Nothing to do here
}
