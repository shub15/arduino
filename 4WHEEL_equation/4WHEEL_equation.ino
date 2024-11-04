#include <Wire.h>

const int motorfrontdir1 = 31;
const int motorfrontspeed1 = 8;
const int motorfrontdir2 = 29;
const int motorfrontspeed2 = 5;
const int motorbackdir1 = 35;
const int motorbackspeed1 = 6;
const int motorbackdir2 = 33;
const int motorbackspeed2 = 7;
int deadzone = 20;
float wheel_radius = 0.075;  // radius of the wheel in meters
float lx = 0.15;             // distance between wheels in x direction
float ly = 0.15;             // distance between wheels in y direction

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
    if (abs(yL) < deadzone) yL = 0;
    if (abs(xR) < deadzone) xR = 0;
    if (abs(yR) < deadzone) yR = 0;
    circle = Wire.read();
  }
}

// Function to set motor direction and speed
void setMotor(int dirPin, int speedPin, float speed) {
  if (speed >= 0) {
    digitalWrite(dirPin, LOW);
    analogWrite(speedPin, min(speed, 200));  // limit speed to max PWM
  } else {
    digitalWrite(dirPin, HIGH);
    analogWrite(speedPin, min(-speed, 200));  // limit speed to max PWM
  }
}

void loop() {
  delay(20);

  // Convert joystick inputs to velocities
  float vx = map(yL, -128, 127, -255, 255);  // Forward/backward
  float vy = map(xL, -128, 127, -255, 255);  // Left/right strafing
  float wz = map(xR, -128, 127, -255, 255);  // Rotation

  // Calculate wheel speeds using mecanum wheel formulas
  float omega1 = (-vx - vy + wz * (lx + ly)) * 4 / wheel_radius;  // Front-left
  float omega2 = (-vx + vy - wz * (lx + ly)) * 4 / wheel_radius;  // Front-right
  float omega3 = (-vx + vy + wz * (lx + ly)) * 4 / wheel_radius;  // Back-right
  float omega4 = (-vx - vy - wz * (lx + ly)) * 4 / wheel_radius;  // Back-left

  // Set motor speeds and directions
  setMotor(motorfrontdir1, motorfrontspeed1, omega1);
  setMotor(motorfrontdir2, motorfrontspeed2, omega2);
  setMotor(motorbackdir1, motorbackspeed1, omega3);
  setMotor(motorbackdir2, motorbackspeed2, omega4);
}
