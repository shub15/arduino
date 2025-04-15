// Rotary Encoder Example Code for Arduino

#define ENCODER_PIN_A 18 // Pin connected to encoder A
#define ENCODER_PIN_B 19 // Pin connected to encoder B

#define pulse 8
#define direction 9

#define button 2

int toggleBtn = 0;
int readBtn = 0;

volatile int encoderPos = 0; // Tracks the position of the encoder
volatile bool encoderDirection; // Tracks the direction of rotation

void setup() {


  pinMode(ENCODER_PIN_A, INPUT_PULLUP);
  pinMode(ENCODER_PIN_B, INPUT_PULLUP);

  // Attach interrupts for the encoder pins
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), readEncoder, CHANGE);

  attachInterrupt(digitalPinToInterrupt(button), toggle, RISING);

  pinMode(pulse,OUTPUT);
  pinMode(direction,OUTPUT);
  

  Serial.begin(115200); // Initialize serial communication
}

void loop() {
  

  readBtn = digitalRead(button);
  Serial.println(readBtn);
  
  digitalWrite(direction,HIGH);
  while(toggleBtn == 1)
  {
    digitalWrite(pulse,HIGH);
    delay(1);
    digitalWrite(pulse,LOW);
    delay(1);
  }

  delay(50); // Reduce serial output frequency
}

void readEncoder() {
  // Read the encoder pins

  // Display encoder position and direction
  static int lastPosition = 0;
  
  if(toggleBtn == 1){
    if (encoderPos != lastPosition) {
    lastPosition = encoderPos;
    Serial.print("Position: ");
    Serial.print(encoderPos);
    Serial.print(" | Direction: ");
    Serial.println(encoderDirection ? "CW" : "CCW");
    }

    int stateA = digitalRead(ENCODER_PIN_A);
    int stateB = digitalRead(ENCODER_PIN_B);

    if(stateA == stateB)
    {
      encoderPos ++;
      encoderDirection = true;
    }
    else
    {
      encoderPos --;
      encoderDirection = false;
    }
  }
  
  
}

void toggle()
{
  toggleBtn = !toggleBtn;
}
