#include <Arduino.h>
#include "MyWebServer.h"

void setup() {
  // put your setup code here, to run once:
  setup_ESP();
  setup_WebServer();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.isConnected())
    WebServer.handleClient();
  touchButton();
}