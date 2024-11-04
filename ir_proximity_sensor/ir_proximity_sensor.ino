int sensor = 10;
// int sensor = 0;

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
}

void loop() {
  Serial.println(digitalRead(sensor));
  // Serial.println(analogRead(sensor));
  delay(100);
}
  