#define STATUS_BLUE D3
#define STATUS_RED D8
#define STATUS_GREEN D7

void setupColorManager() {
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(STATUS_BLUE, OUTPUT);
  pinMode(STATUS_RED, OUTPUT);
  pinMode(STATUS_GREEN, OUTPUT);

  digitalWrite(STATUS_BLUE, LOW);
  digitalWrite(STATUS_RED, LOW);
  digitalWrite(STATUS_GREEN, LOW);
  
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);

  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
}


void randomColor() {
  analogWrite(D5, random(0, 255));
  analogWrite(D6, random(0, 255));
  analogWrite(D1, random(0, 255));
  analogWrite(D2, random(0, 255));
}
