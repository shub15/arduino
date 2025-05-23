#include <Wire.h>

const int pinA = 2;
const int pinB = 3;

int8_t circle = 0;
int8_t cross = 0;

volatile long count1 = 0;
// volatile int lastState = LOW;


void setup() {
  Wire.begin(8);
  Wire1.begin();
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);

  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), updateEncoder, RISING);
}

void receiveEvent(int bytes) {
  // if (Wire.available()) {
  //   Serial.println("available");
  // }
  while (Wire.available()) {
    circle = Wire.read();
    cross = Wire.read();
    Serial.print(circle);
    Serial.println(cross);
  }
}

void loop() {
  // Serial.print("Encoder Position: ");
  // Serial.println(count1);
  // delay(500);

  // Serial.println("Sending data to Slave...");

  Wire1.beginTransmission(7);
  // Wire1.write((count1 >> 8) & 0xFF);  // Send the high byte
  // Wire1.write(count1 & 0xFF);
  Wire1.write(circle);
  Wire1.write(cross);
  byte error = Wire1.endTransmission();
  // Wire1.endTransmission();
  if (error != 0) {
    Serial.print("I2C Transmission Error: ");
    Serial.println(error);
  }
  // delay(10);

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
  } else if (digitalRead(pinA) == digitalRead(pinB)) {
    count1 = count1 - 1;
  }
}