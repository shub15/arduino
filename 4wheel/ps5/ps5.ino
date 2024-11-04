#include <Wire.h>
#include <ps5Controller.h>

// I2C address of Arduino Mega
#define MEGA_ADDRESS 8

void setup() {
    Serial.begin(115200);
    Wire.begin(); // Start I2C
    if (!PS5.begin()) {
        Serial.println("PS5 Controller not found.");
        while (1);
    }
}

void loop() {
    // Read the joystick values
    int leftStickY = PS5.getAnalogHat(LeftHatY); // Forward/Backward
    int leftStickX = PS5.getAnalogHat(LeftHatX); // Left/Right
    int rightStickX = PS5.getAnalogHat(RightHatX); // Rotate

    // Normalize the joystick values to range between -255 and 255
    int frontLeftSpeed = constrain(leftStickY + leftStickX + rightStickX, -255, 255);
    int frontRightSpeed = constrain(leftStickY - leftStickX - rightStickX, -255, 255);
    int rearLeftSpeed = constrain(leftStickY - leftStickX + rightStickX, -255, 255);
    int rearRightSpeed = constrain(leftStickY + leftStickX - rightStickX, -255, 255);

    // Send motor speeds to Arduino Mega via I2C
    Wire.beginTransmission(MEGA_ADDRESS);
    Wire.write(frontLeftSpeed);
    Wire.write(frontRightSpeed);
    Wire.write(rearLeftSpeed);
    Wire.write(rearRightSpeed);
    Wire.endTransmission();

    delay(100); // Adjust for responsiveness
}
