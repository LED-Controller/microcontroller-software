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
}
