#include <math.h>
#include <Wire.h>
#include <HardwareSerial.h>
#define pi 3.1415926535
int motorfrontdir = 30;
int motorfrontpwm = 4;
int motorreardirl = 28;
int motorrearpwml = 10;
int motorreardirr = 26;
int motorrearpwmr = 3;
#define l0 0.3
double wfl, wfr, wrl, wrr, wz;
const double r = 75;
double target_wf = 0, target_wrl = 0, target_wrr = 0;
double current_wf = 0, current_wrl = 0, current_wrr = 0;
const double decelerationRate = 2.0;
double w;
double rL, thetaL, rR, thetaR;
const int deadzone = 40;
// int lx, ly, rx, ry, up, down, left, right, tri, squ, circle, cross, l1, l2, r1, r2;
int8_t lx, ly, rx, ry, up, down, left, right, tri, squ, circle, cross, l1, l2, r1, r2;
int indexA, indexB, indexC, indexD, indexE, indexF, indexG, indexH, indexI, indexJ, indexK, indelx, indexM, indexN, indexO, indexP;
String data1, data2, data3, data4, data5, data6, data7, data8, data9, data10, data11, data12, data13, data14, data15, data16;
String datain;

//ebike
const int ebike_dir_pin = 50;
const int ebike_speed_pin = 3;

int ebike_running = 0;
int32_t drib_speed = 45;

//pneumatic
const int pneumatic = 32;
static int pneumatic_open = 0;

static int prev_cir = 0;
static int prev_tri = 0;
static int prev_cro = 0;
static int prev_squ = 0;
static int prev_ll1 = 0;
static int prev_rr1 = 0;
static int prev_ll2 = 0;
static int prev_rr2 = 0;

// void fetch_data() {
//   if (Serial2.available() > 0) {
//     datain = Serial2.readStringUntil('!');
//   }
// }
// void parse_data(String datain) {
//   indexA = datain.indexOf("A");
//   indexB = datain.indexOf("B");
//   indexC = datain.indexOf("C");
//   indexD = datain.indexOf("D");
//   indexE = datain.indexOf("E");
//   indexF = datain.indexOf("F");
//   indexG = datain.indexOf("G");
//   indexH = datain.indexOf("H");
//   indexI = datain.indexOf("I");
//   indexJ = datain.indexOf("J");
//   indexK = datain.indexOf("K");
//   indelx = datain.indexOf("L");
//   indexM = datain.indexOf("M");
//   indexN = datain.indexOf("N");
//   indexO = datain.indexOf("O");
//   indexP = datain.indexOf("P");

//   data1 = datain.substring(0, indexA);
//   data2 = datain.substring(indexA + 1, indexB);
//   data3 = datain.substring(indexB + 1, indexC);
//   data4 = datain.substring(indexC + 1, indexD);
//   data5 = datain.substring(indexD + 1, indexE);
//   data6 = datain.substring(indexE + 1, indexF);
//   data7 = datain.substring(indexF + 1, indexG);
//   data8 = datain.substring(indexG + 1, indexH);
//   data9 = datain.substring(indexH + 1, indexI);
//   data10 = datain.substring(indexI + 1, indexJ);
//   data11 = datain.substring(indexJ + 1, indexK);
//   data12 = datain.substring(indexK + 1, indelx);
//   data13 = datain.substring(indelx + 1, indexM);
//   data14 = datain.substring(indexM + 1, indexN);
//   data15 = datain.substring(indexN + 1, indexO);
//   data16 = datain.substring(indexO + 1, indexP);

//   lx = data1.toInt();
//   ly = data2.toInt();
//   rx = data3.toInt();
//   ry = data4.toInt();
//   cross = data5.toInt();
//   squ = data6.toInt();
//   tri = data7.toInt();
//   circle = data8.toInt();
//   up = data9.toInt();
//   down = data10.toInt();
//   left = data11.toInt();
//   right = data12.toInt();
//   l1 = data13.toInt();
//   l2 = data14.toInt();
//   r1 = data15.toInt();
//   r2 = data16.toInt();

