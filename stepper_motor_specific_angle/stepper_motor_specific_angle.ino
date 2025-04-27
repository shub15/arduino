// Non-blocking Stepper Motor Control with Angle Positioning
// Uses a 200 steps per revolution stepper motor (1.8 degrees per step)

// Pin definitions for the stepper motor
const int stepPin = 3;    // Step pin
const int dirPin = 2;     // Direction pin
const int enablePin = 4;  // Enable pin (optional, set LOW to enable motor)

// Stepper motor parameters
const int STEPS_PER_REVOLUTION = 1200;  // 200 steps = 360 degrees (1.8° per step)
const float DEGREES_PER_STEP = 360.0 / STEPS_PER_REVOLUTION;

// Variables for non-blocking control
unsigned long lastStepTime = 0;
int stepInterval = 1000;  // Microseconds between steps (adjust for desired speed)
int currentStep = 0;      // Current step position
int targetStep = 0;       // Target step position
bool isMoving = false;    // Flag to indicate if motor is currently moving
bool motorDirection = true; // true = clockwise, false = counterclockwise

void setup() {
  // Set pin modes
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  
  // Initialize pins
  digitalWrite(stepPin, LOW);
  digitalWrite(dirPin, LOW);
  digitalWrite(enablePin, LOW);  // Enable the motor (may be HIGH for some drivers)
  
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("Non-blocking Stepper Motor Control");
  Serial.println("Commands:");
  Serial.println("  'G angle' - Go to specific angle (0-359)");
  Serial.println("  'S' - Stop motor");
  Serial.println("  '+' - Increase speed");
  Serial.println("  '-' - Decrease speed");
  Serial.println("  'R' - Reset position to 0");
}

void loop() {
  // Check for serial commands
  checkSerialCommands();
  
  // Non-blocking motor control
  updateMotor();
}

void updateMotor() {
  // Only process if motor is supposed to be moving
  if (isMoving) {
    // Check if we've reached the target position
    if (currentStep == targetStep) {
      isMoving = false;
      Serial.print("Reached target position: ");
      Serial.print(currentStep);
      Serial.print(" steps (");
      Serial.print(stepToAngle(currentStep));
      Serial.println(" degrees)");
      return;
    }
    
    // If it's time for the next step
    if (micros() - lastStepTime >= stepInterval) {
      lastStepTime = micros();
      
      // Determine direction to move
      if (shouldMoveClockwise()) {
        digitalWrite(dirPin, HIGH);  // Set direction to clockwise
        motorDirection = true;
      } else {
        digitalWrite(dirPin, LOW);   // Set direction to counterclockwise
        motorDirection = false;
      }
      
      // Update current position
      if (motorDirection) {
        currentStep++;
        if (currentStep >= STEPS_PER_REVOLUTION) {
          currentStep = 0;
        }
      } else {
        currentStep--;
        if (currentStep < 0) {
          currentStep = STEPS_PER_REVOLUTION - 1;
        }
      }
    }
  }
}

// Determine the shortest path to the target
bool shouldMoveClockwise() {
  // Calculate the distances in both directions
  int clockwiseDistance;
  int counterclockwiseDistance;
  
  if (targetStep >= currentStep) {
    clockwiseDistance = targetStep - currentStep;
    counterclockwiseDistance = STEPS_PER_REVOLUTION - clockwiseDistance;
  } else {
    counterclockwiseDistance = currentStep - targetStep;
    clockwiseDistance = STEPS_PER_REVOLUTION - counterclockwiseDistance;
  }
  
  // Return true if clockwise is the shorter path
  return clockwiseDistance <= counterclockwiseDistance;
}

// Convert angle to stepper steps
int angleToStep(float angle) {
  // Normalize the angle to 0-359.99
  while (angle < 0) angle += 360;
  while (angle >= 360) angle -= 360;
  
  // Convert to steps
  return round(angle / DEGREES_PER_STEP) % STEPS_PER_REVOLUTION;
}

// Convert steps to angle
float stepToAngle(int steps) {
  return (steps % STEPS_PER_REVOLUTION) * DEGREES_PER_STEP;
}

// Process serial commands
void checkSerialCommands() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    switch (command) {
      case 'G':
      case 'g':
        // Go to a specific angle
        if (Serial.available()) {
          delay(10);  // Wait for the rest of the data
          float targetAngle = Serial.parseFloat();
          targetStep = angleToStep(targetAngle);
          isMoving = true;
          
          Serial.print("Moving to angle: ");
          Serial.print(targetAngle);
          Serial.print(" degrees (step ");
          Serial.print(targetStep);
          Serial.println(")");
        }
        break;
        
      case 'S':
      case 's':
        // Stop the motor
        isMoving = false;
        Serial.print("Motor stopped at angle: ");
        Serial.print(stepToAngle(currentStep));
        Serial.println(" degrees");
        break;
        
      case '+':
        // Increase speed
        if (stepInterval > 200) {
          stepInterval -= 100;
          Serial.print("Speed increased. Step interval: ");
          Serial.println(stepInterval);
        }
        break;
        
      case '-':
        // Decrease speed
        stepInterval += 100;
        Serial.print("Speed decreased. Step interval: ");
        Serial.println(stepInterval);
        break;
        
      case 'R':
      case 'r':
        // Reset position to 0
        currentStep = 0;
        targetStep = 0;
        isMoving = false;
        Serial.println("Position reset to 0 degrees");
        break;
        
      case '\n':
      case '\r':
        // Ignore newlines
        break;
        
      default:
        // Unknown command
        Serial.println("Unknown command");
        break;
    }
    
    // Clear any remaining characters in the buffer
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}