int enablePin = 7;
int directionPin = 4;
int pulsePin = 3;
int led = 13;
void setup() {
  pinMode(enablePin,OUTPUT);
  pinMode(directionPin,OUTPUT);
  pinMode(pulsePin,OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(enablePin,LOW);
}

void loop() {
  digitalWrite(directionPin,HIGH);
  for(int i=0;i<100;i++)
  {
    digitalWrite(pulsePin,HIGH);
//    delayMicroseconds(10);
    digitalWrite(pulsePin,LOW);
//    delayMicroseconds(10);
    digitalWrite(led, HIGH);
//    delay(60);
    digitalWrite(led, LOW);
    delay(1);
  }
//  delay(1000);
}
