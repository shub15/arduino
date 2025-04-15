#include <Wire.h>

const int motorfrontdir1 = 30;
const int motorfrontspeed1 = 11;
const int motorfrontdir2 = 26;
const int motorfrontspeed2 = 9;
const int motorbackdir1 = 24;
const int motorbackspeed1 = 8;
const int motorbackdir2 = 28;
const int motorbackspeed2 = 10;
float speed_factor = 0.5;
int maxPwm = 100;
int deadzone = 50;
float wheel_radius = 0.075;

float lX = 0.15;
float lY = 0.15;

int lx, ly, rx, ry, up, down, left, right, tri, squ, circle, cross, l1, l2, r1, r2;

int indexA, indexB, indexC, indexD, indexE, indexF, indexG, indexH, indexI, indexJ, indexK, indexL, indexM, indexN, indexO, indexP;

String data1, data2, data3, data4, data5, data6, data7, data8, data9, data10, data11, data12, data13, data14, data15, data16;

String datain;

void setup() {
  pinMode(motorfrontdir1, OUTPUT);
  pinMode(motorfrontspeed1, OUTPUT);
  pinMode(motorfrontdir2, OUTPUT);
  pinMode(motorfrontspeed2, OUTPUT);
  pinMode(motorbackdir1, OUTPUT);
  pinMode(motorbackspeed1, OUTPUT);
  pinMode(motorbackdir2, OUTPUT);
  pinMode(motorbackspeed2, OUTPUT);


  Wire.begin();
  Serial.begin(115200);
  Serial2.begin(57600);
}

void setMotor(int dirPin, int speedPin, float speed) {
  // constrain(speed, -maxPwm, maxPwm);
  if (speed >= 0) {
    digitalWrite(dirPin, LOW);
    analogWrite(speedPin, min(speed, maxPwm));
    // analogWrite(speedPin, speed);
  } else if (speed < 0) {
    digitalWrite(dirPin, HIGH);
    analogWrite(speedPin, min(-speed, maxPwm));
    // analogWrite(speedPin, -speed);
  } else {
    analogWrite(speedPin, 0);
  }
}

void loop() {
  



  fetch_data();
  // Serial.println(datain);
  parse_data(datain);
  ps_print();

  // Serial.print(lx);
  // Serial.print(", ");
  // Serial.print(ly);
  // Serial.print(", ");
  // Serial.print(rx);
  // Serial.print(", ");
  // Serial.print(ry);
  // Serial.print(", ");
  // Serial.print(circle);
  // Serial.print(", ");
  // Serial.println(cross);

  Wire.beginTransmission(7);
  // Wire.write(10);  // lx
  // Wire.write(20);  // ly
  // Wire.write(30);  // rx
  // Wire.write(40);  // ry
  // Wire.write(1);   // circle
  // Wire.write(0);   // cross
  Wire.write(lx);
  Wire.write(ly);
  Wire.write(rx);
  Wire.write(ry);
  Wire.write(up);
  Wire.write(down);
  Wire.write(left);
  Wire.write(right);
  Wire.write(tri);
  Wire.write(squ);
  Wire.write(circle);
  Wire.write(cross);
  byte error = Wire.endTransmission();
  if (error != 0) {
    Serial.print("I2C Transmission Error: ");
    Serial.println(error);
  }
  // delay(100);

  // float vx = map(yL, -128, 127, -maxPwm, maxPwm);  // Forward/backward
  // float vy = map(xL, -128, 127, -maxPwm, maxPwm);  // Left/right strafing
  // float wz = map(xR, -128, 127, -maxPwm, maxPwm);  // Rotation
  float vx = ly;
  float vy = lx;
  float wz = rx;

  float omega1 = (-vx - vy + wz * (lX + lY)) * 4 / wheel_radius;  // Front-left
  float omega2 = (-vx + vy - wz * (lX + lY)) * 4 / wheel_radius;  // Front-right
  float omega3 = (-vx + vy + wz * (lX + lY)) * 4 / wheel_radius;  // Back-right
  float omega4 = (-vx - vy - wz * (lX + lY)) * 4 / wheel_radius;  // Back-left

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