//   rL = sqrt(lx * lx + ly * ly);
//   thetaL = atan2(lx, ly);
//   rR = sqrt(rx * rx + ry * ry);
//   thetaR = atan2(ry, rx);
// }
// void ps_print() {

//   Serial.print("lx=");
//   Serial.print(lx);
//   Serial.print(", ");
//   Serial.print("ly=");
//   Serial.print(ly);
//   Serial.print(", ");
//   Serial.print("rx=");
//   Serial.print(rx);
//   Serial.print(", ");
//   Serial.print("ry=");
//   Serial.print(ry);
//   Serial.print(" ");

//   //  // Serial.print("up=");
//   //   Serial.print(up);
//   //   Serial.print(", ");
//   //  // Serial.print("dowm=");
//   //   Serial.print(down);
//   //   Serial.print(", ");
//   // //  Serial.print("left=");
//   //   Serial.print(left);
//   //   Serial.print(", ");
//   // //  Serial.print("right=");
//   //   Serial.print(right);
//   //   Serial.print(",");

//   Serial.print("tri=");
//   Serial.print(tri);
//   Serial.print(", ");
//   Serial.print("squ=");
//   Serial.print(squ);
//   Serial.print(", ");
//   Serial.print("circle=");
//   Serial.print(circle);
//   Serial.print(", ");
//   Serial.print("cross=");
//   Serial.print(cross);
//   Serial.print(", ");

