#include <Arduino.h>
#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include <iostream>

using namespace std;

#define PIN_LED_ROUGE 5
#define PIN_LED_VERTE 4

const char * SSID = "SFR_EAC0";
const char * PASSWORD = "gaz_de_shciste";


//Gestion des évènements du Wifi
//Lorsque la connection vient d'aboutir
void onConnected(const WiFiEventStationModeConnected& event);
//Lorsque l'adresse IP est ditribuée
void onGotIP(const WiFiEventStationModeGotIP& event);

//Objet WebServer
ESP8266WebServer serverWeb(80);

//Fonctions du serveur web

void switchLedOn(){
  digitalWrite(PIN_LED_VERTE, HIGH);
  serverWeb.send(200, "text/html", "Led on");
}
void switchLedOff(){
  digitalWrite(PIN_LED_VERTE, LOW);
  serverWeb.send(200, "text/html", "Led off");
}
void handlerRoot(){
  serverWeb.send(200, "text/html", "Page principale");
}





void setup() {
  //mise en place d'une lisaison série:
  Serial.begin(9600);
  Serial.println("");

  // mode de connection:
  WiFi.mode(WIFI_STA);

  //Démarrage de la connection:
  WiFi.begin(SSID, PASSWORD);
  static WiFiEventHandler onConnectedHandler = WiFi.onStationModeConnected(onConnected);
  static WiFiEventHandler onGotIPHandler = WiFi.onStationModeGotIP(onGotIP);

  //mise en place du serveur WebServer
  serverWeb.on("/switchLedOn", switchLedOn);
  serverWeb.on("/switchLedOff", switchLedOff);
  serverWeb.on("/", handlerRoot);
  serverWeb.begin();


  //configuration des E/S
  pinMode(PIN_LED_ROUGE, OUTPUT);
  pinMode(PIN_LED_VERTE, OUTPUT);

}

void loop() {
  // Si l'objet est connecté au réseau, on effectue les tâches qui doivent l'être dans ce cas:  

  if (WiFi.isConnected()){
    digitalWrite(PIN_LED_ROUGE, HIGH);
    serverWeb.handleClient();
  }
  else {
    digitalWrite(PIN_LED_ROUGE, LOW);
  }
}

void onConnected(const WiFiEventStationModeConnected& event){
  Serial.println("Wifi connectée");
  Serial.println("adresse IP : " + WiFi.localIP().toString());
}


void onGotIP(const WiFiEventStationModeGotIP& event){
  //cout << "adresse IP : " << WiFi.localIP().toString() << endl;
  Serial.println("adresse IP : " + WiFi.localIP().toString());
  Serial.println("adresse passerelle (gateway) : " + WiFi.gatewayIP().toString());
  Serial.println("adresse DNS : " + WiFi.dnsIP().toString());
  Serial.print("Puissance de réception du signal : " );
  Serial.println(WiFi.RSSI());
}