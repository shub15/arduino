const int pinA = 2;
const int pinB = 3;

volatile int encoderPos = 0;
volatile int lastState = LOW;

void setup() {
    Serial.begin(9600);
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    
    attachInterrupt(digitalPinToInterrupt(pinA), updateEncoder, CHANGE);
}

void loop() {
    Serial.print("Encoder Position: ");
    Serial.println(encoderPos);
    delay(500);
}

void updateEncoder() {
    int state = digitalRead(pinA);
    int stateB = digitalRead(pinB);

    if (state != lastState) {
        if (stateB == LOW) {
            encoderPos++;
        } else {
            encoderPos--;
        }
    }
    lastState = state;
}
