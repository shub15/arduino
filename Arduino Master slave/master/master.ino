#include <Wire.h>

int8_t xL, xR, yL, yR, circle;

void setup() {
  Wire.begin();
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
}

void receiveEvent(int bytes) {
  while (Wire.available()) {
    xL = Wire.read();
    yL = Wire.read();
    xR = Wire.read();
    yR = Wire.read();
    circle = Wire.read();
    Serial.println(xL);
  }
}

void loop() {  
  // Serial.println("Sending data to slave...");
  // delay(100);

  Wire.beginTransmission(7);
  Wire.write(xL);
  Wire.endTransmission();
  delay(100);

  // Wire.requestFrom(7, 13);
  // while (Wire.available()) {
  //   int8_t c = Wire.read();
  //   Serial.print(c);
  //   delay(100);
  // }
  // Serial.println();
}