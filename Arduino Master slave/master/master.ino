#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Serial.println("Sending data to Slave...");
  
  Wire.beginTransmission(8);
  Wire.write("Hello, Slave");
  Wire.endTransmission();
  
  delay(500);
  
  Wire.requestFrom(8, 32);
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println();
  
  delay(2000);
}
