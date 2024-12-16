#include <Wire.h>

const int pinA = 2;
const int pinB = 3;

int lx,ly,rx,ry,up,down,left,right,tri,squ,circle,cross,l1,l2,r1,r2;

int indexA,indexB,indexC,indexD,indexE,indexF,indexG,indexH,indexI,indexJ,indexK,indexL,indexM,indexN,indexO,indexP;

String data1,data2,data3,data4,data5,data6,data7,data8,data9,data10,data11,data12,data13,data14,data15,data16;

String datain;

// int8_t circle = 0;
// int8_t cross = 0;

volatile long count1 = 0;
// volatile int lastState = LOW;


void setup() {
  // Wire.begin(8);
  Wire.begin();
  // Wire.onReceive(receiveEvent);
  Serial.begin(115200);
  Serial2.begin(57600);

  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), updateEncoder, RISING);
}

// void receiveEvent(int bytes) {
//   // if (Wire.available()) {
//   //   Serial.println("available");
//   // }
//   while (Wire.available()) {
//     circle = Wire.read();
//     cross = Wire.read();
//     Serial.print(circle);
//     Serial.println(cross);
//   }
// }

void loop() {
  fetch_data();
  parse_data(datain);
  ps_print();
  // Serial.print("Encoder Position: ");
  // Serial.println(count1);
  // delay(500);

  // Serial.println("Sending data to Slave...");

  Wire.beginTransmission(8);
  // Wire.write((count1 >> 8) & 0xFF);  // Send the high byte
  // Wire.write(count1 & 0xFF);
  Wire.write(lx);
  Wire.write(ly);
  Wire.write(rx);
  Wire.write(ry);
  Wire.write(circle);
  // Wire.write(cross);
  byte error = Wire.endTransmission();
  // Wire.endTransmission();
  if (error != 0) {
    Serial.print("I2C Transmission Error: ");
    Serial.println(error);
  }
  // delay(10);

  // delay(500);

  // Wire.requestFrom(8, 32);
  // while (Wire.available()) {
  //   char c = Wire.read();
  //   Serial.print(c);
  // }
  // Serial.println();

  // delay(2000);
}

void updateEncoder() {
  if (digitalRead(pinA) != digitalRead(pinB)) {
    count1 = count1 + 1;
  } else if (digitalRead(pinA) == digitalRead(pinB)) {
    count1 = count1 - 1;
  }
}