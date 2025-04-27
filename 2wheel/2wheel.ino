#include <Arduino.h>  // Add this for ESP32 functionality
#include <ps5Controller.h>

// Left Motor
const int LEFT_PWM_CHANNEL = 0;   // PWM channel for left motor
const int LEFT_DIR_PIN = 26;  // Direction pin for left motor

// Right Motor
const int RIGHT_PWM_CHANNEL = 1;  // PWM channel for right motor
const int RIGHT_DIR_PIN = 33;  // Direction pin for right motor

int lx, ly, rx, ry, tri, cir, squ, cro, l2, r2;
int buff = 40;

// Forward declarations of functions
void stopMotors();
void moveForward(int speed);
void moveBackward(int speed);
void turnLeft(int speed);
void turnRight(int speed);
// void readPS5Controller();

void setup() {
  Serial.begin(115200);
  ps5.begin("e8:47:3a:5a:a3:66");

  // pwm
  pinMode(LEFT_PWM_CHANNEL, OUTPUT);
  pinMode(RIGHT_PWM_CHANNEL, OUTPUT);

  // Set direction pins as outputs
  pinMode(LEFT_DIR_PIN, OUTPUT);
  pinMode(RIGHT_DIR_PIN, OUTPUT);

  // Initialize motors to stopped state
  stopMotors();
}

void loop() {
  if (ps5.isConnected()) {
    lx = ps5.LStickX();  // Added missing semicolons
    ly = ps5.LStickY();
    rx = ps5.RStickX();
    ry = ps5.RStickY();
    tri = ps5.Triangle();
    cir = ps5.Circle();
    cro = ps5.Cross();
    squ = ps5.Square();
    l2 = ps5.L2();
    r2 = ps5.R2();
  }
  processCommand();
}

void processCommand() {
  int speed = 200;  // Default speed (0-255)

  if (ly > buff) {
    moveForward(speed);
    Serial.println("Moving Forward");
  } else if (ly < -buff) {
    moveBackward(speed);
    Serial.println("Moving Backward");
  } else if (lx < -buff) {
    turnLeft(speed);
    Serial.println("Turning Left");
  } else if (lx > buff) {  // Fixed from ly > buff to lx > buff
    turnRight(speed);
    Serial.println("Turning Right");
  } else {
    stopMotors();
    Serial.println("Stopped");
  }
}

// Motor control functions
void moveForward(int speed) {
  // Set direction pins
  digitalWrite(LEFT_DIR_PIN, HIGH);   // Forward direction for left motor
  digitalWrite(RIGHT_DIR_PIN, HIGH);  // Forward direction for right motor

  // Set speed
  analogWrite(LEFT_PWM_CHANNEL, speed);
  analogWrite(RIGHT_PWM_CHANNEL, speed);
}

void moveBackward(int speed) {
  // Set direction pins
  digitalWrite(LEFT_DIR_PIN, LOW);   // Backward direction for left motor
  digitalWrite(RIGHT_DIR_PIN, LOW);  // Backward direction for right motor

  // Set speed
  analogWrite(LEFT_PWM_CHANNEL, speed);
  analogWrite(RIGHT_PWM_CHANNEL, speed);
}

void turnLeft(int speed) {
  // Set direction pins
  digitalWrite(LEFT_DIR_PIN, LOW);    // Left motor backward
  digitalWrite(RIGHT_DIR_PIN, HIGH);  // Right motor forward

  // Set speed
  analogWrite(LEFT_PWM_CHANNEL, speed);
  analogWrite(RIGHT_PWM_CHANNEL, speed);
}

void turnRight(int speed) {
  // Set direction pins
  digitalWrite(LEFT_DIR_PIN, HIGH);  // Left motor forward
  digitalWrite(RIGHT_DIR_PIN, LOW);  // Right motor backward

  // Set speed
  analogWrite(LEFT_PWM_CHANNEL, speed);
  analogWrite(RIGHT_PWM_CHANNEL, speed);
}

void stopMotors() {
  // Set speed to zero
  analogWrite(LEFT_PWM_CHANNEL, 0);
  analogWrite(RIGHT_PWM_CHANNEL, 0);
}