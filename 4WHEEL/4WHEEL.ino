#include <Wire.h>
const int motorfrontdir1 = 4;
const int motorfrontspeed1 = 5;
const int motorfrontdir2 = 6;
const int motorfrontspeed2 =7;
const int motorbackdir1 = 8;
const int motorbackspeed1 =9;
const int motorbackdir2 = 10;
const int motorbackspeed2 = 11;
int8_t xL,xR,yL,yR,circle;
void front()
{
  digitalWrite(motorfrontdir1, LOW);    
  analogWrite(motorfrontspeed1, 100);
  digitalWrite(motorfrontdir2,LOW);
  analogWrite(motorfrontspeed2,100);
  digitalWrite(motorbackdir1,LOW);
  analogWrite(motorbackspeed1,100);
  digitalWrite(motorbackdir2,LOW);
  analogWrite(motorbackspeed2,100);
}
void back()
{
  
  digitalWrite(motorfrontdir1, HIGH);    
  analogWrite(motorfrontspeed1, 100);
  digitalWrite(motorfrontdir2,HIGH);
  analogWrite(motorfrontspeed2,100);
  digitalWrite(motorbackdir1,HIGH);
  analogWrite(motorbackspeed1,100);
  digitalWrite(motorbackdir2,HIGH);
  analogWrite(motorbackspeed2,100);
}
void left()
{
  digitalWrite(motorfrontdir1, HIGH);    
  analogWrite(motorfrontspeed1, 100);
  digitalWrite(motorfrontdir2,LOW);
  analogWrite(motorfrontspeed2,100);
  digitalWrite(motorbackdir1,LOW);
  analogWrite(motorbackspeed1,100);
  digitalWrite(motorbackdir2,HIGH);
  analogWrite(motorbackspeed2,100);
}
void right()
{
  digitalWrite(motorfrontdir1, LOW);    
  analogWrite(motorfrontspeed1, 100);
  digitalWrite(motorfrontdir2,HIGH);
  analogWrite(motorfrontspeed2,100);
  digitalWrite(motorbackdir1,HIGH);
  analogWrite(motorbackspeed1,100);
  digitalWrite(motorbackdir2,LOW);
  analogWrite(motorbackspeed2,100);
}
void clockwise()
{
  digitalWrite(motorfrontdir1, LOW);    
  analogWrite(motorfrontspeed1, 100);
  digitalWrite(motorfrontdir2,HIGH);
  analogWrite(motorfrontspeed2,100);
  digitalWrite(motorbackdir1,LOW);
  analogWrite(motorbackspeed1,100);
  digitalWrite(motorbackdir2,HIGH);
  analogWrite(motorbackspeed2,100);
}
void anticlockwise()
{
  digitalWrite(motorfrontdir1, HIGH);    
  analogWrite(motorfrontspeed1, 100);
  digitalWrite(motorfrontdir2,LOW);
  analogWrite(motorfrontspeed2,100);
  digitalWrite(motorbackdir1,HIGH);
  analogWrite(motorbackspeed1,100);
  digitalWrite(motorbackdir2,LOW);
  analogWrite(motorbackspeed2,100);
}
void northwest()
{ 
  analogWrite(motorfrontspeed1,0);
  digitalWrite(motorfrontdir2,LOW);
  analogWrite(motorfrontspeed2,100);
  digitalWrite(motorbackdir1,LOW);
  analogWrite(motorbackspeed1,100);
  analogWrite(motorbackspeed2,0);
}
void northeast()
{
  digitalWrite(motorfrontdir1,LOW);
  analogWrite(motorfrontspeed1,100);
  analogWrite(motorfrontspeed2,0);
  analogWrite(motorbackspeed2,0);
  digitalWrite(motorbackdir2,LOW);
  analogWrite(motorbackspeed2,100);
}
void southeast()
{ 
  analogWrite(motorfrontspeed1,0);
  digitalWrite(motorfrontdir2,HIGH);
  analogWrite(motorfrontspeed2,100);
  digitalWrite(motorbackdir1,HIGH);
  analogWrite(motorbackspeed1,100);
  analogWrite(motorbackspeed2,0);
}
void southwest()
{
  digitalWrite(motorfrontdir1,HIGH);
  analogWrite(motorfrontspeed1,100);
  analogWrite(motorfrontspeed2,0);
  analogWrite(motorbackspeed2,0);
  digitalWrite(motorbackdir2,HIGH);
  analogWrite(motorbackspeed2,100);
}
void setup() {
  pinMode(motorfrontdir1, OUTPUT);
  pinMode(motorfrontspeed1, OUTPUT);
  pinMode(motorfrontdir2, OUTPUT);
  pinMode(motorfrontspeed2, OUTPUT);
  pinMode(motorbackdir1, OUTPUT);
  pinMode(motorbackspeed1, OUTPUT);
  pinMode(motorbackdir2, OUTPUT);
  pinMode(motorbackspeed2, OUTPUT);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);  
  }
void receiveEvent(int bytes) {
  while (Wire.available()) {
    xL = Wire.read();
    yL = Wire.read();
    xR = Wire.read();
    yR = Wire.read();
    circle = Wire.read();   
  }
}
void loop() {
  delay(100);
  if(yL>90 && -15<xL && xL<15)
  {
    front();
  }
  else if(yL<-90 && -15<xL && xL<15)
  {
    back();
  }
  else if(xL<-90 && -15<yL && yL<15)
  {
    left();
  }
  else if(xL>90 && -15<yL && yL<15)
  {
    right();
  }
  else
  {
    analogWrite(motorfrontspeed1,0);
    analogWrite(motorfrontspeed2,0);
    analogWrite(motorbackspeed2,0);
    analogWrite(motorbackspeed2,0);
  }
}
    
 
  