//   Serial.print("l1=");
//   Serial.print(l1);
//   Serial.print(", ");
//   Serial.print("l2=");
//   Serial.print(l2);
//   Serial.print(", ");
//   Serial.print("r1=");
//   Serial.print(r1);
//   Serial.print(", ");
//   Serial.print("r2=");
//   Serial.println(r2);
//   // delay(500);
// }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Serial2.begin(500000);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  pinMode(motorfrontpwm, OUTPUT);
  pinMode(motorfrontdir, OUTPUT);
  pinMode(motorrearpwml, OUTPUT);
  pinMode(motorreardirl, OUTPUT);
  pinMode(motorrearpwmr, OUTPUT);
  pinMode(motorreardirr, OUTPUT);
}
void receiveEvent(int bytes) {
  while (Wire.available()) {
    lx = Wire.read();
    ly = Wire.read();
    rx = Wire.read();
    ry = Wire.read();
    tri = Wire.read();
    circle = Wire.read();
    cross = Wire.read();
    squ = Wire.read();
    l2 = Wire.read();
    r2 = Wire.read();
    // Serial.println("Recevied!");
    wz = rx;
    if (abs(lx) < deadzone) lx = 0;
    else lx = (lx > 0) ? lx - deadzone : lx + deadzone;

    if (abs(ly) < deadzone) ly = 0;
    else ly = (ly > 0) ? ly - deadzone : ly + deadzone;

    if (abs(rx) < deadzone) rx = 0;
    else rx = (rx > 0) ? rx - deadzone : rx + deadzone;

    if (abs(ry) < deadzone) ry = 0;
    else ry = (ry > 0) ? ry - deadzone : ry + deadzone;
    rL = sqrt(lx * lx + ly * ly);
    thetaL = atan2(lx, ly);
    rR = sqrt(rx * rx + ry * ry);
    thetaR = atan2(ry, rx);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  // fetch_data();
  // parse_data(datain);
  // ps_print();
  compute3wheel();
  applyDeceleration();

  Serial.print(lx);
  Serial.print(" ");
  Serial.print(ly);
  Serial.print(" ");
  Serial.print(rx);
  Serial.print(" ");
  Serial.print(ry);
  Serial.print(" ");
  Serial.print(drib_speed);
  Serial.print(" ");
  Serial.print(ebike_running);
  Serial.print(" ");
  Serial.println(pneumatic_open);
  /* Dribbling */
  if (tri == 1 && !prev_tri) {
    ebike_running = 1;
  }
  if (cross == 1 && !prev_cro) {  // cro button pressed
    ebike_running = 0;
  }
  if (l2 == 1 && !prev_ll2) {
    drib_speed = drib_speed + 2;  //62 speed for passing 50 for dribbling
  }
  if (r2 == 1 && !prev_rr2) {
    drib_speed = drib_speed - 2;
  }
  if (drib_speed < 0) {
    drib_speed = 0;
  }
  if (drib_speed > 100) {
    drib_speed = 100;
  }

  prev_tri = tri;
  prev_cro = cross;
  prev_ll2 = l2;
  prev_rr2 = r2;

  if (ebike_running) {
    // Serial.println("Ebike running");
    int speed = map(drib_speed, 0, 100, 0, 255);  //rpm 2000 test
    digitalWrite(ebike_dir_pin, LOW);
    analogWrite(ebike_speed_pin, 255);
  } else {
    analogWrite(ebike_speed_pin, 0);
  }

  // pneumatics
  if (squ == 1) {
    pneumatic_open = 1;
  } else {
    pneumatic_open = 0;
  }
  //		prev_squ = squ;
  if (pneumatic_open) {
    // Serial.println("Pnematic open");
    digitalWrite(pneumatic, HIGH);
  } else {
    digitalWrite(pneumatic, LOW);
  }
}
void compute3wheel() {
  // Calculate joystick-based velocities
  const double theta = -30 * pi / 180;
  double lx_rotated = lx * cos(theta) - ly * sin(theta);
  double ly_rotated = lx * sin(theta) + ly * cos(theta);
  double vx = ly_rotated;
  double vy = lx_rotated;
  w = rx;
 double speedFactorL = 3*(rL/88+rR/88)/2;    
    // Modify wheel velocities to include yaw correction
    target_wf = ((-0.5*vx) + (sqrt(3)/2)*vy + l0*w) * speedFactorL;
    target_wrr = ((-0.5*vx)-(sqrt(3)/2)*vy + l0*w) * speedFactorL;
    target_wrl = (vx+l0*w) * speedFactorL;
    // target_wf=(-0.866*vx + (1/2)*vy + l0*w)*speedFactorL;
    // target_wrr = (0.866*vx + (1/2)*vy + l0*w)*speedFactorL;
    // target_wrl = (-vx + l0*w)*speedFactorL;
    // Constrain target wheel speeds
    target_wf = constrain(target_wf, -100, 100);
    target_wrr = constrain(target_wrr, -100, 100);
    target_wrl = constrain(target_wrl, -100, 100);
}

void applyDeceleration() {
    // Gradually approach target speeds for each wheel
    current_wf += (target_wf-current_wf)/decelerationRate;
    current_wrl += (target_wrl-current_wrl)/decelerationRate;
    current_wrr += (target_wrr-current_wrr)/decelerationRate;
    
    // Serial.print("wf =");
    // Serial.print(current_wf);
    // Serial.print("wrr =");
    // Serial.print(current_wrr);
    // Serial.print("wrl =");
    // Serial.println(current_wrl);
    
    // Update motor directions a000000.nd speeds based on decelerated values
    if (current_wf >= 0) {
        digitalWrite(motorfrontdir, LOW);
        analogWrite(motorfrontpwm, current_wf);
    } else {
        digitalWrite(motorfrontdir, HIGH);
        analogWrite(motorfrontpwm, -current_wf);
    }
    
    if (current_wrl >= 0) {
        digitalWrite(motorreardirl, LOW);
        analogWrite(motorrearpwml, current_wrl);
    } else {
        digitalWrite(motorreardirl, HIGH);
        analogWrite(motorrearpwml, -current_wrl);
    }
    
    if (current_wrr >= 0) {
        digitalWrite(motorreardirr, LOW);
        analogWrite(motorrearpwmr, current_wrr);
    } else {
        digitalWrite(motorreardirr, HIGH);
        analogWrite(motorrearpwmr, -current_wrr);
    }
}