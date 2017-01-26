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

int exec(char buf[])
{
        strcat(buf,"\r\n");
        int ret=esp8266.write(buf,strlen(buf));

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

        char buf[20] = "AT+CIOBAUD=";
        char baud_str[8];
        itoa(baud,baud_str,10);
        strcat(buf,baud_str);

        ret = exec(buf);
        esp8266.begin(baud);

        delay(1000);

        return ret;
}

