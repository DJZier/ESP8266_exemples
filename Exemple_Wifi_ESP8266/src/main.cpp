#include <Arduino.h>
#include "ESP8266WiFi.h"

#define PIN_LED_ROUGE 5


const char * SSID = "SFR_EAC0";
const char * PASSWORD = "gaz_de_shciste";



void setup() {
  //mise en place d'une lisaison série:
  Serial.begin(115200);
  Serial.println("");

  // mode de connection:
  WiFi.mode(WIFI_STA);

  //Démarrage de la connection:
  WiFi.begin(SSID, PASSWORD);

  //configuration des E/S
  pinMode(PIN_LED_ROUGE, OUTPUT);

}

void loop() {
  // Si l'objet est connecté au réseau, on effectue les tâches qui doivent l'être dans ce cas:

  if (WiFi.isConnected()){
    digitalWrite(PIN_LED_ROUGE, HIGH);
    Serial.println("adresse IP : " + WiFi.localIP().toString());
    Serial.println("adresse passerelle (gateway) : " + WiFi.gatewayIP().toString());
    Serial.println("adresse DNS : " + WiFi.dnsIP().toString());
    Serial.print("Puissance de réception du signal : " );
    Serial.println(WiFi.RSSI());
  }
  else {
    digitalWrite(PIN_LED_ROUGE, LOW);
  }

}