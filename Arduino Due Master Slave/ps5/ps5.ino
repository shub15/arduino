#include <Wire.h>
#include <ps5Controller.h>

void setup() {
  Wire.begin();
  Serial.begin(115200);

  // ps5.begin("e8:47:3a:5a:a3:66");
  ps5.begin("7c:66:ef:78:76:f0");

  Serial.println("Setup complete.");
}

void loop() {
  if (ps5.isConnected()) {
    Wire.beginTransmission(8);
    Wire.write(ps5.Circle());
    Wire.write(ps5.Cross());
    Serial.print("Button State: ");
    Serial.print(ps5.Circle());
    Serial.println(ps5.Cross());
    byte error = Wire.endTransmission();
    if (error != 0) {
      Serial.print("I2C Transmission Error: ");
      Serial.println(error);
    } else {
      Serial.println("I2C Transmission Successful.");
    }
    // delay(100);
  }
}
