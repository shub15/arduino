#include <Wire.h>

const int pinA = 2;
const int pinB = 3;

volatile int16_t count1 = 0;
// volatile int lastState = LOW;


void setup() {
  Wire.begin();
  Serial.begin(9600);

  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), updateEncoder, RISING);
}

void loop() {
  Serial.print("Encoder Position: ");
  Serial.println(count1);
  // delay(500);

  // Serial.println("Sending data to Slave...");

  Wire.beginTransmission(8);
  Wire.write((count1 >> 8) & 0xFF); // Send the high byte
  Wire.write(count1 & 0xFF); 
  Wire.endTransmission();
  delay(100);

  // delay(500);

  // Wire.requestFrom(8, 32);
  // while (Wire.available()) {
  //   char c = Wire.read();
  //   Serial.print(c);
  // }
  // Serial.println();

  // delay(2000);
}

void updateEncoder() {
  if (digitalRead(pinA) != digitalRead(pinB)) {
    count1 = count1 + 1;
  } else if (digitalRead(pinA) == digitalRead(pinB)){
    count1 = count1 - 1;
  }
}