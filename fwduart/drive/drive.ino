int pwm;
int maxi=255;
int buff1=40,buff2=-40;
void forward() {
    pwm=map(ly,buff1,127,0,maxi);
    digitalWrite(dirx,LOW);
    analogWrite(pwmx,pwm);
    digitalWrite(diry,HIGH);
    analogWrite(pwmy,pwm);
    digitalWrite(dirz,LOW);
    analogWrite(pwmz,pwm);
    digitalWrite(dirw,HIGH);
    analogWrite(pwmw,pwm); 
}
void backward() {
    pwm=map(ly,buff2,-128,0,maxi);
    digitalWrite(dirx,HIGH);
    analogWrite(pwmx,pwm);
    digitalWrite(diry,LOW);
    analogWrite(pwmy,pwm);
    digitalWrite(dirz,HIGH);
    analogWrite(pwmz,pwm);
    digitalWrite(dirw,LOW);
    analogWrite(pwmw,pwm); 
}
void rightward() {
    pwm=map(lx,buff1,127,0,maxi);
    digitalWrite(dirx,LOW);
    analogWrite(pwmx,pwm);
    digitalWrite(diry,LOW);
    analogWrite(pwmy,pwm);
    digitalWrite(dirz,LOW);
    analogWrite(pwmz,pwm);
    digitalWrite(dirw,LOW);
    analogWrite(pwmw,pwm); }
void leftward() {
    pwm=map(lx,buff2,-128,0,maxi);
    digitalWrite(dirx,HIGH);
    analogWrite(pwmx,pwm);
    digitalWrite(diry,HIGH);
    analogWrite(pwmy,pwm);
    digitalWrite(dirz,HIGH);
    analogWrite(pwmz,pwm);
    digitalWrite(dirw,HIGH);
    analogWrite(pwmw,pwm); }
void clockwise() {
    pwm=map(ry,buff1,127,0,maxi);
    digitalWrite(dirx,LOW);
    analogWrite(pwmx,pwm);
    digitalWrite(diry,LOW);
    analogWrite(pwmy,pwm);
    digitalWrite(dirz,HIGH);
    analogWrite(pwmz,pwm);
    digitalWrite(dirw,HIGH);
    analogWrite(pwmw,pwm); }
void anticlockwise() {
    pwm=map(ry,buff2,-128,0,maxi);
    digitalWrite(dirx,HIGH);
    analogWrite(pwmx,pwm);
    digitalWrite(diry,HIGH);
    analogWrite(pwmy,pwm);
    digitalWrite(dirz,LOW);
    analogWrite(pwmz,pwm);
    digitalWrite(dirw,LOW);
    analogWrite(pwmw,pwm); }
void killmotor() {
   // digitalWrite(dirx,LOW);
    analogWrite(pwmx,0);
   // digitalWrite(diry,HIGH);
    analogWrite(pwmy,0);
   // digitalWrite(dirz,HIGH);
    analogWrite(pwmz,0);
   // digitalWrite(dirw,LOW);
    analogWrite(pwmw,0); }
