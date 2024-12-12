const int servoPin = 9;

void setServoAngle(int angle) {
  int pulseWidth = map(angle, 0, 180, 500, 2500);

  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(servoPin, LOW);

  delay(20 - (pulseWidth / 1000));
}

void setup() {
  pinMode(servoPin, OUTPUT);
}

void loop() {
  for (int angle = 0; angle <= 180; angle += 1) {
    setServoAngle(angle);
    delay(20);
  }

  // for (int angle = 180; angle >= 0; angle -= 1) {
  //   setServoAngle(angle);
  //   delay(20);
  // }
}