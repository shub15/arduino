#include <Wire.h>

#define DIR_PIN 13
#define PWM_PIN 11

const int PULSES_PER_REVOLUTION = 1;
const int MOTOR_SPEED = 100;        

volatile int16_t encoderPos = 0;
volatile int16_t prevEncoderPos = 0;
int8_t circle;

void setup() {
  Serial.begin(115200);

  Wire.begin(7);
  Wire.onReceive(receiveEvent);
  stopMotor();

  pinMode(DIR_PIN, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);

  Serial.println("System ready...");
}

void loop() {
  Serial.print("Encoder Position: ");
  Serial.println(encoderPos);
  if (circle == 1) {
      rotateMotorOneTurn(1);
  } else {
      stopMotor();
  }

  // delay(100);
}

void receiveEvent(int bytes) {
  if (Wire.available() >= 2) {
    long highByte = Wire.read();
    long lowByte = Wire.read();
    circle = Wire.read();
    encoderPos = (highByte << 8) | lowByte;
  }
}

void rotateMotorOneTurn(int direction) {
  if (direction == 1) {
    digitalWrite(DIR_PIN, HIGH);
  } else if (direction == -1) {
    digitalWrite(DIR_PIN, LOW);
  }

  analogWrite(PWM_PIN, MOTOR_SPEED);
  delay(1000);
  stopMotor();
}

void stopMotor() {
  analogWrite(PWM_PIN, 0);
}
