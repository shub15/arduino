void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(1, INPUT);
}
void loop() {
  int speed = 0;
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  speed = map(analogRead(1), 0, 1023, 0, 255);
  analogWrite(11, speed);
}