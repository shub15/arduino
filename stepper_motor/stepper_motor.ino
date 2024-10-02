int A = 8;
int A_bar = 9;
int B = 10;
int B_bar = 11;
int y = 100;

int xdir = 1;
int xdir1;
int count = 1;

void setup() {
  pinMode(A, OUTPUT);
  pinMode(A_bar, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(B_bar, OUTPUT);
}

void loop() {
  if (count % 100 == 0) {
    xdir1 = xdir * (-1);
    digitalWrite(A, HIGH);
    digitalWrite(A_bar, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(B_bar, LOW);
    delay(y);
  }

  for (count = 1; count <= 600; count++)
  
  if (xdir == 1) {
    digitalWrite(A, HIGH);
    digitalWrite(A_bar, LOW);
    digitalWrite(B, HIGH);
    digitalWrite(B_bar, LOW);
    delay(y);
  }

  if (xdir == -1) 
  {
    digitalWrite(A, HIGH);
    digitalWrite(A_bar, LOW);
    digitalWrite(B, LOW);
    digitalWrite(B_bar, HIGH);
    delay(y);
  }
  count++;
  delay(1000);
}