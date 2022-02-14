#include "VERSION.h"
#include "PRIVATE.h"

#include <ESP8266WiFi.h>

WiFiClient client;
const char* HOST = "192.168.21.25";
const uint16_t PORT = 18533;

String uuid;

void setup() {
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
  }

}

unsigned long lastPing = millis();

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
      if(result == "ping") {
        client.println("pong");
        lastPing = millis();
      }
    }
    yield();
  }
}
