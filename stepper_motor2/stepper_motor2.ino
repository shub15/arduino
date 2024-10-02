void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
}

void loop() {
  digitalWrite(3, HIGH);
  for (int x = 0; x < 800; x++) {
    digitalWrite(2, HIGH);
    delayMicroseconds(500);
    digitalWrite(2, LOW);
    delayMicroseconds(500);
  }
  delay(1000);
}
