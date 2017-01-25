/*
 * Utilities for operating the esp8266
 * using serial AT commands from the 
 * Arduino Uno */

#include <SoftwareSerial.h>

#ifndef RX_PIN
#error RX_PIN not defined!
#endif

#ifndef TX_PIN
#error TX_PIN not defined!
#endif

#define DEFAULT_BAUD 115200

SoftwareSerial esp8266(RX_PIN,TX_PIN);

int exec(const String &str)
{
        int ret=esp8266.print(str + "\r\n");

	      return ret;
}

String readLine()
{
        String line = "";
        char c;

        while((c=esp8266.read()) != -1)
                line += c;

        return line;
}

/*
 * Default baud rate of our esp8266 is 115200
 * Hence begin communication at default baud
 * rate. Then switch to 9600.
 */
int esp_init(const int &baud)
{
        int ret;

        esp8266.begin(DEFAULT_BAUD);
        ret = exec(String("AT+CIOBAUD=") + baud);
        esp8266.begin(baud);

        delay(1000);
        
        return ret;
}

