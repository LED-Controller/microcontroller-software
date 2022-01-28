#define STATUS_BLUE D3
#define STATUS_RED D8
#define STATUS_GREEN D7


void setup() {
  Serial.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(STATUS_BLUE, OUTPUT);
  pinMode(STATUS_RED, OUTPUT);
  pinMode(STATUS_GREEN, OUTPUT);

  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);

  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);

  pinMode(D0, OUTPUT);
  digitalWrite(D0, HIGH);
  
  
  

  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);


  digitalWrite(STATUS_BLUE, HIGH);
  delay(500);
  for(int i = 255; i >= 0; i--) {
    Serial.println(i);
    analogWrite(STATUS_BLUE, i);
    delay(25);
  }
  digitalWrite(STATUS_BLUE, LOW);

  delay(1000);
  for(int i = 0; i <= 255; i++) {
    Serial.println(i);
    analogWrite(STATUS_BLUE, i);
    delay(25);
  }

  digitalWrite(STATUS_BLUE, HIGH);
    
}

unsigned long lastChange = millis();
boolean lastOn = true;

void loop() {
  
  digitalWrite(STATUS_GREEN, LOW);
  digitalWrite(STATUS_RED, LOW);
  digitalWrite(STATUS_BLUE, HIGH);
  
  allOff();

  digitalWrite(STATUS_BLUE, LOW);
  digitalWrite(STATUS_RED, HIGH);
  while(digitalRead(D0) == HIGH) {
    yield();
  }
  Serial.println("BTN");
  
  digitalWrite(STATUS_GREEN, LOW);
  digitalWrite(STATUS_RED, LOW);
  digitalWrite(STATUS_BLUE, HIGH);
  allOn();
  digitalWrite(STATUS_BLUE, LOW);
  digitalWrite(STATUS_GREEN, HIGH);

  while(digitalRead(D0) == HIGH) {
    yield();
  }
  Serial.println("BTN");
  
}


void allOff() {
  for(int i = 255; i >= 0; i--) {
    analogWrite(D2, i); 
    delay(10);
  }
  for(int i = 255; i >= 0; i--) {
    analogWrite(D1, i);
    delay(10);
  }
  for(int i = 255; i >= 0; i--) {
    analogWrite(D6, i);
    delay(10);
  }
  for(int i = 255; i >= 0; i--) {
    analogWrite(D5, i);
    delay(10);
  }
}

void allOn() {
  for(int i = 0; i <= 255; i++) {
    analogWrite(D5, i);
    delay(10);
  }
  for(int i = 0; i <= 255; i++) {
    analogWrite(D6, i);
    delay(10);
  }
  for(int i = 0; i <= 255; i++) {
    analogWrite(D1, i);
    delay(10);
  }
  for(int i = 0; i <= 255; i++) {
    analogWrite(D2, i);
    delay(10);
  }
  
}
