

#include<Wire.h>
#include <FastLED.h>

const int MPU=0x68; 
int16_t AcX,AcY,AcZ;
float AcT,X,Y,Z,max,min,Xoff, Yoff,Zoff;
int i,j,test[3];
boolean check=false;
CRGB leds[300];

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, 3, RGB>(leds, 300);
  for(i=0;i<10;++i){leds[i].setRGB(255,255,255);}
  randomSeed(analogRead(0));

  FastLED.setBrightness(255);
  for(i=0;i<3000;++i){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();

  X=AcX+X;
  Y=AcY+Y;
  Z=AcZ+Z;

  leds[i%300].setRGB(random(256),random(256),random(256));
  if(i%300==0){
    for(j=0;j<300;++j){leds[j].setRGB(0,0,0);}
  }
  FastLED.show();
  }

  Xoff=X/3000;
  Yoff=Y/3000;
  Zoff=Z/3000;
  for(i=0;i<300;++i){leds[i].setRGB(0,0,0);}
}


void loop(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read(); 

  X=AcX-Xoff;  
  Y=AcY-Yoff;
  Z=AcZ-Zoff; 
  AcT=sqrt(sq(X)+sq(Y)+sq(Z));
  


if(AcT>max){
  max=AcT;
}else {
  max=max-1;
}
if(AcT<min){
  min=AcT;
}else {
  min=min+1;
}

if((AcT-min)>(max-min)*(0.75)){

  
  
  if(check==false){
    
  check=true;
  FastLED.setBrightness(255);
  for(int i=0;i<3;++i){
    test[i]=random(256);
    }

  for(i=0;i<10;++i){
    leds[i].setRGB(test[0],test[1],test[2]);
    }

  FastLED.show();
  };
 }else{
  check=false;
  
 }



FastLED.setBrightness(((AcT-min)*(255))/((max-min)));

FastLED.show();

}
