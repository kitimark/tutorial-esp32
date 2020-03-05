#include <Arduino.h>
#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

const char* ssid     = "3BB_PANAT_plus";
const char* password = "0828923625";

// WiFiServer server(80);

AsyncWebServer server(81);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  WiFi.begin(ssid,password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connnected...");

  Serial.println(WiFi.localIP()); 

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false);
  });

  server.on("/26/on", HTTP_GET, [](AsyncWebServerRequest *request){
    // request->send(SPIFFS, "/index.html", String(), false);
    char* res = "PORT 26 ON";
    // TODO: logic
    
    request->send(200, String(), res);
  });

  server.on("/26/off", HTTP_GET, [](AsyncWebServerRequest *request){
    // request->send(SPIFFS, "/index.html", String(), false);
    char* res = "PORT 26 OFF";
    // TODO: logic

    request->send(200, String(), res);
  });
 
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
}