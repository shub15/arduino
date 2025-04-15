int lx, ly, rx, ry, up, down, left, right, tri, squ, circle, cross, l1, l2, r1, r2;

int indexA, indexB, indexC, indexD, indexE, indexF, indexG, indexH, indexI, indexJ, indexK, indexL, indexM, indexN, indexO, indexP;

String data1, data2, data3, data4, data5, data6, data7, data8, data9, data10, data11, data12, data13, data14, data15, data16;

String datain;

void setup() {
  Serial.begin(115200);
  Serial2.begin(57600);
}

void loop() {
  fetch_data();
  parse_data(datain);
  ps_print();
}