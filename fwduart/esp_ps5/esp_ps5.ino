#include <ps5Controller.h>
int lx, ly, rx, ry, cro, squ, tri, cir, upp, downn, leftt, rightt, ll1, ll2, rr1, rr2, start, options, share;
#include <HardwareSerial.h>
#define RXp2 16
#define TXp2 17
void send(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l, int m, int n, int o, int p, int q, int r, int s) {


  Serial2.print(a);
  Serial2.print("A");
  Serial2.print(b);
  Serial2.print("B");
  Serial2.print(c);
  Serial2.print("C");
  Serial2.print(d);
  Serial2.print("D");
  Serial2.print(e);
  Serial2.print("E");
  Serial2.print(f);
  Serial2.print("F");
  Serial2.print(g);
  Serial2.print("G");
  Serial2.print(h);
  Serial2.print("H");
  Serial2.print(i);
  Serial2.print("I");
  Serial2.print(j);
  Serial2.print("J");
  Serial2.print(k);
  Serial2.print("K");
  Serial2.print(l);
  Serial2.print("L");
  Serial2.print(m);
  Serial2.print("M");
  Serial2.print(n);
  Serial2.print("N");
  Serial2.print(o);
  Serial2.print("O");
  Serial2.print(p);
  Serial2.print("P");
  Serial2.print(q);
  Serial2.print("Q");
  Serial2.print(r);
  Serial2.print("R");
  Serial2.print(s);
  Serial2.print("S");
  Serial2.print("!");
  // Serial.print(a);
}

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);

  //  ps5.begin("7C:66:EF:78:76:F0");dev
  ps5.begin("e8:47:3a:5a:a3:66");  //  MAC Address of PS5 Controller is 7C:66:EF:78:76:F0
                                   //Ps3.begin("b4:e6:2d:e9:58:9d");// myesp
  //Ps3.begin("c8:c9:a3:fb:21:ee"); //  aayush1
  //Ps3.begin("30:c6:f7:23:d3:e6");

  //
  //  Serial2.println("AT+IPR=9600");
  //  delay(1000);
  //  Serial2.end();
  //  // Start the software serial for communication with the ESP8266
  //  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  //
  //  Serial.println("Ready");
  //  Serial2.println("AT+GMR");
}

void loop() {

  if (ps5.isConnected()) {

    lx = (ps5.LStickX());
    ly = (ps5.LStickY());
    rx = (ps5.RStickX());
    ry = (ps5.RStickY());
    cro = (ps5.Cross());
    squ = (ps5.Square());
    tri = (ps5.Triangle());
    cir = (ps5.Circle());
    // upp=(Ps3.data.analog.button.up);
    //downn=(Ps3.data.analog.button.down);
    // leftt=(Ps3.data.analog.button.left);
    // rightt=(Ps3.data.analog.button.right);
    upp = (ps5.Up());
    downn = (ps5.Down());
    leftt = (ps5.Left());
    rightt = (ps5.Right());

    ll1 = (ps5.L1());
    rr1 = (ps5.R1());
    //ll1=(Ps3.data.button.l1);
    //rr1=(Ps3.data.button.r1);

    ll2 = (ps5.L2());
    rr2 = (ps5.R2());
    start = (ps5.Touchpad());
    options = (ps5.Options());
    share = (ps5.Share());
    //Serial.printf("Battery Level : %d\n", ps5.Battery());

    // Serial.println(ll1);


    //if (lx==-1){lx=0;}
    //if (ly==-1){ly=0;}
    //if (rx==-1){rx=0;}
    //if (ry==-1){ry=0;}
    // Serial.print("LX = ");
    // Serial.print(lx);
    // Serial.print(" ");
    //  Serial.print("LY = ");
    // Serial.print(ly);
    // Serial.print(" ");
    //
    // Serial.print("RX = ");
    // Serial.print(rx);
    // Serial.print(" ");
    //
    // Serial.print("RY = ");
    // Serial.print(ry);
    // Serial.print(" ");

    // Serial.print("LX = ");
    // Serial.print(lX);
    // Serial.print(" ");
    //
    //    Serial.print(lY); Serial.print("B");
    //    Serial.print(rX); Serial.print("C");
    //    Serial.print(rY); Serial.print("D");
    Serial.print("\n");

  } else {
    lx = 0;
    ly = 0;
    rx = 0;
    ry = 0;
    cro = 0;
    squ = 0;
    tri = 0;
    cir = 0;
    upp = 0;
    downn = 0;
    leftt = 0;
    rightt = 0;
    ll1 = 0;
    rr1 = 0;
    ll2 = 0;
    rr2 = 0;
    start = 0;
    options = 0;
    share = 0;
  }
  send(lx, ly, rx, ry, cro, squ, tri, cir, upp, downn, leftt, rightt, ll1, ll2, rr1, rr2, start, options, share);
}
