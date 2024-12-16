#include <Wire.h>

#define DIR_PIN 13
#define PWM_PIN 11

int enablePin = 7;
int state = 0;

volatile int16_t encoderPos = 0;
volatile int16_t prevEncoderPos = 0;
int8_t lx, ly, rx, ry, circle, cross;

void setup() {
  Serial.begin(115200);

  Wire.begin(7);
  Wire.onReceive(receiveEvent);
  stopMotor();

  pinMode(DIR_PIN, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);

  digitalWrite(enablePin, LOW);

  Serial.println("System ready...");
}

void receiveEvent(int bytes) {
  while (Wire.available()) {
    lx = Wire.read();
    ly = Wire.read();
    rx = Wire.read();
    ry = Wire.read();
    circle = Wire.read();
    cross = Wire.read();
    // Serial.print(circle);
    // Serial.println(cross);
  }
}

void loop() {
  Serial.print(lx);
  Serial.print(", ");
  Serial.print(ly);
  Serial.print(", ");
  Serial.print(rx);
  Serial.print(", ");
  Serial.print(ry);
  Serial.print(", ");
  Serial.print(circle);
  Serial.print(", ");
  Serial.println(cross);
  // delay(100);
  if (circle == 1) {
    state = 1;
  } else if (cross == 1) {
    state = 0;
  }
  if (state == 1) {
    rotateMotor();
  } else {
    stopMotor();
  }
}

void rotateMotor() {
  digitalWrite(DIR_PIN, HIGH);
  // for(int i=0;i<100;i++)
  {
    digitalWrite(PWM_PIN, HIGH);
    delayMicroseconds(1000);
    digitalWrite(PWM_PIN, LOW);
    delayMicroseconds(1000);
  }
}

void stopMotor() {
  digitalWrite(enablePin, HIGH);
}
