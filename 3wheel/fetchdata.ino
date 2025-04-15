void fetch_data() {
  if (Serial2.available() > 0) {
    datain = Serial2.readStringUntil('!');
  }
}