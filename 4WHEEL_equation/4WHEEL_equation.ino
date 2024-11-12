#include <Wire.h>

const int motorfrontdir1 = 31;
const int motorfrontspeed1 = 8;
const int motorfrontdir2 = 29;
const int motorfrontspeed2 = 5;
const int motorbackdir1 = 35;
const int motorbackspeed1 = 6;
const int motorbackdir2 = 33;
const int motorbackspeed2 = 7;
float speed_factor = 0.5;
int maxPwm = 100;
int deadzone = 50;
float wheel_radius = 0.075;
float lx = 0.15;
float ly = 0.15;

int8_t xL, xR, yL, yR, circle;

void setup() {
  pinMode(motorfrontdir1, OUTPUT);
  pinMode(motorfrontspeed1, OUTPUT);
  pinMode(motorfrontdir2, OUTPUT);
  pinMode(motorfrontspeed2, OUTPUT);
  pinMode(motorbackdir1, OUTPUT);
  pinMode(motorbackspeed1, OUTPUT);
  pinMode(motorbackdir2, OUTPUT);
  pinMode(motorbackspeed2, OUTPUT);

  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
}

void receiveEvent(int bytes) {
  while (Wire.available()) {
    xL = Wire.read();
    yL = Wire.read();
    xR = Wire.read();
    yR = Wire.read();

    if (abs(xL) < deadzone) xL = 0;
    else if (xL > 0) xL -= deadzone;
    else if (xL < 0) xL += deadzone;

    if (abs(yL) < deadzone) yL = 0;
    else if (yL > 0) yL -= deadzone;
    else if (yL < 0) yL += deadzone;

    if (abs(xR) < deadzone) xR = 0;
    else if (xR > 0) xR -= deadzone;
    else if (xR < 0) xR += deadzone;

    if (abs(yR) < deadzone) yR = 0;
    else if (yR > 0) yR -= deadzone;
    else if (yR < 0) yR += deadzone;

    circle = Wire.read();
  }
}

void setMotor(int dirPin, int speedPin, float speed) {
  constrain(speed, -maxPwm, maxPwm);
  if (speed >= 0) {
    digitalWrite(dirPin, LOW);
    // analogWrite(speedPin, min(speed, maxPwm));
    analogWrite(speedPin, speed);
  } else {
    digitalWrite(dirPin, HIGH);
    // analogWrite(speedPin, min(-speed, maxPwm));
    analogWrite(speedPin, -speed);
  }
}

void loop() {
  // delay(20);

  // float vx = map(yL, -128, 127, -maxPwm, maxPwm);  // Forward/backward
  // float vy = map(xL, -128, 127, -maxPwm, maxPwm);  // Left/right strafing
  // float wz = map(xR, -128, 127, -maxPwm, maxPwm);  // Rotation
  float vx = yL;
  float vy = xL;
  float wz = xR;

  float omega1 = (-vx - vy + wz * (lx + ly)) * 4 / wheel_radius * speed_factor;  // Front-left
  float omega2 = (-vx + vy - wz * (lx + ly)) * 4 / wheel_radius * speed_factor;  // Front-right
  float omega3 = (-vx + vy + wz * (lx + ly)) * 4 / wheel_radius * speed_factor;  // Back-right
  float omega4 = (-vx - vy - wz * (lx + ly)) * 4 / wheel_radius * speed_factor;  // Back-left

  // float maxOmega = max(max(abs(omega1), abs(omega2)), max(abs(omega3), abs(omega4)));
  // if (maxOmega > maxPwm) {
  //   omega1 = omega1 * maxPwm / maxOmega;
  //   omega2 = omega2 * maxPwm / maxOmega;
  //   omega3 = omega3 * maxPwm / maxOmega;
  //   omega4 = omega4 * maxPwm / maxOmega;
  // }

  setMotor(motorfrontdir1, motorfrontspeed1, omega1);
  setMotor(motorfrontdir2, motorfrontspeed2, omega2);
  setMotor(motorbackdir1, motorbackspeed1, omega3);
  setMotor(motorbackdir2, motorbackspeed2, omega4);
}