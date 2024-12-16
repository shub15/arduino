#define dirx 5 //left front x
#define pwmx 3                                 // X-------Y
#define diry 7 //right front y                // |       |
#define pwmy 9                                // |       |                  
#define dirz 4 //right back z                // |       |
#define pwmz 10                                // W-------Z
#define dirw 2 //left back w
#define pwmw 11

int lx,ly,rx,ry,up,down,left,right,tri,squ,circle,cross,l1,l2,r1,r2;

int indexA,indexB,indexC,indexD,indexE,indexF,indexG,indexH,indexI,indexJ,indexK,indexL,indexM,indexN,indexO,indexP;

String data1,data2,data3,data4,data5,data6,data7,data8,data9,data10,data11,data12,data13,data14,data15,data16;

String datain;

void setup() {
  
      Serial.begin(115200);
      Serial2.begin(9600);
  
    pinMode(dirx, OUTPUT);
    pinMode(pwmx, OUTPUT);
    pinMode(diry, OUTPUT);
    pinMode(pwmy, OUTPUT);
    pinMode(dirz, OUTPUT);
    pinMode(pwmz, OUTPUT);
    pinMode(dirw, OUTPUT);
    pinMode(pwmw, OUTPUT);
}

void loop()
{
  fetch_data();
  parse_data(datain);
  ps_print();
  navigations();}
