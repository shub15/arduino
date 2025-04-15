int enablePin = 7;
int directionPin = 13;
int pulsePin = 12;

const int stepsPerRevolution = 800;  // Update this based on your stepper motor specifications

void setup() {
  pinMode(enablePin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(pulsePin, OUTPUT);
  digitalWrite(enablePin, LOW);  // Enable the driver
  Serial.begin(115200);
}

void moveStepper(int degree, bool direction) {
  Serial.print(degree);
  Serial.print(" ");
  Serial.println(direction);
  int steps = (degree * stepsPerRevolution) / 360;  // Calculate steps for given degree
  if (direction) {
    digitalWrite(directionPin, HIGH);  // Set direction
  } else {
    digitalWrite(directionPin, LOW);  // Set direction
  }
  // digitalWrite(directionPin, direction ? HIGH : LOW); // Set direction
  for (int i = 0; i < steps; i++) {
    digitalWrite(pulsePin, HIGH);
    delayMicroseconds(1000);  // Adjust this delay for motor speed
    digitalWrite(pulsePin, LOW);
    delayMicroseconds(1000);
  }
}

void loop() {
  // Move 60 degrees clockwise
  moveStepper(60, true);
  delay(500);  // Pause

  // Move 60 degrees counter-clockwise
  moveStepper(60, false);
  delay(500);  // Pause

  // Move 15 degrees clockwise
  moveStepper(15, true);

  // Move another 15 degrees clockwise
  moveStepper(15, true);

  // Move 30 degrees clockwise
  moveStepper(30, true);
  delay(500);  // Pause

  // Repeat sequence
}
