#include "VERSION.h"
#include "WIFI_CREDENTIALS.h"
#include <ESP8266WiFi.h>

WiFiClient client;
unsigned long lastPing = millis();
String uuid;

#include "ColorManager.h"
#include "DataHandler.h"


void setup() {
  setupColorManager();
  uuid = WiFi.macAddress();
  
  Serial.begin(115200);
  
  delay(1000);

  Serial.println("");
  Serial.println("LED-Controller");
 
  WiFi.hostname("LED-Controller");
  WiFi.begin(S_WIFI_SSID, S_WIFI_PASS);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
 
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  if (client.connect(HOST, PORT)) {
    client.print("REGISTER ");
    client.println(uuid);
  } else {
    Serial.println("Server down?");
  }
}

void loop() {
  while(true) {
    if((millis() - lastPing) > 20000) {
      Serial.println("timeout");
      ESP.restart();
    }
    
    boolean finish = false;
    String result = "";
    unsigned long timeout = millis();
    while(!finish && ((millis() - timeout) < 5000)) {
      while (client.available()) {
        char c = static_cast<char>(client.read());
        if(c != '\n') {
          result.concat(c);
        } else {
          finish = true;
          break;
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
