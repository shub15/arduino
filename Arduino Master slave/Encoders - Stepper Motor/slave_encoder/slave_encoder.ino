#include <Wire.h>

#define DIR_PIN 13
#define PWM_PIN 11

const int PULSES_PER_REVOLUTION = 1;
const int MOTOR_SPEED = 100;        

volatile int16_t encoderPos = 0;
volatile int16_t prevEncoderPos = 0;

void setup() {
  Serial.begin(9600);

  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  stopMotor();

  pinMode(DIR_PIN, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);

  Serial.println("System ready...");
}

void loop() {
  if (encoderPos > prevEncoderPos) {
    int rotations = encoderPos - prevEncoderPos;
    for (int i = 0; i < rotations; i++) {
      rotateMotorOneTurn(1);
    }
    prevEncoderPos = encoderPos;
  } else if (encoderPos < prevEncoderPos) {
    int rotations = prevEncoderPos - encoderPos;
    for (int i = 0; i < rotations; i++) {
      rotateMotorOneTurn(-1);
    }
    prevEncoderPos = encoderPos;
  }

  Serial.print("Encoder Position: ");
  Serial.println(encoderPos);
  // delay(100);
}

void receiveEvent(int bytes) {
  if (Wire.available() >= 2) {
    uint8_t highByte = Wire.read();
    uint8_t lowByte = Wire.read();
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
