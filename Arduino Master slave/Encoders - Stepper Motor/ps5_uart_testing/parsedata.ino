void parse_data(String datain)
{
indexA=datain.indexOf("A");
indexB=datain.indexOf("B");
indexC=datain.indexOf("C");
indexD=datain.indexOf("D");
indexE=datain.indexOf("E");
indexF=datain.indexOf("F");
indexG=datain.indexOf("G");
indexH=datain.indexOf("H");
indexI=datain.indexOf("I");
indexJ=datain.indexOf("J");
indexK=datain.indexOf("K");
indexL=datain.indexOf("L");
indexM=datain.indexOf("M");
indexN=datain.indexOf("N");
indexO=datain.indexOf("O");
indexP=datain.indexOf("P");

data1=datain.substring(0,indexA);
data2=datain.substring(indexA+1,indexB);
data3=datain.substring(indexB+1,indexC);
data4=datain.substring(indexC+1,indexD);
data5=datain.substring(indexD+1,indexE);
data6=datain.substring(indexE+1,indexF);
data7=datain.substring(indexF+1,indexG);
data8=datain.substring(indexG+1,indexH);
data9=datain.substring(indexH+1,indexI);
data10=datain.substring(indexI+1,indexJ);
data11=datain.substring(indexJ+1,indexK);
data12=datain.substring(indexK+1,indexL);
data13=datain.substring(indexL+1,indexM);
data14=datain.substring(indexM+1,indexN);
data15=datain.substring(indexN+1,indexO);
data16=datain.substring(indexO+1,indexP);

lx=data1.toInt();
ly=data2.toInt();
rx=data3.toInt();
ry=data4.toInt();
up=data5.toInt();
down=data6.toInt();
left=data7.toInt();
right=data8.toInt();
tri=data9.toInt();
squ=data10.toInt();
circle=data11.toInt();
cross=data12.toInt();
l1=data13.toInt();
l2=data14.toInt();
r1=data15.toInt();
r2=data16.toInt();

if (abs(lx) < deadzone) {
    lx = 0;
  } else if (lx > 0) {
    lx -= deadzone;
  } else if (lx < 0) {
    lx += deadzone;
  }

  if (abs(ly) < deadzone) {
    ly = 0;
  } else if (ly > 0) {
    ly -= deadzone;
  } else if (ly < 0) {
    ly += deadzone;
  }

  if (abs(rx) < deadzone) {
    rx = 0;
  } else if (rx > 0) {
    rx -= deadzone;
  } else if (rx < 0) {
    rx += deadzone;
  }

  if (abs(ry) < deadzone) {
    ry = 0;
  } else if (ry > 0) {
    ry -= deadzone;
  } else if (ry < 0) {
    ry += deadzone;
  }
}
