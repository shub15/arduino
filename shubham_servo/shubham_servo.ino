#include <Servo.h>
Servo Servo1;
int servoPin = 9;
int i;
void setup() {
  Servo1.attach(servoPin);
}


void loop() {
  for (i = 170; i <= 1023; i=i+170) {
    int angle = map(i, 0, 1023, 0, 180);
    delay(500);
    Servo1.write(angle);
  }
  i = 64;
}
