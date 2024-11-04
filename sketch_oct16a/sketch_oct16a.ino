#define TX_PIN 10 // Define TX pin
#define RX_PIN 11 // Define RX pin
#define BAUD_RATE 9600

void setup() {
  pinMode(TX_PIN, OUTPUT);
  pinMode(RX_PIN, INPUT);
  Serial.begin(BAUD_RATE); // Optional: for debugging
}

// Function to send data
void sendData(uint8_t data) {
  // Start bit
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(1000000 / BAUD_RATE); // Delay for 1 bit period

  // Send each bit
  for (int i = 0; i < 8; i++) {
    digitalWrite(TX_PIN, (data >> i) & 0x01); // Send the ith bit
    delayMicroseconds(1000000 / BAUD_RATE); // Delay for 1 bit period
  }

  // Stop bit
  digitalWrite(TX_PIN, HIGH);
  delayMicroseconds(1000000 / BAUD_RATE); // Delay for 1 bit period
}

// Function to receive data
uint8_t receiveData() {
  uint8_t data = 0;

  // Wait for start bit (low)
  while (digitalRead(RX_PIN) == HIGH); // Wait for the line to go low

  delayMicroseconds(1000000 / (BAUD_RATE * 2)); // Wait for half the bit period

  // Read each bit
  for (int i = 0; i < 8; i++) {
    data |= (digitalRead(RX_PIN) << i); // Read the ith bit
    delayMicroseconds(1000000 / BAUD_RATE); // Wait for the bit period
  }

  // Wait for stop bit (high)
  while (digitalRead(RX_PIN) == LOW); // Wait for the line to go high

  return data;
}

void loop() {
  sendData(0b10101010); // Example: send data
  delay(1000); // Wait 1 second
}
