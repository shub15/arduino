//int buff1=25,buff2=-50;

void navigations()
{
  if (((lx>-128 && lx<127) ||(ly>-128 && ly<127) || (rx>-128 && rx<127) 
  || (ry>-128 && ry<127)) && (lx>buff1 || lx<buff2 || ly>buff1 || ly<buff2
  ||rx>buff1 || rx<buff2 || ry>buff1 || ry<buff2))
 {
  if ( ly>buff1 && ( lx>buff2 && lx<buff1 ))
  {
    map(ly,buff1,127,0,255);
    forward();
  }
  else if ( ly<buff2 && ( lx>buff2 && lx<buff1))
  {
    backward();
  }
  else if ( lx>buff1 && ( ly>buff2 && ly<buff1 ))
  {
    rightward();
  }
  else if ( lx<buff2 && ( ly>buff2 && ly<buff1 ))
  {
    leftward();
  }
  else if ( ry>buff1 && ( rx>buff2 && rx<buff1 ))
  {
    clockwise();
  }
  else if ( ry<buff2 && ( rx>buff2 && rx<buff1 ))
  {
    anticlockwise();
  }
 }
 else
 {
  killmotor();
 }
}
