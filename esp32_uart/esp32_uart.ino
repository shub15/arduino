// Define the UART2 pins
#define RXD2 16
#define TXD2 17

void setup() {
  // Initialize the Serial Monitor
  Serial.begin(115200);

  // Initialize UART2
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  Serial.println("UART2 initialized");
}

void loop() {
  // Check if data is available on UART2
  if (Serial2.available()) {
    // Read data from UART2 and print it to the Serial Monitor
    String incomingData = Serial2.readStringUntil('\n');
    Serial.print("Received on UART2: ");
    Serial.println(incomingData);
  }

  // Send data to UART2
  if (Serial.available()) {
    // Read data from the Serial Monitor
    String dataToSend = Serial.readStringUntil('\n');
    // Send it over UART2
    Serial2.println(dataToSend);
  }

  delay(100);
}
