const int pinA = 2;
const int pinB = 3;

int lastA = LOW;
int encoderPos = 0;

void setup() {
    Serial.begin(9600);
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
}

void loop() {
    int currentA = digitalRead(pinA);
    int currentB = digitalRead(pinB);

    if (currentA != lastA) {
        if (currentB != currentA) {
            encoderPos++;
        } else {
            encoderPos--;
        }
        Serial.print("Encoder Position: ");
        Serial.println(encoderPos);
    }

    lastA = currentA;
    delay(10);
}
