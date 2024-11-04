#include <Wire.h>
#include <ps5Controller.h>
#include <math.h>

void setup() {
  Wire.begin();
  Serial.begin(115200);
  ps5.begin("7c:66:ef:78:76:f0");
}

void loop() {
  if (ps5.isConnected()) {
    Wire.beginTransmission(8);
    int x1 = ps5.LStickX();
    int y1 = ps5.LStickY();
    int x2 = ps5.RStickX();
    int y2 = ps5.RStickY();
    int r1 = sqrt(pow(x1, 2) + pow(y1, 2));
    int theta1 = atan(y1, x1);
    int r2 = sqrt(pow(x2, 2) + pow(y2, 2));
    int theta2 = atan(y2, x2);
    // Wire.write(x1);
    // Wire.write(y1);
    // Wire.write(x2);
    // Wire.write(y2);
    // Wire.write(ps5.Circle());
    Wire.write(r1);
    Wire.write(theta1);
    Wire.write(r2);
    Wire.write(theta2);
    Serial.print(r1);
    Serial.print(" ");
    Serial.print(theta1);
    Serial.print(" ");
    Serial.print(r2);
    Serial.print(" ");
    Serial.print(theta2);
    Serial.println(" ");
    Wire.endTransmission();
    delay(100);
  }
}