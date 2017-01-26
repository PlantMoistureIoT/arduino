#define MOISTURE_PIN 3
#define LED_PIN 13
#define RX_PIN 10
#define TX_PIN 11

#include "esp8266.h"

int readMoisture()
{
        int ret = analogRead(MOISTURE_PIN);
        return ret;
}

void setup()
{
        Serial.begin(9600); // Setup serial through USB

        esp_init(9600);

        pinMode(LED_PIN,OUTPUT); // Initialize on board LED
        digitalWrite(LED_PIN,LOW); // Disable on board LED
}

void loop()
{
        if(esp8266.available()) {
                Serial.write((char)esp8266.read());
        }

        if(Serial.available()) {
                esp8266.write(Serial.read());
        }
}
