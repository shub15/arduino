#include <Wire.h>

const int MPU_ADDR = 0x68;  // MPU-6050 I2C address

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Initialize MPU-6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);  // Power management register 0x6B
  Wire.write(0);     // Set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);  // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);  // Request a total of 14 registers

  // Read accelerometer data
  int16_t ax = (Wire.read() << 8 | Wire.read());
  int16_t ay = (Wire.read() << 8 | Wire.read());
  int16_t az = (Wire.read() << 8 | Wire.read());

  // Read temperature data
  int16_t temp = (Wire.read() << 8 | Wire.read());

  // Read gyroscope data
  int16_t gx = (Wire.read() << 8 | Wire.read());
  int16_t gy = (Wire.read() << 8 | Wire.read());
  int16_t gz = (Wire.read() << 8 | Wire.read());

  // Print accelerometer data
  Serial.print("Accel X: "); Serial.print(ax);
  Serial.print(" | Accel Y: "); Serial.print(ay);
  Serial.print(" | Accel Z: "); Serial.println(az);

  // Print gyroscope data
  Serial.print("Gyro X: "); Serial.print(gx);
  Serial.print(" | Gyro Y: "); Serial.print(gy);
  Serial.print(" | Gyro Z: "); Serial.println(gz);

  delay(500);
}
