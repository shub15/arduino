#include <Wire.h>

const int pinA = 2;
const int pinB = 3;

int8_t circle;

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
  while (Wire.available()) {
    int8_t x1 = Wire.read();
    int8_t y1 = Wire.read();
    int8_t x2 = Wire.read();
    int8_t y2 = Wire.read();
    circle = Wire.read();
    // Serial.print("Joystick L X: ");
    // Serial.println(x1); 
    // Serial.print("Joystick R Y: ");
    // Serial.println(y2);
    // Serial.print(x1);
    // Serial.print(" ");
    // Serial.print(y1);
    // Serial.print(" ");
    // Serial.print(x2);
    // Serial.print(" ");
    // Serial.print(y2);
    // Serial.print(" ");
    // Serial.print(circle);
    // Serial.println(" ");
  }
}

void loop() {
  Serial.print("Encoder Position: ");
  Serial.println(count1);
  // delay(500);

  // Serial.println("Sending data to Slave...");

  Wire1.beginTransmission(7);
  Wire1.write((count1 >> 8) & 0xFF); // Send the high byte
  Wire1.write(count1 & 0xFF); 
  Wire1.write(circle); 
  byte error = Wire1.endTransmission();
  if (error != 0) {
    Serial.print("I2C Transmission Error: ");
    Serial.println(error);
  }
  delay(10);

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