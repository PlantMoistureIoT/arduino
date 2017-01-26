/* Arduino Moisture Sensing Code
 * Copyright (C) 2016 Madhav Kanbur
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/> */

#define MOISTURE_PIN 3
#define LED_PIN 13
#define RX_PIN 10
#define TX_PIN 11

#define API_KEY "api_key_here"
#define FIELD "field1"

#define DELAY_INTERVAL 15000

#include "esp8266.h"

int readMoisture()
{
        int ret = analogRead(MOISTURE_PIN);
        return ret;
}

void postData(const int& val)
{
        char cmd[256];

        strcpy(cmd,"AT+CIPSTART=\"TCP\",\"184.106.153.149\",80");
        exec(cmd);
        delay(2000);

        strcpy(cmd,"AT+CIPSEND=50");
        exec(cmd);
        delay(1200);

        strcpy(cmd,"GET /update?api_key=" API_KEY "&" FIELD "=");
        char val_str[6];
        itoa(val,val_str,10);
        strcat(cmd,val_str);
        exec(cmd);
        delay(1000);
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
        int moisture = readMoisture();
        Serial.println(moisture);
        postData(moisture);
        delay(DELAY_INTERVAL);
}
