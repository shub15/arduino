#include <Wire.h>

void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
}

void loop() {
  delay(100);
}

void receiveEvent(int bytes) {
  while (Wire.available()) {
    int8_t x1 = Wire.read();
    int8_t y1 = Wire.read();
    int8_t x2 = Wire.read();
    int8_t y2 = Wire.read();
    int8_t circle = Wire.read();
    // Serial.print("Joystick L X: ");
    // Serial.println(x1); 
    // Serial.print("Joystick R Y: ");
    // Serial.println(y2);
    Serial.print(x1);
    Serial.print(" ");
    Serial.print(y1);
    Serial.print(" ");
    Serial.print(x2);
    Serial.print(" ");
    Serial.print(y2);
    Serial.print(" ");
    Serial.print(circle);
    Serial.println(" ");
  }
}
