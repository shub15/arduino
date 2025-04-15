// void readEncoder() {
//   // Read the encoder pins

//   // Display encoder position and direction
//   static int lastPosition = 0;
  
//   if(state == 1){
//     if (encoderPos != lastPosition) {
//     lastPosition = encoderPos;
//     Serial.print("Position: ");
//     Serial.print(encoderPos);
//     Serial.print(" | Direction: ");
//     Serial.println(encoderDirection ? "CW" : "CCW");
//     }

//     int stateA = digitalRead(ENCODER_PIN_A);
//     int stateB = digitalRead(ENCODER_PIN_B);

//     if(stateA == stateB)
//     {
//       encoderPos ++;
//       encoderDirection = true;
//     }
//     else
//     {
//       encoderPos --;
//       encoderDirection = false;
//     }
//   }
// }