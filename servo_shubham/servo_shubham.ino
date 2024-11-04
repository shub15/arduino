#include<Servo.h>

Servo serv;

void setup() {
  serv.attach(7);
}

void loop() {
  serv.write(0);
  serv.write(360);
  delay(500);
}
