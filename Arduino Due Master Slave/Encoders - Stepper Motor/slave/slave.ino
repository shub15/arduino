#include <Wire.h>

volatile int16_t pos = 0;
const int16_t minPos = -1200;  // Minimum encoder position
const int16_t maxPos = 1200;   // Maximum encoder position
// long prevT = 0;
// float eprev = 0;
// float eintegral = 0;


void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  // Wire.onRequest(requestEvent);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

void receiveEvent(int bytes) {
  while (Wire.available()) {
    // Serial.println("connection available");
    uint8_t highByte = Wire.read();
    uint8_t lowByte = Wire.read();
    pos = (highByte << 8) | lowByte;
    // Serial.println(pos);

    if (pos > maxPos) pos = maxPos;
    if (pos < minPos) pos = minPos;
  }
}

void setMotor(int dir, int speed) {
  if (dir == 1) {
    digitalWrite(13, HIGH);
    analogWrite(11, speed);
    // digitalWrite(12, LOW);
  } else if (dir == -1) {
    digitalWrite(13, LOW);
    analogWrite(11, speed);
    // digitalWrite(12, HIGH);
  } else {
    digitalWrite(13, LOW);
    analogWrite(11, 0);
    // digitalWrite(12, LOW);
  }
  // speed = map(xL, 0, 127, 0, 255);
}

void loop() {
  // target position
  // int target = 1200;

  // // PID
  // float kp = 1;
  // float kd = 0;
  // float ki = 0;

  // // time difference
  // long currT = micros();

  // float deltaT = ((float)(currT - prevT)) / 1.0e6;
  // prevT = currT;

  // //error
  // int e = target - pos;

  // // derivative
  // float dedt = (e - eprev) / (deltaT);

  // // integral
  // eintegral = eintegral + e * deltaT;

  // // control signal
  // float u = kp * e + kd * dedt + ki * eintegral;

  // // motor power
  // float pwr = fabs(u);
  // if (pwr > 255) {
  //   pwr = 255;
  // }

  int dir = 0;
  int n;

  // // motor direction
  // if (u < 0) {
  //   dir = -1;
  // }

  // int speed = map(abs(pos), 0, 1200, 0, 255);
  dir = (pos >= 0) ? 1 : -1;
  setMotor(dir, 100);

  // store previous error
  // eprev = e;

  // Serial.print(target);
  // Serial.print(" ");
  // Serial.print(pos);
  // Serial.println();

  Serial.print("Position: ");
  Serial.print(pos);
  Serial.print(" Direction: ");
  Serial.println(dir);
  // Serial.print(" Speed: ");
  // Serial.println(speed);
}




// void requestEvent() {
//   Wire.write("Hello, Master");
// }