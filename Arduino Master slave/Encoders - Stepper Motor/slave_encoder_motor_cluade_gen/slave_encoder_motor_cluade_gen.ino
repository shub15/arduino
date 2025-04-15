#include <Wire.h>

#define DIR_PIN 13
#define PWM_PIN 11
#define PWM_PIN1 12
#define ENABLE_PIN 7

// Stepper timing constants
const unsigned long MICROSTEPS = 16;  // Adjust based on your driver settings
const unsigned long STEPS_PER_REV = 200;  // Standard for most NEMA steppers
const float MIN_STEP_DELAY = 50;  // Minimum delay between steps (microseconds)
const float MAX_STEP_DELAY = 10000;  // Maximum delay between steps (microseconds)

// Motor control variables
unsigned long lastStepTimeMotor1 = 0;
unsigned long lastStepTimeMotor2 = 0;
unsigned long stepIntervalMotor1 = 5000;  // Initial interval, can be adjusted
unsigned long stepIntervalMotor2 = 1000;  // Initial interval, can be adjusted

// Controller variables
int8_t lx, ly, rx, ry, up, down, left, right, tri, squ, circle, cross;
int state = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(7);
  Wire.onReceive(receiveEvent);
  
  // Configure pins
  pinMode(DIR_PIN, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);
  pinMode(PWM_PIN1, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  
  // Initial pin states
  digitalWrite(DIR_PIN, HIGH);
  digitalWrite(ENABLE_PIN, HIGH);  // Motors disabled initially
  
  Serial.println("System ready...");
}

void receiveEvent(int bytes) {
  if (Wire.available() >= 12) {  // Ensure we have complete data
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
  }
}

void loop() {
  // Print debug info
  printDebugInfo();
  
  // Update motor state
  if (circle == 1) {
    enableMotors();
  } else if (cross == 1) {
    disableMotors();
  }
  
  // Motor control logic
  if (state == 1) {
    unsigned long currentTime = micros();
    
    // Motor 1 step control with acceleration ramping
    if (currentTime - lastStepTimeMotor1 >= stepIntervalMotor1) {
      stepMotor(PWM_PIN, currentTime, &lastStepTimeMotor1);
      
      // Gradually adjust speed based on controller input
      if (abs(lx) > 10) {  // Apply deadzone
        stepIntervalMotor1 = map(abs(lx), 0, 127, MAX_STEP_DELAY, MIN_STEP_DELAY);
      }
    }
    
    // Motor 2 step control with acceleration ramping
    if (currentTime - lastStepTimeMotor2 >= stepIntervalMotor2) {
      stepMotor(PWM_PIN1, currentTime, &lastStepTimeMotor2);
      
      // Gradually adjust speed based on controller input
      if (abs(rx) > 10) {  // Apply deadzone
        stepIntervalMotor2 = map(abs(rx), 0, 127, MAX_STEP_DELAY, MIN_STEP_DELAY);
      }
    }
  }
}

void stepMotor(int pin, unsigned long currentTime, unsigned long* lastStepTime) {
  digitalWrite(pin, HIGH);
  delayMicroseconds(5);  // Consistent minimum pulse width
  digitalWrite(pin, LOW);
  *lastStepTime = currentTime;
}

void enableMotors() {
  state = 1;
  digitalWrite(ENABLE_PIN, LOW);
}

void disableMotors() {
  state = 0;
  digitalWrite(ENABLE_PIN, HIGH);
}

void printDebugInfo() {
  Serial.print("Controls: ");
  Serial.print(lx); Serial.print(", ");
  Serial.print(ly); Serial.print(", ");
  Serial.print(rx); Serial.print(", ");
  Serial.print(ry); Serial.print(", ");
  Serial.print(up); Serial.print(", ");
  Serial.print(down); Serial.print(", ");
  Serial.print(left); Serial.print(", ");
  Serial.print(right); Serial.print(", ");
  Serial.print(tri); Serial.print(", ");
  Serial.print(squ); Serial.print(", ");
  Serial.print(circle); Serial.print(", ");
  Serial.println(cross);
  
  Serial.print("Intervals: M1=");
  Serial.print(stepIntervalMotor1);
  Serial.print(" M2=");
  Serial.println(stepIntervalMotor2);
}