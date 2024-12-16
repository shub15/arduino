#include <Wire.h>

#define DIR_PIN 13
#define PWM_PIN 11

int enablePin = 7;
int state = 0;

const int PULSES_PER_REVOLUTION = 1;
const int MOTOR_SPEED = 100;        

volatile int16_t encoderPos = 0;
volatile int16_t prevEncoderPos = 0;
int circle, cross;

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

void loop() {
  // Serial.println(circle);
    Serial.print(circle);
    Serial.println(cross);
  if (circle == 1){
    state = 1;
  }
  else if (cross == 1){
    state = 0;
  }
  if (state == 1) {
      rotateMotor();
  } else {
      stopMotor();
  }

}

void receiveEvent(int bytes) {
  if (Wire.available()) {
    // long highByte = Wire.read();
    // long lowByte = Wire.read();
    circle = Wire.read();
    cross = Wire.read();
    // Serial.println("available");
    // encoderPos = (highByte << 8) | lowByte;
  }
}

void rotateMotor() {
  digitalWrite(DIR_PIN, HIGH);
  for(int i=0;i<100;i++)
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
