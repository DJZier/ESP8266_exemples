#include "MyWebServer.h"




void setup_ESP(){
      // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("");
  pinMode(16,OUTPUT);
  digitalWrite(16,HIGH);
  
}

void setup_WebServer(){
//Mode de Connexion : Station 
  WiFi.mode(WIFI_STA);
  //Démarrage de connexion Wifi
  WiFi.begin(SSID,MDP);

  static WiFiEventHandler onConnectedHandler = WiFi.onStationModeConnected(onConnected);
  static WiFiEventHandler onGotIPHandler = WiFi.onStationModeGotIP(onGotIP);

  //Mise en place du Serveur Web
  WebServer.on("/LED_ON", LED_ON);
  WebServer.on("/LED_OFF", LED_OFF);
  WebServer.on("/",root);
  WebServer.begin();

}

void LED_ON(){
  digitalWrite(16,HIGH);
  LED_STATE=1;
  root();
}
void LED_OFF(){
  digitalWrite(16,LOW);
  LED_STATE=0;
  root();
}

void root(){
  String temp(reinterpret_cast<const __FlashStringHelper *>(index_html));
  if (digitalRead(16)==HIGH)
    temp.replace("%LED%","LED Allumée");
  else
    temp.replace("%LED%","LED Allumée");

  WebServer.send(200, "text/html",index_html);
}

void onConnected(const WiFiEventStationModeConnected event){
  Serial.println("Connecté au réseau WiFi");
}

void onGotIP(const WiFiEventStationModeGotIP event){
    Serial.println("IP : ");
    Serial.println(WiFi.localIP());
    Serial.println("Network Speed :");
    Serial.println(WiFi.RSSI());
}

void touchButton(){
  if (digitalRead(0)==HIGH)
    Serial.println("You pushed");
    delay(200);
}