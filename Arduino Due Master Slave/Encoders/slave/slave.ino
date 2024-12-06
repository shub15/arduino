#include <Wire.h>

volatile long c = 0;
int8_t circle;

void setup() {
  Wire.begin(7);
  Wire.onReceive(receiveEvent);
  // Wire.onRequest(requestEvent);
  Serial.begin(115200);
}

void loop() {
}

void receiveEvent(int bytes) {
  while (Wire.available()) {
    long highByte = Wire.read();
    long lowByte = Wire.read();
    c = (highByte << 8) | lowByte;
    Serial.print("received ");
    Serial.println(c);
  }
}

// void requestEvent() {
//   Wire.write("Hello, Master");
// }