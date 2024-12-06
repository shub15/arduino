#include <Wire.h>

int8_t xL;

void setup() {
  Wire.begin(7);
  Wire.onReceive(receiveEvent);
  // Wire.onRequest(requestEvent);
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}


void receiveEvent(int bytes) {
  while (Wire.available()) {
    xL = Wire.read();
    Serial.println("Received from Master: ");
    Serial.println(xL);
  }
}

void loop() {
  int speed = 0;
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  speed = map(xL, 0, 127, 0, 255);
  analogWrite(11, speed);
}