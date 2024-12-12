#include <Wire.h>
#include <ps5Controller.h>

void setup() {
  Wire.begin(8);
  Serial.begin(115200);
  // ps5.begin("7c:66:ef:78:76:f0");
  ps5.begin("e8:47:3a:5a:a3:66");
}

void loop() {
  if (ps5.isConnected()) {
    Wire.beginTransmission(8);
    Wire.write(ps5.Circle());
    Wire.endTransmission();
  }
}