const int m1 = 4;
const int m2 = 2;
const int m3 = 9;
const int pwm1 = 12;
const int pwm2 = 11;
const int pwm3 = 10;
int deadzone = 50;

int lx, ly, rx, ry, up, down, left, right, tri, squ, circle, cross, l1, l2, r1, r2;

int indexA, indexB, indexC, indexD, indexE, indexF, indexG, indexH, indexI, indexJ, indexK, indexL, indexM, indexN, indexO, indexP;

String data1, data2, data3, data4, data5, data6, data7, data8, data9, data10, data11, data12, data13, data14, data15, data16;

String datain;

void setup() {
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(pwm3, OUTPUT);
  Serial.begin(115200);
  // Serial2.begin(57600);
  Serial2.begin(500000);
}

// void setMotor() {
//   int speed = lx >= 0 || lx < 0 ? map(lx, 0, lx, 0, 255) : map(ly, 0, ly, 0, 255);
//   if (lx >= 0) {
//     digitalWrite(m1, HIGH);
//     digitalWrite(m2, HIGH);
//     analogWrite(pwm1, speed);
//     analogWrite(pwm2, speed);
//   } else if (lx < 0) {
//     digitalWrite(m1, LOW);
//     digitalWrite(m2, LOW);
//     analogWrite(pwm1, speed);
//     analogWrite(pwm2, speed);
//   } else if (ly >= 0) {
//     digitalWrite(m1, HIGH);
//     digitalWrite(m3, HIGH);
//     digitalWrite(m2, LOW);
//     analogWrite(pwm1, speed);
//     analogWrite(pwm2, speed);
//     analogWrite(pwm3, speed);
//   } else if (ly < 0) {
//     digitalWrite(m1, LOW);
//     digitalWrite(m3, LOW);
//     digitalWrite(m2, HIGH);
//     analogWrite(pwm1, speed);
//     analogWrite(pwm2, speed);
//     analogWrite(pwm3, speed);
//   } else {
//     analogWrite(pwm1, 0);
//     analogWrite(pwm2, 0);
//     analogWrite(pwm3, 0);
//   }
// }


void setMotorDirectionSpeed(int dirPin, int pwmPin, int speed) {
  if (speed >= 0) {
    digitalWrite(dirPin, HIGH);
    analogWrite(pwmPin, speed);
  } else {
    digitalWrite(dirPin, LOW);
    analogWrite(pwmPin, abs(speed));
  }
}

void setMotor() {
  int xInput = (abs(lx) < deadzone) ? 0 : lx;
  int yInput = (abs(ly) < deadzone) ? 0 : ly;
  int rotation = (abs(rx) < deadzone) ? 0 : rx;
  
  float x = map(xInput, -128, 127, -255, 255);
  float y = map(yInput, -128, 127, -255, 255);
  float r = map(rotation, -128, 127, -127, 127);

  float m1Speed = 0 * x - 1.0 * y + r;

  float m2Speed = 0.866 * x + 0.5 * y + r;

  float m3Speed = -0.866 * x + 0.5 * y + r;
  
  float maxSpeed = max(max(abs(m1Speed), abs(m2Speed)), abs(m3Speed));
  if (maxSpeed > 255) {
    m1Speed = m1Speed * 255 / maxSpeed;
    m2Speed = m2Speed * 255 / maxSpeed;
    m3Speed = m3Speed * 255 / maxSpeed;
  }
  
  setMotorDirectionSpeed(m1, pwm1, (int)m1Speed);
  setMotorDirectionSpeed(m2, pwm2, (int)m2Speed);
  setMotorDirectionSpeed(m3, pwm3, (int)m3Speed);
  
  if (x == 0 && y == 0 && r == 0) {
    analogWrite(pwm1, 0);
    analogWrite(pwm2, 0);
    analogWrite(pwm3, 0);
  }
}

void loop() {
  fetch_data();
  parse_data(datain);
  ps_print();
  setMotor();
}
