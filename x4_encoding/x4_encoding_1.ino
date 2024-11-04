const int pinA = 2;
const int pinB = 3;

volatile int encoderPos = 0;
volatile int lastA = LOW;
volatile int lastB = LOW;

void setup() {
  Serial.begin(9600);
  
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(pinA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), updateEncoder, CHANGE);
}

void loop() {
  Serial.print("Encoder Position: ");
  Serial.println(encoderPos);
  delay(10);
}

void updateEncoder() {
  int stateA = digitalRead(pinA);
  int stateB = digitalRead(pinB);
  
  if (stateA == HIGH && lastA == LOW) {
    if (stateB == LOW) {
      encoderPos++; // Clockwise
    } else {
      encoderPos--; // Counter-clockwise
    }
  } else if (stateA == LOW && lastA == HIGH) {
    if (stateB == HIGH) {
      encoderPos++; // Clockwise
    } else {
      encoderPos--; // Counter-clockwise
    }
  }
  
  if (stateB == HIGH && lastB == LOW) {
    if (stateA == HIGH) {
      encoderPos++; // Clockwise
    } else {
      encoderPos--; // Counter-clockwise
    }
  } else if (stateB == LOW && lastB == HIGH) {
    if (stateA == LOW) {
      encoderPos++;
    } else {
      encoderPos--;
    }
  }

  lastA = stateA;
  lastB = stateB;
}
