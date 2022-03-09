#include <Adafruit_NeoPixel.h>

#define LED_COUNT 60
#define LED_PIN    D4
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


#define STATUS_BLUE D3
#define STATUS_RED D8
#define STATUS_GREEN D7

#define COLOR_R D6
#define COLOR_G D2
#define COLOR_B D1
#define COLOR_W D5

void updateColor(int r, int g, int b, int w) {
  Serial.print("R: ");
  Serial.print(r);
  Serial.print(", G: ");
  Serial.print(g);
  Serial.print(", B: ");
  Serial.print(b);
  Serial.print(", W: ");
  Serial.println(w);
  
  analogWrite(COLOR_R, r);
  analogWrite(COLOR_G, g);
  analogWrite(COLOR_B, b);
  analogWrite(COLOR_W, w);
}

void neoFill(int r, int g, int b) {
  uint32_t color = strip.Color(r, g, b);
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

void setupColorManager() {  
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(STATUS_BLUE, OUTPUT);
  pinMode(STATUS_RED, OUTPUT);
  pinMode(STATUS_GREEN, OUTPUT);

  digitalWrite(STATUS_BLUE, LOW);
  digitalWrite(STATUS_RED, LOW);
  digitalWrite(STATUS_GREEN, LOW);

  pinMode(COLOR_R, OUTPUT);
  pinMode(COLOR_G, OUTPUT);
  pinMode(COLOR_B, OUTPUT);
  pinMode(COLOR_W, OUTPUT);

  updateColor(0, 0, 0, 0);

  strip.begin();
  strip.show();
  strip.setBrightness(50);
  neoFill(0, 0, 0);
}

void fadeIn(int port) {
  for(int i = 0; i < 100; i++) {
    analogWrite(port, i);
    delay(5);
  }
}

void fadeOut(int port) {
  for(int i = 100; i > 0; i--) {
    analogWrite(port, i);
    delay(5);
  }
}

void clearStatus() {
  digitalWrite(STATUS_BLUE, LOW);
  digitalWrite(STATUS_RED, LOW);
  digitalWrite(STATUS_GREEN, LOW);
}

void fillStatus(int port) {
  clearStatus();
  digitalWrite(port, HIGH);
}

unsigned long welcome = 0;

void welcomeColor() {
  fillStatus(STATUS_GREEN);
  welcome = millis();
}

void colorLoop() {
  if(welcome != 0) {
    if((millis() - welcome) > 2000) {
      welcome = 0;
      if(digitalRead(STATUS_GREEN) == HIGH) {
        clearStatus();
      }
    }
  }
}

void testColors() {
  for(int i = 0; i < 20; i++) {
    digitalWrite(STATUS_BLUE, HIGH);
    delay(100);
    digitalWrite(STATUS_BLUE, LOW);
    digitalWrite(STATUS_RED, HIGH);
    delay(100);
    digitalWrite(STATUS_RED, LOW);
    digitalWrite(STATUS_GREEN, HIGH);
    delay(100);
    digitalWrite(STATUS_GREEN, LOW);
  }
}
