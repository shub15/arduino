#include <Wire.h>

#define DIR_PIN 13
#define PWM_PIN 11
#define PWM_PIN1 12

unsigned long lastStepTimeMotor1 = 0;
unsigned long lastStepTimeMotor2 = 0;
const unsigned long stepIntervalMotor1 = 6000; // Interval for Motor 1 steps
const unsigned long stepIntervalMotor2 = 1; // Interval for Motor 2 steps

boolean nextStep;

// #define ENCODER_PIN_A 18 // Pin connected to encoder A
// #define ENCODER_PIN_B 19 // Pin connected to encoder B

int enablePin = 7;
int state = 0;

// volatile int16_t encoderPos = 0;
// volatile int16_t prevEncoderPos = 0;

// volatile int encoderPos = 0; // Tracks the position of the encoder
// volatile bool encoderDirection; // Tracks the direction of rotation

int8_t lx, ly, rx, ry, up, down, left, right, tri, squ, circle, cross;

// void readEncoder();

void setup() {
  Serial.begin(115200);

  Wire.begin(7);
  Wire.onReceive(receiveEvent);
  stopMotor();

  pinMode(DIR_PIN, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);
  pinMode(PWM_PIN1, OUTPUT);

  digitalWrite(enablePin, LOW);
  digitalWrite(DIR_PIN, HIGH);

  // pinMode(ENCODER_PIN_A, INPUT_PULLUP);
  // pinMode(ENCODER_PIN_B, INPUT_PULLUP);

  // Attach interrupts for the encoder pins
  // attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), readEncoder, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(circle), state, RISING);

  Serial.println("System ready...");
}

void receiveEvent(int bytes) {
  while (Wire.available()) {
    lx = Wire.read();
    ly = Wire.read();
    rx = Wire.read();
    ry = Wire.read();
    up = Wire.read();
    down = Wire.read();
    left = Wire.read();
    right = Wire.read();
    tri = Wire.read();
    squ = Wire.read();
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
  Serial.print(up);
  Serial.print(", ");
  Serial.print(down);
  Serial.print(", ");
  Serial.print(left);
  Serial.print(", ");
  Serial.print(right);
  Serial.print(", ");
  Serial.print(tri);
  Serial.print(", ");
  Serial.print(squ);
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
    unsigned long currentTime = micros();
    
    // Motor 1 logic
    if (currentTime - lastStepTimeMotor1 >= stepIntervalMotor1) {
      nextStep = !nextStep;
      digitalWrite(PWM_PIN, nextStep);
      lastStepTimeMotor1 = currentTime;
      // delayMicroseconds(1); // Small pulse for HIGH
      // digitalWrite(PWM_PIN, LOW);
    }
    
    // Motor 2 logic
    if (currentTime - lastStepTimeMotor2 >= stepIntervalMotor2) {
      lastStepTimeMotor2 = currentTime;
      digitalWrite(PWM_PIN1, HIGH);
      delayMicroseconds(1); // Small pulse for HIGH
      digitalWrite(PWM_PIN1, LOW);
    }
  } else {
    stopMotor();
  }
}

void rotateMotor() {
  // for (int i = 0; i < 400; i++) 
  {
    digitalWrite(PWM_PIN, HIGH);
    delayMicroseconds(7000);
    digitalWrite(PWM_PIN, LOW);
    delayMicroseconds(7000);
  }
}
void rotateMotor1() {
  // digitalWrite(DIR_PIN, HIGH);
  // for (int i = 0; i < 400; i++) 
  {
    digitalWrite(PWM_PIN1, HIGH); 
    delayMicroseconds(1100);
    digitalWrite(PWM_PIN1, LOW);
    delayMicroseconds(1100);
  }
}

void stopMotor() {
  digitalWrite(enablePin, HIGH);
}
