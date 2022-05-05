#include "VERSION.h"
#include "WIFI_CREDENTIALS.h"
#include <ESP8266WiFi.h>

#define BUTTON D0

WiFiClient client;

void sendToServer(String data) {
  Serial.print("Send to server: ");
  Serial.println(data);

  client.println(data);
  client.flush();
}

unsigned long lastPing = millis();
String uuid;

#include "ColorManager.h"
#include "EffectManager.h"
#include "DataHandler.h"
#include "TestMode.h"

void error(String msg) {
  Serial.println(msg);
  fillStatus(STATUS_RED);
  delay(2000);
  ESP.restart();
}

void setup() {
  setupColorManager();
  uuid = WiFi.macAddress();
  
  delay(1000);

  String nameHost = "LED-";
  nameHost.concat(uuid);
  
  Serial.begin(115200);
  Serial.println("");
  Serial.println(nameHost);

  pinMode(BUTTON, INPUT);
  if(digitalRead(BUTTON) == HIGH) {
    Serial.println("TEST-MODE");
    WiFi.mode(WIFI_OFF);
  
    testColors();
    yield();
    updateColor(255, 0, 0, 0);
    runTestMode();
  } else {
    WiFi.hostname(nameHost);
    WiFi.begin(S_WIFI_SSID, S_WIFI_PASS);

    fadeIn(STATUS_BLUE);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      fadeOut(STATUS_BLUE);
      fadeIn(STATUS_BLUE);
    }
    
    Serial.println("WiFi connected");
   
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  
    Serial.print("try to connect... ");
    if (client.connect(HOST, PORT)) {
      Serial.println("OK");
      String registerSend = "REG ";
      registerSend.concat(uuid);
      sendToServer(registerSend);
    } else {
      error("Server down");
    }
  }
}


void loop() {
  colorLoop();
  effectLoop();
  
  if((millis() - lastPing) > (75 * 1000)) {
    error("timeout");
  }

  if(client.available()) {
    boolean finish = false;
    String result = "";
    unsigned long timeout = millis();
    while(!finish && ((millis() - timeout) < 5000)) {
      while (!finish && client.available()) {
        char c = static_cast<char>(client.read());
        if(c != '\n') {
          result.concat(c);
        } else {
          finish = true;
        }
        yield();
      }
      yield();
    }
    if(finish) {
      Serial.println(result);
      handleData(result);
    }
    yield();
  }
}
