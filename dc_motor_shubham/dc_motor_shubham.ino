void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(1, INPUT);
}
void loop() {
  int pwm_value = 0;
  int reading = 0;
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  for (int i = 0; i < 5; i++)
    reading = reading + analogRead(1);
  reading = reading / 5;
  pwm_value = reading >> 2;
  analogWrite(11, pwm_value);
  delay(100);
}