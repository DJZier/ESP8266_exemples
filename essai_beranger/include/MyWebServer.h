#ifndef MYWEBSERVER_H
#define MYWEBSERVER_H

#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"

//Creation of WebServer object
ESP8266WebServer WebServer(80);

//Network ID
const char* SSID ="OPPO A72";
const char* MDP ="berangerqtn";

//LED to drive
int LED_STATE=0;

void setup_ESP();
void setup_WebServer();
void root();
void LED_ON();
void LED_OFF();
void onGotIP(const WiFiEventStationModeGotIP event);
void onConnected(const WiFiEventStationModeConnected event);
void touchButton();

const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="fr">
    <head>
        <meta charset="UTF-8">
        <title>LED Driver</title>
    </head>
    <body>
        <h1>State of the LED</h1>
        <h2>Unknown</h2>
        <h1>LED Driver</h1>
        <a href="/LED_ON">
        <button>Turn the LED ON</button>
        </a>
        <a href="/LED_OFF">
            <button>Turn the LED OFF</button>
        </a>
    </body>
</html>
)=====";


#endif //MYWEBSERVER_H