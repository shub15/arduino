// Pin definitions
const int pinA = 2; // Connect to A pin of rotary encoder
const int pinB = 3; // Connect to B pin of rotary encoder

volatile int encoderPos = 0; // Position of the encoder
volatile int lastA = LOW; // Previous state of A pin
volatile int lastB = LOW; // Previous state of B pin

void setup() {
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  
  // Attach interrupts
  attachInterrupt(digitalPinToInterrupt(pinA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), updateEncoder, CHANGE);
}

void loop() {
  // Print the current position
  Serial.print("Encoder Position: ");
  Serial.println(encoderPos);
  delay(10); // Adjust delay as needed
}

void updateEncoder() {
  // Read the current states of pin A and pin B
  int stateA = digitalRead(pinA);
  int stateB = digitalRead(pinB);
  
  // Detect rising and falling edges on pin A
  if (stateA == HIGH && lastA == LOW) {
    Serial.println("Rising edge detected on pin A");
    if (stateB == LOW) {
      encoderPos++; // Clockwise
    } else {
      encoderPos--; // Counter-clockwise
    }
  } else if (stateA == LOW && lastA == HIGH) {
    Serial.println("Falling edge detected on pin A");
    if (stateB == HIGH) {
      encoderPos++; // Clockwise
    } else {
      encoderPos--; // Counter-clockwise
    }
  }
  
  // Detect rising and falling edges on pin B
  if (stateB == HIGH && lastB == LOW) {
    Serial.println("Rising edge detected on pin B");
    if (stateA == HIGH) {
      encoderPos++; // Clockwise
    } else {
      encoderPos--; // Counter-clockwise
    }
  } else if (stateB == LOW && lastB == HIGH) {
    Serial.println("Falling edge detected on pin B");
    if (stateA == LOW) {
      encoderPos++; // Clockwise
    } else {
      encoderPos--; // Counter-clockwise
    }
  }

  // Update last states
  lastA = stateA;
  lastB = stateB;
}
