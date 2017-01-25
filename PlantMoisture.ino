#include <SoftwareSerial.h>

#define MOISTURE_PIN 3
#define LED_PIN 13
#define RX_PIN 10
#define TX_PIN 11

SoftwareSerial esp8266(RX_PIN,TX_PIN);

int readMoisture(){
    int ret = analogRead(MOISTURE_PIN);
    return ret;
}

void setup() {
    Serial.begin(9600); // Setup serial through USB
    
    esp8266.begin(115200); // Initially begin at 115200 baud rate
    esp8266.print("AT+CIOBAUD=9600\n\r"); // Set baud rate to 9600
    esp8266.begin(9600); // Begin now at 9600
    
    pinMode(LED_PIN,OUTPUT); // Initialize on board LED
    digitalWrite(LED_PIN,HIGH); // Disable on board LED
}

void loop() {
  // put your main code here, to run repeatedly:
  // listen for communication from the ESP8266 and then write it to the serial monitor
   if(esp8266.available() ){
        Serial.write((char)esp8266.read());
   }
 
    // listen for user input and send it to the ESP8266
   if(Serial.available()){
          esp8266.write(Serial.read());
   }
}
